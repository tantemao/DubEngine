#include "Precompiled.h"
#include "ModelIO.h"
#include "Model.h"
#include "Material.h"

using namespace DubEngine;
using namespace DubEngine::Graphics;


void AnimationIO:: Write(FILE* file, const Animation& animation) 
{
    uint32_t count = animation.mPositionKeys.size();
    fprintf_s(file, "PositionKeysCount:%d\n", count);
    for (auto& k : animation.mPositionKeys)
    {
        fprintf_s(file, "%f %f %f %f\n", k.time, k.key.x, k.key.y, k.key.z);
    }

    count = animation.mRotationKeys.size();
    fprintf_s(file, "RoatationKeysCount:%d\n", count);
    for (auto& k : animation.mRotationKeys)
    {
        fprintf_s(file, "%f %f %f %f %f\n", k.time, k.key.x, k.key.y, k.key.z,k.key.w);
    }
    count = animation.mScaleKeys.size();
    fprintf_s(file, "ScleKeysCount:%d\n", count);
    for (auto& k : animation.mPositionKeys)
    {
        fprintf_s(file, "%f %f %f %f\n", k.time, k.key.x, k.key.y, k.key.z);
    }
}
void AnimationIO::Read(FILE* file, Animation& animation)
{

}

void ModelIO::SaveModel(std::filesystem::path filePath, const Model& model)
{
    if (model.meshData.empty())
    {
        return;
    }

    FILE* file = nullptr;
    fopen_s(&file, filePath.u8string().c_str(), "w");
    if (file == nullptr)
    {
        return;
    }

    const uint32_t meshCount = static_cast<uint32_t>(model.meshData.size());
    fprintf_s(file, "MeshCount: %d\n", meshCount);
    for (uint32_t i = 0; i < meshCount; ++i)
    {
        const auto& meshData = model.meshData[i];
        fprintf_s(file, "MaterialIndex: %d\n", meshData.materialIndex);

        const auto& mesh = meshData.mesh;
        const uint32_t vertexCount = static_cast<uint32_t>(mesh.vertices.size());
        fprintf_s(file, "VertexCount: %d\n", vertexCount);

        for (auto& v : mesh.vertices)
        {
            fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d %d\n",
                v.position.x, v.position.y, v.position.z,
                v.normal.x, v.normal.y, v.normal.z,
                v.tangent.x, v.tangent.y, v.tangent.z,
                v.uvCoord.x, v.uvCoord.y,
                v.boneWeights[0],  v.boneWeights[1], v.boneWeights[2], v.boneWeights[3],
                v.boneIndieces[0], v.boneIndieces[1], v.boneIndieces[2], v.boneIndieces[3]);
        }

        const uint32_t indexCount = static_cast<uint32_t>(mesh.indices.size());
        fprintf_s(file, "IndexCount: %d\n", indexCount);
        for (size_t n = 2; n < indexCount; n += 3)
        {
            fprintf_s(file, "%d %d %d\n", mesh.indices[n - 2], mesh.indices[n - 1], mesh.indices[n]);
        }
    }

    fclose(file);
}
void ModelIO::LoadModel(std::filesystem::path filePath, Model& model)
{
    FILE* file = nullptr;
    fopen_s(&file, filePath.u8string().c_str(), "r");
    if (file == nullptr)
    {
        return;
    }

    uint32_t meshCount = 0;
    fscanf_s(file, "MeshCount: %d\n", &meshCount);

    model.meshData.resize(meshCount);
    for (uint32_t i = 0; i < meshCount; ++i)
    {
        auto& meshData = model.meshData[i];
        fscanf_s(file, "MaterialIndex: %d\n", &meshData.materialIndex);

        auto& mesh = meshData.mesh;
        uint32_t vertexCount = 0;
        fscanf_s(file, "VertexCount: %d\n", &vertexCount);
        mesh.vertices.resize(vertexCount);

        for (auto& v : mesh.vertices)
        {
            fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d %d\n",
                &v.position.x, &v.position.y, &v.position.z,
                &v.normal.x, &v.normal.y, &v.normal.z,
                &v.tangent.x, &v.tangent.y, &v.tangent.z,
                &v.uvCoord.x, &v.uvCoord.y,
                & v.boneWeights[0], & v.boneWeights[1], & v.boneWeights[2], & v.boneWeights[3],
                & v.boneIndieces[0], & v.boneIndieces[1], & v.boneIndieces[2], & v.boneIndieces[3]);
        }

        uint32_t indexCount = 0;
        fscanf_s(file, "IndexCount: %d\n", &indexCount);
        mesh.indices.resize(indexCount);
        for (size_t n = 2; n < indexCount; n += 3)
        {
            fscanf_s(file, "%d %d %d\n", &mesh.indices[n - 2], &mesh.indices[n - 1], &mesh.indices[n]);
        }
    }

    fclose(file);
}
void ModelIO::SaveMaterial(std::filesystem::path filePath, const Model& model)
{
    if (model.materialData.empty())
    {
        return;
    }
    filePath.replace_extension("material");

    FILE* file = nullptr;
    fopen_s(&file, filePath.u8string().c_str(), "w");
    if (file == nullptr)
    {
        return;
    }

    uint32_t materialCount = static_cast<uint32_t>(model.materialData.size());
    fprintf_s(file, "MaterialCount: %d\n", materialCount);
    for (auto& materialData : model.materialData)
    {
        auto& m = materialData.material;
        fprintf_s(file, "%f %f %f %f\n", m.ambient.r, m.ambient.g, m.ambient.b, m.ambient.a);
        fprintf_s(file, "%f %f %f %f\n", m.diffuse.r, m.diffuse.g, m.diffuse.b, m.diffuse.a);
        fprintf_s(file, "%f %f %f %f\n", m.specular.r, m.specular.g, m.specular.b, m.specular.a);
        fprintf_s(file, "%f %f %f %f\n", m.emissive.r, m.emissive.g, m.emissive.b, m.emissive.a);

        fprintf_s(file, "%s\n", materialData.diffuseMapName.empty() ? "none" : materialData.diffuseMapName.c_str());
        fprintf_s(file, "%s\n", materialData.specularMapName.empty() ? "none" : materialData.specularMapName.c_str());
        fprintf_s(file, "%s\n", materialData.displacementMapName.empty() ? "none" : materialData.displacementMapName.c_str());
        fprintf_s(file, "%s\n", materialData.normalMapName.empty() ? "none" : materialData.normalMapName.c_str());
    }

    fclose(file);
}
void ModelIO::LoadMaterial(std::filesystem::path filePath, Model& model)
{
    filePath.replace_extension("material");

    FILE* file = nullptr;
    fopen_s(&file, filePath.u8string().c_str(), "r");
    if (file == nullptr)
    {
        return;
    }

    auto TryReadTextureName = [&](auto& fileName)
    {
        char buffer[MAX_PATH]{};
        fscanf_s(file, "%s\n", buffer, (uint32_t)sizeof(buffer));
        if (strcmp(buffer, "none") != 0)
        {
            fileName = filePath.replace_filename(buffer).string();
        }
    };

    uint32_t materialCount = 0;
    fscanf_s(file, "MaterialCount: %d\n", &materialCount);
    model.materialData.resize(materialCount);
    for (auto& materialData : model.materialData)
    {
        auto& m = materialData.material;
        fscanf_s(file, "%f %f %f %f\n", &m.ambient.r, &m.ambient.g, &m.ambient.b, &m.ambient.a);
        fscanf_s(file, "%f %f %f %f\n", &m.diffuse.r, &m.diffuse.g, &m.diffuse.b, &m.diffuse.a);
        fscanf_s(file, "%f %f %f %f\n", &m.specular.r, &m.specular.g, &m.specular.b, &m.specular.a);
        fscanf_s(file, "%f %f %f %f\n", &m.emissive.r, &m.emissive.g, &m.emissive.b, &m.emissive.a);

        TryReadTextureName(materialData.diffuseMapName);
        TryReadTextureName(materialData.specularMapName);
        TryReadTextureName(materialData.displacementMapName);
        TryReadTextureName(materialData.normalMapName);
    }

    fclose(file);
}
void ModelIO::SaveSkeleton(std::filesystem::path filePath, const Model& model)
{
    if(model.skeleton==nullptr)
    {
        return;
    }
    filePath.replace_extension("skeleton");
    FILE* file = nullptr;
    fopen_s(&file, filePath.u8string().c_str(), "w");
    if (file == nullptr)
    {
        return;
    }
    auto WriteMatrix = [&](auto& m)
    {
        fprintf_s(file, "%f %f %f %f\n", m._11, m._12, m._13, m._14);
        fprintf_s(file, "%f %f %f %f\n", m._21, m._22, m._23, m._24);
        fprintf_s(file, "%f %f %f %f\n", m._31, m._32, m._33, m._34);
        fprintf_s(file, "%f %f %f %f\n", m._41, m._42, m._43, m._44);
    };

    uint32_t boneCount = model.skeleton->bones.size();
    fprintf_s(file, "RootBone: %d\n", model.skeleton->root->index);
    fprintf_s(file, "BoneCount: %d\n", boneCount);
    for (uint32_t i = 0; i < boneCount; ++i)
    {
        auto& boneData = model.skeleton->bones[i];
        fprintf_s(file, "BoneName: %s\n", boneData->name.c_str());
        fprintf_s(file, "BoneIndex: %d\n", boneData->index);
        fprintf_s(file, "BoneParentIndex: %d\n", boneData->parentIndex);

        uint32_t childCount = boneData->childrenIndicies.size();
        fprintf_s(file, "BoneChildrenCount: %d\n", childCount);
        for (uint32_t c = 0; c < childCount; ++c)
        {
            fprintf_s(file, "%d\n", boneData->childrenIndicies[c]);
        }

        WriteMatrix(boneData->toParentTransform);
        WriteMatrix(boneData->offsetTransform);
    }
    fclose(file);
}
void ModelIO::LoadSkeleton(std::filesystem::path filePath, Model& model)
{
    filePath.replace_extension("skeleton");
    FILE* file = nullptr;
    fopen_s(&file, filePath.u8string().c_str(), "r");
    if (file == nullptr)
    {
        return;
    }
    auto ReadMatrix = [&](auto& m)
    {
        fscanf_s(file, "%f %f %f %f\n", &m._11, &m._12, &m._13, &m._14);
        fscanf_s(file, "%f %f %f %f\n", &m._21, &m._22, &m._23, &m._24);
        fscanf_s(file, "%f %f %f %f\n", &m._31, &m._32, &m._33, &m._34);
        fscanf_s(file, "%f %f %f %f\n", &m._41, &m._42, &m._43, &m._44);
    };

    model.skeleton = std::make_unique < Skeleton>();

    int boneCount = 0;
    int rootIndex = 0;
    fscanf_s(file, "RootBone: %d\n", &rootIndex);
    fscanf_s(file, "BoneCount: %d\n", &boneCount);
    model.skeleton->bones.resize(boneCount);

    for (uint32_t i = 0; i < boneCount; ++i)
    {
        model.skeleton->bones[i] = std::make_unique<Bone>();
    }
    model.skeleton->root = model.skeleton->bones[rootIndex].get();

    for (uint32_t i = 0; i < boneCount; ++i)
    {
        uint32_t boneIndex = 0;
        char boneName[MAX_PATH]{};
        fscanf_s(file, "BoneName: %s\n", &boneName,(uint32_t)sizeof(boneName));
        fscanf_s(file, "BoneIndex: %d\n",&boneIndex);


        auto& boneData = model.skeleton->bones[boneIndex];
        boneData->name = std::move(boneName);
        boneData->index = boneIndex;

        fscanf_s(file, "BoneParentIndex: %d\n", &boneData->parentIndex);
        if(boneData->parentIndex >= 0)
        {
            boneData->parent = model.skeleton->bones[boneData->parentIndex].get();
        }
        uint32_t childCount = 0;
        fscanf_s(file, "BoneChildrenCount: %d\n", &childCount);
        if (childCount > 0)
        {
            boneData->children.resize(childCount);
            boneData->childrenIndicies.resize(childCount);
            for (uint32_t c = 0; c < childCount; ++c)
            {
                uint32_t childIndex = 0;
                fscanf_s(file, "%d\n", &childIndex);
                boneData->childrenIndicies[c] = childIndex;
                boneData->children[c] = model.skeleton->bones[childIndex].get();

            }
        }
       

        ReadMatrix(boneData->toParentTransform);
        ReadMatrix(boneData->offsetTransform);
    }
    fclose(file);
}

