#include "MacPlatform.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

#include "imgui.h"
#include "imgui_impl_metal.h"
#include "imgui_impl_osx.h"

#include "../../Gui.h"

bool MacPlatform::CreatePlatformWindow(const std::string& windowName)
{
    return true;
}

void MacPlatform::InitImguiImpl()
{
    //ImGui_ImplOSX_Init(mtkView);
    //ImGui_ImplMetal_Init(device);
}

void MacPlatform::ShutdownImguiImpl()
{
    ImGui_ImplOSX_Shutdown();
    ImGui_ImplMetal_Shutdown();
}

bool MacPlatform::DestroyPlatformWindow()
{
    return true;
}

void MacPlatform::BeginRender()
{
}

void MacPlatform::EndRender()
{
}
