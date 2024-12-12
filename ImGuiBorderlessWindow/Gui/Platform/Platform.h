#pragma once

#include <string>

class Platform
{
public:
    static Platform* Get();

    virtual bool CreatePlatformWindow(const std::string& windowName) = 0;
    virtual void InitImguiImpl() = 0;
    virtual void ShutdownImguiImpl() = 0;
    virtual bool DestroyPlatformWindow() = 0;
    virtual void BeginRender() = 0;
    virtual void EndRender() = 0;
    
private:
    static Platform* m_CurrentPlatform;
};
