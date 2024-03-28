#include "Framework.h"

CookieRun::CookieRun(Transform* target)
    : CookieAction("Cookie_Run.xml", true)
{
    SetTarget(target);
}

void CookieRun::Update()
{
    Move();    

    Action::Update();
}