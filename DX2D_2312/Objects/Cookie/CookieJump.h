#pragma once

class CookieJump : public CookieAction
{
protected:
    const float JUMP_POWER = 500.0f;

public:
    CookieJump() = default;
    ~CookieJump() = default;

    virtual void Update() override;
};