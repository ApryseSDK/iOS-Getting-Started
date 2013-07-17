//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2013 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#import <Foundation/Foundation.h>

#import "Tool.h"


@interface PanTool : Tool {
    
}

- (BOOL)handleLongPress:(UILongPressGestureRecognizer *)gestureRecognizer;
- (void)attachInitialMenuItems;

@end
