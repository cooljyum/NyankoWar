#include "Framework.h"

Cookie::Cookie()
{
    Observer::Get()->AddIntEvent("SetAction", bind(&Cookie::SetAction, this, placeholders::_1));
    Observer::Get()->AddEvent("Landing", bind(&Cookie::Landing, this));

    CreateActions();
    actions[curState]->Start();
}

Cookie::~Cookie()
{
    for (auto action : actions)
        delete action.second;
}

void Cookie::Update()
{
    Move();
    Jump();

    actions[curState]->Update();

    UpdateWorld();
}

void Cookie::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    actions[curState]->Render();
}

void Cookie::Move()
{
    if (curState == JUMP_UP || curState == JUMP_DOWN || curState == JUMP_DOUBLE)
        return;

    bool isMove = false;

    isMove |= KEY->Press(VK_RIGHT);
    isMove |= KEY->Press(VK_LEFT);

    isMove ? SetAction(RUN) : SetAction(IDLE);
}

void Cookie::Jump()
{
    if (curState == JUMP_UP)
        return;

    if (KEY->Down(VK_UP))
    {
        if (jumpCount == 0)
        {
            SetAction(JUMP_UP);            
        }
        else if(jumpCount == 1)
        {
            SetAction(JUMP_DOUBLE);            
        }

        jumpCount++;
    }
}

void Cookie::Landing()
{
    SetAction(IDLE);

    jumpCount = 0;
}

void Cookie::SetAction(int state)
{
    if (curState == state) return;

    curState = (State)state;
    actions[curState]->Start();
}

void Cookie::CreateActions()
{
    actions[IDLE] = new CookieAction("Cookie_Idle.xml", true, 0.7f);
    actions[RUN] = new CookieRun(this);
    actions[JUMP_UP] = new CookieJumpUp(this);    
    actions[JUMP_DOWN] = new CookieJumpDown(this);    
    actions[JUMP_DOUBLE] = new CookieJumpDouble(this);        
}