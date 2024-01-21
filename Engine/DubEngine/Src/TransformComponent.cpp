#include"Precompiled.h"
#include"TransformComponent.h"

using namespace DubEngine;

void TransformComponent::DebugUI()
{
	Graphics::SimpleDraw::AddTransform(GetMatrix4());
}

void TransformComponent::Deserialize(rapidjson::Value& value)
{
	if (value.HasMember("Position"))
	{
		const auto& pos = value["Position"].GetArray();
		position.x = pos[0].GetFloat();
		position.x = pos[1].GetFloat();
		position.x = pos[2].GetFloat();
	}
	if (value.HasMember("Rotation"))
	{
		const auto& rot = value["Rotation"].GetArray();
		position.x = rot[0].GetFloat();
		position.x = rot[1].GetFloat();
		position.x = rot[2].GetFloat();
		position.x = rot[3].GetFloat();
	}
	if (value.HasMember("Scale"))
	{
		const auto& s = value["Scale"].GetArray();
		position.x = s[0].GetFloat();
		position.x = s[1].GetFloat();
		position.x = s[2].GetFloat();
	}
}