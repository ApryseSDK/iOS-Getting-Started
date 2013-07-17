//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2013 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------
//
//  IMPORTANT:
//  1. Call the method [PDFNet Initialize:@""] to initialize PDFNet in demo mode.
//  2. Read "About PDFNet SDK for iOS" readme.html in the Sample folder for a list of files
//     you must include in an app that uses PDFViewCtrl.


#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "PDFNetOBJC.h"
#import <CoreText/CoreText.h>



@class PDFViewIOS;

@protocol PDFViewCtrlDelegate;
@protocol ToolDelegate;

typedef enum {
    e_trn_fit_page,
    e_trn_fit_width,
    e_trn_fit_height,
    e_trn_zoom
} TrnPageViewMode;

typedef enum {
    e_trn_single_page = 1, 	
    e_trn_single_continuous, 	
    e_trn_facing, 	
    e_trn_facing_continuous, 	
    e_trn_facing_cover, 	
    e_trn_facing_continuous_cover 
} TrnPagePresentationMode;

typedef enum {
    e_trn_zoom_limit_absolute = 1,
    e_trn_zoom_limit_relative,
    e_trn_zoom_limit_none
} TrnZoomLimitMode;


/**
 * PDFViewCtrl is a utility class that can be used for interactive rendering of PDF documents.
 *
 * On iOS, PDFViewCtrl derives from UIView.
 *
 * PDFViewCtrl defines several coordinate spaces and it is important to understand their
 * differences:
 *
 * - Page Space refers to the space in which a PDF page is defined. It is determined by
 * a page itself and the origin is at the lower-left corner of the page. Note that Page
 * Space is independent of how a page is viewed in PDFView and each page has its own Page
 * space.
 *
 * - Canvas Space refers to the tightest axis-aligned bounding box of all the pages given
 * the current page presentation mode in PDFView. For example, if the page presentation
 * mode is e_single_continuous, all the pages are arranged vertically with one page in each
 * row, and therefore the Canvas Space is rectangle with possibly large height value. For
 * this reason, Canvas Space is also, like Page Space, independent of the zoom factor. Also
 * note that since PDFView adds gaps between adjacent pages, the Canvas Space is larger than
 * the space occupied by all the pages. The origin of the Canvas Space is located at the
 * upper-left corner.
 *
 * - Screen Space (or Client Space) is the space occupied by PDFView and its origin is at
 * the upper-left corner. Note that the virtual size of this space can extend beyond the
 * visible region.
 *
 * - Scrollable Space is the virtual space within which PDFView can scroll. It is determined
 * by the Canvas Space and the current zoom factor. Roughly speaking, the dimensions of the
 * Scrollable Space is the dimensions of the Canvas Space timed by the zoom. Therefore, a large
 * zoom factor will result in a larger Scrollable region given the same Canvas region. For this
 * reason, Scrollable Space might also be referred to as Zoomed Canvas Space. Note that since
 * PDFView adds gaps between pages in Canvas Space and these gaps are not scaled when rendered,
 * the scrollable range is not exactly what the zoom factor times the Canvas range. For
 * functions such as SetHScrollPos(), SetVScrollPos(), GetCanvasHeight(), and
 * GetCanvasWidth(), it is the Scrollable Space that is involved.
 *
 */
@interface PDFViewCtrl : UIView<UIScrollViewDelegate, UIGestureRecognizerDelegate, UIPrintInteractionControllerDelegate> {
    
    @public
    /**
     The view that displays the PDF, that is the content view of a UIScrollView.
     */
    UIView* ContainerView;
    
    /**
     Used by tools to remember current annotation properties.
     */
    PDFDoc* m_annot_holder_doc;


    @private
    UIScrollView* innerScrollView;
    UIScrollView* outerScrollView;
    PDFViewIOS* IOSPDFView;
	CGRect Frame;
    BOOL midZoom;
    BOOL postZoom;
    BOOL m_outerPostZoom;
    BOOL delayRender;
    BOOL m_downloaded_doc;
    int touchedPageNumber;
    NSMutableDictionary* blankPages;
    NSMutableDictionary* tilesOnScreen;
    NSMutableArray* tilesPendingDeletion;
    NSMutableArray* tileBank;
    double lastYPos;
    double lastXPos;
    BOOL searching;
    NSTimer* m_timer;
    BOOL m_new_doc;
    BOOL m_links_enabled;
    BOOL m_annotation_editing_enabled;
    BOOL m_progressive_rendering_enabled;
    double m_progressive_rendering_interval;
    BOOL m_progressive_render_override;
    double m_screenScale;
    BOOL m_retinaEnabled;
    UIColor* pageColor;
    int m_tool_switches;
    BOOL m_no_core_scroll;
    PDFDoc* m_current_doc;
    UIColor* m_Last_highlight_colour;
    BOOL m_request_rending_upon_doc_unlock;
    TrnZoomLimitMode m_zoom_mode;
    double m_zoom_limit_ref_zoom;
    BOOL m_freeze_tile;
    BOOL m_request_pending;
    unsigned int m_memoryInUse;
    NSMutableArray* m_highlights;
    PDFPoint* pagePtA;
    PDFPoint* pagePtB;
    int pageNumber;
    double totalZoom;
    double totalXExtra;
    double totalYExtra;
    double minimumZoom, maximumZoom;
    double m_min_scaled_zoom, m_max_scaled_zoom;
    BOOL m_zoom_enabled;
    int gapYExtra;
    int gapXExtra;
    NSMutableDictionary* thumbnails;
    PDFDoc* m_default_annots;
    NSDictionary* AnnotTypeID;
    BOOL m_rightToLeftLanguage;
    Selection* m_selections;
    BOOL m_PreOpenUrlProgRender;
    BOOL m_OpenUrlExceptionOccured;
}

