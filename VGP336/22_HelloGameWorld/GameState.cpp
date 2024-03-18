#include "GameState.h"
using namespace DubEngine;
using namespace DubEngine::Graphics;
using namespace DubEngine::Input;

void GameState::Initialize()
{
	mGameWorld.AddService<CameraService>();
	mGameWorld.AddService<UpdateService>();
	mGameWorld.Initialize(1000);
	mGameWorld.CreatGameObject("../../Assets/Templates/test_object.json");
	mGameWorld.CreatGameObject("../../Assets/Templates/test_camera.json");
	mGameWorld.CreatGameObject("../../Assets/Templates/test_fps_canmera.json");

}
void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Render()
{
	mGameWorld.Render();
}
void GameState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
	auto input = InputSystem::Get();
	
	if (input->IsKeyPressed(KeyCode::ONE))
	{
		CameraService* cameraService = mGameWorld.GetService<CameraService>();
		cameraService->SetMainCamera(0);
	}

	else if (input->IsKeyPressed(KeyCode::TWO))
	{
		CameraService* cameraService = mGameWorld.GetService<CameraService>();
		cameraService->SetMainCamera(1);
	}
}


void GameState::DebugUI()
{
	mGameWorld.DebugUI();
	/*CameraService* cameraService = mGameWorld.GetService<CameraService>();
	SimpleDraw::Render(cameraService->GetMain());*/
}
