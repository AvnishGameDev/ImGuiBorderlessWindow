#pragma once

#include "../Platform.h"
#include <GLFW/glfw3.h>

class LinuxPlatform : public Platform
{
public:
    static LinuxPlatform* Get() { return instance; }
    static void Create() { instance = new LinuxPlatform(); }
    static void Destroy() { delete instance; }
    
    bool CreatePlatformWindow(const std::string& windowName) override;
    void InitImguiImpl() override;
    void ShutdownImguiImpl() override;
    bool DestroyPlatformWindow() override;
    void BeginRender() override;
    void EndRender() override;
    
    /* File IO Helpers */
    std::string GetAssetPath(const std::string& relativePath) override;
    
    /* Misc */
    void LaunchURL(const std::string& URL) override;

private:
    static LinuxPlatform* instance;
    GLFWwindow* window = nullptr;
    bool isRunning = true;
};
