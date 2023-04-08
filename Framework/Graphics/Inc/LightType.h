#pragma once


#include "Colors.h"

namespace DubEngine::Graphics
{
    struct DirectionalLight
    {
        DEMath::Vector3 direction = DEMath::Vector3::Zero;
        float padding = 0.0f;
        Color ambient = Colors::White;
        Color diffuse = Colors::White;
        Color specular = Colors::White;
    };
}