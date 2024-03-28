#include "Framework.h"

CookieAction::CookieAction(string file, bool isLoop, float speed)
    : Action("Resources/Textures/Cookie/", file, isLoop, speed)
{
}

void CookieAction::Move()
{
    if (KEY->Press(VK_RIGHT))
    {
        velocity.x = 1.0f;
        //target->SetLocalScale(1, 1);
        target->SetLocalRotation(0.0f, 0.0f, 0.0f);
    }

    if (KEY->Press(VK_LEFT))
    {
        velocity.x = -1.0f;
        //target->SetLocalScale(-1, 1);
        target->SetLocalRotation(0.0f, XM_PI, 0.0f);
    }

    target->Translate(Vector2::Right() * velocity.x * MOVE_SPEED * DELTA);
}
