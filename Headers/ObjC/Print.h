//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2014 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "PDFNetOBJC.h"

@protocol PrintDelegate;

@interface Print : NSObject<UIPrintInteractionControllerDelegate>
{
    
}

/**
 * 
 * An asynchronous selector that prepares a document for printing and calls the PrintDelegate selector
 * PreparedToPrint:UserData: when perperation is complete. It may take a moment to prepare the document,
 * so it is recommended that the user be presented with information to this effect.
 *
 * @param doc - A valid PDFDoc object.
 * @param printDelegate - An object that conforms to the PrintDelegate protocol.
 * @param userData - Optional user data that is provided to the delegate's callback selector.
 *
 */
-(void)PrepareDocToPrint:(PDFDoc*)doc Delegate:(NSObject<PrintDelegate>*)printDelegate UserData:(id)userData;

/**
 * 
 * For iPad. A convenience method to print the PDF document located where the first parameter points.
 * Typically called from the PreparedToPrint:UserData: selector of the PrintDelegate protocol.
 * (If called on an iPhone, then 2nd and 3rd parameter are ignored.)
 *
 * @param docFilePath - Number of seconds between refreshes.
 * @param rect - The rectangle from which to present the UIPrintInteractionController.
 * @param view - The view that is the superview of the presented UIPrintInteractionController.
 * @param jobName - The name of the print job. (Optional)
 * @param animated - Whether the presented UIPrintInteractionController is animated.
 * @param completionHandler - Function that is called when printing is complete.
 *
 */
-(void)PrintDoc:(NSString*)docFilePath FromRect:(CGRect)rect InView:(UIView*)view WithJobName:(NSString*)jobName Animated:(BOOL)animated CompletionHandler:(UIPrintInteractionCompletionHandler)completionHandler;

/**
 *
 * For iPhone (and iPod Touch). A convenience method to print the PDF document located where the first parameter points.
 * Typically called from the PreparedToPrint:UserData: selector of the PrintDelegate protocol.
 *
 * @param docFilePath - Number of seconds between refreshes.
 * @param animated - Whether the presented UIPrintInteractionController is animated.
 * @param completionHandler - Function that is called when printing is complete.
 *
 */
-(void)PrintDoc:(NSString*)docFilePath WithJobName:(NSString*)jobName Animated:(BOOL)animated CompletionHandler:(UIPrintInteractionCompletionHandler)completionHandler;

@end

/** Tells the delegate when the PDF is prepared for printing after a call to an instance of Print's selector `PrepareDocToPrint:Delegate:UserData`.
 *
 */
@protocol PrintDelegate <NSObject>

@required

/**
 *
 * Selector called by the Print selector PrepareDocToPrint when the document has been prepared for printing.
 *
 * @param docFilePath - The file path of the PDF document that will be printed.
 * @param userData - User data provided in PrepareDocToPrint:Delegate:UserData:.
 *
 */
- (void)PreparedToPrint:(NSString*)docFilePath UserData:(id)userData;

@end