#pragma once

class CookieJumpDown : public CookieJump
{
private:
    const float FLOOR_HEIGHT = 200.0f;

public:
    CookieJumpDown(Transform* target);
    
    void Update() override;
    void Start() override;
};