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

    DubEngine::GameObject mGameObject;
    DubEngine::GameObject mCameraObject1;
    DubEngine::GameObject mCameraObject2;
    DubEngine::CameraService mCameraService;

};