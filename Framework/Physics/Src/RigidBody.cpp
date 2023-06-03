#include "Precompiled.h"
#include "RigidBody.h"
#include"PhysicsWorld.h"

#include"Graphics/Inc/Transform.h"
using namespace DubEngine;
using namespace DubEngine::Physics;
RigidBody::~RigidBody()
{
	ASSERT(mRigidBody == nullptr && mMotionState == nullptr, "RigidBody:terminate must be called first");
}
void RigidBody::Initialize(Graphics::Transform& graphicsTransform, float mass) 
{
	mGraphicsTransform = &graphicsTransform;
	mMass = mass;
	mMotionState = new btDefaultMotionState(ConvertTobtTransform(graphicsTransform));
	
	mRigidBody = new btRigidBody(mMass, mMotionState, nullptr);
	PhysicsWorld::Get()->Register(this);
}
void RigidBody::Terminate()
{
	PhysicsWorld::Get()->Unregister(this);
	SafeDelete(mMotionState);
	SafeDelete(mRigidBody);
}

bool RigidBody::IsDynamic() const
{
	return mMass > 0.0f;
}
void RigidBody::UpdateTransform()
{
	ApplybtTransformToTransform(mRigidBody->getWorldTransform(), *mGraphicsTransform);
}