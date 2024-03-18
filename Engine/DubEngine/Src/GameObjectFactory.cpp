#include"Precompiled.h"
#include"GameObjectFactory.h"
#include"GameObject.h"
#include"CameraComponent.h"
#include"TransformComponent.h"
#include"FPSCameraComponent.h"

using namespace DubEngine;
namespace rj = rapidjson;
void GameObjectFactory::Make(const std::filesystem::path& templatePath, GameObject& gameObject)
{
	FILE* file = nullptr;
	auto err = fopen_s(&file, templatePath.u8string().c_str(), "r");
	ASSERT(err == 0, "GameObjectFactory:failed to open file %s", templatePath.u8string().c_str());

	char readBuffer[65536];
	rj::FileReadStream readStream(file, readBuffer,sizeof(readBuffer));
	fclose(file);

	rj::Document doc;
	doc.ParseStream(readStream);
	auto components = doc["Components"].GetObj();
	for (auto& component : components)
	{
		const char* componentName = component.name.GetString();
		if (strcmp(componentName,"TransformComponent")==0)
		{
			TransformComponent* transformComponent = gameObject.AddComponent<TransformComponent>();
			transformComponent->Deserialize(component.value);
		}
		else if (strcmp(componentName, "CameraComponent") == 0)
		{
			FPSCameraComponent* fpscameraComponent = gameObject.AddComponent<FPSCameraComponent>();
			fpscameraComponent->Deserialize(component.value);
		}
		else if (strcmp(componentName, "FPSCameraComponent") == 0)
		{
			CameraComponent* cameraComponent = gameObject.AddComponent<CameraComponent>();
			cameraComponent->Deserialize(component.value);
		}
		else
		{
			ASSERT(false, "GameObjectFactory:%s was not defind", componentName);
		}
	}
}