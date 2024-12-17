// Copyright (C) 2023 Avnish Kirnalli.

#include "App.h"

#include <thread>

#include "../Gui.h"
#include "../Themes.h"
#include "../Platform/Platform.h"

#if _DEBUG
#include <iostream>
#endif

using namespace std;

App::App(std::string _appName, int _width, int _height) : appName(std::move(_appName))
{
    // Create gui
    Gui::WIDTH = _width;
    Gui::HEIGHT = _height;
    Gui::windowName = appName.c_str();
    
    if (!Platform::Get()->CreatePlatformWindow(appName))
    {
#if _DEBUG
        std::cerr << "Error creating Platform Window From App!" << std::endl;
#endif
        return;
    }
    
    Gui::CreateImGui();
    
    //Theme::DefaultDark();
}

App::~App()
{
    Gui::DestroyImGui();
    Platform::Get()->DestroyPlatformWindow();
}

void App::Update()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

void App::BeginRender()
{
    Platform::Get()->BeginRender();
    Gui::BeginRender();
    Gui::BeginImGuiRender();
}

void App::EndRender()
{
    Gui::EndImGuiRender();
    Gui::EndRender();
    Platform::Get()->EndRender();
}


