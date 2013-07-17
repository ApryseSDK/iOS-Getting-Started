//
//  ColorSwatchView.h
//  ColorPicker
//
//  Created by Fabián Cañas on 9/9/10.
//  Copyright 2010 Fabián Cañas. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface ColorSwatchView : UIView {
    UIColor *swatchColor;
}

@property (readwrite, retain, nonatomic) UIColor *swatchColor;

@end
