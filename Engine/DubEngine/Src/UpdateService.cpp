#include"Precompiled.h"
#include"UpdateService.h"
#include"Component.h"
using namespace DubEngine;
void DubEngine::UpdateService::Update(float deltaTime)
{
	mIsUpdating = true;
	for (auto& component : mUpdateComponents)
	{
		component->Update(deltaTime);
	}
	mIsUpdating = false;

	RegisterPendingUpdates();
}
void UpdateService::Register(Component* component)
{
	if (mIsUpdating)
	{
		mPendingUpdateComponents.push_back(component);
	}
	else
	{
		mUpdateComponents.push_back(component);
	}
	mUpdateComponents.push_back(component);
}

void UpdateService::UnRegister(Component* component)
{
	auto iter = std::find(mUpdateComponents.begin(), mUpdateComponents.end(), component);
	if (iter != mUpdateComponents.end())
	{
		mUpdateComponents.erase(iter);
	}
	iter = std::find(mPendingUpdateComponents.begin(), mPendingUpdateComponents.end(), component);
	if (iter != mPendingUpdateComponents.end())
	{
		mPendingUpdateComponents.erase(iter);
	}
}

void UpdateService::RegisterPendingUpdates()
{
	for (Component* component : mPendingUpdateComponents)
	{
		mUpdateComponents.push_back(component);
	}
	mPendingUpdateComponents.clear();
}
