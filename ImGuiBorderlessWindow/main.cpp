#include <iostream>
#include <chrono>
#include <string>
#include <thread>

#include "gui.h"
#include "imgui.h"

#include <Windows.h>
#include <shellapi.h>

int __stdcall wWinMain(
    HINSTANCE instance,
    HINSTANCE previousInstance,
    PWSTR arguments,
    int commandShow)
{
    // Create gui
    gui::CreateHWindow("ImGuiBorderlessWindow by AvnishGameDev");
    gui::CreateDevice();
    gui::CreateImGui();

    while (gui::isRunning)
    {
        gui::BeginRender();
        gui::BeginImGuiRender();

        // Render ImGui elements
        if (ImGui::Button("Visit my site"))
        {
            ShellExecute(0, 0, L"https://avnishgamedev.com", 0, 0, SW_SHOW);
        }

        gui::EndImGuiRender();
        gui::EndRender();

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    // Destroy gui
    gui::DestroyImGui();
    gui::DestroyDevice();
    gui::DestroyHWindow();

    return EXIT_SUCCESS;
}