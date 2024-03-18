#pragma once
#include <DubEngine/Inc/DubEngine.h>


class GameState : public DubEngine::AppState
{
public:


    void Initialize() override;
    void Terminate() override; 
    void Render();
    void Update(float deltaTime);

    void DebugUI();
protected:

    DubEngine::GameObject mGameObject;
    DubEngine::GameObject mCameraGameObject1;
    DubEngine::GameObject mCameraGameObject2;
    DubEngine::CameraService mCameraService;

};