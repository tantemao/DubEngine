#pragma once
#include <DubEngine/Inc/DubEngine.h>

using namespace DubEngine;
using namespace DubEngine::Graphics;

class GameState : public DubEngine::AppState
{
public:
    virtual ~GameState() = default;

    virtual void Initialize() override;
    virtual void Terminate() override;
    
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void DebugUI() override;
protected:
    Camera mCamera;
    ConstantBuffer mConstantBuffer;

    MeshPC mCube;
    MeshBuffer mMeshBuffer;
    VertexShader mVertexShader;
    PixelShader mPixelShader;
};