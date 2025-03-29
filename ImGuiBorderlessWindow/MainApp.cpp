// Copyright (C) 2023 Avnish Kirnalli.

#include "MainApp.h"

#include "Gui/Font.h"
#include "Gui/Gui.h"

#include "Gui/GuiHelper.h"
#include "Gui/Themes.h"

#include "Gui/Platform/Platform.h"

MainApp::MainApp() : App("ImGuiBorderlessWindow by AvnishGameDev", 400, 140) // <-- Put your App Name here.
{
    // Check All the available themes in Themes.h and apply any as shown below.
    Theme::Comfy();

    // Loading Font from Assets folder
    Gui::PushFont(GuiFont(Platform::Get()->GetAssetPath("DroidSans.ttf"), 18.0f));
}

void MainApp::Render()
{
    // Add all the UI Components here.
    // Use ImGui namespace for default ImGui UI components.
    // Use GH namespace for advanced UI components.
    
    if (GH::ButtonCentered("Info"))
    {
        Platform::Get()->LaunchURL("https://github.com/AvnishGameDev/ImGuiBorderlessWindow");
    }
}
