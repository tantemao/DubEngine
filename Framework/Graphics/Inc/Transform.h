#pragma once

#include "Common.h"

namespace DubEngine::Graphics
{
    struct Transform
    {
        DEMath::Vector3 position = DEMath::Vector3::Zero;
        DEMath::Quaternion rotation = DEMath::Quaternion::Identity;
        DEMath::Vector3 scale = DEMath::Vector3::One;

        Transform() = default;
        Transform (const DEMath::Matrix4& m)
        {
            position = DEMath::GetTranslation(m);
            rotation = DEMath::Quaternion::CreateFromRotationMatrix(m);
            scale = DEMath::GetScale(m);
        }
        DEMath::Matrix4 GetMatrix4() const
        {
            return {
                DEMath::Matrix4::Scaling(scale) *
                DEMath::Matrix4::MatrixRotationQuaternion(rotation) *
                DEMath::Matrix4::Translation(position)
            };
        }
    };
}