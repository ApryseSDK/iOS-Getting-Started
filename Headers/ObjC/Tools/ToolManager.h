//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2014 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#import <Foundation/Foundation.h>
#import <PDFNet/PDFViewCtrl.h>

#import <UIKit/UIKit.h>

@class PTPDFViewCtrl;
@protocol ToolManagerDelegate;

@interface ToolManager : UIView<PTPDFViewCtrlToolManager>

/**
 * A UIView that conforms to the ToolDelegate protocol; the current tool.
 *
 */
@property (nonatomic, weak) UIView<PTToolDelegate>* tool;

/**
 * An object that conforms to the ToolManagerDelegate protocol.
 *
 */
@property (nonatomic, weak) id<ToolManagerDelegate> delegate;

/**
 * The PDFViewCtrl that the ToolManager is initialized with.
 *
 */
@property (nonatomic, weak) PTPDFViewCtrl* pdfViewCtrl;

/**
 * Returns a newly initialized tool with the required pointer to the PTPDFViewCtrl on which it will operate.
 *
 * @param in_pdfViewCtrl a pointer to the PTPDFViewCtrl that the tool will operate.
 *
 * @return A newly initialized `tool` object.
 *
 */
- (id)initWithPDFViewCtrl:(PTPDFViewCtrl*)in_pdfViewCtrl;

/**
 * Create and set a new tool of the given type as the current tool.
 */
-(UIView<PTToolDelegate>*)changeTool:(Class)toolType;

/**
 * Returns the next tool to use if this tool did not completely handle an event.
 *
 * Tools receive events, listed as the optional selectors in this protocol, from a PTPDFViewCtrl. If a tool does not
 * finish handling an event (indicated by returning `NO` from one of the selectors that return a `BOOL`), then
 * getNextTool is used to instantiate a new tool that will continuning handling the event.
 *
 * @return a newly instantiated UIView that conforms to the ToolDelegate protocol.
 */
- (UIView<PTToolDelegate>*)getNewTool;


// touch gestures (on pdfScrollView)

/** @name Touch and Gesture Methods */

/**
 * Tells the receiver when one or more fingers touch down in the pdfScrollView.
 *
 * @param touches A set of UITouch instances that represent the touches for the starting phase of the event represented by event.
 *
 * @param event An object representing the event to which the touches belong.
 *
 * @return `YES` if the tool has handled the event, `NO` if it should be passed to a new tool of a different type.
 *
 */
- (BOOL)onTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;

/**
 * Tells the receiver when one or more fingers associated with an event move within the pdfScrollView.
 *
 * @param touches A set of UITouch instances that represent the touches for the starting phase of the event represented by event.
 *
 * @param event An object representing the event to which the touches belong.
 *
 * @return `YES` if the tool has handled the event, `NO` if it should be passed to a new tool of a different type.
 *
 */
- (BOOL)onTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;

/**
 * Tells the receiver when one or more fingers are raised from the pdfScrollView.
 *
 * @param touches A set of UITouch instances that represent the touches for the starting phase of the event represented by event.
 *
 * @param event An object representing the event to which the touches belong.
 *
 * @return `YES` if the tool has handled the event, `NO` if it should be passed to a new tool of a different type.
 *
 */
- (BOOL)onTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;

/**
 * Sent to the receiver when a system event (such as a low-memory warning) cancels a touch event.
 *
 * @param touches A set of UITouch instances that represent the touches for the starting phase of the event represented by event.
 *
 * @param event An object representing the event to which the touches belong.
 *
 * @return `YES` if the tool has handled the event, `NO` if it should be passed to a new tool of a different type.
 *
 */
- (BOOL)onTouchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

/**
 * Tells the delegate that a long press has occured on the pdfScrollView.
 *
 * @param gestureRecognizer The gesture recognizer that triggered the event.
 *
 * @return `YES` if the tool has handled the event, `NO` if it should be passed to a new tool of a different type.
 */
- (BOOL)handleLongPress:(UILongPressGestureRecognizer *)gestureRecognizer;

/**
 * Tells the delegate that a single tap has occured on the pdfScrollView.
 *
 * @param gestureRecognizer The gesture recognizer that trigger the event.
 *
 * @return `YES` if the tool has handled the event, `NO` if it should be passed to a new tool of a different type.
 */
- (BOOL)handleTap:(UITapGestureRecognizer *)gestureRecognizer;

/**
 * Returns whether to cancel touches related to the content subview and start dragging.
 *
 * This event cannot be forwarded to another tool.
 *
 * @param view The pdfScrollVIew.
 *
 * @return `YES to cancel further touch messages to pdfScrollView, NO to have view continue to receive those messages.
 */
- (BOOL)touchesShouldCancelInContentView:(UIView *)view;

