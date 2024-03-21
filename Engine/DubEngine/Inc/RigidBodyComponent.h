#pragma once

#include"Component.h"

namespace DubEngine
{
	class RigidBodyComponent final :public Component
	{
	public:
		SET_TYPE_ID(ComponentId::RigidBody);

		void Initialize() override;
		void Terminate() override;
		void Deserialize(rapidjson::Value& value) override;

		void SetPosition(const DubEngine::DEMath::Vector3& position);

	private:
		Physics::RigidBody mRigidBody;
		float mMass = 1.0f;
	};
}