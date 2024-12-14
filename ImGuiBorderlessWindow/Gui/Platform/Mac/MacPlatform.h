#pragma once

#include "../Platform.h"

class MacPlatform : public Platform
{
public:
    static MacPlatform* Get() { return static_cast<MacPlatform*>(Platform::Get()); }
    
    bool CreatePlatformWindow(const std::string& windowName) override;
    void InitImguiImpl() override;
    void ShutdownImguiImpl() override;
    bool DestroyPlatformWindow() override;
    void BeginRender() override;
    void EndRender() override;
};