#pragma mark - Properties

/**
 * An object that conforms to the PDFViewCtrlDelegate protocol.
 *
 */
@property (nonatomic, assign) id<PDFViewCtrlDelegate> delegate;

/**
 * A UIView that conforms to the ToolDelegate protocol.
 *
 */
@property (nonatomic, retain) UIView<ToolDelegate>* tool;

/**
 * Enables or disables the ability for the user to scroll the content.
 *
 */
@property (nonatomic, assign) BOOL scrollEnabled;

/**
 * Enables or disables the ability for the user to pinch-zoom the control.
 *
 */
@property (nonatomic, assign) BOOL zoomEnabled;

/**
 * Enables or disables the document's use of a retina display. If it is disabled,
 * the document will display at a non-retina resolution. Default is enabled.
 *
 */
@property (nonatomic, assign) BOOL retinaEnabled;

#pragma mark - Document Loading and Closing

/**
 * Associates this PDFViewCtrl with a given PDF document.
 *
 * @param doc - A document to be displayed in the view.
 *
 * @note SetDoc acquires a write lock on the document, so the document
 * must be unlocked when this method is called or an exception will be
 * trown.
 *
 */
-(void)SetDoc:(PDFDoc*)doc;

/**
 * @return Currently associated document with this PDFViewCtrl.
 */
-(PDFDoc*)GetDoc;

/**
 * Closes the document currently opened in PDFViewCtrl.
 *
 * @note CloseDoc acquires a write lock on the document, so the document
 * must be unlocked when this method is called or an exception will be
 * trown.
 */
-(void)CloseDoc;

/**
 * Sets the PDF document from a URL. If the PDF is linearized, PDFViewCtrl will
 * display it incrementally while downloading it. If the PDF is not linearized,
 * it will display blank pages until the entire document is downloaded.
 *
 * @param url The URL of the document to open.
 *
 * @param password The password used to open the PDF document if it is password
 * protected.
 *
 * @param fullPath The path to a file that will be used to cache the downloaded file which
 * will be used to resume a download. If no cache file is specified, a file is created in
 * the temporary directory.
 *
 * @note Currently, only the HTTP protocol is supported.
 *
 * @note This method will acquire a write lock on the document that is displayed in the viewer
 * when this method is called, so it must be free of locks or an exception will be thrown.
 */
-(void)OpenUrl:(NSString*)url WithPDFPassword:(NSString*)password;
-(void)OpenUrl:(NSString*)url WithPDFPassword:(NSString*)password WithCacheFile:(NSString*)fullPath;

#pragma mark - Page Navigation

/**
 * @return the current page displayed in the view.
 */
-(int)GetCurrentPage;

/**
 * Sets the current page to the given page.
 *
 * @return true if successful, false otherwise.
 */
-(bool)SetCurrentPage:(int)page_num;

/**
 * Sets the current page to the first page in the document.
 *
 * @return true if successful, false otherwise.
 */
-(bool)GotoFirstPage;

/**
 * Sets the current page to the last page in the document.
 *
 * @return true if successful, false otherwise.
 */
-(bool)GotoLastPage;

/**
 * Sets the current page to the next page in the document.
 *
 * @return true if successful, false otherwise.
 */
-(bool)GotoNextPage;

/**
 * Sets the current page to the previous page in the document.
 *
 * @return true if successful, false otherwise.
 */
-(bool)GotoPreviousPage;

#pragma mark - Viewer scroll position and zoom level

/**
 * @return the current horizontal scroll position. The returned value is expressed in the
 * canvas coordinate system. The canvas coordinate system is defined by a bounding box that
 * surrounds all pages in the view.
 */
-(double)GetHScrollPos;

/**
 * @return the current vertical scroll position. The returned value is expressed in the
 * canvas coordinate system. The canvas coordinate system is defined by a bounding box that
 * surrounds all pages in the view.
 */
-(double)GetVScrollPos;

/**
 * Sets the horizontal scroll position.
 *
 * @param the new horizontal scroll position. The position should be a number in the range
 * between 0 and GetCanvasWidth(). The 'pos' parameter is expressed in the canvas coordinate system.
 * The canvas coordinate system is defined by a bounding box that surrounds all pages in the view.
 * If Animated is not specified, the default value is YES.
 */
-(void)SetHScrollPos: (double)pos;
-(void)SetHScrollPos: (double)pos Animated:(BOOL)animated;

/**
 * Sets the vertical scroll position.
 *
 * @param the new vertical scroll position. The position should be a number in the range
 * between 0 and GetCanvasheight().  The 'pos' parameter is expressed in the canvas coordinate system.
 * The canvas coordinate system is defined by a bounding box that surrounds all pages in the view.
 * If Animated is not specified, the default value is YES.
 */
-(void)SetVScrollPos: (double)pos;
-(void)SetVScrollPos: (double)pos Animated:(BOOL)animated;

/**
 * Returns the current zoom factor.
 *
 * @return current zoom (or scaling) component used to display the page content.
 */
-(double)GetZoom;

/**
 * Sets the zoom factor to a new value. The function zooms to a point at the
 * center of the rendering buffer.
 *
 * @param zoom - new scaling component used to display the page content.
 * @return true if successful, false otherwise.
 */
-(void)SetZoom:(double)zoom;

