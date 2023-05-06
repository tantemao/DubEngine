#pragma once

#include "ConstantBuffer.h"
#include "LightType.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "Material.h"

namespace DubEngine::Graphics
{
    class Camera;
    class RenderObject;
    class Texture;

    class StandardEffect
    {
    public:
        void Initialize(const std::filesystem::path& filePath);
        void Terminate();

        void Begin();
        void End();

        void Render(const RenderObject& renderObject);

        void SetCamera(const Camera& camera);
        void SetDirectionalLight(const DirectionalLight& directionalLight);
        void SetLightCamera(const Camera& camera);
        void SetShadowMap(const Texture* shadowMap);

        void DebugUI();

    private:
        struct TransformData
        {
            DEMath::Matrix4 world;
            DEMath::Matrix4 wvp[2];
            DEMath::Vector3 viewPosition;
            float displacementWeight;
        };

  /*      struct BoneTransformData
        {
            static constexpr size_t  MaxBoneCount = 256;
            DEMath::Matrix4 boneTransforms[MaxBoneCount];
        };*/
        struct SettingsData
        {
            int useDiffuseMap = 1;
            int useSpecularMap = 1;
            int useDisplacementMap = 1;
            int useNormalMap = 1;
            int useShadowMap = 1;
            int useSkinning = 1;
            float depthBias = 0.0f;
            float padding[1] = { 0.0f };
        };

        using TransformBuffer = TypedConstantBuffer<TransformData>;
        using BoneTransformBuffer = ConstantBuffer;
        using LightBuffer = TypedConstantBuffer<DirectionalLight>;
        using MaterialBuffer = TypedConstantBuffer<Material>;
        using SettingsBuffer = TypedConstantBuffer<SettingsData>;

        TransformBuffer mTransformBuffer;
        BoneTransformBuffer mBoneTransformBuffer;
        LightBuffer mLightBuffer;
        MaterialBuffer mMaterialBuffer;
        SettingsBuffer mSettingsBuffer;
        Sampler mSampler;

        VertexShader mVertexShader;
        PixelShader mPixelShader;

       /* BoneTransformData mBoneTransformData;*/
        SettingsData mSettingsData;

        float mDisplacementWeight = 0.0f;
        float mDepthBias = 0.0f;

        const Camera* mCamera = nullptr;
        const Camera* mLightCamera = nullptr;
        const DirectionalLight* mDirectionalLight = nullptr;
        const Texture* mShadowMap = nullptr;
    };
}