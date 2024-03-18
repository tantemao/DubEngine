#pragma once

#include "Component.h"

namespace DubEngine
{
	class CameraComponent final :public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Camera);

		void Initialize() override;
		void Terminate() override;

		void Deserialize(rapidjson::Value& value) override;

		Graphics::Camera& GetCamera() { return mCamera; }
		const Graphics::Camera& GetCamera() const { return mCamera; }

	private:
		Graphics::Camera mCamera;
	};
}