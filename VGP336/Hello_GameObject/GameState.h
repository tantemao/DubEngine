#pragma once
#include <DubEngine/Inc/DubEngine.h>


class GameState : public DubEngine::AppState
{
public:


    void Initialize() override;
    void Terminate() override; 
    void Update(float deltaTime);
    void Render();
    void DebugUI();
protected:
    DubEngine::Graphics::Camera mCamera;
    DubEngine::GameObject mGameObject;
};