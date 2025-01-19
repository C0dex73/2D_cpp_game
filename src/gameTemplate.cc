#include "gameTemplate.hh"
#include "displayManager.hh"

namespace cdxg
{
    GameTemplate::GameTemplate(int initialWidth, int initialHeight, std::string initialTitle):
    mInitialWidth(initialWidth),
    mInitialHeight(initialHeight),
    mInitialTitle(initialTitle)
    {}

    void GameTemplate::Run(){
        
        DisplayManager::CreateWindow(mInitialWidth, mInitialHeight, mInitialTitle);
        Initialize();

        while(!glfwWindowShouldClose(DisplayManager::mpsWindow)){

            Update();

            Render();

            glfwPollEvents();
        }
        
        DisplayManager::CloseWindow();
    } // void Run()
} // namespace cdxg
