//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2013 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#import <Foundation/Foundation.h>
//#import "MagnifierView.h"
#import "PDFViewCtrl.h"

@class PDFViewCtrl;

@class SelectionRectContainerView;


@interface Tool : UIView<ToolDelegate,UIPopoverControllerDelegate> {
    
    @public
    PDFDoc* m_dummy_doc;
    
    @package
    Class nextToolType;
    Annot* m_moving_annotation;
    int m_annot_page_number;
    PDFViewCtrl* m_pdfViewCtrl;
    SelectionRectContainerView* selectionRectContainerView;
    CGRect lastTargetRect;
    HighlightAnnot* m_default_text_annotation;
    Square* m_default_annotation;
    PDFPoint* m_screenPt;
    PDFPoint* m_pagePt;
    UILabel* m_pageNumberLabel;
    UIPopoverController* popoverController;
    
}

@property (nonatomic, assign) BOOL backToPanToolAfterUse;
@property (nonatomic, assign) BOOL pageIndicatorIsVisible;

- (id)initWithPDFViewCtrl:(PDFViewCtrl*)in_pdfViewCtrl;
- (Tool*)getNewTool;
- (void)onLayoutChanged;
- (void)suspendProgressiveRendering;
- (BOOL)conditionalRenderCancel;
- (void)conditionalRenderResume:(BOOL)wasRendering;
- (UIViewController *)viewController;
- (void)noteEditCancelButtonPressed:(BOOL)showMenu;
- (void)editSelectedAnnotationNote;
- (PDFRect*)GetRectUnion:(PDFRect*)rect1 Rect2:(PDFRect*)rect2;
- (void)deleteSelectedAnnotation;
-(void)saveNewNoteForMovingAnnotationWithString:(NSString*)str;


// touch events to override
- (BOOL)onTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (BOOL)onTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (BOOL)onTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (BOOL)onTouchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;
- (BOOL)handleLongPress:(UILongPressGestureRecognizer *)gestureRecognizer;
- (BOOL)handleTap:(UITapGestureRecognizer *)sender;
- (BOOL)touchesShouldCancelInContentView:(UIView *)view;
- (BOOL)touchesShouldBegin:(NSSet *)touches withEvent:(UIEvent *)event inContentView:(UIView *)view;

// scroll events to override
- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(float)scale;
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView;
- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;
- (void)scrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView;
- (void)scrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(UIView *)view;
- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(float)scale;
- (void)scrollViewDidScroll:(UIScrollView *)scrollView;
- (void)scrollViewDidZoom:(UIScrollView *)scrollView;

// internal and convenience methods
- (void) showMenu: (CGRect) targetRect animated:(BOOL)animated;
- (void) showMenu:(CGRect)targetRect;
- (void) showMenu;
- (void) ConvertScreenPtToPagePtX:(float*)x Y:(float*)y PageNumber:(int)pageNumber;
- (void) ConvertPagePtToScreenPtX:(float*)x Y:(float*)y PageNumber:(int)pageNumber;
-(CGRect)PDFRectPage2CGRectScreen:(PDFRect*)r PageNumber:(int)pageNumber;


@end