/**
 * Sets the zoom factor to a new value using the given pixel coordinate
 * (x,y) as a zoom center.
 *
 * The zoom point (x,y) is represented in the screen coordinate system, which
 * starts in the upper-left corner of the client window.
 *
 * @param x - the horizontal coordinate to zoom in.
 * @param y - the vertical coordinate to zoom in.
 * @param zoom - new scaling component used to display the page content.
 * @return true if successful, false otherwise.
 */
-(void)SetZoomX:(int)x Y:(int)y Zoom:(double)zoom;

/**
 * Sets the zoom factor to a new value using the given pixel coordinate
 * (x,y) to find an intersecting paragraph.
 * The width of the paragraph helps to determine the zoom value, center
 * of the paragraph is used as a zoom center.
 * Paragraph has to contain more than one line and be wider than 1/5th of a page width.
 * When called on a paragraph wider than current zoom level, or smart zoom cannot
 * find something to zoom on, the method returns false.
 * The zoom point (x,y) is represented in the screen space, which
 * starts in the upper-left corner of the client window.
 *
 * @param x - the horizontal coordinate to look for a text block.
 * @param y - the vertical coordinate to look for a text block.
 * @param animated - whether or not to animate the zooming
 * @return true if successful, false if no zooming was performed.
 */
-(BOOL)SmartZoomX:(double)in_x y:(double)in_y animated:(BOOL)animated;

/**
 * Changes the viewing area to fit a rectangle rect on page page_num.
 * Rectangle must be specified in page coordinates.
 * This will adjust current page and zoom appropriately.
 *
 * @return true if successful, false otherwise.
 */
-(BOOL)ShowRect: (int)page_num rect:  (PDFRect*)rect;

#pragma mark - Page View and Presentation Modes

/**
 * @return the current page viewing mode
 */
-(TrnPageViewMode)GetPageViewMode;

/**
 * Sets the page viewing mode
 *
 * @param mode - the new page viewing mode.
 * @default The default PageView mode is e_fit_width.
 */
-(void)SetPageViewMode:(TrnPageViewMode)mode;

/**
 * Sets the reference page view mode. In a non-continous page presentation
 * mode, the reference page view mode is used to determine the page view
 * mode upon a page change event. For example, if the reference page view
 * mode is set to e_fit_width, the new page coming in will
 * be displayed with width-fit mode.
 *
 * @param mode
 *            The reference page view mode to set. Valid values are
 *            e_trn_fit_page, e_trn_fit_width, and
 *            e_trn_fit_height.
 */
-(void)SetPageRefViewMode:(TrnPageViewMode)mode;

/**
 * Gets the reference page view mode. See more details about reference
 * page view mode in {@link #setPageRefViewMode(int)}.
 */
-(TrnPageViewMode) GetPageRefViewMode;

/**
 * @return the current page presentation mode.
 */
-(TrnPagePresentationMode)GetPagePresentationMode;

/**
 * Sets the current page presentation mode.
 *
 * @param mode - the new page presentation mode.
 * @default The default PagePresentationMode is e_single_continuous.
 */
-(void)SetPagePresentationMode:(TrnPagePresentationMode)mode;

#pragma mark - Viewer Options

/**
 * Enables or disables URL extraction.
 *
 * @param enabled if true URL extraction is enabled, if false URL extraction is
 * disabled.
 *
 * @default by default URL extraction is disabled
 *
 * @note If set to enabled when the document is already opened, it may not
 * find links on pages that were already rendered. It is suggested to
 * set this flag before opening the document.
 */
- (void)SetUrlExtraction: (BOOL)enabled;

/**
 * Enables or disables drawing of a thin border around each page.
 * @param border_visible - if true, the border will be visible.
 */
-(void)SetPageBorderVisibility: (BOOL)border_visible;

/**
 * Enables or disables the transparency grid (check board pattern) to reflect
 * page transparency.
 * @param trans_grid_visible - if true, the grid is turned on.
 */
-(void)SetPageTransparencyGrid: (BOOL)trans_grid_visible;

/**
 * Sets the default 'paper' color used to draw background of each page.
 * @param r, g, b - RGB color specifying the default page color.
 */
-(void)SetDefaultPageColor: (unsigned char)r g:  (unsigned char)g b:  (unsigned char)b;

/**
 * Sets the default background color used to paint the area surrounding each page.
 * @param r, g, b, a - RGBA color specifying the default background color.
 */
-(void)SetBackgroundColor: (unsigned char)r g:  (unsigned char)g b:  (unsigned char)b a:(unsigned char)a;

/**
 * Sets the horizontal alignment used for rendering pages within the view.
 * @param align an integer specifying the horizontal alignment. Depending
 * of whether align is positive, negative, or zero - pages will be right,
 * left or center aligned:
 *   align<0  -> pages are left aligned.
 *   align==0 -> pages are centered.
 *   align>0  -> pages are right aligned.
 */
-(void)SetHorizontalAlign: (int)align;

/**
 * Sets the vertical alignment used for rendering pages within the view.
 * @param align an integer specifying the vertical alignment. Depending
 * of whether align is positive, negative, or zero - pages will be bottom,
 * top or center aligned:
 *   align<0  -> pages are top aligned.
 *   align==0 -> pages are centered.
 *   align>0  -> pages are bottom aligned.
 */
-(void)SetVerticalAlign: (int)align;

