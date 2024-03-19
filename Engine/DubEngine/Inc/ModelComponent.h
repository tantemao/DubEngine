#pragma once

#include "Component.h"

namespace DubEngine
{
	class ModelComponent final :public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Model);

		void Initialize() override;
		void Terminate() override;

		void Deserialize(rapidjson::Value& value) override;

		Graphics::ModelId GetModelId() const { return mModelId; }
		const Graphics::Model& GetModel() const
		{
			return *Graphics::ModelManager::Get()->GetModel(mModelId);
		}

	private:
		std::string mFileName;
		Graphics::ModelId mModelId;
	};

}