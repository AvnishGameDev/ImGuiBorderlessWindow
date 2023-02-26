#include "App.h"

#include "Gui.h"
#include "Themes.h"

using namespace std;

App::App()
{
    Themes::DefaultDark();
}

void App::Update()
{
    
}

void App::Render()
{
    if (ImGui::Button("Visit my site"))
    {
        ShellExecute(0, 0, L"https://avnishgamedev.com", 0, 0, SW_SHOW);
    }
}