/**
 * Implemented to customize the default behavior when a finger touches down in the pdfScrollView.
 *
 * @param touches A set of UITouch instances that represent the touches for the starting phase of the event represented by event.
 *
 * @param event An object representing the event to which the touch objects in touches belong.
 *
 * @param view The subview in the content where the touch-down gesture occurred.
 *
 * @return `YES` if the tool has handled the event, `NO` if it should be passed to a new tool of a different type.
 */
- (BOOL)touchesShouldBegin:(NSSet *)touches withEvent:(UIEvent *)event inContentView:(UIView *)view;

/** @name pdfScrollView methods */

/**
 * Tells the delegate when the user scrolls the content view within the receiver.
 *
 * @param scrollView The scrollview object in which the scrolling occurred.
 *
 */
- (void)pdfScrollViewDidScroll:(UIScrollView *)scrollView;

/**
 * Tells the delegate when the scroll view is about to start scrolling the content.
 *
 * @param scrollView The scroll-view object that is about to scroll the content view.
 *
 */
- (void)pdfScrollViewWillBeginDragging:(UIScrollView *)scrollView;

/**
 * Tells the delegate when dragging ended in the scroll view.
 *
 * @param scrollView The scroll-view object that is about to scroll the content view.
 *
 * @param decelerate `YES` if the scrolling movement will continue, but decelerate, after a touch-up gesture during a dragging operation. If the value is `NO`, scrolling stops immediately upon touch-up.
 *
 */
- (void)pdfScrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;

/**
 *  Asks the delegate if the scroll view should scroll to the top of the content.
 *
 * If the delegate doesn’t implement this method, `YES` is assumed.
 *
 * @param scrollView The scroll-view object that perform the scrolling operation.
 *
 * @return YES to permit scrolling to the top of the content, NO to disallow it.
 *
 */
- (BOOL)pdfScrollViewShouldScrollToTop:(UIScrollView *)scrollView; // will respect result returned by delegate

/**
 * Tells the delegate that the scroll view scrolled to the top of the content.
 *
 * @param scrollView The scroll-view object that perform the scrolling operation.
 *
 */
- (void)pdfScrollViewDidScrollToTop:(UIScrollView *)scrollView;

/**
 * Tells the delegate that the scroll view is starting to decelerate the scrolling movement.
 *
 * @param scrollView The scroll-view object that is decelerating the scrolling of the content view.
 *
 */
- (void)pdfScrollViewWillBeginDecelerating:(UIScrollView *)scrollView;

/**
 * Tells the delegate that the scroll view has ended decelerating the scrolling movement.
 *
 * @param scrollView The scroll-view object that is decelerating the scrolling of the content view.
 *
 */
- (void)pdfScrollViewDidEndDecelerating:(UIScrollView *)scrollView;

/**
 * Tells the delegate that zooming of the content in the scroll view is about to commence.
 *
 * This method is called at the beginning of zoom gestures and in cases where a change in zoom level is to be animated.
 * You can use this method to store state information or perform any additional actions prior to zooming the view’s content.
 *
 * @param scrollView The scrollview object displaying the content view.
 *
 * @param view The view object whose content is about to be zoomed.
 *
 */
- (void)pdfScrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(UIView *)view;

/**
 * Tells the delegate when the user zooms the content view within the receiver.
 *
 * @param scrollView The scrollview object in which the scrolling occurred.
 *
 * @param view The view object representing that part of the content view that needs to be scaled.
 *
 * @param scale The scale factor to use for scaling.
 *
 */
- (void)pdfScrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(float)scale;

/**
 * Tells the delegate that the scroll view’s zoom factor changed.
 *
 * @param scrollView The scroll-view object whose zoom factor changed.
 *
 */
- (void)pdfScrollViewDidZoom:(UIScrollView *)scrollView;

/**
 * Tells the delegate when a scrolling animation in the scroll view concludes.
 *
 * @param scrollView The scroll-view object that is performing the scrolling animation.
 *
 */
- (void)pdfScrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView;

// Outer scroll view delegates - holds scrollView when in single page mode. //

/** @name outerScrollView methods */

/**
 * Tells the delegate when the user scrolls the content view within the receiver.
 *
 * @param scrollView The scrollview object in which the scrolling occurred.
 *
 */
- (void)outerScrollViewDidScroll:(UIScrollView *)scrollView;

/**
 * Tells the delegate when the scroll view is about to start scrolling the content.
 *
 * @param scrollView The scroll-view object that is about to scroll the content view.
 *
 */
- (void)outerScrollViewWillBeginDragging:(UIScrollView *)scrollView;

