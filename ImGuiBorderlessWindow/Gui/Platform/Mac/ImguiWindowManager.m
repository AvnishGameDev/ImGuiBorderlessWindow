//
//  ImguiWindowManager.m
//  ImGuiBorderlessWindow
//
//  Created by Avnish Kirnalli on 14/12/24.
//

#import "ImguiWindowManager.h"
#import "ImguiMetalRenderer.h"
#import "DraggableView.h"

#import <Cocoa/Cocoa.h>

@implementation ImguiWindowManager

- (instancetype)initWithFrame:(CGRect)frame name:(NSString*)windowName
{
    self = [super init];
    if (self)
    {
        _window = [[NSWindow alloc] initWithContentRect:frame styleMask:NSWindowStyleMaskBorderless backing:NSBackingStoreBuffered defer:NO];
        
        // Setup App Menus
        @autoreleasepool {
            // Get the App Menu (the first menu in the main menu bar)
            NSMenu *appMenu = [[NSMenu alloc] initWithTitle:@"AppMenu"];
            
            // Add "About" menu item
            [[appMenu addItemWithTitle:@"About"
                               action:@selector(showAbout)
                         keyEquivalent:@""] setTarget:self];
            
            // Add separator and "Quit" item
            [appMenu addItem:[NSMenuItem separatorItem]];
            [appMenu addItemWithTitle:[@"Quit " stringByAppendingString:windowName]
                               action:@selector(terminate:)
                        keyEquivalent:@""];
            
            // Set it as the first menu in the main menu bar
            NSMenuItem *appMenuItem = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
            [appMenuItem setSubmenu:appMenu];
            [[NSApp mainMenu] addItem:appMenuItem];
        }
        
        NSWindowController* windowController = [[NSWindowController alloc] initWithWindow:self.window];
        [windowController autorelease];
        
        //View
        _metalRenderer = [[ImguiMetalRenderer alloc] initWithWindowFrame:[self.window frame]];
        _view = [self.metalRenderer metalView];
        [self.window setContentView:self.view];
        
        [self.window setAcceptsMouseMovedEvents:YES];
        
        // Set app title
        [self.window setTitle:windowName];
        
        // Allow to be key window
        self.window.hidesOnDeactivate = NO;
        
        // Curve
        self.window.backgroundColor = [NSColor clearColor];
        self.window.opaque = NO;
        self.window.hasShadow = YES;
        [self.window setLevel:NSMainMenuWindowLevel];
        self.window.contentView.wantsLayer = YES;
        self.window.contentView.layer.cornerRadius = 15.0;
        self.window.contentView.layer.masksToBounds = YES;
        [self.window center];
        
        // Draggable Area at top of Window
        const NSInteger PIXELS_FROM_TOP = 20;
        NSRect draggableFrame = NSMakeRect(0, self.window.contentView.frame.size.height - PIXELS_FROM_TOP,
                                           self.window.contentView.frame.size.width,
                                           PIXELS_FROM_TOP);
        DraggableView *draggableView = [[DraggableView alloc] initWithFrame:draggableFrame];
        draggableView.autoresizingMask = NSViewWidthSizable; // Adjust size with the window
        draggableView.wantsLayer = YES;
        draggableView.layer.backgroundColor = [[NSColor clearColor] CGColor];
        
        [self.window.contentView addSubview:draggableView];
        [self.window orderFront:self];
        [draggableView release];
    }
    return self;
}

- (void)showAbout
{
    [NSApp orderFrontStandardAboutPanel:self];
}

- (void)dealloc
{
    for (NSView* view in self.window.contentView.subviews)
    {
        [view removeFromSuperview];
    }
    [self.window close];
    [self.metalRenderer release];
    
    [super dealloc];
}

@end
