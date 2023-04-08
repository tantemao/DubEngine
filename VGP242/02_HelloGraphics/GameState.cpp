#include "GameState.h"
#include "Input/Inc/InputSystem.h"

void GameState::Initialize()
{
    DubEngine::Graphics::GraphicsSystem::Get()->SetClearColor(DubEngine::Colors::Black);
}

void GameState::Update(float deltaTime)
{    
    auto inputSystem = Input::InputSystem::Get();
    if (inputSystem->IsKeyPressed(Input::KeyCode::ONE))
    {
        DubEngine::Graphics::GraphicsSystem::Get()->SetClearColor(DubEngine::Colors::Red);
    }
    else if (inputSystem->IsKeyPressed(Input::KeyCode::TWO))
    {
        DubEngine::Graphics::GraphicsSystem::Get()->SetClearColor(DubEngine::Colors::Green);
    }
}