/**
 * Sets the vertical and horizontal padding and column spacing between adjacent pages in the view.
 *
 *
 * @param horiz_col_space horizontal column spacing (represented in pixels) between
 * adjacent pages in the view. Default is 10.
 * @param vert_col_space vertical column spacing (represented in pixels) between adjacent
 * pages in the view. Default is 10.
 * @param horiz_pad horizontal padding (represented in pixels) on the left and right side
 * of the view. Default is 10.
 * @param vert_pad vertical padding (represented in pixels) on the top and bottom side
 * of the view. Default is 10.
 */
-(void)SetPageSpacing: (int)horiz_col_space vert_col_space:  (int)vert_col_space horiz_pad:  (int)horiz_pad vert_pad:  (int)vert_pad;

/**
 * Rotates all pages in the document 90 degrees clockwise.
 */
-(void)RotateClockwise;

/**
 * Rotates all pages in the document 90 degrees counter-clockwise.
 */
-(void)RotateCounterClockwise;

/**
 * @return  The current rotation of this PDFViewCtrl.
 */
-(Rotate)GetRotation;


#pragma mark - Rendering Options

/**
 * Sets whether the control will render progressively or will just
 * draw once the entire view has been rendered
 * @param progressive if true the view will be rendered progressively
 *
 * @note Progressive rendering is useful when a PDF page contain lots of elements
 * (e.g. many vector paths, text, or many little images). When progressive rendering
 * is enabled PDFNet will use painter algorithm to draw the page. This way user may
 * be able to see partially rendered page. If a page contains only a single large
 * image, there would be no visible benefit from progressive rendering.
 */
-(void)SetProgressiveRendering:(BOOL)progressive;

/**
 * Sets the interval upon which the device will refresh the display.
 * Note that on single core devices (iPad 1, iPhone 4 and earlier), updating the display will
 * slightly slow down the time to complete rendering.
 *
 * @param seconds - Number of seconds between refreshes.
 */
-(void)SetProgressiveRenderingInterval:(double)seconds;

/**
 * Enable or disable path hinting.
 *
 * @param enabled if YES path hinting is enabled. Path hinting is used to slightly
 * adjust paths in order to avoid or alleviate artifacts of hair line cracks between
 * certain graphical elements. This option is turned on by default.
 *
 */
-(void)SetPathHinting:(BOOL)enabled;

/**
 * Enable or disable anti-aliasing.
 *
 * Anti-Aliasing is a technique used to improve the visual
 * quality of images when displaying them on low resolution
 * devices (for example, low DPI computer monitors).
 *
 * @default Anti-aliasing is enabled by default.
 */
-(void)SetAntiAliasing:(bool)enabled;

/**
 * Set thin line adjustment parameters.
 *
 * @param pixel_grid_fit if true (horizontal/vertical) thin lines will be snapped to
 * integer pixel positions. This helps make thin lines look sharper and clearer. This
 * option is turned off by default.
 *
 * @param stroke_adjust if true auto stroke adjustment is enabled. Currently, this would
 * make lines with sub-pixel width to be one-pixel wide. This option is turned on by default.
 */
-(void)SetThinLineAdjustmentPixelGrid:(bool)pixel_grid StrokeAdjust:(bool)stroke_adjust;

/**
 * Enable or disable image smoothing.
 *
 * The rasterizer allows a trade-off between rendering quality and rendering speed.
 * This function can be used to indicate the preference between rendering speed and quality.
 *
 * @note image smoothing option has effect only if the source image has higher resolution
 * that the output resolution of the image on the rasterized page. PDFNet automatically
 * controls at what resolution/zoom factor, 'image smoothing' needs to take effect.
 *
 * @param smoothing_enabled True to enable image smoothing, false otherwise.
 * @default image smoothing is enabled.
 */
-(void)SetImageSmoothing:(bool)enabled;

/**
 * Sets the gamma factor used for anti-aliased rendering.
 *
 * @param exp is the exponent value of gamma function. Typical values
 * are in the range from 0.1 to 3.
 *
 * Gamma correction can be used to improve the quality of anti-aliased
 * image output and can (to some extent) decrease the appearance common
 * anti-aliasing artifacts (such as pixel width lines between polygons).
 *
 * @note Gamma correction is used only in the built-in rasterizer.
 */
-(void)SetGamma:(double)exp;


/**
 * Enable or disable annotation and forms rendering. By default, all annotations
 * and form fields are rendered.
 *
 * @param render_annots True to draw annotations, false otherwise.
 */
-(void)SetDrawAnnotations:(BOOL)render_annots;

/**
 * Enable or disable highlighting form fields. Default is disabled.
 *
 * @param highlight_fields YES to highlight, NO otherwise.
 */
-(void)SetHighlightFields:(BOOL)highlight_fields;

/**
 * Enable or disable support for overprint and overprint simulation.
 * Overprint is a device dependent feature and the results will vary depending on
 * the output color space and supported colorants (i.e. CMYK, CMYK+spot, RGB, etc).
 *
 * @default By default overprint is only enabled for PDF/X files.
 *
 * @param op e_op_on: always enabled; e_op_off: always disabled; e_op_pdfx_on: enabled for PDF/X files only.
 */
-(void)SetOverprint: (OverprintPreviewMode)op;

/**
 * Sets the Optional Content Group (OCG) context that should be used when
 * viewing the document. This function can be used to change the current
 * OCG context. Optional content (such as PDF layers) will be selectively
 * rendered based on the states of optional content groups in the given
 * context.
 *
 * @param ctx Optional Content Group (OCG) context, or NULL if the rasterizer
 * should render all content on the page.
 *
 * @note Unlike PDFDraw.SetOCGContext() this method copies the given context.
 * As a result, in order to modify the state of OCG groups in the current
 * context use GetOCGContext() to obtain the currently selected content
 * and then modify states.
 */
