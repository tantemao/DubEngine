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
    virtual void OnCreateShape();
    struct Vertex
    {
        DubEngine::DEMath::Vector3 position;
        DubEngine::Color color;
    };
    std::vector<Vertex> mVertices;

    Camera mCamera;
    ConstantBuffer mConstantBuffer;
    MeshBuffer mMeshBuffer;
    VertexShader mVertexShader;
    PixelShader mPixelShader;
};

class Triangle : public GameState
{
public:
    virtual ~Triangle() = default;

protected:
    void OnCreateShape() override;
};