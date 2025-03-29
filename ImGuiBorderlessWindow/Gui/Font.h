#pragma once

#include <string>
#include "ThirdParty/ImGui/imgui.h"

struct GuiFont
{
    GuiFont(const std::string& inFile, float inSize) : fontSize(inSize)
    {
        fontFile = std::move(inFile);
        const auto io = ImGui::GetIO();
        imgui_font = io.Fonts->AddFontFromFileTTF(fontFile.c_str(), inSize);
    }
    
    std::string fontFile;
    float fontSize;

    ImFont* GetImGuiFont() const { return imgui_font; }

private:
    ImFont* imgui_font{nullptr};
};
