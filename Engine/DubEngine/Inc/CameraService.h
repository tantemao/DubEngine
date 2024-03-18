#pragma once

#include"Service.h"
namespace DubEngine
{
	class CameraComponent;

	class CameraService final :public Service
	{
	public:
		SET_TYPE_ID(ServiceId::Camera);

		const Graphics::Camera& GetMain() const;
		void SetMainCamera(uint32_t index);
		void Register(const CameraComponent* cameraComponent);
		void Unregister(const CameraComponent* cameraComponent);

	private:

		using CameraEntries = std::vector<const CameraComponent*>;
		CameraEntries mCameraEntries;
		const CameraComponent* mMainCamera = nullptr;
		
	};
}