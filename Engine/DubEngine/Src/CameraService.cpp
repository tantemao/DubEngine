#include "Precompiled.h"
#include"CameraComponent.h"
#include"CameraService.h"

using namespace DubEngine;
using namespace DubEngine::Graphics;

const Camera& CameraService::GetMain() const
{
	ASSERT(mMainCamera != nullptr, "dsds");
	return
}
class CameraComponent;

//const Camera& CameraService final :public Service


void CameraService::Register(const CameraComponent* cameraComponent)
{
	mCameraEntries.push_back(cameraComponent);
}

void CameraService::Register(const CameraComponent* cameraComponent)
{
	auto iter = std::find(mCameraEntries.begin(), mCameraEntries.end(), cameraComponent);
	if (iter != mCameraEntries.end())
	{
		if (mMainCamera == *iter)
		{
			mMainCamera = nullptr;
		}
		mCameraEntries.ease
	}
}