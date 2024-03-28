#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/ShootingGameScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/AnimationScene.h"

GameManager::GameManager()
{
	Create();

	//SCENE->Add("Start", new TutorialScene());
	//SCENE->Add("Start", new ShootingGameScene());
	//SCENE->Add("Start", new CollisionScene());
	SCENE->Add("Start", new AnimationScene());

	SCENE->ChangeScene("Start");
}

GameManager::~GameManager()
{
	Delete();
}

void GameManager::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();

	Environment::Get()->Update();
	ObjectManager::Get()->Update();
	SCENE->Update();
}

void GameManager::Render()
{
	Device::Get()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Font::Get()->SetColor("White");
	Font::Get()->SetStyle("Default");

	Font::Get()->GetDC()->BeginDraw();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	Font::Get()->RenderText(fps, { 0, SCREEN_HEIGHT - 10 });

	ObjectManager::Get()->Render();
	SCENE->Render();	

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Font::Get()->GetDC()->EndDraw();
	Device::Get()->Present();
}

void GameManager::Create()
{
	Keyboard::Get();
	Timer::Get();
	Environment::Get();
	Font::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);

	Font::Get()->AddColor("White", 1, 1, 1);
	Font::Get()->AddColor("Black", 0, 0, 0);
	Font::Get()->AddStyle("Default", L"��� ������10����ü");	
	Font::Get()->AddStyle("Button", L"���� ���", 40,
		DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_FAR);
}

void GameManager::Delete()
{
	SceneManager::Delete();	
	Keyboard::Delete();
	Timer::Delete();
	Font::Delete();

	Shader::Delete();
	Texture::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}
