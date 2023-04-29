#include <DubEngine/Inc/DubEngine.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    DubEngine::App& mainApp = DubEngine::MainApp();

    mainApp.AddState<GameState>((size_t)States::GameState);

    DubEngine::AppConfig config;
    config.appName = L"Hello Skeletonn";
    config.winWidth = 1280;
    config.winHeight = 720;
    mainApp.Run(config);

    return(0);
}