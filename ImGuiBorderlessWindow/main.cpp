#include <iostream>
#include <chrono>
#include <string>
#include <thread>

#include <Windows.h>
#include <shellapi.h>

#include "App.h"
#include "imgui.h"

#include "Gui.h"
#include "Themes.h"

int __stdcall wWinMain(
    HINSTANCE instance,
    HINSTANCE previousInstance,
    PWSTR arguments,
    int commandShow)
{
    // Create gui
    Gui::CreateHWindow("ImGuiBorderlessWindow by AvnishGameDev", 400, 140);
    Gui::CreateDevice();
    Gui::CreateImGui();

    // Activating Theme
    Themes::DefaultDark();

    auto app = App::Create();
    
    // Main Loop
    while (Gui::isRunning)
    {
        app->Update();
        
        Gui::BeginRender();
        Gui::BeginImGuiRender();

        // Render ImGui elements
        app->Render();

        Gui::EndImGuiRender();
        Gui::EndRender();

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    // Destroy gui
    Gui::DestroyImGui();
    Gui::DestroyDevice();
    Gui::DestroyHWindow();

    return EXIT_SUCCESS;
}