/**
 * Tells the delegate when dragging ended in the scroll view.
 *
 * @param scrollView The scroll-view object that is about to scroll the content view.
 *
 * @param decelerate `YES` if the scrolling movement will continue, but decelerate, after a touch-up gesture during a dragging operation. If the value is `NO`, scrolling stops immediately upon touch-up.
 *
 */
- (void)outerScrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;

/**
 *  Asks the delegate if the scroll view should scroll to the top of the content.
 *
 * If the delegate doesn’t implement this method, `YES` is assumed.
 *
 * @param scrollView The scroll-view object that perform the scrolling operation.
 *
 * @return YES to permit scrolling to the top of the content, NO to disallow it.
 *
 */
- (BOOL)outerScrollViewShouldScrollToTop:(UIScrollView *)scrollView; // will respect result returned by delegate

/**
 * Tells the delegate that the scroll view scrolled to the top of the content.
 *
 * @param scrollView The scroll-view object that perform the scrolling operation.
 *
 */
- (void)outerScrollViewDidScrollToTop:(UIScrollView *)scrollView;

/**
 * Tells the delegate that the scroll view is starting to decelerate the scrolling movement.
 *
 * @param scrollView The scroll-view object that is decelerating the scrolling of the content view.
 *
 */
- (void)outerScrollViewWillBeginDecelerating:(UIScrollView *)scrollView;

/**
 * Tells the delegate that the scroll view has ended decelerating the scrolling movement.
 *
 * @param scrollView The scroll-view object that is decelerating the scrolling of the content view.
 *
 */
- (void)outerScrollViewDidEndDecelerating:(UIScrollView *)scrollView;

/**
 * Tells the delegate that zooming of the content in the scroll view is about to commence.
 *
 * This method is called at the beginning of zoom gestures and in cases where a change in zoom level is to be animated.
 * You can use this method to store state information or perform any additional actions prior to zooming the view’s content.
 *
 * @param scrollView The scrollview object displaying the content view.
 *
 * @param view The view object whose content is about to be zoomed.
 *
 */
- (void)outerScrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(UIView *)view;

/**
 * Tells the delegate when the user zooms the content view within the receiver.
 *
 * @param scrollView The scrollview object in which the scrolling occurred.
 *
 * @param view The view object representing that part of the content view that needs to be scaled.
 *
 * @param scale The scale factor to use for scaling.
 *
 */
- (void)outerScrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(float)scale;

/**
 * Tells the delegate that the scroll view’s zoom factor changed.
 *
 * @param scrollView The scroll-view object whose zoom factor changed.
 *
 */
- (void)outerScrollViewDidZoom:(UIScrollView *)scrollView;

/**
 * Tells the delegate when a scrolling animation in the scroll view concludes.
 *
 * @param scrollView The scroll-view object that is performing the scrolling animation.
 *
 */
- (void)outerScrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView;

/**
 * Tells the delegate that the page layout has changed (such as from cover to cover facing).
 */
- (void)onLayoutChanged;

/**
 * Tells the delegate that tool has been attached to the view hierarchy and can now become
 * the first responder.
 */
- (void)onToolAttachedToViewHierarchy;

/** Tells the delegate that the current page number changes.
 *
 * @param oldPageNumber The previous page number.
 *
 * @param newPageNumber The new page number.
 *
 */
- (void)pageNumberChangedFrom:(int)oldPageNumber To:(int)newPageNumber;

/**
 * Tells the delegate that `postCustomEvent` has been executed on the main loop.
 *
 * This method gives the tool the opportunity to change to a new tool if it wishes to do so.
 *
 * @return `YES` if the tool has handled the event, `NO` if it should be passed to a new tool of a different type.
 *
 */
- (BOOL)onCustomEvent:(id)userData;

/**
 * Tells the delegate that PTPDFViewCtrl has opened a new document via its selector setDoc.
 *
 */
- (void)onSetDoc;

/**
 * Tells the delegate that a render job is complete.
 */
- (void)onRenderFinished;

@end

@protocol ToolManagerDelegate<NSObject>

@optional

/**
 * Tells the delegate that the tool has changed.
 *
 * @param toolManager The ToolManager that had the tool change.
 *
 */
- (void)toolChanged:(ToolManager*)toolManager;

/**
 * Raised when the tools code adds an annotation
 *
 */
- (void)annotationAdded:(PTAnnot*)annotation onPageNumber:(unsigned long)pageNumber;

/**
 * Raised when the tools code modifies an annotation
 *
 */
- (void)annotationModified:(PTAnnot*)annotation onPageNumber:(unsigned long)pageNumber;

/**
 * Raised when the tools code removes an annotation
 *
 */
- (void)annotationRemoved:(PTAnnot*)annotation onPageNumber:(unsigned long)pageNumber;

@end