void ModelIO::SaveAnimations(std::filesystem::path filePath, const Model& model)
{
    if (model.skeleton == nullptr || model.animationClips.empty())
    {
        return;
    }
    filePath.replace_extension("animset");
    FILE* file = nullptr;
    fopen_s(&file, filePath.u8string().c_str(), "w");
    if (file == nullptr)
    {
        return;
    }
    uint32_t animClipCount = model.animationClips.size();
    fprintf_s(file, "AnimClipCount:%d\n", animClipCount);
    for (uint32_t i = 0; i < animClipCount; ++i)
    {
        auto& animClipData = model.animationClips[i];
        fprintf_s(file, "AnimationClipName: %s\n", animClipData.name.c_str());
        fprintf_s(file, "TickDuration:%f\n", animClipData.tickDuration);
        fprintf_s(file, "TicksPerSecond:%f\n", animClipData.ticksPerSecond);


        uint32_t boneAnimCount = animClipData.boneAnimations.size();
        fprintf_s(file, "BoneAnimCount: %d\n", boneAnimCount);
        for (uint32_t b = 0; b < boneAnimCount; ++b)
        {
            auto boneAnim = animClipData.boneAnimations[b].get();
            if (boneAnim == nullptr)
            {
                fprintf_s(file, "[EMPTY]\n");
                continue;
            }

            fprintf_s(file, "[ANIMATION]\n");
            AnimationIO::Write(file, *boneAnim);
            //uint32_t
        }
    }

    fclose(file);
}
void ModelIO::LoadAnimations(std::filesystem::path filePath, Model& model)
{

}