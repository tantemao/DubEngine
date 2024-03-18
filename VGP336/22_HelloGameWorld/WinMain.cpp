#include <DubEngine/Inc/DubEngine.h>
#include "GameState.h"

using namespace DubEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AppConfig config;
    config.appName = L"Hello GameWorld";

    App& myApp = MainApp();
    myApp.AddState<GameState>(0);
    myApp.Run(config);
    return(0);
}