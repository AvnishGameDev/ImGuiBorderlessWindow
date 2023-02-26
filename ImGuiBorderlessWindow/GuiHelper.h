#pragma once

#include <string>

#include "imgui.h"

namespace GH // Gui Helper
{
    static void TextCentered(const std::string& text)
    {
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(text.c_str()).x) * 0.5f);
        ImGui::Text(text.c_str());
    }
    
    static void TextCenteredMultiline(const std::string& text)
    {
        const float win_width = ImGui::GetWindowSize().x;
        const float text_width = ImGui::CalcTextSize(text.c_str()).x;

        // calculate the indentation that centers the text on one line, relative
        // to window left, regardless of the `ImGuiStyleVar_WindowPadding` value
        float text_indentation = (win_width - text_width) * 0.5f;

        // if text is too long to be drawn on one line, `text_indentation` can
        // become too small or even negative, so we check a minimum indentation
        constexpr float min_indentation = 20.0f;
        if (text_indentation <= min_indentation) {
            text_indentation = min_indentation;
        }

        ImGui::NewLine();
        ImGui::SameLine(text_indentation);
        ImGui::PushTextWrapPos(win_width - text_indentation);
        ImGui::TextWrapped(text.c_str());
        ImGui::PopTextWrapPos();
    }
    
    static void TextCenterColored(const std::string& text, const ImVec4& color)
    {
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(text.c_str()).x) * 0.5f);
        ImGui::TextColored(color, text.c_str());
    }

    static bool ButtonCentered(const std::string& text)
    {
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(text.c_str()).x) * 0.5f);
        return ImGui::Button(text.c_str());
    }
}