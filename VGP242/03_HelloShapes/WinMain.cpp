#include <DubEngine/Inc/DubEngine.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0,
    Triangle,
    Square,
    Diamond
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    DubEngine::App& mainApp = DubEngine::MainApp();
    
    mainApp.AddState<GameState>((size_t)States::GameState);
    mainApp.AddState<Triangle>((size_t)States::Triangle);
    mainApp.Run();

    return(0);
}