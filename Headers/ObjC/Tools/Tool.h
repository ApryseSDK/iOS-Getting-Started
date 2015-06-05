//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2014 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#import <Foundation/Foundation.h>

#import <PDFNet/PDFViewCtrl.h>

@class PTPDFViewCtrl;

@class SelectionRectContainerView;

@interface ToolView : UIImageView
@end

#define GET_ANNOT_AT_DISTANCE_THRESHOLD 22
#define GET_ANNOT_AT_MINIMUM_LINE_WEIGHT 10

@interface Tool : UIView<UIGestureRecognizerDelegate, PTToolDelegate,UIPopoverControllerDelegate> {
    
    @public
    PTPDFDoc* m_dummy_doc;
    
    @package
    Class nextToolType;
    PTAnnot* m_moving_annotation;
    int m_annot_page_number;
    __weak PTPDFViewCtrl* m_pdfViewCtrl;
    SelectionRectContainerView* selectionRectContainerView;
    CGRect lastTargetRect;
	CGPoint m_down;
    PTPDFPoint* m_screenPt;
    PTPDFPoint* m_pagePt;
    UILabel* m_pageNumberLabel;
    UIPopoverController* popoverController;
	BOOL textMarkupAdobeHack;
}

/**
 * If YES, next touches will not create a second annotation
 */
@property (nonatomic, assign) BOOL backToPanToolAfterUse;

/**
 * Class of tool to use when document is interacted with after
 * creating a tool. If backToPanToolAfterUse is YES, then this
 * will normally be the PanTool. Otherwise it will be the currently
 * used annotaiton creation tool.
 */
@property (nonatomic, assign) Class defaultClass;

@property (nonatomic, assign) BOOL pageIndicatorIsVisible;
@property (nonatomic, copy) NSString* annotationAuthor;
@property (readonly) BOOL createsAnnotation;
@property (nonatomic, assign) BOOL allowScrolling;

+ (BOOL)createsAnnotation;
- (id)initWithPDFViewCtrl:(PTPDFViewCtrl*)in_pdfViewCtrl;
- (Tool*)getNewTool;
- (void)onLayoutChanged;
- (UIViewController *)viewController;
- (void)noteEditCancelButtonPressed:(BOOL)showMenu;
- (void)editSelectedAnnotationNote;
- (PTPDFRect*)GetRectUnion:(PTPDFRect*)rect1 Rect2:(PTPDFRect*)rect2;
- (void)deleteSelectedAnnotation;
- (void)saveNewNoteForMovingAnnotationWithString:(NSString*)str;
- (void)keepToolAppearanceOnScreen;
- (void)removeAppearanceViews;

// touch events to override
- (BOOL)onTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (BOOL)onTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (BOOL)onTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (BOOL)onTouchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;
- (BOOL)handleLongPress:(UILongPressGestureRecognizer *)gestureRecognizer;
- (BOOL)handleTap:(UITapGestureRecognizer *)sender;
- (BOOL)handleDoubleTap:(UITapGestureRecognizer*)sender;
- (BOOL)touchesShouldCancelInContentView:(UIView *)view;
- (BOOL)touchesShouldBegin:(NSSet *)touches withEvent:(UIEvent *)event inContentView:(UIView *)view;

// scroll events to override
- (void)pdfScrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(float)scale;
- (void)pdfScrollViewDidEndDecelerating:(UIScrollView *)scrollView;
- (void)pdfScrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;
- (void)pdfScrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView;
- (void)pdfScrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(UIView *)view;
- (void)pdfScrollViewDidScroll:(UIScrollView *)scrollView;
- (void)pdfScrollViewDidZoom:(UIScrollView *)scrollView;

// events to notify interested parties
- (void)annotationAdded:(PTAnnot*)annotation onPageNumber:(unsigned long)pageNumber;
- (void)annotationModified:(PTAnnot*)annotation onPageNumber:(unsigned long)pageNumber;
- (void)annotationRemoved:(PTAnnot*)annotation onPageNumber:(unsigned long)pageNumber;

// internal and convenience methods
- (void) showMenu: (CGRect) targetRect animated:(BOOL)animated;
- (void) showMenu:(CGRect)targetRect;
- (void) showMenu;
- (void) hideMenu;
- (void) ConvertScreenPtToPagePtX:(CGFloat*)x Y:(CGFloat*)y PageNumber:(int)pageNumber;
- (void) ConvertPagePtToScreenPtX:(CGFloat*)x Y:(CGFloat*)y PageNumber:(int)pageNumber;
-(CGRect)PDFRectPage2CGRectScreen:(PTPDFRect*)r PageNumber:(int)pageNumber;


@end
