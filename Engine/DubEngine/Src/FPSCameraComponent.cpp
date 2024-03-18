#include"Precompiled.h"
#include"FPSCameraComponent.h"

#include"UpdateService.h"
#include"GameWorld.h"
#include"CameraComponent.h"

using namespace DubEngine;
using namespace DubEngine::Input;
using namespace DubEngine::Graphics;

void FPSCameraComponent::Initialize()
{
	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "FPSCameraComponent: updateservice is unavailable");
	updateService->Register(this);
}

void FPSCameraComponent::Terminate()
{
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "FPSCameraComponent: updateservice is unavailable");
	updateService->UnRegister(this);
	mCameraComponent = nullptr;
}

void FPSCameraComponent::Update(float deltaTime)
{
	Camera& camera = mCameraComponent->GetCamera();
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? mMoveSpeed*  10.0f : mMoveSpeed)*deltaTime;
	const float turnSpeed = mTurnSpeed;
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
}

void FPSCameraComponent::Deserialize(rapidjson::Value& value)
{
	if (value.HasMember("MoveSpeed"))
	{
		mMoveSpeed = value["MoveSpeed"].GetFloat();
	}
	if (value.HasMember("TurnSpeed"))
	{
		mTurnSpeed = value["TurnSpeed"].GetFloat();
	}
}
