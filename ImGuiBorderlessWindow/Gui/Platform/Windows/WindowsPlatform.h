#pragma once

#include "../Platform.h"

#include <Windows.h>
#include <d3d9.h>

class WindowsPlatform : public Platform
{
public:
    static WindowsPlatform* Get() { return static_cast<WindowsPlatform*>(Platform::Get()); }
    
    bool CreatePlatformWindow(const std::string& windowName) override;
    void InitImguiImpl() override;
    void ShutdownImguiImpl() override;
    bool DestroyPlatformWindow() override;
    void BeginRender() override;
    void EndRender() override;
    
    // winapi window vars
    static HWND window;
    static WNDCLASSEX windowClass;

    // Points for window movement
    static POINTS position;

    // DirectX state vars
    static PDIRECT3D9 d3d;
    static LPDIRECT3DDEVICE9 device;
    static D3DPRESENT_PARAMETERS presentParameters;
    
    // Handle window creation & destruction
    void CreateHWindow(const char* inWindowName) noexcept;
    void DestroyHWindow() noexcept;

    // Handle device creation & destruction
    bool CreateDevice() noexcept;
    void ResetDevice() noexcept;
    void DestroyDevice() noexcept;
};