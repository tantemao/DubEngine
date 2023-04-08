#include <DubEngine/Inc/DubEngine.h>
#include "GameState.h"

using namespace DubEngine;
using namespace DubEngine::Graphics;

enum class States : size_t
{
    GameState = 0
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AppConfig config;
    config.appName = L"Hello Simple Draw";
    config.winWidth = 1280;
    config.winHeight = 720;

    App& mainApp = DubEngine::MainApp();    
    mainApp.AddState<GameState>((size_t)States::GameState);
    mainApp.Run(config);

    return(0);
}