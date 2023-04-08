#include "Precompiled.h"
#include "DubEngine.h"


DubEngine::App& DubEngine::MainApp()
{
    static App sApp;
    return sApp;
}