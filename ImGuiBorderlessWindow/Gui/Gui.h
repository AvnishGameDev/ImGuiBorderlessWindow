// Copyright (C) 2023 Avnish Kirnalli.

#pragma once

struct GuiFont;

namespace Gui
{
    inline int WIDTH = 800;
    inline int HEIGHT = 600;
    
    // When this changes, exit threads
    // and closes app :)
    inline bool isRunning = true;

    inline const char* windowName;

    // Handle ImGui creation & destruction
    void CreateImGui() noexcept;
    void DestroyImGui() noexcept;

    // Rendering
    void BeginRender() noexcept;
    void EndRender() noexcept;
    void BeginImGuiRender() noexcept;
    void EndImGuiRender() noexcept;

    // Loading Fonts
    void PushFont(const GuiFont& inFont) noexcept;
    void PopFont();
}
