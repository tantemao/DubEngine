#include"Precompiled.h"
#include"RigidBodyComponent.h"


#include"GameWorld.h"
#include"TransformComponent.h"
using namespace DubEngine;

void RigidBodyComponent::Initialize()
{	 
	TransformComponent* transform = GetOwner().GetComponent<TransformComponent>();
	//mRigidBody.Initialize(*transform,nullptr,mMass);
}	 
	 
void RigidBodyComponent::Terminate()
{	 
	mRigidBody.Terminate();
}	 
	 
void RigidBodyComponent::Deserialize(rapidjson::Value& value)
{	
	if (value.HasMember("Mass"))
	{
		mMass = value["Mass"].GetFloat();
	}
}	 
	 
void RigidBodyComponent::SetPosition(const DubEngine::DEMath::Vector3& position)
{
	mRigidBody.SetPosition(position);
}
