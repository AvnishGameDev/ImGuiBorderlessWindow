//
//  DraggableView.m
//  ImGuiBorderlessWindow
//
//  Created by Avnish Kirnalli on 15/12/24.
//

#import "DraggableView.h"

@implementation DraggableView

- (void)mouseDown:(NSEvent *)event {
    // Start dragging the window
    [self.window performWindowDragWithEvent:event];
}

@end
