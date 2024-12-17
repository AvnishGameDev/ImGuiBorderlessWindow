//
//  ImguiMetalRenderer.m
//  ImGuiBorderlessWindow
//
//  Created by Avnish Kirnalli on 14/12/24.
//

#import "ImguiMetalRenderer.h"

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

@implementation ImguiMetalRenderer

- (MTLRenderPassDescriptor*)renderPassDesc
{
    return [self.metalView currentRenderPassDescriptor];
}

- (ImguiMetalRenderer*)initWithWindowFrame:(CGRect)frame
{
    self = [super init];
    if (self)
    {
        _device = MTLCreateSystemDefaultDevice();
        _commandQueue = [self.device newCommandQueue];
        _metalView = [[MTKView alloc] initWithFrame:frame device:self.device];
        self.metalView.colorPixelFormat = MTLPixelFormatBGRA8Unorm; // Standard pixel format
        self.metalView.clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0); // Default black
        self.metalView.enableSetNeedsDisplay = NO; // Manual rendering
    }
    return self;
}

- (void)dealloc
{
    [self.metalView removeFromSuperview];
    self.metalView.delegate = nil;
    _metalView = nil;
    [super dealloc];
}

@end
