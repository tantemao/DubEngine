#include "GameState.h"
using namespace DubEngine;
using namespace DubEngine::Graphics;
using namespace DubEngine::Input;

void GameState::Initialize()
{

	CameraComponent* cameraComponent = mCameraGameObject1.AddComponent<CameraComponent>();
	cameraComponent->GetCamera().SetPosition({ 0.0f, 1.5f, -4.0f });
	cameraComponent->GetCamera().SetLookAt({ 0.0f, 0.0f, 0.0f });
	mCameraService.Register(cameraComponent);
	
	cameraComponent = mCameraGameObject2.AddComponent<CameraComponent>();
	cameraComponent->GetCamera().SetPosition({ 0.0f, 1.5f, -4.0f });
	cameraComponent->GetCamera().SetLookAt({ 0.0f, 0.0f, 0.0f });
	mCameraService.Register(cameraComponent);


	GameObjectFactory::Make("../../Assets/Templates/text_object.json", mGameObject);
	mGameObject.Initialize();
}
void GameState::Terminate()
{
	mGameObject.Terminate();
}

void GameState::Render()
{

}
void GameState::Update(float deltaTime)
{

	CameraComponent* cameraComponent = mCameraGameObject1.GetComponent<CameraComponent>();
	Camera & camera = cameraComponent->GetCamera();
	auto input = InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		camera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		camera.Walk(-moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::D))
	{
		camera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		camera.Strafe(-moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::E))
	{
		camera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		camera.Rise(-moveSpeed * deltaTime);
	}

	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		camera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		camera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	if (input->IsKeyPressed(KeyCode::ONE))
	{
		mCameraService.SetMainCamera(0);
	}

	if (input->IsKeyPressed(KeyCode::TWO))
	{
		mCameraService.SetMainCamera(1);
	}
}


void GameState::DebugUI()
{
	mGameObject.DebugUI();
	SimpleDraw::Render(mCameraService.GetMain());
}
