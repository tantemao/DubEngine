#include "Precompiled.h"
#include"ColliderComponent.h"

#include"GameWorld.h"

using namespace DubEngine;

void DubEngine::ColliderComponent::Initialize()
{
//
}

void DubEngine::ColliderComponent::Terminate()
{
	mCollisionShape->Terminate();
	delete mCollisionShape;
}

void DubEngine::ColliderComponent::Deserialize(rapidjson::Value& value)
{
	if (value.HasMember("Shape"))
	{
		const auto& shapeData = value["Shape"].GetObj();
		if (shapeData.HasMember("Type"))
		{
			const std::string shapeType = shapeData["Type"].GetString();
			if (shapeType == "Empty")
			{
				Physics::CollisionShapeEmpty* empty = new Physics::CollisionShapeEmpty();
				empty->Initialize();
				mCollisionShape = empty;
			}
			else if (shapeType == "Box")
			{
				const auto&he
			}
		}
		else
		{
			ASSERT(false, "ColliderComponent: must have a shape type");
		}
	}
	else
	{
		ASSERT(false, "ColliderComponent: must have a shape data");
	}
}
