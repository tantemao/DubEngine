#include <DubEngine/Inc/DubEngine.h>

enum class States : size_t
{
    GameState = 0
};
class GameState : public DubEngine::AppState
{
public:
    virtual ~GameState() = default;

};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    DubEngine::App& mainApp = DubEngine::MainApp();
    
    mainApp.AddState<GameState>((size_t)States::GameState);
    mainApp.Run();

    return(0);
}