-(void)SetOCGContext: (Context*)ctx;

/**
 * @return the Optional Content Group (OCG) context associated with this
 * PDFViewCtrl, or NULL (i.e. context.IsValid()==false) if there is no OCG
 * context associated with the view. If an OCG context associated with the
 * view, optional content (such as PDF layers) will be selectively rendered
 * based on the states of optional content groups in the given context.
 */
-(Context*)GetOCGContext;

#pragma mark - Text Search

/**
 * Selects text by searching for a given string of text.
 *
 * @param search_str -
 * @param match_case -
 * @param match_whole_word -
 * @param search_up  -
 * @param reg_exp  - use regular expressions
 *
 * @note this function runs in asynchronous mode: it launches a search thread and returns immediately.
 * If a matched string is found, the corresponding text is highlighted; otherwise, a message box is
 * shown. Users can use SetCustomEventHandlers() to set a TextFindDoneHandler to customize a different
 * behavior.
 */
-(BOOL)FindText:(NSString*)searchString MatchCase:(BOOL)matchCase MatchWholeWord:(BOOL)matchWholeWord SearchUp:(BOOL)searchUp RegExp:(BOOL)regExp;

#pragma mark - Text Selection

/**
 * Sets the selection mode used for text highlighting.
 * @param tm the text selection mode.
 */
-(void)SetTextSelectionMode: (TextSelectionMode)tm;

/**
 * Places a rectangle over text that has been selected
 *
 * @param selection - A selection object.
 *
 * @param color - The color of the drawn rectangle. Set the alpha value to less than 1.0 to give transparency.
 */
-(void)highlightSelection:(Selection*)selection withColor:(UIColor*)color;

/**
 * Clears the rectangle drawn by highlightSelection:withColor:
 */
-(void)hideSelectedTextHighlights;

/**
 * @return return true if there is selection, false otherwise.
 */
-(BOOL)HasSelection;

/**
 * Remove any text selection.
 */
-(void)ClearSelection;

/**
 * @return Current text selection for a given page.
 * If there is only selection on one page, then page number
 * does not need to be provided.
 */
-(Selection*)GetSelection: (int)pagenum;

/**
 * @return the first page number that has text selection on it.
 * Useful when there are selections on multiple pages at the same time.
 */
-(int)GetSelectionBeginPage;

/**
 * @return the last page number that has text selection on it.
 * Useful when there are selections on multiple pages at the same time.
 */
-(int)GetSelectionEndPage;

/**
 * @return returns true if given page number has any text selection on it.
 * Useful when there are selections on multiple pages at the same time.
 */
-(BOOL)HasSelectionOnPage: (int)ipage;

/**
 * Selects text within the given region using the current text selection mode.
 *
 * @return true if some text was selected, false otherwise.
 * @param x1, y1, x2, y2 - two points (screen coordinates, origin located at the upper-left corner of this view)
 * defining the opposite corners of a selection rectangle.
 */
-(BOOL)SelectX1:(double)x1 Y1:(double)y1 X2:(double)x2 Y2:(double)y2;

/**
 * Selects text using structural mode.
 *
 * @return true if some texts were selected, false otherwise.
 * @param (x1, y1), page1 - the first selection point (in page coordinates space) on page page1
 * @param (x2, y2), page2 - the second selection point (in page coordinates space) on page page2
 */
-(BOOL)SelectX1:(double)x1 Y1:(double)y1 PageNumber1:(int)pageNumber1 X2:(double)x2 Y2:(double)y2 PageNumber2:(int)pageNumber2;

/**
 * Selects text within the given region using the current text selection mode.
 *
 * @return true if some text was selected, false otherwise.
 * @param x1, y1, x2, y2 - two points (screen coordinates, origin located at the upper-left corner of this view)
 * defining the opposite corners of a selection rectangle.
 */
