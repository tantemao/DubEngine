#pragma once
#include "Graphics/Inc/Transform.h"

namespace DubEngine::Graphics
{
	struct Transform;
}
namespace DubEngine::Physics
{
	class CollisionShape;

	class RigidBody final
	{
	public:
		RigidBody() = default;
		~RigidBody();
		void Initialize( Graphics::Transform& graphicsTransform ,const CollisionShape& shape,float mass = 0.0f);
		void Terminate();
		//void SetPosition(const DubEngine::DEMath::Vector3)
		bool IsDynamic() const;
		void UpdateTransform();
	private:
		friend class PhysicsWorld;
		btRigidBody* GetRigidBody() { return mRigidBody; }
		btRigidBody* mRigidBody = nullptr;
		btDefaultMotionState* mMotionState = nullptr;
		float mMass = 0.0f;
		bool mIsDynamic;
		Graphics::Transform* mGraphicsTransform = nullptr;
			
	};
}