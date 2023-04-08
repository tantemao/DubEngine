#pragma once

#include "MeshTypes.h"
#include "Material.h"

namespace DubEngine::Graphics
{
    struct Model
    {
        struct MeshData
        {
            Mesh mesh;
            uint32_t materialIndex = 0;
        };

        struct MaterialData
        {
            Material material;
            std::string diffuseMapName;
            std::string specularMapName;
            std::string displacementMapName;
            std::string normalMapName;
        };

        std::vector<MeshData> meshData;
        std::vector<MaterialData> materialData;
    };
}