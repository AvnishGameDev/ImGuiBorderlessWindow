// Copyright (C) 2023 Avnish Kirnalli.

#include <iostream>
#include <thread>

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif

#include "Gui.h"
#include "../MainApp.h"

#ifdef PLATFORM_WINDOWS
int __stdcall wWinMain(
    HINSTANCE instance,
    HINSTANCE previousInstance,
    PWSTR arguments,
    int commandShow)
#else
int main(int argc, char** argv)
#endif
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
    return 0;
}