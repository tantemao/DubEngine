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

    bool mIsLine = true;
    Vector3 mLinePos1 = Vector3::Zero;
    Vector3 mLinePos2 = Vector3::One;
    Color mLineColor = Colors::Cyan;

    int mSlices = 10;
    int mRings = 10;
    float mCircleRadius = 1.0f;
    Color mCircleColor = Colors::Cyan;
};