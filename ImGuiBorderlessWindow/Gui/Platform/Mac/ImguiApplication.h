//
//  ImguiApplication.h
//  ImGuiBorderlessWindow
//
//  Created by Avnish Kirnalli on 14/12/24.
//

#import <Cocoa/Cocoa.h>

#import "ImguiWindowManager.h"

NS_ASSUME_NONNULL_BEGIN

@interface ImguiApplication : NSApplication

@property (nonatomic, strong, readonly) ImguiWindowManager* windowManager;

+ (instancetype)createAppWithFrame:(CGRect)frame name:(NSString*)windowName;

- (void)frame;

- (void)terminate:(nullable id)sender;

@end

NS_ASSUME_NONNULL_END
