#include <iostream>
#include <chrono>
#include <string>
#include <thread>

#include <Windows.h>
#include <shellapi.h>

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
    Gui::CreateHWindow("ImGuiBorderlessWindow by AvnishGameDev");
    Gui::CreateDevice();
    Gui::CreateImGui();

    // Activating Theme
    Themes::DefaultDark();

    // Main Loop
    while (Gui::isRunning)
    {
        Gui::BeginRender();
        Gui::BeginImGuiRender();

        // Render ImGui elements
        if (ImGui::Button("Visit my site"))
        {
            ShellExecute(0, 0, L"https://avnishgamedev.com", 0, 0, SW_SHOW);
        }

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