#pragma once

// Engine engine
#include <Core/Inc/Core.h>
#include <Math/Inc/DEMath.h>

// DirectX Headers
#include <d3d11_1.h>
#include <d3dcompiler.h>

// External libs
#include <ImGui/Inc/imgui.h>

// DirectX libraries
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

template <class T>
inline void SafeRelease(T*& ptr)
{
    if (ptr)
    {
        ptr->Release();
        ptr = nullptr;
    }
}