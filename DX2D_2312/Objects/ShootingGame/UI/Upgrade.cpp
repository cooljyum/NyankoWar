#include "Framework.h"

Upgrade::Upgrade() : Panel(L"Resources/Textures/UI/UpgradePanel.png")
{
    SetActive(true);

    CreateSlots();

    excuteBtn = new Button();
    excuteBtn->SetText("�ռ�");
    excuteBtn->SetEvent(bind(&Upgrade::Excute, this));
    excuteBtn->SetParent(this);    
    excuteBtn->SetTag("ExcuteBtn");
    excuteBtn->Load();
}

Upgrade::~Upgrade()
{
    for (Quad* slot : slots)
        delete slot;

    delete excuteBtn;
}

void Upgrade::Update()
{
    if (!IsActive()) return;

    Panel::Update();

    for (Quad* slot : slots)
        slot->Update();

    for (Item* item : items)
        item->Update();

    excuteBtn->Update();
}

void Upgrade::Render()
{
    if (!IsActive()) return;

    Panel::Render();

    for (Quad* slot : slots)
    {
        slot->Render();        
    }

    for (Item* item : items)
    {
        item->Render();        
    }

    excuteBtn->Render();
    excuteBtn->RenderUI();
}

void Upgrade::AddItem(void* item)
{
    if (count == slots.size())
        return;

    Item* temp = (Item*)item;

    if (temp->GetCount() == 0)
        return;

    temp->AddCount(-1);
    //items[count++]->SetData(temp->GetData());
    FOR(items.size())
    {
        if (items[i]->IsActive()) continue;

        items[i]->SetData(temp->GetData());
        selectItems[i] = temp;
        break;
    }

    count++;
}

void Upgrade::CreateSlots()
{
    selectItems.resize(3);

    FOR(3)
    {
        Quad* slot = new Quad(L"Resources/Textures/UI/ItemSlot.png", false);
        slot->SetParent(this);
        slot->SetLocalPosition(0, 0);
        slot->SetTag("UpgradeSlot" + to_string(i));
        slot->Load();

        slots.push_back(slot);

        Item* item = new Item();
        item->SetParent(slot);
        item->SetObjectEvent(bind(&Upgrade::RemoveItem, this, placeholders::_1), item);
        items.push_back(item);
    }
}

void Upgrade::RemoveItem(void* item)
{
    Item* temp = (Item*)item;

    temp->SetActive(false);

    FOR(items.size())
    {
        if (item == items[i])
        {
            selectItems[i]->AddCount(1);
            break;
        }
    }

    count--;
}

void Upgrade::Excute()
{
    //1. items�ȿ� �ִ� �������� Ű���� �� ������ üũ
    //2. ���е� �����̵� �ϴ� ������ ����â ������ �� ����
    //3. ����->�κ��丮 �ִ� ������ �� ���ҽ�Ű�� ���� 1���� ������ ȹ��    
    //4. ���и� �κ��丮 â�� ������ ī��Ʈ ����

    for (Item* item : items)
        item->SetActive(false);

    if (IsCheck())
        UpgradeSuccess();
    else
        UpgradeFail();
}

bool Upgrade::IsCheck()
{
    if (count < items.size())
        return false;

    checkKey = items.front()->GetData().key;

    for (Item* item : items)
    {
        if (item->GetData().key != checkKey)
            return false;
    }

    return true;
}

void Upgrade::UpgradeSuccess()
{
    Inventory* inventory = (Inventory*)GetParent();

    inventory->CreateItem(checkKey + 1, 1);

    count = 0;

    inventory->Clear();
}

void Upgrade::UpgradeFail()
{
    for (Item* item : items)
        RemoveItem(item);
}
