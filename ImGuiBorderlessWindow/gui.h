#pragma once
#include <d3d9.h>

namespace Gui
{
    // Constant window size
    constexpr int WIDTH = 400;
    constexpr int HEIGHT = 140;

    // When this changes, exit threads
    // and closes app :)
    inline bool isRunning = true;

    // winapi window vars
    inline HWND window = nullptr;
    inline WNDCLASSEX windowClass = { };

    // Points for window movement
    inline POINTS position = { };

    // DirectX state vars
    inline PDIRECT3D9 d3d = nullptr;
    inline LPDIRECT3DDEVICE9 device = nullptr;
    inline D3DPRESENT_PARAMETERS presentParameters = { };

    inline const char* windowName;

    // Handle window creation & destruction
    void CreateHWindow(const char* inWindowName) noexcept;
    void DestroyHWindow() noexcept;

    // Handle device creation & destruction
    bool CreateDevice() noexcept;
    void ResetDevice() noexcept;
    void DestroyDevice() noexcept;

    // Handle ImGui creation & destruction
    void CreateImGui() noexcept;
    void DestroyImGui() noexcept;

    // Rendering
    void BeginRender() noexcept;
    void EndRender() noexcept;
    void BeginImGuiRender() noexcept;
    void EndImGuiRender() noexcept;
}
