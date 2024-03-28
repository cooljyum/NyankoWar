#include "Framework.h"

void CookieJump::Update()
{
    velocity.y -= GRAVITY * DELTA;
    target->Translate(Vector2::Up() * velocity.y * DELTA);

    Move();

    Action::Update();
}
