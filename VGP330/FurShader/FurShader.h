#pragma once

#include <DubEngine/Inc/DubEngine.h>

using namespace DubEngine;
using namespace DubEngine::Graphics;

class FurShaderEffect
{
public:
	void Initialize();
	void Terminate();

	void Render(const Camera& camera);

	void SetDirectionalLight(const DirectionalLight& directionalLight);
	void UpdateFurTexture(float density, float maxLength, int maxLayers);

	void Update(float deltaTime);

	void DebugUI();

private:

	struct TransformData
	{
		Matrix4 world;
		Matrix4 vp;
		Vector3 viewPosition;
		Vector3 forces;
		float currentLayer;
		float maxLength;
	};
	struct FurData
	{
		float width;
		float height;
		float furLength[64];
		float padding[2] = { 0.0f };
	};

	using TransformBuffer = TypedConstantBuffer<TransformData>;
	using LightBuffer = TypedConstantBuffer<DirectionalLight>;
	using FurBuffer = TypedConstantBuffer<FurData>;

	TransformBuffer mTransformBuffer;
	LightBuffer mLightBuffer;
	FurBuffer mFurBuffer;
	VertexShader mVertexShader;
	PixelShader mPixelShader;
	BlendState mBlendState;

	TextureId mDiffuseTexture;
	TextureId mFurTexture;

	RenderObject mFurRenderObject;

	const DirectionalLight* mDirectionalLight = nullptr;

	DEMath::Vector3 mGravity = DEMath::Vector3::Zero;
	DEMath::Vector3 mForces = DEMath::Vector3::Zero;
	float mBlend = 0.0f;
	float mMaxLength = 0.0f;
	float mDensity = 0.0f;
	int mMaxLayers = 0;

	FurData mFurData;
};