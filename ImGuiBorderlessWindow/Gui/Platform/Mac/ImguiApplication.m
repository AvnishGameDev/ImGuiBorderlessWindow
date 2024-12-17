//
//  ImguiApplication.m
//  ImGuiBorderlessWindow
//
//  Created by Avnish Kirnalli on 14/12/24.
//

#import "ImguiApplication.h"

@interface ImguiApplication ()
- (void)setWindowManager:(ImguiWindowManager*)windowManager;
@end

@implementation ImguiApplication

+ (instancetype)createAppWithFrame:(CGRect)frame name:(NSString*)windowName
{
    @autoreleasepool {
        ImguiApplication* app;
        if (NSApp == nil)
        {
            app = [ImguiApplication sharedApplication];
            // NSApp should be valid now
            
            [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
            [NSApp activateIgnoringOtherApps:YES];
            
            // Create Menu
            NSMenu* mainMenu;
            mainMenu = [[NSMenu alloc] init];
            [NSApp setMainMenu:mainMenu];
            mainMenu = nil;
            
            [NSApp finishLaunching];
            NSDictionary *appDefaults = [[NSDictionary alloc] initWithObjectsAndKeys:
                        [NSNumber numberWithBool:NO], @"AppleMomentumScrollSupported",
                        [NSNumber numberWithBool:NO], @"ApplePressAndHoldEnabled",
                        [NSNumber numberWithBool:YES], @"ApplePersistenceIgnoreState",
                        nil];
            [[NSUserDefaults standardUserDefaults] registerDefaults:appDefaults];
            [appDefaults release];
        }
        if (NSApp && ![NSApp delegate])
        {
            //[NSApp setDelegate:[[ImguiAppDelegate alloc] init]];
        }
        [app setWindowManager:[[ImguiWindowManager alloc] initWithFrame:frame name:windowName]];
        return app;
    }
}

- (void)frame
{
    @autoreleasepool {
            NSEvent* ev;
            do {
                ev = [NSApp nextEventMatchingMask: NSEventMaskAny
                                        untilDate: nil
                                           inMode: NSDefaultRunLoopMode
                                          dequeue: YES];
                if (ev) {
                    // handle events here
                    [NSApp sendEvent: ev];
                }
            } while (ev);
        
        [NSApp updateWindows];
    }
}

- (void)setWindowManager:(ImguiWindowManager*)windowManager
{
    _windowManager = windowManager;
}

- (void)terminate:(nullable id)sender
{
    [self.windowManager release];
    [super terminate:sender];
}

@end
