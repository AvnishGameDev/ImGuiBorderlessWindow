//
//  ImguiWindowManager.h
//  ImGuiBorderlessWindow
//
//  Created by Avnish Kirnalli on 14/12/24.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#import "ImguiMetalRenderer.h"

NS_ASSUME_NONNULL_BEGIN

@interface ImguiWindowManager : NSObject

@property (nonatomic, strong, readonly) NSWindow* window;
@property (nonatomic, strong, readonly) NSView* view;
@property (nonatomic, strong, readonly) ImguiMetalRenderer* metalRenderer;

- (instancetype)initWithFrame:(CGRect)frame name:(NSString*)windowName;
- (void)showAbout;

@end

NS_ASSUME_NONNULL_END
