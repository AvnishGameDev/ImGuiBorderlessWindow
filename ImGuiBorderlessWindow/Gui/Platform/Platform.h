#pragma once

#include <string>

/** Callstack:
        1. CreatePlatformWindow()
        2. InitImguiImpl()
        3. BeginRender()
        4. EndRender()
        5. ShutdownImguiImpl()
        6. DestroyPlatformWindow()
 **/

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
    
    /* File IO Helpers */
    virtual std::string GetAssetPath(const std::string& relativePath) = 0;
    
    /* Misc */
    virtual void LaunchURL(const std::string& URL) = 0;
    
private:
    static Platform* m_CurrentPlatform;
};
