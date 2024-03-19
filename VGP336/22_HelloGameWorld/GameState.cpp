#include "GameState.h"
using namespace DubEngine;
using namespace DubEngine::Graphics;
using namespace DubEngine::Input;

void GameState::Initialize()
{

	mGameWorld.LoadLevel("../../Assets/Templates/Levels/test_level.json");

}
void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Render()
{
	mGameWorld.Render();
}
void GameState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
}


void GameState::DebugUI()
{
	mGameWorld.DebugUI();

}
