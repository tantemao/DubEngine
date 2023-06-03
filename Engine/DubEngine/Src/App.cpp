#include "Precompiled.h"
#include "App.h"

#include "AppState.h"

using namespace DubEngine;
using namespace DubEngine::Core;
using namespace DubEngine::Graphics;
using namespace DubEngine::Input;
using namespace DubEngine::Physics;

void App::ChangeState(size_t stateId)
{
    auto iter = mAppStates.find(stateId);
    if (iter != mAppStates.end())
    {
        mNextState = iter->second.get();
    }
}

void App::Run()
{
    ASSERT(false, "[Depreciated] use Run(const AppConfig& config)");
    AppConfig config;
    Run(config);
}

void App::Run(const AppConfig& config)
{
    Window myWindow;
    myWindow.Initialize(
        GetModuleHandle(nullptr), 
        config.appName,
        config.winWidth, 
        config.winHeight);

    auto handle = myWindow.GetWindowHandle();
    InputSystem::StaticInitialize(handle);
    GraphicsSystem::StaticInitialize(handle, false);
    DebugUI::StaticInitialize(handle, false, true);
    SimpleDraw::StaticInitialize(config.debugDrawLimit);
    TextureManager::StaticInitialize("../../Assets/");
    ModelManager::StaticInitialize();
    PhysicsWorld::Settings settings = {
        config.gravity,
        config.simulationSteps,
        config.fixedTimeStep
    };
    PhysicsWorld::StaticIntialize(settings);
    ASSERT(mCurrentState, "App -- no app state found!");
    mCurrentState->Initialize();

    size_t currentState = 0;
    mRunning = true;
    while (mRunning)
    {
        myWindow.ProcessMessage();

        auto inputSystem = InputSystem::Get();
        inputSystem->Update();

        if (!myWindow.IsActive() || inputSystem->IsKeyPressed(Input::KeyCode::ESCAPE))
        {
            Quit();
            continue;
        }
        if (inputSystem->IsKeyPressed(Input::KeyCode::ENTER))
        {
            currentState = (currentState + 1) % (size_t)mAppStates.size();
            ChangeState(currentState);
        }

        if (mNextState != nullptr)
        {
            mCurrentState->Terminate();
            mCurrentState = std::exchange(mNextState, nullptr);
            mCurrentState->Initialize();
        }

        auto deltaTime = TimeUtil::GetDeltaTime();
        if (deltaTime < 0.5f)
        {
            PhysicsWorld::Get()->Update(deltaTime);
            mCurrentState->Update(deltaTime);
        }

        auto graphicsSystem = GraphicsSystem::Get();
        graphicsSystem->BeginRender();
            mCurrentState->Render();

            DebugUI::BeginRender();
                mCurrentState->DebugUI();
            DebugUI::EndRender();

        graphicsSystem->EndRender();
    }

    mCurrentState->Terminate();

    PhysicsWorld::StaticTerminate();
    ModelManager::StaticTerminate();
    TextureManager::StaticTerminate();
    SimpleDraw::StaticTerminate();
    DebugUI::StaticTerminate();
    GraphicsSystem::StaticTerminate();
    InputSystem::StaticTerminate();
    ModelManager::StaticTerminate();
    myWindow.Terminate();
}

void App::Quit()
{
    mRunning = false;
}