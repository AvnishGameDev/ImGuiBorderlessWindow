#include <iostream>
#include <thread>
#include <Windows.h>

#include "Gui.h"
#include "MainApp/MainApp.h"

int __stdcall wWinMain(
    HINSTANCE instance,
    HINSTANCE previousInstance,
    PWSTR arguments,
    int commandShow)
{
    auto app = App::Create<MainApp>();
    
    // Main Loop
    while (Gui::isRunning)
    {
        app->Update();
        
        /* Rendering */
        app->BeginRender();
        app->Render();
        app->EndRender();
    }

    delete app;
    return EXIT_SUCCESS;
}