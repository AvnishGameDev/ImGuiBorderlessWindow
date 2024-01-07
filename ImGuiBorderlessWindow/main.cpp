// Copyright (C) 2023 Avnish Kirnalli.

#include <iostream>
#include <thread>
#include <Windows.h>

#include "Gui/Gui.h"
#include "MainApp.h"

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