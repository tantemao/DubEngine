#include "Precompiled.h"
#include "CameraComponent.h"

#include "GameWorld.h"
#include "CameraService.h"
using namespace DubEngine;
void CameraComponent::Initialize()
{
	CameraService* cameraService = GetOwner().GetWorld().GetService<CameraService>();
	ASSERT(cameraService != nullptr, "CameraComponent:CameraService is not available");
	cameraService->Register(this);
}

void CameraComponent::Terminate()
{
	CameraService* cameraService = GetOwner().GetWorld().GetService<CameraService>();
	ASSERT(cameraService != nullptr, "CameraComponent:CameraService is not available");
	cameraService->Unregister(this);
}

void CameraComponent::Deserialize(rapidjson::Value& value)
{
	if (value.HasMember("Position"))
	{
		const auto& pos = value["Position"].GetArray();
		float x = pos[0].GetFloat();
		float y = pos[1].GetFloat();
		float z = pos[2].GetFloat();
		mCamera.SetPosition({ x,y,z });
	}
	if (value.HasMember("LookAt"))
	{
		const auto& lookAt = value["LookAt"].GetArray();
		float x = lookAt[0].GetFloat();
		float y = lookAt[1].GetFloat();
		float z = lookAt[2].GetFloat();
		mCamera.SetLookAt({ x,y,z });
	}
}