-(BOOL)SelectWithTextSelect: (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;

/**
 * Selects texts using structural mode.
 *
 * @return true if some texts were selected, false otherwise.
 * @param (x1, y1), page1 - the first selection point (in page coordinates space) on page page1
 * @param (x2, y2), page2 - the second selection point (in page coordinates space) on page page2
 */
-(BOOL)SelectWithStructure: (double)x1 y1:  (double)y1 page1:  (int)page1 x2:  (double)x2 y2:  (double)y2 page2:  (int)page2;

/**
 * Selects texts identified by Highlights.
 *
 * @return true if some texts were selected, false otherwise.
 * @param highlights - an instance of Highlights class.
 */
-(BOOL)SelectWithHighlights: (Highlights*)highlights;

/**
 * Selects all text on the page.
 */
-(void)SelectAll;

#pragma mark - User Interaction Options

/** 
 * Enables or disables the user's ability to create and interact with annotations, 
 * except for the ability to follow links (that controlled with EnableLinkActivation).
 *
 * Default is enabled.
 *
 * @param enable - If annotation editing is to be enabled.
 *
 */
-(void)SetAnnotationEditingEnabled:(BOOL)enable;

/**
 * Gets whether annotation editing is enabled.
 * 
 * @return true if annotation editing is enabled.
 */
-(BOOL)AnnotationEditingEnabled;

/**
 * Enables or disables whether links are activated when the user clicks on them
 * @param enable if true enable link activation, otherwise disable it
 */
-(void)EnableLinkActivation:(BOOL)enable;

/**
 * Gets whether link activation is enabled.
 * 
 * @return true if link activation is enabled.
 */
-(BOOL)LinkActivationEnabled;

/**
 * Returns the annotation present at screen coordinates (x, y). If no annotation is present,
 * callling IsValid on the returned annotation will return false.
 * You must lock the doc when retrieving an annotation.
 *
 * @param x - Number of seconds between refreshes.
 * @param y - Number of seconds between refreshes.
 *
 * @return the annotation present at screen coordinates (x, y).
 */
-(Annot*)GetAnnotationAt: (int)x y:  (int)y;

#pragma mark - Gesture Recognizer Targets

// These methods are called in response to gesture recognizers and are
// included in the header file so that subclasses may extend or override the functionality.

/**
 * Called in response to a single tap gesture and is
 * included here so that subclasses may extend or override the functionality.
 *
 * @param gestureRecognizer - The gesture recognizer that trigger the callback.
 */
-(void)handleTap:(UITapGestureRecognizer *)gestureRecognizer;

/**
 * Called in response to a long press gesture and is
 * included here so that subclasses may extend or override the functionality.
 *
 * @param gestureRecognizer - The gesture recognizer that trigger the callback.
 */
-(void)handleLongPress:(UITapGestureRecognizer *)gestureRecognizer;


#pragma mark - Document Locking/Unlocking

// Write Locks

/**
 * Acquires a write lock for PDFDoc instance used by PDFViewCtrl.
 * Simultaneous write access to a PDFDoc instance is not allowed.
 * A write lock cannot be acquired if the thread already holds a read lock.
 * Attempting to do so will throw an exception.
 * 
 * @param cancelThreads - 
 *            If true, other threads accessing the document are terminated before
 *            trying to lock the document. This ensures a quick return from this
 *            function. Otherwise, this function can halt the UI and the app
 *            may be unresponsive before the other thread finishes. If
 *            the rendering thread is canceled, unlocking the document
 *            UnlockDoc will restart the rendering thread.
 */
// -(void)LockDoc:(BOOL)cancelRendering; // DEPRECATED
-(void)DocLock:(BOOL)cancelThreads;

/**
 * Tries to acquire a write lock on the PDFDoc instance used by PDFViewCtrl.
 * Returns true if it succeeds and false otherwise.
 *
 * @param milliseconds - time that the selector will block while trying to aquire 
 * the lock before returning.
 *
 * @return true if the lock was aquired, false otherwise. 
 */
// -(BOOL)TryLockDoc; // DEPRECATED
-(BOOL)DocTryLock:(int)milliseconds;

/**
 * Releases a write lock on the PDFDoc instance used by PDFViewCtrl and restarts the
 * rendering thread if it was canceled.
 */
// -(void) UnlockDoc; // DEPRECATED
-(void)DocUnlock;

// Read Locks

/**
 * Acquires a read lock for PDFDoc instance used by PDFViewCtrl.
 */
-(void)DocLockRead;

/**
 * Tries to acquire read lock on the PDFDoc instance used by PDFViewCtrl.
 * Returns true if it succeeds and false otherwise.
 *
 * @param milliseconds - time that the selector will block while trying to aquire
 * the lock before returning.
 *
 * @return true if the lock was aquired, false otherwise.
 */
-(BOOL)DocTryLockRead:(int)milliseconds;

/**
 * Releases a read lock on the PDFDoc instance used by PDFViewCtrl.
 */
-(void)DocUnlockRead;

/**
 * Sets the minimum and maximum zoom bounds of PDFViewCtrl.
 *
 * @param min - the minimum zoom bound
 *
 * @param max - the maximum zoom bound
 *
 * @param mode - defines how the zoom bounds are to be used
 *
 * @note if the zoom limits are relative, 1.0 is defined as the zoom level
 * where the document is displayed in page fit mode, where the entire page
 * is visible on screen.
 */
-(void)SetZoomMinimum:(double)min Maxiumum:(double)max Mode:(TrnZoomLimitMode)mode;


#pragma mark - Coordinate Coversion

/**
 * @return  the number of the page located under the given screen 
 * coordinate. The positive number indicates a valid page, whereas 
 * number less than 1 means that no page was found. 
 */
-(int)GetPageNumberFromScreenPt:(double)x y:(double)y;

/**
 * Converts a point expressed in screen coordinates to a point on canvas.
 */
-(PDFPoint*)ConvScreenPtToCanvasPt:(PDFPoint*)pt;

/**
 * Converts a point expressed in canvas coordinates to a point on screen.
 */
-(PDFPoint*)ConvCanvasPtToScreenPt:(PDFPoint*)pt;

/**
 * Converts a point expressed in canvas coordinates to a point on a given page.
 * 
 * @param page_num the page number for the page used as the origin of the destination 
 * coordinate system. Negative values are used to represent the current page.
 * Pages are indexed starting from one.
 */
-(PDFPoint*)ConvCanvasPtToPagePt:(PDFPoint*)pt page_num:(int)page_num;

/**
 * Converts a point from a coordinate system of a given page to a point on canvas.
 * 
 * @param page_num the page number for the page used as the origin of the destination 
 * coordinate system. Negative values are used to represent the current page.
 * Pages are indexed starting from one.
 */
-(PDFPoint*)ConvPagePtToCanvasPt:(PDFPoint*)pt page_num:(int)page_num;

/**
 * Converts a point expressed in screen coordinates to a point on a given page.
 * 
 * @param page_num the page number for the page used as the origin of the destination 
 * coordinate system. Negative values are used to represent the current page.
 * Pages are indexed starting from one.
 */
-(PDFPoint*)ConvScreenPtToPagePt:(PDFPoint*)pt page_num:(int)page_num;

/**
 * Converts a point from a coordinate system of a given page to a point on screen.
 * 
 * @param page_num the page number for the page used as the origin of the destination 
 * coordinate system. Negative values are used to represent the current page.
 * Pages are indexed starting from one.
 */
-(PDFPoint*)ConvPagePtToScreenPt:(PDFPoint*)pt page_num:(int)page_num;

/**
 * @return the device transformation matrix. The device transformation 
 * matrix maps the page coordinate system to screen (or device) coordinate 
 * system.
 * 
 * @param page_num same as for PDFViewCtrl.Conv???() methods.
 *
 * @note to obtain a transformation matrix that maps screen 
 * coordinates to page coordinates, you can invert the device matrix. 
 * For example: 
 * @code
 *   Common::Matrix2D scr2page(pdfviewctrl.GetDeviceTransform());
 *   scr2page.Inverse();
 * @endcode 
 */
-(Matrix2D*)GetDeviceTransform:(int)page_num;

#pragma mark - Viewer Dimensions

/**
 * Returns the current canvas width.
 */
-(double)GetCanvasWidth;

/**
 * Returns the current canvas height.
 */
-(double)GetCanvasHeight;

#pragma mark - Rendering Starting/Stopping

/**
 *
 * @param visible_region_only - Specifies if the method refers only to currently
 * visible content.
 *
 * @return true is the rendering thread finished rendering the view,
 * false if the rendering is still in progress.
 */
- (BOOL)IsFinishedRendering: (BOOL)visible_region_only;

/**
 * Cancels rendering in` progress. If PDFViewCtrl is not busy rendering the page,
 * the function has no side effects.
 */
-(void)CancelRendering;

/**
 * Redraws the contents of the buffer.
 */
-(void)Update;

/**
 * Redraws the area covered with a given annotation.
 * @param annot The annotation to update.
 * @param page_num The page number on which the annotation is located.
 */
-(void)UpdateWithAnnot: (Annot*)annot page_num: (int)page_num;

/**
 * Redraws the given area in the buffer.
 * @param update The rectangle to update expressed in screen coordinates.
 */
-(void)UpdateWithRect: (PDFRect*)update;


/**
 * Renders content that requires rendering. May be called to resume rendering after CancelRendering.
 */
-(void)RequestRendering;

#pragma mark - Memory control

/**
 * Set the suggested memory size of the rendered content.
 *
 * PDFViewCtrl keeps off-screen content in order to achieve better viewing
 * experience; however, this increases memory usage. By default, PDFViewCtrl
 * will use 80% of available memory to render on-screen and off-screen content.
 * The value set here will be overidden if PurgeCachedMemory is called.
 *
 * @param allowed_max the allowed heap memory usage in MB.
 *
 * @note <p>
 *       If you want to minimize memory usage at the cost of
 *       viewing experience quality, you can set size_in_mb to 0 and
 *       PDFViewCtrl will not keep any off-screen content. Also note that
 *       this function only controls the memory used to store rendered content
 *       not the entire memory footprint of the control.
 *       </p>
 */
-(void)SetContentBufferSize:(long)allowedMax;

/**
 * Removes all non-visible portions of document to reduce memory consumption. This will
 * reset the value set via SetContentBufferSize back to the default of 80% of available
 * memory.
 *
 * Suggested use is in response to a low memory warning.
 * May slightly slow down the time to complete rendering.
 *
 */
-(void)PurgeCachedMemory;

/**
 * Enables of disables caching of images, fonts, and other resources. Disabling caching
 * can lower memory requirements at the expense of rendering speed.
 *
 * @param enabled if true caching is enabled, if false caching is disabled.
 * @default by default caching is enabled
 */
-(void)SetCaching: (BOOL)enabled;

#pragma mark - Thumbnails

/**
 * Enables or disables the use of thumbnails which are displayed when rendered
 * content is not yet available.
 *
 * <p>
 * Thumbnail view is used before a PDF page is fully rendered. If use_embedded is
 * enabled, thumbnails that are embedded in a PDF document will be used. If
 * generate_at_runtime is enabled, thumbnails will be generated at runtime. If both
 * use_embedded and generate_at_runtime are enabled, thumbnails will only be
 * generated if embedded thumbnails are not present.
 * </p>
 *
 * <p>
 * If runtime thumb view generation is enabled, the thumbnail maximum side
 * length will be used as a reference to calculate the thumbnail resolution.
 * </p>
 *
 * @param use_embedded
 *            If true, embedded thumbnails will be used; otherwise, they are ignored
 * @param generate_at_runtime
 *            If true, runtime thumbnail view generation is enabled
 * @param thumb_max_side_length
 *            If value is higher than zero, it will be used as a reference
 *            to calculate the thumbnail resolution. Pass zero to use
 *            the default internal value.
 */
- (void)SetupThumbnails: (BOOL)use_embedded generate_at_runtime:  (BOOL)generate_at_runtime use_persistent_cache:  (BOOL)use_persistent_cache thumb_max_side_length:  (int)thumb_max_side_length cache_directory_path:  (NSString*)cache_directory_path cache_data_file_size:  (int)cache_data_file_size;


#pragma mark - Miscellaneous

/**
 * @return the total number of pages in the document.
 */
-(int)GetPageCount;

/**
 * Updates the page layout withing the view. This function must be called  
 * after document page sequence is modified (such as when a page is being 
 * added to or removed from a document) or after changes to page dimensions
 * (e.g. after a page is rotated or resized).
 */
-(void)UpdatePageLayout;

/**
 * Used to add extra vertical scroll space to the PDF scroll view (inner scroll view)
 * when the keyboard would otherwise block the bottom of the document when editing
 * interactive forms.
 */
-(void)setExtraVerticalContent:(int)points;

/**
 * Post a message to cause onCustomEvent:userData to be called in the
 * next main message loop. This is useful if a Tool needs to be called by
 * PDFViewCtrl in the main message loop without a touch event being
 * triggered.
 *
 * @param userData An object that can be passed back in the onCustomEvent:(id)userData function.
 */
-(void)postCustomEvent:(id)userData;

/**
 * Requests action object to be executed by PDFViewCtrl. Action must belong to the document
 * currently displayed in PDFViewCtrl.
 * @param action object that is to be executed.
 */
-(void)ExecuteAction: (Action*)action;

@end

#pragma mark - PDFViewCtrlDelegate Protocol

/**
 * The methods declared by the PDFViewCtrlDelegate protocol allow the adopting delegate to respond to messages from
 * the PDFViewCtrl class.
 *
 */
@protocol PDFViewCtrlDelegate<NSObject>

@optional

/** Tells the delegate that the current page number changes.
 *
 * @param oldPageNumber The previous page number.
 *
 * @param newPageNumber The new page number.
 *
 */
- (void)pageNumberChangedFrom:(int)oldPageNumber To:(int)newPageNumber;

/**
 * Tells the delegate that PDFViewCtrl has opened a new document via its selector setDoc.
 *
 * @param doc The new document displayed by the PDFViewCtrl.
 *
 */
- (void)onSetDoc:(PDFDoc*)doc;

/**
 * Tells the delegate that text search has commenced.
 *
 */
- (void)textSearchStart;

/** 
 * Tells the delegate that a text search result has been found. The selection object
 * can be passed to PDFViewCtrl's highlightSelectedTextWithColor: to easily
 * highlight the text.
 *
 * @param selection An Selection object representing the location of the found text.
 *
 */
- (void)textSearchResult:(Selection*) selection;

/** 
 * Tells the delegate that the tool has changed.
 *
 * @param pdfViewCtrl The control that had the tool change.
 *
 */
- (void)toolChanged:(PDFViewCtrl*)pdfViewCtrl;

/**
 * Tells the delegate that a download event has occured. (Occurs when downloading a document with OpenUrl:)
 *
 * @param type The type of the event.
 *
 * @param pageNumber The number of the page that the event is for.
 *
 */
- (void)downloadEventType:(DownloadedType)type pageNumber:(int)pageNum;

/** 
 * Tells the delegate there was a download even error. (Occurs when downloading a document with OpenUrl:)
 *
 * @param exception The type and reason for the error.
 *
 */
- (void)downloadError:(NSException*)exception;

/**
 * Tells the delegate that `postCustomEvent` has been executed on the main loop.
 *
 */
- (void)customEvent:(id)userData;

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

/**
 * Tells the delegate when the user taps on the scrollview.
 *
 * @param gestureRecognizer The gesture recognizer that detected the tap.
 *
 */
- (void)pdfScrollViewTap:(UITapGestureRecognizer *)gestureRecognizer;

/**
 * Tells the delegate when the user double taps on the scrollview.
 *
 * @param gestureRecognizer The gesture recognizer that detected the taps.
 *
 */
- (void)pdfScrollViewDoubleTap:(UITapGestureRecognizer*)gestureRecognizer;

/**
 * Tells the delegate when the user long presses on the scrollview.
 *
 * @param gestureRecognizer The gesture recognizer that deteted the longpress 
 *
 */
- (void)pdfScrollViewLongPress:(UITapGestureRecognizer *)gestureRecognizer;

// Outer scroll view delegates - holds PDF scroll view when in single page mode. //

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


@end

#pragma mark - ToolDelegate Protocol

/**
 * The methods declared by the ToolDelegate protocol allow the adopting delegate to be used as a "Tool", in which
 * specific responses to user input can be defined. For example, the FreeHand tool will use the events to allow 
 * the user to create an Ink annotation on the PDF.
 *
 * The trial version of PDFNet for iOS comes with libTools.a, a precompiled set of Tool classes that implement features
 * such as text selection, hyperlink following and annotation creation and manipulation. Licensed users are provided 
 * with the source code for libTools.a, providing a starting point for customizing specific behaviour and as a rich
 * set of sample code.
 *
 */
@protocol ToolDelegate<NSObject>

@required

/**
 * Returns a newly initialized tool with the required pointer to the PDFViewCtrl on which it will operate.
 *
 * @param in_pdfViewCtrl a pointer to the PDFViewCtrl that the tool will operate.
 *
 * @return A newly initialized `tool` object.
 *
 */
- (id)initWithPDFViewCtrl:(PDFViewCtrl*)in_pdfViewCtrl;

/**
 * Returns the next tool to use if this tool did not completely handle an event.
 *
 * Tools receive events, listed as the optional selectors in this protocol, from a PDFViewCtrl. If a tool does not
 * finish handling an event (indicated by returning `NO` from one of the selectors that return a `BOOL`), then
 * getNextTool is used to instantiate a new tool that will continuning handling the event.
 *
 * @return a newly instantiated UIView that conforms to the ToolDelegate protocol.
 */
- (UIView<ToolDelegate>*)getNewTool;

@optional

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
 * Tells the delegate that PDFViewCtrl has opened a new document via its selector setDoc.
 *
 */
- (void)onSetDoc;

@end



