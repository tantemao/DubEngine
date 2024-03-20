#include"Precompiled.h"
#include"FPSCameraComponent.h"

#include"UpdateService.h"
#include"GameWorld.h"
#include"CameraComponent.h"
#include"TransformComponent.h"

using namespace DubEngine;
using namespace DubEngine::Input;
using namespace DubEngine::Graphics;

void FPSCameraComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "FPSCameraComponent: updateservice is unavailable");
	updateService->Register(this);
}

void FPSCameraComponent::Terminate()
{
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "FPSCameraComponent: updateservice is unavailable");
	updateService->Unregister(this);
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
		camera.Walk(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		camera.Walk(-moveSpeed );
	}

	if (input->IsKeyDown(KeyCode::D))
	{
		camera.Strafe(moveSpeed );
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		camera.Strafe(-moveSpeed );
	}

	if (input->IsKeyDown(KeyCode::E))
	{
		camera.Rise(moveSpeed );
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		camera.Rise(-moveSpeed );
	}

	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		camera.Yaw(input->GetMouseMoveX() * turnSpeed );
		camera.Pitch(input->GetMouseMoveY() * turnSpeed );
	}
	if (mTransformComponent != nullptr)
	{
		mTransformComponent->position = camera.GetPosition();
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
