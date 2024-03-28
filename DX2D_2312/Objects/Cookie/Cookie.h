#pragma once

class Cookie : public GameObject
{
public:
    enum State
    {
        IDLE, RUN, JUMP_UP, JUMP_DOWN, JUMP_DOUBLE
    };

public:
    Cookie();
    ~Cookie();

    void Update() override;
    void Render() override;

private:
    void Move();
    void Jump();    

    void Landing();

    void SetAction(int state);

    void CreateActions();

private:
    map<State, Action*> actions;

    State curState = IDLE;

    int jumpCount = 0;
};