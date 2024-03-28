#include "Framework.h"

CookieJumpDown::CookieJumpDown(Transform* target)
{
    SetTarget(target);

    LoadClip(PATH, "Cookie_JumpDown.xml", false);
}

void CookieJumpDown::Update()
{
    CookieJump::Update();

    if (target->GetGlobalPosition().y < FLOOR_HEIGHT)
    {
        Observer::Get()->ExcuteEvent("Landing");
    }
}

void CookieJumpDown::Start()
{
    Action::Start();
    velocity.y = 0.0f;
}
