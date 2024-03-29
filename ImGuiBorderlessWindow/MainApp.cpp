// Copyright (C) 2023 Avnish Kirnalli.

#include "MainApp.h"

#include "Gui/Font.h"
#include "Gui/Gui.h"

#include "Gui/GuiHelper.h"
#include "Gui/Themes.h"

MainApp::MainApp() : App("ImGuiBorderlessWindow by AvnishGameDev") // <-- Put your App Name here.
{
    // Check All the available themes in Themes.h and apply any as shown below.
    Theme::Comfy();

    // Loading Font
    Gui::PushFont(Font("Gui/ThirdParty/imGui/misc/fonts/DroidSans.ttf", 18.0f));
}

void MainApp::Render()
{
    // Add all the UI Components here.
    // Use ImGui namespace for default ImGui UI components.
    // Use GH namespace for advanced UI components.
    
    if (GH::ButtonCentered("Info"))
    {
        ShellExecute(0, 0, L"https://github.com/AvnishGameDev/ImGuiBorderlessWindow", 0, 0, SW_SHOW); // Open Website
    }
}
