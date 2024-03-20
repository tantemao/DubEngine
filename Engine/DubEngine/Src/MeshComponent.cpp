#include"Precompiled.h"
#include"MeshComponent.h"

#include"GameWorld.h"
#include"RenderService.h"

using namespace DubEngine;
using namespace DubEngine::Graphics;

void MeshComponent::Initialize()
{
	RenderService* rs = GetOwner().GetWorld().GetService<RenderService>();
	rs->Register(this);
}

void MeshComponent::Terminate()
{
	RenderService* rs = GetOwner().GetWorld().GetService<RenderService>();
	rs->Unregister(this);
}

void MeshComponent::Deserialize(rapidjson::Value& value)
{
	Model::MeshData& meshData = mModel.meshData.emplace_back();
	if (value.HasMember("Shape"))
	{
		const auto& shapeData = value["Shape"].GetObj();
		if (shapeData.HasMember("Type"))
		{

			const std::string shapeType = shapeData["Type"].GetString();
			if(shapeType == "Cube")
			{
				const float size = shapeData["Size"].GetFloat();
				meshData.mesh = MeshBuilder::CreateCubePX(size);
			}
			else if (shapeType == "Sphere")
			{

			}
			else if (shapeType == "Plane")
			{

			}
			else
			{
				ASSERT(false, "ShapeType %s is invalid", shapeType.c_str());
			}
		}
	}
}
