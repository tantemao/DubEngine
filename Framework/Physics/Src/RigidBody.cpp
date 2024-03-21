#include "Precompiled.h"
#include "RigidBody.h"
#include"CollisionShape.h"
#include"PhysicsWorld.h"

#include"Graphics/Inc/Transform.h"

using namespace DubEngine;
using namespace DubEngine::Physics;


RigidBody::~RigidBody()
{
	ASSERT(mRigidBody == nullptr && mMotionState == nullptr, "RigidBody:terminate must be called first");
}

void RigidBody::Initialize(Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass)
{
	mGraphicsTransform = &graphicsTransform;
	mMass = mass;
	mMotionState = new btDefaultMotionState(ConvertTobtTransform(graphicsTransform));

	mRigidBody = new btRigidBody(mMass, mMotionState, shape.GetCollisionShape());

	//make it bounce
	mRigidBody->setRestitution(0.8f); // Adjust this value as per your requirements
		
	

	PhysicsWorld::Get()->Register(this);
}


void RigidBody::Terminate()
{
	PhysicsWorld::Get()->Unregister(this);
	SafeDelete(mMotionState);
	SafeDelete(mRigidBody);
}

void RigidBody::SetPosition(const DubEngine::DEMath::Vector3& position)
{
	mGraphicsTransform->position = position;
	mRigidBody->setWorldTransform(ConvertTobtTransform(*mGraphicsTransform));
}

bool RigidBody::IsDynamic() const
{
	return mMass > 0.0f;
}
void RigidBody::UpdateTransform()
{
	ApplybtTransformToTransform(mRigidBody->getWorldTransform(), *mGraphicsTransform);
}

btRigidBody* RigidBody::GetRigidBody() const {
	return mRigidBody;
}

