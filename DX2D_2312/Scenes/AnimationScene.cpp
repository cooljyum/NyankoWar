#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
    cookie = new Cookie();
    cookie->SetLocalPosition(CENTER);
}

AnimationScene::~AnimationScene()
{
}

void AnimationScene::Update()
{
}

void AnimationScene::Render()
{
}

void AnimationScene::PostRender()
{
}
