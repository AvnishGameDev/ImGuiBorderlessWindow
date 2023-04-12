#include "MainApp.h"
#include "../Gui.h"

#include "../GuiHelper.h"

MainApp::MainApp() : App("ImGuiBorderlessWindow by AvnishGameDev")
{
    
}

void MainApp::Render()
{
    if (ImGui::Button("Visit my site"))
    {
        ShellExecute(0, 0, L"https://avnishgamedev.com", 0, 0, SW_SHOW);
    }
}
