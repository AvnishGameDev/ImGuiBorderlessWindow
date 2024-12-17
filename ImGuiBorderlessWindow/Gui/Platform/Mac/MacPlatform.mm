#include "MacPlatform.h"

#include "imgui.h"
#include "imgui_impl_metal.h"
#include "imgui_impl_osx.h"

#include "../../Gui.h"

#import "ImguiApplication.h"

static ImguiApplication* application;

bool MacPlatform::CreatePlatformWindow(const std::string& windowName)
{
    application = [ImguiApplication createAppWithFrame:CGRectMake(0,0,Gui::WIDTH,Gui::HEIGHT) name:[NSString stringWithUTF8String:windowName.c_str()]];
    return true;
}

void MacPlatform::InitImguiImpl()
{
    ImGui_ImplOSX_Init([[application windowManager] view]);
    ImGui_ImplMetal_Init([[[application windowManager] metalRenderer] device]);
}

void MacPlatform::ShutdownImguiImpl()
{
    ImGui_ImplOSX_Shutdown();
    ImGui_ImplMetal_Shutdown();
}

bool MacPlatform::DestroyPlatformWindow()
{
    [application terminate:nil];
    return true;
}

void MacPlatform::BeginRender()
{
    [application frame];
    
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = application.windowManager.metalRenderer.metalView.bounds.size.width;
    io.DisplaySize.y = application.windowManager.metalRenderer.metalView.bounds.size.height;

    CGFloat framebufferScale = application.windowManager.metalRenderer.metalView.window.screen.backingScaleFactor ?: NSScreen.mainScreen.backingScaleFactor;
    io.DisplayFramebufferScale = ImVec2(framebufferScale, framebufferScale);
    
    @autoreleasepool {
        MTLRenderPassDescriptor* renderPassDescriptor = [[[application windowManager] metalRenderer] renderPassDesc];
        id<MTLCommandBuffer> commandBuffer = [[[[application windowManager] metalRenderer] commandQueue] commandBuffer];
        if (renderPassDescriptor == nil)
        {
            [commandBuffer commit];
            return;
        }
        
        // New ImGui Impl Frames
        ImGui_ImplOSX_NewFrame([[application windowManager] view]);
        ImGui_ImplMetal_NewFrame(renderPassDescriptor);
    }
}

void MacPlatform::EndRender()
{
    @autoreleasepool {
        MTLRenderPassDescriptor* renderPassDescriptor = [[[application windowManager] metalRenderer] renderPassDesc];
        id<MTLCommandBuffer> commandBuffer = [[[[application windowManager] metalRenderer] commandQueue] commandBuffer];
        if (renderPassDescriptor == nil)
        {
            [commandBuffer commit];
            return;
        }
        
        ImGui::Render();
        ImDrawData* draw_data = ImGui::GetDrawData();
        
        const ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        id <MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        [renderEncoder pushDebugGroup:@"Dear ImGui rendering"];
        ImGui_ImplMetal_RenderDrawData(draw_data, commandBuffer, renderEncoder);
        [renderEncoder popDebugGroup];
        [renderEncoder endEncoding];
        
        // Present
        [commandBuffer presentDrawable:[[[[application windowManager] metalRenderer] metalView] currentDrawable]];
        [commandBuffer commit];
    }
}

std::string MacPlatform::GetAssetPath(const std::string& relativePath)
{
    @autoreleasepool {
        NSString* path = [NSString stringWithUTF8String:relativePath.c_str()];
        NSBundle* mainBundle = [NSBundle mainBundle];
            
        NSString* assetPath = [mainBundle pathForResource:[@"Assets/" stringByAppendingString:path] ofType:nil];
        return [assetPath UTF8String];
    }
}

void MacPlatform::LaunchURL(const std::string& URL)
{
    @autoreleasepool {
        // Convert C string to an NSString
        NSString* urlString = [NSString stringWithUTF8String:URL.c_str()];
        
        // Create an NSURL object
        NSURL* urlObj = [NSURL URLWithString:urlString];
        
        if ([[NSWorkspace sharedWorkspace] openURL:urlObj]) {
            // Success
        } else {
            NSLog(@"%@", [@"Failed to Launch URL: " stringByAppendingString:urlObj.absoluteString]);
        }
    }
}
