#pragma once
#include <DubEngine/Inc/DubEngine.h>

using namespace DubEngine;
using namespace DubEngine::Graphics;
using namespace DubEngine::Physics;

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
    DirectionalLight mDirectionalLight;

   
    RenderObject mBall;
    RigidBody mBallRigidBody;
    StandardEffect mStandardEffect;

    bool mDrawSkeleton;
};