//
//  ColorPickerViewController.h
//  ColorPicker
//
//  Created by Gilly Dekel on 23/3/09.
//  Extended by Fabián Cañas August 2010.
//  Copyright 2010. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ColorPickerViewController;

@protocol ColorPickerViewControllerDelegate <NSObject>

- (void)colorPickerViewController:(ColorPickerViewController *)colorPicker didSelectColor:(UIColor *)color;
- (void)noteEditCancelButtonPressed;
@end

@interface ColorPickerViewController : UIViewController {
    id<ColorPickerViewControllerDelegate> delegate;
#ifdef IPHONE_COLOR_PICKER_SAVE_DEFAULT
    NSString *defaultsKey;
#else
    UIColor *defaultsColor;
#endif
    IBOutlet UIButton *chooseButton;
}

// Use this member to update the display after the default color value
// was changed.
// This is required when e.g. the view controller is kept in memory
// and is re-used for another color value selection
// Automatically called after construction, so no need to do it here.
-(void) moveToDefault;


@property(nonatomic,assign)	id<ColorPickerViewControllerDelegate> delegate;
#ifdef IPHONE_COLOR_PICKER_SAVE_DEFAULT
  @property(readwrite,nonatomic,retain) NSString *defaultsKey;
#else
  @property(readwrite,nonatomic,retain) UIColor *defaultsColor;
#endif
@property(readwrite,nonatomic,retain) IBOutlet UIButton *chooseButton;

- (IBAction) chooseSelectedColor;
- (IBAction) chooseEmptyColor;
- (IBAction) cancelColorSelection;
- (UIColor *) getSelectedColor;

@end

