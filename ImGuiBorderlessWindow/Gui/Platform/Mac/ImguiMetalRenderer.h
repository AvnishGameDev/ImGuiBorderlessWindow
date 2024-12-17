//
//  ImguiMetalRenderer.h
//  ImGuiBorderlessWindow
//
//  Created by Avnish Kirnalli on 14/12/24.
//

#import <Foundation/Foundation.h>

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ImguiMetalRenderer : NSObject

@property (nonatomic, strong, readonly) id<MTLDevice> device;
@property (nonatomic, strong, readonly) id<MTLCommandQueue> commandQueue;
@property (nonatomic, strong, readonly) MTKView* metalView;

- (MTLRenderPassDescriptor*)renderPassDesc;

- (ImguiMetalRenderer*)initWithWindowFrame:(CGRect)frame;

@end

NS_ASSUME_NONNULL_END
