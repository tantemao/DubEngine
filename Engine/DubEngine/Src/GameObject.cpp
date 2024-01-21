#include"Precompiled.h"
#include"GameObject.h"
#include"TransformComponent.h"
using namespace DubEngine;
static uint32_t gUniqueId = 0;

void GameObject::Initialize()
{
	ASSERT(!mInitialized, "GameObject: is already initialized");
	for (auto& component : mComponents)
	{
		component->Initialize();
	}
	
	mUniqueId = ++gUniqueId;
	mInitialized = true;

	ASSERT(HasA<TransformComponent>(), "GameObject: must have a transform");
}
void GameObject::Terminate()
{
	for (auto& component : mComponents)
	{
		component->Terminate();
	}
}

void GameObject::Update(float deltaTime)
{

}
void GameObject::DebugUI()
{
	for (auto& component : mComponents)
	{
		component->DebugUI();
	}
}