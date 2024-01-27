#include "GameState.h"
using namespace DubEngine;
using namespace DubEngine::Graphics;
using namespace DubEngine::Input;

void GameState::Initialize()
{

	CameraComponent* cameraComponent = mCameraObject1.AddComponent<CameraComponent>();
	cameraComponent->GetCamera().SetPosition({ 1.0f, 1.5f, -4.0f });
	cameraComponent->GetCamera().SetLookAt({ 0.0f, 0.0f, 0.0f });
	
	
	GameObjectFactory::Make("../../Assets/Templates/text_object.json", mGameObject);
	mGameObject.Initialize();
}
void GameState::Terminate()
{
	mGameObject.Terminate();
}

void GameState::Update(float deltaTime)
{

	CameraComponent* cameraComponent = mCameraGameObject1.GetComponent<CameraComponent>();

	// movement
	auto input = InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}

	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}

	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}

void GameState::Render()
{

}

void GameState::DebugUI()
{
	mGameObject.DebugUI();
	SimpleDraw::Render(mCameraService.GetMain());
}
