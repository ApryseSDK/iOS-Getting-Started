/*! \file PDFNetOBJC.h
\brief
*/
#ifndef PDFNetOBJC_H
#define PDFNetOBJC_H

#import "Private.h"

#import <Foundation/Foundation.h>

@class PDFDoc;
@class PrinterMode;
@class DictIterator;
@class Annot;
@class TRNField;
@class SElement;
@class SDFDoc;
@class Contect;
@class PDFRect;
@class Context;
@class ResultCodeInfo;
@class Obj;
@class Redaction;
@class QuadPoint;
@class Page;
@class PatternColor;
@class Font;
@class SecurityHandler;
@class SignatureHandler;
typedef size_t SignatureHandlerId;

/**
* Provides the fields that represent reference points in streams for seeking.
*/
typedef enum ReferencePos
{
e_begin = SEEK_SET,
e_end   = SEEK_END,
e_cur   = SEEK_CUR
}ReferencePos;


typedef enum OpenMode
{
e_read_mode,   ///< Opens file for reading. An exception is thrown if the file doesn't exist.
e_write_mode,  ///< Opens an empty file for writing. If the given file exists, its contents are destroyed.
e_append_mode, ///< Opens for reading and appending. Creates the file first if it doesn't exist.
}OpenMode;

typedef enum FlattenThresholdFlag {
/** Render (flatten) any text that is clipped or occluded. */
e_very_strict,
/** Render text that are marginally clipped or occluded. */
e_strict,
/** Render text that are somewhat clipped or occluded. */
e_default,
/** Only render text that are seriously clipped or occluded. */
e_keep_most,
/** Only render text that are completely occluded, or used as a clipping path. */
e_keep_all
}FlattenThresholdFlag;


typedef enum FlattenFlag {
/**
* Disable flattening and convert all content as is.
*/
e_flatten_off,
/**
* Feature reduce PDF to a simple two layer representation consisting
* of a single background RGB image and a simple top text layer.
*/
e_flatten_simple,
/**
* Feature reduce PDF while trying to preserve some
* complex PDF features (such as vector figures, transparency, shadings,
* blend modes, Type3 fonts etc.) for pages that are already fast to render.
* This option can also result in smaller & faster files compared to e_flatten_simple,
* but the pages may have more complex structure.
*/
e_flatten_fast
}FlattenFlag;


typedef enum AnnotationOutputFlag {
e_internal_xfdf,				// include the annotation file in the XOD output. This is the default option
e_external_xfdf,				// output the annotation file externally to the same output path with extension .xfdf.
// This is not available when using streaming conversion
e_flatten                      // flatten all annotations that are not link annotations
}AnnotationOutputFlag;

typedef enum ProxyType {  e_p_default,
e_p_none,
e_http,
e_socks5}ProxyType;

/**
* How to handle objects that failed to load?
*
* @param type - If e_abort then conversion process is aborted, if
* e_skip then the converter will not add this web page to the PDF
* output, and if e_skip then the converter will try to add this
* web page to the PDF output.
*/
typedef enum ErrorHandling {
e_abort,	// Abort the conversion process.
e_skip,		// Do not add the object to the final output
e_ignore	// Try to add the object to the final output.
}ErrorHandling;

typedef enum CompressionMode
{
e_jbig2,
e_flate,
e_none
}CompressionMode;



typedef enum DownsampleMode
{
e_off,
e_default
}DownsampleMode;

typedef enum MonoCompressionMode {  e_mn_jbig2,
e_mn_flate,
e_mn_none}MonoCompressionMode;

typedef enum MonoDownsampleMode {  e_mn_off,
e_mn_default}MonoDownsampleMode;

typedef enum BdStyle {  e_solid,
e_dashed,
e_beveled,
e_inset,
e_underline}BdStyle;


typedef enum SaveOptions
{
e_incremental   = 0x01,     // Save the document using incremental mode.
e_remove_unused = 0x02,     // Remove unused objects. Requires full save.
e_hex_strings   = 0x04,     // Save all string in hexadecimal format.
e_omit_xref     = 0x08,     // Do not save cross-reference table
e_linearized    = 0x10,     // Save the document in linearized (fast web-view) format. Requires full save.
e_compatibility = 0x20      // Save the document in a manner that maximizes compatibility with older PDF consumers (e.g. the file will not use compressed object and xref streams).
}SaveOptions;

/**
* The object type.
*/
typedef enum ObjType
{
e_null,
e_bool,
e_number,
e_name,
e_string,
e_dict,
e_array,
e_stream
}ObjType;


typedef enum Permission
{
e_owner = 1,		///< the user has 'owner' rights (e.g. rights to change the document's security settings).
e_doc_open,         ///< open and decrypt the document.
e_doc_modify,       ///< edit the document more than adding or modifying text notes.
e_print,            ///< print the document.
e_print_high,       ///< high resolution print.
e_extract_content,  ///< enable content extraction
e_mod_annot,        ///< allow modifications to annotations
e_fill_forms,       ///< allow changes to fill in forms
e_access_support,   ///< content access for the visually impaired.
e_assemble_doc      ///< allow document assembly
}Permission;

/**
* The algorithm to be used in encrypting and decrypting the document.
*/
typedef enum AlgorithmType {
e_RC4_40 = 1,      ///< 40-bit RC4 algorithm.
e_RC4_128,         ///< 128-bit RC4 algorithm.
e_AES              ///< Use Crypt filters with 128-bit AES (Advanced Encryption Standard) algorithm.
}AlgorithmType;


typedef enum OverloadedFunction {
has_CloneProc         = 0x01,
has_AuthProc          = 0x02,
has_AuthFailedProc    = 0x04,
has_GetAuthDataProc   = 0x08,
has_EditSecurDataProc = 0x10,
has_FillEncDictProc   = 0x20
}OverloadedFunction;


typedef enum FunctionType
{
e_sampled     = 0, // uses a table of sample values to define the function.
e_exponential = 2, // defines a set of coefficients for an exponential function.
e_stitching   = 3, // a combination of other functions, partitioned across a domain.
e_postscript  = 4  // A PostScript calculator function.
}FunctionType;


typedef enum ColorSpaceType
{
e_device_gray,
e_device_rgb,
e_device_cmyk,
e_cal_gray,
e_cal_rgb,
e_lab,
e_icc,
e_indexed,
e_pattern,
e_separation,
e_device_n,
e_c_null
}ColorSpaceType;

/**
* PDF page can define as many as five separate boundaries to control various aspects of the
* imaging process (for more details please refer to Section 10.10.1 'Page Boundaries' in PDF
* Reference Manual):
*
* - The media box defines the boundaries of the physical medium on which the page is to be
* printed. It may include any extended area surrounding the finished page for bleed, printing
* marks, or other such purposes. It may also include areas close to the edges of the medium
* that cannot be marked because of physical limitations of the output device. Content falling
* outside this boundary can safely be discarded without affecting the meaning of the PDF file.
*
* - The crop box defines the region to which the contents of the page are to be clipped (cropped)
* when displayed or printed. Unlike the other boxes, the crop box has no defined meaning in
* terms of physical page geometry or intended use; it merely imposes clipping on the page
* contents. The default value is the page's media box.
*
* - The bleed box defines the region to which the contents of the page should be clipped when
* output in a production environment. This may include any extra bleed area needed to
* accommodate the physical limitations of cutting, folding, and trimming equipment.
* The default value is the page's crop box.
*
* - The trim box defines the intended dimensions of the finished page after trimming. It may
* be smaller than the media box to allow for production related content, such as printing
* instructions, cut marks, or color bars. The default value is the page's crop box.
*
* - The art box defines the extent of the page's meaningful content (including potential
* white space) as intended by the page's creator. The default value is the page's crop box.
*/
typedef enum Box
{
e_media,
e_crop,
e_bleed,
e_trim,
e_art
}Box;

/**
* Specifies page rotation, in degrees.
*/
typedef enum Rotate
{
e_0,
e_90,
e_180,
e_270
}Rotate;

typedef enum GStateAttribute
{
e_transform = 0,            // General graphics state attributes
e_rendering_intent,

e_stroke_cs,
e_stroke_color,
e_fill_cs,
e_fill_color,

e_line_width,                // Path attributes
e_line_cap,
e_line_join,
e_flatness,
e_miter_limit,
e_dash_pattern,

e_char_spacing,              // Text attributes
e_word_spacing,
e_horizontal_scale,
e_leading,
e_font,
e_font_size,
e_text_render_mode,
e_text_rise,
e_text_knockout,

// Adjusts the text position by a given amount. The attribute can be
// accessed through Element interface
e_text_pos_offset,

e_blend_mode,                // Extended graphics state attributes
e_opacity_fill,
e_opacity_stroke,
e_alpha_is_shape,
e_soft_mask,
e_smoothnes,
e_auto_stoke_adjust,
e_stroke_overprint,
e_fill_overprint,
e_overprint_mode,
e_transfer_funct,
e_BG_funct,
e_UCR_funct,
e_halftone,

// null attribute
e_g_null
}GStateAttribute;



typedef enum LineCap
{
e_butt_cap = 0,     // The stroke is squared off at the endpoint of the path.
e_round_cap,        // A semicircular arc with a diameter equal to the line width.
e_square_cap        // squared off stroke continues beyond the endpoint of the path.
}LineCap;



typedef enum LineJoin
{
e_miter_join = 0,   // The two segments are extended until they meet
e_round_join,       // A circle with a diameter equal to the line width
e_bevel_join        // The two segments are finished with butt caps
}LineJoin;


typedef enum TextRenderingMode
{
e_fill_text = 0,            // Fill text.
e_stroke_text,              // Stroke text.
e_fill_stroke_text,         // Fill, then stroke text.
e_invisible_text,           // Neither fill nor stroke text (invisible).
e_fill_clip_text,           // Fill text and add to path for clipping (see above).
e_stroke_clip_text,         // Stroke text and add to path for clipping.
e_fill_stroke_clip_text,    // Fill, then stroke text and add to path for clipping.
e_clip_text                 // Add text to path for clipping.
}TextRenderingMode;


typedef enum RenderingIntent
{
e_absolute_colorimetric,
e_relative_colorimetric,
e_saturation,
e_perceptual
}RenderingIntent;

typedef enum BlendMode
{
e_bl_compatible = 0,
e_bl_normal,
e_bl_multiply,
e_bl_screen,
e_bl_difference,
e_bl_darken,
e_bl_lighten,
e_bl_color_dodge,
e_bl_color_burn,
e_bl_exclusion,
e_bl_hard_light,
e_bl_overlay,
e_bl_soft_light,
e_bl_luminosity,
e_bl_hue,
e_bl_saturation,
e_bl_color
}BlendMode;

typedef enum FieldType {  e_button,
e_check,
e_radio,
e_text,
e_choice,
e_signature,
e_f_null}FieldType;

typedef enum FieldFlag {  e_read_only,
e_required,
e_no_export,
e_pushbutton_flag,
e_radio_flag,
e_toggle_to_off,
e_radios_in_unison,
e_multiline,
e_password,
e_file_select,
e_no_spellcheck,
e_no_scroll,
e_comb,
e_rich_text,
e_combo,
e_edit,
e_sort,
e_multiselect,
e_commit_on_sel_change}FieldFlag;

/**
* Enumeration specifying the form of quadding (justification) to be used
* in displaying the text fields.
*/
typedef enum TextJustification
{
e_left_justified,
e_centered,
e_right_justified
}TextJustification;

/**
* PDF supports the standard annotation types listed in the following enumeration
* (plug-in extensions may add new annotation types):
*/
typedef enum AnnotType
{
e_Text,           ///< Text annotation
e_Link,           ///< Link annotation
e_FreeText,       ///< Free text annotation
e_Line,           ///< Line annotation
e_Square,         ///< Square annotation
e_Circle,         ///< Circle annotation
e_Polygon,        ///< Polygon annotation
e_Polyline,       ///< Polyline annotation
e_Highlight,      ///< Highlight annotation
e_Underline,      ///< Underline annotation
e_Squiggly,       ///< Squiggly-underline annotation
e_StrikeOut,      ///< Strikeout annotation
e_Stamp,          ///< Rubber stamp annotation
e_Caret,          ///< Caret annotation
e_Ink,            ///< Ink annotation
e_Popup,          ///< Pop-up annotation
e_FileAttachment, ///< File attachment annotation
e_Sound,          ///< Sound annotation
e_Movie,          ///< Movie annotation
e_Widget,         ///< Widget annotation
e_Screen,         ///< Screen annotation
e_PrinterMark,    ///< Printer's mark annotation
e_TrapNet,        ///< Trap network annotation
e_Watermark,      ///< Watermark annotation
e_3D,             ///< 3D annotation
e_Redact,         ///< Redact annotation
e_Projection,	  ///< Projection annotation, Adobe supplement to ISO 32000
e_RichMedia,      ///< Rich Media annotation, Adobe supplement to ISO 32000
e_Unknown         ///< Any other annotation type, not listed in PDF spec and unrecognized by PDFTron software
}AnnotType;

/**
* AnnotFlags specifying various characteristics of the annotation.
*
* - If e_invisible is set, do not display the annotation if it does not belong to
* one of the standard annotation types and no annotation handler is available. If clear,
* display such an unknown annotation using an appearance stream specified by its appearance
* dictionary, if any.
*
* - If e_hidden is set, do not display or print the annotation or allow it to interact
* with the user, regardless of its annotation type or whether an annotation handler
* is available.
*
* - If e_print_annot is set, print the annotation when the page is printed. If clear, never
* print the annotation, regardless of whether it is displayed on the screen. This can be
* useful, for example, for annotations representing interactive pushbuttons, which would
* serve no meaningful purpose on the printed page.
*
* - If e_no_zoom is set, do not scale the annotation's appearance to match the
* magnification of the page.
*
* - If e_no_rotate is set, do not rotate the annotation's appearance to match the rotation
* of the page.
*
* - If e_no_view is set, do not display the annotation on the screen or allow it to
* interact with the user. The annotation may be printed (depending on the setting of the
* Print flag) but should be considered hidden for purposes of on-screen display and user
* interaction.
*
* - If e_annot_read_only is set, do not allow the annotation to interact with the user. The
* annotation may be displayed or printed (depending on the settings of the NoView and Print
* flags) but should not respond to mouse clicks or change its appearance in response to
* mouse motions.
*
* - If e_locked is set, do not allow the annotation to be deleted or its properties
* (including position and size) to be modified by the user. However, this flag does not
* restrict changes to the annotation's contents, such as the value of a form field.
*
* - If e_toggle_no_view is set, invert the interpretation of the NoView flag for certain
* events. A typical use is to have an annotation that appears only when a mouse cursor is
* held over it.
*
* - If e_locked_contents is set, do not allow the contents of the annotation to be modified
* by the user. This flag does not restrict deletion of the annotation or changes to other
* annotation properties, such as position and size.
*/
typedef enum AnnotFlag
{
e_invisible,         // PDF 1.2
e_hidden,            // PDF 1.2
e_print_annot,             // PDF 1.2
e_no_zoom,           // PDF 1.3
e_no_rotate,         // PDF 1.3
e_no_view,           // PDF 1.3
e_annot_read_only,         // PDF 1.3
e_locked,            // PDF 1.4
e_toggle_no_view,     // PDF 1.5
e_locked_contents    // PDF 1.7
}AnnotFlag;

/**
* An annotation can define as many as three separate appearances:
*
*  - The normal appearance is used when the annotation is not interacting
* with the user. This appearance is also used for printing the annotation.
*
*  - The rollover appearance is used when the user moves the cursor into the
*    annotation's active area without pressing the mouse button.
*
*  - The down appearance is used when the mouse button is pressed or held down
*    within the annotation's active area.
*/
typedef enum AnnotationState
{
e_normal,
e_rollover,
e_down
}AnnotationState;

/**
* Border Effect Style
*/
typedef enum BorderEffect
{
e_None,   ///< No effect.
e_Cloudy  ///< Use "cloudy" border.
}BorderEffect;

/**
* FileIcon style
*/
typedef enum FileIcon
{
e_Graph,      ///< The icon has graph appearance
e_PushPin,    ///<The icon has a push pin appearance.
e_Paperclip,  ///<The icon has a paper clip appearance
e_Tag,        ///< The icon has tag appearance
e_fi_Unknown     ///< The icon has unrecognized appearance type
}FileIcon;

/**
* View Destination Fit Types:
*
* XYZ - Destination specified as upper-left corner point and a zoom factor.
* Fit - Fits the page into the window
* FitH - Fits the widths of the page into the window
* FitV - Fits the height of the page into a window.
* FitR - Fits the rectangle specified by its upper-left and lower-right corner points into the window.
* FitB - Fits the rectangle containing all visible elements on the page into the window.
* FitBH - Fits the width of the bounding box into the window.
* FitBV - Fits the height of the bounding box into the window.
*/
typedef enum FitType
{
e_XYZ,
e_Fit,
e_FitH,
e_FitV,
e_FitR,
e_FitB,
e_FitBH,
e_FitBV
}FitType;

/**
* PDF supports the standard action types listed in the following table.
* Plug-in extensions may add new action types.
*/
typedef enum ActionType
{
e_GoTo,         ///< Go to a destination in the current document.
e_GoToR,        ///< ('Go-to remote') Go to a destination in another document.
e_GoToE,        ///< ('Go-to embedded'; PDF 1.6) Go to a destination in an embedded file.
e_Launch,       ///< Launch an application, usually to open a file.
e_Thread,       ///< Begin reading an article thread.
e_URI,          ///< Resolve a uniform resource identifier.
e_a_sound,        ///< Play a sound.
e_a_Movie,        ///< Play a movie.
e_Hide,         ///< Set an annotations Hidden flag.
e_Named,        ///< Execute an action predefined by the viewer application.
e_SubmitForm,   ///< Send data to a uniform resource locator.
e_ResetForm,    ///< Set fields to their default values.
e_ImportData,   ///< Import field values from a file.
e_JavaScript,   ///< Execute a JavaScript script.
e_SetOCGState,  ///< (PDF 1.5) Set the states of optional content groups.
e_Rendition,    ///< (PDF 1.5) Controls the playing of multimedia content.
e_Trans,        ///< Updates the display of a document, using a transition dictionary.
e_GoTo3DView,   ///< (PDF 1.6) Set the current view of a 3D annotation
e_RichMediaExecute, ///< Adobe supplement to ISO 32000; specifies a command to be sent to rich media annotation's handler
e_a_Unknown       ///< Unknown Action type
}ActionType;

/**
* Flags used by submit form actions. Exclude flag is also used by reset form action.
* No other action types use flags in the current version of PDF standard (ISO 2300).
*
*/
typedef enum FormActionFlag
{
e_exclude = 0,
e_include_no_value_fields  = 1,
e_export_format = 2,			// submit in HTML format if set, FDF format if clear
e_get_method = 3,
e_submit_coordinates = 4,
e_xfdf = 5,
e_include_append_saves = 6,
e_include_annotations = 7,
e_submit_pdf = 8,
e_canonical_format = 9,
e_excl_non_user_annots = 10,
e_excl_F_key = 11,
// bit 12 is unused by PDF standard
e_embed_form = 13
}FormActionFlag;

/**
* For each line, one can choose a separate style for the start and the end of the line.
* The styles are defined by the "EndingStyle" enumeration.
*/
typedef enum EndingStyle
{
e_l_Square,	///< A square filled with the annotations interior color, if any
e_l_Circle,	///< A circle filled with the annotations interior color, if any
e_Diamond,	///< A diamond shape filled with the annotations interior color, if any
e_OpenArrow,	///< Two short lines meeting in an acute angle to form an open arrowhead
e_ClosedArrow,	///< Two short lines meeting in an acute angle as in the OpenArrow style and connected by a third line to form a triangular closed arrowhead filled with the annotations interior color, if any
e_Butt,	///< A short line at the endpoint perpendicular to the line itself
e_ROpenArrow,  ///< Two short lines in the reverse direction from OpenArrow
e_RClosedArrow, ///< A triangular closed arrowhead in the reverse direction from ClosedArrow
e_Slash,	///< A short line at the endpoint approximately 30 degrees clockwise from perpendicular to the line itself
e_l_None,	///< No special line ending
e_l_Unknown	///< Non-standard or invalid ending
}EndingStyle;

/**
* This enum represents the intent of the LineAnnot annotation.
* For each line, one can specify the purpose of the line by choosing its intent
* defined by the "LineIntentType" enum.
*/
typedef enum LineIntentType
{
e_LineArrow,  ///< LineAnnot is an arrow
e_LineDimension, ///< LineAnnot is a dimension
e_l_null
}LineIntentType;

/**
* Enumeration type describing the annotations caption positioning.
* Valid values are e_Inline, meaning the caption shall be centered inside the line,
* and e_Top, meaning the caption shall be on top of the line.
*/
typedef enum CapPos
{
e_Inline, ///< the caption shall be centered inside the line
e_Top ///< the caption shall be on top of the line
}CapPos;

/**
* This enum defines the intention of the FreeText annotation
*/
typedef enum IntentName
{
e_f_FreeText,				///<The annotation intended to function as a plain FreeText annotation.
e_f_FreeTextCallout,		///<The annotation is intended to function as a callout.
e_f_FreeTextTypeWriter,	///<The annotation is intended to function as a click-to-type or typewriter object and no callout line is drawn.
e_f_Unknown				///<User defined or Invalid.
}IntentName;

/**
* This enum specifies the highlighting mode of the Link Annotation.
* The annotations highlighting mode is the visual effect that shall be used when
* the mouse button is pressed or held down inside its active area, possible values as
* follows:
*
* e_l_none - No highlighting.
* e_invert - Invert the contents of the annotation rectangle.
* e_outline - Invert the annotation's border.
* e_push - Display the annotation as if it were being pushed below the surface of the page.
*/
typedef enum LinkHighlightingMode
{
e_l_none,
e_invert,
e_outline,
e_push
}LinkHighlightingMode;

/**
* This enum specifies the intention of the PolyLine annotation, it used
* for the purposes of generating the appearance of the annotation.
*/
typedef enum PolyLineIntentType
{
e_PolygonCloud,  ///< The annotation is intended to function as a cloud object.
e_PolyLineDimension, ///< The polyline annotation is intended to function as a dimension. (PDF 1.7)
e_PolygonDimension, ///< The polygon annotation is intended to function as a dimension. (PDF 1.7)
e_p_Unknown           ///< Non-standard intent type
}PolyLineIntentType;

/**
* This enum represents the justification format of the RedactionAnnot annotation's overlay text.
*
*/
typedef enum QuadForm
{
e_LeftJustified,  ///< Overlay text is left justified
e_Centered,       ///< Overlay text is centered
e_RightJustified, ///< Overlay text is right justified
e_r_None            ///< No justification to the overlay text.
}QuadForm;

/**
* This enum represents the RubberStampIcon type of the RubberStamp annotation
*/
typedef enum RubberStampIcon
{
e_Approved,				///<a stamp with the text "Approved"
e_Experimental,			///<a stamp with the text "Experimental"
e_NotApproved,			///<a stamp with the text "Not Approved"
e_AsIs,					///<a stamp with the text "As Is"
e_Expired,				///<a stamp with the text "Expired"
e_NotForPublicRelease,	///<a stamp with the text "Not For Public Release"
e_Confidential,			///<a stamp with the text "Confidential"
e_Final,				///<a stamp with the text "Final"
e_Sold,					///<a stamp with the text "Sold"
e_Departmental,			///<a stamp with the text "Departmental"
e_ForComment,			///<a stamp with the text "For Comment"
e_TopSecret,			///<a stamp with the text "Top Secret"
e_ForPublicRelease,		///<a stamp with the text "For Public Release"
e_Draft,				///<a stamp with the text "Draft"
e_r_Unknown				///< Non-standard or user defined stamp.
}RubberStampIcon;

/**
* An enumeration indicating where to position the text of the annotations
* caption relative to its icon.
*
* e_NoIcon - No icon; caption only
* e_NoCaption - No caption; icon only
* e_CBelowI - Caption below the icon
* e_CAboveI - Caption above the icon
* e_CRightILeft - Caption to the right of the icon
* e_CLeftIRight - Caption to the left of the icon
* e_COverlayI - Caption overlaid directly on the icon
* Default value: e_NoIcon.
*/
typedef enum ScreenIconCaptionRelation
{
e_NoIcon,
e_NoCaption,
e_CBelowI,
e_CAboveI,
e_CRightILeft,
e_CLeftIRight,
e_COverlayI
}ScreenIconCaptionRelation;

/**
* This enum represents the circumstances under which
* the icon shall be scaled inside the annotation rectangle.
*/
typedef enum ScreenScaleCondition
{
e_Always, ///< Always scale
e_WhenBigger,  ///<  Scale only when the icon is bigger than the annotation rectangle
e_WhenSmaller, ///< Scale only when the icon is smaller than the annotation rectangle
e_Never ///< Never scale
}ScreenScaleCondition;

/**
* This enum represents the scale type of the annotation.
*
* e_Anamorphic - Scale the icon to fill the annotation rectangle
* exactly, without regard to its original aspect
* ratio (ratio of width to height).
* e_Proportional - Scale the icon to fit the width or height
* of the annotation rectangle while maintaining
* the icons original aspect ratio. If the
* required horizontal and vertical scaling
* factors are different, use the smaller of the two,
* centering the icon within the annotation rectangle
* in the other dimension.
* Default value: e_Proportional.
*/
typedef enum ScreenScaleType
{
e_Anamorphic,
e_Proportional
}ScreenScaleType;

/**
* The SoundIcon of the Sound annotation.
*/
typedef enum SoundIcon
{
e_Speaker,	///< Speaker sound
e_Mic,		///< Mic sound
e_s_Unknown	///< Invalid or non-standard
}SoundIcon;

/**
* TextIcon enumeration defines the type of icon
* associated with the Text annotation.
*
*/
typedef enum TextIcon
{
e_Comment,      ///<comment icon
e_Key,          ///<key icon
e_Help,	        ///<Help icon
e_NewParagraph, ///<New Paragraph icon
e_Paragraph,    ///<Paragraph icon
e_Insert,       ///<Insert icon
e_Note,	        ///<Note icon
e_t_Unknown       ///<Unknown, no icon associated or non-standard icon.
}TextIcon;

/**
* This enum specifies the Highlighting mode of the widget annotation
*/
typedef enum WidgetHighlightingMode
{
e_w_none,     ///< No highlighting.
e_w_invert,   ///< Invert the contents of the annotation rectangle.
e_w_outline,  ///< Invert the annotation's border.
e_w_push,     ///< Display the annotation's down appearance, if any. If no down appearance is defined, the contents of the annotation rectangle shall be offset to appear as if it were being pushed below the surface of the page.
e_toggle    ///< Same as e_w_push (which is preferred).
}WidgetHighlightingMode;

/**
* An enumeration indicating where to position the text of the annotations
* caption relative to its icon.
*
* e_w_NoIcon - No icon; caption only
* e_w_NoCaption - No caption; icon only
* e_w_CBelowI - Caption below the icon
* e_w_CAboveI - Caption above the icon
* e_w_CRightILeft - Caption to the right of the icon
* e_w_CLeftIRight - Caption to the left of the icon
* e_w_COverlayI - Caption overlaid directly on the icon
* Default value: e_w_NoIcon.
*/
typedef enum WidgetIconCaptionRelation
{
e_w_NoIcon,
e_w_NoCaption,
e_w_CBelowI,
e_w_CAboveI,
e_w_CRightILeft,
e_w_CLeftIRight,
e_w_COverlayI
}WidgetIconCaptionRelation;

/**
* This enum represents the circumstances under which
* the icon shall be scaled inside the annotation rectangle .
*/
typedef enum WidgetScaleCondition
{
e_w_Always, ///< Always scale
e_w_WhenBigger,  ///<  Scale only when the icon is bigger than the annotation rectangle
e_w_WhenSmaller, ///< Scale only when the icon is smaller than the annotation rectangle
e_w_Never ///< Never scale
}WidgetScaleCondition;

/**
* This enum represents the scale type of the annotation.
*
* e_w_Anamorphic - Scale the icon to fill the annotation rectangle
* exactly, without regard to its original aspect
* ratio (ratio of width to height).
* e_w_Proportional - Scale the icon to fit the width or height
* of the annotation rectangle while maintaining
* the icons original aspect ratio. If the
* required horizontal and vertical scaling
* factors are different, use the smaller of the two,
* centering the icon within the annotation rectangle
* in the other dimension.
* Default value: e_w_Proportional.
*/
typedef enum WidgetScaleType
{
e_w_Anamorphic,
e_w_Proportional
}WidgetScaleType;

/**
* OCDrawMode controls drawing or enumerating the page with respect to optional content.
* Together with the value of SetNonOCDrawing this mode controls drawing or enumerating
* content on a page with optional content:
* <ul>
* <li>Content that is marked as optional content is drawn or not drawn according to the
* OCDrawMode and the visibility state as determined by the Optional Content Groups (OCGs)
* and OCMDs.
* </li>
* <li>Content that is not marked as optional content is drawn when GetNonOCDrawing() is
* true, and not drawn when GetNonOCDrawing() is false.
* </li>
* </ul>
*/
typedef enum OCDrawMode
{
/**
* Draw or enumerate optional content that is visible, according to the current state of
* Optional Content Groups (OCGs) and Optional Content Membership Dictionaries (OCMDs).
* This is the default mode.
*/
e_VisibleOC,

/**
* Draw or enumerate all optional content, regardless of its visibility state. If the
* context's 'SetNonOCDrawing' is enabled, all contents of document are shown.
*/
e_AllOC,

/**
* Draw or enumerate no optional content, regardless of its visibility state. If the
* context's 'SetNonOCDrawing' is not enabled, nothing is drawn, resulting in a blank page.
*/
e_NoOC
}OCDrawMode;

/**
* Visibility Policy Type.
* A Visibility Policy is used to determine whether an PDF::Element is visible
* in a given OCG::Context, depending on whether all groups in OCGs array are
* "ON" or "OFF", or when any of the groups is "ON" or "OFF".
*/
typedef enum VisibilityPolicyType {
e_AllOn,  ///< visible only if all of the entries in OCGs are ON.
e_AnyOn,  ///< visible if any of the entries in OCGs are ON.
e_AnyOff, ///< visible if any of the entries in OCGs are OFF.
e_AllOff  ///< visible only if all of the entries in OCGs are OFF.
}VisibilityPolicyType;

/**
* PDF/A Conformance Level (19005:1/2/3).
*
* Level A conforming files must adhere to all of the requirements of ISO 19005.
* A file meeting this conformance level is said to be a 'conforming PDF/A -1a file.'
*
* Level B conforming files shall adhere to all of the requirements of ISO 19005 except
* those of 6.3.8 and 6.8. A file meeting this conformance level is said to be a
* 'conforming PDF/A-1b file'. The Level B conformance requirements are intended to be
* those minimally necessary to ensure that the rendered visual appearance of a
* conforming file is preservable over the long term.
*/
typedef enum Conformance
{
e_NoConformance     = 0,
e_Level1A,
e_Level1B,
e_Level2A,
e_Level2B,
e_Level2U,
e_Level3A,
e_Level3B,
e_Level3U,
}Conformance;


typedef enum ErrorCode
{
// PDF/A-1 Level B Validation Errors --------------------------------
e_PDFA0_1_1  =11,   ///< Corrupt document.
e_PDFA0_1_2  =12,   ///< Corrupt content stream.
e_PDFA0_1_3  =13,   ///< Using JPEG2000 compression (PDF 1.4 compatibility).
e_PDFA0_1_4  =14,   ///< Contains compressed object streams (PDF 1.4 compatibility).
e_PDFA0_1_5  =15,   ///< Contains cross-reference streams (PDF 1.4 compatibility).
e_PDFA1_2_1  =121,  ///< Document does not start with % character.
e_PDFA1_2_2  =122,  ///< File header line not followed by % and 4 characters > 127.
e_PDFA1_3_1  =131,  ///< The trailer dictionary does not contain ID.
e_PDFA1_3_2  =132,  ///< Trailer dictionary contains Encrypt.
e_PDFA1_3_3  =133,  ///< Data after last EOF marker.
e_PDFA1_3_4  =134,  ///< Linearized file: ID in 1st page and last trailer are different.
e_PDFA1_4_1  =141,  ///< Subsection header: starting object number and range not separated by a single space.
e_PDFA1_4_2  =142,  ///< 'xref' and cross reference subsection header not separated by a single EOL marker.
e_PDFA1_6_1  =161,  ///< Invalid hexadecimal strings used.
e_PDFA1_7_1  =171,  ///< The 'stream' token is not followed by CR and LF or a single LF.
e_PDFA1_7_2  =172,  ///< The 'endstream' token is not preceded by EOL.
e_PDFA1_7_3  =173,  ///< The value of Length does not match the number of bytes.
e_PDFA1_7_4  =174,  ///< A stream object dictionary contains the F, FFilter, or FDecodeParms keys.
e_PDFA1_8_1  =181,  ///< Object number and generation number are not separated by a single white-space.
e_PDFA1_8_2  =182,  ///< Generation number and 'obj' are not separated by a single white-space.
e_PDFA1_8_3  =183,  ///< Object number not preceded by EOL marker
e_PDFA1_8_4  =184,  ///< 'endobj' not preceded by EOL marker
e_PDFA1_8_5  =185,  ///< 'obj' not followed by EOL marker
e_PDFA1_8_6  =186,  ///< 'endobj' not followed by EOL marker
e_PDFA1_10_1 =1101, ///< Using LZW compression.
e_PDFA1_11_1 =1111, ///< A file specification dictionary contains the EF key.
e_PDFA1_11_2 =1112, ///< Contains the EmbeddedFiles key
e_PDFA1_12_1 =1121, ///< Array contains more than 8191 elements
e_PDFA1_12_2 =1122, ///< Dictionary contains more than 4095 elements
e_PDFA1_12_3 =1123, ///< Name with more than 127 bytes
e_PDFA1_12_4 =1124, ///< Contains an integer value outside of the allowed range [-2^31, 2^31-1],
e_PDFA1_12_5 =1125, ///< Exceeds the maximum number (8,388,607) of indirect objects in a PDF file.
e_PDFA1_12_6 =1126, ///< The number of nested q/Q operators is greater than 28.
e_PDFA1_13_1 =1131, ///< Optional content (layers) not allowed.
e_PDFA2_2_1  =221,  ///< DestOutputProfile-s in OutputIntents array do not match.
e_PDFA2_3_2  =232,  ///< Not a valid ICC color profile.
e_PDFA2_3_3  =233,  ///< The N entry does not match the number of color components in the embedded ICC profile.
e_PDFA2_3_3_1=2331, ///< Device-specific color space used, but no GTS_PDFA1 OutputIntent.
e_PDFA2_3_3_2=2332, ///< Device-specific color space, does not match OutputIntent.
e_PDFA2_3_4_1=2341, ///< Device-specific color space used in an alternate color space.
e_PDFA2_4_1  =241,  ///< Image with Alternates key.
e_PDFA2_4_2  =242,  ///< Image with OPI key.
e_PDFA2_4_3  =243,  ///< Image with invalid rendering intent.
e_PDFA2_4_4  =244,  ///< Image with Interpolate key set to true.
e_PDFA2_5_1  =251,  ///< XObject with OPI key.
e_PDFA2_5_2  =252,  ///< PostScript XObject.
e_PDFA2_6_1  =261,  ///< Contains a reference XObject.
e_PDFA2_7_1  =271,  ///< Contains an XObject that is not supported (e.g. PostScript XObject).
e_PDFA2_8_1  =281,  ///< Contains an invalid Transfer Curve in the extended graphics state.
e_PDFA2_9_1  =291,  ///< Use of an invalid rendering intent.
e_PDFA2_10_1 =2101, ///< Illegal operator.
e_PDFA3_2_1  =321,  ///< Embedded font is damaged.
e_PDFA3_3_1  =331,  ///< Incompatible CIDSystemInfo entries
e_PDFA3_3_2  =332,  ///< Type 2 CIDFont without CIDToGIDMap
e_PDFA3_3_3_1=3331, ///< CMap not embedded
e_PDFA3_3_3_2=3332, ///< Inconsistent WMode in embedded CMap dictionary and stream.
e_PDFA3_4_1  =341,  ///< The font is not embedded.
e_PDFA3_5_1  =351,  ///< Embedded composite (Type0) font program does not define all font glyphs.
e_PDFA3_5_2  =352,  ///< Embedded Type1 font program does not define all font glyphs.
e_PDFA3_5_3  =353,  ///< Embedded TrueType font program does not define all font glyphs.
e_PDFA3_5_4  =354,  ///< The font descriptor dictionary does not include a CIDSet stream for CIDFont subset.
e_PDFA3_5_5  =355,  ///< The font descriptor dictionary does not include a	CharSet string for Type1 font subset.
e_PDFA3_5_6  =356,  ///< CIDSet in subset font is incomplete.
e_PDFA3_6_1  =361,  ///< Widths in embedded font are inconsistent with /Widths entry in the font dictionary.
e_PDFA3_7_1  =371,  ///< A non-symbolic TrueType font must use WinAnsiEncoding or MacRomanEncoding.
e_PDFA3_7_2  =372,  ///< A symbolic TrueType font must not specify encoding.
e_PDFA3_7_3  =373,  ///< A symbolic TrueType font does not have exactly one entry in cmap table.
e_PDFA4_1    =41,   ///< Transparency used (ExtGState with soft mask).
e_PDFA4_2    =42,   ///< Transparency used (XObject with soft mask).
e_PDFA4_3    =43,   ///< Transparency used (Page or Form XObject with transparency group).
e_PDFA4_4    =44,   ///< Transparency used (Blend mode is not 'Normal').
e_PDFA4_5    =45,   ///< Transparency used ('CA' value is not 1.0).
e_PDFA4_6    =46,   ///< Transparency used ('ca' value is not 1.0).
e_PDFA5_2_1  =521,  ///< Unknown annotation type.
e_PDFA5_2_2  =522,  ///< FileAttachment annotation is not permitted.
e_PDFA5_2_3  =523,  ///< Sound annotation is not permitted.
e_PDFA5_2_4  =524,  ///< Movie annotation is not permitted.
e_PDFA5_2_5  =525,  ///< Redact annotation is not permitted.
e_PDFA5_2_6  =526,  ///< 3D annotation is not permitted.
e_PDFA5_2_7  =527,  ///< Caret annotation is not permitted.
e_PDFA5_2_8  =528,  ///< Watermark annotation is not permitted.
e_PDFA5_2_9  =529,  ///< Polygon annotation is not permitted.
e_PDFA5_2_10 =5210, ///< PolyLine annotation is not permitted.
e_PDFA5_2_11 =5211, ///< Screen annotation is not permitted.
e_PDFA5_3_1  =531,  ///< An annotation dictionary contains the CA key with a value other than 1.0.
e_PDFA5_3_2_1=5321, ///< An annotation dictionary is missing F key.
e_PDFA5_3_2_2=5322, ///< An annotation's 'Print' flag is not set.
e_PDFA5_3_2_3=5323, ///< An annotation's 'Hidden' flag is set.
e_PDFA5_3_2_4=5324, ///< An annotation's 'Invisible' flag is set.
e_PDFA5_3_2_5=5325, ///< An annotation's 'NoView' flag is set.
e_PDFA5_3_3_1=5331, ///< An annotation's C entry present but no OutputIntent present
e_PDFA5_3_3_2=5332, ///< An annotation's C entry present but OutputIntent has non-RGB destination profile
e_PDFA5_3_3_3=5333, ///< An annotation's IC entry present but no OutputIntent present
e_PDFA5_3_3_4=5334, ///< An annotation's IC entry present and OutputIntent has non-RGB destination profile
e_PDFA5_3_4_0=5340, ///< Annotation is missing AP entry.
e_PDFA5_3_4_1=5341, ///< An annotation AP dictionary has entries other than the N entry.
e_PDFA5_3_4_2=5342, ///< An annotation AP dictionary does not contain N entry
e_PDFA5_3_4_3=5343, ///< AP has an N entry whose value is invalid.
e_PDFA6_1_1  =611,  ///< Contains an action type that is not permitted.
e_PDFA6_1_2  =612,  ///< Contains a non-predefined Named action.
e_PDFA6_2_1  =621,  ///< The document catalog dictionary contains AA entry.
e_PDFA6_2_2 = 622,  ///< Contains the JavaScript key.
e_PDFA6_2_3 = 623,  ///< Invalid destination.
e_PDFA7_2_1  =721,  ///< The document catalog does not contain Metadata stream.
e_PDFA7_2_2  =722,  ///< The Metadata object stream contains Filter key.
e_PDFA7_2_3  =723,  ///< The XMP Metadata stream is not valid.
e_PDFA7_2_4  =724,  ///< XMP property not predefined and no extension schema present.
e_PDFA7_2_5  =725,  ///< XMP not included in 'xpacket'.
e_PDFA7_3_1  =731,  ///< Document information entry 'Title' not synchronized with XMP.
e_PDFA7_3_2  =732,  ///< Document information entry 'Author' not synchronized with XMP.
e_PDFA7_3_3  =733,  ///< Document information entry 'Subject' not synchronized with XMP.
e_PDFA7_3_4  =734,  ///< Document information entry 'Keywords' not synchronized with XMP.
e_PDFA7_3_5  =735,  ///< Document information entry 'Creator' not synchronized with XMP.
e_PDFA7_3_6  =736,  ///< Document information entry 'Producer' not synchronized with XMP.
e_PDFA7_3_7  =737,  ///< Document information entry 'CreationDate' not synchronized with XMP.
e_PDFA7_3_8  =738,  ///< Document information entry 'ModDate' not synchronized with XMP.
e_PDFA7_3_9  =739,  ///< Wrong value type for predefined XMP property.
e_PDFA7_5_1  =751,  ///< 'bytes' and 'encoding' attributes are allowed in the header of an XMP packet.
e_PDFA7_8_1  =781,  ///< XMP Extension schema doesn't have a description.
e_PDFA7_8_2  =782,  ///< XMP Extension schema is not valid. Required property 'namespaceURI' might be missing in PDF/A Schema value Type.
e_PDFA7_8_3  =783,  ///< 'pdfaExtension:schemas' not found.
e_PDFA7_8_4  =784,  ///< 'pdfaExtension:schemas' is using a wrong value type.
e_PDFA7_8_5  =785,  ///< 'pdfaExtension:property' not found.
e_PDFA7_8_6  =786,  ///< 'pdfaExtension:property' is using a wrong value type.
e_PDFA7_8_7  =787,  ///< 'pdfaProperty:name' not found.
e_PDFA7_8_8  =788,  ///< 'pdfaProperty:name' is using a wrong value type.
e_PDFA7_8_9  =789,  ///< A description for a property is missing in 'pdfaSchema:property' sequence.
e_PDFA7_8_10 =7810, ///< 'pdfaProperty:valueType' not found.
e_PDFA7_8_11 =7811, ///< The required namespace prefix for extension schema is 'pdfaExtension'.
e_PDFA7_8_12 =7812, ///< The required field namespace prefix is 'pdfaSchema'.
e_PDFA7_8_13 =7813, ///< The required field namespace prefix is 'pdfaProperty'.
e_PDFA7_8_14 =7814, ///< The required field namespace prefix is 'pdfaType'.
e_PDFA7_8_15 =7815, ///< The required field namespace prefix is 'pdfaField'.
e_PDFA7_8_16 =7816, ///< 'pdfaSchema:valueType' not found.
e_PDFA7_8_17 =7817, ///< 'pdfaSchema:valueType' is using a wrong value type.
e_PDFA7_8_18= 7818, ///< Required property 'valueType' missing in PDF/A Schema Value Type.
e_PDFA7_8_19= 7819, ///< 'pdfaType:type' not found.
e_PDFA7_8_20 =7820, ///< 'pdfaType:type' is using a wrong value type.
e_PDFA7_8_21 =7821, ///< 'pdfaType:description' not found.
e_PDFA7_8_22 =7822, ///< 'pdfaType:namespaceURI' not found.
e_PDFA7_8_23 =7823, ///< 'pdfaType:field' is using a wrong value type.
e_PDFA7_8_24 =7824, ///< 'pdfaField:name' not found.
e_PDFA7_8_25 =7825, ///< 'pdfaField:name' is using a wrong value type.
e_PDFA7_8_26 =7826, ///< 'pdfaField:valueType' not found.
e_PDFA7_8_27 =7827, ///< 'pdfaField:valueType' is using a wrong type.
e_PDFA7_8_28 =7828, ///< 'pdfaField:description' not found.
e_PDFA7_8_29 =7829, ///< 'pdfaField:description' is using a wrong type.
e_PDFA7_8_30 =7830, ///< Required description for 'pdfaField::valueType' is missing.
e_PDFA7_8_31 =7831, ///< A property doesn't match its custom schema type.
e_PDFA7_11_1 =7111, ///< Missing PDF/A identifier
e_PDFA7_11_2 =7112, ///< Invalid PDF/A identifier namespace
e_PDFA7_11_3 =7113, ///< Invalid PDF/A conformance level.
e_PDFA7_11_4 =7114, ///< Invalid PDF/A part number.
e_PDFA7_11_5 =7115, ///< Invalid PDF/A amendment identifier.
e_PDFA9_1    =91,   ///< An interactive form field contains an action.
e_PDFA9_2    =92,   ///< The NeedAppearances flag in the interactive form dictionary is set to true.
e_PDFA9_3    =93,   ///< AcroForms contains XFA.
e_PDFA9_4    =94,   ///< Catalog contains NeedsRendering.

// PDF/A-1 Level A Validation Errors --------------------------------
e_PDFA3_8_1  =381,  ///< The font dictionary is missing 'ToUnicode' entry.
e_PDFA8_2_2  =822,  ///< The PDF is not marked as Tagged PDF.
e_PDFA8_3_3_1=8331, ///< Bad StructTreeRoot
e_PDFA8_3_3_2=8332, ///< Each structure element dictionary in the structure hierarchy must have a Type entry with the name value of StructElem.
e_PDFA8_3_4_1=8341, ///< A non-standard structure type does not map to a standard type.


// PDF/A-2 Level B Validation Errors --------------------------------
e_PDFA1_2_3   =123,     ///< Bad file header.
e_PDFA1_10_2  =1102,    ///< Invalid use of Crypt filter.
e_PDFA1_10_3  =1103,    ///< Bad stream Filter.
e_PDFA1_12_10 =11210,   ///< Bad Permission Dictionary
e_PDFA1_13_5  =1135,    ///< Page dimensions are outside of the allowed range (3-14400).
e_PDFA2_3_10  =2310,    ///< Contains DestOutputProfileRef
e_PDFA2_4_2_10 =24220,  ///< OPM is 1
e_PDFA2_4_2_11 =24221,  ///< Incorrect colorant specification in DeviceN
e_PDFA2_4_2_12 =24222,  ///< tintTransform is different in Separations with the same colorant name.
e_PDFA2_4_2_13 =24223,  ///< alternateSpace is different in Separations with the same colorant name.
e_PDFA2_5_10   = 2510,  ///< HTP entry in ExtGState.
e_PDFA2_5_11   = 2511,  ///< Unsupported HalftoneType.
e_PDFA2_5_12   = 2512,  ///< Uses HalftoneName key.
e_PDFA2_8_3_1  = 2831,  ///< JPEG2000: Only the JPX baseline is supported.
e_PDFA2_8_3_2  = 2832,  ///< JPEG2000: Invalid number of colour channels.
e_PDFA2_8_3_3  = 2833,  ///< JPEG2000: Invalid color space.
e_PDFA2_8_3_4  = 2834,  ///< JPEG2000: The bit-depth JPEG2000 data must be in range 1-38.
e_PDFA2_8_3_5  = 2835,  ///< JPEG2000: All colour channels in the JPEG2000 data must have the same bit-depth.
e_PDFA2_10_20  = 21020, ///< Page Group entry is missing in a document without OutputIntent.
e_PDFA2_10_21  = 21021, ///< Invalid blend mode.
e_PDFA11_0_0   = 11000, ///< Catalog contains Requirements key.
e_PDFA6_2_11_8 = 62118, ///<  Use of .notdef glyph

e_PDFA_LAST
}ErrorCode;


typedef enum ContentItemType
{
e_MCR,     ///< marked-content reference.
e_MCID,    ///< marked-content identifier.
e_OBJR,    ///< object reference dictionary.
e_c_Unknown  ///< unknown content type.
}ContentItemType;

/**
* Enumaration used to indicate operator type.
*/
typedef enum PathSegmentType
{
// Start a new sub-path at the given (x,y) coordinate.
// Number of arguments: 2
e_moveto = 1,

// A line from the current point to the given (x,y) coordinate which becomes
// the new current point.
// Number of arguments: 2
e_lineto,

// A cubic Bzier curve from the current point to (x,y) using (x1,y1) as
// the control point at the beginning of the curve and (x2,y2) as the control
// point at the end of the curve.
// Number of arguments: 6
e_cubicto,

// A quadratic Bzier curve from the current point to (x,y) using (x1,y1) as
// the control point. Note that e_conicto does not appear in PDF content streams.
// This operator is only used to represent glyph outlines (e.g. PDF::Font::GetGlyphPath()
// may return a path containing e_conicto operator).
// Number of arguments: 4
e_conicto,

// A rectangle at the given (x,y) coordinate and the given width and height (w, h).
// Number of arguments: 4
e_rect,

// Close the current subpath by drawing a straight line from the current point
// to current subpath's initial point.
// Number of arguments: 0
e_closepath
}PathSegmentType;

typedef enum StandardType1Font {  e_times_roman = 0,
e_times_bold,
e_times_italic,
e_times_bold_italic,
e_helvetica,
e_helvetica_bold,
e_helvetica_oblique,
e_helvetica_bold_oblique,
e_courier,
e_courier_bold,
e_courier_oblique,
e_courier_bold_oblique,
e_symbol,
e_zapf_dingbats,
e_ft_null}StandardType1Font;



typedef enum Encoding
{
e_IdentityH=0,
e_Indices
}Encoding;


typedef enum FontType
{
e_FontType1,			// FontType 1 PostScript font
e_TrueFontType,			// TrueFontType font
e_MMFontType1,			// FontType 1 multiple master PostScript font
e_FontType3,			// FontType 3 PostScript font
e_FontType0,			// FontType 0 PostScript composite (CID) font
e_CIDFontType0,			// FontType 0 CID font
e_CIDFontType2,			// FontType 2 CID font
}FontType;


typedef enum ShadingType
{
e_function_shading,
e_axial_shading,
e_radial_shading,
e_free_gouraud_shading,
e_lattice_gouraud_shading,
e_coons_shading,
e_tensor_shading,
e_s_null
}ShadingType;


typedef enum PatternColorType
{
e_uncolored_tiling_pattern,
e_colored_tiling_pattern,
e_shading,
e_p_null
}PatternColorType;

typedef enum TilingType {  e_constant_spacing,
e_no_distortion,
e_constant_spacing_fast_fill}TilingType;


typedef enum InputFilter
{
e_i_none,     // Input stream is not compressed
e_i_jpeg,     // Input image is a JPEG image
e_jp2,      // Input image is a JP2 (JPEG2000) image
e_i_flate,    // Input image is a Flate compressed
e_g3,       // Input image is a G3 stream
e_g4,       // Input image is a G4 stream
e_ascii_hex // Input image stream compressed using ASCIIHexDecode filter
}InputFilter;


typedef enum ElementType
{
e_e_null,                  // undefined element type
e_path,                  // path object
e_text_obj_begin,            // marks the beginning of a text container
e_text_obj,                  // text object within a text container
e_text_obj_new_line,         // indicates the start of the new text line
e_text_obj_end,              // marks the end of text container
e_image,                 // image XObject
e_inline_image,          // inline image object
e_e_shading,               // shading object
e_form,                  // a form XObject
e_group_begin,           // push graphics state operator (q)
e_group_end,             // pop graphics state operator (Q)
e_marked_content_begin,  // marks the beginning of marked content sequence (BMC, BDC)
e_marked_content_end,    // marks the end of marked content sequence (EMC)
e_marked_content_point   // designate a marked-content point (MP, DP)
}ElementType;

/**
*
* Enumeration describing the placement of the element written to a page.
*/
typedef enum WriteMode {
e_underlay,    ///> element is put in the background layer of the page
e_overlay,     ///> element appears on top of the existing graphics
e_replacement  ///> element will replace current page contents
}WriteMode;


typedef enum Threshold
{
// SWIG
}Threshold;


typedef enum FlattenMode
{
/**
* Feature reduce PDF to a simple two layer representation consisting
* of a single background RGB image and a simple top text layer.
*/
e_simple,
/**
* Feature reduce PDF while trying to preserve some
* complex PDF features (such as vector figures, transparency, shadings,
* blend modes, Type3 fonts etc.) for pages that are already fast to render.
* This option can also result in smaller & faster files compared to e_simple,
* but the pages may have more complex structure.
*/
e_fast
}FlattenMode;

typedef enum PageLabelStyle
{
e_decimal,              ///< Decimal Arabic numerals
e_roman_uppercase,      ///< Uppercase Roman numerals
e_roman_lowercase,      ///< Lowercase Roman numerals
e_alphabetic_uppercase, ///< Uppercase letters (A to Z for the first 26 pages, AA to ZZ for the next 26, and so on)
e_alphabetic_lowercase, ///< Lowercase letters (a to z for the first 26 pages, aa to zz for the next 26, and so on)
e_pg_none                  ///< No numeric portion in the label
}PageLabelStyle;


typedef enum PageSetFilter
{
e_all,
e_even,
e_odd
}PageSetFilter;

/**
* PageMode specifies how the document should be displayed
* when opened:
*
* - e_UseNone Displays document, but neither thumbnails nor
*   bookmarks.
* - e_UseThumbs Displays document plus thumbnails.
* - e_UseBookmarks Displays document plus bookmarks.
* - e_FullScreen Displays document in full-screen viewing mode.
* - e_UseOC Displays Optional Content (OC) group panel.
* - e_UseAttachments - Displays attachments panel.
*/
typedef enum PageMode
{
e_UseNone,
e_UseThumbs,
e_UseBookmarks,
e_FullScreen,
e_UseOC,
e_UseAttachments
}PageMode;

/**
* PageLayout specifies the page layout to be used when the
* document is opened:
*
* - e_Default PageLayout is not explicitly specified, use user defined
* preferred layout.
*
* - e_SinglePage Display one page at a time.
*
* - e_OneColumn Display the pages in one-column
* mode.
*
* - e_TwoColumnLeft Display the pages in two-column continuous
* mode with first page on left (i.e. all odd numbered pages
* on the left).
*
* - e_TwoColumnRight Display the pages in two-column
* continuous mode with first page on right (i.e. all odd
* numbered pages on the right).
*
* - e_TwoPageLeft Display the pages two at a time, with
* odd-numbered pages on the left.
*
* - e_TwoPageRight Display the pages two at a time, with
* odd-numbered pages on the right.
*/
typedef enum PageLayout
{
e_Default,
e_SinglePage,
e_OneColumn,
e_TwoColumnLeft,
e_TwoColumnRight,
e_TwoPageLeft,
e_TwoPageRight
}PageLayout;

/**
* ViewerPref enumeration specifies how various GUI elements
* should behave when the document is opened.
*
* - e_HideToolbar A flag specifying whether to hide the
* viewer applications toolbars when the document is active.
* Default value: false.
*
* - e_HideMenubar A flag specifying whether to hide the viewer
* applications menu bar when the document is active.
* Default value: false.
*
* - e_HideWindowUI A flag specifying whether to hide user
* interface elements in the documents window (such as scroll
* bars and navigation controls), leaving only the documents
* contents displayed. Default value: false.
*
* - e_FitWindow A flag specifying whether to resize the
* documents window to fit the size of the first displayed
* page. Default value: false.
*
* - e_CenterWindow A flag specifying whether to position the
* documents window in the center of the screen.
* Default value: false.
*
* - e_DisplayDocTitle A flag specifying whether the windows
* title bar should display the document title taken from the
* Title entry of the document information dictionary.
* If false, the title bar should instead display the name of
* the PDF file containing the document. Default value: false.
*/
typedef enum ViewerPref
{
e_HideToolbar,
e_HideMenubar,
e_HideWindowUI,
e_FitWindow,
e_CenterWindow,
e_DisplayDocTitle,
}ViewerPref;


typedef enum InsertFlag {
e_pd_none,				//default, do not insert bookmarks
e_insert_bookmark	//insert bookmarks
}InsertFlag;


typedef enum ExtractFlag {
e_forms_only,				// default, only extract form fields to FDF
e_annots_only,				// only extract annots
e_both                      // extract both form fields and annots
}ExtractFlag;

typedef enum DownloadedType {  e_downloadedtype_page = 0,
e_downloadedtype_thumb,
e_downloadedtype_named_dests,
e_downloadedtype_outline,
e_downloadedtype_finished,
e_downloadedtype_failed,
e_downloadedtype_opened}DownloadedType;

/**
* PDFNet includes two separate rasterizer implementations utilizing different
* graphics libraries.
*
* The default rasterizer is 'e_BuiltIn' which is a high-quality,
* anti-aliased and platform independent rasterizer. This rasterizer
* is available on all supported platforms.
*
* On Windows platforms, PDFNet also includes GDI+ based rasterizer.
* This rasterizer is included mainly to provide vector output for
* printing, for EMF/WMF export, etc. For plain image rasterization
* we recommend using the built-in rasterizer.
*/
typedef enum RasterizerType {
e_BuiltIn,  ///< high-quality, platform independent rasterizer.
e_GDIPlus   ///< GDI+ based rasterizer.
}RasterizerType;

/**
* Determines if overprint is used.
* e_op_on: overprint is always on;
* e_op_off: overprint is always off.
* e_op_pdfx_on: overprint is on only for PDF/X files.
*/

typedef enum OverprintPreviewMode
{
e_op_off = 0,
e_op_on,
e_op_pdfx_on
}OverprintPreviewMode;

/**
* Pixel format type.
*/
typedef enum PixelFormat {
e_rgba,
e_bgra,
e_rgb,
e_bgr,
e_gray,
e_gray_alpha,
e_cmyk
}PixelFormat;


typedef enum CloudErrorCode
;;
/**
* ConnectToCloud() is used to connect PDFNet with your 'pay-as-you-go' account
* (http://www.pdftron.com/pdfnet/cloud).
*
* PDFTron Cloud is a 'pay-as-you-go' service that offers PDFTron document
* conversion and processing capabilities with minimal startup costs.
*
* PDFTron Cloud account allows applications to convert documents either on your
* own servers (e.g. using PDFNet SDK or DocPub CLI) or via PDFTron hosted REST
* service.
*
* Benefits of the self-hosted model are related to privacy and increased
* flexibility and speed from your own hardware infrastructure. On the other hand,
* self-hosted model may be more costly due to operation fees.
*
* @note Please note that in order to use ConnectToCloud() you need to have a
* valid Enterprise or Web CPU license for PDFNet. If you do not need additional
* functionality provided by PDFNet (e.g. you simply need to convert), please use
* DocPub CLI instead of PDFNet SDK.
*
* @note ConnectToCloud() should be called once, immediately after
* PDFNet.Initialize("...license key...").
*
* @param api_id Your API ID (i.e. username). You should receive this information
* via email after Cloud API service (https://api.pdftron.com) sign-up. You can also
* find your 'API ID' in the 'Account' section in your PDFTron Cloud account.

* @param api_secret (i.e. password). This information is provided together with
* 'api_id' and can also be retrieved from https://api.pdftron.com.
*
* @return CloudErrorCode will be returned. STATUS_OK if PDFNet successfully connected to your Cloud account.
*
* @exception If called before call to PDFNet.Initialized or in DEMO mode, the function will throw an exception.
*/
static PDFNet::CloudErrorCode ConnectToCloud(const char* api_id, const char* api_secret);

enum CMSType
{
e_lcms,		///< Use LittleCMS (available on all supported platforms).
e_icm,		///< Use Windows ICM2 (available only on Windows platforms).
e_no_cms    ///< No ICC color management.
}CloudErrorCode;

typedef enum CMSType {  e_lcms,
e_icm,
e_no_cms}CMSType;

/**
* Standard character orderings. PDFNet.AddFontSubst() can be used
* to associate a specific font with a given character ordering
* and to override default font mapping algorithm.
*/
typedef enum CharacterOrdering {
e_Identity = 0,    ///< Generic/Unicode
e_Japan1   = 1,    ///< Japanese
e_Japan2   = 2,    ///< Japanese
e_GB1      = 3,    ///< Chinese; Simplified
e_CNS1     = 4,    ///< Chinese; Traditional
e_Korea1   = 5     ///< Korean
}CharacterOrdering;

/**
* PagePresentationMode lists common modes of presenting PDF pages.
*/
/**
* PagePresentationMode lists common modes of presenting PDF pages.
*/
typedef enum PagePresentationMode
{
e_single_page = 1,         //<<< Display one page at a time.
e_single_continuous,       //<<< Display the pages in one column.
e_facing,                  //<<< Display the pages two at a time, with odd-numbered pages on the left.
e_facing_continuous,       //<<< Display the pages in two columns, with odd-numbered pages on the left.
e_facing_cover,            //<<< Display the pages two at a time, with odd-numbered pages on the right.
e_facing_continuous_cover  //<<< Display the pages in two columns, with odd-numbered pages on the right.
}PagePresentationMode;

/**
* TextSelectionMode lists different text selection modes that can be used to highlight text.
* PDFView currently supports the following text selection modes:
*   - e_structural - Selects text based on the logical structure of the page. This type of selection is similar to HTML like selection in web-browsers.
*   - e_rectangular - Selects all words that intersect the given selection rectangle.
*/
/**
* TextSelectionMode lists different text selection modes that can be used to highlight text.
* PDFView currently supports the following text selection modes:
*   - e_structural - Selects text based on the logical structure of the page. This type of selection is similar to HTML like selection in web-browsers.
*   - e_rectangular - Selects all words that intersect the given selection rectangle.
*/
typedef enum TextSelectionMode {
e_structural,
e_rectangular
}TextSelectionMode;

/**
* PageViewMode lists common modes of viewing PDF pages. PDFView currently supports
* the following viewing modes:
*   - e_fit_page - page zoom is automatically adjusted so that entire page fits into available space.
*   - e_fit_width - page zoom is automatically adjusted so that page width fits into available space.
*   - e_fit_height - page zoom is automatically adjusted so that page height fits into available space.
*   - e_zoom - page is zoomed. The zoom ratio is specified using SetZoom() function.
*   - PVM_SIZE - the size of the enum, should always stay as the last element
*/
/**
* PageViewMode lists common modes of viewing PDF pages. PDFView currently supports
* the following viewing modes:
*   - e_fit_page - page zoom is automatically adjusted so that entire page fits into available space.
*   - e_fit_width - page zoom is automatically adjusted so that page width fits into available space.
*   - e_fit_height - page zoom is automatically adjusted so that page height fits into available space.
*   - e_zoom - page is zoomed. The zoom ratio is specified using SetZoom() function.
*   - PVM_SIZE - the size of the enum, should always stay as the last element
*/
typedef enum PageViewMode
{
e_fit_page = 0,
e_fit_width,
e_fit_height,
e_zoom,
PVM_SIZE	//must stay as the last element
}PageViewMode;


typedef enum SizeType
{
e_relative_scale = 1,
e_absolute_size = 2,
e_s_font_size = 3
}SizeType;


typedef enum HorizontalAlignment
{
e_horizontal_left = -1,
e_horizontal_center = 0,
e_horizontal_right = 1
}HorizontalAlignment;


typedef enum VerticalAlignment
{
e_vertical_bottom = -1,
e_vertical_center = 0,
e_vertical_top = 1
}VerticalAlignment;


typedef enum TextAlignment
{
e_align_left = -1,
e_align_center = 0,
e_align_right = 1
}TextAlignment;

/**
* Processing options that can be passed in Begin() method to direct
* the flow of content recognition algorithms
*/
typedef enum ProcessingFlags
{
// Disables expanding of ligatures using a predefined mapping.
// Default ligatures are: fi, ff, fl, ffi, ffl, ch, cl, ct, ll,
// ss, fs, st, oe, OE.
e_no_ligature_exp = 1,

// Disables removing duplicated text that is frequently used to
// achieve visual effects of drop shadow and fake bold.
e_no_dup_remove = 2,

// Treat punctuation (e.g. full stop, comma, semicolon, etc.) as
// word break characters.
e_punct_break = 4,

// Enables removal of text that is obscured by images or
// rectangles. Since this option has small performance penalty
// on performance of text extraction, by default it is not
// enabled.
e_remove_hidden_text = 8,

// Enables removing text that uses rendering mode 3 (i.e. invisible text).
// Invisible text is usually used in 'PDF Searchable Images' (i.e. scanned
// pages with a corresponding OCR text). As a result, invisible text
// will be extracted by default.
e_no_invisible_text = 16
}ProcessingFlags;

/**
* Flags controlling the structure of XML output in a call to GetAsXML().
*/
typedef enum XMLOutputFlags
{
// Output words as XML elements instead of inline text.
e_words_as_elements = 1,

// Include bounding box information for each XML element.
// The bounding box information will be stored as 'bbox' attribute.
e_output_bbox = 2,

// Include font and styling information.
e_output_style_info = 4
}XMLOutputFlags;

/**
* Search modes that control how searching is conducted.
*/
typedef enum TextSearchModes
{
//use regular expressions
e_reg_expression = 0x0001,

//match case-sensitively
e_case_sensitive = e_reg_expression << 1,

//match the entire word
e_whole_word	 = e_case_sensitive << 1,

//search upward (from the end of the file and from the bottom of a page)
e_search_up		 = e_whole_word << 1,

//tells the search process to return when each page is finished; this is
//useful when a user needs Run() to return periodically so that certain
//things (e.g., UI) can be updated from time to time.
e_page_stop		 = e_search_up << 1,

//tells the search process to compute Highlight information.
e_highlight		 = e_page_stop << 1,

//tells the search process to compute the ambient string of the found pattern.
//This is useful if a user wants to examine or display what surrounds the
//found pattern.
e_ambient_string = e_highlight << 1
}TextSearchModes;



/**
*	SWIG director's base class
*
*	Contains virtual functions which match the signature of the PDFNet function pointers.
*  Each virtual function has a matching static function calling it.
*	User extends this class in the target language and overrides the function of interest.
*	The static function is assigned to the function pointer.
*/
@interface Callback : NSObject
{


}





/**
* Declaration for the callback function that will be called just
* before PDFView starts rendering.
*
* @param data Custom data to be passed as a parameter to 'proc'.
*/
- (void)RenderBeginEventProc;
+ (void)StaticRenderBeginEventProc: (SWIGTYPE_p_void*)data;
/**
* Declaration for the callback function that will be called after
* PDFView is done with rendering.
*
* @param data Custom data to be passed as a parameter to 'proc'.
* @param canceled - this parameter is false if PDFView successfully
* completed the rendering, or is true if the rendering was canceled.
*
* @note this callback is available only in the C++ SDK and not
* available in pre-packaged PDF viewing controls (.NET/Java/ActiveX).
*/
- (void)RenderFinishEventProc: (BOOL)cancelled;
+ (void)StaticRenderFinishEventProc: (SWIGTYPE_p_void*)data cancelled:  (BOOL)cancelled;
/**
* Error handling.
* A type of callback function (or a delegate in .NET terminology) that is called in case
* an error is encountered during rendering.
*/
- (void)ErrorReportProc: (NSString *)message;
+ (void)StaticErrorReportProc: (NSString *)message data:  (SWIGTYPE_p_void*)data;
/**
* A prototype for a callback function (or a delegate in .NET terminology)
* that will be called whenever current page number changes.
*
* @param current_page the current page.
* @param num_pages total number of pages in the document.
* @param data Custom data to be passed as a second parameter to 'curr_pagenum_proc'.
*/
- (void)CurrentPageProc: (int)current_page num_pages:  (int)num_pages;
+ (void)StaticCurrentPageProc: (int)current_page num_pages:  (int)num_pages data:  (SWIGTYPE_p_void*)data;
/**
* A prototype for a callback function (or a delegate in .NET terminology)
* that will be called whenever current zoom (magnification) number changes.
*
* @param current_zoom the current zoom.
* @param data Custom data to be passed as a second parameter to 'curr_zoom_proc'.
*/
- (void)CurrentZoomProc: (double)curr_zoom_proc;
+ (void)StaticCurrentZoomProc: (double)curr_zoom_proc data:  (SWIGTYPE_p_void*)data;
- (void)CreateTileProc: (NSString *)buffer originX:  (int)originX originY:  (int)originY width:  (int)width height:  (int)height cellNumber:  (long long)cellNumber finalRender:  (BOOL)finalRender predictionRender:  (BOOL)predictionRender tiles_remaining:  (int)tiles_remaining first_tile:  (BOOL)first_tile canvas_width:  (int)canvas_width canvas_height:  (int)canvas_height cell_side_length:  (int)cell_side_length cell_per_row:  (int)cell_per_row cell_per_col:  (int)cell_per_col thumb_nail_id:  (int)thumb_nail_id;
+ (void)StaticCreateTileProc: (SWIGTYPE_p_void*)callingObject buffer:  (NSString *)buffer originX:  (int)originX originY:  (int)originY width:  (int)width height:  (int)height canvasNumber:  (int)canvasNumber cellNumber:  (long long)cellNumber finalRender:  (BOOL)finalRender predictionRender:  (BOOL)predictionRender tiles_remaining:  (int)tiles_remaining first_tile:  (BOOL)first_tile canvas_width:  (int)canvas_width canvas_height:  (int)canvas_height cell_side_length:  (int)cell_side_length cell_per_row:  (int)cell_per_row cell_per_col:  (int)cell_per_col thumb_nail_id:  (int)thumb_nail_id;
- (void)RemoveTileProc: (int)canvasNumber cellNumber:  (long long)cellNumber thumb_nail_id:  (int)thumb_nail_id;
+ (void)StaticRemoveTileProc: (SWIGTYPE_p_void*)callingObject canvasNumber:  (int)canvasNumber cellNumber:  (long long)cellNumber thumb_nail_id:  (int)thumb_nail_id;
- (void)ThumbAsyncHandler: (int)page_num was_thumb_found:  (BOOL)was_thumb_found thumb_buf:  (NSString *)thumb_buf thumb_width:  (int)thumb_width thumb_height:  (int)thumb_height custom_data:  (SWIGTYPE_p_void*)custom_data;
+ (void)StaticThumbAsyncHandler: (SWIGTYPE_p_void*)callingObject page_num:  (int)page_num was_thumb_found:  (BOOL)was_thumb_found thumb_buf:  (NSString *)thumb_buf thumb_width:  (int)thumb_width thumb_height:  (int)thumb_height custom_data:  (SWIGTYPE_p_void*)custom_data;
- (void)FindTextAsyncHandler: (BOOL)success select:  (SWIGTYPE_p_Selection*)select;
+ (void)StaticFindTextProc: (unsigned char)success select:  (SWIGTYPE_TRN_PDFViewSelection*)select user_data:  (SWIGTYPE_p_void*)user_data;
- (id)init;

@end


/**
A collection of Obj objects.
*/
@interface VectorObj : NSObject
{


}




/**
The number of elements in the vector.
*/
- (unsigned long)size;
/**
The allocated storage capacity.
*/
- (unsigned long)capacity;
/**
Request a change in capacity.
*/
- (void)reserve: (unsigned long)n;
/**
Return true if the vector is empty; false otherwise.
*/
- (BOOL)isEmpty;
/**
Clear content.
*/
- (void)clear;
/**
Add element at the end.
*/
- (void)add: (Obj*)x;
/**
Return element at index i.
*/
- (Obj*)get: (int)i;
/**
Set element at index i.
*/
- (void)set: (int)i val:  (Obj*)val;
/**
Default constructor.
*/
- (id)init;
@end


/**
A collection of Page objects.
*/
@interface VectorPage : NSObject
{


}




/**
The number of elements in the vector.
*/
- (unsigned long)size;
/**
The allocated storage capacity.
*/
- (unsigned long)capacity;
/**
Request a change in capacity.
*/
- (void)reserve: (unsigned long)n;
/**
Return true if the vector is empty; false otherwise.
*/
- (BOOL)isEmpty;
/**
Clear content.
*/
- (void)clear;
/**
Add element at the end.
*/
- (void)add: (Page*)x;
/**
Return element at index i.
*/
- (Page*)get: (int)i;
/**
Set element at index i.
*/
- (void)set: (int)i val:  (Page*)val;
/**
Default constructor.
*/
- (id)init;
@end


/**
A collection of String objects.
*/
@interface VectorString : NSObject
{


}




/**
The number of elements in the vector.
*/
- (unsigned long)size;
/**
The allocated storage capacity.
*/
- (unsigned long)capacity;
/**
Request a change in capacity.
*/
- (void)reserve: (unsigned long)n;
/**
Return true if the vector is empty; false otherwise.
*/
- (BOOL)isEmpty;
/**
Clear content.
*/
- (void)clear;
/**
Add element at the end.
*/
- (void)add: (NSString*)x;
/**
Return element at index i.
*/
- (NSString*)get: (int)i;
/**
Set element at index i.
*/
- (void)set: (int)i val:  (NSString*)val;
/**
Default constructor.
*/
- (id)init;
@end


/**
A collection of Redaction objects.
*/
@interface VectorRedaction : NSObject
{


}




/**
The number of elements in the vector.
*/
- (unsigned long)size;
/**
The allocated storage capacity.
*/
- (unsigned long)capacity;
/**
Request a change in capacity.
*/
- (void)reserve: (unsigned long)n;
/**
Return true if the vector is empty; false otherwise.
*/
- (BOOL)isEmpty;
/**
Clear content.
*/
- (void)clear;
/**
Add element at the end.
*/
- (void)add: (Redaction*)x;
/**
Return element at index i.
*/
- (Redaction*)get: (int)i;
/**
Set element at index i.
*/
- (void)set: (int)i val:  (Redaction*)val;
/**
Default constructor.
*/
- (id)init;
@end


/**
A collection of QuadPoint objects.
*/
@interface VectorQuadPoint : NSObject
{


}




/**
The number of elements in the vector.
*/
- (unsigned long)size;
/**
The allocated storage capacity.
*/
- (unsigned long)capacity;
/**
Request a change in capacity.
*/
- (void)reserve: (unsigned long)n;
/**
Return true if the vector is empty; false otherwise.
*/
- (BOOL)isEmpty;
/**
Clear content.
*/
- (void)clear;
/**
Add element at the end.
*/
- (void)add: (QuadPoint*)x;
/**
Return element at index i.
*/
- (QuadPoint*)get: (int)i;
/**
Set element at index i.
*/
- (void)set: (int)i val:  (QuadPoint*)val;
/**
Default constructor.
*/
- (id)init;
@end


@interface TRN_matrix2d : NSObject
{


}




- (void)setM_a: (double)value;
- (double)getM_a;
- (void)setM_b: (double)value;
- (double)getM_b;
- (void)setM_c: (double)value;
- (double)getM_c;
- (void)setM_d: (double)value;
- (double)getM_d;
- (void)setM_h: (double)value;
- (double)getM_h;
- (void)setM_v: (double)value;
- (double)getM_v;
- (id)init;
@end


@interface TRN_rect : NSObject
{


}




- (void)setX1: (double)value;
- (double)getX1;
- (void)setY1: (double)value;
- (double)getY1;
- (void)setX2: (double)value;
- (double)getX2;
- (void)setY2: (double)value;
- (double)getY2;
- (void)setMp_rect: (SWIGTYPE_TRN_Obj*)value;
- (SWIGTYPE_TRN_Obj*)getMp_rect;
- (id)init;
@end


@interface TRN_date : NSObject
{


}




- (void)setYear: (unsigned short)value;
- (unsigned short)getYear;
- (void)setMonth: (char)value;
- (char)getMonth;
- (void)setDay: (char)value;
- (char)getDay;
- (void)setHour: (char)value;
- (char)getHour;
- (void)setMinute: (char)value;
- (char)getMinute;
- (void)setSecond: (char)value;
- (char)getSecond;
- (void)setUT: (char)value;
- (char)getUT;
- (void)setUT_hour: (char)value;
- (char)getUT_hour;
- (void)setUT_minutes: (char)value;
- (char)getUT_minutes;
- (void)setMp_obj: (SWIGTYPE_TRN_Obj*)value;
- (SWIGTYPE_TRN_Obj*)getMp_obj;
- (id)init;
@end


@interface TRN_chardata : NSObject
{


}




- (void)setChar_code: (unsigned int)value;
- (unsigned int)getChar_code;
- (void)setX: (double)value;
- (double)getX;
- (void)setY: (double)value;
- (double)getY;
- (void)setChar_data: (NSData*)value;
- (NSData*)getChar_data;
- (void)setBytes: (int)value;
- (int)getBytes;
- (id)init;
@end


@interface TRN_point : NSObject
{


}




- (void)setX: (double)value;
- (double)getX;
- (void)setY: (double)value;
- (double)getY;
- (id)init;
@end


@interface TRN_quadpoint : NSObject
{


}




- (void)setP1: (TRN_point*)value;
- (TRN_point*)getP1;
- (void)setP2: (TRN_point*)value;
- (TRN_point*)getP2;
- (void)setP3: (TRN_point*)value;
- (TRN_point*)getP3;
- (void)setP4: (TRN_point*)value;
- (TRN_point*)getP4;
- (id)init;
@end


@interface PDFPoint : TRN_point




- (id)init;
- (id)initWithPx: (double)px py:  (double)py;
@end


/**
* 2D Matrix
*
* A Matrix2D object represents a 3x3 matrix that, in turn, represents an affine transformation.
* A Matrix2D object stores only six of the nine numbers in a 3x3 matrix because all 3x3
* matrices that represent affine transformations have the same third column (0, 0, 1).
*
* Affine transformations include rotating, scaling, reflecting, shearing, and translating.
* In PDFNet, the Matrix2D class provides the foundation for performing affine transformations
* on vector drawings, images, and text.
*
* A transformation matrix specifies the relationship between two coordinate spaces.
* By modifying a transformation matrix, objects can be scaled, rotated, translated,
* or transformed in other ways.
*
* A transformation matrix in PDF is specified by six numbers, usually in the form
* of an array containing six elements. In its most general form, this array is denoted
* [a b c d h v]; The following table lists the arrays that specify the most common
* transformations:
*
*   - Translations are specified as [1 0 0 1 tx ty], where tx and ty are the distances
*     to translate the origin of the coordinate system in the horizontal and vertical
*     dimensions, respectively.
*
*   - Scaling is obtained by [sx 0 0 sy 0 0]. This scales the coordinates so that 1
*     unit in the horizontal and vertical dimensions of the new coordinate system is
*     the same size as sx and sy units, respectively, in the previous coordinate system.
*
*   - Rotations are produced by [cos(A) sin(A) -sin(A) cos(A) 0 0], which has the effect
*     of rotating the coordinate system axes by an angle 'A' counterclockwise.
*
*   - Skew is specified by [1 tan(A) tan(B) 1 0 0], which skews the x axis by an angle
*     A and the y axis by an angle B.
*
*  Matrix2D elements are positioned as follows :
*			| m_a m_b 0 |
*			| m_c m_d 0 |
*			| m_h m_v 1 |
*
* A single Matrix2D object can store a single transformation or a sequence of transformations.
* The latter is called a composite transformation. The matrix of a composite transformation is
* obtained by multiplying (concatenating) the matrices of the individual transformations.
* Because matrix multiplication is not commutative-the order in which matrices are multiplied
* is significant. For example, if you first rotate, then scale, then translate, you get a
* different result than if you first translate, then rotate, then scale.
*
* For more information on properties of PDF matrices please refer to PDF Reference Manual
* (Sections 4.2 'Coordinate Systems' and 4.2.3 'Transformation Matrices')
*
* @code
* The following sample illustrates how to use Matrix2D in order to position
* an image on the page. Note that PDFNet uses the same convention of matrix
* multiplication used in PostScript and OpenGL.
*
*	Element element = eb.CreateImage(Image(...));
*	double deg2rad = 3.1415926535 / 180.0;
*
*	Matrix2D mtx = Matrix2D(1, 0, 0, 1, 0, 200); // Translate
*	mtx *= Matrix2D(300, 0, 0, 200, 0, 0);    // Scale
*	mtx *= Matrix2D::RotationMatrix( 90 * deg2rad ); // Rotate
*	element.GetGState().SetTransform(mtx);
*	writer.WritePlacedElement(element);
* @endcode
*
* @code
* The following sample sample illustrates how to use Matrix2D in order to calculate
* absolute positioning for the text on the page.
* ...
* Matrix2D text_mtx = text_element.GetTextMatrix();
* double x, y;
* for (CharIterator itr = text_element.GetCharIterator(); itr.HasNext(); itr.Next()) {
*   x = itr.Current().x; // character positioning information
*   y = itr.Current().y;
*   // Get current transformation matrix (CTM)
*   Matrix2D ctm = text_element.GetCTM();
*
*   // To get the absolute character positioning information concatenate current
*   // text matrix with CTM and then multiply relative positioning coordinates with
*   // the resulting matrix.
*   Matrix2D mtx = ctm * text_mtx;
*   mtx.Mult(x, y);
* }
* @endcode
*/
@interface Matrix2D : TRN_matrix2d





/**
* Creates and initializes a Matrix object based on six numbers that define an
* affine transformation.
*
* @param a the matrix element in the first row, first column.
* @param b the matrix element in the first row, second column.
* @param c the matrix element in the second row, first column.
* @param d the matrix element in the second row, second column.
* @param h the matrix element in the third row, first column.
* @param v the matrix element in the third row, second column.
*
* @default when none the arguments are specified, an identity matrix is created.
*/
- (id)initWithA: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
/**
* The Set method sets the elements of this matrix.
*
* @param a the matrix element in the first row, first column.
* @param b the matrix element in the first row, second column.
* @param c the matrix element in the second row, first column.
* @param d the matrix element in the second row, second column.
* @param h the matrix element in the third row, first column.
* @param v the matrix element in the third row, second column.
*/
- (void)Set: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
/**
* The Concat method updates this matrix with the product of itself and another matrix
* specified through an argument list.
*
* @param a the matrix element in the first row, first column.
* @param b the matrix element in the first row, second column.
* @param c the matrix element in the second row, first column.
* @param d the matrix element in the second row, second column.
* @param h the matrix element in the third row, first column.
* @param v the matrix element in the third row, second column.
*/
- (void)Concat: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
/**
* Transform/multiply the point (in_out_x, in_out_y) using this matrix
*/
- (PDFPoint*)Mult: (PDFPoint*)pt;
/**
* @return If this matrix is invertible, the Inverse method returns its inverse matrix.
*/
- (Matrix2D*)Inverse;
/**
* The Translate method updates this matrix with the product of itself and a
* translation matrix (i.e. it is equivalent to this.m_h += h; this.m_v += v).
*
* @param h the horizontal component of the translation.
* @param v the vertical component of the translation.
*
* @return updated this matrix
*/
- (void)Translate: (double)h v:  (double)v;
/**
* The Scale method updates this matrix with the product of itself and a scaling matrix.
* (i.e. it is equivalent to this.m_a *= h; this.m_d *= v).
* @param h the horizontal scale factor.
* @param v the vertical scale factor
*
* @return updated this matrix
*/
- (void)Scale: (double)h v:  (double)v;
/**
* Create zero matrix (0 0 0 0 0 0)
*/
+ (Matrix2D*)ZeroMatrix;
/**
* Create identity matrix (1 0 0 1 0 0)
*/
+ (Matrix2D*)IdentityMatrix;
/**
* @return A rotation matrix for a given angle.
* @param angle the angle of rotation in radians.
* Positive values specify clockwise rotation.
*/
+ (Matrix2D*)RotationMatrix: (double)angle;


@end


@interface GSChangesIterator : NSObject
{


}





- (void)Next;
- (int)Current;
- (BOOL)HasNext;
- (id)init;
@end


@interface UInt32Iterator : NSObject
{


}





- (void)Next;
- (SWIGTYPE_p_unsigned_int*)Current;
- (BOOL)HasNext;
- (id)init;
@end


@interface CharIterator : NSObject
{


}





- (void)Next;
- (TRN_chardata*)Current;
- (BOOL)HasNext;
- (id)init;
@end


/**
* Provides a generic view of a sequence of bytes.
*
* A Filter is the abstract base class of all filters. A filter is an abstraction of
* a sequence of bytes, such as a file, an input/output device, an inter-process communication
* pipe, or a TCP/IP socket. The Filter class and its derived classes provide a generic view
* of these different types of input and output, isolating the programmer from the specific
* details of the operating system and the underlying devices.
*
* Besides providing access to input/output sources Filters can be also to transform the data
* (e.g. to compress the data stream, to normalize the image data, to encrypt data, etc).
* Filters can also be attached to each other to form pipelines. For example, a filter used to
* open an image data file can be attached to a filter that decompresses the data, which is
* attached to another filter that will normalize the image data.
*
* Depending on the underlying data source or repository, filters might support only some of
* these capabilities. An application can query a stream for its capabilities by using the
* IsInputFilter() and CanSeek() properties.
*
* @note To read or write data to a filter, a user will typically use FilterReader/FilterWriter class.
* instead of using Filter methods
*
* For example:
* @code
* StdFile file("my_stream.txt", StdFile::e_read_mode);
* FilterReader reader(file);
* while (reader.Read(..)) ...
* @endcode
*/
@interface Filter : NSObject
{


}





/**
* Attaches a filter to the this filter. If this filter owns another
* filter it will be deleted. This filter then becomes the owner of the
* attached filter.
*/
- (void)AttachFilter: (Filter*)attach_filter;
/**
* Release the ownership of the attached filter. After the attached filter is
* released this filter points to NULL filter.
*
* @return - Previously attached filter.
*/
- (Filter*)ReleaseAttachedFilter;
/**
* @return - returns attached Filter or a NULL filter if no filter is attached.
*/
- (Filter*)GetAttachedFilter;
/**
* @return - returns the first filter in the chain (usually a file filter)
*/
- (Filter*)GetSourceFilter;
/**
* @return - descriptive name of the filter.
*/
- (NSString *)GetName;
/**
* @return - string representing the name of corresponding decode filter as
* it should appear in document (e.g. both ASCIIHexDecode and ASCIIHexEncode
* should return ASCIIHexDecode).
*/
- (NSString *)GetDecodeName;
/**
* @return - the size of buffer returned by Begin(). If the Size() returns 0
* end of data has been reached.
*/
- (unsigned long)Size;
/**
* Moves the Begin() pointer num_bytes forward.
*
* @param num_bytes - number of bytes to consume. num_bytes must be less than or
* equal to Size().
*/
- (void)Consume: (unsigned long)num_bytes;
/**
* @return - the number of bytes consumed since opening the filter or
*   the last Seek operation
*/
- (unsigned long)Count;
/**
* Sets a new counting point for the current filter. All subsequent Consume()
* operations will increment this counter.
*
* Make sure that the output filter is flushed before using SetCount().
*
* @return - the value of previous counter
*/
- (unsigned long)SetCount: (unsigned long)new_count;
/**
* The functions specifies the length of the data stream. The default
* implementation doesn't do anything. For some derived filters such
* as file segment filter it may be useful to override this function
* in order to limit the stream length.
*
* @param - the length of stream in bytes
*/
- (void)SetStreamLength: (unsigned long)bytes;
/**
* Forces any data remaining in the buffer to be written to input or
* output filter.
*/
- (void)Flush;
/**
* Forces any data remaining in the filter chain to the source or destination.
*/
- (void)FlushAll;
/**
* @return - boolean indicating whether this is an input filter.
*/
- (BOOL)IsInputFilter;
/**
* @return - true if the stream supports seeking; otherwise, false.
* default is to return false.
*/
- (BOOL)CanSeek;
/**
* When overridden in a derived class, sets the position within the current stream.
*
* @param offset - A byte offset relative to origin. If offset is negative,
*  the new position will precede the position specified by origin by the number
*  of bytes specified by offset. If offset is zero, the new position will be the
*  position specified by origin. If offset is positive, the new position will follow
*  the position specified by origin by the number of bytes specified by offset.
*
* @param origin - A value of type ReferencePos indicating the reference point used
* to obtain the new position
*
* @note - After each Seek() operation the number of consumed bytes (i.e.
* Count()) is set to 0.
*
* @exception - throws FilterExc if the method is not implemented in derived class
*/
- (void)Seek: (long)offset origin:  (ReferencePos)origin;
/**
* Reports the current read position in the stream relative to the stream origin.
*
* @return - The current position in the stream
* @exception - throws FilterExc if the method is not implemented in derived class
*/
- (long)Tell;
/**
* Create Filter iterator. Filter iterator similar to a regular filter. However,
* there can be only one owner of the attached filter.
*
* @note - Derived classes should make sure that there is only one owner of the
*   attached stream. Otherwise the attached stream may be deleted several times.
*
* @exception - throws an exception if the method is not implemented in the derived class
*/
- (Filter*)CreateInputIterator;
/**
* @return the file path to the underlying file stream.
* Default implementation returns empty string.
*/
- (NSString*)GetFilePath;

/**
*	Writes the entire filter, starting at current position, to
*	specified filepath.  Should only be called on an input filter.
*
*	@param path the output filepath.
*	@param append 'true' to append to existing file contents, 'false' to overwrite.
*/
- (void)WriteToFile: (NSString*)path append:  (BOOL)append;
- (id)init;

@end


/**
* ASCII85Encode filter can be used to encode any data stream
* into a stream that does not contain any binary characters.
*/
@interface ASCII85Encode : Filter





/**
* @param line_width specifies the width of the encoded line expressed in the number of characters.
*/
- (id)initWithInput_filter: (Filter*)input_filter line_width:  (int)line_width buf_sz:  (unsigned long)buf_sz;


@end


/**
* FilterReader is a utility class providing a convenient way to read data
* from an input filter (using Filter directly is not very intuitive).
*
* For example:
* @code
* StdFile file("my_stream.txt", StdFile::e_read_mode);
* FilterReader reader(file);
* while (reader.Read(...)) ...
* @endcode
*/
@interface FilterReader : NSObject
{


}





/**
* @return - the next character from the stream or EOF (-1) if the end of file is reached.
*/
- (int)Get;
/**
* @return - the next character without extracting it from the stream or
*			 or EOF (-1) if the end of file is reached.
*/
- (int)Peek;
/**
* @return - returns the number of bytes actually read and stored in buffer (buf),
*   which may be less than buf_size if the end of the stream is encountered before
*   reaching count.
*/
- (NSData*)Read: (unsigned long)buf_size;
/**
* Attaches a filter to the this FilterReader.
*/
- (void)AttachFilter: (Filter*)filter;
/**
* @return - The attached Filter or a NULL filter if no filter is attached.
*/
- (Filter*)GetAttachedFilter;
/**
* Sets the position within the current stream.
*
* @param offset - A byte offset relative to origin. If offset is negative,
*  the new position will precede the position specified by origin by the number
*  of bytes specified by offset. If offset is zero, the new position will be the
*  position specified by origin. If offset is positive, the new position will follow
*  the position specified by origin by the number of bytes specified by offset.
*
* @param origin - A value of type ReferencePos indicating the reference point used
* to obtain the new position
*
* @note - After each Seek() operation the number of consumed bytes (i.e. Count()) is set to 0.
* @exception - throws an exception if the method is not implemented in the associated filter.
*/
- (void)Seek: (long)offset origin:  (ReferencePos)origin;
/**
* Reports the current read position in the stream relative to the stream origin.
*
* @return - The current position in the stream
* @exception - throws an exception if the method is not implemented in the associated filter.
*/
- (long)Tell;
/**
* @return - the number of bytes consumed since opening the filter or
* since the last Seek operation.
*/
- (unsigned long)Count;
/**
* Forces any data remaining in the buffer to be written to input or output filter.
*/
- (void)Flush;
/**
* Forces any data remaining in the filter chain to the source or destination.
*/
- (void)FlushAll;
- (id)init;
- (id)initWithFilter: (Filter*)filter;

@end


/**
* FilterWriter is a utility class providing a convenient way to write data
* to an output filter (using Filter directly is not very intuitive).
*
* For example:
* @code
* StdFile outfile("file.dat", StdFile::e_write_mode);
* FilterWriter fwriter(outfile);
* fwriter.WriteBuffer(buf, buf_sz);
* fwriter.Flush();
* @endcode
*/
@interface FilterWriter : NSObject
{


}





/**
* Write a single character to the output stream.
* @param ch An unsigned character to write to the output stream.
*/
- (void)WriteUChar: (unsigned char)ch;
/**
* Write an integer to the output stream.
* @param num An integer to write to the output stream.
*/
- (void)WriteInt16: (short)num;
- (void)WriteUInt16: (unsigned short)num;
- (void)WriteInt32: (int)num;
- (void)WriteUInt32: (unsigned int)num;
- (void)WriteInt64: (long long)num;
- (void)WriteUInt64: (unsigned long long)num;
/**
* Write a string to the output stream.
* @param str A string to write to the output stream.
*/
- (void)WriteString: (NSString*)str;
/**
* Write the entire input stream to the output stream (i.e. to this FilterWriter).
* @param reader A FilterReader attached to an input stream.
*/
- (void)WriteFilter: (FilterReader*)reader;
/**
* Write out a null terminated 'line' followed by a end of line character
* default end of line character  is carriage return.
*/
- (void)WriteLine: (NSString *)line eol:  (char)eol;
/**
* @return - returns the number of bytes actually written to a stream. This number may
*   less than buf_size if the stream is corrupted.
*/
- (unsigned long)WriteBuffer: (NSData*)buf;
/**
* Attaches a filter to the this FilterWriter.
*/
- (void)AttachFilter: (Filter*)filter;
/**
* @return - The attached Filter or a NULL filter if no filter is attached.
*/
- (Filter*)GetAttachedFilter;
/**
* Sets the position within the current stream.
*
* @param offset - A byte offset relative to origin. If offset is negative,
*  the new position will precede the position specified by origin by the number
*  of bytes specified by offset. If offset is zero, the new position will be the
*  position specified by origin. If offset is positive, the new position will follow
*  the position specified by origin by the number of bytes specified by offset.
*
* @param origin - A value of type ReferencePos indicating the reference point used
* to obtain the new position
*
* @note - After each Seek() operation the number of consumed bytes (i.e. Count()) is set to 0.
* @exception - throws an exception if the method is not implemented in the associated filter.
*/
- (void)Seek: (long)offset origin:  (ReferencePos)origin;
/**
* Reports the current read position in the stream relative to the stream origin.
*
* @return - The current position in the stream
* @exception - throws an exception if the method is not implemented in the associated filter.
*/
- (long)Tell;
/**
* @return - the number of bytes consumed since opening the filter or
* since the last Seek operation.
*/
- (unsigned long)Count;
/**
* Forces any data remaining in the buffer to be written to input or output filter.
*/
- (void)Flush;
/**
* Forces any data remaining in the filter chain to the source or destination.
*/
- (void)FlushAll;
- (id)init;
- (id)initWithFilter: (Filter*)filter;

@end


/**
* FlateEncode filter can be used to compress any data stream
* using Flate (i.e. ZIP) compression method.
*/
@interface FlateEncode : Filter





/**
* Constructor for Flate encoder.
*
* @param input_filter the input data stream
* @param compression_level must be a number between 0 and 9: 1 gives best speed,
* 9 gives best compression, 0 gives no compression at all (the input data is simply
* copied a block at a time), -1 requests a default compromise between speed
* and compression (currently equivalent to level 6).
* @param buf_sz filter buffer size (in bytes).
*/
- (id)initWithInput_filter: (Filter*)input_filter compression_level:  (int)compression_level buf_sz:  (unsigned long)buf_sz;


@end


/**
* MappedFile is a utility class to read files on a file system. Because MappedFile file is
* derived from pdftron.Filters.Filter you can directly chain MappedFile objects to other
* 'pdftron.Filters'.
*
* MappedFile objects support random access to files using the Seek method. Seek
* allows the read/write position to be moved to any position within the file. This
* is done through a shared memory mapped chunk manager. The byte offset is relative
* to the seek reference point, which can be the beginning, the current position,
* or the end of the underlying file, as represented by the three properties of the
* Filter.ReferencePos class.
*
* MappedFile objects are thread-safe, meaning separate copies of a MappedFile can Seek
* to different locations in the file, without conflicting with one another.
*
* Disk files always support random access. At the time of construction, the CanSeek()
* property value is set to true or false depending on the underlying file type.
*
* @note .NET or Java applications should explicitly Close() files when they are not needed.
* If the files are not closed or disposed this may lead to the resource exhaustion.
*/
@interface MappedFile : Filter





/**
* Create a new instance of MappedFile class with the specified path
*/
- (id)initWithFilename: (NSString*)filename;
/**
* Check is the two file paths are equivalent (i.e. they refer to the
* same file on disc.
* @return true if the two files share the same filename, false otherwise.
*/
+ (BOOL)Equivalent: (NSString*)ph1 ph2:  (NSString*)ph2;
/**
* @return the size of the current file.
*/
- (unsigned long)FileSize;


@end


/**
* @param page_num - a page number on which to perform the redaction.
* @param bbox - the bounding box for the redaction in PDF page coordinate system.
* @param negative - if true, remove the content outside of the redaction area,
* otherwise remove the content inside the redaction area.
* @param text - optional anchor text to be placed in the redaction region.
*/
- (id)initWithPage_num: (int)page_num bbox:  (PDFRect*)bbox negative:  (BOOL)negative text:  (NSString*)text;
@interface Redaction : NSObject
{


}





- (void)setMp_imp: (SWIGTYPE_TRN_Redaction*)value;
- (SWIGTYPE_TRN_Redaction*)getMp_imp;


@end


/**
* A class containing options for ToSvg functions
*/
@interface SVGOutputOptions : NSObject
{


}





/**
* Creates an SVGOutputOptions object with default settings
*/
- (id)init;
/**
* Sets whether to embed all images
* @param embed_images if true, images will be embeded
*/
- (void)SetEmbedImages: (BOOL)embed_images;
/**
* Sets whether to disable conversion of font data to SVG
* @param no_fonts if true, font data conversion is disabled
*/
- (void)SetNoFonts: (BOOL)no_fonts;
/**
* Sets whether to disable mapping of text to public Unicode region. Instead text will be converted using a custom encoding
* @param no_unicode if true, mapping of text to public Unicode region is disabled
*/
- (void)SetNoUnicode: (BOOL)no_unicode;
/**
* Some viewers do not support the default text positioning correctly. This option works around this issue to place text correctly, but produces verbose output. This option will override SetRemoveCharPlacement
* @param individual_char_placement if true, text will be positioned correctly
*/
- (void)SetIndividualCharPlacement: (BOOL)individual_char_placement;
/**
* Sets whether to disable the output of character positions.  This will produce slightly smaller output files than the default setting, but many viewers do not support the output correctly
* @param remove_char_placement if true, the output of character positions is disabled
*/
- (void)SetRemoveCharPlacement: (BOOL)remove_char_placement;


@end


/**
* A class containing options common to ToXps and ToXod functions
*/
@interface XPSOutputCommonOptions : NSObject
{


}





/**
* Creates an XPSConvertOptions object with default settings
*/
- (id)init;
/**
* Sets whether ToXps should be run in print mode. Default is false.
* @param print_mode if true print mode is enabled
*/
- (void)SetPrintMode: (BOOL)print_mode;
/**
* The output resolution, from 1 to 1000, in Dots Per Inch (DPI) at which to render elements which cannot be directly converted. Default is 150.
* @param dpi the resolution in Dots Per Inch
*/
- (void)SetDPI: (unsigned int)dpi;
/**
* Sets whether rendering of pages should be permitted when necessary to guarantee output. Default is true.
* @param render if false rendering is not permitted under any circumstance
*/
- (void)SetRenderPages: (BOOL)render;
/**
* Sets whether thin lines should be thickened. Default is true.
* @param thicken if true then thin lines will be thickened
*/
- (void)SetThickenLines: (BOOL)thicken;


@end


/**
* A class containing options for ToXps functions
*/
@interface XPSOutputOptions : XPSOutputCommonOptions





/**
* Sets whether the output format should be open xps. Default is Microsoft xps output.
* @param openxps if true open xps output is used
*/
- (void)SetOpenXps: (BOOL)openxps;
- (id)init;

@end


/**
* A class containing options for ToXod functions
*/
@interface XODOutputOptions : XPSOutputCommonOptions





/**
* Sets whether per page thumbnails should be included in the file. Default is true.
* @param include_thumbs if true thumbnails will be included
*/
- (void)SetOutputThumbnails: (BOOL)include_thumbs;
/**
* The width and height of a square in which all thumbnails will
* be contained. Default is 400.
* @param size the maximum dimension (width or height) that
* thumbnails will have.
*/
- (void)SetThumbnailSize: (unsigned int)size;
/**
* If rendering is permitted, sets the maximum number of page elements before that page will be rendered.
* Default is 10000.
* @param element_limit the maximum number of elements before a given page will be rendered
*/
- (void)SetElementLimit: (unsigned int)element_limit;
/**
* If rendering is permitted, sets whether pages containing opacity masks should be rendered.
* This option is used as a workaround to a bug in Silverlight where opacity masks are transformed incorrectly.
* Default is false.
* @param opacity_render if true pages with opacity masks will be rendered
*/
- (void)SetOpacityMaskWorkaround: (BOOL)opacity_render;
/**
* Specifies the maximum image size in pixels. Default is 2000000.
* @param max_pixels the maximum number of pixels an image can have.
*/
- (void)SetMaximumImagePixels: (unsigned int)max_pixels;
/**
* Flatten images and paths into a single background image overlaid with
* vector text. This option can be used to improve speed on devices with
* little processing power such as iPads. Default is e_fast.
* @param flatten select which flattening mode to use.
*/
- (void)SetFlattenContent: (FlattenFlag)flatten;
/**
* Where possible output JPG files rather than PNG. This will apply to both
* thumbnails and document images. Default is true.
* @param prefer_jpg if true JPG images will be used whenever possible.
*/
- (void)SetPreferJPG: (BOOL)prefer_jpg;
/**
* Outputs rotated text as paths. This option is used as a workaround to a bug in Silverlight
* where pages with rotated text could cause the plugin to crash. Default is false.
* @param workaround if true rotated text will be changed to paths
*/
- (void)SetSilverlightTextWorkaround: (BOOL)workaround;
/**
* Choose how to output annotations. Default is e_internal_xfdf.
* @param annot_output the flag to specify the output option
*/
- (void)SetAnnotationOutput: (AnnotationOutputFlag)annot_output;
/**
* Output XOD as a collection of loose files rather than a zip archive.
* This option should be used when using the external part retriever in Webviewer. Default is false.
* @param generate if true XOD is output as a collection of loose files
*/
- (void)SetExternalParts: (BOOL)generate;
/**
* Encrypt XOD parts with AES 128 encryption using the supplied password.
* This option is not available when using SetExternalParts(true)
* @param pass the encryption password
*/
- (void)SetEncryptPassword: (NSString *)pass;
- (id)init;

@end


/**
* A class containing options common to ToHtml and ToEpub functions
*/
@interface HTMLOutputOptions : NSObject
{


}





/**
* Creates an HTMLOutputCommonOptions object with default settings
*/
- (id)init;
/**
* Use JPG files rather than PNG. This will apply to all generated images. Default is true.
* @param prefer_jpg if true JPG images will be used whenever possible.
*/
- (void)SetPreferJPG: (BOOL)prefer_jpg;
/**
* The output resolution, from 1 to 1000, in Dots Per Inch (DPI) at which to render elements which cannot be directly converted.
* Default is 150.
* @param dpi the resolution in Dots Per Inch
*/
- (void)SetDPI: (unsigned int)dpi;
/**
* Specifies the maximum image size in pixels. Default is 2000000.
* @param max_pixels the maximum number of pixels an image can have
*/
- (void)SetMaximumImagePixels: (unsigned int)max_pixels;
/**
* Switch between fixed (pre-paginated) and reflowable HTML generation. Default is false.
* @param reflow if true, generated HTML will be reflowable, otherwise, fixed positioning will be used
*/
- (void)SetReflow: (BOOL)reflow;
/**
* Set an overall scaling of the generated HTML pages. Default is 1.0.
* @param scale A number greater than 0 which is used as a scale factor. For example, calling SetScale(0.5) will reduce the HTML body of the page to half its original size, whereas SetScale(2) will double the HTML body dimensions of the page and will rescale all page content appropriately.
*/
- (void)SetScale: (double)scale;


@end


/**
* A class containing options common to ToEpub functions
*/
@interface EPUBOutputOptions : NSObject
{


}





/**
* Creates an EPUBOutputOptions object with default settings
*/
- (id)init;
/**
* Create the EPUB in expanded format. Default is false.
* @param expanded if false a single EPUB file will be generated, otherwise, the generated EPUB will be in unzipped (expanded) format
*/
- (void)SetExpanded: (BOOL)expanded;
/**
* Set whether the first content page in the EPUB uses the cover image or not. If this
* is set to true, then the first content page will simply wrap the cover image in HTML.
* Otherwise, the page will be converted the same as all other pages in the EPUB. Default is false.
* @param reuse if true the first page will simply be EPUB cover image, otherwise, the first page will be converted the same as the other pages
*/
- (void)SetReuseCover: (BOOL)reuse;


@end


/**
* Proxy settings to be used when loading content from web pages.
*
* @note These Proxy settings will only be used if type is not e_default.
*/
@interface Proxy : NSObject
{


}





/**
* Default constructor
*/
- (id)init;
/**
* Set the type of proxy to use.
*
* @param type - If e_default, use whatever the html2pdf library decides
* on. If e_none, explicitly sets that no proxy is to be used. If e_http
* or e_socks5 then the corresponding proxy protocol is used.
*/
- (void)SetType: (ProxyType)type;
/**
* Set the proxy host to use.
*
* @param host - String defining the host name, e.g. "myserver" or "www.xxx.yyy.zzz"
*/
- (void)SetHost: (NSString*)host;
/**
* Set the port number to use
*
* @param port - A valid port number, e.g. 3128.
*/
- (void)SetPort: (int)port;
/**
* Set the username to use when logging into the proxy
*
* @param username - The login name, e.g. "elbarto".
*/
- (void)SetUsername: (NSString*)username;
/**
* Set the password to use when logging into the proxy with username
*
* @param password - The password to use, e.g. "bart".
*/
- (void)SetPassword: (NSString*)password;

- (void)setMp_impl: (SWIGTYPE_TRN_HTML2PDF_Proxy*)value;
- (SWIGTYPE_TRN_HTML2PDF_Proxy*)getMp_impl;


@end


/**
* Settings that control how a web page is opened and converted to PDF.
*/
@interface WebPageSettings : NSObject
{


}





/**
* Default constructor
*/
- (id)init;
/**
* Print the background of this web page?
*
* @param background - If true background is printed.
*/
- (void)SetPrintBackground: (BOOL)background;
/**
* Print the images of this web page?
*
* @param load - If true images are printed.
*/
- (void)SetLoadImages: (BOOL)load;
/**
* Allow javascript from this web page to be run?
*
* @param enable - If true javascript's are allowed.
*/
- (void)SetAllowJavaScript: (BOOL)enable;
/**
* Allow intelligent shrinking to fit more content per page?
*
* @param enable - If true intelligent shrinking is enabled and
* the pixel/dpi ratio is non constant.
*/
- (void)SetSmartShrinking: (BOOL)enable;
/**
* Set the smallest font size allowed, e.g 9.
*
* @param size - No fonts will appear smaller than this.
*/
- (void)SetMinimumFontSize: (int)size;
/**
* Default encoding to be used when not specified by the web page.
*
* @param encoding - Default encoding, e.g. utf-8 or iso-8859-1.
*
* @note available encodings are Apple Roman, Big5, Big5-HKSCS,
* CP949, EUC-JP, EUC-KR, GB18030-0, IBM 850,
* IBM 866, IBM 874, ISO 2022-JP, ISO 8859-1 to 10, ISO 8859-13 to 16,
* Iscii-Bng, Dev, Gjr, Knd, Mlm, Ori, Pnj, Tlg, Tml, JIS X 0201, JIS X 0208,
* KOI8-R, KOI8-U, MuleLao-1, ROMAN8, Shift-JIS, TIS-620, TSCII,
* UTF-8, UTF-16, UTF-16BE, UTF-16LE, UTF-32, UTF-32BE, UTF-32LE,
* Windows-1250 to 1258, WINSAMI2.
*/
- (void)SetDefaultEncoding: (NSString*)encoding;
/**
* Url or path to user specified style sheet.
*
* @param url - URL or file path to user style sheet to be used
* with this web page.
*/
- (void)SetUserStyleSheet: (NSString*)url;
/**
* Allow Netscape and flash plugins from this web page to
* be run? Enabling will have limited success.
*
* @param enable - If true Netscape & flash plugins will be run.
*/
- (void)SetAllowPlugins: (BOOL)enable;
/**
* Controls how content will be printed from this web page.
*
* @param print - If true the print media type will be used, otherwise
* the screen media type will be used to print content.
*/
- (void)SetPrintMediaType: (BOOL)print;
/**
* Add sections from this web page to the outline and
* table of contents?
*
* @param include - If true PDF pages created from this web
* page will show up in the outline, and table of contents,
* otherwise, produced PDF pages will be excluded.
*/
- (void)SetIncludeInOutline: (BOOL)include;
/**
* HTTP authentication username to use when logging into the website.
*
* @param username - The login name to use with the server, e.g. "bart".
*/
- (void)SetUsername: (NSString*)username;
/**
* HTTP authentication password to use when logging into the website.
*
* @param password - The login password to use with the server, e.g. "elbarto".
*/
- (void)SetPassword: (NSString*)password;
/**
* Amount of time to wait for a web page to start printing after
* it's completed loading. Converter will wait a maximum of msec milliseconds
* for javascript to call window.print().
*
* @param msec - Maximum wait time in milliseconds, e.g. 1200.
*/
- (void)SetJavaScriptDelay: (int)msec;
/**
* Zoom factor to use when loading object.
*
* @param zoom - How much to magnify the web content by, e.g. 2.2.
*/
- (void)SetZoom: (double)zoom;
/**
* Allow local and piped files access to other local files?
*
* @param block - If true local files will be inaccessible.
*/
- (void)SetBlockLocalFileAccess: (BOOL)block;
/**
* Stop slow running javascript's?
*
* @param stop - If true, slow running javascript's will be stopped.
*/
- (void)SetStopSlowScripts: (BOOL)stop;
/**
* Forward javascript warnings and errors to output?
*
* @param forward - If true javascript errors and warnings will be forwarded
* to stdout and the log.
*/
- (void)SetDebugJavaScriptOutput: (BOOL)forward;
/**
* How to handle objects that failed to load?
*
* @param type - If e_abort then conversion process is aborted, if
* e_skip then the converter will not add this web page to the PDF
* output, and if e_skip then the converter will try to add this
* web page to the PDF output.
*/
- (void)SetLoadErrorHandling: (ErrorHandling)type;
/**
* Convert external links in HTML document to external
* PDF links?
*
* @param convert - If true PDF pages produced from this web page
* can have external links.
*/
- (void)SetExternalLinks: (BOOL)convert;
/**
* Should internal links in HTML document be converted
* into PDF references?
*
* @param convert - If true PDF pages produced from this web page
* will have links to other PDF pages.
*/
- (void)SetInternalLinks: (BOOL)convert;
/**
* Turn HTML forms into PDF forms?
*
* @param forms - If true PDF pages produced from this web page
* will have PDF forms for any HTML forms the web page has.
*/
- (void)SetProduceForms: (BOOL)forms;
/**
* Use this proxy to load content from this web page.
*
* @param proxy - Contains settings for proxy
*/
- (void)SetProxy: (Proxy*)proxy;

- (void)setMp_impl: (SWIGTYPE_TRN_HTML2PDF_WebPageSettings*)value;
- (SWIGTYPE_TRN_HTML2PDF_WebPageSettings*)getMp_impl;


@end


/**
* Settings for table of contents.
*/
@interface TOCSettings : NSObject
{


}





/**
* Default table of contents settings.
*/
- (id)init;
/**
* Use a dotted line when creating TOC?
*
* @param enable - Table of contents will use dotted lines.
*/
- (void)SetDottedLines: (BOOL)enable;
/**
* Create links from TOC to actual content?
*
* @param enable - Entries in table of contents will
* link to section in the PDF.
*/
- (void)SetLinks: (BOOL)enable;
/**
* Caption text to be used with TOC.
*
* @param caption - Text that will appear with the table of contents.
*/
- (void)SetCaptionText: (NSString*)caption;
/**
* Indentation used for every TOC level...
*
* @param indentation - How much to indent each level, e.g. "2"
*/
- (void)SetLevelIndentation: (int)indentation;
/**
* How much to shrink font for every level, e.g. 0.8
*
* @param shrink - Rate at which lower level entries will appear smaller
*/
- (void)SetTextSizeShrink: (double)shrink;
/**
* xsl style sheet used to convert outline XML into a
* table of content.
*
* @param style_sheet - Path to xsl style sheet to be used to generate
* this table of contents.
*/
- (void)SetXsl: (NSString*)style_sheet;

- (void)setMp_impl: (SWIGTYPE_TRN_HTML2PDF_TOCSettings*)value;
- (SWIGTYPE_TRN_HTML2PDF_TOCSettings*)getMp_impl;


@end


/**
* A class that stores image text optimization settings.
*/
@interface TextSettings : NSObject
{


}





/**
* 	create an TextSettings object with default options
*/
- (id)init;
/**
* Sets whether embedded fonts will be subset.  This
* will generally reduce the size of fonts, but will
* strip font hinting.  Subsetting is off by default.
* @param subset if true all embedded fonts will be subsetted.
*/
- (void)SubsetFonts: (BOOL)subset;
/**
* Sets whether fonts should be embedded.  This
* will generally increase the size of the file, but will
* make the file appear the same on different machines.
* Font embedding is off by default.
* @param embed if true all fonts will be embedded.
*/
- (void)EmbedFonts: (BOOL)embed;


@end


/**
* A class that stores downsampling/recompression
* settings for color and grayscale images.
*/
@interface ImageSettings : NSObject
{


}





/**
* 	create an ImageSettings object with default options
*/
- (id)init;
/**
* Sets the maximum and resampling dpi for images.
* By default these are set to 144 and 96 respectively.
* @param maximum the highest dpi of an image before
* it will be resampled
* @param resampling the image dpi to resample to if an
* image is encountered over the maximum dpi
*/
- (void)SetImageDPI: (double)maximum resampling:  (double)resampling;
/**
* Sets the output compression mode for this type of image
* The default value is e_retain
* @param mode the compression mode to set
*/
- (void)SetCompressionMode: (CompressionMode)mode;
/**
* Sets the downsample mode for this type of image
* The default value is e_default which will allow downsampling of images
* @param mode the downsample mode to set
*/
- (void)SetDownsampleMode: (DownsampleMode)mode;
/**
* Sets the quality for lossy compression modes
* from 1 to 10 where 10 is lossless (if possible)
* the default value is 5
*/
- (void)SetQuality: (unsigned int)quality;
/**
* Sets whether recompression to the specified compression
* method should be forced when the image is not downsampled.
* By default the compression method for these images
* will not be changed.
* @param force if true the compression method for all
* images will be changed to the specified compression mode
*/
- (void)ForceRecompression: (BOOL)force;
/**
* Sets whether image changes that grow the
* PDF file should be kept.  This is off by default.
* @param force if true all image changes will be kept.
*/
- (void)ForceChanges: (BOOL)force;


@end


/**
* A class that stores image downsampling/recompression
* settings for monochrome images.
*/
@interface MonoImageSettings : NSObject
{


}





/**
* 	create an MonoImageSettings object with default options
*/
- (id)init;
/**
* Sets the maximum and resampling dpi for monochrome images.
* By default these are set to 144 and 96 respectively.
* @param maximum the highest dpi of an image before
* it will be resampled
* @param resampling the image dpi to resample to if an
* image is encountered over the maximum dpi
*/
- (void)SetImageDPI: (double)maximum resampling:  (double)resampling;
/**
* Sets the output compression mode for monochrome images
* The default value is e_jbig2
* @param mode the compression mode to set
*/
- (void)SetCompressionMode: (MonoCompressionMode)mode;
/**
* Sets the downsample mode for monochrome images
* The default value is e_default
* @param mode the compression mode to set
*/
- (void)SetDownsampleMode: (MonoDownsampleMode)mode;
/**
* Sets whether recompression to the specified compression
* method should be forced when the image is not downsampled.
* By default the compression method for these images
* will not be changed.
* @param force if true the compression method for all
* images will be changed to the specified compression mode
*/
- (void)ForceRecompression: (BOOL)force;
/**
* Sets whether image changes that grow the
* PDF file should be kept.  This is off by default.
* @param force if true all image changes will be kept.
*/
- (void)ForceChanges: (BOOL)force;


@end


/**
* A class that stores settings for the optimizer
*/
@interface OptimizerSettings : NSObject
{


}





/**
* 	create an OptimizerSettings object with default options
*/
- (id)init;
/**
* updates the settings for color image processing
*/
- (void)SetColorImageSettings: (ImageSettings*)settings;
/**
* updates the settings for grayscale image processing
*/
- (void)SetGrayscaleImageSettings: (ImageSettings*)settings;
/**
* updates the settings for monochrome image processing
*/
- (void)SetMonoImageSettings: (MonoImageSettings*)settings;
/**
* updates the settings for text processing
*/
- (void)SetTextSettings: (TextSettings*)settings;
- (void)setM_color_image_settings: (ImageSettings*)value;
- (ImageSettings*)getM_color_image_settings;
- (void)setM_grayscale_image_settings: (ImageSettings*)value;
- (ImageSettings*)getM_grayscale_image_settings;
- (void)setM_mono_image_settings: (MonoImageSettings*)value;
- (MonoImageSettings*)getM_mono_image_settings;
- (void)setM_text_settings: (TextSettings*)value;
- (TextSettings*)getM_text_settings;


@end


/**
* A class representing predominant text style associated with a
* given Line, a Word, or a Glyph. The class includes information about
* the font, font size, font styles, text color, etc.
*/
@interface TextExtractorStyle : NSObject
{


}





/**
* @return low-level PDF font object. A high level font object can
* be instantiated as follows:
* In C++: pdftron.PDF.Font f(style.GetFont())
* In C#: pdftron.PDF.Font f = new pdftron.PDF.Font(style.GetFont());
*/
- (Obj*)GetFont;
/**
* @return the font name used to draw the selected text.
*/
- (NSString*)GetFontName;
/**
* @return The font size used to draw the selected text as it
* appears on the output page.
* @note Unlike the 'font size' in the graphics state (pdftron.PDF.GState)
* the returned font size accounts for the effects CTM, text matrix,
* and other graphics state attributes that can affect the appearance of
* text.
*/
- (double)GetFontSize;
/**
* @return The weight (thickness) component of the fully-qualified font name
* or font specifier. The possible values are 100, 200, 300, 400, 500, 600, 700,
* 800, or 900, where each number indicates a weight that is at least as dark as
* its predecessor. A value of 400 indicates a normal weight; 700 indicates bold.
* Note: The specific interpretation of these values varies from font to font.
* For example, 300 in one font may appear most similar to 500 in another.
*/
- (int)GetWeight;
/**
* @return true if glyphs have dominant vertical strokes that are slanted.
* @note the return value corresponds to the state of 'italic' flag in the 'Font Descriptor'.
*/
- (BOOL)IsItalic;
/**
* @return true if glyphs have serifs, which are short strokes drawn at an angle on the top
* and bottom of glyph stems.
* @note the return value corresponds to the state of 'serif' flag in the 'Font Descriptor'.
*/
- (BOOL)IsSerif;
/**
* @return text color in RGB color space.
*/
- (NSMutableArray*)GetColor;
- (void)setMp_style: (SWIGTYPE_TRN_TextExtractorStyle*)value;
- (SWIGTYPE_TRN_TextExtractorStyle*)getMp_style;
- (id)init;

@end


@interface Highlight : NSObject
{


}




- (void)setPage_num: (int)value;
- (int)getPage_num;
- (void)setPosition: (int)value;
- (int)getPosition;
- (void)setLength: (int)value;
- (int)getLength;
- (id)init;
- (id)initWithPg: (int)pg pos:  (int)pos len:  (int)len;
@end


/**
* BorderStyle structure specifies the characteristics of the annotation's border.
* The border is specified as a rounded rectangle.
*/
@interface BorderStyle : NSObject
{


}






/**
* Creates a new border style with given parameters.
* @param s The border style.
* @param b_width The border width expressed in the default user space.
* @param b_hr The horizontal corner radius expressed in the default user space.
* @param b_vr The vertical corner radius expressed in the default user space.
* @param b_dash An array of numbers defining a pattern of dashes and gaps to be used
* in drawing the border. The dash array is specified in the same format as in the line
* dash pattern parameter of the graphics state except that the phase is assumed to be 0.
*
* @note If the corner radii are 0, the border has square (not rounded) corners; if
* the border width is 0, no border is drawn.
*/
- (id)initWithS: (BdStyle)s b_width:  (double)b_width b_hr:  (double)b_hr b_vr:  (double)b_vr;
/**
* @return the border style.
*/
- (BdStyle)GetStyle;
/**
* Sets the border style.
*/
- (void)SetStyle: (BdStyle)style;
/**
* @return horizontal corner radius.
*/
- (double)GetHR;
/**
* Sets horizontal corner radius.
*/
- (void)SetHR: (double)hr;
/**
* @return vertical corner radius.
*/
- (double)GetVR;
/**
* Sets vertical corner radius.
*/
- (void)SetVR: (double)vr;
/**
* @return the border width.
*/
- (double)GetWidth;
/**
* Sets the border width
*/
- (void)SetWidth: (double)width;
/**
* @return the border dash pattern.
* @see BorderStyle()
*/
- (NSMutableArray*)GetDash;
/**
* Sets the border dash pattern.
* @see BorderStyle()
*/
- (void)SetDash: (NSMutableArray*)dash;

- (id)initWithS: (BdStyle)s b_width:  (double)b_width b_hr:  (double)b_hr b_vr:  (double)b_vr b_dash:  (NSMutableArray*)b_dash;

@end


/**
* SDFDoc is a low-level document representing a graph of SDF::Obj nodes that
* can be used to build higher-level document models such as PDF (Portable Document
* Format) or FDF (Forms Document Format).
*
* SDFDoc brings together document security, document utility methods, and all SDF
* objects.
*
* A SDF document can be created from scratch using a default constructor:
*
* SDFDoc mydoc;
* Obj trailer = mydoc.GetTrailer();
*
* SDF document can be also created from an existing file (e.g. an external PDF document):
* @code
* SDFDoc mydoc("in.pdf");
* Obj trailer = mydoc.GetTrailer();
* @endcode
* or from a memory buffer or some other Filter/Stream such as a HTTP Filter connection:
*
* @code
* MemoryFilter memory = ....
* SDFDoc mydoc(memory);
* Obj trailer = mydoc.GetTrailer();
* @endcode
*
* Finally SDF document can be accessed from a high-level PDF document as follows:
*
* @code
* PDFDoc doc("in.pdf");
* SDFDoc& mydoc = doc.GetSDFDoc();
* Obj trailer = mydoc.GetTrailer();
* @endcode
*
* Note that the examples above used doc.GetTrailer() in order to access document
* trailer, the starting SDF object (root node) in every document. Following the trailer
* links, it is possible to visit all low-level objects in a document (e.g. all pages,
* outlines, fonts, etc).
*
* SDFDoc also provides utility methods used to import objects and object collections
* from one document to another. These methods can be useful for copy operations between
* documents such as a high-level page merge and document assembly.
*/
@interface SDFDoc : NSObject
{


}





/**
* Default constructor. Creates a new document.
* The new document contains only trailer and Info dictionary.
* To build the rest of the document get document's root dictionary using GetTrailer() and
* populate it with new key/value pairs.
*/
- (id)init;
/**
* Open a SDF/Cos document from a file.
*
* @param filepath - path name to the file.
*
* @note Make sure to call InitStdSecurityHandler() or InitSecurityHandler() after SDFDoc(...)
* in case the document is encrypted.
*/
- (id)initWithFilepath: (NSString*)filepath;
/**
* Open a SDF/Cos document from a Filter (i.e. a data stream) object.
*
* @param stream - input stream containing a serialized document. The input stream may be a
* random-access file, memory buffer, slow HTTP connection etc.
*
* @note if the input stream doesn't support Seek() operation the document will load whole
* data stream in memory before parsing. In case of linearized PDF, the document may be parsed
* on-the-fly while it is being loaded in memory. Note that since StdFile implements Seek()
* interface, the document does not have to be fully in memory before it is used.
*
* @note Make sure to call InitStdSecurityHandler() or InitSecurityHandler() after SDFDoc(...)
* in case the document is encrypted.
*/
- (id)initWithStream: (Filter*)stream;
/**
* Open a SDF/Cos document from a memory buffer.
*
* @note the document should be fully loaded in the memory buffer.
* @note the buffer ownership is not transfered to the document so the user should
* clean-up if necessary.
*
* @param buf - a memory buffer containing the serialized document
* @param buf_size - the size of memory buffer.
*
* @note Make sure to call InitStdSecurityHandler() or InitSecurityHandler() after SDFDoc(...)
* in case the document is encrypted.
*/
- (id)initWithBuf: (NSData*)buf buf_size:  (unsigned long)buf_size;
/**
*	Close SDFDoc
*/
- (void)Close;
/**
* @return true if the document is/was originally encrypted false otherwise.
*/
- (BOOL)IsEncrypted;
/**
* Initializes document's SecurityHandler. This version of InitSecurityHandler()
* works with Standard and Custom PDF security and can be used in situations where
* the password is obtained dynamically via user feedback. See EncTest sample for
* example code.
*
* This function should be called immediately after an encrypted
* document is opened. The function does not have any side effects on
* documents that are not encrypted.
*
* If the security handler was successfully initialized it can be later obtained
* using GetSecurityHandler() method.
*
* @exception An exception is thrown if the matching handler for document's
* security was not found in the global SecurityManager. In this case, you
* need to register additional custom security handlers with the global
* SecurityManager (using SecurityManagerSingleton).
*
* @return true if the SecurityHandler was successfully initialized (this
* may include authentication data collection, verification etc.),
* false otherwise.
*
* @param custom_data An optional parameter used to specify custom data
* that should be passed in SecurityHandler::Initialize() callback.
*/
- (BOOL)InitSecurityHandler;
/**
* Initializes document's SecurityHandler using the supplied
* password. This version of InitSecurityHandler() assumes that
* document uses Standard security and that a password is specified
* directly.
*
* This function should be called immediately after an encrypted
* document is opened. The function does not have any side effects on
* documents that are not encrypted.
*
* If the security handler was successfully initialized, it can be later
* obtained using GetSecurityHandler() method.
*
* @return true if the given password successfully unlocked the document,
* false otherwise.
*
* @exception An exception is thrown if the document's security Filter is
* not 'Standard'. In this case, you need to register additional custom
* security handlers with the global SecurityManager (SecurityManagerSingleton).
*
* @param password Specifies the password used to open the document without
* any user feedback. If you would like to dynamically obtain the password,
* you need to derive a custom class from StdSecurityHandler() and use
* InitSecurityHandler() without any parameters. See EncTest sample
* for example code.
*
* @param password_len An optional parameter used to specify the size of
* the password buffer, in bytes. If the 'password_sz' is 0, or if the parameter
* is not specified, the function assumes that the string is null terminated.
*/
- (BOOL)InitStdSecurityHandler: (NSString *)password password_sz:  (int)password_sz;
/**
* @return - true if document was modified, false otherwise
*/
- (BOOL)IsModified;
/**
* @return - true if the document requires full save.
*/
- (BOOL)IsFullSaveRequired;
/**
* @return - A dictionary representing the root of the document (i.e.
* a document trailer dictionary)
*/
- (Obj*)GetTrailer;
/**
* @param - obj_num object number of the object to retrieve.
* @return - the latest version of the object matching specified object number.
* @exception - exception is thrown if the object is not found.
*/
- (Obj*)GetObj: (unsigned int)obj_num;
/**
* @param obj - an object to import.
* @param deep_copy - a boolean indicating whether to perform a deep or shallow copy.
* In case of shallow copy all indirect references will be set to null.
*
* If the object belongs to a document the function will perform deep or shallow
* clone depending whether deep_copy flag was specified.
*
* If the object does not belong to any document ImportObj does not take the
* object ownership. ImportObj copies the source object and it is users
* responsibility to delete free objects.
*
* @return - a pointer to the root indirect object in this document
*/
- (Obj*)ImportObj: (Obj*)obj deep_copy:  (BOOL)deep_copy;
/**
* The function performs a deep copy of all objects specified in the 'obj_list'.
* If objects in the list are directly or indirectly referring to the same object/s,
* only one copy of the shared object/s will be copied. Therefore, unlike repeated calls
* to ImportObj, this method will import only one copy of shared objects (objects
* representing an intersection of graphs specified through 'obj_list' of root pointers.
*
* @note - All object in the import list must belong to the same source document.
* @note - The function does not perform the shallow copy since ImportObj() can be used instead.
*
* @param obj - a list of root objects to import. All directly or indirectly objects will be
* imported as well.
* @return - a list of imported root objects in this document
*/
- (VectorObj*)ImportObjs: (VectorObj*)obj_list;
/**
* @return - The size of cross reference table
*/
- (unsigned int)XRefSize;
/**
* Removes 'marked' flag from all objects in cross reference table.
*/
- (void)ClearMarks;
/**
* Saves the document to a file.
*
* If a full save is requested to the original path, the file is saved to a file
* system-determined temporary file, the old file is deleted, and the temporary file
* is renamed to path.
*
* A full save with remove unused or linearization option may re-arrange object in
* the cross reference table. Therefore all pointers and references to document objects
* and resources should be re acquired in order to continue document editing.
*
* In order to use incremental save the specified path must match original path and
* e_incremental flag bit should be set.
*
* @param path - The full path name to which the file is saved.
* @param flags - A bit field composed of an OR of the SDFDoc::SaveOptions values.
* @param progress - A pointer to the progress interface. NULL if progress tracking is not required.
* @param header - File header. A new file header is set only during full save.
*
* @exception - if the file can't be opened for saving or if there is a problem during Save
*	an Exception object will be thrown.
*/
- (void)SaveSDFDocToFile: (NSString*)path flags:  (unsigned int)flags header:  (NSString *)header;
/**
* Saves the document to a memory buffer.
*
* @param out_buf a pointer to the buffer containing the serialized version of the
* document. (C++ Note) The buffer is owned by a document and the client doesn't need to
* do any initialization or cleanup.
* @param out_buf_size the size of the serialized document (i.e. out_buf) in bytes.
*
* @param flags - A bit field composed of an OR of the SDFDoc::SaveOptions values.
* Note that this method ignores e_incremental flag.
* @param progress - A pointer to the progress interface. NULL if progress tracking is not required.
* @param header - File header. A new file header is set only during full save.
*
* @exception - if there is a problem during Save an Exception object will be thrown.
*/
- (NSData*)SaveSDFDocToBuf: (unsigned int)flags header:  (NSString *)header;
/**
* Saves the document to a stream.
*
* @param stream The output stream where to write data.
* @param flags - A bit field composed of an OR of the SDFDoc::SaveOptions values.
* @param progress - A pointer to the progress interface. NULL if progress tracking is not required.
* @param header - File header. A new file header is set only during full save. See also GetHeader()
*
* @exception - if there is a problem during Save an Exception object will be thrown.
*/
- (void)Save: (Filter*)stream flags:  (unsigned int)flags header:  (NSString *)header;
/**
* @return the header string identifying the document version to which the file conforms.
* For a file conforming to PDF version 1.4, the header should be %PDF-1.4.
* In general header strings have the following syntax: %AAA-N.n where AAA identifies
* document specification (such as PDF, FDF, PJTF etc), N is the major version and
* n is the minor version. The new header string can be set during a full save (see SDFDoc::Save()).
* For a document that is not serialized the function returns an empty string.
*/
- (NSString *)GetHeader;
/**
* @return Currently selected SecurityHandler.
*
* @note InitSecurityHandler() should be called before GetSecurityHandler()
* in order to initialize the handler.
*
* @note Returned security handler can be modified in order to change the
* security settings of the existing document. Changes to the current handler
* will not invalidate the access to the original file and will take effect
* during document Save().
*
* @note If the security handler is modified, document will perform a full save
* even if e_incremental was given as a flag in Save() method.
*/
- (SecurityHandler*)GetSecurityHandler;
/**
* The function sets a new SecurityHandler as the current security handler.
*
* @param - new SecurityHandler
*
* @note Setting a new security handler will not invalidate the access to
* the original file and will take effect during document Save().
*
* @note If the security handler is modified, document will perform a full save
* even if e_incremental was given as a flag in Save() method.
*/
- (void)SetSecurityHandler: (SecurityHandler*)handler;
/**
* This function removes document security.
*/
- (void)RemoveSecurity;
/**
* Sometimes it is desirable to modify all indirect references to a given
* indirect object. It would be inefficient to manually search for all
* indirect references to a given indirect object.
*
* A more efficient and less error prone method is to replace the indirect
* object in the cross reference table with a new object. This way the object
* that is referred to is modified (or replaced) and indirect references do
* not have to be changed.
*
* @param - obj_num1 & obj_num2 are object numbers of objects to be swapped.
*
* @exception the function throws exception in case the swap can't be
* performed.
*/
- (void)Swap: (unsigned int)obj_num1 obj_num2:  (unsigned int)obj_num2;
/**
* The following list of methods is used to create SDF/Cos indirect objects.
*
* Unlike direct objects, indirect objects can be referenced by more than one
* object (i.e. indirect objects they can be shared).
*
* @note In C++ doc.CreateIndirect???(...) is equivalent to ???::CreateIndirect(...).
*/
- (Obj*)CreateIndirectName: (NSString *)name;
- (Obj*)CreateIndirectArray;
- (Obj*)CreateIndirectBool: (BOOL)value;
- (Obj*)CreateIndirectDict;
- (Obj*)CreateIndirectNull;
- (Obj*)CreateIndirectNumber: (double)value;
- (Obj*)CreateIndirectString: (NSData*)value size:  (unsigned int)size;
- (Obj*)CreateIndirectStringWithStr: (NSString*)str;
/**
* @note After calling the following methods the filter object is invalidated and should not be used
*/
- (Obj*)CreateIndirectStreamWithFilterReader: (FilterReader*)data filter_chain:  (Filter*)filter_chain;
- (Obj*)CreateIndirectStream: (FilterReader*)data;
- (Obj*)CreateIndirectStreamWithbuf: (NSString *)data data_size:  (unsigned long)data_size filter_chain:  (Filter*)filter_chain;
/**
* Call this function to determine whether the document is represented in
* linearized (fast web view) format.
*
* @return - true if document is stored in fast web view format, false otherwise.
*
* @note any changes to the document can invalidate linearization. The function will
* return 'true' only if the original document is linearized and if it is not
* modified.
*
* In order to provide good performance over relatively slow communication links,
* PDFNet can generate PDF documents with linearized objects and hint tables that
* can allow a PDF viewer application to download and view one page of a PDF file
* at a time, rather than requiring the entire file (including fonts and images) to
* be downloaded before any of it can be viewed.
*
* To save a document in linearized (fast web view) format you only need to pass
* 'SDFDoc.SaveOptions.e_linearized' flag in the Save method.
*/
- (BOOL)IsLinearized;
/**
* Returns document's initial linearization dictionary if it is available.
*
* @return - the linearization dictionary of the original document or NULL
* if the dictionary is not available.
*/
- (Obj*)GetLinearizationDict;
/**
* Returns document's initial linearization hint stream if it is available.
*
* @return - the linearization hint stream of the original document or NULL
* if the hint stream is not available.
*/
- (Obj*)GetHintStream;
/**
* Locks the document to prevent competing threads from accessing the document
* at the same time. Threads attempting to access the document will wait in
* suspended state until the thread that owns the lock calls doc.Unlock().
*/
- (void)Lock;
/**
* Removes the lock from the document.
*/
- (void)Unlock;
/**
* Try locking the document, waiting no longer than specified number of milliseconds.
* @return true if the document is locked for multi-threaded access, false otherwise.
*/
- (BOOL)TryLock: (int)milliseconds;
/**
* Locks the document to prevent competing write threads (using Lock()) from accessing the document
* at the same time. Other reader threads however, will be allowed to access the document.
* Threads attempting to obtain write access to the document will wait in
* suspended state until the thread that owns the lock calls doc.UnlockRead().
* Note: To avoid deadlocks obtaining a write lock while holding
* a read lock is not permitted and will throw an exception. If this situation is encountered
* please either unlock the read lock before the write lock is obtained
* or acquire a write lock (rather than read lock) in the first place.
*/
- (void)LockRead;
/**
* Removes the lock from the document.
*/
- (void)UnlockRead;
/**
* Try locking the document, waiting no longer than specified number of milliseconds.
* @return true if the document is locked for multi-threaded access, false otherwise.
*/
- (BOOL)TryLockRead: (int)milliseconds;
/**
* @return The filename of the document if the document is loaded from disk,
* or empty string if the document is not yet saved or is loaded from a memory
* buffer.
*/
- (NSString*)GetFileName;
/**
* A document uses a temporary file which is used to cache the contents
* of any new stream object created in the document (that is the default behavior).
* Use this function to enable to disable this feature dynamically.
*/
- (void)EnableDiskCaching: (BOOL)use_cache_flag;





@end


/**
* Obj is a concrete class for all SDF/Cos objects. Obj hierarchy implements the
* composite design pattern. As a result, you can invoke a member function of any
* 'derived' object through Obj interface. If the member function is not supported
* (e.g. if you invoke Obj::GetNumber() on a boolean object) an Exception will be
* thrown.
*
* You can use GetType() or obl.Is???() member functions to find out type-information at
* run time, however most of the time the type can be inferred from the PDF specification.
* Therefore when you call Doc::GetTrailer() you can assume that returned object is
* a dictionary. If there is any ambiguity use Is???() methods.
*
* Objects can't be shared across documents, however you can use Doc::ImportObj()
* to copy objects from one document to another.
*
* Objects can be shared within a document provided that they are created as indirect.
* Indirect objects are the ones that are referenced in cross-reference table.
* To create an object as indirect use doc.CreateIndirect???() (where ? is the
* Object type).
*/
@interface Obj : NSObject
{


}





/**
* @return the object type.
* @note this method can be invoked on any Obj.
*/
- (ObjType)GetType;
/**
* @return true if this is a Bool object, false otherwise.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsBool;
/**
* @return true if this is a Number object, false otherwise.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsNumber;
/**
* @return true if this is a Null object, false otherwise.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsNull;
/**
* @return true if this is a Str (String) object, false otherwise.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsString;
/**
* @return true if this is Name, false otherwise.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsName;
/**
* @return true if this is Indirect object (i.e. object referenced in the
* cross-reference table), false otherwise.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsIndirect;
/**
* @return true if this is a Container (a dictionary, array, or a stream),
* false otherwise.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsContainer;
/**
* @return true if this is a dictionary (i.e. Dict), false otherwise.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsDict;
/**
* @return true if this is an Array, false otherwise.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsArray;
/**
* @return true if this is a Stream, false otherwise.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsStream;
/**
* @return the document to which this object belongs.
* @note this method can be invoked on any Obj.
*/
- (SDFDoc*)GetDoc;
/**
* The function writes the Obj to the output stream
* @param stream - the input stream where the Obj will be written
* @note this method can be invoked on any Obj.
*/
- (void)Write: (FilterWriter*)stream;
/**
* @return the 'size' of the object. The definition of 'size' depends on
* the object type. In particular:
*  - For a dictionary or a stream object, the method will return the
*    number of key/value pairs in the dictionary.
*  - For an array object the method will return the number of Obj
*    entries in the array.
*  - For a string object the method will return the number of bytes
*    in the string buffer.
*  - For any other object the method will always return 1.
*
* @note this method can be invoked on any Obj.
*/
- (unsigned long)Size;
/**
* @return object number. If this is not an Indirect object, object number of
* a containing indirect object is returned.
* @note this method can be invoked on any Obj.
*/
- (unsigned int)GetObjNum;
/**
* @return generation number. If this is not an Indirect object, generation number of
* a containing indirect object is returned.
* @note this method can be invoked on any Obj.
*/
- (unsigned short)GetGenNum;
/**
* @return object offset from the beginning of the file. If this is not an Indirect object,
* offset of a containing indirect object is returned.
* @note this method can be invoked on any Obj.
*/
- (unsigned long)GetOffset;
/**
* @return true if the object is in use or is marked as free.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsFree;
/**
* Set the object mark. Mark is a boolean value that can be associated with every
* indirect object. This is especially useful when and object graph should be
* traversed and an operation should be performed on each node only once.
* @note this method can be invoked on any Obj.
*/
- (void)SetMark: (BOOL)mark;
/**
* @return true if the object is marked.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsMarked;
/**
* @return true if the object is loaded in memory.
* @note this method can be invoked on any Obj.
*/
- (BOOL)IsLoaded;
/**
* @return true if this is a valid object, false otherwise. If the function returns
* false then the underlying SDF/Cos object is null or is not valid.
*/
- (BOOL)IsValid;
/**
* @return bool value if this is Bool.
* @exception Exception is thrown if the object is not Obj::Type::e_bool
*/
- (BOOL)GetBool;
/**
* @param b - bool value used to set Bool object.
* @exception An Exception is thrown if this is not a Obj::Type::e_bool
*/
- (void)SetBool: (BOOL)b;
/**
* @return value, if this is Number.
* @exception An Exception is thrown if the object is not a Obj::Type::e_number
*/
- (double)GetNumber;
/**
* @param n - value used to set Number object.
* @exception An Exception is thrown if this is not a Obj::Type::e_number
*/
- (void)SetNumber: (double)n;
/**
* @return a pointer to the string buffer. Please note that the string may not
* be NULL terminated and that it may not be represented in ASCII or Unicode
* encoding. For more information on SDF/Cos String objects, please refer to
* section 3.2.3 'String Objects' in PDF Reference Manual.
*
* @note if SDF/Cos String object is represented as 'PDF Text' (Section 3.8.1
* 'Text Strings' in PDF Reference) you can use GetAsPDFText method to obtain
* Unicode representation of the string.
*
* @note use Size() member function in order to obtain the number of bytes in string buffer.
*
* @exception Exception is thrown if this is not a Obj::Type::e_string.
*/
- (NSData*)GetBuffer;
/**
* Convert the SDF/Cos String object to 'PDF Text String' (a Unicode string).
*
* PDF Text Strings are not used to represent page content, however they
* are used in text annotations, bookmark names, article names, document
* information etc. These strings are encoded in either PDFDocEncoding or
* Unicode character encoding. For more information on PDF Text Strings,
* please refer to section 3.8.1 'Text Strings' in PDF Reference.
*
* @note Not all SDF/Cos String objects are used to represent 'PDF Text'.
* PDF Reference indicates (on a case by case basis ) where an SDF/Cos String
* object can be used as 'PDF Text'.
*
* @exception An Exception is thrown if this is not a Obj::Type::e_string.
*/
- (NSString*)GetAsPDFText;
/**
* Sets the string object value.
*
* @param value - character buffer.
* @param size - the size of character buffer.
* @exception An Exception is thrown if this is not a Obj::Type::e_string
*/
- (void)SetString: (NSData*)value size:  (unsigned long)size;
/**
* Sets the string object value.
* @param str - A Unicode string value.
* @exception An Exception is thrown if this is not a Obj::Type::e_string
*/
- (void)SetStringWithStr: (NSString*)str;
/**
* @return string representing the Name object.
* @exception An Exception is thrown if this is not a Obj::Type::e_name
*/
- (NSString *)GetName;
/**
* @param name - value used to set Name object.
* @exception An Exception is thrown if this is not a Obj::Type::e_name
*/
- (void)SetName: (NSString *)name;
/**
* @return an iterator that addresses the first element in the dictionary.
* @exception An Exception is thrown if this is not a dictionary object (Dict).
*
* Sample code used to traverse all entries in the dictionary:
* @code
*  DictIterator itr = dict.GetDictIterator();
*  while (itr.HasNext()) {
*      Obj key = itr.Key();
*      Obj value = itr.Value();
*      // ...
*      itr.Next()
*   }
* @endcode
*/
- (DictIterator*)GetDictIterator;
/**
* Search the dictionary for a given key.
*
* @param key - a key to search for in the dictionary
*
* @return The iterator to the matching key/value pair or invalid iterator
* (i.e. itr.HasNext()==fase) if the if the dictionary does not contain the given key.
*
* @note A dictionary entry whose value is Obj::Null is equivalent to an absent entry.
* @exception Exception is thrown if this is not a dictionary or a stream
*
* Sample code used to search a dictionary for a given key:
* @code
*  DictIterator itr = info_dict.Find("Info");
*  if (itr.HasNext()) {
*    Obj info = itr.Value();
*    if (info.IsDict())
*      info.PutString("Producer", "PDFTron PDFNet SDK");
* }
* @endcode
*/
- (DictIterator*)Find: (NSString *)key;
/**
* Search the dictionary for a given key.
*
* @param key - a key to search for in the dictionary
* @return NULL if the dictionary does not contain the specified key.
* Otherwise return the corresponding value.
* @note A dictionary entry whose value is Obj::Null is equivalent to an absent entry.
* @exception Exception is thrown if this is not a dictionary or a stream
*/
- (Obj*)FindObj: (NSString *)key;
/**
* Search the dictionary for a given key and throw an exception if the key is not found.
*
* @param key - a key to search for in the dictionary
* @return Obj::Null object if the value matching specified key is a Obj::Null object.
* @return otherwise return the iterator to the matching key/value pair.
* @exception An Exception is thrown if the dictionary does not contain the specified key.
* @exception An Exception is thrown if this is not a Obj::Type::e_dict or a stream.
*/
- (DictIterator*)Get: (NSString *)key;
/**
* Inserts a <key, Obj::Type::e_name> pair in the dictionary.
*
* @param key The key of the value to set.
* @param name The value of the Obj::Type::e_name object to be inserted into
* the dictionary.
*
* @return A newly created name object.
* @exception An Exception is thrown if this is not a dictionary or a stream object.
* @note If a dictionary already contains an entry with the same key, the old entry
* will be deleted and all DictIterators to this entry will be invalidated.
*/
- (Obj*)PutName: (NSString *)key name:  (NSString *)name;
/**
* Inserts a <key, Obj::Type::e_array> pair in the dictionary.
*
* @param key The key of the value to set.
* @return A newly created array object.
*
* @exception An Exception is thrown if this is not a dictionary or a stream object.
*
* @note If a dictionary already contains an entry with the same key, the old entry
* will be deleted and all DictIterators to this entry will be invalidated.
*/
- (Obj*)PutArray: (NSString *)key;
/**
* Inserts a <key, Obj::Type::e_bool> pair in the dictionary.
*
* @param key The key of the value to set.
* @param value The value of the Obj::Type::e_bool object to be inserted into
* the dictionary.
*
* @return A newly created boolean object.
* @exception An Exception is thrown if this is not a dictionary or a stream object.
* @note If a dictionary already contains an entry with the same key, the old entry
* will be deleted and all DictIterators to this entry will be invalidated.
*/
- (Obj*)PutBool: (NSString *)key value:  (BOOL)value;
/**
* Inserts a <key, Obj::Type::e_dict> pair in the dictionary.
*
* @param key The key of the value to set.
*
* @return A newly created dictionary.
* @exception An Exception is thrown if this is not a dictionary or a stream object.
* @note If a dictionary already contains an entry with the same key, the old entry
* will be deleted and all DictIterators to this entry will be invalidated.
*/
- (Obj*)PutDict: (NSString *)key;
/**
* Inserts a <key, Obj::Type::e_number> pair in the dictionary.
*
* @param key The key of the value to set.
* @param value The value of the Obj::Type::e_number object to be inserted into
* the dictionary.
*
* @return A newly created number object.
* @exception An Exception is thrown if this is not a dictionary or a stream object.
* @note If a dictionary already contains an entry with the same key, the old entry
* will be deleted and all DictIterators to this entry will be invalidated.
*/
- (Obj*)PutNumber: (NSString *)key value:  (double)value;
/**
* Inserts a <key, Obj::Type::e_string> pair in the dictionary.
*
* @param key The key of the value to set.
* @param value The value of the Obj::Type::e_string object to be inserted into
* the dictionary.
*
* @return A newly created string object.
* @exception An Exception is thrown if this is not a dictionary or a stream object.
* @note If a dictionary already contains an entry with the same key, the old entry
* will be deleted and all DictIterators to this entry will be invalidated.
*/
- (Obj*)PutString: (NSString *)key value:  (NSString *)value;
/**
* Inserts a <key, Obj::Type::e_string> pair in the dictionary.
*
* @param key The key of the value to set.
* @param value The buffer used to set the value of the Obj::Type::e_string
* object to be inserted into the dictionary.
* @param size The number of bytes to copy from the 'value' buffer parameter.
*
* @return A newly created string object.
* @exception An Exception is thrown if this is not a dictionary or a stream object.
* @note If a dictionary already contains an entry with the same key, the old entry
* will be deleted and all DictIterators to this entry will be invalidated.
*/
- (Obj*)PutStringWithSize: (NSString *)key value:  (NSString *)value size:  (int)size;
/**
* Inserts a <key, Obj::Type::e_string> pair in the dictionary.
*
* @param key The key of the value to set.
* @param value The value of the Obj::Type::e_string object to be inserted into
* the dictionary.
* @note PutText will create the string object as a 'PDF Text' object.
*
* @return A newly created string object.
* @exception An Exception is thrown if this is not a dictionary or a stream object.
* @note If a dictionary already contains an entry with the same key, the old entry
* will be deleted and all DictIterators to this entry will be invalidated.
*/
- (Obj*)PutText: (NSString *)key value:  (NSString*)value;
/**
* Inserts a <key, Obj::Type::e_null> pair in the dictionary.
* @param key The key of the value to set.
* @exception An Exception is thrown if this is not a dictionary or a stream object.
* @note The effect of calling this method is essentially the same as dict.Erase(key) .
*/
- (void)PutNull: (NSString *)key;
/**
* Inserts a <key, Obj> pair in the dictionary.
* @param key The key of the value to set.
* @param obj The value to be inserted into the dictionary. If 'obj' is
* indirect (i.e. is a shared) object it will be inserted by reference,
* otherwise the object will be cloned and then inserted into the dictionary.
* @return A newly inserted object.
* @exception An Exception is thrown if this is not a dictionary or a stream object.
*/
- (Obj*)Put: (NSString *)key obj:  (Obj*)obj;
/**
* Inserts a <key, [x1,y1,x2,y2]> pair in the dictionary.
*
* @param key The key of the value to set.
* @param x1,y1,x2,y2 - The values for an array of four numbers to be
* inserted into the dictionary.
* @return A newly created array object.
*
* @exception An Exception is thrown if this is not a dictionary or a stream object.
* @note If a dictionary already contains an entry with the same key, the old entry
* will be deleted and all DictIterators to this entry will be invalidated.
*/
- (Obj*)PutRect: (NSString *)key x1:  (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
/**
* Inserts a <key, [a,b,c,d,h,v]> pair in the dictionary.
*
* @param key The key of the value to set.
* @param value - A matrix used to set the values in an array of six numbers.
* The resulting array will be inserted into the dictionary.
* @return A newly created array object.
*
* @exception An Exception is thrown if this is not a dictionary or a stream object.
* @note If a dictionary already contains an entry with the same key, the old entry
* will be deleted and all DictIterators to this entry will be invalidated.
*/
- (Obj*)PutMatrix: (NSString *)key value:  (Matrix2D*)value;
/**
* Removes an element in the dictionary that matches the given key.
* @exception An Exception is thrown if this is not a dictionary or a stream.
*/
- (void)EraseDictElementWithKey: (NSString *)key;
/**
* Removes an element in the dictionary from specified position.
* @exception An Exception is thrown if this is not a dictionary or a stream.
*/
- (void)EraseDictElementWithPos: (DictIterator*)pos;
/**
* Change the key value of a dictionary entry.
* The key can't be renamed if another key with the same name already exists
* in the dictionary. In this case Rename returns false.
*
* @exception An Exception is thrown if this is not a dictionary or a stream.
*/
- (BOOL)Rename: (NSString *)old_key new_key:  (NSString *)new_key;
/**
* @param index - The array element to obtain. The first element in an array has an index of zero.
*
* @exception throws an Exception if index is outside the array bounds.
* @exception An Exception is thrown if this is not an Obj::Type::e_array.
*/
- (Obj*)GetAt: (unsigned long)index;
/**
* Inserts an Obj::Type::e_name object in the array.
* @return A newly created name object.
*
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
* @param name The value of the Obj::Type::e_name object to be inserted.
*
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)InsertName: (unsigned long)pos name:  (NSString *)name;
/**
* Inserts an Obj::Type::e_array object in the array.
* @return A newly created array object.
*
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
*
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)InsertArray: (unsigned long)pos;
/**
* Inserts an Obj::Type::e_bool object in the array.
* @return A newly created boolean object.
*
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
* @param value The value of the Obj::Type::e_bool object to be inserted.
*
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)InsertBool: (unsigned long)pos value:  (BOOL)value;
/**
* Inserts an Obj::Type::e_dict object in the array.
* @return A newly created dictionary object.
*
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
*
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)InsertDict: (unsigned long)pos;
/**
* Inserts an Obj::Type::e_number object in the array.
* @return A newly created number object.
*
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
* @param value The value of the Obj::Type::e_number object to be inserted.
*
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)InsertNumber: (unsigned long)pos value:  (double)value;
/**
* Inserts an Obj::Type::e_string object in the array.
* @return A newly created string object.
*
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
* @param value The value of the Obj::Type::e_string object to be inserted.
*
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)InsertString: (unsigned long)pos value:  (NSString *)value;
/**
* Inserts an Obj::Type::e_string object in the array.
* @return A newly created string object.
*
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
* @param value The buffer used to set the value of the Obj::Type::e_string
* object to be inserted.
* @param size The number of bytes to copy from the 'value' buffer parameter.
*
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)InsertStringWithSize: (unsigned long)pos value:  (NSString *)value size:  (int)size;
/**
* Inserts an Obj::Type::e_string object in the array.
* @return A newly created string object.
*
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
* @param value The value of the Obj::Type::e_string object to be inserted.
*
* @note InsertText will create the string object as a 'PDF Text' object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)InsertText: (unsigned long)pos value:  (NSString*)value;
/**
* Inserts an Obj::Type::e_null object in the array.
* @return A newly created null object.
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)InsertNull: (unsigned long)pos;
/**
* Inserts an existing Obj in this array.
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
* @param obj The value to be inserted into the dictionary. If 'obj' is
* indirect (i.e. is a shared) object it will be inserted by reference,
* otherwise the object will be cloned and then inserted.
* @return A newly inserted object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)Insert: (unsigned long)pos obj:  (Obj*)obj;
/**
* Inserts an array of 4 numbers in this array.
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
*
* @param x1,y1,x2,y2 - The values for an array of four numbers to be
* inserted in this array.
* @return A newly created array object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)InsertRect: (unsigned long)pos x1:  (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
/**
* Inserts an array of 6 numbers in this array.
* @param pos - The location in the array to insert the object . The object is inserted
*          before the specified location. The first element in an array has a pos of
*	        zero. If pos >= Array->Length(), appends obj to array.
*
* @param value - A matrix used to set the values in an array of six numbers.
* The resulting array will be then inserted in this array.
* @return A newly created array object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)InsertMatrix: (unsigned long)pos value:  (Matrix2D*)value;
/**
* Appends a new Obj::Type::e_name object at the end of the array.
* @return The new array object.
* @param name - The value of the Obj::Type::e_name object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBackName: (NSString *)name;
/**
* Appends a new Obj::Type::e_array object at the end of the array.
* @return The new array object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBackArray;
/**
* Appends a new Obj::Type::e_bool object at the end of the array.
* @return The new boolean object.
* @param name - The value of the Obj::Type::e_bool object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBackBool: (BOOL)value;
/**
* Appends a new Obj::Type::e_dict object at the end of the array.
* @return The new dictionary object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBackDict;
/**
* Appends a new Obj::Type::e_number object at the end of the array.
* @return The new number object.
* @param value - The value of the Obj::Type::e_number object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBackNumber: (double)value;
/**
* Appends a new Obj::Type::e_string object at the end of the array.
* @return The new string object.
* @param value - The value of the Obj::Type::e_string object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBackString: (NSString *)value;
/**
* Appends a new Obj::Type::e_string object at the end of the array.
* @return The new string object.
* @param value The buffer used to set the value of the Obj::Type::e_string
* object to be inserted.
* @param size The number of bytes to copy from the 'value' buffer parameter.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBackStringWithSize: (NSString *)value size:  (int)size;
/**
* Appends a new Obj::Type::e_string object at the end of the array.
* @return The new string object.
* @param value The value of the Obj::Type::e_string object to be inserted.
* @note InsertText will create the string object as a 'PDF Text' object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBackText: (NSString*)value;
/**
* Appends a new Obj::Type::e_null object at the end of the array.
* @return The new null object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBackNull;
/**
* Appends an existing Obj at the end of the array.
* @param obj The value to be inserted into the dictionary. If 'obj' is
* indirect (i.e. is a shared) object it will be inserted by reference,
* otherwise the object will be cloned and then appended.
* @return A newly appended object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBack: (Obj*)obj;
/**
* Appends an array of 4 numbers at the end of the array.
* @param x1,y1,x2,y2 - The values for an array of four numbers to be
* appended.
* @return A newly appended array object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBackRect: (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
/**
* Appends an array of 6 numbers at the end of the array.
* @param value - A matrix used to set the values in an array of six numbers.
* The resulting array will be then inserted in this array.
* @return A newly appended array object.
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (Obj*)PushBackMatrix: (Matrix2D*)value;
/**
* Checks whether the position is within the array bounds and then removes it from the
* array and moves each subsequent element to the slot with the next smaller index and
* decrements the arrays length by 1.
*
* @param idx The index for the array member to remove. Array indexes start at 0.
*
* @exception An Exception is thrown if this is not an Obj::Type::e_array
*/
- (void)EraseAt: (unsigned long)pos;
/**
* @return the length of the raw/encoded stream equal to the Length parameter
* @exception An Exception is thrown if this is not a Obj::Type::e_stream
*/
- (unsigned long)GetRawStreamLength;
/**
* @param decrypt - If true decrypt the stream if the stream is encrypted.
* @return - A filter to the encoded stream
* @exception An Exception is thrown if this is not a Obj::Type::e_stream
*/
- (Filter*)GetRawStream: (BOOL)decrypt;
/**
* @return - A filter to the decoded stream
* @exception An Exception is thrown if this is not a Obj::Type::e_stream
*/
- (Filter*)GetDecodedStream;
/**
* allows to replace the content stream with a new one
* without creating a new object
*/
- (void)SetStreamData: (NSString *)data data_size:  (unsigned long)data_size filter_chain:  (Filter*)filter_chain;
/**
* @return true if two Obj's point to the same object.
* This method does not compare object content. For this operation use
* IsEqualValue() instead.
* @param to - Obj to compare to
*/
- (BOOL)IsEqual: (Obj*)to;
- (id)init;

@end


/**
* DictIterator is used to traverse key/value pairs in a dictionary.
* For example a DictIterator can be used to print out all the entries
* in a given Obj dictionary as follows:
* @code
*  DictIterator itr = dict.GetDictIterator();
*  while (itr.HasNext()) {
*      Obj key = itr.Key();
*	    cout << key.GetName() << endl;
*      Obj value = itr.Value();
*      // ...
*      itr.Next()
*   }
* @endcode
*/
@interface DictIterator : NSObject
{


}





/**
* Advances the iterator to the next element of the collection.
*/
- (void)Next;
/**
* @return the key of the current dictionary entry.
*/
- (Obj*)Key;
/**
* @return the value of the current dictionary entry.
*/
- (Obj*)Value;
/**
* @return true if the iterator can be successfully advanced to the
* next element; false if the end collection is reached.
*/
- (BOOL)HasNext;	/**
* Copy constructor.
*/
- (id)initWithC: (DictIterator*)c;




@end


/**
* Standard Security Handler is a standard password-based security handler.
*/
@interface SecurityHandler : NSObject
{


}





/**
* @return true if the SecurityHandler permits the specified action (Permission p)
* on the document, or false if the permission was not granted.
*
* @param p A Permission to be granted.
*
* @note in order to check for permission the method will repeatedly (up to three
* times) attempt to GetAuthorizationData() and Authorize() permission. If the
* permission is not granted AuthorizeFailed() callback will be called. This callback
* method allows derived class to provide UI feedback for failed authorization.
*/
- (BOOL)GetPermission: (Permission)p;
/**
* @return The length of the encryption key in bytes.
* @note The returned key length is given in bytes.
*/
- (int)GetKeyLength;
/**
* @return The encryption algorithm identifier. A code specifying the algorithm
* to be used in encrypting and decrypting the document. Returned number corresponds
* to V entry in encryption dictionary. Currently allowed values are from 0-4.
* See PDF Reference Manual for more details.
*/
- (int)GetEncryptionAlgorithmID;
/**
* @return The name of the security handler as it appears in the serialized file
* as the value of /Filter key in /Encrypt dictionary.
*/
- (NSString *)GetHandlerDocName;
/**
* @return - true if the SecurityHandler was modified (by calling SetModified())
* or false otherwise.
*
* If the user changes SecurityHandler's settings (e.g. by changing a password),
* IsModified() should return true.
*/
- (BOOL)IsModified;
/**
* The method allows derived classes to set SecurityHandler is modified flag.
* This method should be called whenever there are changes (e.g. a password change)
* to the SecurityHandler
*/
- (void)SetModified: (BOOL)is_modified;	/**
* Create a Standard Security Handler.
*
* @param crypt_type The encryption algorithm identifier.
*/
- (id)initWithCrypt_type: (AlgorithmType)crypt_type;
/**
* Create a Standard Security Handler.
*
* @param key_len The bit length of the encryption key (40 or 128 bit).
* @param enc_code The encryption algorithm identifier. The number corresponds
* to the V entry in encryption dictionary. Currently allowed values are (see
* Table 3.18 in PDF Reference Manual v1.6 for more details):
*   - 1 : Encryption using 40-bit RC4 algorithm.
*   - 2 : Encryption using 128-bit RC4 algorithm. Available in PDF 1.4 and above.
*   - 3 : This algorithm was deprecated by PDF standard and is not supported.
*   - 4 : Encryption using Crypt filters and 128-bit AES (Advanced Encryption
*         Standard) algorithm. Available in PDF 1.6 and above.
*
* @default values for key_len and enc_code are 128 and 2 respectively.
*/
- (id)initWithName: (NSString *)name key_len:  (int)key_len enc_code:  (int)enc_code;

/**
* Set the new user password to an ASCII text string
* @param password the new user password
*/
- (void)ChangeUserPassword: (NSString *)password;
/**
* Set the new user password to a binary string
* @param password the new user password
*/
- (void)ChangeUserPasswordWithLength: (NSString *)password pwd_length:  (unsigned long)pwd_length;
/**
* @return Current user password.
*/
- (NSString *)GetUserPassword;
/**
* @return Length of the current user password string. This has to be used
* when password is a non-ASCII string that may contain '\0' bytes.
*/
- (unsigned long)GetUserPasswordSize;
/**
* Set the new master password to an ASCII text string
* @param password the new master/owner password
*/
- (void)ChangeMasterPassword: (NSString *)password;
/**
* Set the new master password to a binary string
* @param password the new user password
*/
- (void)ChangeMasterPasswordWithLength: (NSString *)password pwd_length:  (unsigned long)pwd_length;
/**
* @return Current master (owner) password.
*/
- (NSString *)GetMasterPassword;
/**
* @return Length of the current owner password string. This has to be used
* when password is a non-ASCII string that may contain '\0' bytes.
*/
- (unsigned long)GetMasterPasswordSize;
/**
* Set the permission setting of the StdSecurityHandler.
* @param perm indicates a permission to set or clear. It can be any of the
* following values:
*
*	e_print				// print the document.
*	e_doc_modify		// edit the document more than adding or modifying text notes.
*	e_extract_content	// enable content extraction
*	e_mod_annot			// allow modifications to annotations
*	e_fill_forms		// allow changes to fill in forms
*	e_access_support	// content access for the visually impaired.
*	e_assemble_doc		// allow document assembly
*	e_print_high		// high resolution print.
*
* @param value true if the permission/s should be granted, false otherwise.
*/
- (void)SetPermission: (Permission)perm value:  (BOOL)value;
/**
* Change the revision number and the encryption algorithm of the
* standard security handler.
*
* @param rev_num the new revision number of the standard security
* algorithm. Currently allowed values for the revision number are
* (see Table 3.18 in PDF Reference Manual v1.6 for more details):
*   - 2 : Encryption using 40-bit RC4 algorithm.
*   - 3 : Encryption using 128-bit RC4 algorithm. Available in PDF 1.4 and above.
*   - 4 : Encryption using Crypt filters and 128-bit AES (Advanced Encryption
*         Standard) algorithm. Available in PDF 1.6 and above.
*/
- (void)ChangeRevisionNumber: (int)rev_num;
/**
* Indicates whether the document-level metadata stream is to
* be encrypted.
*
* @param encrypt_metadata true if metadata stream should be
* encrypted, false otherwise.
*
* @note EncryptMetadata flag affects only Crypt filters available
* in PDF 1.5 (Acrobat 6) and later. By default, metadata stream
* will be encrypted.
*/
- (void)SetEncryptMetadata: (BOOL)encrypt_metadata;
/**
* @return the revision number of the standard security algorithm.
*/
- (int)GetRevisionNumber;
/**
* @return true if the SecurityHandler requires a user password.
*/
- (BOOL)IsUserPasswordRequired;
/**
* @return true if the SecurityHandler requires a master (owner) password.
*/
- (BOOL)IsMasterPasswordRequired;
/**
* @return true is this security handler uses 128 bit AES (Advanced Encryption Standard)
* algorithm to encrypt strings or streams.
*/
- (BOOL)IsAES;
/**
* The following function can be used to verify whether a given stream is
* encrypted using AES.
*
* @return true if the given stream is encrypted using AES encryption.
* @param stream A pointer to an SDF::Stream object
*/
- (BOOL)IsAESWithStream: (Obj*)stream;
/**
* @return true is this security handler uses RC4 algorithm to encrypt strings or streams.
*/
- (BOOL)IsRC4;
/**
* A callback method indicating repeated failed authorization.
* Override this callback in order to provide a UI feedback for failed
* authorization. Default implementation returns immediately.
*/
- (void)AuthorizeFailed;
/**
* The method is called when a user tries to set security for an encrypted
* document and when a user tries to open a file. It must decide, based on
* the contents of the authorization data structure, whether or not the
* user is permitted to open the file, and what permissions the user has
* for this file.
*
* @note - This callback must not obtain the authorization data (e.g. by
* displaying a user interface into which a user can type a password).
* This is handled by the security handlers GetAuthorizationData(), which
* must be called before this callback. Instead, Authorize() should work
* with authorization data it has access to.
*
* @param p - permission to authorize
*/
- (BOOL)Authorize: (Permission)p;
/**
* This method is invoked in case Authorize() failed. The callback must
* determine the users authorization properties for the document by
* obtaining authorization data (e.g. a password through a GUI dialog).
*
* The authorization data is subsequently used by the security handlers Authorize()
* to determine whether or not the user is authorized to open the file.
*
* @return false if the operation was canceled, true otherwise.
* @param req_opr - the permission for which authorization data is requested.
*/
- (BOOL)GetAuthorizationData: (Permission)req_opr;
/**
* Called when the security handler should activate a dialog box
* with the current security settings that may be modified.
*
* @return true if the operation was successful false otherwise.
*/
- (BOOL)EditSecurityData: (SDFDoc*)doc;
/**
* Called when an encrypted document is saved. Fills the document's Encryption
* dictionary with whatever information the security handler wants to store in
* the document.
*
* The sequence of events during creation of the encrypt_dict is as follows:
*  - encrypt_dict is created (if it does not exist)
*  - Filter attribute is added to the dictionary
*  - call this method to allow the security handler to add its own attributes
*  - call the GetCryptKey to get the algorithm version, key, and key length
*  - checks if the V attribute has been added to the dictionary and, if not,
*    then sets V to the algorithm version
*  - set the Length attribute if V is 2 or greater
*  - add the encrypt_dict to the document
*
*	@param doc - The document to save.
*  @return - encrypt_dict
*
* @warning - Unlike all other strings and streams, direct object elements of
* the encrypt_dict are not encrypted automatically. If you want them encrypted,
* you must encrypt them before inserting them into the dictionary.
*/
- (Obj*)FillEncryptDict: (SDFDoc*)doc;
/**
* @return A new, cloned instance of SecurityHandler.
* @note this method must be implemented in any derived class from SecurityHandler.
*/
- (SecurityHandler*)Clone: (SWIGTYPE_TRN_SecurityHandler*)base;
/**
* The method can be called in GetAuthorizationData() callback to
* specify user supplied ASCII password.
*/
- (void)InitPassword: (NSString *)password;
/**
* The method can be called in GetAuthorizationData() callback to
* specify user supplied non-ASCII password.
*/
- (void)InitPasswordWithLength: (NSString *)password pwd_length:  (unsigned long)pwd_length;
/**
* This method informs base security handler which methods are overridden in the
* derived class. The only place this method needs to be invoked is in
* Create(name, key_len, enc_code) static factory method in the derived class.
*
* @param overloaded_funct A flag that specifies which functions are overloaded
* in the derived class. For example: SetDerived(SecurityHandler::has_Clone + SecurityHandler::has_FillEncDictProc);
*/
- (void)SetDerived: (unsigned int)overloaded_funct;
/**
* @return The derived class or NULL for standard security handler.
*/
- (SecurityHandler*)GetDerived;


- (id)init;

@end


/**
* A NameTree is a common data structure in PDF. See section 3.8.5 'Name Trees'
* in PDF Reference Manual for more details.
*
* A name tree serves a similar purpose to a dictionary - associating keys and
* values - but by different means. NameTrees allow efficient storage of very
* large association collections (string/Obj* maps). A NameTree can have many
* more entries than a SDF/Cos dictionary can.
*
* NameTree-s use SDF/Cos-style strings (not null-terminated C strings), which
* may use Unicode encoding etc.
*
* @code
*   PDFDoc doc("../Data/PDFReference.pdf");
*   NameTree dests = NameTree::Find(*doc.GetSDFDoc(), "Dests");
*   if (dests.IsValid()) {
*     // Traversing the NameTree
*     UString key;
*     for (DictIterator i = dests.GetIterator(); i.HasNext(); i.Next())
*        i.Key().GetAsPDFText(key); // ...
*   }
* @endcode
*/
@interface NameTree : NSObject
{


}





/**
* Retrieves the NameTree inside the '/Root/Names' dictionary with the
* specified key name, or creates it if it does not exist.
*
* @param doc - The document in which the name tree is created.
* @param name - The name of the NameTree to create.
*
* @return The newly created NameTree for the doc or an existing tree with
* the same key name.
*
* @note although it is possible to create a name tree anywhere in the document
* the convention is that all trees are located under '/Root/Names' dictionary.
*/
+ (NameTree*)Create: (SDFDoc*)doc name:  (NSString*)name;
/**
* Retrieves a name tree, with the given key name, from the '/Root/Names'
* dictionary of the doc.
*
* @param doc - The document in which to search for the name.
* @param name - The name of the name tree to find.
*
* @return The requested NameTree. If the requested NameTree exists
* NameTree.IsValid() will return true, and false otherwise.
*/
+ (NameTree*)Find: (SDFDoc*)doc name:  (NSString*)name;	/**
* Create a high level NameTree wrapper around an existing SDF/Cos NameTree.
* This does not copy the object.
*
* @param name_tree SDF/Cos root of the NameTree object.
*/
- (id)initWithName_tree: (Obj*)name_tree;

/**
* @return whether this is a valid (non-null) NameTree. If the
* function returns false the underlying SDF/Cos object is null and
* the NameTree object should be treated as null as well.
*/
- (BOOL)IsValid;
- (DictIterator*)GetNameIteratorWithKey: (NSData*)key key_sz:  (int)key_sz;
/**
* Search for the specified key in the NameTree.
*
* @return If the key is present the function returns a NameTreeIterator the points
* to the given Key/Value pair. If the key is not found the function returns End()
* (a non-valid) iterator.
*
* @param key data buffer representing the key to be found.
* @param key_sz The size (in bytes) of the key.
*
* @code
*   DictIterator i = dests.Find("MyKey", 5);
*   if (i.HasNext()) {
*     UString key;
*     i.GetKey().GetAsPDFText(key); // ...
*     cout << "Value: " << i.GetValue().GetType() << endl;
*   }
* @endcode
*/
- (DictIterator*)GetIterator;
/**
* Search the NameTree for a given key.
*
* @param key - a key to search for in the dictionary
* @param key_sz - the buffer size used to store the key.
* @return null if the tree does not contain the specified key, otherwise
* return the corresponding value.
*/
- (Obj*)GetValue: (NSData*)key key_sz:  (int)key_sz;
/**
* Puts a new entry in the name tree. If an entry with this key
* is already in the tree, it is replaced.
*
* @param key data buffer representing the key of the new entry.
* @param key_sz The size (in bytes) of the key.
* @param the value associated with the key. It can be any SDF::Obj.
*/
- (void)Put: (NSData*)key key_sz:  (int)key_sz value:  (Obj*)value;
/**
* Removes the specified object from the tree. Does nothing if no object
* with that name exists.
*
* @param key data buffer representing the key of the entry to be removed.
* @param key_sz The size (in bytes) of the key.
*/
- (void)EraseNameTreeEntryWithKey: (NSData*)key key_sz:  (int)key_sz;
/**
* Removes the NameTree entry pointed by the iterator.
*/
- (void)EraseNameTreeEntryWithPos: (DictIterator*)pos;
/**
* @return the object to the underlying SDF/Cos object. If the NameTree.IsValid()
* returns false the SDF/Cos object is NULL.
*/
- (Obj*)GetSDFObj;


@end


/**
* A NumberTree is a common data structure in PDF. See section 3.8.6 'Number Trees'
* in PDF Reference Manual for more details.
*
* A number tree serves a similar purpose to a dictionary - associating keys and
* values - but by different means. NumberTrees allow efficient storage of very
* large association collections (number/Obj* maps). A NumberTree can have many
* more entries than a SDF/Cos dictionary can.
*
* Sample code:
* @code
*   PDFDoc doc("../Data/test.pdf");
*   NumberTree labels(doc.GetRoot().Get("PageLabels").Value());
*   if (labels.IsValid()) {
*     // Traversing the NumberTree
*     for (NumberTreeIterator i = labels.GetIterator(); i.HasNext(); i.Next())
*         cout << "Key: " << i.Key().GetNumber() << endl;
*   }
* @endcode
*/
@interface NumberTree : NSObject
{


}





/**
* Create a high level NumberTree wrapper around an existing SDF/Cos NumberTree.
* This does not copy the object.
*
* @param number_tree SDF/Cos root of the NumberTree object.
*/
- (id)initWithNumber_tree: (Obj*)number_tree;
/**
* @return whether this is a valid (non-null) NumberTree. If the
* function returns false the underlying SDF/Cos object is null and
* the NumberTree object should be treated as null as well.
*/
- (BOOL)IsValid;
- (DictIterator*)GetNumberIteratorWithKey: (int)key;
/**
* Search for the specified key in the NumberTree.
*
* @return If the key is present the function returns a NumberTreeIterator the points
* to the given Key/Value pair. If the key is not found the function returns End()
* (a non-valid) iterator.
*
* @param key the number representing the key to be found.
*
* Sample code:
*   NumberTreeIterator i = dests.Find(5);
*   if (i.HasNext()) {
*     cout << "Key: " << i.GetKey()->GetNumber() << endl;
*     cout << "Value: " << i.GetValue()->GetType() << endl;
*   }
*
*/
- (DictIterator*)GetIterator;
- (Obj*)GetValue: (int)key;
/**
* Puts a new entry in the name tree. If an entry with this number
* is already in the tree, it is replaced.
*
* @param key A number representing the key of the new entry.
* @param the value associated with the key. It can be any SDF::Obj.
*/
- (void)Put: (int)key value:  (Obj*)value;
/**
* Removes the specified object from the tree. Does nothing if no object
* with that number exists.
*
* @param key A number representing the key of the entry to be removed.
*/
- (void)EraseNumberTreeEntryWithKey: (int)key;
/**
* Removes the NumberTree entry pointed by the iterator.
*/
- (void)EraseNumberTreeEntryWithPos: (DictIterator*)pos;
/**
* @return the object to the underlying SDF/Cos object. If the NumberTree.IsValid()
* returns false the SDF/Cos object is NULL.
*/
- (Obj*)GetSDFObj;


@end


/**
* ObjSet is a lightweight container that can hold a collection of SDF objects.
*/
@interface ObjSet : NSObject
{


}





/**
* Create a new name object in this object set.
*/
- (Obj*)CreateName: (NSString *)name;
/**
* Create a new array object in this object set.
*/
- (Obj*)CreateArray;
/**
* Create a new boolean object in this object set.
*/
- (Obj*)CreateBool: (BOOL)value;
/**
* Create a new dictionary object in this object set.
*/
- (Obj*)CreateDict;
/**
* Create a new null object in this object set.
*/
- (Obj*)CreateNull;
/**
* Create a new number object in this object set.
*/
- (Obj*)CreateNumber: (double)value;
/**
* Create a new string object in this object set.
*/
- (Obj*)CreateString: (NSString*)value;

- (id)init;

@end



/**
* A base class for SignatureHandler. SignatureHandler instances are responsible for defining the digest and cipher
* algorithms to create and/or validate a signed PDF document. SignatureHandlers are added to PDFDoc instances by
* calling the PDFDoc::AddSignatureHandler method.
*/
@interface SignatureHandler : NSObject
{
void* m_cPtr;
}

- (void*) getCptr;
- (void) unsetCPtr;
- (NSString*) GetName;
- (void) AppendData : (NSData*) data;
- (BOOL) Reset;
- (NSData*) CreateSignature;
- (id) init;
- (id) initWithCptr: (void*) cptr;
- (void) dealloc;

@end // @interface SignatureHandler



/**
* Although PDF is not a programming language it provides several types of function
* object that represent parameterized classes of functions, including mathematical
* formulas and sampled representations with arbitrary resolution. Functions are used
* in various ways in PDF, including device-dependent rasterization information for
* high-quality printing (halftone spot functions and transfer functions), color
* transform functions for certain color spaces, and specification of colors as a
* function of position for smooth shadings. Functions in PDF represent static,
* self-contained numerical transformations.<br><br>
*
* PDF::Function represents a single, flat interface around all PDF function types.
*/
@interface Function : NSObject
{


}





/**
* Create a PDF::Function object from an existing SDF function dictionary. If funct_dict
* is null, a non valid Function object is created.
*/
- (id)initWithFunct_dict: (Obj*)funct_dict;
/**
* @return The function type
*/
- (FunctionType)GetType;
/**
* @return the number of input components required by the function
*/
- (int)GetInputCardinality;
/**
* @return the number of output components returned by the function
*/
- (int)GetOutputCardinality;
/**
* Evaluate the function at a given point.
*
* @note that size of 'in' array must be greater than or equal to function
* input cardinality. and the size of 'out' array must be greater than or equal
* to function output cardinality.
*/
- (NSMutableArray*)Eval: (NSMutableArray*)in_arr;
/**
* @return the underlying SDF/Cos object
*/
- (Obj*)GetSDFObj;



@end


/**
* ColorPt is an array of colorants (or tint values) representing a color point
* in an associated color space.
*/
@interface ColorPt : NSObject
{


}





/**
* Constructors and destructor
*/
- (id)initWithX: (double)x y:  (double)y z:  (double)z w:  (double)w;
/**
* A utility method to set the first 4 tint values. For example,
* color.Set(red, green, blue) will initialize the ColorPt to given
* tint values.
* @note All colorants should be in the range [0..1].
* @note color.Set(gray) is equivalent to Set(0, gray);
*/
- (void)Set: (double)x y:  (double)y z:  (double)z w:  (double)w;
/**
* Sets a tint value at a given colorant index.
*
* @param colorant_index the color index. For example, for a color point
* associated with a Gray color space the only allowed value for index
* is 0. For a color point associated with a CMYK color space, the color_index
* can range from 0 (cyan) to 4 (black).
*
* @param colorant_value The new tint value.
*
* For example, the following snippet will initialize the color point
* to [red, green, blue]:
* @code
* color.SetColorantNum(3);
* color.Set(0, red);
* color.Set(1, green);
* color.Set(2, blue);
* @endcode
*
* The above code snippet is equivalent to the following line:
*   color.Set(red, green, blue)
*
* @note If a color point has more than 4 colorants, SetColorantNum(num_colorants)
* must be called before getting or setting tint values.
*/
- (void)SetTintWithIndex: (int)colorant_index colorant_value:  (double)colorant_value;
/**
* @return the tint value at a given colorant index.
*
* The number of colorants depends on the associated color space. To find
* how many colorant are associated with a given color space use
* color_space.GetComponentNum().
*
* For example, if you have a color point in the RGB color space you can
* extract its colorants as follows:
* @code
* UInt8 rgb[3] = ;;
* @endcode
*/
- (double)Get: (int)colorant_index;
/**
* If a color point has more than 4 colorants, SetColorantNum(num_colorants)
* must be called before getting or setting tint values.
* The number of colorants depends on the associated color space. To find
* how many colorant are associated with a given color space use
* color_space.GetComponentNum().
*/
- (void)SetColorantNum: (int)num;



@end


/**
* This abstract class is used to serve as a color space tag to identify the specific
* color space of a Color object. It contains methods that transform colors in a specific
* color space to/from several color space such as DeviceRGB and DeviceCMYK.
*
* For purposes of the methods in this class, colors are represented as arrays of color
* components represented as doubles in a normalized range defined by each ColorSpace.
* For many ColorSpaces (e.g. DeviceRGB), this range is 0.0 to 1.0. However, some ColorSpaces
* have components whose values have a different range. Methods are provided to inquire per
* component minimum and maximum normalized values.
*
* @note Note that in Pattern color space (i.e. for ColorSpace::e_pattern) 'color values'
* are PDF::PatternColor objects instead of the numeric component values (i.e. ColorPt)
* used with other spaces.
*/
@interface ColorSpace : NSObject
{


}





/**
* Create a new DeviceGray ColorSpace object
*/
+ (ColorSpace*)CreateDeviceGray;
/**
* Create a new DeviceRGB ColorSpace object
*/
+ (ColorSpace*)CreateDeviceRGB;
/**
* Create a new DeviceCMYK ColorSpace object
*/
+ (ColorSpace*)CreateDeviceCMYK;
/**
* Create a new Pattern ColorSpace object
*/
+ (ColorSpace*)CreatePattern;
/**
* Create a PDF 'ICCBased' color space given an ICC profile
*/
+ (ColorSpace*)CreateICCWithString: (SDFDoc*)doc filepath:  (NSString*)filepath;	/**
* Create a ColorSpace from the given SDF/Cos object listed under ColorSpaces entry
* in page Resource dictionary. If color_space dictionary is null, a non valid ColorSpace
* object is created.
*/
- (id)initWithColor_space: (Obj*)color_space;

+ (ColorSpace*)CreateICCWithStream: (SDFDoc*)doc stm:  (Filter*)stm;
+ (ColorSpace*)CreateICCWithBuf: (SDFDoc*)doc buf:  (NSData*)buf buf_sz:  (unsigned long)buf_sz;
/**
* @return The type of this color space
*/
- (ColorSpaceType)GetType;
/**
* @return the underlying SDF/Cos object
*/
- (Obj*)GetSDFObj;
/**
* @return The number of colorants (tint components) used to represent color
*  point in this color space
*/
- (int)GetComponentNum;
/**
* Set color to the initial value used for this color space.
* The initial value depends on the color space (see 4.5.7 in PDF Ref. Manual).
*/
- (void)InitColor: (ColorPt*)out_colorants;
/**
* Initialize default ranges for each color component in the color space.
* For example, default ranges for DeviceRGB are [0 1 0 1 0 1] but for Lab
* the default values might be [0 100 -100 100 -100 100].
*
* @param an vector of numbers representing the lower bound for each color component.
* @param an vector of numbers representing the the difference between high and
* low bound for each color component.
*
* @note the size of resulting vectors will match the number of color components
* in this color space.
*/
- (void)InitComponentRanges: (NSMutableArray*)out_decode_low out_decode_range:  (NSMutableArray*)out_decode_range;
/**
* A convenience function used to convert color points from the current
* color space to DeviceGray color space.
*
* @param in_color input color point in the current color space
* @param out_color output color point in the DeviceGray color space
*
* @note the number to input colorants must match the number of colorants
* expected by the current color space.
*/
- (ColorPt*)Convert2Gray: (ColorPt*)in_color;
/**
* A convenience function used to convert color points from the current
* color space to DeviceRGB color space.
*
* @param in_color input color point in the current color space
* @param out_color output color point in the DeviceRGB color space
*
* @note the number to input colorants must match the number of colorants
* expected by the current color space.
*/
- (ColorPt*)Convert2RGB: (ColorPt*)in_color;
/**
* A convenience function used to convert color points from the current
* color space to DeviceCMYK color space.
*
* @param in_color input color point in the current color space
* @param out_color output color point in the DeviceCMYK color space
*
* @note the number to input colorants must match the number of colorants
* expected by the current color space.
*/
- (ColorPt*)Convert2CMYK: (ColorPt*)in_color;
/**
* @return the alternate color space if it is available or NULL otherwise.
* Color spaces that include alternate color space are e_separation, e_device_n,
* and e_icc.
*/
- (ColorSpace*)GetAlternateColorSpace;
/**
* @return the base color space if this is an e_indexed or e_pattern with
* associated base color space; NULL otherwise.
*/
- (ColorSpace*)GetBaseColorSpace;
/**
* @return the highest index for the color lookup table for Indexed color space.
* Since the color table is indexed from zero to highval, the actual number of entries is
* highval + 1. For color spaces other than indexed the method returns 0.
*
* @note for color spaces other than Indexed this method throws an exception.
*/
- (int)GetHighVal;
/**
* Get the base color given a component value (index) in Indexed color space.
*
* @param color_idx color value represented in the index color space
* @param out_color the color represented in the base (associated) color space
*
* @note for color spaces other than Indexed this method throws an exception.
*/
- (ColorPt*)GetBaseColor: (unsigned char)color_idx;
/**
* @return True if Separation or DeviceN color space contains None colorants.
* For DeviceN the function returns true only if component colorant names are all None.
*
* @note for color spaces other than Separation or DeviceN this method throws
* an exception.
*/
- (BOOL)IsNone;
/**
* @return True if Separation color space contains the colorant All.
*
* @note for color spaces other than Separation this method throws an exception.
*/
- (BOOL)IsAll;
/**
* @return the function that transforms tint values into color component
* values in the alternate color space.
*
* @note for color spaces other than Separation this method throws an exception.
*/
- (Function*)GetTintFunction;



@end


/**
* Rect is a utility class used to manipulate PDF rectangle objects (refer to
* section 3.8.3 of the PDF Reference Manual).
*
* Rect can be associated with a SDF/Cos rectangle array using Rect(Obj*) constructor
* or later using Rect::Attach(Obj*) or Rect::Update(Obj*) methods.
*
* Rect keeps a local cache for rectangle points so it is necessary to call Rect::Update()
* method if the changes to the Rect should be saved in the attached Cos/SDF array.
*
* @note - Although rectangles are conventionally specified by their lower-left and
* upper-right corners, it is acceptable to specify any two diagonally opposite corners.
*/
@interface PDFRect : TRN_rect





/**
* Rect default constructor.
*/
- (id)init;
/**
* Create a Rect and initialize it using given Cos/SDF rectangle Array object.
* The rect is attached to this object.
*/
- (id)initWithRect: (Obj*)rect;
/**
* Create a Rect and initialize it using specified parameters.
* The rect is not attached to any Cos/SDF object.
*/
- (id)initWithX1: (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
/**
* Attach the Cos/SDF object to the Rect.
*
* @param rect - underlying Cos/SDF object. Must be an SDF::Array with four
*  SDF::Number elements.
*/
- (void)Attach: (Obj*)rect;
/**
* Saves changes made to the Rect object in the attached (or specified) SDF/Cos rectangle.
*
* @param rect - an optional parameter indicating a SDF array that should be
*  updated and attached to this Rect. If parameter rect is NULL or is omitted, update
*  is performed on previously attached Cos/SDF rectangle.
*
* @return true if the attached Cos/SDF rectangle array was successfully updated,
* false otherwise.
*/
- (BOOL)Update: (Obj*)rect;
/**
* Set the coordinates of the rectangle
*/
- (void)Set: (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
/**
* @return rectangle's width
*/
- (double)Width;
/**
* @return rectangle's height
*/
- (double)Height;
/**
* Determines if the specified point is contained within the rectangular region
* defined by this Rectangle
*
* @return true is the point is in the rectangle, false otherwise.
*/
- (BOOL)Contains: (double)x y:  (double)y;
/**
* Makes a Rect equal to the intersection of two existing rectangles.
*
* @param rect1 - A Rect object that contains a source rectangle.
* @param rect2 - A Rect object that contains a source rectangle.
*
* @return true if the intersection is not empty; 0 if the intersection is empty.
*
* @note The intersection is the largest rectangle contained in both existing rectangles.
*/
- (BOOL)IntersectRect: (PDFRect*)rect1 rect2:  (PDFRect*)rect2;
/**
* Arrange the points in the rectangle so that the first point is the lower-left
* corner and the second point is the upper-right corner of the rectangle.
*
* @note Although rectangles are conventionally specified by their lower-left
* and upper-right corners, it is acceptable to specify any two diagonally
* opposite corners.
*/
- (void)Normalize;
/**
* Expands the rectangle by the specified size, in all directions.
*
* @param amount Specifies the amount to increase the rectangle in all directions.
*/
- (void)InflateWithAmount: (double)amount;
/**
* Expands the rectangle by the specified size, in all directions.
*
* @param x Specifies the amount to increase the rectangle's Left (x1) and Right (x2) properties.
* @param y Specifies the amount to increase the rectangle's Top (y1) and Bottom (y1) properties.
*/
- (void)InflateWithXY: (double)x y:  (double)y;
/**
* @return The horizontal value of lower-left point.
*/
- (double)GetX1;
/**
* @return The vertical value of lower-left point.
*/
- (double)GetY1;
/**
* @return The horizontal value of upper-right point.
*/
- (double)GetX2;
/**
* @return The vertical value of upper-right point.
*/
- (double)GetY2;
/**
* Set the horizontal value of lower-left point.
*/
- (void)SetX1: (double)x1;
/**
* Set the vertical value of lower-left point.
*/
- (void)SetY1: (double)y1;
/**
* Set the horizontal value of upper-right point.
*/
- (void)SetX2: (double)x2;
/**
* Set the vertical value of upper-right point.
*/
- (void)SetY2: (double)y2;




@end


/**
* TextExtractor::Word object represents a word on a PDF page.
* Each word contains a sequence of characters in one or more styles
* (see TextExtractor::Style).
*/
@interface Word : NSObject
{


}





/**
* @return The number of glyphs in this word.
*/
- (int)GetNumGlyphs;
/**
* @param out_bbox The bounding box for this word (in unrotated page
* coordinates).
* @note To account for the effect of page '/Rotate' attribute,
* transform all points using page.GetDefaultMatrix().
*/
- (PDFRect*)GetBBox;
/**
* @param out_quad The quadrilateral representing a tight bounding box
* for this word (in unrotated page coordinates).
*/
- (NSMutableArray*)GetQuad;
/**
* @param glyph_idx The index of a glyph in this word.
* @param out_quad The quadrilateral representing a tight bounding box
* for a given glyph in the word (in unrotated page coordinates).
*/
- (NSMutableArray*)GetGlyphQuad: (int)glyph_idx;
/**
* @param char_idx The index of a character in this word.
* @return The style associated with a given character.
*/
- (TextExtractorStyle*)GetCharStyle: (int)char_idx;
/**
* @return predominant style for this word.
*/
- (TextExtractorStyle*)GetStyle;
/**
* @return the number of characters in this word.
*/
- (int)GetStringLen;
/**
* @return the content of this word represented as a Unicode string.
*/
- (NSString*)GetString;
/**
* @return the next word on the current line.
*/
- (Word*)GetNextWord;
/**
* @return the index of this word of the current line. A word that
* starts the line will return 0, whereas the last word in the line
* will return (line.GetNumWords()-1).
*/
- (int)GetCurrentNum;
/**
* @return true if this is a valid word, false otherwise.
*/
- (BOOL)IsValid;
- (void)setMp_word: (SWIGTYPE_TRN_TextExtractorWord*)value;
- (SWIGTYPE_TRN_TextExtractorWord*)getMp_word;
- (id)init;

@end


/**
* TextExtractor::Line object represents a line of text on a PDF page.
* Each line consists of a sequence of words, and each words in one or
* more styles.
*/
@interface TextExtractorLine : NSObject
{


}





/**
* @return The number of words in this line.
*/
- (int)GetNumWords;
/**
* @return true is this line is not rotated (i.e. if the
* quadrilaterals returned by GetBBox() and GetQuad() coincide).
*/
- (BOOL)IsSimpleLine;
/**
* @param out_bbox The bounding box for this line (in unrotated page
* coordinates).
* @note To account for the effect of page '/Rotate' attribute,
* transform all points using page.GetDefaultMatrix().
*/
- (PDFRect*)GetBBox;
/**
* @param out_quad The quadrilateral representing a tight bounding box
* for this line (in unrotated page coordinates).
*/
- (NSMutableArray*)GetQuad;
/**
* @return the first word in the line.
* @note To traverse the list of all words on this line use word.GetNextWord().
*/
- (Word*)GetFirstWord;
/**
* @return the i-th word in this line.
*/
- (Word*)GetWord: (int)word_idx;
/**
* @return the next line on the page.
*/
- (TextExtractorLine*)GetNextLine;
/**
* @return the index of this line of the current page.
*/
- (int)GetCurrentNum;
/**
* @return predominant style for this line.
*/
- (TextExtractorStyle*)GetStyle;
/**
* @return The unique identifier for a paragraph or column
* that this line belongs to. This information can be used to
* identify which lines belong to which paragraphs.
*/
- (int)GetParagraphID;
/**
* @return The unique identifier for a paragraph or column
* that this line belongs to. This information can be used to
* identify which lines/paragraphs belong to which flows.
*/
- (int)GetFlowID;
/**
* @return true is this line of text ends with a hyphen (i.e. '-'),
* false otherwise.
*/
- (BOOL)EndsWithHyphen;
/**
* @return true if this is a valid line, false otherwise.
*/
- (BOOL)IsValid;
- (void)setMp_line: (SWIGTYPE_TRN_TextExtractorLine*)value;
- (SWIGTYPE_TRN_TextExtractorLine*)getMp_line;
- (id)initWithImpl: (SWIGTYPE_TRN_TextExtractorLine*)impl;

@end


/**
* Page is a high-level class representing PDF page object (see 'Page Objects' in
* Section 3.6.2, 'Page Tree,' in PDF Reference Manual).
*
* Among other associated objects, a page object contains:
*  - A series of objects representing the objects drawn on the page (See Element and
*    ElementReader class for examples of how to extract page content).
*  - A list of resources used in drawing the page
*  - Annotations
*  - Beads, private metadata, optional thumbnail image, etc.
*/
@interface Page : NSObject
{


}





/**
* Initialize a page using an existing low-level Cos/SDF page object.
*
* @param page_dict - a low-level (SDF/Cos) page dictionary.
*
* @note This constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*
* @note Because PDF::PDFDoc provides a complete high-level interface for Page creation
* and traversal this constructor is rarely used.
*/
- (id)initWithPage_dict: (Obj*)page_dict;
/**
* @return true if this is a valid (non-null) page, false otherwise.
* If the function returns false the underlying SDF/Cos object is null
* or is not valid.
*/
- (BOOL)IsValid;
/**
* @return the Page number indication the position of this Page in document's page sequence.
* Document's page sequence is indexed from 1. Page number 0 means that the page is not part
* of document's page sequence or that the page is not valid.
*/
- (int)GetIndex;
/**
* @return the box specified for the page object intersected with the media box.
*
* @param type The type of the page bounding box. Possible values are: e_media, e_crop,
* e_bleed, e_trim, and e_art.
*
* If the value for 'type' is e_crop, this call is equivalent to GetCropBox().
* If the value for 'type' is e_media, this call is equivalent to GetMediaBox().
*/
- (PDFRect*)GetBox: (Box)type;
/**
* Sets the page bounding box specified by 'page_region' for this page.
*
* @param type The type of the page bounding box. Possible values are: e_media, e_crop,
* e_bleed, e_trim, and e_art.
* @param box A rectangle specifying the coordinates to set for the box. The coordinates are
* specified in user space units.
*/
- (void)SetBox: (Box)type box:  (PDFRect*)box;
/**
* @return the crop box for this page. The page dimensions are specified in user space
* coordinates.
*
* The crop box is the region of the page to display and print.
* @note this method is equivalent to GetBox(Page::e_crop)
*/
- (PDFRect*)GetCropBox;
/**
* Sets the crop box for this page. The crop box is the region of the page to
* display and print.
*
* @param box the new crop box for this page. The page dimensions are specified in user space
* coordinates.
*
* The crop box defines the region to which the contents of the page are to be clipped (cropped)
* when displayed or printed.
*
* @note this method is equivalent to SetBox(Page::e_crop)
*/
- (void)SetCropBox: (PDFRect*)box;
/**
* @return the media box for this page. The page dimensions are specified in user space
* coordinates.
*
* The media box defines the boundaries of the physical medium on which the page is to
* be printed. It may include any extended area surrounding the finished page for bleed,
* printing marks, or other such purposes.
*
* @note this method is equivalent to GetBox(Page::e_media)
* @exception if the page is missing media box the function throws Exception
*/
- (PDFRect*)GetMediaBox;
/**
* Sets the media box for this page.
*
* @param box the new media box for this page. The page dimensions are specified in user space
* coordinates.
*
* The media box defines the boundaries of the physical medium on which the page is to
* be printed. It may include any extended area surrounding the finished page for bleed,
* printing marks, or other such purposes.
*
* @note this method is equivalent to SetBox(Page::e_media)
*/
- (void)SetMediaBox: (PDFRect*)box;
/**
* @return the bounding box for this page. The page dimensions are specified in user space
* coordinates.
*
* The bounding box is defined as the smallest rectangle that includes all the visible content on the page.
*/
- (PDFRect*)GetVisibleContentBox;
/**
* @return the rotation value for this page.
*/
- (Rotate)GetRotation;
/**
* Sets the rotation value for this page.
*
* @param angle Rotation value to be set for a given page. Must be one
* of the Page::Rotate values.
*/
- (void)SetRotation: (Rotate)angle;
/**
* @return the width for the given page region/box taking into account page
* rotation attribute (i.e. /Rotate entry in page dictionary).
*
* @param box_type indicates the page box/region to query for width.
*/
- (double)GetPageWidth: (Box)box_type;
/**
* @return the height for the given page region/box taking into account page
* rotation attribute (i.e. /Rotate entry in page dictionary).
*
* @param box_type indicates the page box/region to query for height.
*/
- (double)GetPageHeight: (Box)box_type;
/**
* @return the matrix that transforms user space coordinates to rotated and cropped coordinates.
* The origin of this space is the bottom-left of the rotated, cropped page.
*
* @param flip_y this parameter can be used to mirror the page. if 'flip_y' is true the Y
* axis is not flipped and it is increasing, otherwise Y axis is decreasing.
*
* @param box_type an optional parameter used to specify the page box/region that the matrix
* should map to. By default, the function transforms user space coordinates to cropped
* coordinates.
*
* @param angle an optional parameter used to specify page rotation in addition to the
* rotation specified in the page dictionary. This parameter is usually used to rotate the
* page without modifying the document itself.
*/
- (Matrix2D*)GetDefaultMatrix: (BOOL)flip_y box_type:  (Box)box_type angle:  (Rotate)angle;
/**
* Returns SDF/Cos array containing annotation dictionaries. See Section 8.4 in
* the PDF Reference for a description of the annotation array.
*
* @return an array of annotation dictionaries representing annotations
* associated with the page or NULL if page dictionary is not specified.
*/
- (Obj*)GetAnnots;
/**
* Returns the number of annotations on a page. Widget annotations (form fields) are
* included in the count.
*
* @return The number of annotations on a page.
*/
- (unsigned int)GetNumAnnots;
/**
* Returns the annotation on the page.
*
* @return Annotation object. If the index is out of range returned Annot object
* is not valid (i.e. annot.IsValid() returns false).
*
* @param index - The index of the annotation to get on a page. The first annotation
* on a page has an index of zero.
*/
- (Annot*)GetAnnot: (unsigned int)index;
/**
* Adds an annotation at the specified location in a page's annotation array.
*
* @param pos - The location in the array to insert the object. The object is inserted
* before the specified location. The first element in an array has a pos of zero.
* If pos >= GetNumAnnots(), the method appends the annotation to the array.
* @param annot - The annotation to add.
*/
- (void)AnnotInsert: (unsigned int)pos annot:  (Annot*)annot;
/**
* Adds an annotation to the end of a page's annotation array.
* @param annot - The annotation to prepend in a page's annotation array.
*/
- (void)AnnotPushBack: (Annot*)annot;
/**
* Adds an annotation to the beginning of a page's annotation array.
* @param annot - The annotation to append in a page's annotation array.
*/
- (void)AnnotPushFront: (Annot*)annot;
/**
* Removes the given annotation from the page.
* @note Removing the annotation invalidates the given Annot object.
* @param index - A zero based index of the annotation to remove.
*/
- (void)AnnotRemoveWithAnnot: (Annot*)annot;
/**
* Removes the annotation at a given location.
* @note Removing the annotation invalidates any associated Annot object.
* @param index - A zero based index of the annotation to remove.
*/
- (void)AnnotRemoveWithIndex: (unsigned int)index;
/**
* A utility method used to scale physical dimensions of the page including
* all page content.
*
* @param scale A number greater than 0 which is used as a scale factor.
*  For example, calling page.Scale(0.5) will reduce physical dimensions of the
*  page to half its original size, whereas page.Scale(2) will double the physical
* dimensions of the page and will rescale all page content appropriately.
*
* @note Unlike SetUserUnitSize(unit_size) which is only supported in PDF 1.6
* (i.e. Acrobat 7) and above, page.Scale(sc) supports all PDF versions.
*/
- (void)Scale: (double)scale;
/**
* Flatten/Merge existing form field appearances with the page content and
* remove widget annotation.
*
* Form 'flattening' refers to the operation that changes active form fields
* into a static area that is part of the PDF document, just like the other
* text and images in the document. A completely flattened PDF form does not
* have any widget annotations or interactive fields.
*
* @note An alternative approach to set the field as read only is using
* Field.SetFlag(Field::e_read_only, true) method. Unlike Field.SetFlag(...),
* the result of FlattenField() operation can not be programatically reversed.
*/
- (void)FlattenField: (TRNField*)filed;
/**
* Tests whether this page has a transition.
*/
- (BOOL)HasTransition;
/**
* Returns the UserUnit value for the page. A UserUnit is a positive number giving
* the size of default user space units, in multiples of 1/72 inch.
*
* @return the UserUnit value for the page. If the key is not present in the
* page dictionary the default of 1.0 is returned.
*/
- (double)GetUserUnitSize;
/**
* Sets the UserUnit value for a page.
*
* @param unit_size A positive number giving the size of default user space
* units, in multiples of 1/72 inch.
*
* @note This is a PDF 1.6 feature. See the implementation note 171 in
* PDF Reference for details.
*/
- (void)SetUserUnitSize: (double)unit_size;
/**
* @return a pointer to the page resource dictionary.
* @exception if the page is missing resource dictionary the function throws Exception
*/
- (Obj*)GetResourceDict;
/**
* @return NULL if page is empty, otherwise a single stream or an array of streams.
*/
- (Obj*)GetContents;
/**
* Returns the page dictionary.
*
* @return the object to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;
/**
* Some of the page attributes are designated as inheritable.
* If such an attribute is omitted from a page object, its value is inherited
* from an ancestor node in the page tree. If the attribute is a required one,
* a value must be supplied in an ancestor node; if it is optional and no
* inherited value is specified, the default value should be used.
*
* The function walks up the page inheritance tree in search for specified
* attribute.
*
* @return if the attribute was found return a pointer to the value. Otherwise
* the function return NULL.
*
*	Resources dictionary (Required; inheritable)
*  MediaBox rectangle (Required; inheritable)
*  CropBox rectangle (Optional; inheritable)
*  Rotate integer (Optional; inheritable)
*/
- (Obj*)FindInheritedAttribute: (NSString *)attrib;
/**
* @return Object representing the Image thumbnail.
*/
- (Obj*)GetThumb;


@end


@interface PageIterator : NSObject
{


}





- (void)Next;
- (Page*)Current;
- (BOOL)HasNext;
- (id)init;
@end


/**
* The Date class is a utility class used to simplify work with PDF date objects.
*
* PDF defines a standard date format, which closely follows international
* standard ASN.1 (Abstract Syntax Notation One), A date is a string of the form
* (D:YYYYMMDDHHmmSSOHH'mm'); See PDF Reference Manual for details.
*
* Date can be associated with a SDF/Cos date string using Date(Obj*) constructor
* or later using Date::Attach(Obj*) or Date::Update(Obj*) methods.
*
* Date keeps a local date/time cache so it is necessary to call Date::Update()
* method if the changes to the Date should be saved in the attached Cos/SDF string.
*/
@interface Date : TRN_date





/**
* Date default constructor.
*/
- (id)init;
/**
* Create a Date and initialize it using given Cos/SDF string date object.
* String date object is attached to this Date.
*/
- (id)initWithD: (Obj*)d;
/**
* Create a Date and initialize it using specified parameters.
* The Date is not attached to any Cos/SDF object.
*/
- (id)initWithYear: (unsigned short)year month:  (char)month day:  (char)day hour:  (char)hour minute:  (char)minute second:  (char)second;
/**
* Indicates whether the Date is valid (non-null).
*
* @return True if this is a valid (non-null) Date; otherwise false.
*
* @note If this method returns false the underlying SDF/Cos object is null and
* the Date object should be treated as null as well.
*/
- (BOOL)IsValid;
/**
* Sets the date object to the current date and time. The method also updates
* associated SDF object.
*/
- (void)SetCurrentTime;
/**
* Attach the Cos/SDF object to the Date.
*
* @param d - underlying Cos/SDF object. Must be an SDF::Str containing
*  a PDF date object.
*/
- (void)Attach: (Obj*)d;
/**
* Saves changes made to the Date object in the attached (or specified) SDF/Cos string.
*
* @param d - an optional parameter indicating a SDF string that should be
*  updated and attached to this Date. If parameter d is NULL or is omitted, update
*  is performed on previously attached Cos/SDF date.
*
* @return true if the attached Cos/SDF string was successfully updated, false otherwise.
*/
- (BOOL)Update: (Obj*)d;
/**
* @return The year.
*/
- (unsigned short)GetYear;
- (unsigned char)GetMonth;
- (unsigned char)GetDay;
- (unsigned char)GetHour;
- (unsigned char)GetMinute;
- (unsigned char)GetSecond;
- (unsigned char)GetUT;
- (unsigned char)GetUTHour;
- (unsigned char)GetUTMin;




@end


/**
* GState is a class that keeps track of a number of style attributes used to visually
* define graphical Elements. Each PDF::Element has an associated GState that can be used to
* query or set various graphics properties.
*
* @note current clipping path is not tracked in the graphics state for efficiency
* reasons. In most cases tracking of the current clipping path is best left to the
* client.
*/
@interface GState : NSObject
{


}





/**
* @return the transformation matrix for this element.
* @note If you are looking for a matrix that maps coordinates to the initial
* user space see Element::GetCTM().
*/
- (Matrix2D*)GetTransform;
/**
* @return color space used for stroking
*/
- (ColorSpace*)GetStrokeColorSpace;
/**
* @return color space used for filling
*/
- (ColorSpace*)GetFillColorSpace;
/**
* @return a color value/point represented in the current stroke color space
*/
- (ColorPt*)GetStrokeColor;
/**
* @return the SDF pattern object of currently selected PatternColorSpace used for stroking.
*/
- (PatternColor*)GetStrokePattern;
/**
* @return a color value/point represented in the current fill color space
*/
- (ColorPt*)GetFillColor;
/**
* @return the pattern color of currently selected pattern color space used for filling.
*/
- (PatternColor*)GetFillPattern;
/**
* @return current value of flatness tolerance
*
* Flatness is a number in the range 0 to 100; a value of 0 specifies the output
* devices default flatness tolerance.
*
* The flatness tolerance controls the maximum permitted distance in device pixels
* between the mathematically correct path and an approximation constructed from
* straight line segments.
*/
- (double)GetFlatness;
/**
* @return currently selected LineCap style
*
* The line cap style specifies the shape to be used at the ends of open sub-paths
* (and dashes, if any) when they are stroked.
*/
- (LineCap)GetLineCap;
/**
* @return currently selected LineJoin style
*
* The line join style specifies the shape to be used at the corners of paths that
* are stroked.
*/
- (LineJoin)GetLineJoin;
/**
* @return the thickness of the line used to stroke a path.
* @note A line width of 0 denotes the thinnest line that can be rendered at device
* resolution: 1 device pixel wide.
*/
- (double)GetLineWidth;
/**
* @return current value of miter limit.
*
* The miter limit imposes a maximum on the ratio of the miter length to the
* line width. When the limit is exceeded, the join is converted from a miter
* to a bevel.
*/
- (double)GetMiterLimit;
/**
* @return The method fills the vector with an array of numbers representing the dash pattern
*
* The line dash pattern controls the pattern of dashes and gaps used to stroke
* paths. It is specified by a dash array and a dash phase. The dash arrays elements
* are numbers that specify the lengths of alternating dashes and gaps; the dash phase
* specifies the distance into the dash pattern at which to start the dash. The elements
* of both the dash array and the dash phase are expressed in user space units.
*/
- (NSMutableArray*)GetDashes;
/**
* @return the phase of the currently selected dash pattern. dash phase is expressed in
* user space units.
*/
- (double)GetPhase;
/**
* @return currently selected character spacing.
*
* The character spacing parameter is a number specified in unscaled text space
* units. When the glyph for each character in the string is rendered, the character
* spacing is added to the horizontal or vertical component of the glyphs displacement,
* depending on the writing mode. See Section 5.2.1 in PDF Reference Manual for details.
*/
- (double)GetCharSpacing;
/**
* @return currently selected word spacing
*
* Word spacing works the same way as character spacing, but applies only to the
* space character (char code 32). See Section 5.2.2 in PDF Reference Manual for details.
*/
- (double)GetWordSpacing;
/**
* @return currently selected horizontal scale
*
* The horizontal scaling parameter adjusts the width of glyphs by stretching
* or compressing them in the horizontal direction. Its value is specified as
* a percentage of the normal width of the glyphs, with 100 being the normal width.
* The scaling always applies to the horizontal coordinate in text space, independently
* of the writing mode. See Section 5.2.3 in PDF Reference Manual for details.
*/
- (double)GetHorizontalScale;
/**
* @return currently selected leading parameter
*
* The leading parameter is measured in unscaled text space units. It specifies
* the vertical distance between the baselines of adjacent lines of text.
* See Section 5.2.4 in PDF Reference Manual for details.
*/
- (double)GetLeading;
/**
* @return currently selected font
*/
- (Font*)GetFont;
/**
* @return the font size
*/
- (double)GetFontSize;
/**
* @return current text rendering mode.
*
* The text rendering mode determines whether showing text causes glyph outlines to
* be stroked, filled, used as a clipping boundary, or some combination of the three.
* See Section 5.2.5 in PDF Reference Manual for details..
*/
- (TextRenderingMode)GetTextRenderMode;
/**
* @return current value of text rise
*
* Text rise specifies the distance, in unscaled text space units, to move the
* baseline up or down from its default location. Positive values of text rise
* move the baseline up
*/
- (double)GetTextRise;
/**
* @return a boolean flag that determines the text element is considered
* elementary objects for purposes of color compositing in the transparent imaging
* model.
*/
- (BOOL)IsTextKnockout;
/**
* @return The color intent to be used for rendering the Element
*/
- (RenderingIntent)GetRenderingIntent;
/**
* A utility function that maps a string representing a rendering intent to
* RenderingIntent type.
*
* @return The color rendering intent type matching the specified string
*/
+ (RenderingIntent)GetRenderingIntentType: (NSString *)name;
/**
* @return the current blend mode to be used in the transparent imaging model.
* Corresponds to the /BM key within the ExtGState's dictionary.
*/
- (BlendMode)GetBlendMode;
/**
* @return the opacity value for painting operations other than stroking.
* Returns the value of the /ca key in the ExtGState dictionary. If the value is not
* found, the default value of 1 is returned.
*/
- (double)GetFillOpacity;
/**
* @return opacity value for stroke painting operations for paths and glyph outlines.
* Returns the value of the /CA key in the ExtGState dictionary. If the value is not
* found, the default value of 1 is returned.
*/
- (double)GetStrokeOpacity;
/**
* @return the alpha source flag ('alpha is shape'), specifying whether the
* current soft mask and alpha constant are to be interpreted as shape values
* (true) or opacity values (false).
*/
- (BOOL)GetAISFlag;
/**
* @return Associated soft mask. NULL if the soft mask is not selected or
* SDF dictionary representing the soft mask otherwise.
*/
- (Obj*)GetSoftMask;
/**
* @return The soft mask transform. This is the transformation matrix at the moment the soft
* mask is established in the graphics state with the gs operator. This information is only
* relevant when applying the soft mask that may be specified in the graphics state to the
* current element.
*/
- (Matrix2D*)GetSoftMaskTransform;
/**
* @return whether overprint is enabled for stroke painting operations.
* Corresponds to the /OP key within the ExtGState's dictionary.
*/
- (BOOL)GetStrokeOverprint;
/**
* @return whether overprint is enabled for fill painting operations.
* Corresponds to the /op key within the ExtGState's dictionary.
*/
- (BOOL)GetFillOverprint;
/**
* @return the overprint mode used by this graphics state.
* Corresponds to the /OPM key within the ExtGState's dictionary.
*/
- (int)GetOverprintMode;
/**
* @return a flag specifying whether stroke adjustment is enabled in the graphics
* state. Corresponds to the /SA key within the ExtGState's dictionary.
*/
- (BOOL)GetAutoStrokeAdjust;
/**
* @return the smoothness tolerance used to control the quality of smooth
* shading. Corresponds to the /SM key within the ExtGState's dictionary.
* The allowable error (or tolerance) is expressed as a fraction of the range
* of the color component, from 0.0 to 1.0.
*/
- (double)GetSmoothnessTolerance;
/**
* @return currently selected transfer function (NULL by default) used during
* color conversion process. A transfer function adjusts the values of color
* components to compensate for nonlinear response in an output device and in
* the human eye. Corresponds to the /TR key within the ExtGState's dictionary.
*/
- (Obj*)GetTransferFunct;
/**
* @return currently selected black-generation function (NULL by default) used
* during conversion between DeviceRGB and DeviceCMYK. Corresponds to the /BG key
* within the ExtGState's dictionary.
*/
- (Obj*)GetBlackGenFunct;
/**
* @return currently selected undercolor-removal function (NULL by default) used
* during conversion between DeviceRGB and DeviceCMYK. Corresponds to the /UCR key
* within the ExtGState's dictionary.
*/
- (Obj*)GetUCRFunct;
/**
* @return currently selected halftone dictionary or stream (NULL by default).
* Corresponds to the /HT key within the ExtGState's dictionary.
* Halftoning is a process by which continuous-tone colors are approximated on an
* output device that can achieve only a limited number of discrete colors.
*/
- (Obj*)GetHalftone;
/**
* Set the transformation matrix associated with this element.
*
* @param mtx The new transformation for this text element.
*
* @note in PDF associating a transformation matrix with an element
* ('cm' operator) will also affect all subsequent elements.
*/
- (void)SetTransformWithMatrix: (Matrix2D*)mtx;
/**
* Set the transformation matrix associated with this element.
*
* A transformation matrix in PDF is specified by six numbers, usually
* in the form of an array containing six elements. In its most general
* form, this array is denoted [a b c d h v]; it can represent any linear
* transformation from one coordinate system to another. For more
* information about PDF matrices please refer to section 4.2.2 'Common
* Transformations' in PDF Reference Manual, and to documentation for
* pdftron::Common::Matrix2D class.
*
* @param a - horizontal 'scaling' component of the new text matrix.
* @param b - 'rotation' component of the new text matrix.
* @param c - vertical 'scaling' component of the new text matrix.
* @param d - 'rotation' component of the new text matrix.
* @param h - horizontal translation component of the new text matrix.
* @param v - vertical translation component of the new text matrix.
*/
- (void)SetTransform: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
/**
* Concatenate the given matrix to the transformation matrix of this element.
*/
- (void)ConcatWithMatrix: (Matrix2D*)mtx;
- (void)Concat: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
/**
* Sets the color space used for stroking operations
*/
- (void)SetStrokeColorSpace: (ColorSpace*)cs;
/**
* Sets the color space used for filling operations
*/
- (void)SetFillColorSpace: (ColorSpace*)cs;
/**
* Sets the color value/point used for stroking operations.
* The color value must be represented in the currently selected color space used
* for stroking.
*/
- (void)SetStrokeColorWithColorPt: (ColorPt*)c;
/**
* Set the stroke color to the given tiling pattern.
* @param pattern SDF pattern object.
* @note The currently selected stroke color space must be Pattern color space.
*/
- (void)SetStrokeColorWithPattern: (PatternColor*)pattern;
/**
* Set the stroke color to the given uncolored tiling pattern.
* @param SDF pattern (PatternType = 1 and PaintType = 2) object.
* @param c is a color in the patterns underlying color space.
* @note The currently selected stroke color space must be Pattern color space.
*/
- (void)SetStrokeColorWithPatternAndColorPt: (PatternColor*)pattern c:  (ColorPt*)c;
/**
* Sets the color value/point used for filling operations.
* The color value must be represented in the currently selected color space used
* for filling.
*/
- (void)SetFillColorWithColorPt: (ColorPt*)c;
/**
* Set the fill color to the given tiling pattern.
* @param pattern New pattern color.
* @note The currently selected fill color space must be Pattern color space.
*/
- (void)SetFillColorWithPattern: (PatternColor*)pattern;
/**
* Set the fill color to the given uncolored tiling pattern.
* @param SDF pattern (PatternType = 1 and PaintType = 2) object.
* @param c is a color in the patterns underlying color space.
* @note The currently selected fill color space must be Pattern color space.
*/
- (void)SetFillColorWithPatternAndColorPt: (PatternColor*)pattern c:  (ColorPt*)c;
/**
* Sets the value of flatness tolerance.
*
* @param flatness is a number in the range 0 to 100; a value of 0 specifies the output
* devices default flatness tolerance.
*
* The flatness tolerance controls the maximum permitted distance in device pixels
* between the mathematically correct path and an approximation constructed from
* straight line segments.
*/
- (void)SetFlatness: (double)flatness;
/**
* Sets LineCap style property.
* The line cap style specifies the shape to be used at the ends of open subpaths
* (and dashes, if any) when they are stroked.
*/
- (void)SetLineCap: (LineCap)cap;
/**
* Sets LineJoin style property.
*
* The line join style specifies the shape to be used at the corners of paths that
* are stroked.
*/
- (void)SetLineJoin: (LineJoin)join;
/**
* Sets the thickness of the line used to stroke a path.
* @param width a non-negative number expressed in user space units.
* A line width of 0 denotes the thinnest line that can be rendered at device
* resolution: 1 device pixel wide.
*/
- (void)SetLineWidth: (double)width;
/**
* Sets miter limit.
* @param miter_limit A number that imposes a maximum on the ratio of the miter
* length to the line width. When the limit is exceeded, the join is converted
* from a miter to a bevel.
*/
- (void)SetMiterLimit: (double)miter_limit;
/**
* Sets the dash pattern used to stroke paths.
*
* The line dash pattern controls the pattern of dashes and gaps used to stroke
* paths. It is specified by a dash array and a dash phase. The dash arrays elements
* are numbers that specify the lengths of alternating dashes and gaps; the dash phase
* specifies the distance into the dash pattern at which to start the dash. The elements
* of both the dash array and the dash phase are expressed in user space units.
*/
- (void)SetDashPattern: (NSMutableArray*)dash_array phase:  (double)phase;
/**
* Sets character spacing.
* @param char_spacing a number specified in unscaled text space units. When the
* glyph for each character in the string is rendered, the character spacing is
* added to the horizontal or vertical component of the glyphs displacement,
* depending on the writing mode. See Section 5.2.1 in PDF Reference Manual for details.
*/
- (void)SetCharSpacing: (double)char_spacing;
/**
* Sets word spacing.
* @param word_spacing - a number specified in unscaled text space units.
* Word spacing works the same way as character spacing, but applies only to the
* space character (char code 32). See Section 5.2.2 in PDF Reference Manual for details.
*/
- (void)SetWordSpacing: (double)word_spacing;
/**
* Sets horizontal scale.
* The horizontal scaling parameter adjusts the width of glyphs by stretching
* or compressing them in the horizontal direction. Its value is specified as
* a percentage of the normal width of the glyphs, with 100 being the normal width.
* The scaling always applies to the horizontal coordinate in text space, independently
* of the writing mode. See Section 5.2.3 in PDF Reference Manual for details.
*/
- (void)SetHorizontalScale: (double)hscale;
/**
* Sets the leading parameter.
*
* The leading parameter is measured in unscaled text space units. It specifies
* the vertical distance between the baselines of adjacent lines of text.
* See Section 5.2.4 in PDF Reference Manual for details.
*/
- (void)SetLeading: (double)leading;
/**
* Sets the font and font size used to draw text.
*/
- (void)SetFont: (Font*)font font_sz:  (double)font_sz;
/**
* Sets text rendering mode.
* The text rendering mode determines whether showing text causes glyph outlines to
* be stroked, filled, used as a clipping boundary, or some combination of the three.
* See Section 5.2.5 in PDF Reference Manual for details..
*/
- (void)SetTextRenderMode: (TextRenderingMode)rmode;
/**
* Sets text rise.
* Text rise specifies the distance, in unscaled text space units, to move the
* baseline up or down from its default location. Positive values of text rise
* move the baseline up
*/
- (void)SetTextRise: (double)rise;
/**
* Mark the object as elementary for purposes of color compositing in the
* transparent imaging model.
*/
- (void)SetTextKnockout: (BOOL)knockout;
/**
* Sets the color intent to be used for rendering the Element.
*/
- (void)SetRenderingIntent: (RenderingIntent)intent;
/**
* Sets the current blend mode to be used in the transparent imaging model.
* Corresponds to the /BM key within the ExtGState's dictionary.
* @param BM - New blending mode type.
*
* @code
* // C#
* gs.SetBlendMode(GState.BlendMode.e_lighten);
*
* // C++
* gs->SetBlendMode(GState::e_lighten);
* @endcode
*/
- (void)SetBlendMode: (BlendMode)BM;
/**
* Sets the opacity value for painting operations other than stroking.
* Corresponds to the value of the /ca key in the ExtGState dictionary.
*/
- (void)SetFillOpacity: (double)ca;
/**
* Sets opacity value for stroke painting operations for paths and glyph outlines.
* Corresponds to the value of the /CA key in the ExtGState dictionary.
*/
- (void)SetStrokeOpacity: (double)CA;
/**
* Specifies if the alpha is to be interpreted as a shape or opacity mask.
* The alpha source flag ('alpha is shape'), specifies whether the
* current soft mask and alpha constant are to be interpreted as shape values
* (true) or opacity values (false).
*/
- (void)SetAISFlag: (BOOL)AIS;
/**
* Sets the soft mask of the extended graphics state.
* Corresponds to the /SMask key within the ExtGState's dictionary.
* @param BG - SDF/Cos black-generation function or name
*/
- (void)SetSoftMask: (Obj*)SM;
/**
* Specifies if overprint is enabled for stroke operations. Corresponds to the /OP
* key within the ExtGState's dictionary.
*/
- (void)SetStrokeOverprint: (BOOL)OP;
/**
* Specifies if overprint is enabled for fill operations. Corresponds to the /op
* key within the ExtGState's dictionary.
*/
- (void)SetFillOverprint: (BOOL)op;
/**
* Sets the overprint mode. Corresponds to the /OPM key within the ExtGState's
* dictionary.
*/
- (void)SetOverprintMode: (int)OPM;
/**
* Specify whether to apply automatic stroke adjustment.
* Corresponds to the /SA key within the ExtGState's dictionary.
*/
- (void)SetAutoStrokeAdjust: (BOOL)SA;
/**
* Sets the smoothness tolerance used to control the quality of smooth
* shading. Corresponds to the /SM key within the ExtGState's dictionary.
*/
- (void)SetSmoothnessTolerance: (double)SM;
/**
* Sets black-generation function used during conversion between DeviceRGB
* and DeviceCMYK. Corresponds to the /BG key within the ExtGState's
* dictionary.
* @param BG - SDF/Cos black-generation function or name
*/
- (void)SetBlackGenFunct: (Obj*)BG;
/**
* Sets undercolor-removal function used during conversion between DeviceRGB
* and DeviceCMYK. Corresponds to the /UCR key within the ExtGState's
* dictionary.
* @param UCR - SDF/Cos undercolor-removal function or name
*/
- (void)SetUCRFunct: (Obj*)UCR;
/**
* Sets transfer function used during color conversion process. A transfer
* function adjusts the values of color components to compensate for nonlinear
* response in an output device and in the human eye. Corresponds to the /TR key
* within the ExtGState's dictionary.
* @param TR - SDF/Cos transfer function, array, or name
*/
- (void)SetTransferFunct: (Obj*)TR;
/**
* @return currently selected halftone dictionary or stream (NULL by default).
* Corresponds to the /HT key within the ExtGState's dictionary.
* Halftoning is a process by which continuous-tone colors are approximated on an
* output device that can achieve only a limited number of discrete colors.
* @param HT - SDF/Cos halftone dictionary, stream, or name
*/
- (void)SetHalftone: (Obj*)HT;
- (id)init;

@end


/**
* An interactive form (sometimes referred to as an AcroForm) is a
* collection of fields for gathering information interactively from
* the user. A PDF document may contain any number of Fields appearing
* on any combination of pages, all of which make up a single, global
* interactive form spanning the entire document.
*
* PDFNet fully supports reading, writing, and editing PDF forms and
* provides many utility methods so that work with forms is simple and
* efficient. Using PDFNet forms API arbitrary subsets of form fields
* can be imported or exported from the document, new forms can be
* created from scratch, and the appearance of existing forms can be
* modified.
*
* In PDFNet Fields are accessed through FieldIterator-s. The list of
* all Fields present in the document can be traversed as follows:
*
* @code
* FieldIterator itr = pdfdoc.GetFieldIterator();
* for(; itr.HasNext(); itr.Next()) {
*   Field field = itr.Current();
*   Console.WriteLine("Field name: {0}", field.GetName());
*  }
* @endcode
*
* For a full sample, please refer to 'InteractiveForms' sample project.
*
* To search field by name use FieldFind method. For example:
* @code
* FieldIterator itr = pdfdoc.FieldFind("name");
* if (itr.HasNext()) {
*   Console.WriteLine("Field name: {0}", itr.Current().GetName());
* }
* else { ...field was not found... }
* @endcode
*
* If a given field name was not found or if the end of the field list
* was reached the iterator HasNext() will return false.
*
* If you have a valid iterator you can access the Field using Current() method. For example:
* Field field = itr.Current();
*
* Using Flatten(...) method it is possible to merge field
* appearances with the page content. Form 'flattening' refers to the
* operation that changes active form fields into a static area that is
* part of the PDF document, just like the other text and images in
* the document. A completely flattened PDF form does not have any
* widget annotations or interactive fields.
*/
@interface TRNField : NSObject
{


}





/**
* Construct a PDF::Field from a SDF dictionary representing a terminal field node.
*/
- (id)initWithField_dict: (Obj*)field_dict;
/**
* @return whether this is a valid (non-null) Field. If the
* function returns false the underlying SDF/Cos object is null and
* the Field object should be treated as null as well.
*/
- (BOOL)IsValid;
/**
* @return The fields value, whose type/format varies depending on the field type.
* See the descriptions of individual field types for further information.
*/
- (FieldType)GetType;
/**
* @return the value of the Field (the value of its /V key) or NULL if the
* value is not specified.
*
* The format of fields value varies depending on the field type.
*/
- (Obj*)GetValue;
- (NSString*)GetValueAsString;
/**
* @return Field value as a boolean.
* @note This method is usually for check-box and radio button fields.
*/
- (BOOL)GetValueAsBool;
/**
* Sets the value of the field (i.e. the value of the field's /V key).
* The format of field's value varies depending on the field type.
*
* @param value the new field value.
*
* @note in order to remove/erase the existing value use pass a SDF::Null
* object to SetValue().
*
* @note <p>In PDF, Field's value is separate from its annotation (i.e. how the
* field appears on the page). After you modify Field's value you need to
* refresh Field's appearance using RefreshAppearance() method.
* </p><p>
* Alternatively, you can delete "AP" entry from the Widget annotation and set
* "NeedAppearances" flag in AcroForm dictionary (i.e.
* doc.GetAcroForm().Put("NeedAppearances", Obj.CreateBool(true)); )
* This will force viewer application to auto-generate new field appearances
* every time the document is opened.
* </p><p>
* Yet another option is to generate a custom annotation appearance using
* ElementBuilder and ElementWriter and then set the "AP" entry in the widget
* dictionary to the new appearance stream. This functionality is useful in
* applications that need advanced control over how the form fields are rendered.
* </p>
*/
- (void)SetValueWithString: (NSString*)value;
- (void)SetValueWithObj: (Obj*)value;
- (void)SetValue: (NSString *)value;
/**
* Sets the value of a check-box or radio-button field.
* @param value If true, the filed will be set to 'True', if false the field will
* be set to 'False'.
*
* @note This method is usually for check-box and radio button fields.
*/
- (void)SetValueWithBool: (BOOL)value;
/**
* Regenerates the appearance stream for the Widget Annotation containing
* variable text. Call this method if you modified field's value and would
* like to update field's appearance.
*
* @note If this field contains text, and has been added to a rotated page, the text in
* the field may be rotated. If RefreshAppearance is called *after* the field is added
* to a rotated page, then any text will be rotated in the opposite direction of the page
* rotation. If this method is called *before* the field is added to any rotated page, then
* no counter rotation will be applied. If you wish to call RefreshAppearance on a field
* already added to a rotated page, but you don't want the text to be rotated, you can do one
* of the following; temporarily un-rotate the page, or, temporarily remove the "P" object
* from the field.
*/
- (void)RefreshAppearance;
/**
* Removes any appearances associated with the field.
*/
- (void)EraseAppearance;
/**
* @return The default value to which the field reverts when a reset-form action
* is executed or NULL if the default value is not specified.
*
* The format of fields value varies depending on the field type.
*/
- (Obj*)GetDefaultValue;
- (NSString*)GetDefaultValueAsString;
/**
* @return a string representing the fully qualified name of the field
* (e.g. "employee.name.first").
*/
- (NSString*)GetName;
/**
* @return a string representing the partial name of the field (e.g.
* "first" when "employee.name.first" is fully qualified name).
*/
- (NSString*)GetPartialName;
/**
* Modifies the field name.
*
* @param field_name a string representing the fully qualified name of
* the field (e.g. "employee.name.first").
*/
- (void)Rename: (NSString*)field_name;
/**
* @return true if this Field is a Widget Annotation
*
* Determines whether or not this Field is an Annotation.
*/
- (BOOL)IsAnnot;
/**
* @return the value of given field flag
*/
- (BOOL)GetFlag: (FieldFlag)flag;
/**
* Set the value of given FieldFlag.
*
* @note You can use this method to set the field as read-only.
* An alternative approach to set the field as read only is using Page.Flatten(...)
* method. Unlike Flatten(...), the result of SetFlag(...) can be programatically
* reversed.
*/
- (void)SetFlag: (FieldFlag)flag value:  (BOOL)value;
/**
* @return the form of quadding (justification) to be used in displaying
* the text fields.
*/
- (TextJustification)GetJustification;
/**
* Sets the justification to be used in displaying the text field.
* @note This method is specific to a text field.
*/
- (void)SetJustification: (TextJustification)j;
/**
* Sets the maximum length of the field's text, in characters.
* @note This method is specific to a text field.
*/
- (void)SetMaxLen: (int)max_len;
/**
* Returns the total number of options in a list or combo box.
*/
- (int)GetOptCount;
/**
* @return The string of the option at the givent index.
* @note The index must be less than the value returned by GetOptCount().
*/
- (NSString*)GetOpt: (int)index;
/**
* @return The maximum length of the field's text, in characters, or a
* negative number if the length is not limited.
* @note This method is specific to a text field.
*/
- (int)GetMaxLen;
/**
* @return The default graphics state that should be used in formatting the
* text. The state corresponds to /DA entry in the field dictionary.
*/
- (GState*)GetDefaultAppearance;
/**
* Flatten/Merge existing form field appearances with the page content and
* remove widget annotation.
*
* Form 'flattening' refers to the operation that changes active form fields
* into a static area that is part of the PDF document, just like the other
* text and images in the document. A completely flattened PDF form does not
* have any widget annotations or interactive fields.
*
* @note an alternative approach to set the field as read only is using
* Field.SetFlag(Field::e_read_only, true) method. Unlike Field.SetFlag(...),
* the result of Flatten() operation can not be programatically reversed.
*/
- (void)Flatten: (Page*)page;
/**
* @return The rectangle that should be refreshed after changing a field.
*/
- (PDFRect*)GetUpdateRect;
/**
* Some of the Field attributes are designated as inheritable.
* If such an attribute is omitted from a Field object, its value is inherited
* from an ancestor node in the Field tree. If the attribute is a required one,
* a value must be supplied in an ancestor node; if it is optional and no
* inherited value is specified, the default value should be used.
*
* The function walks up the Field inheritance tree in search for specified
* attribute.
*
* @return The attribute value if the given attribute name was found
* or a NULL object if the given attribute name was not found.
*
*  Resources dictionary (Required; inheritable)
*  MediaBox rectangle (Required; inheritable)
*  CropBox rectangle (Optional; inheritable)
*  Rotate integer (Optional; inheritable)
*/
- (Obj*)FindInheritedAttribute: (NSString *)attrib;
/**
* @return the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;

/**
* Sets the signature handler to use for adding a signature to this field. If the signature handler is not found
* in PDFDoc's signature handlers list, this field will not be signed. To add signature handlers, use PDFDoc.AddSignatureHandler
* method.
*
* If a signature handler is already assigned to this field and this method is called once again, the associate signature
* handler for this field will be updated with the new handler.
*
* @param signature_handler_id The unique id of the SignatureHandler to use for adding signature in this field.
*
* @return The signature dictionary created using the SignatureHandler, or NULL pointer if the signature handler is not found.
*/
- (Obj*)UseSignatureHandler: (SignatureHandlerId)signature_handler_id;


@end


@interface FieldIterator : NSObject
{


}





- (void)Next;
- (TRNField*)Current;
- (BOOL)HasNext;
- (id)init;
@end


/**
* FileSpec corresponds to the PDF file specification object.
*
* A PDF file can refer to the contents of another file by using a file specification,
* which can take either of the following forms:
*
* - A simple file specification gives just the name of the target file in
*   a standard format, independent of the naming conventions of any particular file system.
*
* - A full file specification includes information related to one or more specific file
*   systems.
*
* - A URL reference.
*
* Although the file designated by a file specification is normally external to the
* PDF file referring to it, it is also possible to embed the file allowing its contents
* to be stored or transmitted along with the PDF file. However, embedding a file does not
* change the presumption that it is external to (or separate from) the PDF file.
*
* For more details on file specifications, please refer to Section 3.10, 'File Specifications'
* in the PDF Reference Manual.
*/
@interface FileSpec : NSObject
{


}





/**
* Creates a file specification for the given file. By default, the specified
* file is embedded in PDF.
*
* @param doc - A document to which the FileSpec should be added. To obtain
* SDFDoc from PDFDoc use PDFDoc::GetSDFDoc() or Obj::GetDoc().
*
* @param path - The path to convert into a file specification.
*
* @param embed - A flag indicating whether to embed specified in the PDF.
* By default, all files are embedded.
*
* @return newly created FileSpec object.
*/
+ (FileSpec*)Create: (SDFDoc*)doc path:  (NSString*)path embed:  (BOOL)embed;
/**
* Creates a URL file specification.
*
* @param doc - A document to which the FileSpec should be added. To obtain
* SDFDoc from PDFDoc use PDFDoc::GetSDFDoc() or Obj::GetDoc().
*
* @param url - A uniform resource locator (URL) of the form defined in
* Internet RFC 1738, Uniform Resource Locators Specification.
*
* @return newly created FileSpec object.
*/
+ (FileSpec*)CreateURL: (SDFDoc*)doc url:  (NSString *)url;	/**
* Create a FileSpec and initialize it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithF: (Obj*)f;

/**
* @return whether this is a valid (non-null) FileSpec. If the
* function returns false the underlying SDF/Cos object is null or is not valid
* and the FileSpec object should be treated as null as well.
*/
- (BOOL)IsValid;
/**
* The function saves the data referenced by this FileSpec to an external file.
*
* @param save_as An optional parameter indicating the filepath and filename
* where the data should be saved. If this parameter is not specified, the function
* will attempt to save the file using FileSpec.GetFilePath().
*
* If the file is embedded, the function saves the embedded file.
* If the file is not embedded, the function will copy the external file.
* If the file is not embedded and the external file can't be found, the function
* returns false.
*
* @return true is the file was saved successfully, false otherwise.
*/
- (BOOL)Export: (NSString*)save_as;
/**
* The function returns data referenced by this FileSpec.
*
* @return A stream (filter) containing file data.
* If the file is embedded, the function returns a stream to the embedded file.
* If the file is not embedded, the function will return a stream to the external file.
* If the file is not embedded and the external file can't be found, the function
* returns NULL.
*/
- (Filter*)GetFileData;
/**
* @return The file path for this file specification.
*
* If the FileSpec is a dictionary, a corresponding platform specific path
* is returned (DOS, Mac, or Unix). Otherwise the function returns the path represented
* in the form described in Section 3.10.1, 'File Specification Strings,' or , if the
* file system is URL, as a uniform resource locator (URL). If the FileSpec is not
* valid, an empty string is returned.
*/
- (NSString*)GetFilePath;
/**
* The functions sets the descriptive text associated with the file specification.
* This test is typically used in the EmbeddedFiles name tree.
*/
- (void)SetDesc: (NSString*)desc;
/**
* @return The underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;


@end


/**
* Annot is a base class for different types of annotations. For annotation
* specific properties, please refer to derived classes.
*
* An annotation is an interactive object placed on a page, such as a text note, a link,
* or an embedded file. PDF includes a wide variety of standard annotation types.
* An annotation associates an object such as a widget, note, or movie with a location
* on a page of a PDF document, or provides a means of interacting with the user
* via the mouse and keyboard. For more details on PDF annotations please refer to
* section 12.5 in the PDF Reference Manual and the documentation in derived classes.
*/
@interface Annot : NSObject
{


}





/**
* Creates a new annotation of a given type, in the specified document.
* The newly created annotation does not contain any properties specific
* to a given annotation type, which means an invalid annotation object could be created.
* It is therefore recommended to always create an annotation using type specific methods,
* such as Annots::Line::Create() or Annots::FileAttachment::Create().
* Users should only call Annot::Create() to create annotations of non-standard types
* that are not recognized by PDFTron software (by using Annot::e_Unknown as a type).
*
* @param doc A document to which the annotation is added.
* @param type Subtype of annotation to create.
* @param pos A rectangle specifying the annotation's bounds, specified in
* user space coordinates.
*
* @return A newly created blank annotation for the given annotation type.
*/
+ (Annot*)Create: (SDFDoc*)doc type:  (AnnotType)type pos:  (PDFRect*)pos;	/**
* Create an annotation and initialize it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;

/**
* @return True if this is a valid (non-null) annotation, false otherwise.
* If the function returns false the underlying SDF/Cos object is null or is
* not valid and the annotation object should be treated as a null object.
*/
- (BOOL)IsValid;
/**
* @return The underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;
/**
* @return The type of this annotation. Corresponds to the "Subtype" entry of annotation
* dictionary, as per PDF Reference Manual section 12.5.2
*/
- (AnnotType)GetType;
/**
* @return Annotation's bounding rectangle, specified in user space coordinates.
*
* The meaning of the rectangle depends on the annotation type. For Link and RubberStamp
* annotations, the rectangle specifies the area containing the hyperlink area or stamp.
* For Note annotations, the rectangle is describing the popup window when it's opened.
* When it's closed, the icon is positioned at lower left corner.
*/
- (PDFRect*)GetRect;
/**
* Return true if this annotation is classified as a markup annotation.
*
* @return boolean value, true if this annotation is classified as a markup annotation.
*/
- (BOOL)IsMarkup;
/**
* Sets the size and location of an annotation on its page.
* @param p Annotation's bounding rectangle, specified in user space coordinates.
*
* The meaning of the rectangle depends on the annotation type. For Link and RubberStamp
* annotations, the rectangle specifies the area containing the hyperlink area or stamp.
* For Note annotations, the rectangle is describing the popup window when it's opened.
* When it's closed, the icon is positioned at lower left corner.
*/
- (void)SetRect: (PDFRect*)p;
/**
* Gets the page the annotation is associated with.
*
* @return A Page object or null page object if the page reference is not available.
* The page object returned is an indirect reference to the page object with which
* this annotation is associated.
* This entry shall be present in screen annotations associated with rendition actions.
*
* Optional. PDF 1.3 PDF 1.4 PDF 1.5 not used in FDF files.
*/
- (Page*)GetPage;
/**
* Sets the reference to a page the annotation is associated with.
* (Optional PDF1.3; not used in FDF files)
*
* @param Page The page object user wants the annotation to be associated with.
*
* @note The parameter should be an indirect reference to the page object with
* which this annotation is associated. This entry shall be present in screen
* annotations associated with rendition actions
*/
- (void)SetPage: (Page*)page;
/**
* @return The unique identifier for this annotation, or NULL if the identifier is not
* available. The returned value is a String object and is the value of the "NM"
* field, which was added as an optional attribute in PDF 1.4.
*/
- (Obj*)GetUniqueID;
/**
* Sets the unique identifier for this annotation.
* @param id A buffer containing a unique identifier for this annotation.
* @param id_buf_sz The size of 'id' buffer, or 0 if the string is NULL terminated.
* @note It is necessary to ensure that the unique ID generated is actually unique.
*/
- (void)SetUniqueID: (NSString *)id id_buf_sz:  (int)id_buf_sz;
/**
* Gets an annotation's last modified date.
* @return The annotation's last modified time and date. If the annotation has no associated
* date structure, the returned date is not valid (date.IsValid() returns false). Corresponds
* to the "M" entry of the annotation dictionary.
*/
- (Date*)GetDate;
/**
* Sets an annotation's last modified date.
* @param The annotation's last modified time and date. Corresponds to the "M" entry of the
* annotation dictionary.
*/
- (void)SetDate: (Date*)date;
/**
* @return The value of given Flag
* @param flag The Flag property to query.
*/
- (BOOL)GetFlag: (AnnotFlag)flag;
/**
* Sets the value of given Flag.
*
* @param flag The Flag property to modify.
* @param value The new value for the property.
*/
- (void)SetFlag: (AnnotFlag)flag value:  (BOOL)value;
/**
* Gets the border style for the annotation. Typically used for Link annotations.
*
* @return Annotation's border style.
*/
- (BorderStyle*)GetBorderStyle;
/**
* Sets the border style for the annotation.
*
* @param bs New border style for this annotation.
* @param oldStyleOnly PDF manual specifies two ways to add border information to an annotation object,
* either through an array named 'Border' (PDF 1.0), or a dictionary called 'BS' (PDF 1.2) the latter
* taking precedence over the former. However, if you want to create a border with rounded corners, you can only
* do that using PDF 1.0 Border specification, in which case if you call SetBorderStyle() set the parameter
* oldStyleOnly to true. This parameter has a default value of false in the API and does not need to be used otherwise.
*/
- (void)SetBorderStyle: (BorderStyle*)bs oldStyleOnly:  (BOOL)oldStyleOnly;
/**
* Gets the annotation's appearance for the given combination of annotation
* and appearance states.
*
* @param annot_state the annotation's appearance state, which selects the applicable
* appearance stream from the appearance sub-dictionary. An annotation can define as many
* as three separate appearances: The normal, rollover, and down appearance.

* @param app_state is an optional parameter specifying the appearance state
* to look for (e.g. "Off", "On", etc). If appearance_state is NULL, the choice
* between different appearance states is determined by the AS (Appearance State)
* entry in the annotation dictionary.
*
* @return The appearance stream for this annotation, or NULL if the annotation
* does not have an appearance for the given combination of annotation and
* appearance states.
*/
- (Obj*)GetAppearance: (AnnotationState)annot_state app_state:  (NSString *)app_state;
/**
* Sets the annotation's appearance for the given combination of annotation
* and appearance states.
* (Optional; PDF1.2)
*
* @param app_stream a content stream defining the new appearance.
*
* @param annot_state the annotation's appearance state, which selects the applicable
* appearance stream from the appearance sub-dictionary. An annotation can define as many
* as three separate appearances: The normal, rollover, and down appearance.
*
* @param app_state is an optional parameter specifying the appearance state
* (e.g. "Off", "On", etc) under which the new appearance should be stored. If
* appearance_state is NULL, the annotation will have only one annotation state.
*/
- (void)SetAppearance: (Obj*)app_stream annot_state:  (AnnotationState)annot_state app_state:  (NSString *)app_state;
/**
* Removes the annotation's appearance for the given combination of annotation
* and appearance states.
*
* @param annot_state the annotation's appearance state, which selects the applicable
* appearance stream from the appearance sub-dictionary. An annotation can define as many
* as three separate appearances: The normal, rollover, and down appearance.
*
* @param app_state is an optional parameter specifying the appearance state
* (e.g. "Off", "On", etc) under which the new appearance should be stored. If
* appearance_state is NULL, the annotation will have only one annotation state.
*/
- (void)RemoveAppearance: (AnnotationState)annot_state app_state:  (NSString *)app_state;
/**
* Flatten/Merge the existing annotation appearances with the page content and
* delete this annotation from a given page.
*
* Annotation 'flattening' refers to the operation that changes active annotations
* (such as markup, widgets, 3D models, etc.) into a static area that is part of the
* PDF document, just like the other text and images in the document.
*
* @note an alternative approach to set the annotation as read only is using
* Annot.SetFlag(Annot::e_read_only, true) method. Unlike Annot.SetFlag(...),
* the result of Flatten() operation can not be programatically reversed.
*/
- (void)Flatten: (Page*)page;
/**
* Gets the annotation's active appearance state.
*
* @return the name of the active state.
* The annotation's appearance state, which
* selects the applicable appearance stream from an appearance subdictionary.
*/
- (NSString *)GetActiveAppearanceState;
/**
* Sets the annotation's active appearance state.
* (Required if the appearance dictionary AP contains one or more subdictionaries; PDF1.2)
*
* @param: astate Character string representing the name of the active appearance state.
* The string used to select the annotation's appearance state, which
* selects the applicable appearance stream from an appearance subdictionary.
*/
- (void)SetActiveAppearanceState: (NSString *)astate;
/**
* Gets an annotation's color in RGB color space.
*
* @return A ColorPt object containing an array of three numbers in the range 0.0 to 1.0,
* representing an RGB colour used for the following purposes:
*   - The background of the annotation's icon when closed
*   - The title bar of the annotation's pop-up window
*   - The border of a link annotation
*
*  If the annotation does not specify an explicit color, a default color is returned.
*  Text annotations return 'default yellow;' all others return black.
*/
- (ColorPt*)GetColorAsRGB;
/**
* Returns the annotation's color in CMYK color space.
*
* @return A ColorPt object containing an array of four numbers in the range 0.0 to 1.0,
* representing a CMYK color used for the following purposes:
*   - The background of the annotation's icon when closed
*   - The title bar of the annotation's pop-up window
*   - The border of a link annotation
*
* If the annotation does not specify an explicit color, a default color is returned.
* Text annotations return 'default yellow;' all others return black.
*/
- (ColorPt*)GetColorAsCMYK;
/**
* Returns the annotation's color in Gray color space.
*
* @return A ColorPt object containing a number in the range 0.0 to 1.0,
* representing a Gray Scale color used for the following purposes:
* The background of the annotations icon when closed
* The title bar of the annotations pop-up window
* The border of a link annotation
* If the annotation does not specify an explicit color, black color is returned.
*/
- (ColorPt*)GetColorAsGray;
/**
* Returns the color space the annotation's color is represented in.
*
* @return An integer that is either 1(for DeviceGray), 3(DeviceRGB), or 4(DeviceCMYK).
* If the annotation has no color, i.e. is transparent, 0 will be returned.
*/
- (int)GetColorCompNum;
/**
* Sets an annotation's color.
* (Optional; PDF1.1)
*
* @param c A ColorPt object in RGB or Gray or CMYK color space representing the annotation's color.
* The ColorPt contains an array of numbers in the range 0.0 to 1.0, representing a color used for the following purposes:
*    The background of the annotations icon when closed
*     The title bar of the annotations pop-up window
*     The border of a link annotation
*
* The number of array elements determines the color space in which the color shall be defined:
* 0 No color; transparent
* 1 DeviceGray
* 3 DeviceRGB
* 4 DeviceCMYK
*
* @param comp_num - The number of color components used to represent the color (i.e. 1, 3, 4).
*/
- (void)SetColor: (ColorPt*)c comp_num:  (int)comp_num;
/**
* Returns the struct parent of an annotation.
* (Required if the annotation is a structural content item; PDF1.3)
*
* @return An integer which is the integer key of the annotation's entry
* in the structural parent tree.
* @note The StructParent is the integer key of the annotation's entry
* in the structural parent tree.
*
*/
- (int)GetStructParent;
/**
* Sets the struct parent of an annotation.
* (Required if the annotation is a structural content item; PDF1.3)
*
* @param keyval An integer which is the integer key of the
* annotation's entry in the structural parent tree.
* @note The StructParent is the integer key of the annotation's entry
* in the structural parent tree.
*
*/
- (void)SetStructParent: (int)keyval;
/**
* Returns optional content associated with this annotation.
*
* @return A SDF object corresponding to the group of optional properties.
* @note The return value is an Optional Content Group (OCG) or Optional Content Membership
* Dictionary (PDF::OCG::OCMD) specifying the optional content properties for the annotation.
* Before the annotation is drawn, its visibility shall be determined based on this entry
* as well as the annotation flags specified in the Flag entry. If it is determined to be
* invisible, the annotation shall be skipped, as if it were not in the document.
*/
- (Obj*)GetOptionalContent;
/**
* Associates optional content with this annotation. (Optional, PDF1.5).
*
* @param oc A pointer to an SDF object corresponding to the optional content,
* a PDF::OCG::Group or membership dictionary specifying the PDF::OCG::Group properties for
* the annotation. Before the annotation is drawn, its visibility
* shall be determined based on this entry as well as the annotation
* flags specified in the Flag entry . If it is determined to be invisible,
* the annotation shall be skipped, as if it were not in the document.
*/
- (void)SetOptionalContent: (Obj*)oc;
/**
* Sets the content of this annotation. (Optional).
*
* @param contents A reference to unicode string object with the text that will be associated with
* this annotation. This is the text that annotation displays on user interaction, if the annotation
* type supports it.
*/
- (void)SetContents: (NSString*)contents;
/**
* Extract the content of this annotation. (Optional).
*
* @return  A unicode string object with the text that is associated with
* this annotation. This is the text that annotation displays on user interaction,
* if the annotation type supports it.
*/
- (NSString*)GetContents;
/**
* Regenerates the appearance stream for the annotation.
* This method can be used to auto-generate the annotation appearance after creating
* or modifying the annotation without providing an explicit appearance or
* setting the "NeedAppearances" flag in the AcroForm dictionary.
*
* @note If this annotation contains text, and has been added to a rotated page, the text in
* the annotation may be rotated. If RefreshAppearance is called *after* the annotation is added
* to a rotated page, then any text will be rotated in the opposite direction of the page
* rotation. If this method is called *before* the annotation is added to any rotated page, then
* no counter rotation will be applied. If you wish to call RefreshAppearance on an annotation
* already added to a rotated page, but you don't want the text to be rotated, you can do one
* of the following; temporarily un-rotate the page, or, temporarily remove the "P" object
* from the annotation.
*/
- (void)RefreshAppearance;
/**
* Scales the geometry of the annotation so that its appearance would now fit a new
* rectangle on the page, in user units. Users still have to call RefreshAppearance() later
* if they want a corresponding appearance stream to be generated for the new rectangle.
* The main reason for not combining the two operations together is to be able to resize
* annotations that do not have an appearance stream.
*
* @param newrect A reference to the new rectangle to which this annotation has to be resized.
*/
- (void)Resize: (PDFRect*)newrect;


@end


/**
* A pop-up annotation (PDF 1.3) displays text in a pop-up window for entry and
* editing. It shall not appear alone but is associated with a markup annotation,
* its parent annotation, and shall be used for editing the parents text.
* It shall have no appearance stream or associated actions of its own and
* shall be identified by the Popup entry in the parents annotation dictionary.
*/
@interface Popup : Annot





/**
* Creates a Popup annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a Popup annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Popup annotation in the specified document.
*
* @param doc A document to which the Popup annotation is added.
* @param pos A rectangle specifying the Popup annotation's bounds in default user space units.
*
* @return A newly created blank Popup annotation.
*/
+ (Popup*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
/**
* Returns the parent annotation of the Popup annotation.
*
* @return An annot object which is the parent annotation of the Popup annotation.
* @note This annotation object represents the parent annotation with which this
* pop-up annotation shall be associated.
* @note If this entry is present, the parent annotations Contents, M, C, and T entries
* shall override those of the pop-up annotation itself.
*/
- (Annot*)GetParent;
/**
* Sets the Parent annotation of the Popup annotation.
* (Optional)
*
* @param parent An annot object which is the parent annotation of the Popup annotation.
* @note This annotation object represents the parent annotation with which this
* pop-up annotation shall be associated.
* @note If this entry is present, the parent annotations Contents, M, C, and T entries
* shall override those of the pop-up annotation itself.
*/
- (void)SetParent: (Annot*)parent;
/**
* Returns the initial opening condition of Popup.
*
* @return A bool indicating whether the Popup is initially open.
* @note This is a flag specifying whether the pop-up
* annotation's window shall initially be displayed.
* Default value: false (closed).
*/
- (BOOL)IsOpen;
/**
* Sets the initial opening condition of Popup.
* (Optional)
*
* @param is_open A bool indicating whether the Popup is initially open.
* @note This is a flag specifying whether the pop-up
* annotation's window shall initially be displayed.
* Default value: false (closed).
*/
- (void)SetOpen: (BOOL)is_open;

- (id)init;


@end


/**
* Markup is a base class for a number of annotations types that
* are used to mark up PDF documents. These annotations have text that
* appears as part of the annotation and may be displayed in other ways by a
* conforming reader, such as in a Comments pane.
* Markup annotations may be divided into the following groups:
* - Free text annotations display text directly on the page.
*   The annotations Contents entry specifies the displayed text.
* - Most other markup annotations have an associated pop-up window
*   that may contain text. The annotations Contents entry specifies
*   the text that shall be displayed when the pop-up window is opened.
*   These include text, line, square, circle, polygon, polyline,
*   highlight,underline, squiggly-underline, strikeout, rubber stamp,
*   caret, ink, and file attachment annotations.
* - Sound annotations do not have a pop-up window but may also have
*   associated text specified by the Contents entry.
* - A subset of markup annotations are intended to markup text of a
*   document (e.g. highlight, strikeout, jagged, underline) and they
*   are derived from TextMarkup base class.
*
* @note The pop-up annotation type must not appear by itself; it must be
* associated with a markup annotation that uses it to display text.
*
* The meaning of an annotation's Contents entry varies by annotation type.
* Typically, it is the text that shall be displayed for the annotation or,
* if the annotation does not display text, an alternate description of the
* annotations contents in human-readable form. When separating text into
* paragraphs, a CARRIAGE RETURN (0Dh) must be used.
*/
@interface Markup : Annot





/**
* Creates a markup annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a markup annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Returns the title of the markup annotation.
*
* @return A string representing the title of the markup annotation,
* or null is the title is not specified.
*
* @note The title is The text label that is displayed in the
* title bar of the annotations pop-up window when open and active
* Markup annotation.
* This entry is also used to identify the user who added the annotation.
* It corresponds to the 'T' field of the annotation's dictionary.
*/
- (NSString*)GetTitle;
/**
* Sets the title of the markup annotation.
* (Optional; PDF1.1)
*
* @param title A string.
* @note The title is The text label that is displayed in the
* title bar of the annotations pop-up window when open and active
* Markup annotation.
* This entry is also used to identify the user who added the annotation.
* It corresponds to the 'T' field of the annotation's dictionary.
*/
- (void)SetTitle: (NSString*)title;
/**
* Returns the Popup object associated with this markup annotation.
*
* @return A Popup object that is associated with this markup annotation.
* @note The Popup is An indirect reference to a pop-up annotation for
* entering or editing the text associated with this annotation.
*/
- (Popup*)GetPopup;
/**
* Sets the Popup object associated with this markup annotation.
* (Optional; PDF1.3 )
*
* @param bs A Popup object that is associated with this markup annotation.
* @note the Popup is An indirect reference to a pop-up annotation for
* entering or editing the text associated with this annotation.
*/
- (void)SetPopup: (Popup*)bs;
/**
* @return The opacity value.
* Default value: 1.0.
* @note This value is applied to all visible elements of the annotation in its closed state
* (including its background and border) but not to the pop-up window that appears when
* the annotation is opened. When an appearance stream is presented with the annotation,
* this entry is ignored.(However, if the compliant viewer regenerates
* the annotations appearance stream, it may incorporate this Opacity entry
* into the streams content.)
* @note This corresponds to the 'CA' field of the annotation's dictionary.
*/
- (double)GetOpacity;
/**
* Sets the opacity value for the annotation.
* (Optional; PDF1.4 )
*
* @param op A number indicating the Markup annotation's opacity value.
* Default value: 1.0.
* @note This value is applied to all visible elements of the annotation in its closed state
* (including its background and border) but not to the pop-up window that appears when
* the annotation is opened. When an appearance stream is presented with the annotation,
* this entry is ignored.(However, if the compliant viewer regenerates
* the annotations appearance stream, it may incorporate this Opacity entry
* into the streams content.)
* @note This corresponds to the 'CA' field of the annotation's dictionary.
*/
- (void)SetOpacity: (double)op;
/**
* Returns the subject of the Markup annotation.
* (PDF 1.5)
*
* @return A string representing the subject of the Markup annotation.
* @note The subject is a short piece of text description about the annotation.
* @note This corresponds to the 'Subj' field of the annotation's dictionary.
*/
- (NSString*)GetSubject;
/**
* Sets subject of the Markup annotation.
* (Optional; PDF 1.5 )
*
* @param subj A string representing the subject of the Markup annotation.
* @note The subject is a short piece of text description about the annotation.
* @note This corresponds to the 'Subj' field of the annotation's dictionary.
*/
- (void)SetSubject: (NSString*)subj;
/**
* @return The creation date for the markup annotation.
*
* @note This corresponds to the 'CreationDate' field of the markup annotation's dictionary.
*/
- (Date*)GetCreationDates;
/**
* Sets the creation date for the markup annotation.
* (Optional; PDF 1.5 )
*
* @param dt A Date object indicating the date the markup annotation is created.
* @note This corresponds to the 'CreationDate' field of the markup annotation's dictionary.
*/
- (void)SetCreationDates: (Date*)dt;
/**
* @return the border effect of the markup annotation.
* Default value: e_None.
*
* Beginning with PDF 1.5, some annotations (square, circle, and polygon) may have a 'BE' entry,
* which is a border effect dictionary that specifies an effect that shall be applied to the border
* of the annotations. Beginning with PDF 1.6, the free text annotation may also have a BE entry.
* @note When "e_Cloudy" is chosen,the width and
* dash array specified by the annotation's BorderStyle entry
* needs to be taken into consideration.
*/
- (BorderEffect)GetBorderEffect;
/**
* Sets the border effect of the markup annotation. (Optional; PDF 1.5 )
*
* Beginning with PDF 1.5, some annotations (square, circle, and polygon) may have a 'BE' entry,
* which is a border effect dictionary that specifies an effect that shall be applied to the border
* of the annotations. Beginning with PDF 1.6, the free text annotation may also have a BE entry.
* @param effect An entry from the enum "BorderEffect" that
* represents the border effect of the Markup annotation.
* Default value: e_None.
* @note When "e_Cloudy" is chosen,the width and
* dash array specified by the annotation's BorderStyle entry
* needs to be taken into consideration.
*/
- (void)SetBorderEffect: (BorderEffect)effect;
/**
* @return A number describing the intensity of the border effect, in the range 0 to 2.
*
* Beginning with PDF 1.5, some annotations (square, circle, and polygon) may have a 'BE' entry,
* which is a border effect dictionary that specifies an effect that shall be applied to the border
* of the annotations. Beginning with PDF 1.6, the free text annotation may also have a BE entry.
* @param effect An entry from the enum "BorderEffect" that
* represents the border effect of the Markup annotation.
* @note this parameter applies only if border effect is e_Cloudy.
* @default 0
*/
- (double)GetBorderEffectIntensity;
/**
* Sets the border effect intensity of the markup annotation.
* (Optional; valid only if Border effect is Cloudy)
*
* Beginning with PDF 1.5, some annotations (square, circle, and polygon) may have a 'BE' entry,
* which is a border effect dictionary that specifies an effect that shall be applied to the border
* of the annotations. Beginning with PDF 1.6, the free text annotation may also have a BE entry.
* @param effect An entry from the enum "BorderEffect" that
* represents the border effect of the Markup annotation.
* @param intensity A number describing the intensity of the border effect, in the
* range 0 (which is default) to 2.
* @note this parameter applies only if Border effect is e_Cloudy.
*/
- (void)SetBorderEffectIntensity: (double)intensity;
/**
* Returns the interior color of the annotation.
*
* @return A ColorPt object that denotes the color of the annotation.
* @note The color can be in different color spaces: Gray, RGB, or CMYK.
* Call "GetInteriorColorCompNum" to access the color space information.
* @note According to PDF Reference Manual interior color is not the property
* that is expected for Markup annotations in general, but it applies
* to many derived annotations (Line,Square,Circle,Polygon,PolyLine,Redaction) and therefore get()/set() methods are
* provided in the base class Markup. Annotations that do not use interior color
* will ignore the interior color ('IC' entry), if present in their annotation dictionary.
* In case no color is specified, CMYK white is returned.
*/
- (ColorPt*)GetInteriorColor;
/**
* Returns the number indicating the interior color space of the annotation.
*
* @return An integer indicating the number of channels forming the color space.
* 3 corresponds to RGB, 4 corresponds to CMYK, and 1 corresponds to Gray.
* If the interior is transparent, the return value is 0.
*/
- (int)GetInteriorColorCompNum;
/**
* Sets the interior color of the Markup annotation.
*
* @param c A ColorPt object that denotes the color of the Markup annotation.
* @param CompNum An integer indicating the number of channels forming the
* color space used. It also defines the length of the array to be allocated
* for storing the entries of c.
* @note It is necessary to make sure the consistency between the type of
* parameter c and the value of parameter CompNum. RGB ColorPt corresponds to 3,
* CMYK ColorPt corresponds to 4, Gray ColorPt corresponds to 1, and transparent
* corresponds to 0.
* @note According to PDF Reference Manual interior color is not the property
* that is expected for Markup annotations in general, but it applies
* to many derived annotation classes and therefore get()/set() methods are
* provided in the base class Markup. Annotations that do not use interior color
* will ignore the interior color ('IC' entry), if present in their annotation dictionary.
*
* Entries out of the specified color space array length will be discarded.
* Missing entries for a specified color space will lead to potential
* exceptions.
*/
- (void)SetInteriorColor: (ColorPt*)c CompNum:  (int)CompNum;
/**
* Returns the inner bounding rectangle of the Markup annotation.
*
* @return A rectangle specifying the region where content should be displayed.
*
* @note This rectangle can be same as or inside of  the annotations rectangle.
* If it is smaller, such a difference may occur in
* situations where a border effect causes the size of the annotation Rect
* entry to increase beyond that of the rectangle. For FreeText annotation with
* a callout, content rectangle specifies an inner region for the text to be displayed.
* @note According to PDF Reference Manual content rectangle is not the property
* that is expected for Markup annotations in general, but it applies
* to many derived annotation classes (FreeText,Square,Circle,Caret) and therefore get()/set() methods are
* provided in the base class Markup. Annotations that do not use this property
* will ignore the content rectangle ('RD' entry), if present in their annotation dictionary.
*/
- (PDFRect*)GetContentRect;
/**
* Sets the inner bounding rectangle of the Markup annotation. (Optional)
*
* @param cr A Rect struct to be assign to the 'RD' entry of the annotation dictionary.
* @note This rectangle can be same as or inside of  the annotations rectangle.
* If it is smaller, such a difference may occur in
* situations where a border effect causes the size of the annotation Rect
* entry to increase beyond that of the rectangle. For FreeText annotation with
* a callout, content rectangle specifies an inner region for the text to be displayed.
* @note According to PDF Reference Manual content rectangle is not the property
* that is expected for Markup annotations in general, but it applies
* to many derived annotation classes (FreeText,Square,Circle,Caret) and therefore get()/set() methods are
* provided in the base class Markup. Annotations that do not use this property
* will ignore the content rectangle ('RD' entry), if present in their annotation dictionary.
*/
- (void)SetContentRect: (PDFRect*)cr;
/**
* Returns the rectangle difference between overall annotation rectangle and content rectangle.
*
* @return A set of four numbers represented as a Rect struct.
* @note The four numbers of the returning struct specify the difference
* between two rectangles: the Rect entry of the annotation and the actual
* bounding box of the underlying rectangle. Such a difference may occur in
* situations where a border effect causes the size of the annotation Rect
* entry to increase beyond that of the rectangle.
* The four numbers of the returning struct correspond to the differences
* in default user space, between the left, top, right, and bottom of the
* two above mentioned rectangles.
* @note GetPadding() and GetContentRectangle() both use 'RD' entry of the
* annotation dictionary, but represent it to user in different ways.
* @see GetContentRect()
*/
- (PDFRect*)GetPadding;
/**
* Sets the rectangle difference between overall annotation rectangle and content rectangle. (Optional)
*
* @param rd A set of four numbers represented as a Rect struct
* @note The four numbers of rd specify the difference
* between two rectangles: the Rect entry of the annotation and the actual
* bounding box of the underlying rectangle. Such a difference may occur in
* situations where a border effect causes the size of the annotation Rect
* entry to increase beyond that of the rectangle.
* The four numbers of the rd correspond to the differences
* in default user space, between the left, top, right, and bottom of the
* two above mentioned rectangles.
* @note SetPadding() and SetContentRectangle() both use 'RD' entry of the
* annotation dictionary. Two methods are provided to give users additional
* flexibility and ease of use in setting the values of the 'RD' field.
* @see GetContentRect()
*/
- (void)SetPaddingWithRect: (PDFRect*)rd;
- (void)SetPadding: (double)x;

- (id)init;


@end


/**
* A file attachment annotation contains a reference to a file, which may be
* embedded in the PDF document.
*/
@interface FileAttachment : Markup





/**
* Creates an FileAttachment annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates an FileAttachment annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a file attachment annotation.
*
* A file attachment annotation contains a reference to a file, which typically
* is embedded in the PDF file.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds, in user space coordinates.
* @param icon_name The name of an icon to be used in displaying the annotation, default is PushPin.
* @note PDF Viewer applications should provide predefined icon appearances for at least
* the following standard names: Graph, PushPin, Paperclip, Tag. Additional names may
* be supported as well. Default value: PushPin.
*
* @return A new file attachment annotation.
*/
+ (FileAttachment*)CreateFileAttchWithFileSpec: (SDFDoc*)doc pos:  (PDFRect*)pos fs:  (FileSpec*)fs icon_name:  (FileIcon)icon_name;
+ (FileAttachment*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos fs:  (FileSpec*)fs;
/**
* Creates a file attachment annotation.
*
* A file attachment annotation contains a reference to a file, which typically
* is embedded in the PDF file.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds, in user space coordinates.
* @param icon_name The name of an icon to be used in displaying the annotation, default is PushPin.
* @note PDF Viewer applications should provide predefined icon appearances for at least
* the following standard names: Graph PushPin Paperclip Tag. Additional names may
* be supported as well. Default value: PushPin.
*
* @return A new file attachment annotation.
*/
+ (FileAttachment*)CreateFileAttchWithPath: (SDFDoc*)doc pos:  (PDFRect*)pos path:  (NSString*)path icon_name:  (FileIcon)icon_name;
/**
* Creates a file attachment annotation. This method should be used when a nonstandard
* icon type is desired in the annotation.
*
* A file attachment annotation contains a reference to a file, which typically
* is embedded in the PDF file.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds, in user space coordinates.
* @param icon_name The name of an icon to be used in displaying the annotation, default is PushPin.
* @note PDF Viewer applications should provide predefined icon appearances for at least
* the following standard names: Graph PushPin Paperclip Tag. Additional names may
* be supported as well. Default value: PushPin.
*
* @return A new file attachment annotation.
*/
+ (FileAttachment*)CreateFileAttchWithIconName: (SDFDoc*)doc pos:  (PDFRect*)pos path:  (NSString*)path icon_name:  (NSString *)icon_name;
/**
* @return the file specification that contains a file reference or the embedded file data stream.
*/
- (FileSpec*)GetFileSpec;
/**
* Sets the file specification.
*
* @param file The file specification to associate with this annotation..
* The file specification contains a file reference or the embedded file data stream.
*/
- (void)SetFileSpec: (FileSpec*)file;
/**
* The function saves the data referenced by this File Attachment to an
* external file.
*
* If the file is embedded, the function saves the embedded file.
* If the file is not embedded, the function will copy the external file.
* If the file is not embedded and the external file can't be found, the function
* returns false.
*
* @param save_as An optional parameter indicating the filepath and filename
* where the data should be saved. If this parameter is not specified the function
* will attempt to save the file using FileSpec.GetFilePath().
*
* @return true is the file was saved successfully, false otherwise.
*
*/
- (BOOL)Export: (NSString*)save_as;
/**
* @return the type the associated icon style.
* @default e_PushPin
* @note The annotation dictionary's appearance stream, if present, will take precedence over this entry
* when displaying the annotation in the viewer.
*/
- (FileIcon)GetIcon;
/**
* Sets the icon style associated with FileAttachment annotation.
* (Optional)
*
* @param type icon style.
* @default e_PushPin
* @note The annotation dictionary's appearance stream, if present, will take precedence over this entry
* when displaying the annotation in the viewer.
*/
- (void)SetIcon: (FileIcon)type;
/**
* Returns the name of the icon associated with the FileAttachment annotation.
*
* @return A string denoting the name of the icon.
*
* @see GetIcon() GetIconName() returns the icon name as it appears in the annotation dictionary, while GetIcon() returns
* the same icon name converted to enumeration value.
* @note The annotation dictionary's appearance stream, if present, will take precedence over this entry
* when displaying the annotation in the viewer.
*/
- (NSString *)GetIconName;
/**
* Sets the name of the icon associated with the FileAttachment annotation.
* (Optional)
*
* @param icon A string.denoting the name of the icon.
* @note this method should be used to assign non-standard icon type to the annotation.
* @see SetIcon()
* @note The annotation dictionary's appearance stream, if present, will take precedence over this entry
* when displaying the annotation in the viewer.
*/
- (void)SetIconName: (NSString *)icon;

- (id)init;


@end


@interface QuadPoint : TRN_quadpoint




- (id)init;
- (id)initWithP11: (PDFPoint*)p11 p22:  (PDFPoint*)p22 p33:  (PDFPoint*)p33 p44:  (PDFPoint*)p44;
- (id)initWithR: (PDFRect*)r;
@end


/**
* A TextMarkup is a base class for highlight, underline,
* strikeout, and squiggly annotations.
*/
@interface TextMarkup : Markup





/**
* Creates a TextMarkup annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a TextMarkup annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Returns the number of QuadPoints in the QuadPoints array of the TextMarkup annotation
* (PDF 1.6)
*
* @return The number of QuadPoints.
* @note QuadPoints specify the coordinates of quadrilaterals in default user space. Each quadrilateral
* encompasses a word or group of contiguous words in the text underlying the annotation.
* The four points(p1, p2, p3, p4) of a QuadPoint specify the quadrilaterals four vertices
* in counterclockwise order.
* The text needs to be oriented with respect to the edge connecting points (p1) and (p2).
* The annotation dictionarys Appearance entry, if present, takes precedence over QuadPoints.
*/
- (int)GetQuadPointCount;
/**
* Returns the QuadPoint located at a certain index of the QuadPoint array.
* (PDF 1.6)
*
* @param idx The index where the QuadPoint is located. The index starts at zero and must be less than return value of GetQuadPointCount().
* @return The QuadPoint located at a certain index of the QuadPoint array of the TextMarkup annotation.
* @note QuadPoints specify the coordinates of quadrilaterals in default user space. Each quadrilateral
* encompasses a word or group of contiguous words in the text underlying the annotation.
* The four points(p1, p2, p3, p4) of a QuadPoint specify the quadrilaterals four vertices
* in counterclockwise order.
* The text needs to be oriented with respect to the edge connecting points (p1) and (p2).
* The annotation dictionarys Appearance entry, if present, takes precedence over QuadPoints.
*/
- (QuadPoint*)GetQuadPoint: (int)idx;
/**
* Sets the QuadPoint to be located at a certain index of the QuadPoint array.
* (Optional; PDF1.6 )
*
* @param idx The index where the QuadPoint is to be located (the index is counted from 0).
* @param qp The QuadPoint to be located at a certain index of the QuadPoint array of the TextMarkup annotation.
* @attention To make this QuadPoint compatible with Adobe Acrobat|Reader, you can use either clockwise or counterclockwise order,
* but the points p3 and p4 must be swapped. This is because those readers do not follow the PDF specification for TextMarkup QuadPoints.
* @note An array of n QuadPoints specifying the coordinates of n quadrilaterals in default user space. Each quadrilateral shall
* encompasses a word or group of contiguous words in the text underlying the annotation. The coordinates for each quadrilateral
* shall be given in the order p1, p2, p3, p4 specifying the quadrilaterals four vertices in counterclockwise order.
* The text shall be oriented with respect to the edge connecting points (p1) and (p2).
* The annotation dictionarys Appearance(AP) entry, if present, shall take precedence over QuadPoints.
*/
- (void)SetQuadPoint: (int)idx qp:  (QuadPoint*)qp;



@end


/**
* An ink annotation (PDF 1.3) represents a freehand scribble composed
* of one or more disjoint paths. When opened, it shall display a pop-up
* window containing the text of the associated note.
*/
@interface Ink : Markup





/**
* Creates an Ink annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates an Ink annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Ink annotation in the specified document.
*
* @param doc A document to which the Ink annotation is added.
* @param pos A rectangle specifying the Ink annotation's bounds in default user space units.
*
* @return A newly created blank Ink annotation.
*/
+ (Ink*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
/**
* Returns number of paths in the annotation.
*
* @return An integer representing the number of paths in the 'InkList'
* entry of the annotation dictionary.
* @note Each path is an array of Point objects specifying points along the path.
* When drawn, the points shall be connected by straight lines or curves
* in an implementation-dependent way.
*/
- (int)GetPathCount;
/**
* Returns number of points in a certain stroked path in the InkList.
*
* @param pathindex path index for each the point count is returned. Index starts at 0.
* @return An integer representing the number of points in the stroked path of the Ink list.
* @see GetPathCount()
*/
- (int)GetPointCount: (unsigned int)pathindex;
/**
* Returns the specific point in a given path.
*
* @param pathindex path index for each the point is returned. Index starts at 0.
* @param pointindex index of point in the path. Index starts at 0.
* @return A Point object for specified path and point index.
* @note Each path is an array of Point objects specifying points along the path.
* When drawn, the points shall be connected by straight lines or curves
* in an implementation-dependent way.
*/
- (PDFPoint*)GetPoint: (unsigned int)pathindex pointindex:  (unsigned int)pointindex;
/**
* Sets the specific point in the Ink List, adding it if needed.
*
* @param pathindex An unsigned integer indicating the index of the path.
* @param pointindex An unsigned integer indicating the index of the point
* within the stroked path indicated by the parameter "pathindex".
* @param pt A Point object that is to be assigned.
* @note Ink annotation contains an array of paths.
* Each path is an array of Point objects specifying points along the path.
* When drawn, the points shall be connected by straight lines or curves
* in an implementation-dependent way.
*/
- (void)SetPoint: (unsigned int)pathindex pointindex:  (unsigned int)pointindex pt:  (PDFPoint*)pt;

- (id)init;


@end


/**
* A destination defines a particular view of a document, consisting of the
* following:
*
* - The page of the document to be displayed
* - The location of the document window on that page
* - The magnification (zoom) factor to use when displaying the page
*
* Destinations may be associated with Bookmarks, Annotations, and Remote Go-To Actions.
*
* Destination is a utility class used to simplify work with PDF Destinations;
* Please refer to section 8.2.1 'Destinations' in PDF Reference Manual for details.
*/
@interface Destination : NSObject
{


}





/**
* Create a new 'XYZ' Destination.
*
* The new Destination displays the page designated by 'page', with the
* coordinates ('left', 'top') positioned at the top-left corner of the
* window and the contents of the page magnified by the factor 'zoom'.
* A null value for any of the parameters 'left', 'top', or 'zoom' specifies
* that the current value of that parameter is to be retained unchanged.
* A 'zoom' value of 0 has the same meaning as a null value.
*/
+ (Destination*)CreateXYZ: (Page*)page left:  (double)left top:  (double)top zoom:  (double)zoom;
/**
* Create a new 'Fit' Destination.
*
* The new Destination displays the page designated by 'page', with its contents
* magnified just enough to fit the entire page within the window both
* horizontally and vertically. If the required horizontal and vertical
* magnification factors are different, use the smaller of the two, centering
* the page within the window in the other dimension.
*/
+ (Destination*)CreateFit: (Page*)page;
/**
* Create a new 'FitH' Destination.
*
* The new Destination displays the page designated by 'page', with the
* vertical coordinate 'top' positioned at the top edge of the window and
* the contents of the page magnified just enough to fit the entire width
* of the page within the window.
*/
+ (Destination*)CreateFitH: (Page*)page top:  (double)top;
/**
* Create a new 'FitV' Destination.
*
* The new Destination displays the page designated by 'page', with the
* horizontal coordinate 'left' positioned at the left edge of the window
* and the contents of the page magnified just enough to fit the entire
* height of the page within the window.
*/
+ (Destination*)CreateFitV: (Page*)page left:  (double)left;
/**
* Create a new 'FitR' Destination.
*
* The new Destination displays the page designated by 'page', with its
* contents magnified just enough to fit the rectangle specified by the
* coordinates 'left', 'bottom', 'right', and 'top' entirely within the
* window both horizontally and vertically. If the required horizontal
* and vertical magnification factors are different, use the smaller of
* the two, centering the rectangle within the window in the other
* dimension.
*/
+ (Destination*)CreateFitR: (Page*)page left:  (double)left bottom:  (double)bottom right:  (double)right top:  (double)top;
/**
* Create a new 'FitB' Destination.
*
* The new Destination displays the page designated by 'page', with its
* contents magnified just enough to fit its bounding box entirely within
* the window both horizontally and vertically. If the required
* horizontal and vertical magnification factors are different, use the
* smaller of the two, centering the bounding box within the window in
* the other dimension.
*/
+ (Destination*)CreateFitB: (Page*)page;
/**
* Create a new 'FitBH' Destination.
*
* The new Destination displays the page designated by 'page', with
* the vertical coordinate 'top' positioned at the top edge of the window
* and the contents of the page magnified just enough to fit the entire
* width of its bounding box within the window.
*/
+ (Destination*)CreateFitBH: (Page*)page top:  (double)top;
/**
* Create a new 'FitBV' Destination.
*
* The new Destination displays Display the page designated by 'page',
* with the horizontal coordinate 'left' positioned at the left edge of
* the window and the contents of the page magnified just enough to fit
* the entire height of its bounding box within the window.
*/
+ (Destination*)CreateFitBV: (Page*)page left:  (double)left;	/**
* Create a Destination and initialize it using given Cos/SDF object.
*
* @param dest - a low-level (SDF/Cos) destination object. The low-level
* destination can be either a named destination (i.e. a Name or a String)
* or an explicit destination (i.e. an Array Obj). Please refer to section
* 8.2.1 'Destinations' in PDF Reference Manual for more details.
*
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*
* @note Named destinations (in case 'dest' is a Name or a String) are
* automatically resolved to the explicit destination. If the name can't
* be resolved to the explicit destination dest.IsValid() will return false.
*/
- (id)initWithDest: (Obj*)dest;

/**
* @return True if this is a valid Destination and can be resolved, false otherwise.
*
* @note If this method returns false the underlying SDF/Cos object is null and
* the Action object should be treated as null as well.
*/
- (BOOL)IsValid;
/**
* @return destination's FitType.
* @exception An Exception is thrown if this is not a valid Destination.
*/
- (FitType)GetFitType;
/**
* @return the Page that this destination refers to.
* @exception An Exception is thrown if this is not a valid Destination.
*/
- (Page*)GetPage;
/**
* Modify the destination so that it refers to the new 'page' as the destination page.
*
* @param page The new page associated with this Destination.
* @exception An Exception is thrown if this is not a valid Destination.
*/
- (void)SetPage: (Page*)page;
/**
* @return the object to the underlying SDF/Cos object.
* The returned SDF/Cos object is an explicit destination (i.e. the Obj is either
* an array defining the destination, using the syntax shown in Table 8.2 in PDF
* Reference Manual), or a dictionary with a 'D' entry whose value is such an
* array. The latter form allows additional attributes to be associated with
* the destination
*/
- (Obj*)GetSDFObj;
/**
* @return the explicit destination SDF/Cos object. This is always an Array
* as shown in Table 8.2 in PDF Reference Manual.
*
* @exception An Exception is thrown if this is not a valid Destination.
*/
- (Obj*)GetExplicitDestObj;


@end


/**
* Actions are typically what happens when a user clicks on a link or bookmark.
*
* Instead of simply jumping to a destination in the document, an annotation or
* outline item can specify an action for the viewer application to perform, such
* as launching an application, playing a sound, or changing an annotations
* appearance state.
*
* @note Although the Action class provides utility functions for most commonly used
* action types, it is possible to read, write, and edit any action type using SDF API
* and dictionary entries described in Section 8.5 in the PDF Reference Manual.
*/
@interface Action : NSObject
{


}





/**
* Creates a new 'GoTo'action. GoTo action takes the user to the
* specified Destination view located in the same document.
*
* @param dest A Destination for the new Action.
*
* @note This method can only be used for destinations in the same
* document as the source document. For cross-document links use
* Action::CreateGotoRemote().
*/
+ (Action*)CreateGoto: (Destination*)dest;
/**
* Creates a new 'GoTo' action using a 'Named Destination'. GoTo action
* takes the user to the specified 'Named Destination' view located in the
* same document.
*
* @param key - a string buffer representing the destination name. The named
* destination will be stored in document's '/Dest' SDF::NameTree.
* @param key_sz The size in bytes of the key buffer.
* @param dest The explicit destination used to create the named destination.
*/
+ (Action*)CreateGotoWithNamedDestination: (NSData*)key key_sz:  (int)key_sz dest:  (Destination*)dest;
/**
* Creates a new 'GoToR'action. A remote go-to action is similar to an
* ordinary go-to action but jumps to a destination in another PDF file
* instead of the current file.
*
* @param file The file referred to by the action.
* @param page_num A page number within the remote document. The first page is
* numbered 0.
* @new_window A flag specifying whether to open the destination document
* in a new window. If new_window is false, the destination document replaces
* the current document in the same window, otherwise the viewer application
* should behave in accordance with the current user preference.
*/
+ (Action*)CreateGotoRemote: (FileSpec*)file page_num:  (int)page_num;
/**
* Creates a new 'GoToR'action. See the above method for details.
*
* @param file The file referred to by the action.
* @param page_num A page number within the remote document. The first page is
* numbered 0.
* @new_window A flag specifying whether to open the destination document
* in a new window. If new_window is false, the destination document replaces
* the current document in the same window, otherwise the viewer application
* should behave in accordance with the current user preference.
*/
+ (Action*)CreateGotoRemoteWithNewWindow: (FileSpec*)file page_num:  (int)page_num new_window:  (BOOL)new_window;
/**
* Create a new URI action. The URI action is typically resolved by opening a URL in
* the default web browser.
*
* @param doc The document in which to create the action.
* @param uri The uniform resource identifier to resolve, encoded in 7-bit ASCII.
* A uniform resource identifier (URI) is a string that identifies (resolves to) a resource
* on the Internet; typically a file that is the destination of a hypertext link, although
* it can also resolve to a query or other entity. (URIs are described in Internet RFC 2396,
* Uniform Resource Identifiers (URI).
*/
+ (Action*)CreateURI: (SDFDoc*)doc uri:  (NSString *)uri;
/**
* Creates a new 'SubmitForm'action. A submit-form action transmits the names
* and values of selected interactive form fields to a specified uniform
* resource locator (URL), presumably the address of a Web server that will
* process them and send back a response.
*
* @param url A URL file specification giving the uniform resource locator (URL)
* of the script at the Web server that will process the submission.
*/
+ (Action*)CreateSubmitForm: (FileSpec*)url;
/**
* Creates a new 'Launch' action. A launch action opens up a file using the
* most appropriate program.
*
* @param doc the document in which to create the action
* @param path the full path of the file to be opened
*/
+ (Action*)CreateLaunch: (SDFDoc*)doc path:  (NSString *)path;
/**
* Creates a new 'Show/Hide Field' action. A show/hide field action shows
* or hide certain fields when it's invoked.
*
* @param doc the document in which to create the action
* @param field the list of fields to hide
* @param cnt the number of fields to hide
*/
+ (Action*)CreateHideField: (SDFDoc*)doc list_length:  (int)list_length field_list:  (NSMutableArray*)field_list;
/**
* Creates a new 'Import Data' action. An import data action imports
* form data from a FDF file into a PDF document.
*
* @param doc the document in which to create the action
* @param path the full path of the FDF file
*/
+ (Action*)CreateImportData: (SDFDoc*)doc path:  (NSString *)path;
/**
* Creates a new 'Reset Form' action. A reset form action reset chosen
* form fields to their default value.
*
* @param doc the document in which to create the action
* @param field the list of fields to reset
* @param cnt the number of fields to reset
*/
+ (Action*)CreateResetForm: (SDFDoc*)doc;
/**
* Creates a new 'JavaScript' action. A javascript action executes a JavaScript
* script when it's invoked.
*
* @param doc the document in which to create the action
* @param script the JavaScript script to be executed
*/
+ (Action*)CreateJavaScript: (SDFDoc*)doc script:  (NSString *)script;	/**
* A constructor. Creates an Action and initializes it using given Cos/SDF object.
*
* @param in_obj Pointer to the Cos/SDF object.
*
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithIn_obj: (Obj*)in_obj;

/**
* Indicates whether the Action is valid (non-null).
*
* @return True if this is a valid (non-null) Action; otherwise false.
*
* @note If this method returns false the underlying SDF/Cos object is null and
* the Action object should be treated as null as well.
*/
- (BOOL)IsValid;
/**
* @return The type of this Action.
*/
- (ActionType)GetType;
/**
* Executes current action; this will only work for some action types that can be executed
* only using the information contained in the action object or the associated PDF doc.
* See also PDFViewCtrl::ExecuteAction()
*/
- (void)Execute;
/**
* @return The next action dictionary, an array of action dictionaries,
* or NULL if there are no additional actions.
*
* Sequences of actions can be chained together. For example, the effect
* of clicking a link annotation with the mouse might be to play a sound,
* jump to a new page, and start up a movie. Note that the Next entry is
* not restricted to a single action but may contain an array of actions,
* each of which in turn may have a Next entry of its own. The actions may
* thus form a tree instead of a simple linked list. Actions within each
* Next array are executed in order, each followed in turn by any actions
* specified in its Next entry, and so on recursively.
*/
- (Obj*)GetNext;
/**
* @return The Actions Destination view.
*
* @note This only works for Actions whose subtype is "GoTo".
*
* @note All named destinations are automatically resolved to the
* explicit destination so you can access destination members directly.
*/
- (Destination*)GetDest;
/**
* @return value of the given action flag.
*
* Action flags are currently only used by submit and reset form actions.
*/
- (BOOL)GetFormActionFlag: (FormActionFlag)flag;
/**
* Set the value of a given field flag.
*
* Action flags are currently only used by submit and reset form actions.
*/
- (void)SetFormActionFlag: (FormActionFlag)flag value:  (BOOL)value;
/**
* @return Pointer to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;


@end


/**
* Construct a FDF::FDFField from a SDF dictionary representing a terminal field node.
*/
- (id)initWithField_dict: (Obj*)field_dict fdf_dict:  (Obj*)fdf_dict;
@interface FDFField : NSObject
{


}




/**
* @return the value of the Field (the value of its /V key) or NULL if the
* value is not specified.
* The format of fields value varies depending on the field type.
*/
- (Obj*)GetValue;
/**
* Sets the value of the FDFField (the value of the field's /V key).
* @return the value of the field (the value of its /V key) or NULL if the
* value is not specified.
* The format of fields value varies depending on the field type.
*
* @note in order to remove/erase the existing value use SetValue(SDF::Null)
*/
- (void)SetValue: (Obj*)value;
/**
* @return a string representing the fully qualified name of the field
* (e.g. "employee.name.first").
*/
- (NSString*)GetName;
/**
* @return a string representing the partial name of the field (e.g.
* "first" when "employee.name.first" is fully qualified name).
*/
- (NSString*)GetPartialName;
/**
* @return the object to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;
/**
* The function returns the specified attribute.
*
* @return return the attribute value if the given attribute name
* was found or a NULL object if the given attribute name was not found.
*/
- (Obj*)FindAttribute: (NSString *)attrib;


@end


@interface FDFFieldIterator : NSObject
{


}





- (void)Next;
- (FDFField*)Current;
- (BOOL)HasNext;
- (id)init;
@end


/**
* FDFDoc is a class representing Forms Data Format (FDF) documents.
* FDF is typically used when submitting form data to a server, receiving
* the response, and incorporating it into the interactive form. It can also
* be used to export form data to stand-alone files that can be stored, transmitted
* electronically, and imported back into the corresponding PDF interactive form.
* In addition, beginning in PDF 1.3, FDF can be used to define a container for
* annotations that are separate from the PDF document to which they apply.
*/
@interface FDFDoc : NSObject
{


}





/**
* Create a FDF document from an existing SDF/Cos document.
*
* @param sdfdoc An SDF document. FDFDoc will take the ownership of the low-level document.
* @note the SDFDoc will become invalid.  If you would
* like to access the low level document use GetSDFDoc
*/
- (id)initWithSdfdoc: (SDFDoc*)sdfdoc;
/**
* Open an existing FDF document
*
* @param filepath - pathname to the file.
*/
- (id)initWithFilepath: (NSString*)filepath;
/**
* Open an existing FDF document
*
* @param stream - input stream containing a serialized document. The input stream may be a
* random-access file, memory buffer, slow HTTP connection etc.
*
* @note if the input stream doesn't support Seek() operation the document will load whole
* data stream in memory before parsing. In case of linearized FDF, the document may be parsed
* on-the-fly while it is being loaded in memory. Note that since StdFile implements Seek()
* interface, the document does not have to be fully in memory before it is used.
*
* @note Make sure to call InitSecurityHandler() after FDFDoc(...) for encrypted documents.
*/
- (id)initWithStream: (Filter*)stream;
/**
*	Close FDFDoc
*/
- (void)Close;
/**
* @return - true if document was modified, false otherwise
*/
- (BOOL)IsModified;
/**
* Saves the document to a file.
*
* If a full save is requested to the original path, the file is saved to a file
* system-determined temporary file, the old file is deleted, and the temporary file
* is renamed to path.
*
* A full save with remove unused or linearization option may re-arrange object in
* the cross reference table. Therefore all pointers and references to document objects
* and resources should be re acquired in order to continue document editing.
*
* In order to use incremental save the specified path must match original path and
* e_incremental flag bit should be set.
*
* @param path - The full path name to which the file is saved.
*
* @exception - if the file can't be opened for saving or if there is a problem during Save
*	an Exception object will be thrown.
*/
- (void)SaveFDFDocToFile: (NSString*)path;
/**
* Saves the document to a memory buffer.
*
* @param out_buf a pointer to the buffer containing the serialized version of the
* document. (C++ Note) The buffer is owned by a document and the client doesn't need to
* do any initialization or cleanup.
* @param out_buf_size the size of the serialized document (i.e. out_buf) in bytes.
*
* @exception - if there is a problem during Save an Exception object will be thrown.
*/
- (NSData*)SaveFDFDocToBuf;
/**
* @return - A dictionary representing the Cos root of the document (document's trailer)
*/
- (Obj*)GetTrailer;
/**
* @return - A dictionary representing the Cos root of the document (/Root entry
* within the trailer dictionary)
*/
- (Obj*)GetRoot;
/**
* @return the FDF dictionary located in "/Root" or NULL if dictionary is not present.
*/
- (Obj*)GetFDF;
/**
* Get the PDF document file that this FDF file was exported from or is intended
* to be imported into.
*
* @return a String with the PDF document file name.
*/
- (NSString*)GetPDFFileName;
/**
* Set the PDF document file that this FDF file was exported from or is intended
* to be imported into.
*
* @param filepath - pathname to the file.
*/
- (void)SetPDFFileName: (NSString*)filepath;
/**
* Get the ID entry from "/Root/FDF" dictionary.
*
* @return - An object representing the ID entry in "/Root/FDF" dictionary.
*/
- (Obj*)GetID;
/**
* Set the ID entry in "/Root/FDF" dictionary.
*
* @param id - ID array object.
*/
- (void)SetID: (Obj*)id;
/**
* An interactive form (sometimes referred to as an AcroForm) is a
* collection of fields for gathering information interactively from
* the user. A FDF document may contain any number of fields appearing
* on any combination of pages, all of which make up a single, global
* interactive form spanning the entire document.
*
* The following methods are used to access and manipulate Interactive form
* fields (sometimes referred to as AcroForms).
*
* @return an iterator to the first Filed in the document.
* @note if the document has no AcroForms, HasNext()
* will return false.
*/
- (FDFFieldIterator*)GetFieldIterator;
/**
* field_name - a string representing the fully qualified name of
* the field (e.g. "employee.name.first").
*
* @return a FDFField associated with the given field_name or invalid
* field (null) if the field is not found.
*/
- (FDFFieldIterator*)GetFieldIteratorWithFieldName: (NSString*)field_name;
- (FDFField*)GetField: (NSString*)field_name;
/**
* Create a new interactive form FDFField.
* @return
* @exception
*/
- (FDFField*)FieldCreateWithObj: (NSString*)field_name type:  (FieldType)type field_value:  (Obj*)field_value;
- (FDFField*)FieldCreate: (NSString*)field_name type:  (FieldType)type;
- (FDFField*)FieldCreateWithString: (NSString*)field_name type:  (FieldType)type field_value:  (NSString*)field_value;
/**
* @return document's SDF/Cos document
*/
- (SDFDoc*)GetSDFDoc;
/**
* Convert FDF file to and from XFDF file
* @param filepath - string containing either the XFDF file name or the xml buffer containing the XFDF
* @return A new TRN_FDFDoc.
*/
+ (FDFDoc*)CreateFromXFDF: (NSString*)filepath;
/**
* Export FDF file as an XFDF file
* @param filepath - the filepath of the exported XFDF file
*/
- (void)SaveAsXFDF: (NSString*)filepath;
/**
* Merge the annotations from XFDF file into FDF file
*
* @param command_file - string containing the xml command file path or xml string of the command
* @param permitted_user - optional user name of the permitted user
*/
- (void)MergeAnnots: (NSString*)command_file permitted_user:  (NSString*)permitted_user;
- (id)init;




@end


/**
* A Caret annotation (PDF 1.5) is a visual symbol that indicates
* the presence of text edits.
*/
@interface Caret : Markup





/**
* Creates an Caret annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates an Caret annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Caret annotation in the specified document.
*
* @param doc A document to which the Caret annotation is added.
* @param pos A rectangle specifying the Caret annotation's bounds in default user space units.
*
* @return A newly created blank Caret annotation.
*/
+ (Caret*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
/**
* Creates a new Caret annotation, in the specified document, specifying
* a set of four numbers that shall describe the numerical differences
* between two rectangles: the Rect entry of the annotation and the actual
* boundaries of the underlying Caret.
*
* @param doc A document to which the Caret annotation is added.
* @param pos A rectangle specifying the Caret annotation's bounds in default user space units.
* @param diff A set of four numbers(represented as a Rect object)specifying the numerical differences
* between two rectangles: the Rect entry of the annotation and the actual
* boundaries of the underlying Caret.
* @return A newly created Caret annotation with rectangle difference specified.
*/
+ (Caret*)CreateWithPadding: (SDFDoc*)doc pos:  (PDFRect*)pos padding:  (PDFRect*)padding;
/**
* Returns the paragraph symbol associated with the caret.
*
* @return The name of the symbol. This can be either "P" (Use a new
* paragraph symbol ()) or "None" (Don't use any symbol).
* Default value: None.
*/
- (NSString *)GetSymbol;
/**
* Sets the caret symbol.
* @param symbol The name of the symbol. This can be either "P" (Use a new
* paragraph symbol ()) or "None" (Don't use any symbol).
* Default value: None.
*/
- (void)SetSymbol: (NSString *)symbol;

- (id)init;


@end


/**
* A Circle annotation is a type of markup annotation that displays an ellipse on
* the page. When opened, it can display a pop-up window containing the text of
* the associated note. The ellipse may be inscribed and possibly padded within the
* annotation rectangle defined by the annotation dictionary's Rect entry.
*/
@interface Circle : Markup





/**
* Creates an Circle annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a Circle annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Circle annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds in default user space units.
*
* @return A newly created blank Circle annotation.
*/
+ (Circle*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;

- (id)init;


@end


/**
* A HighlightAnnot annotation covers a word or a group of contiguous words with partially transparent
* color.
*/
@interface HighlightAnnot : TextMarkup





/**
* Creates a HighlightAnnot annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a HighlightAnnot annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new HighlightAnnot annotation in the specified document.
*
* @param doc A document to which the HighlightAnnot annotation is added.
* @param pos A rectangle specifying the HighlightAnnot annotation's bounds in default user space units.
*
* @return A newly created blank HighlightAnnot annotation.
*/
+ (HighlightAnnot*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;



@end


/**
* A line annotation (PDF 1.3) is used to display a single straight
* line on the page. When opened, it should display a pop-up window containing
* the text of the associated note.
*/
@interface LineAnnot : Markup





/**
* Creates a LineAnnot annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a LineAnnot annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new LineAnnot annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds in default user space units.
*
* @return A newly created blank LineAnnot annotation.
*/
+ (LineAnnot*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
/**
* Returns the coordinates of the start of a line.
*
* @return A point specifying the coordinates of the start of the line.
*/
- (PDFPoint*)GetStartPoint;
/**
* Sets the coordinates of the start of a line.
* @param sp  A point specifying the coordinates of the end of the line.
*
*/
- (void)SetStartPoint: (PDFPoint*)sp;
/**
* Returns the coordinates of the end of a line.
*
* @return A point specifying the coordinates of the end of the line.
*/
- (PDFPoint*)GetEndPoint;
/**
* Sets the coordinates of the end of a line.
* @param ep - A point specifying the coordinates of the end of the line.
*
*/
- (void)SetEndPoint: (PDFPoint*)ep;
/**
* Returns the ending style that applies to the first point of the line.
*
* @return A enum value from the "EndingStyle".
* @note Default value: e_None.
*/
- (EndingStyle)GetStartStyle;
/**
* Sets the ending style that applies to the first point of the line.
* (Optional; PDF1.4.)
*
* @param sst A enum value from the "EndingStyle".
* @note Default value: e_None.
*/
- (void)SetStartStyle: (EndingStyle)sst;
/**
* Returns the ending style  that applies to the second point of the line.
*
* @return A enum value from the "EndingStyle".
* @note Default value: e_None.
*/
- (EndingStyle)GetEndStyle;
/**
* Sets the ending style  that applies to the second point of the line.
* (Optional; PDF1.4)
*
* @param est A enum value from the "EndingStyle".
* @note Default value: e_None.
*/
- (void)SetEndStyle: (EndingStyle)est;
/**
* Returns the leader line length of a line.
*
* @return A number denoting the length of the leader line in default user space units.
* @note Usually if this entry is specified, the line is intended to be a dimension line (see
* "IT" entry of the annotation dictionary).
* @note Leader length is length of leader lines in default user space that extend from each endpoint
* of the line perpendicular to the line itself. A positive value shall mean that the leader lines
* appear in the direction that is clockwise when traversing the line from its starting point to
* its ending point (as specified by L); a negative value shall indicate the opposite direction.
* Default value: 0 (no leader lines)
*/
- (double)GetLeaderLineLength;
/**
* Sets the leader line length of a line.
* (PDF 1.6)
*
* @param A number denoting the length of the leader line in default user space units.
* @note Usually if this entry is specified, the line is intended to be a dimension line (see
* "IT" entry of the annotation dictionary).
* @note Leader length is length of leader lines in default user space that extend from each endpoint
* of the line perpendicular to the line itself. A positive value shall mean that the leader lines
* appear in the direction that is clockwise when traversing the line from its starting point to
* its ending point (as specified by L); a negative value shall indicate the opposite direction.
* Default value: 0 (no leader lines)
*/
- (void)SetLeaderLineLength: (double)ll;
/**
* Returns the leader line extension length of a line.
*
* @return A number denoting the length of the leader line extension in default user space units.
* @note The leader line extension length is a non-negative number that shall represents
* the length of leader line extensions that extend from the line proper 180 degrees from
* the leader lines.
* Default value: 0 (no leader line extensions)
*/
- (double)GetLeaderLineExtensionLength;
/**
* Sets the leader line extension length of a line.
* (PDF 1.6)
*
* @param A number denoting the length of the leader line extension in default user space units.
* @note The leader line extension length is a non-negative number that shall represents
* the length of leader line extensions that extend from the line proper 180 degrees from
* the leader lines.
* Default value: 0 (no leader line extensions)
*/
- (void)SetLeaderLineExtensionLength: (double)ll;
/**
* Returns true if caption is to be shown, otherwise false.
*
* @return A boolean value indicating whether the caption will be shown.
* @note If true, the text specified by the Contents or RCentries shall be replicated as a
* caption in the appearance of the line. The text shall be rendered in a manner
* appropriate to the content, taking into account factors such as writing direction.
* Default value: false.
*/
- (BOOL)GetShowCaption;
/**
* Sets the option of whether to show caption.
*
* @param showCaption A boolean value indicating whether the caption will be shown.
* @note If true, the text specified by the Contents or RC entries shall be replicated as a
* caption in the appearance of the line. The text shall be rendered in a manner
* appropriate to the content, taking into account factors such as writing direction.
* Default value: false.
*/
- (void)SetShowCaption: (BOOL)showCaption;
/**
* Returns the intent type of the line.
*
* @return An intent type value from the "IntentType" enum.
* @note Intent type describes the intent of the line annotation. Valid values shall be "e_LineArrow", which means
* that the annotation is intended to function as an arrow, and "e_LineDimension", which means that the annotation
* is intended to function as a dimension line.
*/
- (LineIntentType)GetIntentType;
/**
* Sets the intent type of the line.
* (For PDF 1.6)
*
* @param style An intent type value from the "IntentType" enum.
* @note Intent type describes the intent of the line annotation. Valid values shall be "e_LineArrow", which means
* that the annotation is intended to function as an arrow, and "e_LineDimension", which means that the annotation
* is intended to function as a dimension line.
*/
- (void)SetIntentType: (LineIntentType)style;
/**
* Returns the leader line offset length of a line.
*
* @return A number denoting the length of the leader line offset in default user space units.
* @note Leader line offset number is a non-negative number that shall represent the length of the leader
* line offset, which is the amount of empty space between the endpoints of the
* annotation and the beginning of the leader lines.
*/
- (double)GetLeaderLineOffset;
/**
* Sets the leader line offset length of a line.
* (PDF 1.7)
*
* @param ll A number denoting the length of the leader line offset in default user space units.
* @note Leader line offset number is a non-negative number that shall represent the length of the leader
* line offset, which is the amount of empty space between the endpoints of the
* annotation and the beginning of the leader lines.
*/
- (void)SetLeaderLineOffset: (double)ll;
/**
* Returns the caption position of a line.
*
* @return A cap position value from the "CapPos" enum.
* @note Caption position describes the annotations caption positioning.
* Default value: Inline
* @see CapPos
*/
- (CapPos)GetCaptionPosition;
/**
* Sets the caption position of a line.
* (Optional, PDF 1.7)
*
* @param style A caption position value from the "CapPos" enum.
* @note Caption position describes the annotations caption positioning.
* Default value: Inline
* @see CapPos
*/
- (void)SetCaptionPosition: (CapPos)style;
/**
* Returns the horizontal offset of the caption.
*
* @return A number denoting the horizontal offset of the caption in default user space units.

* @note The horizontal offset specifies the offset of the caption text from the line's midpoint,
* with a positive value indicating offset to the right and a negative value indicating offset to the left.
* Default value: 0 (no offset from normal horizontal positioning).
*/
- (double)GetTextHOffset;
/**
* Sets the horizontal offset of the caption.
* (For PDF 1.7 )
*
* @param offset A number denoting the horizontal offset of the caption in default user space units.
* @note The horizontal offset specifies the offset of the caption text from the line's midpoint,
* with a positive value indicating offset to the right and a negative value indicating offset to the left.
* Default value: 0 (no offset from normal horizontal positioning).
*/
- (void)SetTextHOffset: (double)offset;
/**
* Returns the vertical offset of the caption.
*
* @return A number denoting the vertical offset of the caption in default user space units.
* @note The vertical offset specifies the offset of the caption text perpendicular to the annotation line,
* with a positive value indicating a shift up and a negative value indicating a shift down.
* Default value: 0 (no offset from normal vertical positioning).
*/
- (double)GetTextVOffset;
/**
* Sets the vertical offset of the caption.
* (For PDF 1.7 )
*
* @param offset A number denoting the vertical offset of the caption in default user space units.
* @note The vertical offset specifies the offset of the caption text perpendicular to the annotation line,
* with a positive value indicating a shift up and a negative value indicating a shift down.
* Default value: 0 (no offset from normal vertical positioning).
*/
- (void)SetTextVOffset: (double)offset;

- (id)init;


@end


/**
* A FreeText annotation (PDF 1.3) displays text directly on the page.
* Unlike an ordinary Text annotation, a FreeText annotation has no
* open or closed state; The content of the FreeText annotation is always
* visible instead of being displayed in a popup window.
*/
@interface FreeText : Markup





/**
* Creates a FreeText annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a FreeText annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new FreeText annotation in the specified document.
*
* @param doc A document to which the FreeText annotation is added.
* @param pos A rectangle specifying the FreeText annotation's bounds in default user space units.
*
* @return A newly created blank FreeText annotation.
*/
+ (FreeText*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
/**
* Returns the default appearance of the FreeText annotation.
*
* @return A string representing the default appearance of the annotation.
* @note The default appearance string is used to format the text.
* The annotation dictionarys Appearance entry, if present,
* will take precedence over this entry.
* @note this method corresponds to the 'DA' entry in the annotation dictionary.
*/
- (NSString*)GetDefaultAppearance;
/**
* Sets the default appearance of the FreeText annotation.
*
* @param app_str A string representing the default appearance of the annotation.
* @note The default appearance string is used to format the text.
* The annotation dictionarys Appearance entry, if present,
* will take precedence over this entry.
* @note this method corresponds to the 'DA' entry in the annotation dictionary.
*/
- (void)SetDefaultAppearance: (NSString *)app_str;
/**
* Returns the quading format of the FreeText annotation.
* (PDF 1.4)
*
* @return A int (code) indicating the quading format of the FreeText annotation.
* @note The following are the quading formats corresponding to each int code.
* 0 Left-justified
* 1 Centered
* 2 Right-justified
*/
- (int)GetQuaddingFormat;
/**
* Sets the quading format of the FreeText annotation.
* (Optional; PDF1.4)
*
* @param app_qform A int code indicating the quading format of the FreeText annotation.
* Default value: 0 (left-justified).
* @note The int code specifies the form of quadding (justification)
* that shall be used in displaying the annotations text:
* 0 Left-justified
* 1 Centered
* 2 Right-justified
*/
- (void)SetQuaddingFormat: (int)app_qform;
/**
* Returns the callout line points of the FreeText annotation.
* (PDF 1.6)
*
* @param p1 The starting point.
* @param p2 The ending point.
* @param p3 The knee point.
* @return Three point objects if the line is bent or two point objects if
* the line is straight.
* @note If the line is straight, i.e. only has two points,
* two points will be returned in p1 and p2, and p3 will be the same as p2.
* The coordinates are given in default user space.
*/
- (PDFPoint*)GetCalloutLinePoint1;
- (PDFPoint*)GetCalloutLinePoint2;
- (PDFPoint*)GetCalloutLinePoint3;
/**
* Sets the callout line points of the FreeText annotation.
* (Optional; meaningful only if IT is FreeTextCallout; PDF 1.6)
*
* @param p1 The starting point.
* @param p2 The ending point.
* @param p3 The knee point.
* @note The coordinates are defined in default user space.
*/
- (void)SetCalloutLinePointsWithKneePoint: (PDFPoint*)p1 p2:  (PDFPoint*)p2 p3:  (PDFPoint*)p3;
/**
* Sets the callout line points of the FreeText annotation.
* (Optional; meaningful only if IT is FreeTextCallout; PDF 1.6)
*
* @param p1 The staring point.
* @param p2 The ending point.
* @note The coordinates are defined in default user space.
*/
- (void)SetCalloutLinePoints: (PDFPoint*)p1 p2:  (PDFPoint*)p2;
/**
* Returns Intent name of the FreeText annotation.
* (PDF 1.4)
*
* @returns The intent name of the annotation as
* an entry from the enum "IntentName".
*/
- (IntentName)GetIntentName;
/**
* Sets the Intent name of the FreeText annotation.
* (Optional; PDF1.4)
*
* @param mode The intent name of the annotation as
* an entry from the enum "IntentName".
*/
- (void)SetIntentName: (IntentName)mode;
/**
* Returns the ending style of the callout line of the FreeText Annotation.
*
* @return The ending style represented as one of the entries of the enum "EndingStyle"
* @note The ending style specifies the line ending style that
* shall be used in drawing the callout line specified in CallOut LineAnnot Points
* (CL). The enum entry shall specify the line ending style for the endpoint
* defined by the starting point(p1) of the CallOut LineAnnot Points.
* Default value: e_None.
*/
- (EndingStyle)GetEndingStyle;
/**
* Sets the ending style of the callout line of the FreeText Annotation.
* (Optional; meaningful only if CL is present; PDF 1.6)
*
* @param est The ending style represented using one of the
* entries of the enum "EndingStyle"
* @note The ending style specifies the line ending style that
* shall be used in drawing the callout line specified in CallOut LineAnnot Points
* (CL). The enum entry shall specify the line ending style for the endpoint
* defined by the starting point(p1) of the CallOut LineAnnot Points.
* Default value: e_None.
*/
- (void)SetEndingStyle: (EndingStyle)est;
/**
* Sets the ending style of the callout line of the FreeText Annotation.
* (Optional; meaningful only if CL is present; PDF 1.6)
*
* @param est The ending style represented using a string.
* @note The ending style specifies the line ending style that
* shall be used in drawing the callout line specified in CallOut LineAnnot Points
* (CL). The enum entry shall specify the line ending style for the endpoint
* defined by the starting point(p1) of the CallOut LineAnnot Points.
* Default value: "None".
*/
- (void)SetEndingStyleWithString: (NSString *)est;
/**
* Sets the text color of the FreeText Annotation.
*
* @param color ColorPt object representing the color.
* @param col_comp number of colorant components in ColorPt object.
*
* @note Current implementation of this method creates a non-standard
* entry in the annotation dictionary and uses it to generate the appearance
* stream. Make sure you call RefreshAppearance() after changing text or
* line color, and remember that editing the annotation in other PDF
* applications will produce different appearance.
*/
- (void)SetTextColor: (ColorPt*)color col_comp:  (int)col_comp;
/**
* Returns the text color of the FreeText Annotation.
*
* @param color reference to ColorPt object, where results will be saved.
* @param col_comp reference to an integer,
* where number of colorant components will be written.
*
* @note Current implementation of this method uses a non-standard
* entry in the annotation dictionary and will not return meaningful
* results when called on annotations not created with PDFTron software.
*/
- (ColorPt*)GetTextColor;
- (int)GetTextColorCompNum;
/**
* Sets the line and border color of the FreeText Annotation.
*
* @param color ColorPt object representing the color.
* @param col_comp number of colorant components in ColorPt object.
*
* @note Current implementation of this method creates a non-standard
* entry in the annotation dictionary and uses it to generate the appearance
* stream. Make sure you call RefreshAppearance() after changing text or
* line color, and remember that editing the annotation in other PDF
* applications will produce different appearance.
*/
- (void)SetLineColor: (ColorPt*)color col_comp:  (int)col_comp;
/**
* Returns the line and border color of the FreeText Annotation.
*
* @param color reference to ColorPt object, where results will be saved.
* @param col_comp reference to an integer,
* where number of colorant components will be written.
*
* @note Current implementation of this method uses a non-standard
* entry in the annotation dictionary and will not return meaningful
* results when called on annotations not created with PDFTron software.
*/
- (ColorPt*)GetLineColor;
- (int)GetLineColorCompNum;
- (void)SetFontSize: (double)font_size;
- (double)GetFontSize;

- (id)init;


@end


/**
* A link annotation represents either a hypertext link to a destination elsewhere in the document
* or an action to be performed.
*/
@interface Link : Annot





/**
* Creates a Link annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a Link annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Link annotation in the specified document.
*
* @param doc A document to which the Link annotation is added.
* @param pos A rectangle specifying the Link annotation's bounds in default user space units.
*
* @return A newly created blank Link annotation.
*/
+ (Link*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
/**
* Creates a new Link annotation.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds in default user space units.
* @param action Action for the link annotation.
*
* @return A new Link annotation.
*/
+ (Link*)CreateWithAction: (SDFDoc*)doc pos:  (PDFRect*)pos action:  (Action*)action;
/**
* Removes this annotation's action.
*/
- (void)RemoveAction;
/**
* Returns the Action of the Link Annotation.
*
* @return An Action object of the Link annotation.
* @note The return value is an action that shall be performed when the
* link annotation is activated
*/
- (Action*)GetAction;
/**
* Sets the Action of the Link Annotation.
* (Optional; PDF1.1 )
*
* @param action An Action object that shall be associated with this Link annotation.
* @note The parameter is an action that shall be performed when the
* link annotation is activated.
*/
- (void)SetAction: (Action*)action;
/**
* Returns the highlighting mode of this Link annotation.
*
* @return the highLighting mode as a value of the enum "HighlightingMode".
* @note The annotations highlighting mode is the visual effect that shall be used when
* the mouse button is pressed or held down inside its active area.
*/
- (LinkHighlightingMode)GetHighlightingMode;
/**
* Sets the highlighting mode for this Link annotation.
* (Optional; PDF1.2 )
*
* @param mode the mode as a value of the enum "HighlightingMode".
* @note The annotations highlighting mode is the visual effect that shall be used when
* the mouse button is pressed or held down inside its active area.
*/
- (void)SetHighlightingMode: (LinkHighlightingMode)mode;
/**
* Returns the number of QuadPoints in the 'QuadPoints' array of the Link annotation.
*
* @return The number of QuadPoints.
* @note An array of n QuadPoints specifying the coordinates of n quadrilaterals
* in default user space that comprise the region in which the link should be active.
* The coordinates specifying the four vertices of the quadrilateral are in counterclockwise order.
* For orientation purposes, the bottom of a quadrilateral is the line formed by p1 and p2 of the QuadPoint.
* QuadPoints shall be ignored if any coordinate in the array lies outside the region specified by Rect.
*/
- (int)GetQuadPointCount;
/**
* Returns the QuadPoint located at a certain index of the QuadPoint array of the Link
* annotation.
*
* @param idx The index of the QuadPoint, starts at zero and should be less than the return value of GetQuadPointCount().
* @return The QuadPoint located at a certain index of the QuadPoint array of the Link annotation.
* @note An array of n QuadPoints specifying the coordinates of n quadrilaterals
* in default user space that comprise the region in which the link should be active.
* The coordinates specifying the four vertices of the quadrilateral are in counterclockwise order.
* For orientation purposes, the bottom of a quadrilateral is the line formed by p1 and p2 of the QuadPoint.
* QuadPoints shall be ignored if any coordinate in the array lies outside the region specified by Rect.
*/
- (QuadPoint*)GetQuadPoint: (int)idx;
/**
* Set the QuadPoint to be located at a certain index of the QuadPoint array of the Link annotation.
* (Optional; PDF1.6 )
*
* @param idx The index of the QuadPoint, starts at zero and should be less than the return value of GetQuadPointCount().
* @param qp  The QuadPoint to be stored in the annotation.
* @note An array of n QuadPoints specifying the coordinates of n quadrilaterals
* in default user space that comprise the region in which the link should be active.
* The coordinates specifying the four vertices of the quadrilateral are in counterclockwise order.
* For orientation purposes, the bottom of a quadrilateral is the line formed by p1 and p2 of the QuadPoint.
* QuadPoints shall be ignored if any coordinate in the array lies outside the region specified by Rect.
*/
- (void)SetQuadPoint: (int)idx qp:  (QuadPoint*)qp;

- (id)init;


@end


/**
* A movie annotation contains animated graphics and sound to be
* presented on the computer screen and through the speakers. When the
* annotation is activated, the movie is played.
*/
@interface Movie : Annot





/**
* Creates a Movie annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a Movie annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Movie annotation in the specified document.
*
* @param doc A document to which the Movie annotation is added.
* @param pos A rectangle specifying the Movie annotation's bounds in default user space units.
*
* @return A newly created blank Movie annotation.
*/
+ (Movie*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
/**
* Returns the title of the Movie Annotation.
*
* @return A string representing the title of the Movie Annotation.
* @note Movie actions may use this title to reference the movie annotation.
*/
- (NSString*)GetTitle;
/**
* Sets the title of the Movie Annotation.
*(Optional)
*
* @param title A string representing the title of the Movie Annotation.
* @note Movie actions may use this title to reference the movie annotation.
*/
- (void)SetTitle: (NSString*)title;
/**
* Returns the option of whether the Movie is to be played.
*
* @return a boolean value indicating if the movie is to be played.
* @note IsToBePlayed is a flag specifying whether to play the movie when the annotation is activated.
* The movie shall be played using default activation parameters. If the value is false,
* the movie shall not be played.
* Default value: true.
*/
- (BOOL)IsToBePlayed;
/**
* Sets the option of whether the Movie is to be played.
*(Optional)
*
* @param isplay A boolean value telling if the movie is to be played.
* Default value: true.
* @note IsToBePlayed is a flag specifying whether to play the movie when the annotation is activated.
* The movie shall be played using default activation parameters. If the value is false,
* the movie shall not be played.
* Default value: true.
*/
- (void)SetToBePlayed: (BOOL)isplay;

- (id)init;


@end


/**
* This header defines classes for the Polygon and PolyLine annotations.
* Polygon annotations (PDF 1.5) display closed polygons on the page.
* Such polygons may have any number of vertices connected by straight lines.
* Polyline annotations (PDF 1.5) are similar to polygons, except that the
* first and last vertex are not implicitly connected.
*/
@interface PolyLine : LineAnnot





/**
* Creates a PolyLine annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a PolyLine annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new PolyLine annotation in the specified document.
*
* @param doc A document to which the PolyLine annotation is added.
* @param pos A rectangle specifying the PolyLine annotation's bounds in default user space units.
*
* @return A newly created blank PolyLine annotation.
*/
+ (PolyLine*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
/**
* Returns the number of vertices in the Vertices array.
*
* @return the number of vertices.
* @note The Vertices are the points between which the lines are drawn.
* The viewer can draw either the straight lines or the smoothly connecting ones.
*/
- (int)GetVertexCount;
/**
* Returns the vertex(as a Point object) corresponding to the index
* within the Vertices array.
*
* @param idx The index of the vertex, should be less than the value returned by GetVertexCount().
* @return A Point object corresponding to the vertex in the specified index position.
* @note The Vertices are the points between which the lines are drawn.
* The viewer can draw either the straight lines or the smoothly connecting ones.
*/
- (PDFPoint*)GetVertex: (int)idx;
/**
* Sets the vertex(in Point object form) corresponding to the index
* within the Vertices array.
*
* @param idx The index of the vertex.
* @param pt A Point object corresponding to the vertex to be added to the array.
* @note The Vertices are the points between which the lines are drawn.
* The viewer can draw either the straight lines or the smoothly connecting ones.
*/
- (void)SetVertex: (int)idx pt:  (PDFPoint*)pt;
/**
* Returns the intent name as a value of the "IntentName" enumeration type.
*
* @returns The intent type of the annotation.
* @see IntentType
*/
- (PolyLineIntentType)GetIntentName;
/**
* Sets the Intent name as a value of the "IntentName" enumeration type.
* (Optional; PDF1.6 )
*
* @param mode The intent name of the annotation.
* @see IntentType
*/
- (void)SetIntentName: (PolyLineIntentType)mode;

- (id)init;


@end


@interface PDFPolygon : PolyLine




+ (PDFPolygon*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (id)initWithD: (Obj*)d;
- (id)init;
- (id)initWithAnn: (Annot*)ann;
@end


/**
* A redaction annotation (PDF 1.7) identifies content that is intended to
* be removed from the document. The intent of redaction annotations is to
* enable the following:
* a)Content identification. A user applies redact annotations that specify
* the pieces or regions of content that should be removed. Up until the
* next step is performed, the user can see, move and redefine these
* annotations.
* b)Content removal. The user instructs the viewer application to apply
* the redact annotations, after which the content in the area specified
* by the redact annotations is removed. In the removed contents place,
* some marking appears to indicate the area has been redacted. Also, the
* redact annotations are removed from the PDF document.
* RedactionAnnot annotations provide a mechanism for the first step in the
* redaction process (content identification). This allows content to be
* marked for redaction in a non-destructive way, thus enabling a review
* process for evaluating potential redactions prior to removing the
* specified content.
* RedactionAnnot annotations shall provide enough information to be used
* in the second phase of the redaction process (content removal).
* This phase is application-specific and requires the conforming reader
* to remove all content identified by the redaction annotation, as well
* as the annotation itself.
* Conforming readers that support redaction annotations shall provide
* a mechanism for applying content removal, and they shall remove all
* traces of the specified content. If a portion of an image is contained
* in a redaction region, that portion of the image data shall be destroyed;
* clipping or image masks shall not be used to hide that data.
* Such conforming readers shall also be diligent in their consideration
* of all content that can exist in a PDF document, including XML Forms
* Architecture (XFA) content and Extensible Metadata Platform (XMP)
* content.
*/
@interface RedactionAnnot : Markup





/**
* Creates a RedactionAnnot annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates an RedactionAnnot annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new RedactionAnnot annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds, in user space coordinates.
*
* @return A newly created blank Circle annotation.
*/
+ (RedactionAnnot*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
/**
* Returns the number of QuadPoints in the QuadPoints array of the RedactionAnnot annotation.
*
* @return The number of QuadPoints.
* @note An array of n QuadPoints that denote
* the content region that is intended to be removed. If quad points are not present,
* the Rect entry denotes the content region that is intended to be removed.
*/
- (int)GetQuadPointCount;
/**
* Returns the QuadPoint located at a certain index of the QuadPoint array of the RedactionAnnot
* annotation.
*
* @param idx The index of the QuadPoint, starts at zero and must be less than return value of GetQuadPointCount().
* @return The QuadPoint located at a certain index of the QuadPoint array of the RedactionAnnot annotation.
* @note An array of n QuadPoints that denote
* the content region that is intended to be removed. If quad points are not present,
* the Rect entry denotes the content region that is intended to be removed.
*/
- (QuadPoint*)GetQuadPoint: (int)idx;
/**
* Set the QuadPoint to be located at a certain index of the QuadPoint array of the RedactionAnnot
* annotation.
* (Optional; PDF1.6 )
*
* @param idx The index position where the QuadPoint of interest is to be inserted, starting at 0.
* @param qp  The QuadPoint to be inserted at that position.
* @note  For orientation purposes, the bottom of a quadrilateral is the line formed by p1 and p2 of the QuadPoint.
* QuadPoints shall be ignored if any coordinate in the array lies outside the region specified by Rect.
*/
- (void)SetQuadPoint: (int)idx qp:  (QuadPoint*)qp;
/**
* Returns Overlay appearance of the RedactionAnnot annotation.
*
* @return An SDF object that represents the overlay appearance of the RedactionAnnot annotation.
* @note This object is a form XObject specifying the overlay appearance for this
* redaction annotation. After this redaction is applied and the affected content has been removed,
* the overlay appearance should be drawn such that its origin lines up with the lower-left corner
* of the annotation rectangle. This form XObject is not necessarily related to other annotation
* appearances, and may or may not be present in the Appearance dictionary. This entry takes precedence over the Interior Color(IC),
* OverlayText, OverlayTextAppearance(DA), and QuadPoint(Q) entries.
*/
- (Obj*)GetAppFormXO;
/**
* Sets Overlay appearance of the RedactionAnnot annotation.
* (Optional)
*
* @param formxo An SDF object that represents the overlay appearance of the RedactionAnnot annotation.
* @note This object is a form XObject specifying the overlay appearance for this
* redaction annotation. After this redaction is applied and the affected content has been removed,
* the overlay appearance should be drawn such that its origin lines up with the lower-left corner
* of the annotation rectangle. This form XObject is not necessarily related to other annotation
* appearances, and may or may not be present in the Appearance dictionary. This entry takes precedence over the Interior Color(IC),
* OverlayText, OverlayTextAppearance(DA), and QuadPoint(Q) entries.
*/
- (void)SetAppFormXO: (Obj*)formxo;
/**
* Returns Overlay text of the RedactionAnnot annotation.
*
* @return A string containing the overlay text of the annotation.
* @note The OverlayText string is a text string specifying the
* overlay text that should be drawn over the redacted region
* after the affected content has been removed.
* This entry is ignored if the Overlay appearance(RO) entry is present.
*/
- (NSString*)GetOverlayText;
/**
* Sets Overlay text of the RedactionAnnot annotation.
*
* @param title A string containing the overlay text of the annotation.
* @note The OverlayText string is a text string specifying the
* overlay text that should be drawn over the redacted region
* after the affected content has been removed.
* This entry is ignored if the Overlay appearance stream (RO) entry is present.
*/
- (void)SetOverlayText: (NSString*)title;
/**
* Returns the option of whether to use repeat for the RedactionAnnot annotation.
*
* @return A bool indicating whether to repeat for the RedactionAnnot annotation.
* @note If UseRepeat value is true, then the text specified by OverlayText
* should be repeated to fill the redacted region after the affected content
* has been removed. This entry is ignored if the Overlay appearance stream
* (RO) entry is present.
* Default value: false.
*/
- (BOOL)GetUseRepeat;
/**
* Sets the option of whether to use repeat for the RedactionAnnot annotation.
*
* @param app A bool indicating whether to repeat for the RedactionAnnot annotation.
* @note If UseRepeat value is true, then the text specified by OverlayText
* should be repeated to fill the redacted region after the affected content
* has been removed. This entry is ignored if the Overlay appearance stream
* (RO) entry is present.
* Default value: false.
*/
- (void)SetUseRepeat: (BOOL)repeat;
/**
* Returns Overlay text appearance of the RedactionAnnot annotation.
*
* @return A string containing the overlay text appearance of the annotation.
* @note The overlay text appearance is the appearance string to be used
* in formatting the overlay text when it is drawn after the affected content
* has been removed. This entry is ignored if the Overlay appearance stream
* (RO) entry is present.
*/
- (NSString*)GetOverlayTextAppearance;
/**
* Sets Overlay text appearance of the RedactionAnnot annotation.
*
* @param app A string containing the overlay text appearance of the annotation.
* @note The overlay text appearance is the appearance string to be used
* in formatting the overlay text when it is drawn after the affected content
* has been removed. This entry is ignored if the Overlay appearance stream
* (RO) entry is present.
*/
- (void)SetOverlayTextAppearance: (NSString*)app;
/**
* Returns Overlay text quadding(justification) format of the RedactionAnnot annotation.
*
* @return A value of the "QuadForm" enum type, indicating the
* overlay text quadding(justification) format of the RedactionAnnot annotation's overlay text.
*/
- (QuadForm)GetQuadForm;
/**
* Sets Overlay text quadding (justification) format of the RedactionAnnot annotation.
*
* @param form A value of the "QuadForm" enum type, indicating the
* overlay text quadding(justification) format of the RedactionAnnot annotation.
* @note Quadding format specifies the form of justification to be
* used in displaying the overlay text.
*/
- (void)SetQuadForm: (QuadForm)form;

- (id)init;


@end


/**
* A RubberStamp annotation displays text or graphics intended
* to look as if they were stamped on the page with a rubber stamp.
*/
@interface RubberStamp : Markup





/**
* Creates a RubberStamp annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a RubberStamp annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new RubberStamp annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds in default user space units.
*
* @return A newly created blank RubberStamp annotation.
*/
+ (RubberStamp*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos icon:  (RubberStampIcon)icon;
/**
* Returns the type of the icon associated with the RubberStamp annotation.
*
* @return A value of enum "Icon" that represents
* the type of icon associated with the annotation.
* Default value: e_Draft.
*/
- (RubberStampIcon)GetIcon;
- (void)SetRubberStampIconType: (RubberStampIcon)type;
/**
* Sets the type of the icon associated with the RubberStamp annotation.
*
* @param type A value of enum "Icon" type that represents
* the type of icon associated with the annotation.
* Default value: e_Draft.
*/
- (void)SetIcon;
/**
* Returns the name of the icon associated with the RubberStamp annotation.
*
* @return A string that is the name of the icon associated with
* the RubberStamp annotation.
* @note The following icon names are equivalent
* to predefined icon types from the enum "Icon":
* "Approved" = e_Approved
* "Experimental" = e_Experimental
* "NotApproved" = e_NotApproved
* "AsIs" = e_AsIs
* "Expired" = e_Expired
* "NotForPublicRelease" = e_NotForPublicRelease
* "Confidential" = e_Confidential
* "Final" = e_Final
* "Sold" = e_Sold
* "Departmental" = e_Departmental
* "Format" = e_ForComment
* "TopSecret" = e_TopSecret
* "ForPublicRelease" = e_ForPublicRelease
* "Draft" = e_Draft
* "Unknown" = e_Unknown
* Names other than mentioned above do not have predefined icon appearances.
*/
- (NSString *)GetIconName;
/**
* Sets the name of the icon associated with the RubberStamp annotation.
*
* @param iconstring the name of the icon associated with
* the RubberStamp annotation.
* @note The following icon names are equivalent
* to predefined icon types from the enum "Icon":
* "Approved" = e_Approved
* "Experimental" = e_Experimental
* "NotApproved" = e_NotApproved
* "AsIs" = e_AsIs
* "Expired" = e_Expired
* "NotForPublicRelease" = e_NotForPublicRelease
* "Confidential" = e_Confidential
* "Final" = e_Final
* "Sold" = e_Sold
* "Departmental" = e_Departmental
* "Format" = e_ForComment
* "TopSecret" = e_TopSecret
* "ForPublicRelease" = e_ForPublicRelease
* "Draft" = e_Draft
* "Unknown" = e_Unknown
* Names other than mentioned above do not have predefined icon appearances.
*/
- (void)SetRubberStampIconName: (NSString *)icon;

- (id)init;


@end


/**
* A screen annotation (PDF 1.5) specifies a region of a page upon which
* media clips may be played. It also serves as an object from which
* actions can be triggered.
*/
@interface Screen : Annot





/**
* Creates a Screen annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a Screen annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Screen annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds in default user space units.
*
* @return A newly created blank Screen annotation.
*/
+ (Screen*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
/**
* Returns the title of the annotation.
*
* @return A string representing the title of the annotation.
*/
- (NSString*)GetTitle;
/**
* Sets the title of the Annotation.
*(Optional)
*
* @param title A string representing the title of the annotation.
*/
- (void)SetTitle: (NSString*)title;
/**
* Returns the action of the Screen annotation
*
* @return An action object representing the action of the annotation.
* @note The action is an action that shall be performed when the annotation is activated.
*/
- (Action*)GetAction;
/**

* Sets the action of the Screen annotation
* (Optional; PDF1.1 )
*
* @param action An action object representing the action of the annotation.
* @note The action is an action that shall be performed when the annotation is activated.
*/
- (void)SetAction: (Action*)action;
/**
* Returns the additional actions of the annotation.
*
* @return An SDF object representing the additional actions dictionary of the annotation.
* @note An additional-actions dictionary defines the screen annotations behaviour
* in response to various trigger events. This corresponds to 'AA' entry of the
* annotation dictionary.
*/
- (Obj*)GetTriggerAction;
/**
* Assigns additional actions to the annotation
* (Optional; PDF1.1 )
*
* @param action An SDF dictionary object representing the actions of the annotation.
* @note An additional-actions dictionary defines the screen annotations behaviour
* in response to various trigger events. This corresponds to 'AA' entry of the
* annotation dictionary.
*/
- (void)SetTriggerAction: (Obj*)action;
/**
* Returns the rotation value of the  annotation.
*
* @return An integer representing the rotation value of the  annotation.
* @note The Rotation specifies the number of degrees by which the
* annotation shall be rotated counterclockwise relative to the page.
* The value shall be a multiple of 90.
* Default value: 0.
*/
- (int)GetRotation;
/**
* Sets the rotation value of the  annotation.
* (Optional)
*
* @param rot An integer representing the rotation value of the  annotation.
* @note the Rotation specifies the number of degrees by which the
* annotation shall be rotated counterclockwise relative to the page.
* The value shall be a multiple of 90.
* Default value: 0.
*/
- (void)SetRotation: (int)rot;
/**
* Returns the number indicating border color space of the annotation.
*
* @return An integer indicating a color space value from the ColorSpace::Type enum.
* That is, 1 corresponding to "e_device_gray",
* 3 corresponding to "e_device_rgb", and 4 corresponding to "e_device_cmyk".
* 0 means this annotation had no color assigned.
*/
- (int)GetBorderColorCompNum;
/**
* Returns the border color of the annotation.
*
* @return A color object that denotes the color of the Screen border.
* @note The color can be in different color spaces: Gray, RGB, or CMYK.
* Call "GetBorderColorCompNum" to access the color space information corresponding to the border color.
*/
- (ColorPt*)GetBorderColor;
/**
* Sets the border color of the annotation.
* (Optional)
*
* @param c A color object that denotes the color of the screen border.
* @param CompNum An integer which value indicates the color space used for the parameter c.
*/
- (void)SetBorderColor: (ColorPt*)c CompNum:  (int)CompNum;
/**
* Returns the number indicating background color space of the annotation.
*
* @return An integer indicating a color space value from the ColorSpace::Type enum.
* That is, 1 corresponding to "e_device_gray",
* 3 corresponding to "e_device_rgb", and 4 corresponding to "e_device_cmyk" if color space is applicable,
* 0 means no background color was assigned.
*/
- (int)GetBackgroundColorCompNum;
/**
* Returns the background color of the annotation.
*
* @return A color object that denotes the color of the Screen background.
* @note The color can be in different color spaces: Gray, RGB, or CMYK.
* Call "GetBackgroundColorCompNum" to access the color space information corresponding to the border color.
*/
- (ColorPt*)GetBackgroundColor;
/**
* Sets the background color of the annotation.
*(Optional)
*
* @param c A color point that denotes the color of the screen background.
* @param CompNum An integer which value indicates the color space used for the parameter c.
*/
- (void)SetBackgroundColor: (ColorPt*)c CompNum:  (int)CompNum;
/**
* Returns static caption text of the annotation.
*
* @return A string containing the static caption text of the annotation.
* @note The static caption is the annotations normal caption, which
* shall be displayed when it is not interacting with the user.
*/
- (NSString*)GetStaticCaptionText;
/**
* Sets static caption text of the annotation.
* (Optional; button fields only)
*
* @param ct A string containing the static caption text of the annotation.
* @note The static caption is the annotations normal caption, which
* shall be displayed when it is not interacting with the user.
*/
- (void)SetStaticCaptionText: (NSString*)ct;
/**
* Returns the rollover caption text of the annotation.
*
* @return A string containing the rollover caption text of the annotation.
* @note The rollover caption shall be displayed when the user rolls the cursor
* into its active area without pressing the mouse button.
*/
- (NSString*)GetRolloverCaptionText;
/**
* Sets the roll over caption text of the annotation.
* (Optional; button fields only)
*
* @param ct A string containing the roll over caption text of the annotation.
* @note The rollover caption shall be displayed when the user rolls the cursor
* into its active area without pressing the mouse button.
*/
- (void)SetRolloverCaptionText: (NSString*)ct;
/**
* Returns the button down caption text of the annotation.
*
* @return A string containing the button down text of the annotation.
* @note The button down caption shall be displayed when the mouse button is
* pressed within its active area.
*/
- (NSString*)GetMouseDownCaptionText;
/**
* Sets the button down caption text of the annotation.
* (Optional; button fields only)
*
* @param ct A string containing the button down text of the annotation.
* @note The button down caption shall be displayed when the mouse button is
* pressed within its active area.
*/
- (void)SetMouseDownCaptionText: (NSString*)ct;
/**
* Returns the static icon associated with the annotation.
*
* @return An SDF object that represents the static icon
* associated with the annotation.
* @note The static icon object is a form XObject defining the
* annotations normal icon, which shall be
* displayed when it is not interacting with the user.
*/
- (Obj*)GetStaticIcon;
/**
* Sets the static icon associated with the annotation.
* (Optional; button fields only)
*
* @param ic An SDF object that represents the static icon
* associated with the annotation.
* @note The static icon object is a form XObject defining the
* annotations normal icon, which shall be
* displayed when it is not interacting with the user.
*/
- (void)SetStaticIcon: (Obj*)ic;
/**
* Returns the rollover icon associated with the annotation.
*
* @return An SDF object that represents the rollover icon
* associated with the annotation.
* @note The rollover icon object is a form XObject defining the
* annotations rollover icon, which shall be displayed
* when the user rolls the cursor into its active area without
* pressing the mouse button.
*/
- (Obj*)GetRolloverIcon;
/**
* Sets the rollover icon associated with the annotation.
* (Optional; button fields only)
*
* @param ic An SDF object that represents the rollover icon
* associated with the annotation.
* @note The rollover icon object is a form XObject defining the
* annotations rollover icon, which shall be displayed
* when the user rolls the cursor into its active area without
* pressing the mouse button.
*/
- (void)SetRolloverIcon: (Obj*)ic;
/**
* Returns the Mouse Down icon associated with the annotation.
*
* @return An SDF object that represents the Mouse Down icon
* associated with the annotation.
* @note The Mouse Down icon object is a form XObject defining the
* annotations alternate (down) icon, which shall be displayed
* when the mouse button is pressed within its active area.
*/
- (Obj*)GetMouseDownIcon;
/**
* Sets the Mouse Down icon associated with the annotation.
* (Optional; button fields only)
*
* @param ic An SDF object that represents the Mouse Down icon
* associated with the annotation.
* @note The Mouse Down icon object is a form XObject defining the
* annotations alternate (down) icon, which shall be displayed
* when the mouse button is pressed within its active area.
*/
- (void)SetMouseDownIcon: (Obj*)ic;
/**
* Returns the Icon and caption relationship of the  annotation.
*
* @return A value of the "IconCaptionRelation" enum type.
* Default value: e_NoIcon.
* @see IconCaptionRelation
*/
- (ScreenIconCaptionRelation)GetIconCaptionRelation;
/**
* Sets the Icon and caption relationship of the  annotation.
* (Optional; pushbutton fields only)
*
* @param icr A value of the "IconCaptionRelation" enum type.
* Default value: e_NoIcon.
* @see IconCaptionRelation
*/
- (void)SetIconCaptionRelation: (ScreenIconCaptionRelation)icr;
/**
* Returns the condition under which the icon should be scaled.
*
* @return A value of the "ScaleCondition" enum type.
* Default value: e_Always.
* @see ScaleCondition
*/
- (ScreenScaleCondition)GetScaleCondition;
/**
* Sets the condition under which the icon should be scaled.
* (Optional)
*
* @param sd A value of the "ScaleCondition" enum type.
* Default value: e_Always.
*/
- (void)SetScaleCondition: (ScreenScaleCondition)sd;
/**
* Returns the Scale Type of the annotation.
*
* @return A value of the "ScaleType" enum which represents the Scale Type of the annotation.
* Default value: P.
* @see ScaleType
*/
- (ScreenScaleType)GetScaleType;
/**
* Sets the Scale Type of the annotation.
* (Optional)
*
* @param st An entry of the "ScaleType" enum which represents the Scale Type of the annotation.
* Default value: P.
* @see ScaleType
*/
- (void)SetScaleType: (ScreenScaleType)st;
/**
* Returns the horizontal leftover space of the icon within the annotation.
*
* @return A number indicating the horizontal
* leftover space of the icon within the annotation.
* @note the horizontal leftover is a number that shall be between
* 0.0 and 1.0 indicating the fraction of leftover space to allocate at the left.
* A value of 0.0 shall position the icon at the left of the annotation rectangle.
* A value of 0.5 shall center it in the horizontal direction within the rectangle.
* This entry shall be used only if the icon is scaled proportionally.
* Default value: 0.5.
*/
- (double)GetHIconLeftOver;
/**
* Sets the horizontal leftover space of the icon within the annotation.
* (Optional)
*
* @param hl A number indicating the horizontal
* leftover space of the icon within the annotation.
* @note the horizontal leftover space is a number that shall be between
* 0.0 and 1.0 indicating the fraction of leftover space to allocate at the left.
* A value of 0.0 shall position the icon at the left of the annotation rectangle.
* A value of 0.5 shall center it in the horizontal direction within the rectangle.
* This entry shall be used only if the icon is scaled proportionally.
* Default value: 0.5.
*/
- (void)SetHIconLeftOver: (double)hl;
/**
* Returns the vertical leftover space of the icon within the annotation.
*
* @return a number indicating the vertical
* leftover space of the icon within the annotation.
* @note the vertical leftover space is a number that
* shall be between 0.0 and 1.0 indicating the fraction of leftover
* space to allocate at the bottom of the icon.
* A value of 0.0 shall position the icon at the bottom
* of the annotation rectangle.
* A value of 0.5 shall center it in the vertical direction within
* the rectangle.
* This entry shall be used only if the icon is scaled proportionally.
* Default value: 0.5.
*/
- (double)GetVIconLeftOver;
/**
* Sets the vertical leftover space of the icon within the annotation.
* (Optional)
*
* @param vl A number indicating the vertical
* leftover space of the icon within the annotation.
* @note the vertical leftover space is a number that
* shall be between 0.0 and 1.0 indicating the fraction of leftover
* space to allocate at the bottom of the icon.
* A value of 0.0 shall position the icon at the bottom
* of the annotation rectangle.
* A value of 0.5 shall center it in the vertical direction within
* the rectangle.
* This entry shall be used only if the icon is scaled proportionally.
* Default value: 0.5.
*/
- (void)SetVIconLeftOver: (double)vl;
/**
* Returns the "fit full" flag.
*
* @return A boolean value indicating the "fit full" flag value.
* @note the fit full flag, if true, indicates that the button
* appearance shall be scaled to fit fully within the bounds of
* the annotation without taking into consideration the line
* width of the border.
* Default value: false.
*/
- (BOOL)GetFitFull;
/**
* Sets the "fit full" flag.
* (Optional)
*
* @param ff A boolean value indicating the "fit full" flag value.
* @note the fit full flag, if true, indicates that the button
* appearance shall be scaled to fit fully within the bounds of
* the annotation without taking into consideration the line
* width of the border. Default value: false.
*/
- (void)SetFitFull: (BOOL)ff;

- (id)init;


@end


/**
* A Sound annotation represents a sound recording attached to a point in
* the PDF document. When closed, this annotation appear as an icon; when open
* and activated, a sound record from the computers microphone or imported from a file
* associated with this annotation is played.The icon of this annotation by default
* is a speaker.
*/
@interface Sound : Markup





/**
* Creates a Sound annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a Sound annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Sound annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds in default user space units.
*
* @return A newly created blank Sound annotation.
*/
+ (Sound*)CreateSoundWithRect: (SDFDoc*)doc pos:  (PDFRect*)pos icon:  (SoundIcon)icon;
/**
* Creates a new Sound annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A point specifying the annotation's location in default user space units.
*
* @return A newly created blank Sound annotation.
*/
+ (Sound*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
+ (Sound*)CreateSoundWithPoint: (SDFDoc*)doc pos:  (PDFPoint*)pos icon:  (SoundIcon)icon;
/**
* Returns the sound object of the Sound annotation.
*
* @return An SDF object representing a sound stream.
* @note The sound stream is to be played when the Sound
* annotation is activated.
*/
- (Obj*)GetSoundStream;
/**
* Sets the sound object of the Sound annotation.
*
* @param sound_stream An SDF object representing a sound stream.
* @note The sound stream is to be played when the Sound
* annotation is activated.
*/
- (void)SetSoundStream: (Obj*)sound_stream;
/**
* Returns the Icon of the Sound annotation.
*
* @return A value of the "Icon" enum.
* Default value: e_Speaker.
* @note The Icon defines the appearance associated with the Sound annotation.
* The annotations appearance stream, if present, will take
* precedence over this entry.
*/
- (SoundIcon)GetIcon;
- (void)SetSoundIconType: (SoundIcon)type;
/**
* Sets the Icon of the Sound annotation.
*(Optional)
*
* @param type A value of the "Icon" enumeration type.
* Default value: e_Speaker.
* @note The Icon defines the appearance associated with the Sound annotation.
* The annotations appearance stream, if present, will take
* precedence over this entry.
*/
- (void)SetIcon;
/**
* Returns the Icon name of the Sound annotation.
*
* @return A string denoting the Icon name of the Sound annotation.
* @note The following Icon names are equivalent
* to predefined Icons from the enum "Icon":
* "Speaker" = e_Speaker
* "Mic" = e_Mic
* "Unknown" = e_Unknown
* The Icon defines the appearance associated with the Sound annotation.
* Names other than mentioned above do not have predefined icon appearances.
* The annotations appearance stream, if present, will take
* precedence over this entry.
*/
- (NSString *)GetIconName;
/**
* Sets the Icon name of the Sound annotation.
*(Optional)
*
* @param type A string denoting the Icon name of the Sound annotation.
* @note The following Icon names are equivalent
* to predefined types from the enum "Icon":
* "Speaker" = e_Speaker
* "Mic" = e_Mic
* "Unknown" = e_Unknown
* The Icon defines the appearance associated with the Sound annotation.
* Names other than mentioned above do not have predefined icon appearances.
* The annotations appearance stream, if present, will take
* precedence over this entry.
*/
- (void)SetSoundIconName: (NSString *)type;

- (id)init;


@end


/**
* Square annotation is used to display a rectangle on the page. When opened,
* a square annotation can display a pop-up window containing the text of the
* associated note. The rectangle may be inscribed and possibly padded within the
* annotation rectangle defined by the annotation dictionary's Rect entry.
*/
@interface Square : Markup





/**
* Creates an Square annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a Square annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Square annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds, in user space coordinates.
*
* @return A newly created blank Square annotation.
*/
+ (Square*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;

- (id)init;


@end


/**
* A Squiggly annotation shows as a wavy line segment across the bottom
* of a word or a group of contiguous words.
*/
@interface Squiggly : TextMarkup





/**
* Creates a Squiggly annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a Squiggly annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Squiggly annotation in the specified document.
*
* @param doc A document to which the Popup annotation is added.
* @param pos A rectangle specifying the Popup annotation's bounds in default user space units.
*
* @return A newly created blank Squiggly annotation.
*/
+ (Squiggly*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;



@end


/**
* A StrikeOut annotation shows as a line segment crossing out
* a word or a group of contiguous words.
*/
@interface StrikeOut : TextMarkup





/**
* Creates a StrikeOut annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a StrikeOut annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new StrikeOut annotation in the specified document.
*
* @param doc A document to which the Popup annotation is added.
* @param pos A rectangle specifying the Popup annotation's bounds in default user space units.
*
* @return A newly created blank StrikeOut annotation.
*/
+ (StrikeOut*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;



@end


/**
* A text annotation represents a "sticky note" attached to a point in
* the PDF document. When closed, the annotation shall appear as an icon;
* when open, it shall display a pop-up window containing the text of
* the note in a font and size chosen by the conforming reader.
* Text annotations do not scale and rotate with the page (i.e. they should
* behave as if the NoZoom and NoRotate annotation flags).
*/
@interface Text : Markup





/**
* Creates a Text annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a Text annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithMku: (Annot*)mku;
/**
* Creates a new Text annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds in default user space units.
*
* @return A newly created blank Text annotation.
*/
+ (Text*)CreateTextWithRect: (SDFDoc*)doc pos:  (PDFRect*)pos contents:  (NSString*)contents;
/**
* Creates a new Text annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds in default user space units.
* @param contents The text of the annotation, that shall be displayed in its popup window.
*
* @return A newly created Text annotation.
*/
+ (Text*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
/**
* Creates a new Text annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A point specifying the annotation's location in default user space units.
*        This determines the location of bottom left corner of the annotation's icon.
* @param contents The text of the annotation, that shall be displayed in its popup window.
*
* @return A newly created Text annotation.
*/
+ (Text*)CreateTextWithPoint: (SDFDoc*)doc pos:  (PDFPoint*)pos contents:  (NSString*)contents;
/**
* Returns the initial status of the Text annotation.
*
* @return A boolean value that specifies whether the annotation shall
* initially be displayed as opened.
* Default value: false.
*/
- (BOOL)IsOpen;
/**
* Sets the initial status of the Text annotation.
* (Optional)
*
* @param isopen A boolean value that specifies whether the annotation shall
* initially be displayed as opened.
* Default value: false.
*/
- (void)SetOpen: (BOOL)isopen;
/**
* Returns the type of the icon associated with the Text annotation.
*
* @return A value of the enumeration type "Icon".
* Default value: e_Note.
* @note The annotations appearance stream,
* if present, will take precedence over this entry.
*/
- (TextIcon)GetIcon;
/**
* Returns the name of the icon associated with the Text annotation.
*
* @return A string denoting the name of the icon.
* @note The following icon names are equivalent
* to predefined icon types from the enum "Icon":
* "Comment" = e_Comment
* "Key" = e_Key
* "Help" = e_Help
* "NewParagraph" = e_NewParagraph
* "Paragraph" = e_Paragraph
* "Insert" = e_Insert
* "Note" = e_Note
* "Unknown" = e_Unknown
* Names other than mentioned above do not have predefined icon appearances.
* @note The annotations appearance stream,
* if present, will take precedence over this entry.
*/
- (NSString *)GetIconName;
- (void)SetTextIconType: (TextIcon)icon;
/**
* Sets the type of the icon associated with the Text annotation.
* (Optional)
*
* @param icon A value of the enum "Icon" type.
* Default value: e_Note.
* @note The annotations appearance stream,
* if present, will take precedence over this entry.
*/
- (void)SetIcon;
/**
* Sets the name of the icon associated with the Text annotation.
* (Optional)
*
* @param icon A string denoting the name of the icon.
* @note The following icon names are equivalent
* to predefined icon types from the enum "Icon":
* "Comment" = e_Comment
* "Key" = e_Key
* "Help" = e_Help
* "NewParagraph" = e_NewParagraph
* "Paragraph" = e_Paragraph
* "Insert" = e_Insert
* "Note" = e_Note
* "Unknown" = e_Unknown
* Names other than mentioned above do not have predefined icon appearances.
* @note The annotations appearance stream,
* if present, will take precedence over this entry.
*/
- (void)SetTextIconName: (NSString *)icon;
/**
* Returns the string indicating the state of the Text annotation.
* (PDF 1.5)
*
* @return A string that indicates the state of the Text annotation when first loaded.
* Default: Unmarked if StateModel is Marked; None if StateModel is Review.
*/
- (NSString*)GetState;
/**
* Sets the string indicating the state of the Text annotation.
* (Optional; PDF 1.5 )
*
* @param state A string that indicates the state of the Text annotation when first loaded.
* Default: Unmarked if StateModel is Marked; None if StateModel is Review.
*/
- (void)SetState: (NSString*)state;
/**
* Returns the string indicating the state model of the Text annotation.
* (PDF 1.5)
*
* @return A string containing the state model name - either "Marked" or "Review".
*/
- (NSString*)GetStateModel;
/**
* Sets the string indicating the state model of the Text annotation.
* (Required if State is present, otherwise optional; PDF 1.5 )
*
* @param sm A string containing the state model name - either "Marked" or "Review".
*/
- (void)SetStateModel: (NSString*)sm;

- (id)init;


@end


/**
* An Underline annotation shows as a line segment across the bottom
* of a word or a group of contiguous words.
*/
@interface Underline : TextMarkup





/**
* Creates an Underline annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates an Underline annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Underline annotation in the specified document.
*
* @param doc A document to which the Underline annotation is added.
* @param pos A rectangle specifying the Underline annotation's bounds in default user space units.
*
* @return A newly created blank Underline annotation.
*/
+ (Underline*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;



@end


/**
* A Watermark annotation is an annotation that is printed at a fixed
* size and position on a page, regardless of the dimensions of the printed page.
*/
@interface Watermark : Annot





/**
* Creates a Watermark annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a Watermark annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new Watermark annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds in default user space units.
*
* @return A newly created blank Watermark annotation.
*/
+ (Watermark*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;

- (id)init;


@end


/**
* A Widget annotation (PDF 1.2) are used to represent the appearance of interactive
* form field and to manage user interactions with forms.
*/
@interface Widget : Annot





/**
* Creates a widget annotation and initializes it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithD: (Obj*)d;
/**
* Creates a widget annotation and initializes it using given annotation object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithAnn: (Annot*)ann;
/**
* Creates a new widget annotation in the specified document.
*
* @param doc A document to which the annotation is added.
* @param pos A rectangle specifying the annotation's bounds in default user space units.
* @param field A form field associated with this widget.
*
* @return A newly created blank widget annotation.
*/
+ (Widget*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos field:  (TRNField*)field;
/**
* Returns the field associated with the Widget.
* @return A Field object.
*/
- (TRNField*)GetField;
/**
* @return the HighlightingMode of the widget annotation.
* @note The annotations highlighting mode is the visual effect that shall be used
* when the mouse button is pressed or held down inside its active area
* @note A highlighting mode other than e_push will override any down appearance
* defined for the annotation.
* @default e_invert.
*/
- (WidgetHighlightingMode)GetHighlightingMode;
/**
* Sets the HighlightingMode for the widget annotation.
* @note The annotations highlighting mode is the visual effect that shall be used
* when the mouse button is pressed or held down inside its active area
* @param mode - New highlighting mode for the widget.
* @note A highlighting mode other than e_push shall override any down appearance defined
* for the annotation.
* Default value: e_invert.
*/
- (void)SetHighlightingMode: (WidgetHighlightingMode)mode;
/**
* Returns the action of the widget annotation
*
* @return An action object representing the action of the widget annotation
* that should be performed when the annotation is activated.
*/
- (Action*)GetAction;
/**
* Sets the action of the widget annotation
* (Optional; PDF1.2 )
*
* @param action An action object representing the action of the widget annotation
* that should be performed when the annotation is activated.
*/
- (void)SetAction: (Action*)action;
/**
* Returns the additional actions of the annotation.
*
* @return An SDF object representing the additional actions dictionary of the annotation.
* @note An additional-actions dictionary defines the screen annotations behaviour
* in response to various trigger events. This corresponds to 'AA' entry of the
* annotation dictionary.
*/
- (Obj*)GetTriggerAction;
/**
* Assigns additional actions to the annotation
* (Optional; PDF1.1 )
*
* @param action An SDF dictionary object representing the actions of the annotation.
* @note An additional-actions dictionary defines the screen annotations behaviour
* in response to various trigger events. This corresponds to 'AA' entry of the
* annotation dictionary.
*/
- (void)SetTriggerAction: (Obj*)action;
/**
* Returns the rotation value of the  annotation.
*
* @return An integer representing the rotation value of the  annotation.
* @note The Rotation specifies the number of degrees by which the
* annotation shall be rotated counterclockwise relative to the page.
* The value shall be a multiple of 90.
* Default value: 0.
*/
- (int)GetRotation;
/**
* Sets the rotation value of the  annotation.
* (Optional)
*
* @param rot An integer representing the rotation value of the  annotation.
* @note the Rotation specifies the number of degrees by which the
* annotation shall be rotated counterclockwise relative to the page.
* The value shall be a multiple of 90.
* Default value: 0.
*/
- (void)SetRotation: (int)rot;
/**
* Returns the number indicating border color space of the annotation.
*
* @return An integer indicating a color space value from the ColorSpace::Type enum.
* That is, 1 corresponding to "e_device_gray",
* 3 corresponding to "e_device_rgb", and 4 corresponding to "e_device_cmyk".
* 0 means this annotation had no color assigned.
*/
- (int)GetBorderColorCompNum;
/**
* Returns the border color of the annotation.
*
* @return A color object that denotes the color of the Screen border.
* @note The color can be in different color spaces: Gray, RGB, or CMYK.
* Call "GetBorderColorCompNum" to access the color space information corresponding to the border color.
*/
- (ColorPt*)GetBorderColor;
/**
* Sets the border color of the annotation.
* (Optional)
*
* @param c A color object that denotes the color of the screen border.
* @param CompNum An integer which value indicates the color space used for the parameter c.
*/
- (void)SetBorderColor: (ColorPt*)c CompNum:  (int)CompNum;
/**
* Returns the number indicating background color space of the annotation.
*
* @return An integer indicating a color space value from the ColorSpace::Type enum.
* That is, 1 corresponding to "e_device_gray",
* 3 corresponding to "e_device_rgb", and 4 corresponding to "e_device_cmyk" if color space is applicable,
* 0 means no background color was assigned.
*/
- (int)GetBackgroundColorCompNum;
/**
* Returns the background color of the annotation.
*
* @return A color object that denotes the color of the Screen background.
* @note The color can be in different color spaces: Gray, RGB, or CMYK.
* Call "GetBackgroundColorCompNum" to access the color space information corresponding to the border color.
*/
- (ColorPt*)GetBackgroundColor;
/**
* Sets the background color of the annotation.
* (Optional)
*
* @param c A color point that denotes the color of the screen background.
* @param CompNum An integer which value indicates the color space used for the parameter c.
*/
- (void)SetBackgroundColor: (ColorPt*)c CompNum:  (int)CompNum;
/**
* Returns static caption text of the annotation.
*
* @return A string containing the static caption text of the annotation.
* @note The static caption is the annotations normal caption, which
* shall be displayed when it is not interacting with the user.
* Unlike the remaining entries with the captions, which apply only to widget
* annotations associated with pushbutton fields, the Static Caption(CA) entry may be used
* with any type of button field, including check boxes.
* @note This property is part of the Widget appearance characteristics dictionary, this dictionary
* that shall be used in constructing a dynamic appearance stream specifying the annotations visual
* presentation on the page.
*/
- (NSString*)GetStaticCaptionText;
/**
* Sets static caption text of the annotation.
* (Optional; button fields only)
*
* @param ct A string containing the static caption text of the annotation.
* @note The static caption is the annotations normal caption, which
* shall be displayed when it is not interacting with the user.
* Unlike the remaining entries with the captions, which apply only to widget
* annotations associated with pushbutton fields, the Static Caption(CA) entry may be used
* with any type of button field, including check boxes.
* @note This property is part of the Widget appearance characteristics dictionary, this dictionary
* that shall be used in constructing a dynamic appearance stream specifying the annotations visual
* presentation on the page.
*/
- (void)SetStaticCaptionText: (NSString*)ct;
/**
* Returns the rollover caption text of the annotation.
*
* @return A string containing the rollover caption text of the annotation.
* @note The rollover caption shall be displayed when the user rolls the cursor
* into its active area without pressing the mouse button.
*/
- (NSString*)GetRolloverCaptionText;
/**
* Sets the roll over caption text of the annotation.
* (Optional; button fields only)
*
* @param ct A string containing the roll over caption text of the annotation.
* @note The rollover caption shall be displayed when the user rolls the cursor
* into its active area without pressing the mouse button.
*/
- (void)SetRolloverCaptionText: (NSString*)ct;
/**
* Returns the button down caption text of the annotation.
*
* @return A string containing the button down text of the annotation.
* @note The button down caption shall be displayed when the mouse button is
* pressed within its active area.
*/
- (NSString*)GetMouseDownCaptionText;
/**
* Sets the button down caption text of the annotation.
* (Optional; button fields only)
*
* @param ct A string containing the button down text of the annotation.
* @note The button down caption shall be displayed when the mouse button is
* pressed within its active area.
*/
- (void)SetMouseDownCaptionText: (NSString*)ct;
/**
* Returns the static icon associated with the annotation.
*
* @return An SDF object that represents the static icon
* associated with the annotation.
* @note The static icon object is a form XObject defining the
* annotations normal icon, which shall be
* displayed when it is not interacting with the user.
*/
- (Obj*)GetStaticIcon;
/**
* Sets the static icon associated with the annotation.
* (Optional; button fields only)
*
* @param ic An SDF object that represents the static icon
* associated with the annotation.
* @note The static icon object is a form XObject defining the
* annotations normal icon, which shall be
* displayed when it is not interacting with the user.
*/
- (void)SetStaticIcon: (Obj*)ic;
/**
* Returns the rollover icon associated with the annotation.
*
* @return An SDF object that represents the rollover icon
* associated with the annotation.
* @note The rollover icon object is a form XObject defining the
* annotations rollover icon, which shall be displayed
* when the user rolls the cursor into its active area without
* pressing the mouse button.
*/
- (Obj*)GetRolloverIcon;
/**
* Sets the rollover icon associated with the annotation.
* (Optional; button fields only)
*
* @param ic An SDF object that represents the rollover icon
* associated with the annotation.
* @note The rollover icon object is a form XObject defining the
* annotations rollover icon, which shall be displayed
* when the user rolls the cursor into its active area without
* pressing the mouse button.
*/
- (void)SetRolloverIcon: (Obj*)ic;
/**
* Returns the Mouse Down icon associated with the annotation.
*
* @return An SDF object that represents the Mouse Down icon
* associated with the annotation.
* @note The Mouse Down icon object is a form XObject defining the
* annotations alternate (down) icon, which shall be displayed
* when the mouse button is pressed within its active area.
*/
- (Obj*)GetMouseDownIcon;
/**
* Sets the Mouse Down icon associated with the annotation.
* (Optional; button fields only)
*
* @param ic An SDF object that represents the Mouse Down icon
* associated with the annotation.
* @note The Mouse Down icon object is a form XObject defining the
* annotations alternate (down) icon, which shall be displayed
* when the mouse button is pressed within its active area.
*/
- (void)SetMouseDownIcon: (Obj*)ic;
/**
* Returns the Icon and caption relationship of the  annotation.
*
* @return A value of the "IconCaptionRelation" enum type.
* Default value: e_NoIcon.
* @see IconCaptionRelation
*/
- (WidgetIconCaptionRelation)GetIconCaptionRelation;
/**
* Sets the Icon and caption relationship of the  annotation.
* (Optional; pushbutton fields only)
*
* @param icr A value of the "IconCaptionRelation" enum type.
* Default value: e_NoIcon.
* @see IconCaptionRelation
*/
- (void)SetIconCaptionRelation: (WidgetIconCaptionRelation)icr;
/**
* Returns the condition under which the icon should be scaled.
*
* @return A value of the "ScaleCondition" enum type.
* Default value: e_Always.
* @see ScaleCondition
*/
- (WidgetScaleCondition)GetScaleCondition;
/**
* Sets the condition under which the icon should be scaled.
* (Optional)
*
* @param sd A value of the "ScaleCondition" enum type.
* Default value: e_Always.
*/
- (void)SetScaleCondition: (WidgetScaleCondition)sd;
/**
* Returns the Scale Type of the annotation.
*
* @return A value of the "ScaleType" enum which represents the Scale Type of the annotation.
* Default value: P.
* @see ScaleType
*/
- (WidgetScaleType)GetScaleType;
/**
* Sets the Scale Type of the annotation.
* (Optional)
*
* @param st An entry of the "ScaleType" enum which represents the Scale Type of the annotation.
* Default value: P.
* @see ScaleType
*/
- (void)SetScaleType: (WidgetScaleType)st;
/**
* Returns the horizontal leftover space of the icon within the annotation.
*
* @return A number indicating the horizontal
* leftover space of the icon within the annotation.
* @note the horizontal leftover is a number that shall be between
* 0.0 and 1.0 indicating the fraction of leftover space to allocate at the left.
* A value of 0.0 shall position the icon at the left of the annotation rectangle.
* A value of 0.5 shall center it in the horizontal direction within the rectangle.
* This entry shall be used only if the icon is scaled proportionally.
* Default value: 0.5.
*/
- (double)GetHIconLeftOver;
/**
* Sets the horizontal leftover space of the icon within the annotation.
* (Optional)
*
* @param hl A number indicating the horizontal
* leftover space of the icon within the annotation.
* @note the horizontal leftover space is a number that shall be between
* 0.0 and 1.0 indicating the fraction of leftover space to allocate at the left.
* A value of 0.0 shall position the icon at the left of the annotation rectangle.
* A value of 0.5 shall center it in the horizontal direction within the rectangle.
* This entry shall be used only if the icon is scaled proportionally.
* Default value: 0.5.
*/
- (void)SetHIconLeftOver: (double)hl;
/**
* Returns the vertical leftover space of the icon within the annotation.
*
* @return a number indicating the vertical
* leftover space of the icon within the annotation.
* @note the vertical leftover space is a number that
* shall be between 0.0 and 1.0 indicating the fraction of leftover
* space to allocate at the bottom of the icon.
* A value of 0.0 shall position the icon at the bottom
* of the annotation rectangle.
* A value of 0.5 shall center it in the vertical direction within
* the rectangle.
* This entry shall be used only if the icon is scaled proportionally.
* Default value: 0.5.
*/
- (double)GetVIconLeftOver;
/**
* Sets the vertical leftover space of the icon within the annotation.
* (Optional)
*
* @param vl A number indicating the vertical
* leftover space of the icon within the annotation.
* @note the vertical leftover space is a number that
* shall be between 0.0 and 1.0 indicating the fraction of leftover
* space to allocate at the bottom of the icon.
* A value of 0.0 shall position the icon at the bottom
* of the annotation rectangle.
* A value of 0.5 shall center it in the vertical direction within
* the rectangle.
* This entry shall be used only if the icon is scaled proportionally.
* Default value: 0.5.
*/
- (void)SetVIconLeftOver: (double)vl;
/**
* Returns the "fit full" flag.
*
* @return A boolean value indicating the "fit full" flag value.
* @note the fit full flag, if true, indicates that the button
* appearance shall be scaled to fit fully within the bounds of
* the annotation without taking into consideration the line
* width of the border.
* Default value: false.
*/
- (BOOL)GetFitFull;
/**
* Sets the "fit full" flag.
* (Optional)
*
* @param ff A boolean value indicating the "fit full" flag value.
* @note the fit full flag, if true, indicates that the button
* appearance shall be scaled to fit fully within the bounds of
* the annotation without taking into consideration the line
* width of the border. Default value: false.
*/
- (void)SetFitFull: (BOOL)ff;

- (id)init;


@end


/**
* The OCG::Config object represents an optional-content (OC) configuration
* structure (see section 4.10.3 in PDF Reference), used to persist a set
* of visibility states and other optional-content information in a PDF file
* A document has a default configuration, saved in the D entry in the
* 'OCProperties' dictionary (that can be obtained using pdfdoc.GetOCConfig()),
* and can have a list of other configurations, saved as an array in the
* 'Configs' entry in the OCProperties dictionary.
* <p>
* Configurations are typically used to initialize the OCG ON-OFF states for
* an optional-content context (OCG::Context). The OCG order in the configuration
* is the order in which the groups appear in the Layers panel of a PDF viewer.
* The configuration can also define a set of mutually exclusive OCGs, called a
* radio button group.
* </p>
*/
@interface Config : NSObject
{


}





/**
* Creates a new optional-content configuration object in the document.
* @param doc The document in which the new OCG::Config will be created.
* @param default_config If true, the configuration will be set as the
* default OCG configuration (i.e. listed as a D entry under 'OCProperies'
* dictionary).
* @return The newly created configuration object.
*/
+ (Config*)Create: (PDFDoc*)doc default_config:  (BOOL)default_config;	/**
* Creates a new optional-content configuration from an existing SDF/Cos object.
*/
- (id)initWithOcg_config: (Obj*)ocg_config;

/**
* @return true is this is a valid (non-null) configuration, false otherwise.
*/
- (BOOL)IsValid;
/**
* @return the Obj array that specifies the order of optional content (OC) groups
* in this configuration or NULL if the configuration does not contain any OCGs.
* The order of OCGs in the array is used to represent the order in which the
* group names are displayed in the Layers panel of a PDF viewer application.
* For more information, please refer to Section 4.10.3 in the PDF Reference.
*/
- (Obj*)GetOrder;
/**
* Sets the user interface display order of optional-content groups (OCGs) in
* this configuration. This is the order in which the group names are displayed
* in the Layers panel of a PDF viewer.
*
* @param ocgs_array The SDF/Cos object containing the OCG order array.
* For more information, please refer to section 4.10.3 in the PDF Reference.
*/
- (void)SetOrder: (Obj*)ocgs_array;
/**
* @return the name of an optional-content configuration (suitable for
* presentation in a user interface).
*/
- (NSString*)GetName;
/**
* Sets the name of an optional-content configuration (suitable for presentation
* in a user interface). The method stores the specified string as the Name entry
* in the configuration's SDF/Cos dictionary.
* @param name The new name string.
*/
- (void)SetName: (NSString*)name;
/**
* @return the creator property of an optional-content configuration. The string
* is used to represent the name of the application or feature that created this
* configuration.
*/
- (NSString*)GetCreator;
/**
* Sets the creator property of an optional-content configuration. Stores the
* specified string as the Creator entry in the configuration's SDF/Cos dictionary.
* @param name The new creator string.
*/
- (void)SetCreator: (NSString*)name;
/**
* @return the base initialization state. This state is used to initialize the states
* of all the OCGs in a document when this configuration is applied. The value of this entry
* must be one of the following names:
*  <li>ON: The states of all groups are turned ON. </li>
*  <li>OFF: The states of all groups are turned OFF.</li>
*  <li>Unchanged: The states of all groups are left unchanged.</li>
*
* <p> After base initialization, the contents of the ON and OFF arrays are processed, overriding
* the state of the groups included in the arrays.</p>
* @note: If BaseState is present in the document's default configuration dictionary, its value must
* be "ON".
* @default ON.
*/
- (NSString *)GetInitBaseState;
/**
* @return the "ON" initialization array from the configuration dictionary or
* NULL if the array is not present. The returned object is an array of optional
* content groups whose state should be set to ON when this configuration is applied.
* Note: If the BaseState entry is ON, this entry is redundant.
*/
- (Obj*)GetInitOnStates;
/**
* @return the "OFF" initialization array from the configuration dictionary or
* NULL if the array is not present. The returned object is an array of optional
* content groups whose state should be set to OFF when this configuration is applied.
* Note: If the BaseState entry is OFF, this entry is redundant.
*/
- (Obj*)GetInitOffStates;
/**
* Sets the base initialization state. For more info, please see GetInitBaseState().
* @param state new base state ("ON", "OFF", or "Unchanged").
*/
- (void)SetInitBaseState: (NSString *)state;
/**
* Sets the 'ON' initialization array in the configuration dictionary.
* For more info, please see SetInitOnStates() and  section 4.10.3 in PDF Reference.
*/
- (void)SetInitOnStates: (Obj*)on_array;
/**
* Sets the 'OFF' initialization array in the configuration dictionary.
* For more info, please see SetInitOffStates() and section 4.10.3 in PDF Reference.
*/
- (void)SetInitOffStates: (Obj*)off_array;
/**
* @return OCG configuration intent. An intent is a name object (or an array of name
* objects) broadly describing the intended use, which can be either "View" or "Design".
* A group's content is considered to be optional (that is, the group's state is considered
* in its visibility) if any intent in its list matches an intent of the context. The
* intent list of the context is usually set from the intent list of the document
* configuration. If the configuration has no Intent entry, the default value of
* "View" is used.
*/
- (Obj*)GetIntent;
/**
* Sets the Intent entry in an optional-content configuration's SDF/Cos dictionary.
* For more information, see GetIntent().
* @param intent The new Intent entry value (a name object or an array of name objects).
*/
- (void)SetIntent: (Obj*)intent;
/**
* @return the list of locked OCGs or NULL if there are no locked OCGs.
* The on/off state of a locked OCG cannot be toggled by the user through the
* user interface.
*/
- (Obj*)GetLockedOCGs;
/**
* Sets the array of locked OCGs. The on/off state of a locked OCG cannot be
* toggled by the user through the user interface.
*
* @param locked_ocg_array An SDF/Cos array of OCG objects to be locked in this
* configuration, or an empty array if the configuration should not contain
* locked OCGs. The default is the empty array.
*/
- (void)SetLockedOCGs: (Obj*)locked_ocg_array;
/**
* @return Pointer to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;


@end


/**
* The OCG::Group object represents an optional-content group. This corresponds
* to a PDF OCG dictionary representing a collection of graphic objects that can
* be made visible or invisible (Section 4.10.1 'Optional Content Groups' in PDF
* Reference). Any graphic content of the PDF can be made optional, including page
* contents, XObjects, and annotations. The specific content objects in the group
* have an OC entry in the PDF as part of the surrounding marked content or in the
* XObject dictionary. The group itself is a named object that can be typically
* manipulated through a Layers panel in a PDF viewer.
* <p>
* In the simplest case, the group's ON-OFF state makes the associated content
* visible or hidden. The ON-OFF state of a group can be toggled for a particular
* context (OCG::Context), and a set of states is kept in a configuration (OCG::Config).
* The visibility can depend on more than one group in an optional-content membership
* dictionary (OCG::OCMD), and can also be affected by the context's draw mode
* (OCGContext::OCDrawMode).
* </p><p>
* A group has an Intent entry, broadly describing the intended use. A group's
* content is considered to be optional (that is, the group's state is considered in
* its visibility) if any intent in its list matches an intent of the context. The
* intent list of the context is usually set from the intent list of the document
* configuration.
* </p><p>
* A Usage dictionary entry provides more specific intended usage information than
* an intent entry. Possible key values are: CreatorInfo, Language, Export, Zoom,
* Print, View, User, PageElement. The usage value can act as a kind of metadata,
* describing the sort of things that belong to the group, such as text in French,
* fine detail on a map, or a watermark. The usage values can also be used by the
* AutoState mechanism to make decisions about what groups should be on and what
* groups should be off. The AutoState mechanism considers the usage information
* in the OCGs, the AS array of the configuration, and external factors; for example,
* the language the application is running in, the current zoom level on the page,
* or whether the page is being printed.
*/
@interface Group : NSObject
{


}





/**
* Creates a new optional-content group (OCG) object in the document.
* @param doc The document in which the new OCG will be created.
* @param name The name of the optional-content group.
* @return The newly created OCG::Group object.
*/
+ (Group*)Create: (PDFDoc*)doc name:  (NSString*)name;	/**
* Creates a new optional-content group (OCG) object from an existing
* SDF/Cos object.
*/
- (id)initWithOcg: (Obj*)ocg;

/**
* @return True if this is a valid (non-null) OCG, false otherwise.
*/
- (BOOL)IsValid;
/**
* @return the name of this optional-content group (OCG).
*/
- (NSString*)GetName;
/**
* Sets the name of this optional-content group (OCG).
* @param name The new name.
*/
- (void)SetName: (NSString*)name;
/**
* @return true if this OCG object is in the ON state in a given context,
* false otherwise.
* @param context The context for which to get the group's state.
*/
- (BOOL)GetCurrentState: (Context*)context;
/**
* Sets the current ON-OFF state of the optional-content group (OCG) object in a given context.
* @param context The context for which to set the group's state.
* @param state The new state.
*/
- (void)SetCurrentState: (Context*)context state:  (BOOL)state;
/**
* @return The initial state (ON or OFF) of the optional-content group
* (OCG) object in a given configuration.
*
* @param config The configuration for which to get the group's initial state.
* @note If the configuration has a BaseState of Unchanged, and the OCG is
* not listed explicitly in its ON list or OFF list, then the initial state
* is taken from the OCG's current state in the document's default context.
*/
- (BOOL)GetInitialState: (Config*)config;
/**
* Sets the initial state (ON or OFF) of the optional-content group (OCG)
* object in a given configuration.
*
* @param config The configuration for which to set the group's initial state.
* @param state The new initial state, true if the state is ON, false if it is OFF.
*/
- (void)SetInitialState: (Config*)config state:  (BOOL)state;
/**
* @return OCG intent.
* An intent is a name object (or an array of name objects) broadly describing the
* intended use, which can be either "View" or "Design". A group's content is
* considered to be optional (that is, the group's state is considered in its
* visibility) if any intent in its list matches an intent of the context. The
* intent list of the context is usually set from the intent list of the document
* configuration.
*/
- (Obj*)GetIntent;
/**
* Sets the Intent entry in an optional-content group's SDF/Cos dictionary.
* For more information, see GetIntent().
* @param intent The new Intent entry value (a name object or an array of name objects).
*/
- (void)SetIntent: (Obj*)intent;
/**
* @return true if this OCG is locked in a given configuration, false otherwise.
* The on/off state of a locked OCG cannot be toggled by the user through the user interface.
* @param config The OC configuration.
*/
- (BOOL)IsLocked: (Config*)config;
/**
* Sets the locked state of an OCG in a given configuration. The on/off state of a
* locked OCG cannot be toggled by the user through the user interface.
*
* @param config IN/OUT The optional-content configuration.
* @param locked true if the OCG should be locked, false otherwise.
*/
- (void)SetLocked: (Config*)config locked:  (BOOL)locked;
/**
* @return true if this group is associated with a Usage dictionary, false otherwise.
*/
- (BOOL)HasUsage;
/**
* @return The usage information associated with the given key in the Usage dictionary
* for the group, or a NULL if the entry is not present. A Usage dictionary entry
* provides more specific intended usage information than an intent entry.
*
* @param key The usage key in the usage dictionary entry. The possible key values are:
* CreatorInfo, Language, Export, Zoom, Print, View, User, PageElement.
*/
- (Obj*)GetUsage: (NSString *)key;
/**
* @return Pointer to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;


@end


/**
* <p>
* The OCG::Context object represents an optional-content context in a document, within which
* document objects such as words or annotations are visible or hidden. The context keeps track
* of the ON-OFF states of all of the optional-content groups (OCGs) in a document. Content is
* or is not visible with respect to the OCG states stored in a specific context. Unlike other
* objects in OCG namespace, the OCG::Context does not correspond to any explicit PDF structure.
* </p><p>
* Each PDFView has a default context (PDF::GetOCGContext()) that it uses for on-screen drawing
* and that determines the default state for any drawing. The context has flags that control
* whether to draw content that is marked as optional, and whether to draw content that is not
* marked as optional.
* </p><p>
* When enumerating page content, OCG::Context can be passed as a parameter in ElementReader.Begin()
* method. When using PDFDraw, PDFRasterizer, or PDFView class to render PDF pages use
( PDFDraw::SetOCGContext() method to select an OC context.
* </p><p>
* There can be more than one Context object, representing different combinations of OCG states.
* You can change the states of OCGs within any context. You can build contexts with your own
* combination of OCG states, and issue drawing or enumeration commands using that context.
* For example, you can pass an optional-content context to ElementReader.Begin(). You can save
* the resulting state information as part of the configuration (e.g. using Config::SetInit methods),
* but the context itself has no corresponding PDF representation, and is not saved.
* </p>
*/
@interface Context : NSObject
{


}





/**
* Create a context object that represents an optional-content state of the
* document from a given configuration.
*
* @param config A configuration from which to take initial OCG states.
*/
- (id)initWithConfig: (Config*)config;
/**
* @return true is this is a valid (non-null) context, false otherwise.
*/
- (BOOL)IsValid;
/**
* @return the ON-OFF states (true or false) for the given optional-content
* group (OCG) in this OC context.
*
* @param group The optional-content group (OCG) that is queried.
*/
- (BOOL)GetState: (Group*)group;
/**
* Sets the ON-OFF states for the given optional-content group (OCG) in this
* context.
* @param group The optional-content group (OCG) that is queried.
* @param state true for 'ON' and false for 'OFF'.
*/
- (void)SetState: (Group*)group state:  (BOOL)state;
/**
* Sets the sates of all OCGs in the context to ON or OFF.
* @param all_on A flag used to specify whether the OCG states should be set
* to ON (if true), or OFF (if false).
*/
- (void)ResetStates: (BOOL)all_on;
/**
* Sets the non-OC status for this context. Content that is not marked
* as optional content is drawn (or element.IsOCVisible()) when 'draw_non_OC'
* is true, and not drawn/visible otherwise.
*
* @param draw_non_OC A flag specifying whether the content that is not
* marked as optional should be treated as visible.
*/
- (void)SetNonOCDrawing: (BOOL)draw_non_OC;
/**
* @return the non-OC status for this context. The flag indicates whether the
* content that is not marked as optional should be treated as visible.
* For more information, please see SetNonOCDrawing().
*/
- (BOOL)GetNonOCDrawing;
/**
* Sets the drawing and enumeration type for this context. This type, together
* with the visibility determined by the OCG and OCMD states, controls whether
* content that is marked as optional content is drawn or enumerated.
*
* @param oc_draw_mode A flag specifying the visibility of optional content.
*/
- (void)SetOCDrawMode: (OCDrawMode)oc_draw_mode;
/**
* @return the drawing and enumeration type for this context.
* For more information, please see SetOCMode() and OCG::Context::OCDrawMode.
*/
- (OCDrawMode)GetOCMode;



@end


/**
* The OCMD object represents an Optional Content Membership Dictionary (OCMD)
* that allows the visibility of optional content to depend on the states in a
* set of optional-content groups (OCG::Group). The object directly corresponds
* to the OCMD dictionary (Section 4.10.1 'Optional Content Groups' in PDF
* Reference).
* <p>
* An OCMD collects a set of OCGs. It sets a visibility policy, so that
* content in the member groups is visible only when all groups are ON
* or OFF, or when any of the groups is ON or OFF. This makes it possible
* to set up complex dependencies among groups. For example, an object can be
* visible only if some other conditions are met (such as if another layer is
* visible).
* </p>
*/
@interface OCMD : NSObject
{


}





/**
* Creates a new optional-content membership dictionary (OCMD) object in the
* given document for the given groups and visibility policy.
*
* @param doc The document in which the new OCMD will be created.
* @param ocgs An array of optional-content groups (OCGs) to be members of the dictionary.
* @param policy The visibility policy that determines the visibility of content with respect
* to the ON-OFF state of OCGs listed in the dictionary.
*
* @return The newly created OCG::OCMD object.
*/
+ (OCMD*)Create: (PDFDoc*)doc ocgs:  (Obj*)ocgs vis_policy:  (VisibilityPolicyType)vis_policy;	/**
* Creates a new optional-content group membership dictionary (OCMD) object from
* an existing SDF/Cos object.
*/
- (id)initWithOcmd: (Obj*)ocmd;

/**
* @return True if this is a valid (non-null) OCMD, false otherwise.
*/
- (BOOL)IsValid;
/**
* Returns the optional-content groups listed under 'OCGs' entry in the object
* dictionary.
*
* @return A dictionary (for a single OCG::Group object), an SDF::Obj array
* (for multiple OCG::Group objects) or NULL (for an empty OCMD).
*/
- (Obj*)GetOCGs;
/**
* Returns the optional-content membership dictionary's visibility policy, which
* determines the visibility of content with respect to the ON-OFF state of
* OCGs listed in the dictionary.
*
* @return The visibility policy.
*/
- (VisibilityPolicyType)GetVisibilityPolicy;
/**
* Sets the optional-content membership dictionary's visibility policy, which
* determines the visibility of content with respect to the ON-OFF state of
* OCGs listed in the dictionary.
* @param vis_policy New visibility policy.
*/
- (void)SetVisibilityPolicy: (VisibilityPolicyType)vis_policy;
/**
* @return If the PDOCMD has a visibility expression entry, return the
* SDF::Obj array object representing the expression, otherwise returns NULL.
*/
- (Obj*)GetVisibilityExpression;
/**
* @return true if content tagged with this OCMD is visible in the given
* context, false if it is hidden.
* <p>
* Based on the optional-content groups listed in the dictionary, the current
* ON-OFF state of those groups within the specified context, and the
* dictionary's visibility policy, test whether the content tagged with
* this dictionary would be visible.
*
* @param context The context in which the visibility of content is tested.
*/
- (BOOL)IsCurrentlyVisible: (Context*)context;
/**
* @return Pointer to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;


@end


/**
* PDFACompliance class is used to validate PDF documents for PDF/A (ISO 19005:1/2/3)
* compliance or to convert existing PDF files to PDF/A compliant documents.
*
* The conversion option analyzes the content of existing PDF files and performs
* a sequence of modifications in order to produce a PDF/A compliant document.
* Features that are not suitable for long-term archiving (such as encryption,
* obsolete compression schemes, missing fonts, or device-dependent color) are
* replaced with their PDF/A compliant equivalents. Because the conversion process
* applies only necessary changes to the source file, the information loss is
* minimal. Also, because the converter provides a detailed report for each change,
* it is simple to inspect changes and to determine whether the conversion loss
* is acceptable.
*
* The validation option in PDF/A Manager can be used to quickly determine whether
* a PDF file fully complies with the PDF/A specification according to the
* international standard ISO 19005:1/2/3. For files that are not compliant, the
* validation option can be used to produce a detailed report of compliance
* violations as well as a list of relevant error objects.
*
* Key Functions:
* - Checks if a PDF file is compliant with PDF/A (ISO 19005:1/2/3) specification.
* - Converts any PDF to a PDF/A compliant document.
* - Supports PDF/A-1a, PDF/A-1b, PDF/A-2b
* - Produces a detailed report of compliance violations and associated PDF objects.
* - Keeps the required changes a minimum, preserving the consistency of the original.
* - Tracks all changes to allow for automatic assessment of data loss.
* - Allows user to customize compliance checks or omit specific changes.
* - Preserves tags, logical structure, and color information in existing PDF documents.
* - Offers automatic font substitution, embedding, and subsetting options.
* - Supports automation and batch operation. PDF/A Converter is designed to be used
*   in unattended mode in high throughput server or batch environments
*/
@interface PDFACompliance : NSObject
{


}





/**
* Perform PDF/A validation or PDF/A conversion on the input PDF document.
*
* @param convert A flag used to instruct PDF/A processor to perform PDF/A
* conversion (if 'true') or PDF/A validation (if 'false'). After PDF/A conversion
* you can save the resulting document using Save() method(s).
* @param filepath - pathname to the file.
* @param password An optional parameter that can be used to specify the
* password for encrypted PDF documents (typically only useful in the conversion mode).
* @param conf The PDF conformance level. The default value is e_Level1B.
* @param max_ref_objs The maximum number of object references per error condition.
*
* @exception. Throws an exception if the file can't be opened.
*/
- (id)initWithConvert: (BOOL)convert file_path:  (NSString*)file_path password:  (NSString *)password conf:  (Conformance)conf exceptions:  (int)exceptions num_exceptions:  (int)num_exceptions max_ref_objs:  (int)max_ref_objs first_stop:  (BOOL)first_stop;
/**
* Perform PDF/A validation or PDF/A conversion on the input PDF document
* which is stored in a memory buffer.
*
* @param convert A flag used to instruct PDF/A processor to perform PDF/A
* conversion (if 'true') or PDF/A validation (if 'false'). After PDF/A conversion
* you can save the resulting document using Save() method(s).
* @param buf A memory buffer containing the serialized PDF document.
* @param buf_size The size of memory buffer.
* @param password An optional parameter that can be used to specify the
* password for encrypted PDF documents (typically only useful in the conversion mode).
* @param conf The PDF conformance level. The default value is e_Level1B.
* @param max_ref_objs The maximum number of object references per error condition.
*
* @exception. Throws an exception if the file can't be opened.
*/
- (id)initWithConvert: (BOOL)convert buf:  (NSString *)buf buf_size:  (unsigned long)buf_size password:  (NSString *)password conf:  (Conformance)conf exceptions:  (int)exceptions num_exceptions:  (int)num_exceptions max_ref_objs:  (int)max_ref_objs first_stop:  (BOOL)first_stop;
/**
* Serializes the converted PDF/A document to a file on disk.
* @note This method assumes that the first parameter passed in PDFACompliance
* constructor (i.e. the convert parameter) is set to 'true'.
* @param filepath - the output file name.
* @param linearized - An optional flag used to specify whether the the resulting
* PDF/A document should be web-optimized (linearized).
*/
- (void)SaveAsFile: (NSString*)file_path linearized:  (BOOL)linearized;
- (void)SaveAs: (NSString*)file_path;
/**
* Serializes the converted PDF/A document to a memory buffer.
* @note This method assumes that the first parameter passed in PDFACompliance
* constructor (i.e. the convert parameter) is set to 'true'.
* @param out_buf a pointer to the buffer containing the serialized version of the
* document. (C++ Note) The buffer is owned by a PDFACompliance class and the client
* doesn't need to do any initialization or cleanup.
* @param out_buf_size the size of the serialized document (i.e. out_buf) in bytes.
* @param linearized - An optional flag used to specify whether the the resulting
* PDF/A document should be web-optimized (linearized).
*/
- (NSData*)SaveAsMemBuf: (BOOL)linearized;
/**
* @return The number of compliance violations.
*/
- (unsigned long)GetErrorCount;
/**
* @return The error identifier.
* @param idx The index in the array of error code identifiers.
* The array is indexed starting from zero.
*
* @exception throws an Exception if the index is outside the array bounds.
*/
- (ErrorCode)GetError: (unsigned long)idx;
/**
* @return The number of object references associated with a given error.
* @param id error code identifier (obtained using GetError() method).
*/
- (unsigned long)GetRefObjCount: (ErrorCode)id;
/**
* @return A specific object reference associated with a given error type.
* The return value is a PDF object identifier (i.e. object number for
* 'pdftron.SDF.Obj)) for the that is associated with the error.
*
* @param id error code identifier (obtained using GetError() method).
* @param err_idx The index in the array of object references.
* The array is indexed starting from zero.
*
* @exception throws an Exception if the index is outside the array bounds.
*/
- (unsigned long)GetRefObj: (ErrorCode)id obj_idx:  (unsigned long)obj_idx;
/**
* @param id error code identifier (obtained using GetError() method).
* @return A descriptive error message for the given error identifier.
*/
+ (NSString *)GetPDFAErrorMessage: (ErrorCode)id;


- (id)initWithConvert: (BOOL)convert file_path:  (NSString*)file_path password:  (NSString *)password conf:  (Conformance)conf exceptions:  (int)exceptions num_exceptions:  (int)num_exceptions max_ref_objs:  (int)max_ref_objs;


@end


/**
* An application or plug-in extension that processes logical structure can attach
* additional information, called attributes, to any structure element.
* The attribute information is held in one or more attribute objects associated
* with the structure element. An attribute object is a dictionary or stream
* that includes an entry identifying the application or plug-in that owns the
* attribute information. Other entries represent the attributes: the keys are
* attribute names, and values are the corresponding attribute values.
*/
@interface AttrObj : NSObject
{


}





/**
* @return The name of the application or plug-in extension owning the
* attribute data.
*/
- (NSString *)GetOwner;
/**
* @return Pointer to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;
- (id)initWithDict: (Obj*)dict;

@end


/**
*/
@interface ClassMap : NSObject
{


}





/**
* @return true if this is a valid (non-null) ClassMap, false otherwise.
* If the function returns false the underlying SDF/Cos object is null or is
* not valid and the ClassMap object should be treated as a null object.
*/
- (BOOL)IsValid;
/**
* Returns the ClassMap dictionary.
*
* @return the object to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;
- (id)initWithDict: (Obj*)dict;

@end


/**
* Content items are graphical objects that exist in the document independently
* of the structure tree but are associated with structure elements.
*
* Content items are leaf nodes of the structure tree.
*/
@interface ContentItem : NSObject
{


}





/**
* Copy constructor and assignment operator.
*/
- (id)initWithArg0: (ContentItem*)arg0;
/**
* @return the content item type.
*/
- (ContentItemType)GetType;
/**
* Find the parent structure element.
*/
- (SElement*)GetParent;
/**
* The page on which the marked content is drawn, whether directly as part of
* page content or indirectly by being in a Form XObject or annotation drawn
* on that page.
*/
- (Page*)GetPage;
/**
* @return Pointer to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;
/**
* @return mcid (marked-content identifier).
*
* @note this method only applies to content items with types e_MCR or e_MCID.
*/
- (int)GetMCID;
/**
* @return The stream object that contains the marked-content sequence.
* The function will return a non-NULL object only if the marked-content
* sequence resides in a content stream other than the content stream for the
* page (e.g. in a form XObject).
*
* @note this method only applies to content items with type e_MCR.
*/
- (Obj*)GetContainingStm;
/**
* @return NULL or the PDF object owning the stream returned by
* GetContainingStm() (e.g. the annotation to which an appearance stream
* belongs).
*
* @note this method only applies to content items with type e_MCR.
*/
- (Obj*)GetStmOwner;
/**
* @return The referenced object.
* @note this method only applies to content items with type e_OBJR.
*/
- (Obj*)GetRefObj;


@end


/**
* RoleMap is a dictionary that maps the names of structure types used in the
* document to their approximate equivalents in the set of standard structure
* types.
*/
@interface RoleMap : NSObject
{


}





/**
* Initialize a RoleMap using an existing low-level Cos/SDF role map dictionary.
*
* @param dict - a low-level (SDF/Cos) RoleMap dictionary.
*
* @note This constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithDict: (Obj*)dict;
/**
* @return true if this is a valid (non-null) RoleMap, false otherwise.
* If the function returns false the underlying SDF/Cos object is null or is
* not valid and the RoleMap should be treated as NULL object.
*/
- (BOOL)IsValid;
/**
* @return The direct mapping of given StructElement type, or NULL
* if such mapping is not defined.
*
* @param structural element type
*/
- (NSString *)GetDirectMap: (NSString *)type;
/**
* Returns the RoleMap dictionary.
* @return the object to the underlying SDF/Cos dictionary.
*/
- (Obj*)GetSDFObj;


@end


/**
* STree is the root of the structure tree, which is a central repository
* for information related to a PDF document's logical structure. There is at most
* one structure tree in each document.
*/
@interface STree : NSObject
{


}





/**
* Initialize a STree using an existing low-level Cos/SDF object.
*
* @param struct_dict - a low-level (SDF/Cos) dictionary representing the .
*
* @note This constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithStruct_dict: (Obj*)struct_dict;
/**
* Create a structure tree if it is missing, else return the existing
* structure tree
*
* @return structure tree of the document
*/
+ (STree*)Create: (PDFDoc*)doc;
/**
* Inserts the specified kid element after the given position as a kid of
* the specified structure tree root.
*
* @param insert_before The position after which the kid is inserted. If
* element currently has no kids, insert_before is ignored.
*/
- (void)Insert: (SElement*)kid insert_before:  (int)insert_before;
/**
* @return true if this is a valid STree object, false otherwise.
*/
- (BOOL)IsValid;
/**
* @return The number of kids of the structure tree root.
*/
- (int)GetNumKids;
/**
* @return The kid at an array index in the structure tree root.
* @param index The index of the kid to obtain.
*/
- (SElement*)GetKid: (int)index;
/**
* @return the element associated with the given ID.
*
* @param id_buf A pointer to a buffer containing the ID to search for.
* @param id_buf_sz The number of characters in id_buf.
*/
- (SElement*)GetElement: (NSString *)id_buf id_buf_sz:  (int)id_buf_sz;
/**
* @return the RoleMap object from the structure tree root.
*/
- (RoleMap*)GetRoleMap;
/**
* @return the ClassMap object from the structure tree root.
*/
- (ClassMap*)GetClassMap;
/**
* @return Pointer to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;


@end


/**
* SElement represents PDF structural elements, which are nodes in a tree
* structure, defining a PDF document's logical structure.
*
* Unlike the StructTree, SElement can have two different kinds
* of children: another SElement or a ContentItem (which can be marked
* content (MC), or a PDF object reference (OBJR)).
*/
@interface SElement : NSObject
{


}





/**
* Creates a new SElement.
*/
+ (SElement*)Create: (PDFDoc*)doc struct_type:  (NSString *)struct_type;
/**
* Inserts the specified kid SElement into this element.
*
* @param insert_before The position after which the kid is inserted. If
* element currently has no kids, insert_before is ignored.
*/
- (void)Insert: (SElement*)kid insert_before:  (int)insert_before;
/**
* @param insert_before The position after which the kid is inserted. If
* element currently has no kids, insert_before is ignored.
*/
- (int)CreateContentItem: (PDFDoc*)doc page:  (Page*)page insert_before:  (int)insert_before;
/**
* @return true if this is a valid structure element object, false otherwise.
*/
- (BOOL)IsValid;
/**
* @return The element's structural element type. The type corresponds to
* the 'S' (i.e. subtype) key in the structure element dictionary.
*
* The type identifies the nature of the structure element and its role
* within the document (such as a chapter, paragraph, or footnote).
*/
- (NSString *)GetType;
/**
* @return The number of direct kids.
*/
- (int)GetNumKids;
/**
* @return true if the kid at a given array index is a content item,
* false otherwise.
* @param index The index of the kid type to obtain.
*
* To retrieve a content item at a given array index use GetAsContentItem(index),
* otherwise use GetAsStructElem(index)
*/
- (BOOL)IsContentItem: (int)index;
/**
* @return The kid at a given array index assuming that the kid is a ContentItem.
* @note use IsContentItem(index) prior to calling this method to make sure that
* the kid is indeed a ContentItem.
* @param index The index of the kid to obtain.
*/
- (ContentItem*)GetAsContentItem: (int)index;
/**
* @return The kid at a given array index assuming that the kid is a SElement.
* @note use IsContentItem(index) prior to calling this method to make sure that
* the kid is not a ContentItem and is another SElement.
* @param index The index of the kid to obtain.
*/
- (SElement*)GetAsStructElem: (int)index;
/**
* @return The immediate ancestor element of the specified element in
* the structure tree.
*
* @note If the element's parent is the structure tree root, the returned
* SElement will be not valid (i.e. element.IsValid() -> false) and the
* underlying SDF/Cos object will be NULL.
*/
- (SElement*)GetParent;
/**
* @return The structure tree root of the document that directly or
* indirectly contains this element.
*/
- (STree*)GetStructTreeRoot;
/**
* @return if this SElement has title.
*
* The title of the structure element, a text string representing it in
* human-readable form.
*/
- (BOOL)HasTitle;
/**
* @return The title of this structure element.
*/
- (NSString*)GetTitle;
/**
* @return the ID of an element, or NULL if the ID is not defined.
*/
- (Obj*)GetID;
/**
* @return if this structure element defines ActualText.
*
* ActualText is an exact replacement for the structure element and its children.
* This replacement text is useful when extracting the document's contents in
* support of accessibility to users with disabilities or for other purposes.
*/
- (BOOL)HasActualText;
/**
* @return The ActualText associated with this element.
*
* @note The ActualText can be defined as an empty string. To differentiate
* between an ActualText string of zero length and no ActualText being defined,
* use HasActualText().
*/
- (NSString*)GetActualText;
/**
* @return if this structure element defines Alt text.
*
* Alt text is an alternate description of the structure element and
* its children in human-readable form, which is useful when extracting
* the documents contents in support of accessibility.
*/
- (BOOL)HasAlt;
/**
* @return The alternate text associated with this element.
*
* @note The Alt text can be defined as an empty string. To differentiate
* between an Alt text string of zero length and no Alt text being defined,
* use HasAlt().
*/
- (NSString*)GetAlt;
/**
* @return Pointer to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;
- (id)initWithDict: (Obj*)dict;

@end


/**
* A %PDF document may optionally display a document outline on the screen, allowing
* the user to navigate interactively from one part of the document to another.
* The outline consists of a tree-structured hierarchy of Bookmarks (sometimes
* called outline items), which serve as a 'visual table of contents' to display the
* documents structure to the user.
*
* Each Bookmark has a title that appears on screen, and an Action that specifies
* what happens when a user clicks on the Bookmark. The typical action for a
* user-created Bookmark is to move to another location in the current document,
* although any action (see PDF::Action) can be specified.
*
* Bookmark is a utility class used to simplify work with %PDF bookmarks (or
* outlines; see section 8.2.2 'Document Outline' in %PDF Reference Manual for
* more details).
*/
@interface Bookmark : NSObject
{


}





/**
* Creates a new valid Bookmark with given title in the
* specified document.
*
* @param in_doc The document in which a Bookmark is to be created.
* @param in_title The title string value of the new Bookmark.
*
* @return The new Bookmark.
*
* @note The new Bookmark is not linked to the outline tree.
* Use AddChild()/AddNext()/AddPrev() methods in order to link the Bookmark
* to the outline tree
*/
+ (Bookmark*)Create: (PDFDoc*)in_doc in_title:  (NSString*)in_title;	/**
* A constructor. Creates a null (non-valid) bookmark.
*/
- (id)init;
/**
* A constructor. Creates a Bookmark and initialize it using given Cos/SDF object.
*
* @param in_bookmark_dict Pointer to the Cos/SDF object (outline item dictionary).
*
* @return The new Bookmark.
*
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithIn_bookmark_dict: (Obj*)in_bookmark_dict;

/**
* Indicates whether the Bookmark is valid (non-null).
*
* @return True if this is a valid (non-null) Bookmark; otherwise false.
*
* @note If this method returns false the underlying SDF/Cos object is null and
* the Bookmark object should be treated as null as well.
*/
- (BOOL)IsValid;
/**
* Indicates whether the Bookmark has children.
*
* @return True if the Bookmark has children; otherwise false.
*/
- (BOOL)HasChildren;
/**
* Returns the Bookmark's next (right) sibling.
*
* @return the Bookmarks next (right) sibling.
*/
- (Bookmark*)GetNext;
/**
* Returns the Bookmark's previous (left) sibling.
*
* @return The Bookmarks previous (left) sibling.
*/
- (Bookmark*)GetPrev;
/**
* Returns the Bookmark's first child.
*
* @return The Bookmarks first child.
*/
- (Bookmark*)GetFirstChild;
/**
* Returns the Bookmark's last child.
*
* @return The Bookmarks last child.
*/
- (Bookmark*)GetLastChild;
/**
* Returns the Bookmark's parent Bookmark.
*
* @return The Bookmarks parent Bookmark.
*/
- (Bookmark*)GetParent;
/**
* Returns the Bookmark specified by the given title string.
*
* @param in_title The title string value of the Bookmark to find.
*
* @return A Bookmark matching the title string value specified.
*/
- (Bookmark*)Find: (NSString*)in_title;
/**
* Adds a new Bookmark as the new last child of this Bookmark.
*
* @param in_title The title string value of the new Bookmark.
*
* @return The newly created child Bookmark.
*
* @note If this Bookmark previously had no children, it will be open
* after the child is added.
*/
- (Bookmark*)AddChildWithTitle: (NSString*)in_title;
/**
* Adds the specified Bookmark as the new last child of this Bookmark.
*
* @param in_bookmark The Bookmark object to be added as a last child of this Bookmark.
*
* @note Parameter in_bookmark must not be linked to a bookmark tree.
* @note If this Bookmark previously had no children, it will be open
* after the child is added.
*/
- (Bookmark*)AddChildWithBookmark: (Bookmark*)in_bookmark;
/**
* Adds a new Bookmark to the tree containing this Bookmark, as the
* new right sibling.
*
* @param in_title The title string value of the new Bookmark.
*
* @return The newly created sibling Bookmark.
*/
- (Bookmark*)AddNextWithTitle: (NSString*)in_title;
/**
* Adds the specified Bookmark as the new right sibling to this Bookmark,
* adjusting the tree containing this Bookmark appropriately.
*
* @param in_bookmark The Bookmark object to be added to this Bookmark.
*
* @note Parameter in_bookmark must not be linked to a bookmark tree.
*/
- (void)AddNextWithBookmark: (Bookmark*)in_bookmark;
/**
* Adds a new Bookmark to the tree containing this Bookmark, as the
* new left sibling.
*
* @param in_title The title string value of the new Bookmark.
*
* @return The newly created sibling Bookmark.
*/
- (Bookmark*)AddPrevWithTitle: (NSString*)in_title;
/**
* Adds the specified Bookmark as the new left sibling to this Bookmark,
* adjusting the tree containing this Bookmark appropriately.
*
* @param in_bookmark The Bookmark object to be added to this Bookmark.
*
* @note Parameter in_bookmark must not be linked to a bookmark tree.
*/
- (void)AddPrevWithBookmark: (Bookmark*)in_bookmark;
/**
* Removes the Bookmark's subtree from the bookmark tree containing it.
*/
- (void)Delete;
/**
* Unlinks this Bookmark from the bookmark tree that contains it, and
* adjusts the tree appropriately.
*
* @note After the bookmark is unlinked is can be moved to another place
* in the bookmark tree located in the same document.
*/
- (void)Unlink;
/**
* Returns the indentation level of the Bookmark in its containing tree.
*
* @return The indentation level of the Bookmark in its containing tree.
*
* @note The root level has an indentation level of zero.
*/
- (int)GetIndent;
/**
* Indicates whether the Bookmark is open.
*
* @return True if this Bookmark is open; otherwise false.
*
* @note An open Bookmark shows all its children.
*/
- (BOOL)IsOpen;
/**
* Opens or closes the Bookmark.
*
* @param in_open Boolean value that contains the status.
* If true, the Bookmark is opened. Otherwise the Bookmark is closed.
*
* @note An opened Bookmark shows its children, while a closed Bookmark does not.
*/
- (void)SetOpen: (BOOL)in_open;
/**
* Returns the number of opened bookmarks in this subtree.
*
* @return The number of opened bookmarks in this subtree (not including
* this Bookmark). If the item is closed, a negative integer whose
* absolute value specifies how many descendants would appear if the
* item were reopened.
*/
- (int)GetOpenCount;
/**
* Returns the Bookmark's title string.
*
* @return The Bookmarks title string).
*/
- (NSString*)GetTitle;
/**
* Returns the Bookmark's title string object.
* @return The Bookmark's title string object.
*/
- (Obj*)GetTitleObj;
/**
* Sets the Bookmarks title string.
*
* @param title The new title string for the bookmark.
*/
- (void)SetTitle: (NSString*)title;
/**
* Returns the Bookmark's action.
*
* @return The Bookmarks action.
*/
- (Action*)GetAction;
/**
* Sets the Bookmarks action.
*
* @param in_action The new Action for the Bookmark.
*/
- (void)SetAction: (Action*)in_action;
/**
* Removes the Bookmarks action.
*/
- (void)RemoveAction;
/**
* Returns the Bookmark's flags.
*
* @return The flags of the Bookmark object.
* Bit 1 (least-significant bit) indicates italic font whereas
* bit 2 indicates bold font.
* Therefore, 0 indicates normal, 1 is italic, 2 is bold, and 3 is bold-italic.
*/
- (int)GetFlags;
/**
* Sets the Bookmark's flags.
*
* @param in_flags The new bookmark flags.
* Bit 1 (the least-significant bit) indicates italic font whereas
* bit 2 indicates bold font.
* Therefore, 0 indicates normal, 1 is italic, 2 is bold, and 3 is bold-italic.
*/
- (void)SetFlags: (int)in_flags;
/**
* Returns the Bookmark's RGB color value.
*
* @param out_r Reference to a variable that receives the red component of the color.
* @param out_g Reference to a variable that receives the green component of the color.
* @param out_b Reference to a variable that receives the blue component of the color.
*
* @note The three numbers  \a out_r, \a out_g, and \a out_b are in the range 0.0 to 1.0,
* representing the components in the DeviceRGB color space of the color
* to be used for the Bookmarks text.
*
* <b>Example:</b>
* \code
*   double red, green, blue;
*   bookmark.GetColor(red, green, blue);
* \endcode
*/
- (NSMutableArray*)GetColor;
/**
* Sets the Bookmark's color value.
*
* @param in_r The red component of the color.
* @param in_g The green component of the color.
* @param in_b The blue component of the color.
*
* @note The three numbers \a in_r, \a in_g, and \a in_b are in the range 0.0 to 1.0, representing
* the components in the DeviceRGB color space of the color to be used
* for the Bookmark's text.
* Default color value is black, [0.0 0.0 0.0].
*/
- (void)SetColor: (double)in_r in_g:  (double)in_g in_b:  (double)in_b;
/**
* Returns the underlying SDF/Cos object.
*
* @return The underlying SDF/Cos object.
*
* @note A null (non-valid) bookmark returns a null object.
*/
- (Obj*)GetSDFObj;



@end


/**
* ContentReplacer is a utility class for replacing content (text and images)
* in existing PDF (template) documents.
*
* Users can replace content in a PDF page using the following operations:
* - Replace an image that exists in a target rectangle with a replacement image.
* - Replace text that exists in a target rectangle with replacement text.
* - Replace all instances of a specially marked string with replacement string.
*
* The following code replaces an image in a target region. This code also
* replaces the text "[NAME]" and "[JOB_TITLE]" with "John Smith"
* and "Software Developer" respectively. Notice the square braces ('[' and ']') on
* the target strings in the original PDFDoc. These square braces are not included in
* the actual function calls below, as they're implicitly added.
*
* @code
* PDFDoc doc("../../TestFiles/BusinessCardTemplate.pdf");
* doc.InitSecurityHandler();
* ContentReplacer replacer;
* Page page = doc.GetPage(1);
* Image img = Image::Create(doc, "../../TestFiles/peppers.jpg");
* replacer.AddImage(page.GetMediaBox(), img.GetSDFObj());
* replacer.AddString("NAME", "John Smith");
* replacer.AddString("JOB_TITLE", "Software Developer");
* replacer.Process(page);
* @endcode
*/
@interface ContentReplacer : NSObject
{


}





/**
* Create a new ContentReplacer object, to which replacement rules will be added.
* The same object can be used to 'Process' multiple pages.
*/
- (id)init;
/**
* Replace the image that best fits into 'target_region' with 'replacement_image'.
*
* @param target_region - The rectangle defining the area in which an image
* that best fits the rectangle will be replaced by 'replacement_image'.
*
* @param replacement_image - The 'SDF.Obj' of a 'PDF.Image' object.
*
* @remarks The best fit is the image that closest matches 'target_region'. For example if
* there are two images on the page, one taking up all of the page, and the other
* smaller, and the smaller one has similar dimensions and position of
* 'target_region', then the smaller image would be replaced, not the larger.
* Furthermore, if 'target_region' encloses multiple images, then only the image
* with the largest area in 'target_region' will be replaced.
*/
- (void)AddImage: (PDFRect*)target_region replacement_image:  (Obj*)replacement_image;
/**
* All text inside 'target_region' will be deleted and replaced with 'replacement_text'.
*
* @param target_region - The rectangle defining the area in which all text will
* be replaced by 'replacement_text'.
*
* @param replacement_text - The new text that will replace the existing text
* in 'target_region'.
*
* @remarks The 'replacement_text' will be styled in the same font/color/style that is used
* by the original text. If there are multiple font styles, the most prevalent style will
* be used. Also, the 'replacement_text' will wrap within the 'target_region',
* but if it is too long, the overflow text will not be visible, and no surrounding
* content will be affected.
*/
- (void)AddText: (PDFRect*)target_region replacement_text:  (NSString*)replacement_text;
/**
* Any text of the form "[template_text]" will be replaced by "replacement_text".
*
* @param template_text - The text to remove.
*
* @param replacement_text - The new text that will appear in place of 'template_text'.
*
* @remarks Only text wrapped in '[' and ']' will be checked, and if it matches 'template_text',
* then 'template_text' and the surrounding square braces will be replaced
* by 'replacement_text'. For example AddString("TITLE", "Doctor") will replace any
* text consisting of "[TITLE]" with "Doctor".
*/
- (void)AddString: (NSString*)template_text replacement_text:  (NSString*)replacement_text;
/**
* Apply the replacement instructions to the target page. Subsequent calls
* to 'Process' can be made on other pages, and it will apply the same rules.
*
* @param page - The page to apply the content replacement instructions to.
*/
- (void)Process: (Page*)page;



@end


/**
* Converter is a utility class used to convert documents and files to PDF.
* Conversion of XPS, EMF and image files to PDF documents is performed internally.
* Other document formats are converted via native application and printing.
*
* @code
* using namespace pdftron;
* using namespace PDF;
* PDFDoc pdfdoc;
*
* Convert::FromXps(pdfdoc, input_path + "simple-xps.xps" );
* Convert::FromEmf(pdfdoc, input_path + "simple-emf.emf" );
* Convert::ToPdf(pdfdoc, input_path + test docx file.docx );
*
* // Save the PDF document
* UString outputFile = output_path + "ConverterTest.pdf";
* pdfdoc.Save(outputFile, SDF::SDFDoc::e_remove_unused, NULL);
* @endcode
*
* The PDFTron PDFNet printer needs to be installed to convert document formats.
* On Windows installation of printer drivers requires administrator UAC, manifests
* have been added to the Convert samples (C++, C# and Visual Basic).
*
* To install the printer the process must be running as administrator.  Execute:
*
* @code
* Convert::Printer::Install();
* @endcode
*
* Installation can take a few seconds, so it is recommended that you install the printer
* once as part of your deployment process.  Duplicated installations will be quick since
* the presence of the printer is checked before installation is attempted.  The printer
* is a virtual XPS printer supported on Vista and Windows 7, and on Windows XP with the
* XPS Essentials Pack.
*
* There is no need to uninstall the printer after conversions, it can be left installed
* for later access. To uninstall the printer the process must be running as administrator.
* Execute:
*
* @code
* Convert::Printer::Uninstall();
* @endcode
*/
@interface Convert : NSObject
{


}





/**
* Convert the specified XPS document to PDF and append converted pages
* to the specified PDF document.
*
* @param in_pdfdoc the PDFDoc to append to
*
* @param in_filename the path to the XPS document to convert
*
*/
+ (void)FromXpsWithFilename: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
/**
* Convert the specified XPS document contained in memory to PDF
* and append converted pages to the specified PDF document.
*
* @param in_pdfdoc the PDFDoc to append to
*
* @param buf the buffer containing the xps document
*
* @param buf_sz the size of the buffer
*
*/
+ (void)FromXpsWithBuffer: (PDFDoc*)in_pdfdoc buf:  (NSString *)buf buf_sz:  (unsigned long)buf_sz;
/**
* Convert the specified EMF to PDF and append converted pages to
* to the specified PDF document.  EMF will be fitted to the page.
*
* @param in_pdfdoc the PDFDoc to append to
*
* @param in_filename the path to the EMF document to convert
*
* @note This method is available only on Windows platforms.
*/
+ (void)FromEmf: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
/**
* Convert the PDFDoc to EMF and save to the specified path
*
* @param in_pdfdoc the PDFDoc to convert to EMF
*
* @param in_filename the path to the EMF files to create, one file per page
*
* @note This method is available only on Windows platforms.
*/
+ (void)ToEmfWithPDFDoc: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
/**
* Convert the Page to EMF and save to the specified path
*
* @param in_page the Page to convert to EMF
*
* @param in_filename the path to the EMF file to create
*
* @note This method is available only on Windows platforms.
*/
+ (void)ToEmfWithPage: (Page*)in_page in_filename:  (NSString*)in_filename;
/**
* Convert the PDFDoc to SVG and save to the specified path
*
* @param in_pdfdoc the PDFDoc to convert to SVG
*
* @param in_filename the path to the SVG files to create, one file per page
*
* @param in_options the conversion options
*/
+ (void)ToSvgWithPDFDoc: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename in_options:  (SVGOutputOptions*)in_options;
/**
* Convert the Page to SVG and save to the specified path
*
* @param in_page the Page to convert to SVG
*
* @param in_filename the path to the SVG file to create
*
* @param in_options the conversion options
*/
+ (void)ToSvg: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
+ (void)ToSvgWithPage: (Page*)in_page in_filename:  (NSString*)in_filename in_options:  (SVGOutputOptions*)in_options;
/**
* Convert the PDFDoc to XPS and save to the specified path
*
* @param in_pdfdoc the PDFDoc to convert to XPS
*
* @param in_filename the path to the document to create
*
* @param options the conversion options
*
* @see XPSOutputOptions
*
*/
+ (void)ToXpsWithPDFDoc: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename options:  (XPSOutputOptions*)options;
/**
* Convert the input file to XPS format and save to the specified path
*
* @param in_inputFilename the file to convert to XPS
*
* @param in_outputFilename the path to the XPS file to create
*
* @param options the conversion options
*
* @see XPSOutputOptions
*
* @see ToPdf()
*
* @note: Requires the Convert::Printer class for all file formats
* that ToPdf also requires.
*/
+ (void)ToXps: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
+ (void)ToXpsWithFilename: (NSString*)in_inputFilename in_outputFilename:  (NSString*)in_outputFilename options:  (XPSOutputOptions*)options;
/**
* Convert the input file to XOD format and save to the specified path
*
* @param in_inputFilename the file to convert to XOD
*
* @param in_outputFilename the path to the XOD file to create
*
* @param options the conversion options
*
* @see XODOutputOptions
*
* @see ToPdf()
*
* @note: Requires the Convert::Printer class for all file formats
* that ToPdf also requires.
*/
+ (void)ToXodWithFilename: (NSString*)in_filename out_filename:  (NSString*)out_filename options:  (XODOutputOptions*)options;
/**
* Convert the input file to XOD format and save to the specified path
*
* @param in_pdfdoc the PDFDoc to convert to XOD
*
* @param in_outputFilename the path to the XOD file to create
*
* @param options the conversion options
*
* @see XODOutputOptions
*
* @see ToPdf()
*
*/
+ (void)ToXod: (NSString*)in_filename out_filename:  (NSString*)out_filename;
+ (void)ToXodWithPDFDoc: (PDFDoc*)in_pdfdoc out_filename:  (NSString*)out_filename options:  (XODOutputOptions*)options;
/**
* Convert a file to HTML and save to the specified path
*
* @param in_inputFilename the file to convert to HTML
*
* @param out_path the path to where generated content will be stored
*
* @param options the conversion options
*
* @see HTMLOutputOptions
*
* @see ToPdf()
*
*/
+ (void)ToHtmlWithFilename: (NSString*)in_filename out_path:  (NSString*)out_path options:  (HTMLOutputOptions*)options;
/**
* Convert the PDF to HTML and save to the specified path
*
* @param in_pdfdoc the PDF doc to convert to HTML
*
* @param out_path the path to where generated content will be stored
*
* @param options the conversion options
*
* @see HTMLOutputOptions
*
* @see ToPdf()
*
*/
+ (void)ToHtml: (NSString*)in_filename out_path:  (NSString*)out_path;
+ (void)ToHtmlWithPDFDoc: (PDFDoc*)in_pdfdoc out_path:  (NSString*)out_path options:  (HTMLOutputOptions*)options;
/**
* Convert a file to EPUB format and save to the specified path
*
* @param in_inputFilename the file to convert to EPUB
*
* @param out_path the path to where generated content will be stored
*
* @param options the conversion options
*
* @see HTMLOutputOptions
*
* @see EPUBOutputOptions
*
* @see ToPdf()
*
*/
+ (void)ToEpubWithFilename: (NSString*)in_filename out_path:  (NSString*)out_path html_options:  (HTMLOutputOptions*)html_options epub_options:  (EPUBOutputOptions*)epub_options;
/**
* Convert the PDFDoc to EPUB format and save to the specified path
*
* @param in_pdfdoc the PDFDoc to convert to EPUB
*
* @param out_path the path to where generated content will be stored
*
* @param options the conversion options
*
* @see HTMLOutputOptions
*
* @see EPUBOutputOptions
*
* @see ToPdf()
*
*/
+ (void)ToEpub: (NSString*)in_filename out_path:  (NSString*)out_path html_options:  (HTMLOutputOptions*)html_options;
+ (void)ToEpubWithPDFDoc: (PDFDoc*)in_pdfdoc out_path:  (NSString*)out_path html_options:  (HTMLOutputOptions*)html_options epub_options:  (EPUBOutputOptions*)epub_options;
/**
* Generate a stream that incrementally converts the input file to XOD format.
*
* @param in_inputFilename the file to convert to XOD
*
* @param in_outputFilename the path to the XOD file to create
*
* @param options the conversion options
*
* @return A filter from which the file can be read incrementally.
*
* @see XODOutputOptions
*
* @see ToPdf()
*
* @note: Requires the Convert::Printer class for all file formats
* that ToPdf also requires.
*/
+ (Filter*)ToXodWithFilenameToStream: (NSString*)in_filename options:  (XODOutputOptions*)options;
/**
* Generate a stream that incrementally converts the input file to XOD format.
*
* @param in_pdfdoc the PDFDoc to convert to XOD
*
* @param in_outputFilename the path to the XOD file to create
*
* @param options the conversion options
*
* @return A filter from which the file can be read incrementally.
*
* @see XODOutputOptions
*
* @see ToPdf()
*
*/
+ (Filter*)ToXodWithPDFDocToStream: (PDFDoc*)in_pdfdoc options:  (XODOutputOptions*)options;
/**
* Convert the file or document to PDF and append to the specified PDF document
*
* @param in_pdfdoc the PDFDoc to append the converted document to. The
* PDFDoc can then be converted to XPS, EMF or SVG using the other functions
* in this class.
*
* @param in_filename the path to the document to be converted to pdf
*
* @note Internally formats include BMP, EMF, JPEG, PNG, TIF, XPS.
*
* @note Formats that require external applications for conversion use the
* Convert::Printer class and the PDFNet printer to be installed. This is
* only supported on Windows platforms.  Document formats in this category
* include RTF(MS Word or Wordpad), TXT (Notepad or Wordpad), DOC and DOCX
* (MS Word), PPT and PPTX (MS PowerPoint), XLS and XLSX (MS Excel),
* OpenOffice documents, HTML and MHT (Internet Explorer), PUB (MS Publisher),
* MSG (MS Outlook).
*/
+ (void)ToPdf: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
/**
* Utility function to determine if ToPdf or ToXps will require the PDFNet
* printer to convert a specific external file to PDF.
*
* @param in_filename the path to the document to be checked
*
* @return true if ToPdf requires the printer to convert the file, false
* otherwise.
*
* @note Current implementation looks only at the file extension not
* file contents. If the file extension is missing, false will be returned
*/
+ (BOOL)RequiresPrinter: (NSString*)in_filename;


@end


/**
* Contains the information required to draw the path. Contains an array of
* PathSegmentType Operators and corresponding path data Points. A point may
* be on or off (off points are control points). The meaning of a point
* depends on associated id (or segment type) in the path segment type array.
*/
@interface PathData : NSObject
{


}





/**
* Overwrite the existing operators.
*
* @param operators - The new operators to use.
*/
- (void)SetOperators: (NSData*)operators;
/**
* Overwrite the existing data points.
*
* @param points - The new data points to use.
*/
- (void)SetPoints: (NSMutableArray*)points;
/**
* Get the current operators.
*
* @return The existing PathSegmentType operators.
*/
- (NSData*)GetOperators;
/**
* Get the current data points.
*
* @return The existing data points.
*/
- (NSMutableArray*)GetPoints;
/**
* If PathData was acquired from Font::GetGlyphPath then is
* method will indicate if this is an 'undefined character code'.
*
* @return True if this is valid, otherwise false.
*
* @note See Font::GetGlyphPath for more information regarding
* what an 'undefined character code' means.
*/
- (BOOL)IsDefined;
- (id)init;

@end


/**
* A font that is used to draw text on a page. It corresponds to a Font Resource
* in a PDF file. More than one page may reference the same Font object.
* A Font has a number of attributes, including an array of widths, the character
* encoding, and the font's resource name.
*
* PDF document can contain several different types of fonts and Font class
* represents a single, flat interface around all PDF font types.
*
* There are two main classes of fonts in PDF: simple and composite fonts.
*
* Simple fonts are Type1, TrueType, and Type3 fonts. All simple fonts have the
* following properties:<BR><BR>
*  - Glyphs in the font are selected by single-byte character codes
*    obtained from a string that is shown by the text-showing operators.
*    Logically, these codes index into a table of 256 glyphs; the mapping
*    from codes to glyphs is called the font's encoding. Each font program
*    has a built-in encoding. Under some circumstances, the encoding can
*    be altered by means described in Section 5.5.5 "Character Encoding" in
*    PDF Reference Manual.<BR><BR>
*
*  - Each glyph has a single set of metrics. Therefore simple fonts support
*    only horizontal writing mode.<BR><BR>
*
* A composite font is one whose glyphs are obtained from a font like object
* called a CIDFont (e.g. CIDType0Font and CIDType0Font). A composite font is
* represented by a font dictionary whose Subtype value is Type0. The Type 0 font
* is known as the root font, while its associated CIDFont is called its descendant.
* CID-keyed fonts provide a convenient and efficient method for defining
* multiple-byte character encodings and fonts with a large number of glyphs.
* These capabilities provide great flexibility for representing text in writing
* systems for languages with large character sets, such as Chinese, Japanese,
* and Korean (CJK).
*/
@interface Font : NSObject
{


}





/**
* Create a PDF::Font object from an existing SDF font object that is embedded
* in the document. If font_dict is null, a non valid font is created.
*/
- (id)initWithFont_dict: (Obj*)font_dict;
/**
* Create a PDF::Font object for the given standard (also known as base 14 font)
*/
+ (Font*)Create: (SDFDoc*)doc type:  (StandardType1Font)type embed:  (BOOL)embed;
/**
* Embed an external TrueType font in the document as a Simple font.
*
* @note glyphs in the Simple font are selected by single-byte character codes.
* If you want to work with multi-byte character codes (e.g. UTF16) you need to
* create a CID font.
*
* @param doc Document in which the external font should be embedded.
* @param font_path Path to the external font file.
* @param embed A boolean indicating whether the font should be embedded or
* not. For accurate font reproduction set the embed flag to 'true'.
* @param subset A boolean indicating whether the embedded font should
* be subsetted.
*/
+ (Font*)CreateTrueTypeFont: (SDFDoc*)doc font_path:  (NSString*)font_path embed:  (BOOL)embed subset:  (BOOL)subset;
/**
* Embed an external TrueType font in the document as a CID font.
* By default the function selects "Identity-H" encoding that maps 2-byte
* character codes ranging from 0 to 65,535 to the same Unicode value.
* Other predefined encodings are listed in Table 5.15 'Predefined CMap names'
* in PDF Reference Manual.
*
* @param doc - document in which the external font should be embedded.
* @param font_path - path to the external font file.
* @param embed - a boolean indicating whether the font should be embedded or
* not. For accurate font reproduction set the embed flag to 'true'.
* @param subset - a boolean indicating whether the embedded font should
* be subsetted
*/
+ (Font*)CreateCIDTrueTypeFont: (SDFDoc*)doc font_path:  (NSString*)font_path embed:  (BOOL)embed subset:  (BOOL)subset encoding:  (Encoding)encoding;
/**
* Create a new Unicode font based on the description of an existing PDF font.
* @note This method is experimental. For now it is only used in FieldRefresh.cpp.
*/
+ (Font*)CreateFromFont: (SDFDoc*)doc from:  (Font*)from char_set:  (NSString*)char_set;
+ (Font*)CreateFromName: (SDFDoc*)doc name:  (NSString *)name char_set:  (NSString*)char_set;
/**
* Embed an external Type1 font in the document.
*
* @param doc - document in which the external font should be embedded.
* @param font_path - path to the external font file.
* @param embed - a boolean indicating whether the font should be embedded or
* not. For accurate font reproduction set the embed flag to 'true'.
*/
+ (Font*)CreateType1Font: (SDFDoc*)doc font_path:  (NSString*)font_path embed:  (BOOL)embed;
/**
* @return Font Type
*/
- (FontType)GetType;
/**
* @return true for non-CID based fonts such as Type1, TrueType, and Type3
*
* All simple fonts have the following properties:<BR><BR>
*
* - Glyphs in the font are selected by single-byte character codes
*   obtained from a string that is shown by the text-showing operators.
*   Logically, these codes index into a table of 256 glyphs; the mapping
*   from codes to glyphs is called the font's encoding. Each font program
*   has a built-in encoding. Under some circumstances, the encoding can
*   be altered by means described in Section 5.5.5 "Character Encoding" in
*   PDF Reference Manual.<BR><BR>
*
* - Each glyph has a single set of metrics. Therefore simple fonts support
*   only horizontal writing mode.<BR><BR>
*/
- (BOOL)IsSimple;
/**
* @return a SDF/Cos object of this Font.
*/
- (Obj*)GetSDFObj;
/**
* @return a SDF/Cos object representing FontDescriptor or NULL is FontDescriptor
* is not present.
*/
- (Obj*)GetDescriptor;
/**
* @return the name of a font. The behavior depends on the font type;
* for a Type 3 font it gets the value of the Name key in a PDF Font resource.
* For other types it gets the value of the BaseFont key in a PDF font resource.
*/
- (NSString *)GetName;
/**
* @return the face's family name. This is an ASCII string, usually in English,
* which describes the typeface's family (like 'Times New Roman', 'Bodoni', 'Garamond',
* etc). This is a least common denominator used to list fonts.
*/
- (NSString *)GetFamilyName;
/**
* @return true if all glyphs have the same width
*/
- (BOOL)IsFixedWidth;
/**
* @return true if glyphs have serifs
*/
- (BOOL)IsSerif;
/**
* @return true if font contains characters outside the Adobe standard Latin character set.
*/
- (BOOL)IsSymbolic;
/**
* @return true if glyphs have dominant vertical strokes that are slanted.
*/
- (BOOL)IsItalic;
/**
* @return true if font contains no lowercase letters
*/
- (BOOL)IsAllCap;
/**
* @return true if bold glyphs should be painted with extra pixels at very small text sizes.
*/
- (BOOL)IsForceBold;
/**
* @return true if the font uses horizontal writing mode, false for vertical writing mode.
*/
- (BOOL)IsHorizontalMode;
/**
* @return advance width, measured in glyph space units for the glyph
* matching given character code.
*
* @note 1000 glyph units = 1 text space unit
* @note The width returned has NOT been scaled by the font size, text matrix,
*		 nor the CTM.
*
* The function gets the advance width of the font glyph. The advance width
* is the amount by which the current point advances when the glyph is drawn.
* The advance width may not correspond to the visible width of the glyph
* and for this reason, the advance width cannot be used to determine the glyphs'
* bounding boxes.
*/
- (double)GetWidth: (unsigned int)char_code;
/**
* @return the maximal advance width, in font units, for all glyphs in this face.
*/
- (double)GetMaxWidth;
/**
* @return the default width to use for character codes whose widths are
* not specified in a font dictionary's Widths array.
*/
- (double)GetMissingWidth;
/**
* GetCharCodeIterator represents an iterator interface used to traverse
* a list of char codes for which there is a glyph outline in the embedded font.
*/
- (UInt32Iterator*)GetCharCodeIterator;
/**
* The function retrieves the glyph outline for a given character code.
*
* @param char_code character to query
* @param conics2cubics if set to true converts all quadratic Bezier curves to cubic
* Beziers, otherwise no conversion is performed.
* @param An optional matrix used to transform glyph data coordinates. If null/unspecified,
* glyph data points will not be transformed.
*
* @return A PathData object containing the path information.
*
* @note the function can return only the following operators (Element::e_moveto,
* Element::e_lineto, Element::e_cubicto and optionally Element::e_conicto if
* conics2cubics parameter is set to true.
*
* @note This function is not applicable to Type3 font and will throw an exception.
* Use GetType3GlyphStream instead.
*
* @note Check PathData::IsDefined to see if the char_code was mapped to 'undefined character code'.
*/
- (PathData*)GetGlyphPath: (unsigned int)char_code conics2cubics:  (BOOL)conics2cubics transform:  (Matrix2D*)transform;
/**
* Maps the encoding specific 'charcode' to Unicode. Conversion of 'charcode'
* to Unicode can result in up to four Unicode characters.
*
* @param char_code encoding specific 'charcode' that needs to be converted
* to Unicode.
*
* @param out_uni_arr A pointer to an array of Unicode characters where
* the conversion result will be stored.
*
* @param in_uni_sz The number of characters that can be written to out_uni_arr.
* You can assume that the function will never map to more than 10 characters.
*
* @param out_char_num The function will modify this value to return the
* number of Unicode characters written in 'out_uni_arr' array.
*
* @return true if char_code was mapped to Unicode public area or false if
* the char_code was mapped to Unicode private area.
*
* A char_code is mapped to Unicode private area when the information required
* for proper mapping is missing in PDF document (e.g. a predefined encoding
* or ToUnicode CMap).
*
* @note This function is not applicable to CIDFonts (e_CIDType0 and e_CIDType2)
* and will throw an exception if called.
*/
- (NSString*)MapToUnicode: (unsigned int)char_code;
/**
* Tests whether or not the specified font is stored as a font file in a stream
* embedded in the PDF file.
*
* @return true if the font is embedded in the file, false otherwise.
*/
- (BOOL)IsEmbedded;
/**
* @return the PostScript font name for the embedded font. If the embedded font
* name is not available the function returns the empty string .
*/
- (NSString *)GetEmbeddedFontName;
/**
* @return the stream object of the embedded font or NULL if there if the
* font is not embedded.
* @note This function is not applicable to Type3 font and will throw exception.
*/
- (Obj*)GetEmbeddedFont;
/**
* @return the size of decoded buffer containing embedded font data or 0
* if this information is not known in advance.
*
* @note The size of decoded buffer may not be known in advance for all
* fonts and may not be correct.
* @note This function is not applicable to Type3 font and will throw exception.
*/
- (int)GetEmbeddedFontBufSize;
/**
* @return the number of font units per EM square for this face. This is
* typically 2048 for TrueType fonts, 1000 for Type1 fonts
*
* @note Only relevant for scalable formats (such as TrueType and Type1).
*
* @note This function is not applicable to Type3 font and will throw an exception.
* Use GetType3FontMatrix instead.
*/
- (unsigned short)GetUnitsPerEm;
/**
* @return A rectangle expressed in the glyph coordinate system, specifying the
* font bounding box. This is the smallest rectangle enclosing the shape that would
* result if all of the glyphs of the font were placed with their origins coincident
* and then filled.
*/
- (PDFRect*)GetBBox;
/**
* The face's ascender is the vertical distance from the baseline to the topmost
* point of any glyph in the face. This field's value is a positive number, expressed
* in the glyph coordinate system. For all font types except Type 3, the units of
* glyph space are one-thousandth of a unit of text space. Some font designs use
* a value different from 'bbox.yMax'.
*
* @note Only relevant for scalable formats.
*/
- (double)GetAscent;
/**
* The face's descender is the vertical distance from the baseline to the bottommost
* point of any glyph in the face. This field's value is a negative number expressed
* in the glyph coordinate system. For all font types except Type 3, the units of
* glyph space are one-thousandth of a unit of text space. Some font designs use
* a value different from 'bbox.yMin'.
*
* @note Only relevant for scalable formats.
*/
- (double)GetDescent;
/**
* @return Font::e_null if the font is not a standard Type1 font or some
* other StandardType1Font value for a standard Type1 font.
*/
- (int)GetStandardType1FontType;
/**
* @return true if the embedded font is represented as CFF (Compact Font Format).
* @note Only Type1 and Type1C fonts can be represented in CFF format
*/
- (BOOL)IsCFF;
/**
* @return Type3 font matrix, mapping glyph space to text space
* A common practice is to define glyphs in terms of a 1000-unit
* glyph coordinate system, in which case the font matrix is [0.001 0 0 0.001 0 0].
*
* @note Relevant only for a Type3 font.
*/
- (Matrix2D*)GetType3FontMatrix;
/**
* @return a SDF/Cos glyph stream for the given char_code.
* If specified char_code is not found in the CharProcs dictionary the
* function returns NULL.
*
* @note Relevant only for a Type3 font.
*/
- (Obj*)GetType3GlyphStream: (unsigned int)char_code;
/**
* @return vertical advance. vertical advance is a displacement vector for vertical
* writing mode (i.e. writing mode 1); its horizontal component is always 0.
*
* @param char_code character to query for vertical advance
* @param out_pos_vect_x - initialized by the method. horizontal component of the
* position vector defining the position of the vertical writing mode origin
* relative to horizontal writing mode origin.
* @param out_pos_vect_y - initialized by the method. vertical component of the
* position vector defining the position of the vertical writing mode origin
* relative to horizontal writing mode origin.
*
* @note Use this method only for composite fonts with vertical writing mode
* (i.e. if Font.IsHorizontalMode() returns false). The method will return 0 as vertical
* advance for simple fonts or for composite fonts with only horizontal writing mode.
* @note Relevant only for a Type0 font.
*/
- (NSMutableArray*)GetVerticalAdvance: (unsigned int)char_code;
/**
* @return descendant CIDFont.
*
* @note Relevant only for a Type0 font.
*/
- (Font*)GetDescendant;
/**
* @return a CID matching specified charcode.
*
* @note Relevant only for a Type0 font.
*/
- (unsigned int)MapToCID: (unsigned int)char_code;



@end


/**
* Shading is a class that represents a flat interface around all PDF shading types:
*
*  - In Function-based (type 1) shadings, the color at every point in
*    the domain is defined by a specified mathematical function. The function need
*    not be smooth or continuous. This is the most general of the available shading
*    types, and is useful for shadings that cannot be adequately described with any
*    of the other types.
*
*  - Axial shadings (type 2) define a color blend along a line between two points,
*    optionally extended beyond the boundary points by continuing the boundary
*    colors.
*
*  - Radial shadings (type 3) define a color blend that varies between two circles.
*    Shadings of this type are commonly used to depict three-dimensional spheres
*    and cones.
*
*  - Free-form Gouraud-shaded triangle mesh shadings (type 4) and lattice Gouraud
*    shadings (type 5) are commonly used to represent complex colored and shaded
*    three-dimensional shapes. The area to be shaded is defined by a path composed entirely
*    of triangles. The color at each vertex of the triangles is specified, and a technique
*    known as Gouraud interpolation is used to color the interiors. The interpolation
*    functions defining the shading may be linear or nonlinear.
*
*  - Coons patch mesh shadings (type 6) are constructed from one or more color
*    patches, each bounded by four cubic Bzier curves.
*
*    A Coons patch generally has two independent aspects:
*    - Colors are specified for each corner of the unit square, and bilinear
*      interpolation is used to fill in colors over the entire unit square<BR>
*    - Coordinates are mapped from the unit square into a four-sided patch whose
*      sides are not necessarily linear. The mapping is continuous: the corners
*      of the unit square map to corners of the patch and the sides of the unit
*      square map to sides of the patch.
*
*  - Tensor-product patch mesh shadings (type 7) are identical to type 6
*    (Coons mesh), except that they are based on a bicubic tensor-product
*    patch defined by 16 control points, instead of the 12 control points
*    that define a Coons patch. The shading Patterns dictionaries representing
*    the two patch types differ only in the value of the Type entry and
*    in the number of control points specified for each patch in the data stream.
*    Although the Coons patch is more concise and easier to use, the tensor-
*    product patch affords greater control over color mapping.
*/
@interface Shading : NSObject
{


}





/**
* Create a Shading from the given SDF/Cos object listed under /Shading entry
* in the page Resource dictionary. If shading_dict dictionary is null, a non valid Shading
* object is created.
*/
- (id)initWithShading_dict: (Obj*)shading_dict;
/**
* @return The shading type
*/
- (ShadingType)GetType;
/**
* @return the underlying SDF/Cos object
*/
- (Obj*)GetSDFObj;
/**
* @return The color space in which color values are expressed.
* This may be any device, CIE-based, or special color space
* except a Pattern space.
*/
- (ColorSpace*)GetBaseColorSpace;
/**
* @return true if shading has a bounding box, false otherwise.
*/
- (BOOL)HasBBox;
/**
* @return a rectangle giving the left, bottom, right, and top
* coordinates, respectively, of the shadings bounding box. The coordinates
* are interpreted in the shadings target coordinate space. If present, this
* bounding box is applied as a temporary clipping boundary when the shading
* is painted, in addition to the current clipping path and any other clipping
* boundaries in effect at that time.
*
* @note Use HasBBox() method to determine whether the shading has a
* background color.
*/
- (PDFRect*)GetBBox;
/**
* @return true if the shading has a background color or false otherwise.
*/
- (BOOL)HasBackground;
/**
* An color point represented in base color space specifying a single
* background color value. If present, this color is used before
* any painting operation involving the shading, to fill those portions of the
* area to be painted that lie outside the bounds of the shading object itself.
* In the opaque imaging model, the effect is as if the painting operation were
* performed twice: first with the background color and then again with the
* shading.
*
* @note The background color is applied only when the shading is used as part
* of a shading pattern, not when it is painted directly with the sh operator.
*
* @note Use HasBackground() method to determine whether the shading has a
* background color.
*/
- (ColorPt*)GetBackground;
/**
* @return A flag indicating whether to filter the shading function to prevent
* aliasing artifacts. See Table 4.25
*/
- (BOOL)GetAntialias;
/**
* @return a number specifying the limiting value of a parametric variable t.
* The variable is considered to vary linearly between GetParamStart() and
* GetParamEnd() as the color gradient varies between the starting and ending points
* of the axis for Axial shading or circles for Radial shading.
* The variable t becomes the input argument to the color function(s).
* @note the returned value corresponds to the first value in Domain array.
*
* @note for shadings other than Axial or Radial this method throws an exception.
*/
- (double)GetParamStart;
/**
* @return a number specifying the limiting value of a parametric variable t.
* The variable is considered to vary linearly between GetParamStart() and
* GetParamEnd() as the color gradient varies between the starting and ending points
* of the axis for Axial shading or circles for Radial shading.
* The variable t becomes the input argument to the color function(s).
* @note the returned value corresponds to the second value in Domain array.
*
* @note for shadings other than Axial or Radial this method throws an exception.
*/
- (double)GetParamEnd;
/**
* @return a flag specifying whether to extend the shading beyond the starting
* point of the axis for Axial shading or starting circle for Radial shading.
*
* @note for shadings other than Axial or Radial this method throws an exception.
*/
- (BOOL)IsExtendStart;
/**
* @return a flag specifying whether to extend the shading beyond the ending
* point of the axis for Axial shading or ending circle for Radial shading.
*
* @note for shadings other than Axial or Radial this method throws an exception.
*/
- (BOOL)IsExtendEnd;
/**
* @return a color point for the given value of parametric variable t.
*
* @note for shadings other than Axial or Radial this method throws an exception.
*/
- (ColorPt*)GetColorForAxialOrRadial: (double)t;
/**
* @return for Axial shading returns four numbers (out_x0, out_y0, out_x1, out_y1)
* specifying the starting and ending coordinates of the axis, expressed in the
* shadings target coordinate space.
*
* @note for shadings other than Axial this method throws an exception.
*/
- (NSMutableArray*)GetCoordsAxial;
/**
* @return for Radial shading returns six numbers (x0 y0 r0 x1 y1 r1) specifying
* the centers and radii of the starting and ending circles, expressed in the
* shadings target coordinate space. The radii r0 and r1 must both be greater
* than or equal to 0. If one radius is 0, the corresponding circle is treated
* as a point; if both are 0, nothing is painted.
*
* @note for shadings other than Radial this method throws an exception.
*/
- (NSMutableArray*)GetCoordsRadial;
/**
* @return An array of four numbers [xmin xmax ymin ymax] specifying the rectangular
* domain of coordinates over which the color function(s) are defined.
* If the function does not contain /Domain entry the function returns: [0 1 0 1].
*
* @note for shadings other than Function this method throws an exception.
*/
- (NSMutableArray*)GetDomain;
/**
* @return a matrix specifying a mapping from the coordinate space specified
* by the Domain entry into the shadings target coordinate space.
*
* @note for shadings other than Function this method throws an exception.
*/
- (Matrix2D*)GetMatrix;
/**
* @return a color point for the given value of parametric variable (t1, t2).
*
* @note for shadings other than Function this method throws an exception.
*/
- (ColorPt*)GetColorForFunction: (double)t1 t2:  (double)t2;



@end


/**
* Patterns are quite general, and have many uses; for example, they can be used
* to create various graphical textures, such as weaves, brick walls, sunbursts,
* and similar geometrical and chromatic effects.

* Patterns are specified in a special family of color spaces named Pattern, whose
* 'color values' are PatternColor objects instead of the numeric component values
* used with other spaces. Therefore PatternColor is to pattern color space what is
* ColorPt to all other color spaces.
*
* A tiling pattern consists of a small graphical figure called a pattern cell.
* Painting with the pattern replicates the cell at fixed horizontal and vertical
* intervals to fill an area. The effect is as if the figure were painted on the
* surface of a clear glass tile, identical copies of which were then laid down
* in an array covering the area and trimmed to its boundaries. This is called
* tiling the area.
*
* The pattern cell can include graphical elements such as filled areas, text,
* and sampled images. Its shape need not be rectangular, and the spacing of
* tiles can differ from the dimensions of the cell itself.
*
* The order in which individual tiles (instances of the cell) are painted is
* unspecified and unpredictable; it is inadvisable for the figures on adjacent
* tiles to overlap.
*/
@interface PatternColor : NSObject
{


}





/**
* Create a PatternColor from the given SDF/Cos object listed under Pattern entry
* in page Resource dictionary
*/
- (id)initWithPattern: (Obj*)pattern;
/**
* @return The pattern type
*/
- (PatternColorType)GetType;
/**
* @return the underlying SDF/Cos object
*/
- (Obj*)GetSDFObj;
/**
* @return pattern matrix, a transformation matrix that maps the patterns
* internal coordinate system to the default coordinate system of the patterns
* parent content stream (the content stream in which the pattern is defined as
* a resource). The concatenation of the pattern matrix with that of the parent content
* stream establishes the pattern coordinate space, within which all graphics objects
* in the pattern are interpreted.
*/
- (Matrix2D*)GetMatrix;
/**
* @return The shading object defining the shading patterns gradient fill.
*
* @note for patterns other than Shading this method throws an exception.
*/
- (Shading*)GetShading;
/**
* @return the tiling type identifier that controls adjustments to the spacing
* of tiles relative to the device pixel grid:
*
* @note for patterns other than Tiling this method throws an exception.
*/
- (TilingType)GetTilingType;
/**
* @return A rectangle in the pattern coordinate system giving the
* coordinates of the left, bottom, right, and top edges, respectively,
* of the pattern cells bounding box. These boundaries are used to clip
* the pattern cell.
*
* @note for patterns other than Tiling this method throws an exception.
*/
- (PDFRect*)GetBBox;
/**
* @return the desired horizontal spacing between pattern cells, measured
* in the pattern coordinate system.
*
* @note that XStep and YStep may differ from the dimensions of the pattern
* cell implied by the BBox entry. This allows tiling with irregularly shaped
* figures. XStep and YStep may be either positive or negative, but not zero.
*
* @note for patterns other than Tiling this method throws an exception.
*/
- (double)GetXStep;
/**
* @return the desired vertical spacing between pattern cells, measured in
* the pattern coordinate system.
*
* @note for patterns other than Tiling this method throws an exception.
*/
- (double)GetYStep;



@end


/**
* Image class provides common methods for working with PDF images.
*
* @note PDF::Element contains a similar interface used to access image data.
* To create the Image object from image PDF::Element, pass the Element's SDF/Cos
* dictionary to Image constructor (i.e. Image image(element->GetXObject()) )
*/
@interface Image : NSObject
{


}





/**
* Create and embed an Image from an external file taking into account specified
* compression hints.
*
* @return PDF::Image object representing the embedded image.
*
* By default the function will either pass-through data preserving the original
* compression or will compress data using Flate compression. It is possible to
* fine tune compression or to select a different compression algorithm using
* 'encoder_hints' object.
*
* @param doc - A document to which the image should be added. To obtain
* SDF::Doc from PDFDoc use PDFDoc::GetSDFDoc() or Obj::GetDoc().
*
* @param filename - The name of the image file. Currently supported formats are
* JPEG, PNG, GIF, TIFF, BMP, EMF, and WMF. Other raster formats can be embedded by
* decompressing image data and using other versions of Image::Create(...) method.
*
* @param encoder_hints - An optional SDF::Obj containing a hint (or an SDF::Array of
* hints) that could be used to select a specific compression method and compression
* parameters. For a concrete example of how to create encoder hints, please take a look
* at JBIG2Test and AddImage sample projects. The image encoder accepts the following
* hints:
*
*  - /JBIG2; SDF::Name("JBIG2"), An SDF::Name Object with value equal to "JBIG2". If the
*	image is monochrome (i.e. bpc == 1), the encoder will compress the image using JBIG2Decode
*	lossless filter.
*
*  - [/JBIG2 /Lossy] - An SDF::Array with two SDF::Name parameters. If the image is
*	monochrome (i.e. bpc == 1), the encoder will compress the image using JBIG2Decode
*	lossy filter. Generally the lossy compression results in smaller files but image may
*	loose some information.
*
*  - [/JBIG2 /Threshold 0.6 /SharePages 50] - Compress a monochrome image using lossy JBIG2Decode
*  compression with the given image threshold and by sharing segments from a specified number
*  of pages. The threshold is a floating point number in the rage from 0 to 1. Increasing the threshold
*  value will decrease the loss of image quality, but may increase the file size. The default value
*  for threshold is 0.85. "SharePages" parameter can be used to specify the maximum number of
*  pages sharing a common 'JBIG2Globals' segment stream. Increasing the value of this parameter
*  improves compression ratio at the expense of memory usage.
*
*  - [/JPEG] - Use JPEG compression with default compression.
*  - [/JPEG /Quality 60] - Use JPEG compression with given quality setting. The "Quality"
*	value is expressed on the 0..100 scale.
*
*  - [/JP2] or [/JPEG2000] - Use JPEG2000 compression to compress a RGB or a grayscale image
*
*  - [/Flate] - Use Flate compression with maximum compression at the expense of
*	speed.
*
*  - [/Flate /Level 9] - Use Flate compression using specified compression level.
*	Compression "Level" must be a number between 0 and 9: 1 gives best speed,
*	9 gives best compression, 0 gives no compression at all (the input data is simply
*	copied a block at a time).
*
*  - /RAW or [/RAW] - The encoder will not use any compression method and the image
*	will be stored in the raw format.
*
* @note For C++ developers: Current document does not take the ownership of the
* encoder_hints object. Therefore it is a good programming practice to create
* encoder_hints object on the stack.
*/
+ (Image*)CreateWithFile: (SDFDoc*)doc filename:  (NSString*)filename encoder_hints:  (Obj*)encoder_hints;
/**
* Create and embed an Image. Embed the raw image data taking into account
* specified compression hints.
*
* By default the function will compress all images using Flate compression.
* It is possible to fine tune compression or to select a different compression
* algorithm using 'encoder_hints' object.
*
* @return PDF::Image object representing the embedded image.
*
* @param doc - A document to which the image should be added. The 'Doc' object
* can be obtained using Obj::GetDoc() or PDFDoc::GetSDFDoc().
* @param image_data - The stream or buffer containing image data. The image data must
* not be compressed and must follow PDF format for sample representation (please refer
* to section 4.8.2 'Sample Representation' in PDF Reference Manual for details).
* @param width - The width of the image, in samples.
* @param height - The height of the image, in samples.
* @param bpc - The number of bits used to represent each color component.
* @param color_space - The color space in which image samples are represented.
* @param encoder_hints - An optional parameter that can be used to fine tune
* compression or to select a different compression algorithm. See Image::Create()
* for details.
*/
+ (Image*)Create: (SDFDoc*)doc filename:  (NSString*)filename;
/**
* Create and embed an Image. Embed the raw image data taking into account
* specified compression hints.
* @note see Image::Create for details.
*/
+ (Image*)CreateWithData: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height bpc:  (int)bpc color_space:  (ColorSpace*)color_space encoder_hints:  (Obj*)encoder_hints;
+ (Image*)CreateWithFilterData: (SDFDoc*)doc image_data:  (FilterReader*)image_data width:  (int)width height:  (int)height bpc:  (int)bpc color_space:  (ColorSpace*)color_space encoder_hints:  (Obj*)encoder_hints;
/**
* Create and embed an ImageMask. Embed the raw image data taking into account
* specified compression hints. The ImageMask can be used as a stencil mask for
* painting in the current color or as an explicit mask specifying which areas of
* the image to paint and which to mask out. One of the most important uses of
* stencil masking is for painting character glyphs represented as bitmaps.
*
* @return PDF::Image object representing the embedded ImageMask.
*
* @param doc - A document to which the image should be added. The 'Doc' object
* can be obtained using Obj::GetDoc() or PDFDoc::GetSDFDoc().
* @param image_data - The stream or buffer containing image data stored in 1 bit per
* sample format. The image data must not be compressed and must follow PDF format for
* sample representation (please refer to section 4.8.2 'Sample Representation' in PDF
* Reference Manual for details).
* @param width - The width of the image, in samples.
* @param height - The height of the image, in samples.
* @param encoder_hints - An optional parameter that can be used to fine tune
* compression or to select a different compression algorithm. See Image::Create()
* for details.
*/
+ (Image*)CreateImageMaskWithBuffer: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height encoder_hints:  (Obj*)encoder_hints;
/**
* Create and embed an ImageMask.
* @note see Image::CreateImageMask for details.
*/
+ (Image*)CreateImageMask: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height;
+ (Image*)CreateImageMaskWithStream: (SDFDoc*)doc image_data:  (FilterReader*)image_data width:  (int)width height:  (int)height encoder_hints:  (Obj*)encoder_hints;
/**
* Create and embed a Soft Mask. Embed the raw image data taking into account
* specified compression hints.
*
* @param A soft-mask image (see Soft-Mask Images in PDF Reference Manual) to
* be used as a source of mask shape or mask opacity values in the transparent
* imaging model.
*
* @param doc - A document to which the image should be added. The 'Doc' object
* can be obtained using Obj::GetDoc() or PDFDoc::GetSDFDoc().
* @param image_data - The stream or buffer containing image data represented in
* DeviceGray color space (i.e. one component per sample). The image data must not
* be compressed and must follow PDF format for sample representation (please refer
* to section 4.8.2 'Sample Representation' in PDF Reference Manual for details).
* @param width - The width of the image, in samples.
* @param height - The height of the image, in samples.
* @param bpc - The number of bits used to represent each color component.
* @param encoder_hints - An optional parameter that can be used to fine tune
* compression or to select a different compression algorithm. See Image::Create()
* for details.

* @note this feature is available only in PDF 1.4 and higher.
*/
+ (Image*)CreateSoftMaskWithBuffer: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height bpc:  (int)bpc encoder_hints:  (Obj*)encoder_hints;
/**
* Create and embed a Soft Mask. Embed the raw image data taking into account
* specified compression hints.
* @note see Image::CreateSoftMask for details.
*/
+ (Image*)CreateSoftMask: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height bpc:  (int)bpc;
/**
* Directly embed the image that is already compressed using the Image::InputFilter
* format. The function can be used to pass-through pre-compressed image data.
*
* @return PDF::Image object representing the embedded image.
*
* @param doc - A document to which the image should be added. The 'Doc' object
* can be obtained using Obj::GetDoc() or PDFDoc::GetSDFDoc().
* @param image_data - The stream or buffer containing compressed image data.
* The compression format must match the input_format parameter.
* @param width - The width of the image, in samples.
* @param height - The height of the image, in samples.
* @param bpc - The number of bits used to represent each color component.
* @param color_space - The color space in which image samples are specified.
* @param input_format - Image::InputFilter describing the format of pre-compressed
* image data.
* @param encoder_hints - An optional parameter that can be used to fine tune
* compression or to select a different compression algorithm. See Image::Create()
* for details.
*/
+ (Image*)CreateSoftMaskWithStream: (SDFDoc*)doc image_data:  (FilterReader*)image_data width:  (int)width height:  (int)height bpc:  (int)bpc encoder_hints:  (Obj*)encoder_hints;
/**
* Embed the raw image data taking into account specified compression hints.
* @note see the above method for details.
*/
+ (Image*)CreateWithBufferAndFormat: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height bpc:  (int)bpc color_space:  (ColorSpace*)color_space input_format:  (InputFilter)input_format;	/**
* Create an image from an existing image represented as a SDF/Cos object.
*
* @note To create the Image object from image PDF::Element, pass the Element's
* SDF/Cos dictionary to Image constructor (i.e. Image image(element->GetXObject()))
*/
- (id)initWithImage_xobject: (Obj*)image_xobject;

+ (Image*)CreateWithStreamAndFormat: (SDFDoc*)doc image_data:  (FilterReader*)image_data width:  (int)width height:  (int)height bpc:  (int)bpc color_space:  (ColorSpace*)color_space input_format:  (InputFilter)input_format;
/**
* @return the underlying SDF/Cos object
*/
- (Obj*)GetSDFObj;
/**
* @return whether this is a valid raster image. If the function returns false the
* underlying SDF/Cos object is not a valid raster image and this Image object should
* be treated as null.
*/
- (BOOL)IsValid;
/**
* @return A stream (filter) containing decoded image data
*/
- (Filter*)GetImageData;
/**
* @return the size of image data in bytes
*/
- (int)GetImageDataSize;
/**
* @return The SDF object representing the color space in which image
* samples are specified or NULL if:
*  - the image is an image mask
*  - or is compressed using JPXDecode with missing ColorSpace entry in image dictionary.
*
* The returned color space may be any type of color space except Pattern.
*/
- (ColorSpace*)GetImageColorSpace;
/**
* @return the width of the image, in samples.
*/
- (int)GetImageWidth;
/**
* @return the height of the image, in samples.
*/
- (int)GetImageHeight;
/**
* @return Decode array or NULL if the parameter is not specified. A decode object is an
* array of numbers describing how to map image samples into the range of values
* appropriate for the images color space . If ImageMask is true, the array must be
* either [0 1] or [1 0]; otherwise, its length must be twice the number of color
* components required by ColorSpace. Default value depends on the color space,
* See Table 4.36 in PDF Ref. Manual.
*/
- (Obj*)GetDecodeArray;
/**
* @return the number of bits used to represent each color component. Only a
* single value may be specified; the number of bits is the same for all color
* components. Valid values are 1, 2, 4, 8, and 16.
*/
- (int)GetBitsPerComponent;
/**
* @return the number of color components per sample.
*/
- (int)GetComponentNum;
/**
* @return a boolean indicating whether the inline image is to be treated as an image mask.
*/
- (BOOL)IsImageMask;
/**
* @return a boolean indicating whether image interpolation is to be performed.
*/
- (BOOL)IsImageInterpolate;
/**
* @return an image XObject defining an image mask to be applied to this image (See
* 'Explicit Masking', 4.8.5), or an array specifying a range of colors
* to be applied to it as a color key mask (See 'Color Key Masking').
*
* If IsImageMask() return true, this method will return NULL.
*/
- (Obj*)GetMask;
/**
* Set an Explicit Image Mask.
*
* @param An Image object which serves as an explicit mask for the
* base (this) image. The base image and the image mask need not have the
* same resolution (Width and Height values), but since all images are defined on
* the unit square in user space, their boundaries on the page will coincide; that is,
* they will overlay each other. The image mask indicates which places on the page
* are to be painted and which are to be masked out (left unchanged). Unmasked areas
* are painted with the corresponding portions of the base image; masked areas
* are not.
*
* @note image_mask must be a valid image mask (i.e. image_mask.IsImageMask() must
* return true.
*/
- (void)SetMaskWithImage: (Image*)image_mask;
/**
* Set a Color Key Mask.
*
* @param mask is an Cos/SDF array specifying a range of colors to be masked
* out. Samples in the image that fall within this range are not painted, allowing
* the existing background to show through. The effect is similar to that of the
* video technique known as chroma-key. For details of the array format please
* refer to section 4.8.5 'Color Key Masking' in PDF Reference Manual.
*
* @note the current document takes the ownership of the given SDF object.
*/
- (void)SetMaskWithColor: (Obj*)mask;
/**
* @return an image XObject defining a Soft Mask to be applied to this image
* (See section 7.5.4 'Soft-Mask Images' in PDF Reference Manual), or NULL
* if the image does not have the soft mask.
*/
- (Obj*)GetSoftMask;
/**
* Set a Soft Mask.
*
* @param soft_mask is a subsidiary Image object defining a soft-mask image
* (See section 7.5.4 'Soft-Mask Images' in PDF Reference Manual) to be used
* as a source of mask shape or mask opacity values in the transparent imaging
* model. The alpha source parameter in the graphics state determines whether
* the mask values are interpreted as shape or opacity.
*/
- (void)SetSoftMask: (Image*)soft_mask;
/**
* @return The color rendering intent to be used in rendering the image.
*/
- (RenderingIntent)GetImageRenderingIntent;
/**
* Saves this image to a file.
*
* The output image format (TIFF, JPEG, or PNG) will be
* automatically selected based on the properties of the embedded
* image. For example, if the embedded image is using CCITT Fax
* compression, the output format will be TIFF. Similarly, if the
* embedded image is using JPEG compression the output format will
* be JPEG. If your application needs to explicitly control output
* image format you may want to use ExportAsTiff() or ExportAsPng().
*
* @param filename string that specifies the path name for
* the saved image. The filename should not include the extension
* which will be appended to the filename string based on the output
* format.
*
* @return the number indicating the selected image format:
* (0 - PNG, 1 - TIF, 2 - JPEG).
*/
- (int)ExportToFile: (NSString*)filename;
/**
* Saves this image to the output stream.
*
* @return the number indicating the selected image format:
* (0 - PNG, 1 - TIF, 2 - JPEG).
*
* @param writer A pointer to FilterWriter used to write to the
* output stream. If the parameter is null, nothing will be written
* to the output stream, but the function returns the format identifier.
*
* @note see the overloaded Image::Export method for more information.
*/
- (int)ExportToStream: (FilterWriter*)writer;
/**
* Saves this image to a TIFF file.
*
* @param filename string that specifies the path name for
* the saved image. The filename should include the file extension
*/
- (void)ExportAsTiffFile: (NSString*)filename;
/**
* Saves this image to a TIFF output stream.
*
* @param writer FilterWriter used to write to the output stream.
*/
- (void)ExportAsTiffStream: (FilterWriter*)writer;
/**
* Saves this image to a PNG file.
*
* @param filename string that specifies the path name for
* the saved image. The filename should include the file extension
*/
- (void)ExportAsPngFile: (NSString*)filename;
/**
* Saves this image to a PNG output stream.
*
* @param writer FilterWriter used to write to the output stream.
*/
- (void)ExportAsPngStream: (FilterWriter*)writer;


@end


/**
* Element is the abstract interface used to access graphical elements used to build the
* display list.
*
* Just like many other classes in PDFNet (e.g. ColorSpace, Font, Annot, etc), Element
* class follows the composite design pattern. This means that all Elements are
* accessed through the same interface, but depending on the Element type (that can be
* obtained using GetType()), only methods related to that type can be called.
* For example, if GetType() returns e_image, it is illegal to call a method specific to
* another Element type (i.e. a call to a text specific GetTextData() will throw an
* Exception).
*/
@interface Element : NSObject
{


}





/**
* @return the current element type.
*/
- (ElementType)GetType;
/**
* @return GState of this Element
*/
- (GState*)GetGState;
/**
* @return Current Transformation Matrix (CTM) that maps coordinates to the
* initial user space.
*/
- (Matrix2D*)GetCTM;
/**
* Obtains the bounding box for a graphical element.
*
* Calculates the bounding box for a graphical element (i.e. an Element that belongs
* to one of following types: e_path, e_text, e_image, e_inline_image, e_shading e_form).
* The returned bounding box is guaranteed to encompass the Element, but is not guaranteed
* to be the smallest box that could contain the element. For example, for Bezier curves
* the bounding box will enclose all control points, not just the curve itself.
*
* @return true if this is a graphical element and the bounding box can be calculated;
* false for non-graphical elements which don't have bounding box.
*
* @param out_bbox (Filled by the method) A reference to a rectangle specifying the
* bounding box of Element (a rectangle that surrounds the entire element). The coordinates
* are represented in the default PDF page coordinate system and are using units called points
* ( 1 point = 1/72 inch =  2.54 /72 centimeter). The bounding box already accounts for the
* effects of current transformation matrix (CTM), text matrix, font size, and other properties
* in the graphics state. If this is a non-graphical element (i.e. the method returns false) the
* bounding box is undefined.
*/
- (PDFRect*)GetBBox;
/**
* @return Parent logical structure element (such as 'span' or 'paragraph').
* If the Element is not associated with any structure element, the returned
* SElement will not be valid (i.e. selem.IsValid() -> false).
*/
- (SElement*)GetParentStructElement;
/**
* @return Marked Content Identifier (MCID) for this Element or
* a negative number if the element is not assigned an identifier/MCID.
*
* Marked content identifier can be used to associate an Element with
* logical structure element that refers to the Element.
*/
- (int)GetStructMCID;
/**
* @return true if this element is visible in the optional-content
* context (OCG::Context). The method considers the context's current OCMD stack,
* the group ON-OFF states, the non-OC drawing status, the drawing and enumeration mode,
* and the intent.
*
* When enumerating page content, OCG::Context can be passed as a parameter in
* ElementReader.Begin() method. When using PDFDraw, PDFRasterizer, or PDFView class to
* render PDF pages use PDFDraw::SetOCGContext() method to select an OC context.
*/
- (BOOL)IsOCVisible;
/**
* @return true if the current path element is a clipping path and should be added
* to clipping path stack.
*/
- (BOOL)IsClippingPath;
/**
* @return true if the current path element should be stroked
*/
- (BOOL)IsStroked;
/**
* @return true if the current path element should be filled
*/
- (BOOL)IsFilled;
/**
* @return true if the current path should be filled using non-zero winding rule,
* or false if the path should be filled using even-odd rule.
*
* According non-zero winding rule, you can determine whether a test point is inside or
* outside a closed curve as follows: Draw a line from a test point to a point that
* is distant from the curve. Count the number of times the curve crosses the test
* line from left to right, and count the number of times the curve crosses the test
* line from right to left. If those two numbers are the same, the test point is
* outside the curve; otherwise, the test point is inside the curve.
*
* According to even-odd rule, you can determine whether a test point is inside
* or outside a closed curve as follows: Draw a line from the test point to a point
* that is distant from the curve. If that line crosses the curve an odd number of
* times, the test point is inside the curve; otherwise, the test point is outside
* the curve.
*/
- (BOOL)IsWindingFill;
/**
* @return true if the current clip path is using non-zero winding rule, or false
* for even-odd rule.
*/
- (BOOL)IsClipWindingFill;
/**
* Returns the PathData stored by the path element.
*
* @return The PathData which contains the operators and corresponding point data.
*/
- (PathData*)GetPathData;
/**
* Set the PathData of this element. The PathData contains the array of points
* stored by the element and the array of path segment types.
*/
- (void)SetPathData: (PathData*)data;
/**
* Indicate whether the path is a clipping path or non-clipping path
*/
- (void)SetPathClip: (BOOL)clip;
/**
* Indicate whether the path should be stroked
*/
- (void)SetPathStroke: (BOOL)stroke;
/**
* Indicate whether the path should be filled
*/
- (void)SetPathFill: (BOOL)fill;
/**
* Sets path's fill rule.
* @param winding_rule if winding_rule is true path will be filled using non-zero
* winding fill rule, otherwise even-odd fill will be used.
*/
- (void)SetWindingFill: (BOOL)winding_rule;
/**
* Sets clipping path's fill rule.
* @param winding_rule if winding_rule is true clipping should use non-zero
* winding rule, or false for even-odd rule.
*/
- (void)SetClipWindingFill: (BOOL)winding_rule;
/**
* @return the SDF object of the Image/Form object.
*/
- (Obj*)GetXObject;
/**
* @return A stream (filter) containing decoded image data
*/
- (Filter*)GetImageData;
/**
* @return the size of image data in bytes
*/
- (int)GetImageDataSize;
/**
* @return The SDF object representing the color space in which image
* are specified or NULL if the image is an image mask
*
* The returned color space may be any type of color space except Pattern.
*/
- (ColorSpace*)GetImageColorSpace;
/**
* @return the width of the image, in samples.
*/
- (int)GetImageWidth;
/**
* @return the height of the image, in samples.
*/
- (int)GetImageHeight;
/**
* @return Decode array or NULL if the parameter is not specified. A decode object is an
* array of numbers describing how to map image samples into the range of values
* appropriate for the color space of the image. If ImageMask is true, the array must be
* either [0 1] or [1 0]; otherwise, its length must be twice the number of color
* components required by ColorSpace. Default value depends on the color space,
* See Table 4.36 in PDF Ref. Manual.
*/
- (Obj*)GetDecodeArray;
/**
* @return the number of bits used to represent each color component. Only a
* single value may be specified; the number of bits is the same for all color
* components. Valid values are 1, 2, 4, and 8.
*/
- (int)GetBitsPerComponent;
/**
* @return the number of color components per sample.
*/
- (int)GetComponentNum;
/**
* @return a boolean indicating whether the inline image is to be treated as an image mask.
*/
- (BOOL)IsImageMask;
/**
* @return a boolean indicating whether image interpolation is to be performed.
*/
- (BOOL)IsImageInterpolate;
/**
* @return an image XObject defining an image mask to be applied to this image (See
* 'Explicit Masking', 4.8.5), or an array specifying a range of colors
* to be applied to it as a color key mask (See 'Color Key Masking').
*
* If IsImageMask() return true, this method will return NULL.
*/
- (Obj*)GetMask;
/**
* @return The color rendering intent to be used in rendering the image.
*/
- (RenderingIntent)GetImageRenderingIntent;
/**
* @return a pointer to Unicode string for this text Element. The
* function maps character codes to Unicode array defined by Adobe
* Glyph List (http://partners.adobe.com/asn/developer/type/glyphlist.txt).
*
* @note In PDF text can be encoded using various encoding schemes
* and in some cases it is not possible to extract Unicode encoding.
* If it is not possible to map charcode to Unicode the function will
* map a character to undefined code, 0xFFFD. This code is defined in
* private Unicode range.
*
* @note If you would like to map raw text to Unicode (or some other encoding)
* yourself use CharIterators returned by CharBegin()/CharEnd() and
* PDF::Font code mapping methods.
*
* @note The string owner is the current element (i.e. ElementReader or ElementBuilder).
*/
- (NSString*)GetTextString;
/**
* @return a pointer to the internal text buffer for this text element.
* @note GetTextData() returns the raw text data and not a Unicode string.
* In PDF text can be encoded using various encoding schemes so it is necessary
* to consider Font encoding while processing the content of this buffer.
*
* @note Most of the time GetTextString() is what you are looking for instead.
* GetTextString() maps the raw text directly into Unicode (as specified by Adobe
* Glyph List (AGL) ). Even if you would prefer to decode text yourself it is more
* convenient to use CharIterators returned by CharBegin()/CharEnd() and
* PDF::Font code mapping methods.
*
* @note the buffer owner is the current element (i.e. ElementReader or ElementBuilder).
*/
- (NSData*)GetTextData;
/**
* @return the size of the internal text buffer returned in GetTextData().
*/
- (unsigned int)GetTextDataSize;
/**
* @return a reference to the current text matrix (Tm).
*/
- (Matrix2D*)GetTextMatrix;
/**
* @return a CharIterator addressing the first CharData element in the text run.
*
* CharIterator points to CharData. CharData is a data structure that contains
* the char_code number (used to retrieve glyph outlines, to map to Unicode, etc.),
* character positioning information (x, y), and the number of bytes taken by the
* character within the text buffer.
*
* @note CharIterator follows the standard STL forward-iterator interface.
*
* An example of how to use CharIterator.
* @code
*     for (CharIterator itr = element.GetCharIterator(); itr.HasNext(); itr.Next()) {
* 			unsigned int char_code = itr.Current().char_code;
* 			double char_pos_x = itr.Current().x;
* 			double char_pos_y = itr.Current().y;
*     }
* @endcode
*
* @note Character positioning information (x, y) is represented in text space.
* In order to get the positioning in the user space, the returned value should
* be scaled using the text matrix (GetTextMatrix()) and the current transformation
* matrix (GetCTM()). See section 4.2 'Other Coordinate Spaces' in PDF Reference
* Manual for details and PDFNet FAQ - "How do I get absolute/relative text and
* character positioning?".
*
* @note within a text run a character may occupy more than a single byte (e.g.
* in case of composite/Type0 fonts). The role of CharIterator/CharData is to
* provide a uniform and easy to use interface to access character information.
*/
- (CharIterator*)GetCharIterator;
/**
* @return The text advance distance in text space.
*
* The total sum of all of the advance values from rendering all of the characters
* within this element, including the advance value on the glyphs, the effect of
* properties such as 'char-spacing', 'word-spacing' and positioning adjustments
* on 'TJ' elements.
*
* @note Computed text length is represented in text space. In order to get the
* length of the text run in the user space, the returned value should be scaled
* using the text matrix (GetTextMatrix()) and the current transformation
* matrix (GetCTM()). See section 4.2 'Other Coordinate Spaces' in PDF Reference
* Manual for details.
*/
- (double)GetTextLength;
/**
* @return The number used to adjust text matrix in horizontal direction when drawing
* text. The number is expressed in thousandths of a unit of text space. The returned
* number corresponds to a number value within TJ array. For 'Tj' text strings the
* returned value is always 0.
*
* @note because CharIterator positioning information already accounts for TJ
* adjustments this method is rarely used.
*/
- (double)GetPosAdjustment;
/**
* Returns the offset (out_x, out_y) to the start of the current line relative to
* the beginning of the previous line.
*
* out_x and out_y are numbers expressed in unscaled text space units.
* The returned numbers correspond to the arguments of 'Td' operator.
*/
- (PDFPoint*)GetNewTextLineOffset;
/**
* Sets the offset (dx, dy) to the start of the current line relative to the beginning
* of the previous line.
*/
- (void)SetNewTextLineOffset: (double)dx dy:  (double)dy;
/**
* @return true if this element is directly associated with a text matrix
* (that is Tm operator is just before this text element) or false if the text
* matrix is default or is inherited from previous text elements.
*/
- (BOOL)HasTextMatrix;
/**
* Set the text data for the current e_text Element.
* @param text_data a pointer to a buffer containing text.
* @param text_data_size the size of the internal text buffer
*/
- (void)SetTextData: (NSData*)text_data text_data_size:  (int)text_data_size;
/**
* Sets the text matrix for a text element.
*
* @param mtx The new text matrix for this text element
*/
- (void)SetTextMatrixWithMatrix2D: (Matrix2D*)mtx;
/**
* Sets the text matrix for a text element. This method accepts text
* transformation matrix components directly.
*
* A transformation matrix in PDF is specified by six numbers, usually
* in the form of an array containing six elements. In its most general
* form, this array is denoted [a b c d h v]; it can represent any linear
* transformation from one coordinate system to another. For more
* information about PDF matrices please refer to section 4.2.2 'Common
* Transformations' in PDF Reference Manual, and to documentation for
* Matrix2D class.
*
* @param a - horizontal 'scaling' component of the new text matrix.
* @param b - 'rotation' component of the new text matrix.
* @param c - 'rotation' component of the new text matrix.
* @param d - vertical 'scaling' component of the new text matrix.
* @param h - horizontal translation component of the new text matrix.
* @param v - vertical translation component of the new text matrix.
*/
- (void)SetTextMatrix: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
/**
* @return Set the horizontal adjustment factor (i.e. a number value within TJ array)
*
* @note Positive values move the current text element backwards (along text direction).
*       Negative values move the current text element forward (along text direction).
*/
- (void)SetPosAdjustment: (double)adjust;
/**
* Recompute the character positioning information (i.e. CharIterator-s) and
* text length.
*
* Element objects caches text length and character positioning information.
* If the user modifies the text data or graphics state the cached information
* is not correct. UpdateTextMetrics() can be used to recalculate the correct
* positioning and length information.
*/
- (void)UpdateTextMetrics;
/**
* @return the SDF object of the Shading object.
*/
- (Shading*)GetShading;
/**
* @return a dictionary containing the property list or NULL if property
* dictionary is not present.
*
* @note the function automatically looks under Properties sub-dictionary of the
* current resource dictionary if the dictionary is not in-line. Therefore you
* can assume that returned Obj is dictionary if it is not NULL.
*/
- (Obj*)GetMCPropertyDict;
/**
* @return a tag is a name object indicating the role or significance of
* the marked content point/sequence.
*/
- (Obj*)GetMCTag;
- (id)init;

@end


/**
* ElementBuilder is used to build new PDF::Elements (e.g. image, text, path, etc)
* from scratch. In conjunction with ElementWriter, ElementBuilder can be used to create
* new page content.
*
* @note Analogous to ElementReader, every call to ElementBuilder.Create? method destroys
* the Element currently associated with the builder and all previous Element pointers are
* invalidated.
*
* @note For C++ developers. Analogous to ElementReader, ElementBuilder is the owner of
* all Element objects it creates.
*/
@interface ElementBuilder : NSObject
{


}





/**
* The function sets the graphics state of this Element to the given value.
* If 'gs' parameter is not specified or is NULL the function resets the
* graphics state of this Element to the default graphics state (i.e. the
* graphics state at the beginning of the display list).
*
* The function can be used in situations where the same ElementBuilder is used
* to create content on several pages, XObjects, etc. If the graphics state is not
* Reset() when moving to a new display list, the new Element will have the same
* graphics state as the last Element in the previous display list (and this may
* or may not be your intent).
*
* Another use of Reset(gs) is to make sure that two Elements have the graphics
* state.
*/
- (void)Reset: (GState*)gs;
/**
* Create a content image Element out of a given document Image.
*/
- (Element*)CreateImage: (Image*)img;
/**
* Create a content image Element out of a given document Image.
* @param mtx the image transformation matrix.
*/
- (Element*)CreateImageWithMatrix: (Image*)img mtx:  (Matrix2D*)mtx;
/**
* Create a content image Element out of a given document Image with
* the lower left corner at (x, y), and scale factors (hscale, vscale).
*/
- (Element*)CreateImageWithCornerAndScale: (Image*)img x:  (double)x y:  (double)y hscale:  (double)hscale vscale:  (double)vscale;
/**
* Create e_group_begin Element (i.e. 'q' operator in PDF content stream).
* The function saves the current graphics state.
*/
- (Element*)CreateGroupBegin;
/**
* Create e_group_end Element (i.e. 'Q' operator in PDF content stream).
* The function restores the previous graphics state.
*/
- (Element*)CreateGroupEnd;
/**
* Create a shading Element.
*/
- (Element*)CreateShading: (Shading*)sh;
/**
* Create a Form XObject Element.
* @param form a Form XObject content stream
*/
- (Element*)CreateFormWithObj: (Obj*)form;
/**
* Create a Form XObject Element using the content of the existing page.
* This method assumes that the XObject will be used in the same
* document as the given page. If you need to create the Form XObject
* in a different document use CreateForm(Page, Doc) method.
*
* @param page A page used to create the Form XObject.
*/
- (Element*)CreateFormWithPage: (Page*)page;
/**
* Create a Form XObject Element using the content of the existing page.
* Unlike CreateForm(Page) method, you can use this method to create form
* in another document.
*
* @param page A page used to create the Form XObject.
* @param doc Destination document for the Form XObject.
*/
- (Element*)CreateFormWithPageAndDestination: (Page*)page doc:  (PDFDoc*)doc;
/**
* Start a text block ('BT' operator in PDF content stream).
* The function installs the given font in the current graphics state.
*/
- (Element*)CreateTextBeginWithFont: (Font*)font font_sz:  (double)font_sz;
/**
* Start a text block ('BT' operator in PDF content stream).
*/
- (Element*)CreateTextBegin;
/**
* Ends a text block.
*/
- (Element*)CreateTextEnd;
/**
* Create a text run using the given font.
* @note a text run can be created only within a text block
*/
- (Element*)CreateTextRunWithFont: (NSString *)text_data font:  (Font*)font font_sz:  (double)font_sz;
/**
* Create a new text run.
* @note a text run can be created only within a text block
* @note you must set the current Font and font size before calling this function.
*/
- (Element*)CreateTextRun: (NSString *)text_data;
/**
* Create a new Unicode text run.
*
* @param text_data pointer to Unicode text
* @param text_data_sz number of characters (not bytes) in text_data
*
* @note you must set the current Font and font size before calling this function
* and the font must be created using Font::CreateCIDTrueTypeFont() method.
*
* @note a text run can be created only within a text block
*/
- (Element*)CreateUnicodeTextRun: (unsigned short*)text_data text_data_sz:  (unsigned int)text_data_sz;
/**
* Create e_text_new_line Element (i.e. a Td operator in PDF content stream).
* Move to the start of the next line, offset from the start of the current
* line by (dx , dy). dx and dy are numbers expressed in unscaled text space
* units.
*/
- (Element*)CreateTextNewLineWithOffset: (double)dx dy:  (double)dy;
/**
* Create e_text_new_line Element (i.e. a T* operator in PDF content stream).
*/
- (Element*)CreateTextNewLine;
/**
* Create a path Element using given path segment data
*/
- (Element*)CreatePath: (NSMutableArray*)points seg_types:  (NSData*)seg_types;
/**
* Create a rectangle path Element.
*
* @param x, y The coordinates of the lower left corner of the rectangle.
* @param width, height - The width and height of the rectangle.
*/
- (Element*)CreateRect: (double)x y:  (double)y width:  (double)width height:  (double)height;
/**
* Create an ellipse (or circle, if rx == ry) path Element.
*
* @param cx, cy The coordinates of the ellipse center.
* @param rx, ry - The width and height of the ellipse rectangle.
*/
- (Element*)CreateEllipse: (double)cx cy:  (double)cy rx:  (double)rx ry:  (double)ry;
/**
* Starts building a new path Element that can contain an arbitrary sequence
* of lines, curves, and rectangles.
*/
- (void)PathBegin;
/**
* Finishes building of the path Element.
* @return the path Element
*/
- (Element*)PathEnd;
/**
* Set the current point.
*/
- (void)MoveTo: (double)x y:  (double)y;
/**
* Draw a line from the current point to the given point.
*/
- (void)LineTo: (double)x y:  (double)y;
/**
* Draw a Bezier curve from the current point to the given point (x2, y2) using
* (cx1, cy1) and (cx2, cy2) as control points.
*/
- (void)CurveTo: (double)cx1 cy1:  (double)cy1 cx2:  (double)cx2 cy2:  (double)cy2 x2:  (double)x2 y2:  (double)y2;
/**
* Draw an arc with the specified parameters (lower left corner, width, height and angles).
*
* @param	x, y			coordinates of the lower left corner of the ellipse encompassing rectangle
* @param	width, height	overall width and height of the full ellipse (not considering the angular extents).
* @param	start			starting angle of the arc in degrees
* @param	extent			angular extent of the arc in degrees
*/
- (void)ArcToWithParam: (double)x y:  (double)y width:  (double)width height:  (double)height start:  (double)start extent:  (double)extent;
/**
* Draw an arc from the current point to the end point.
*
* @param xr, yr				x and y radius for the arc
* @param rx					x-axis rotation in degrees
* @param isLargeArc			indicates if smaller or larger arc is chosen
*								1 - one of the two larger arc sweeps is chosen
*								0 - one of the two smaller arc sweeps is chosen
* @param sweep					direction in which arc is drawn (1 - clockwise, 0 - counterclockwise)
* @param endX, endY			end point
*
* @note The Arc is defined the same way as it is specified by SVG or XPS standards. For
*		further questions please refer to the XPS or SVG standards.
*/
- (void)ArcToEndPt: (double)xr yr:  (double)yr rx:  (double)rx isLargeArc:  (BOOL)isLargeArc sweep:  (BOOL)sweep endX:  (double)endX endY:  (double)endY;
/**
* Add an ellipse (or circle, if rx == ry) to the current path as a complete subpath.
* Setting the current point is not required before using this function.
*
* @param cx, cy The coordinates of the ellipse center.
* @param rx, ry - The radii of the ellipse.
*/
- (void)Ellipse: (double)cx cy:  (double)cy rx:  (double)rx ry:  (double)ry;
/**
* Add a rectangle to the current path as a complete subpath.
* Setting the current point is not required before using this function.
*
* @param x, y The coordinates of the lower left corner of the rectangle.
* @param width, height - The width and height of the rectangle.
*/
- (void)Rect: (double)x y:  (double)y width:  (double)width height:  (double)height;
/**
* Closes the current subpath.
*/
- (void)ClosePath;

- (id)init;

@end


/**
* ElementReader can be used to parse and process content streams. ElementReader provides a
* convenient interface used to traverse the Element display list of a page. The display list
* representing graphical elements (such as text-runs, paths, images, shadings, forms, etc) is
* accessed using the intrinsic iterator. ElementReader automatically concatenates page contents
* spanning multiple streams and provides a mechanism to parse contents of sub-display lists
* (e.g. forms XObjects and Type3 fonts).
*
* A sample use case for ElementReader is given below:
* @code
* ...
* ElementReader reader;
* reader.Begin(page);
* for (Element element=reader.Next(); element; element = reader.Next()) // Read page contents
* {
*   switch (element.GetType())	{
*     case Element::e_path: { // Process path data...
*         const double* data = element.GetPathPoints();
*         int sz = element.GetPointCount();
*     }
*     break;
*     case Element::e_text:
*         // ...
*     break;
*   }
* }
* reader.End();
* @endcode
*
*  For a full sample, please refer to ElementReader and ElementReaderAdvTest sample projects.
*/
@interface ElementReader : NSObject
{


}





- (void)ReaderBeginWithPage: (Page*)page ocg_context:  (Context*)ocg_context;
/**
* Begin processing a page.
*
* @param page A page to start processing.
*
* @param ocg_context An optional parameter used to specify the Optional Content (OC)
* Context that should be used when processing the page. When the OCG::Context is specified,
* Element::IsOCVisible() will return 'true' or 'false' depending on the visibility of the
* current Optional Content Group (OCG) and the states of flags in the given context.
*
* @note When page processing is completed, make sure to call ElementReader.End().
*/
- (void)Begin: (Page*)page;
- (void)ReaderBeginWithSDFObj: (Obj*)content_stream resource_dict:  (Obj*)resource_dict ocg_context:  (Context*)ocg_context;
/**
* @return a page Element or a 'NULL' element if the end of current-display list was
* reached. You may use GetType() to determine the type of the returned Element.
*
* @note Every call to ElementReader::Next() destroys the current Element.
* Therefore, an Element becomes invalid after subsequent
* ElementReader::Next() operation.
*/
- (Element*)Next;
/**
* @return the current Element or a 'NULL' Element. The current element is the one
* returned in the last call to Next().
*
* @note Every call to ElementReader::Next() destroys the current Element. Therefore, an
* Element becomes invalid after subsequent ElementReader::Next() operation.
*/
- (Element*)Current;
/**
* When the current element is a form XObject you have the option to skip form
* processing (by not calling FormBegin()) or to open the form stream and
* continue Element traversal into the form.
*
* To open a form XObject display list use FormBegin() method. The Next() returned
* Element will be the first Element in the form XObject display list. Subsequent calls to Next()
* will traverse form's display list until NULL is returned. At any point you can
* close the form sub-list using ElementReader::End() method. After the form display
* list is closed (using End()) the processing will return to the parent display list
* at the point where it left off before entering the form XObject.
*/
- (void)FormBegin;
/**
* A method used to spawn the sub-display list representing the tiling pattern
* of the current element in the ElementReader. You can call this method at any
* point as long as the current element is valid.
*
* @param fill_pattern If true, the filling pattern of the current element will
* be spawned; otherwise, the stroking pattern of the current element will be
* spawned. Note that the graphics state will be inherited from the parent content
* stream (the content stream in which the pattern is defined as a resource) automatically.
*
* @param reset_ctm_tfm An optional parameter used to indicate whether the pattern's
* display list should set its initial CTM and transformation matrices to identity matrix.
* In general, we should leave it to be false.
*
* To open a tiling pattern sub-display list use PatternBegin(pattern) method.
* The Next() returned Element will be the first Element in the pattern display list.
* Subsequent calls to Next() will traverse pattern's display list until NULL is
* encountered. At any point you can close the pattern sub-list using
* ElementReader::End() method. After the pattern display list is closed,
* the processing will return to the parent display list at the point where
* pattern display list was spawned.
*/
- (void)PatternBegin: (BOOL)fill_pattern reset_ctm_tfm:  (BOOL)reset_ctm_tfm;
/**
* A method used to spawn a sub-display list representing a Type3 Font glyph. You can
* call this method at any point as long as the current element in the ElementReader
* is a text element whose font type is type 3.
*
* @param char_data The information about the glyph to process. You can get this information
* by dereferencing a CharIterator.
*
* @param resource_dict - An optional '/Resource' dictionary parameter.
* If any glyph descriptions refer to named resources but Font Resource dictionary
* is absent, the names are looked up in the supplied resource dictionary.
*
* To open a Type3 font sub-display list use Type3FontBegin() method. The Next()
* returned Element will be the first Element in the glyph's display list.
* Subsequent calls to Next() will traverse glyph's display list until NULL is
* returned. At any point you can close the glyph sub-list using ElementReader::End()
* method. After the glyph display list is closed, the processing will return to the
* parent display list at the point where glyph display list was spawned.
*/
- (void)Type3FontBegin: (TRN_chardata*)char_data resource_dict:  (Obj*)resource_dict;
/**
* Close the current display list.
*
* If the current display list is a sub-list created using FormBegin(), PatternBegin(),
* or Type3FontBegin() methods, the function will end the sub-list and will return
* processing to the parent display list at the point where it left off before
* entering the sub-list.
*
* @return true if the closed display list is a sub-list or false if it is a root
* display list.
*/
- (BOOL)End;
/**
* @return an iterator to the beginning of the list containing identifiers of modified
* graphics state attributes since the last call to ClearChangeList(). The list can
* be consulted to determine which graphics states were modified between two
* Elements. Attributes are ordered in the same way as they are set in the content
* stream. Duplicate attributes are eliminated.
*/
- (GSChangesIterator*)GetChangesIterator;
/**
* @return true if given GState attribute was changed since the last call to
* ClearChangeList().
*/
- (BOOL)IsChanged: (GStateAttribute)attrib;
/**
* Clear the list containing identifiers of modified graphics state attributes.
* The list of modified attributes is then accumulated during a subsequent call(s)
* to ElementReader.Next().
*/
- (void)ClearChangeList;
/**
* @param extra resource dictionary for finding images, fonts, etc.
*/
- (void)AppendResource: (Obj*)res;
/**
* @return SDF/Cos object matching the specified name in the current resource
* dictionary. For 'Page' the name is looked up in the page's /Resources/<Class>
* dictionary. For Form XObjects, Patterns, and Type3 fonts that have a content
* stream within page content stream the specified resource is first looked-up in the
* resource dictionary of the inner stream. If the resource is not found, the name is
* looked up in the outer content streams resource dictionary. The function returns
* NULL if the resource was not found.
*/
- (Obj*)GetFont: (NSString *)name;
/**
* @note see ElementReader::GetFont
*/
- (Obj*)GetXObject: (NSString *)name;
/**
* @note see ElementReader::GetFont
*/
- (Obj*)GetShading: (NSString *)name;
/**
* @note see ElementReader::GetFont
*/
- (Obj*)GetColorSpace: (NSString *)name;
/**
* @note see ElementReader::GetFont
*/
- (Obj*)GetPattern: (NSString *)name;
/**
* @note see ElementReader::GetFont
*/
- (Obj*)GetExtGState: (NSString *)name;

- (id)init;

@end


/**
* ElementWriter can be used to assemble and write new content to a page, Form XObject,
* Type3 Glyph stream, pattern stream, or any other content stream.
*/
@interface ElementWriter : NSObject
{


}





/**
* Begin writing to the given page.
*
* By default, new content will be appended to the page, as foreground graphics.
* It is possible to add new page content as background graphics by setting the
* second parameter in begin method to 'true' (e.g. writer.Begin(page, true)).
*
* @param page The page to write content.
*
* @param placement An optional flag indicating whether the new content should
* be added as a foreground or background layer to the existing page. By default, the new
* content will appear on top of the existing graphics.
*
* @param page_coord_sys An optional flag used to select the target coordinate system
* if true (default), the coordinates are relative to the lower-left corner of the page,
* otherwise the coordinates are defined in PDF user coordinate system (which may,
* or may not coincide with the page coordinates).
*
* @param compress An optional flag indicating whether the page content stream
* should be compressed. This may be useful for debugging content streams. Also
* some applications need to do a clear text search on strings in the PDF files.
* By default, all content streams are compressed.
*/
- (void)WriterBeginWithPage: (Page*)page placement:  (WriteMode)placement page_coord_sys:  (BOOL)page_coord_sys compress:  (BOOL)compress;
/**
* Begin writing an Element sequence to a new stream. Use this function to write
* Elements to a content stream other than the page. For example, you can create
* Form XObjects (See Section '4.9 Form XObjects' in PDF Reference for more details)
* pattern streams, Type3 font glyph streams, etc.
*
* @param doc - A low-level SDF/Cos document that will contain the new stream. You can
* access low-level document using PDFDoc::GetSDFDoc() or Obj::GetDoc() methods.
*
* @param compress An optional flag indicating whether the page content stream
* should be compressed. This may be useful for debugging content streams. Also
* some applications need to do a clear text search on strings in the PDF files.
* By default, all content streams are compressed.
*
* @note the newly created content stream object is returned when writing operations
* are completed (i.e. after the call to ElementWriter::End()).
*/
- (void)Begin: (Page*)page placement:  (WriteMode)placement page_coord_sys:  (BOOL)page_coord_sys;
- (void)WriterBeginWithSDFDoc: (SDFDoc*)doc compress:  (BOOL)compress;
/**
* Begin writing an Element sequence to a stream. Use this function to write
* Elements to a content stream which will replace an existing content stream in an
* object passed as a parameter.
*
* @param stream_obj_to_update - A low-level SDF stream object that will contain the new stream.
* Old stream inside that object will be discarded.
*
* @param compress An optional flag indicating whether the content stream
* should be compressed. This may be useful for debugging content streams. Also
* some applications need to do a clear text search on strings in the PDF files.
* By default, all content streams are compressed.
*
* @note The content stream object is returned when writing operations
* are completed (i.e. after the call to ElementWriter::End()).
*/
- (void)WriterBeginWithSDFObj: (Obj*)stream_obj_to_update compress:  (BOOL)compress;
/**
* Finish writing to a page
*
* @return A low-level stream object that was used to store Elements.
*/
- (Obj*)End;
/**
* Writes the Element to the content stream.
*/
- (void)WriteElement: (Element*)element;
/**
* A utility function that surrounds the given Element with a graphics state
* Save/Restore Element (i.e. in PDF content stream represented as 'q element Q').
*
* The function is equivalent to calling WriteElement three times:
*	 WriteElement(eSave);
*	 WriteElement(element);
*	 WriteElement(eRestore);
*
* where eSave is 'e_group_begin' and eRestore is 'e_group_end' Element
*
* The function is useful when XObjects such as Images and Forms are drawn on
* the page.
*/
- (void)WritePlacedElement: (Element*)element;
/**
* The Flush method flushes all pending Element writing operations.
* This method is typically only required to be called when intermixing
* direct content writing (i.e. WriteBuffer/WriteString) with Element writing.
*/
- (void)Flush;
/**
* Writes an arbitrary buffer to the content stream.
* This function can be used to insert comments, inline-image data, and
* chunks of arbitrary content to the output stream.
*/
- (void)WriteBuffer: (NSData*)data;
/**
* Writes an arbitrary string to the content stream.
* Serves the same purpose as WriteBuffer().
*/
- (void)WriteString: (NSString *)str;

- (id)init;

@end


/**
* Flattener is a optional PDFNet add-on that can be used to simplify and optimize
* existing PDF's to render faster on devices with lower memory and speeds.
*
* PDF documents can frequently contain very complex page description (e.g.
* thousands of paths, different shadings, color spaces, blend modes, large images
* etc.) that may not be suitable for interactive viewing on mobile devices.
* Flattener can be used to speed-up PDF rendering on mobile devices and on the Web
* by simplifying page content (e.g. flattening complex graphics into images) while
* maintaining vector text whenever possible.
*
* By using the FlattenMode::e_simple option each page in the PDF will be
* reduced to a single background image, with the remaining text over top in vector
* format. Some text may still get flattened, in particular any text that is clipped,
* or underneath, other content that will be flattened.
*
* On the other hand the FlattenMode::e_fast will not flatten simple content, such
* as simple straight lines, nor will it flatten Type3 fonts.
*
* @note 'Flattener' is available as a separately licensable add-on to PDFNet
* core license or for use via Cloud API (http://www.pdftron.com/pdfnet/cloud).
*
* @note See 'pdftron.PDF.Optimizer' for alternate approach to optimize PDFs with
* focus on file size reduction.
*/
@interface Flattener : NSObject
{


}





/**
* Flattener constructor
*/
- (id)init;
/**
* The output resolution, from 1 to 1000, in Dots Per Inch (DPI) at which to
* render elements which cannot be directly converted.
* the default value is 150 Dots Per Inch
* @param dpi the resolution in Dots Per Inch
*/
- (void)SetDPI: (unsigned int)dpi;
/**
* Specifies the maximum image size in pixels.
* @param max_pixels the maximum number of pixels an image can have.
*/
- (void)SetMaximumImagePixels: (unsigned int)max_pixels;
/**
* Specifies whether to leave images in existing compression, or as JPEG.
* @param jpg if true PDF will contain all JPEG images.
*/
- (void)SetPreferJPG: (BOOL)jpg;
/**
* Used to control how precise or relaxed text flattening is. When some text is
* preserved (not flattened to image) the visual appearance of the document may be altered.
* @param threshold the threshold setting to use.
*/
- (void)SetThreshold: (Threshold)threshold;
/**
* Process each page in the PDF, flattening content that matches the mode criteria.
* @param doc the document to flatten.
* @param mode indicates the criteria for which elements are flattened.
*/
- (void)Process: (PDFDoc*)doc mode:  (FlattenMode)mode;



@end


/**
* LinkInfo is a utility class used to store information about links when used along
* with the SetUrlExtraction feature.
*/
@interface LinkInfo : NSObject
{


}





- (void)setRect: (PDFRect*)value;
- (PDFRect*)getRect;
- (void)setUrl: (SWIGTYPE_p_pdftron__UString*)value;
- (SWIGTYPE_p_pdftron__UString*)getUrl;
- (id)init;

@end


/**
* Image2RGB is a filter that can decompress and normalize any PDF image stream
* (e.g. monochrome, CMYK, etc) into a raw RGB pixel stream.
*/
@interface Image2RGB : Filter





- (id)initWithImage_element: (Element*)image_element;
- (id)initWithImage_xobject: (Obj*)image_xobject;
- (id)initWithImage: (Image*)image;

@end


/**
* Image2RGBA is a filter that can decompress and normalize any PDF image stream
* (e.g. monochrome, CMYK, etc) into a raw RGBA pixel stream.
*/
@interface Image2RGBA : Filter





- (id)initWithImage_element: (Element*)image_element premultiply:  (BOOL)premultiply;
- (id)initWithImage_element: (Element*)image_element;
- (id)initWithImage_xobject: (Obj*)image_xobject premultiply:  (BOOL)premultiply;
- (id)initWithImage: (Image*)image premultiply:  (BOOL)premultiply;

@end


/**
* Highlights is used to store the necessary information and perform certain
* tasks in accordance with Adobe's Highlight standard, whose details can be
* found at:
*
* http://partners.adobe.com/public/developer/en/pdf/HighlightFileFormat.pdf
*
* In a nutshell, the Highlights class maintains a set of highlights.
* Each highlight contains three pieces of information:
*
* page: the number of the page this Highlight is on;
* position: the start position (text offset) of this Highlight;
* length: the length of this Highlight.
*
* Possible use case scenarios for Highlights include:
*  - Load a Highlight file (in XML format) and highlight the corresponding
*    texts in the viewer (e.g., if the viewer is implemented using PDFViewCtrl,
*    it can be achieved simply by calling PDFViewCtrl::SelectByHighlights()
*    method);
*  - Save the Highlight information (e.g., constructed by the TextSearch
*    class) to an XML file for external uses.
*
* Note:
*  - The Highlights class does not maintain the corresponding PDF document for
*    its highlights. It is the user's responsibility to match them up.
*  - The Highlights class ensures that each highlight it maintains is
*    unique (no two highlights have the same page, position and length values).
*  - The current implementation of Highlights only supports the 'characters'
*    encoding for 'units' as described in the format; the 'words' encoding is
*    not supported at this point.
*
*
* For a sample code, please take a look at the TextSearchTest sample project.
*/
@interface Highlights : NSObject
{


}





/**
* Constructor and destructor.
*/
- (id)init;
/**
* Load the Highlight information from a file. Note that the
* pre-existing Highlight information is discarded.
*
* @param file_name the name of the file to load from.
*/
- (void)Load: (NSString*)file_name;
/**
* Save the current Highlight information in the class to a file.
*
* @param file_name the name of the file to save to.
*/
- (void)Save: (NSString*)file_name;
/**
* Add highlights.
*
* @param hlts the Highlights instance containing the highlights to be added.
*/
- (void)Add: (Highlights*)hlts;
/**
* Clear the current Highlight information in the class.
*/
- (void)Clear;
/**
* Rewind the internal pointer to the first highlight.
*
* @param doc the PDF document to which the highlights correspond.
*
* @note the PDF document can be a dummy document unless GetCurrentQuads()
* is to be called.
*/
- (void)Begin: (PDFDoc*)doc;
/**
* Query if there is any subsequent highlight after the current highlight.
*/
- (BOOL)HasNext;
/**
* Move the current highlight to the next highlight.
*/
- (void)Next;
/**
* Get the page number of the current highlight.
*/
- (int)GetCurrentPageNumber;
/**
* Get the corresponding quadrangles of the current highlight.
*
* @param quads the output pointer to the resulting quadrangles.
*
* @return the number of the resulting quadrangles. Each quadrangle has
* eight doubles (x1, y1), (x2, y2), (x3, y3), (x4, y4) denoting the four
* vertices in counter-clockwise order.
*
* @note the 'quads' array is owned by the current Highlights and does not need to be
* explicitly released. Since a highlight may correspond to multiple quadrangles, e.g.,
* when it crosses a line, the number of resulting quadrangles may be larger than 1.
*/
- (VectorQuadPoint*)GetCurrentQuads;



@end


/**
* A class representing the current text selection.
*/
@interface Selection : NSObject
{


}





/**
* @return the page number containing the selected text.
*/
- (int)GetPageNum;
/**
* Returns the list of tight bounding quads in the current text selection.
* @param quads - Sets a pointer to an array of vertices representing
* a list of bounding quads for the selected text. Each bounding quad is
* represented using 8 numbers in an array of doubles. Each two consecutive
* values represent the x and y coordinates of a quad vertex and the four
* vertices are arranged counter-clockwisely,
*
*			3--------2
*			|        |
*			|        |
*			|        |
*			0--------1
*
* e.g., (quad[0], quad[1]) is the coordinate of vertex 0, and
* (quad[4], quad[5]) is the coordinate of vertex 2. Note that it is only ensured
* that the four vertices are arranged sequentially; it is possible in practice that
* (quad[0], quad[1]) is the coordinate of any vertex.
*
* @return the number of quads in 'quads' array.
*
* @note the 'quads' array is owned by the current selection and does
* not need to be explicitly released.
*/
- (VectorQuadPoint*)GetQuads;
/**
* @return the current text selection represented as an Unicode string.
*/
- (NSString*)GetAsUnicode;
/**
* @return the current text selection in HTML format. HTML text will
* contain styling information such as text color, font size, style etc.
* @note this function can be used to implement clipboard copy and paste
* that preserves text formating.
*/
- (NSString *)GetAsHtml;
- (id)init;

@end


/**
* The Optimizer class provides functionality for optimizing/shrinking
* output PDF files.
*
* 'pdftron.PDF.Optimizer' is an optional PDFNet Add-On utility class that can be
* used to optimize PDF documents by reducing the file size, removing redundant
* information, and compressing data streams using the latest in image compression
* technology. PDF Optimizer can compress and shrink PDF file size with the
* following operations:
* - Remove duplicated fonts, images, ICC profiles, and any other data stream.
* - Optionally convert high-quality or print-ready PDF files to small, efficient and web-ready PDF.
* - Optionally down-sample large images to a given resolution.
* - Optionally compress or recompress PDF images using JBIG2 and JPEG2000 compression formats.
* - Compress uncompressed streams and remove unused PDF objects.
*
* @note 'Optimizer' is available as a separately licensable add-on to PDFNet
* core license or for use via Cloud API (http://www.pdftron.com/pdfnet/cloud).
*
* @note See 'pdftron.PDF.Flattener' for alternate approach to optimize PDFs for fast
* viewing on mobile devices and the Web.
*/
@interface Optimizer : NSObject
{


}





/**
* Optimize the given document using the optimizers settings
* @param doc the document to optimize
* @param color_image_settings the image processing settings
* for color images
* @param grayscale_image_settings the image processing settings
* for grayscale images
* @param mono_image_settings the image processing settings
* for monochrome images
*/
+ (void)Optimize: (PDFDoc*)doc settings:  (OptimizerSettings*)settings;


@end


/**
* PDF page labels can be used to describe a page. This is used to
* allow for non-sequential page numbering or the addition of arbitrary
* labels for a page (such as the inclusion of Roman numerals at the
* beginning of a book). PDFNet PageLabel object can be used to specify
* the numbering style to use (for example, upper- or lower-case Roman,
* decimal, and so forth), the starting number for the first page,
* and an arbitrary prefix to be pre-appended to each number (for
* example, "A-" to generate "A-1", "A-2", "A-3", and so forth.)
*
* PageLabel corresponds to the PDF Page Label object (Section 8.3.1,
* 'Page Labels' in the PDF Reference Manual.
*
* Each page in a PDF document is identified by an integer page index
* that expresses the pages relative position within the document.
* In addition, a document may optionally define page labels to identify
* each page visually on the screen or in print. Page labels and page
* indices need not coincide: the indices are fixed, running consecutively
* through the document starting from 1 for the first page, but the
* labels can be specified in any way that is appropriate for the particular
* document. For example, if the document begins with 12 pages of front
* matter numbered in roman numerals and the remainder of the document is
* numbered in Arabic, the first page would have a page index of 1 and a
* page label of i, the twelfth page would have index 12 and label xii,
* and the thirteenth page would have index 13 and label 1.
*
* For purposes of page labeling, a document can be divided into labeling
* ranges, each of which is a series of consecutive pages using the same
* numbering system. Pages within a range are numbered sequentially in
* ascending order. A page's label consists of a numeric portion based
* on its position within its labeling range, optionally preceded by a
* label prefix denoting the range itself. For example, the pages in an
* appendix might be labeled with decimal numeric portions prefixed with
* the string "A-" and the resulting page labels would be "A-1", "A-2",
*
* @note
* There is no default numbering style; if no 'S' (Style) entry is present,
* page labels consist solely of a label prefix with no numeric portion.
* For example, if the 'P' entry (Prefix) specifies the label prefix
* "Appendix", each page is simply labeled "Appendix" with no page number.
* If the 'P' entry is also missing or empty, the page label is an empty
* string.
*
* Sample code (See PableLabelsTest sample project for examples):
* @code
* // Create a page labeling scheme that starts with the first page in
* // the document (page 1) and is using uppercase roman numbering
* // style.
* doc.SetPageLabel(1, PageLabel::Create(doc, PageLabel::e_roman_uppercase, "My Prefix ", 1));
*
* // Create a page labeling scheme that starts with the fourth page in
* // the document and is using decimal Arabic numbering style.
* // Also the numeric portion of the first label should start with number
* // 4 (otherwise the first label would be "My Prefix 1").
* PageLabel L2 = PageLabel::Create(doc, PageLabel::e_decimal, "My Prefix ", 4);
* doc.SetPageLabel(4, L2);
*
* // Create a page labeling scheme that starts with the seventh page in
* // the document and is using alphabetic numbering style. The numeric
* // portion of the first label should start with number 1.
* PageLabel L3 = PageLabel::Create(doc, PageLabel::e_alphabetic_uppercase, "My Prefix ", 1);
* doc.SetPageLabel(7, L3);
*
* // Read page labels from an existing PDF document.
* PageLabel label;
* for (int i=1; i<=doc.GetPageCount(); ++i) {
* label = doc.GetPageLabel(i);
* if (label.IsValid()) {
*   UString title = label.GetLabelTitle(i);
* }
*
* @endcode
*/
@interface PageLabel : NSObject
{


}





/**
* Creates a new PageLabel.
*
* @param doc A document to which the page label is added.
* @param style The numbering style for the label.
* @param prefix The string used to prefix the numeric portion of the
* page label.
* @param start_at the value to use when generating the numeric portion of the first
* label in this range; must be greater than or equal to 1.
*
* @return newly created PageLabel object.
*/
+ (PageLabel*)Create: (SDFDoc*)doc style:  (PageLabelStyle)style prefix:  (NSString*)prefix start_at:  (int)start_at;	/**
* Create a PageLabel and initialize it using given Cos/SDF object.
* @note The constructor does not copy any data, but is instead the logical
* equivalent of a type cast.
*/
- (id)initWithL: (Obj*)l first_page:  (int)first_page last_page:  (int)last_page;

/**
* @return whether this is a valid (non-null) PageLabel. If the
* function returns false the underlying SDF/Cos object is null or is
* not valid and the PageLabel object should be treated as null as well.
*/
- (BOOL)IsValid;
/**
* @return the full label title that is in effect for the given page.
* If there is no label object in effect, this method returns an
* empty string.
*/
- (NSString*)GetLabelTitle: (int)page_num;
/**
* Sets the numbering style for the label.
*
* @param style the numbering style for the label.
*
* You may use label style to customize the page numbering schemes
* used throughout a document. There are three numbering formats:
*  - decimal (often used for normal page ranges)
*  - roman (often used for front matter such as a preface)
*  - alphabetic (often used for back matter such as appendices)
*
* @note
* There is no default numbering style; if no 'S' (Style) entry is present,
* page labels consist solely of a label prefix with no numeric portion.
*/
- (void)SetStyle: (PageLabelStyle)style;
/**
* @return page numbering style.
*/
- (PageLabelStyle)GetStyle;
/**
* @return the string used to prefix the numeric portion of
* the page label
*/
- (NSString*)GetPrefix;
/**
* @param prefix the string used to prefix the numeric portion of
* the page label.
*/
- (void)SetPrefix: (NSString*)prefix;
/**
* @return the value to use when generating the numeric portion of
* the first label in this range; must be greater than or equal to 1.
*/
- (int)GetStart;
/**
* @param start_at the value to use when generating the numeric
* portion of the first label in this range; must be greater than
* or equal to 1.
*/
- (void)SetStart: (int)start_at;
/**
* @return the first page in the range associated with this label
* or -1 if the label is not associated with any page.
*/
- (int)GetFirstPageNum;
/**
* @return the last page in the range associated with this label
* or -1 if the label is not associated with any page.
*/
- (int)GetLastPageNum;
/**
* @return The pointer to the underlying SDF/Cos object.
*/
- (Obj*)GetSDFObj;


@end


/**
* PageSet is a container of page numbers ordered following a linear sequence.
* The page numbers are integers and must be greater than zero. Duplicates are allowed.
*
* (NOTE: This is not a mathematical set)
*/
@interface PageSet : NSObject
{


}





/**
* Default constructor. Constructs 'PageSet' with no pages
*/
- (id)init;
/**
* Construct a set of pages with just one number
*
* @see AddPage
*/
- (id)initWithOne_page: (int)one_page;
/**
* Construct a range of pages
*
* @see AddRange
*/
- (id)initWithRange_start: (int)range_start range_end:  (int)range_end filter:  (PageSetFilter)filter;
/**
* Add a value to the sequence.
*
* @param one_page The page number being added
*/
- (void)AddPage: (int)one_page;
/**
* Add a range of values to the sequence. Reverse ordering is legal.
*
* @param range_start The starting value in the range
* @param range_end The ending value in the range
* @param filter
*		-e_all: Default, includes all pages in the range
*		-e_odd: Includes odd numbers in the range (discards even numbers)
*		-e_even: Includes even numbers in the range (discards odd numbers)
*/
- (void)AddRange: (int)range_start range_end:  (int)range_end filter:  (PageSetFilter)filter;





@end


/**
* PDFDocInfo is a high-level utility class that can be used
* to read and modify document's metadata.
*/
@interface PDFDocInfo : NSObject
{


}





/**
* @return The documents title.
*/
- (NSString*)GetTitle;
/**
* @return SDF/Cos string object representing document's title.
*/
- (Obj*)GetTitleObj;
/**
* Set documents title.
* @param title New title of the document.
*/
- (void)SetTitle: (NSString*)title;
/**
* @return The name of the person who created the document.
*/
- (NSString*)GetAuthor;
/**
* @return SDF/Cos string object representing document's author.
*/
- (Obj*)GetAuthorObj;
/**
* Set the author of the document.
* @param The name of the person who created the document.
*/
- (void)SetAuthor: (NSString*)author;
/**
* @return The subject of the document.
*/
- (NSString*)GetSubject;
/**
* @return SDF/Cos string object representing document's subject.
*/
- (Obj*)GetSubjectObj;
/**
* Set the subject of the document
* @param subject The subject of the document.
*/
- (void)SetSubject: (NSString*)subject;
/**
* @return Keywords associated with the document.
*/
- (NSString*)GetKeywords;
/**
* @return SDF/Cos string object representing document's keywords.
*/
- (Obj*)GetKeywordsObj;
/**
* Set keywords associated with the document.
* @param Keywords Keywords associated with the document.
*/
- (void)SetKeywords: (NSString*)keywords;
/**
* @return If the document was converted to PDF from another
* format, the name of the application that created the original
* document from which it was converted.
*/
- (NSString*)GetCreator;
/**
* @return SDF/Cos string object representing document's creator.
*/
- (Obj*)GetCreatorObj;
/**
* Set documents creator.
* @param creator The name of the application that created
* the original document.
*/
- (void)SetCreator: (NSString*)creator;
/**
* @return If the document was converted to PDF from another format,
* the name of the application (for example, Distiller) that
* converted it to PDF.
*/
- (NSString*)GetProducer;
/**
* @return SDF/Cos string object representing document's producer.
*/
- (Obj*)GetProducerObj;
/**
* Set documents producer.
* @param producer The name of the application that generated PDF.
*/
- (void)SetProducer: (NSString*)producer;
/**
* @return The date and time the document was created,
* in human-readable form.
*/
- (Date*)GetCreationDate;
/**
* Set documents creation date.
* @param creation_date The date and time the document was created.
*/
- (void)SetCreationDate: (Date*)creation_date;
/**
* @return The date and time the document was most recently
* modified, in human-readable form.
*/
- (Date*)GetModDate;
/**
* Set documents modification date.
* @param mod_date The date and time the document was most
* recently modified.
*/
- (void)SetModDate: (Date*)mod_date;
/**
* @return documents SDF/Cos 'Info' dictionary or NULL if
* the info dictionary is not available.
*/
- (Obj*)GetSDFObj;	/**
* PDFDocInfo constructor. Typically this constructor is
* never used since it is easier to obtain DocInfo using
* PDFDoc.GetDocInfo()
*/
- (id)initWithTr: (Obj*)tr;



@end


/**
* PDFDocViewPrefs is a high-level utility class that can be
* used to control the way the document is to be presented on
* the screen or in print.
*
* PDFDocViewPrefs class corresponds to PageMode, PageLayout, and
* ViewerPreferences entries in the documents catalog. For more
* details please refer to section 8.1 'Viewer Preferences' in
* PDF Reference Manual.
*/
@interface PDFDocViewPrefs : NSObject
{


}





/**
* A utility method used to set the fist page displayed after
* the document is opened. This method is equivalent to
* PDFDoc::SetOpenAction(goto_action).
*
* If OpenAction is not specified the document should be
* opened to the top of the first page at the default magnification
* factor.
*
* @param dest A value specifying the page destination to be
* displayed when the document is opened.
*
* Example:
* @code
* Destination dest = Destination::CreateFit(page);
* pdfdoc.GetViewPrefs().SetInitialPage(dest);
* @endcode
*/
- (void)SetInitialPage: (Destination*)dest;
/**
* Sets PageMode property and change the value of the
* PageMode key in the Catalog dictionary.
*
* @param mode New PageMode setting. Default value is e_UseNone.
*/
- (void)SetPageMode: (PageMode)mode;
/**
* @return The value of currently selected PageMode property.
*/
- (PageMode)GetPageMode;
/**
* Sets PageLayout property and change the value of the
* PageLayout key in the Catalog dictionary.
*
* @param mode New PageLayout setting. Default value is
* e_SinglePage.
*/
- (void)SetLayoutMode: (PageLayout)layout;
/**
* @return The value of currently selected PageLayout property.
*/
- (PageLayout)GetLayoutMode;
/**
* Sets the value of given ViewerPref property.
*
* @param pref the ViewerPref property type to modify.
* @param value The new value for the property.
*/
- (void)SetPref: (ViewerPref)pref value:  (BOOL)value;
/**
* @return the value of given ViewerPref property.
* @param pref the ViewerPref property type to query.
*/
- (BOOL)GetPref: (ViewerPref)pref;
/**
* Set the documents page mode, specifying how to display the
* document on exiting full-screen mode.
*
* @param mode PageMode used after exiting full-screen mode.
* Default value: e_UseNone.
*
* @note This entry is meaningful only if the value of the
* PageMode is set to e_FullScreen; it is ignored otherwise.
*/
- (void)SetNonFullScreenPageMode: (PageMode)mode;
/**
* @return the PageMode used after exiting full-screen mode.
* @note This entry is meaningful only if the value of the
* PageMode is set to e_FullScreen; it is ignored otherwise.
*/
- (PageMode)GetNonFullScreenPageMode;
/**
* Sets the predominant reading order for text.
*
* This flag has no direct effect on the documents contents
* or page numbering but can be used to determine the relative
* positioning of pages when displayed side by side or
* printed n-up.
*
* @param left_to_right - true if the predominant reading
* order for text is from left to right and false if it is
* right to left (including vertical writing systems, such
* as Chinese, Japanese, and Korean).
* Default value: left_to_right is true.
*/
- (void)SetDirection: (BOOL)left_to_right;
/**
* @return true is the predominant reading order for text
* is left to right, false otherwise. See SetDirection() for
* more information.
*/
- (BOOL)GetDirection;
/**
* Sets the page boundary representing the area of a page
* to be displayed when viewing the document on the screen.
*
* @param box page boundary displayed when viewing the document
* on the screen. By default, PDF viewers will display the
* crop-box.
*/
- (void)SetViewArea: (Box)box;
/**
* @return the page boundary representing the area of a page
* to be displayed when viewing the document on the screen.
*/
- (Box)GetViewArea;
/**
* Sets the page boundary to which the contents of a page are
* to be clipped when viewing the document on the screen.
*
* @param box screen clip region. The default value is
* page crop-box.
*/
- (void)SetViewClip: (Box)box;
/**
* @return the page boundary to which the contents of a page
* are to be clipped when viewing the document on the screen.
*/
- (Box)GetViewClip;
/**
* Sets the page boundary representing the area of a page to
* be rendered when printing the document.
*
* @param box printing region. The default value is page
* crop-box.
*/
- (void)SetPrintArea: (Box)box;
/**
* @return the page boundary representing the area of a page
* to be rendered when printing the document.
*/
- (Box)GetPrintArea;
/**
* Sets the page boundary to which the contents of a page are
* to be clipped when printing the document.
*
* @param box printing clip region. The default value is page
* crop-box.
*/
- (void)SetPrintClip: (Box)box;
/**
* @return the page boundary to which the contents of a page
* are to be clipped when printing the document.
*/
- (Box)GetPrintClip;
/**
* @return documents SDF/Cos 'ViewerPreferences' dictionary
* or NULL if the object is not present.
*/
- (Obj*)GetSDFObj;	/**
* PDFDocViewPrefs constructor. Typically this constructor is
* never used since it is easier to obtain PDFDocViewPrefs using
* PDFDoc.GetViewPrefs()
*/
- (id)initWithTr: (Obj*)tr;



@end


/**
* PDFDoc is a high-level class describing a single PDF (Portable Document
* Format) document. Most applications using PDFNet will use this class to
* open existing PDF documents, or to create new PDF documents from scratch.
*
* The class offers a number of entry points into the document. For example,
*  - To access pages use pdfdoc.GetPageIterator() or pdfdoc.PageFind(page_num).
*  - To access form fields use pdfdoc.GetFieldIterator() or pdfdoc.FieldFind(name).
*  - To access document's meta-data use pdfdoc.GetDocInfo().
*  - To access the outline tree use pdfdoc.GetFirstBookmark().
*  - To access low-level Document Catalog use pdfdoc.GetRoot().
*  ...
*
* The class also offers utility methods to slit and merge PDF pages,
* to create new pages, to flatten forms, to change security settings, etc.
*/
@interface PDFDoc : NSObject
{


}





/**
* Default constructor. Creates an empty new document.
*/
- (id)init;
/**
* Create a PDF document from an existing SDF/Cos document.
*
* @param sdfdoc a pointer to the SDF document. Created PDFDoc will
* take the ownership of the low-level document.
*
* @note the SDFDoc will become invalid.  If you would
* like to access the low level document use GetSDFDoc
*/
- (id)initWithSdfdoc: (SDFDoc*)sdfdoc;
/**
* Open an existing PDF document
*
* @param filepath - pathname to the file.
*
* @note Make sure to call InitSecurityHandler() after PDFDoc(...) in case
* a document is encrypted
*/
- (id)initWithFilepath: (NSString*)filepath;
/**
* Open an existing PDF document
*
* @param stream - input stream containing a serialized document. The input stream may be a
* random-access file, memory buffer, slow HTTP connection etc.
*
* @note if the input stream doesn't support Seek() operation the document will load whole
* data stream in memory before parsing. In case of linearized PDF, the document may be parsed
* on-the-fly while it is being loaded in memory. Note that since StdFile implements Seek()
* interface, the document does not have to be fully in memory before it is used.
*
* @note Make sure to call InitSecurityHandler() after PDFDoc(...) for encrypted documents.
*/
- (id)initWithStream: (Filter*)stream;
/**
* Open a SDF/Cos document from a memory buffer.
* @note the document should be fully loaded in the memory buffer.
* @note the buffer ownership is not transfered to the document so the user should
* clean-up any allocated memory if necessary.
*
* @param buf - a memory buffer containing the serialized document
* @param buf_size - the size of memory buffer.
*/
- (id)initWithBuf: (NSData*)buf buf_size:  (unsigned long)buf_size;
/**
*	Close PDFDoc
*/
- (void)Close;
/**
* @return true if the document is/was originally encrypted false otherwise.
*/
- (BOOL)IsEncrypted;
/**
* Initializes document's SecurityHandler. This version of InitSecurityHandler()
* works with Standard and Custom PDF security and can be used in situations where
* the password is obtained dynamically via user feedback. See EncTest sample for
* example code.
*
* This function should be called immediately after an encrypted
* document is opened. The function does not have any side effects on
* documents that are not encrypted.
*
* If the security handler was successfully initialized it can be later obtained
* using GetSecurityHandler() method.
*
* @exception An exception is thrown if the matching handler for document's
* security was not found in the global SecurityManager. In this case, you
* need to register additional custom security handlers with the global
* SecurityManager (using SecurityManagerSingleton).
*
* @return true if the SecurityHandler was successfully initialized (this
* may include authentication data collection, verification etc.),
* false otherwise.
*
* @param custom_data An optional parameter used to specify custom data
* that should be passed in SecurityHandler::Initialize() callback.
*/
- (BOOL)InitSecurityHandler;
/**
* Initializes document's SecurityHandler using the supplied
* password. This version of InitSecurityHandler() assumes that
* document uses Standard security and that a password is specified
* directly.
*
* This function should be called immediately after an encrypted
* document is opened. The function does not have any side effects on
* documents that are not encrypted.
*
* If the security handler was successfully initialized, it can be later
* obtained using GetSecurityHandler() method.
*
* @return true if the given password successfully unlocked the document,
* false otherwise.
*
* @exception An exception is thrown if the document's security Filter is
* not 'Standard'. In this case, you need to register additional custom
* security handlers with the global SecurityManager (SecurityManagerSingleton).
*
* @param password Specifies the password used to open the document without
* any user feedback. If you would like to dynamically obtain the password,
* you need to derive a custom class from StdSecurityHandler() and use
* InitSecurityHandler() without any parameters. See EncTest sample
* for example code.
*
* @param password_len An optional parameter used to specify the size of
* the password buffer, in bytes. If the 'password_sz' is 0, or if the parameter
* is not specified, the function assumes that the string is null terminated.
*/
- (BOOL)InitStdSecurityHandlerWithPassword: (NSString *)password password_sz:  (int)password_sz;
- (BOOL)InitStdSecurityHandler: (NSString *)password;
/**
* @return Currently selected SecurityHandler.
*
* @note InitSecurityHandler() should be called before GetSecurityHandler()
* in order to initialize the handler.
*
* @note Returned security handler can be modified in order to change the
* security settings of the existing document. Changes to the current handler
* will not invalidate the access to the original file and will take effect
* during document Save().
*
* @note If the security handler is modified, document will perform a full save
* even if e_incremental was given as a flag in Save() method.
*/
- (SecurityHandler*)GetSecurityHandler;
/**
* The function sets a new SecurityHandler as the current security handler.
*
* @param - new SecurityHandler
*
* @note Setting a new security handler will not invalidate the access to
* the original file and will take effect during document Save().
*
* @note If the security handler is modified, document will perform a full save
* even if e_incremental was given as a flag in Save() method.
*/
- (void)SetSecurityHandler: (SecurityHandler*)handler;
/**
* This function removes document security.
*/
- (void)RemoveSecurity;
/**
* Indicates whether this documents contains any digital signatures.
* @return True if a digital signature is found in this PDFDoc.
*/
- (BOOL)HasSignatures;
/**
* Adds a signature handler to the signature manager.
*
* @param signature_handler The signature handler instance to add to the signature manager.
*
* @return A unique ID representing the SignatureHandler within the SignatureManager.
*/
- (SignatureHandlerId)AddSignatureHandler: (SignatureHandler*)signature_handler;
/**
* Removes a signature handler from the signature manager.
*
* @param signature_handler_id The unique id of the signature handler to remove.
*/
- (void)RemoveSignatureHandler: (unsigned long)signature_handler_id;
/**
* Gets the associated signature handler instance from the signature manager by looking it up with the handler name.
*
* @param signature_handler_id The unique id of the signature handler to get.
*
* @return The signature handler instance if found, otherwise NULL.
*/
- (SignatureHandler*)GetSignatureHandler: (SignatureHandlerId)signature_handler_id;
/**
* @return The class representing document information metadata.
* (i.e. entries in the document information dictionary).
*/
- (PDFDocInfo*)GetDocInfo;
/**
* @return Viewer preferences for this document.
*
* PDFDocViewPrefs is a high-level utility class that can be
* used to control the way the document is to be presented on
* the screen or in print.
*/
- (PDFDocViewPrefs*)GetViewPrefs;
/**
* Call this function to determine whether the document has been modified since
* it was last saved.
*
* @return - true if document was modified, false otherwise
*/
- (BOOL)IsModified;
/**
* Call this function to determine whether the document is represented in
* linearized (fast web view) format.
*
* @return - true if document is stored in fast web view format, false otherwise.
*
* @note any changes to the document can invalidate linearization. The function will
* return 'true' only if the original document is linearized and if it is not
* modified.
*
* In order to provide good performance over relatively slow communication links,
* PDFNet can generate PDF documents with linearized objects and hint tables that
* can allow a PDF viewer application to download and view one page of a PDF file
* at a time, rather than requiring the entire file (including fonts and images) to
* be downloaded before any of it can be viewed.
*
* To save a document in linearized (fast web view) format you only need to pass
* 'Doc.SaveOptions.e_linearized' flag in the Save method.
*/
- (BOOL)IsLinearized;
/**
* Saves the document to a file.
*
* If a full save is requested to the original path, the file is saved to a file
* system-determined temporary file, the old file is deleted, and the temporary file
* is renamed to path.
*
* A full save with remove unused or linearization option may re-arrange object in
* the cross reference table. Therefore all pointers and references to document objects
* and resources should be re acquired in order to continue document editing.
*
* In order to use incremental save the specified path must match original path and
* e_incremental flag bit should be set.
*
* @param path - The full path name to which the file is saved.
* @param flags - A bit field composed of an OR of SDFDoc::SaveOptions values.
* @param progress - A pointer to the progress interface. NULL if progress tracking is not required.
*
* @exception - if the file can't be opened for saving or if there is a problem during Save
*	an Exception object will be thrown.
*
* @note a write lock must be acquired before saving in a multithreaded environment.
*/
- (void)SaveToFile: (NSString*)path flags:  (unsigned int)flags;
/**
* Saves the document to a memory buffer.
*
* @param out_buf a pointer to the buffer containing the serialized version of the
* document. (C++ Note) The buffer is owned by a document and the client doesn't need to
* do any initialization or cleanup.
* @param out_buf_size the size of the serialized document (i.e. out_buf) in bytes.
*
* @param flags - A bit field composed of an OR of SDFDoc::SaveOptions values. Note that
* this method ignores e_incremental flag.
* @param progress - A pointer to the progress interface. NULL if progress tracking is not required.
*
* @exception - if there is a problem during Save an Exception object will be thrown.
*/
- (NSData*)SaveToBuf: (unsigned int)flags;
/**
* Saves the document to a stream.
*
* @param stream The output stream where to write data.
* @param flags - A bit field composed of an OR of the SDFDoc::SaveOptions values.
* @param progress - A pointer to the progress interface. NULL if progress tracking is not required.
* @param header - File header. A new file header is set only during full save. See also GetHeader()
*
* @exception - if there is a problem during Save an Exception object will be thrown.
*/
- (void)Save: (Filter*)stream flags:  (unsigned int)flags;
/**
* @return an iterator to the first page in the document.
* Use the Next() method on the returned iterator to traverse all pages in the document.
* For example:
* @code
*   PageIterator itr = pdfdoc.GetPageIterator();
*   while (itr.HasNext()) { //  Read every page
*      Page page = itr.Current();
*      // ...
*      itr.Next()
*   }
* @endcode
*
* For full sample code, please take a look at ElementReader, PDFPageTest and PDFDraw sample projects.
*/
- (PageIterator*)GetPageIterator: (unsigned int)page_number;
/**
* @param page_number - the page number in document's page sequence. Page numbers
* in document's page sequence are indexed from 1.
*
* @return a Page corresponding to a given page number, or null (invalid page)
* if the document does not contain the given page number.
*
* For example:
* @code
*   Page page = pdfdoc.GetPage(page_num);
*   if (page == null) return; //  Page not found
* @endcode
*/
- (Page*)GetPage: (unsigned int)page_number;
/**
* @param page_itr - the PageIterator to the page that should be removed
* A PageIterator for the given page can be obtained using PDFDoc::Find(page_num)
* or using direct iteration through document's page sequence.
*/
- (void)PageRemove: (PageIterator*)page_itr;
/**
* Insert/Import a single page at a specific location in the page sequence.
*
* @param where - The location in the page sequence indicating where to insert
* the page. The page is inserted before the specified location.
*
* @param page - A page to insert.

* @note Invalidates all PageIterators pointing to the document.
*/
- (void)PageInsert: (PageIterator*)where page:  (Page*)page;
/**
* Inserts a range of pages from specified PDFDoc
*
* @param insertBeforeThisPage - the destination of the insertion. If less than or equal to 1,
* the pages are added to the beginning of the document. If larger than the number of pages
* in the destination document, the pages are appended to the document.
* @param sourceDoc - source PDFDoc to insert from
* @param startPage - start of the page number to insert
* @param endPage - end of the page number to insert
* @param flag - specifies insert options
* @param progress - A pointer to the progress interface. NULL if progress tracking is not required.
*/
- (void)InsertPages: (int)insertBeforeThisPage sourceDoc:  (PDFDoc*)sourceDoc startPage:  (int)startPage endPage:  (int)endPage flag:  (InsertFlag)flag;
/**
* Inserts a range of pages from specified PDFDoc using PageSet
*
* @param insertBeforeThisPage - the destination of the insertion. If less than or equal to 1,
* the pages are added to the beginning of the document. If larger than the number of pages
* in the destination document, the pages are appended to the document.
* @param sourceDoc - source PDFDoc to insert from
* @param sourcePageSet - a collection of the page number to insert
* @param flag - specifies insert options
* @param progress - A pointer to the progress interface. NULL if progress tracking is not required.
*/
- (void)InsertPagesWithPageSet: (int)insertBeforeThisPage sourceDoc:  (PDFDoc*)sourceDoc sourcePageSet:  (PageSet*)sourcePageSet flag:  (InsertFlag)flag;
/**
* Moves a range of pages from specified PDFDoc. Pages are deleted from source document after move.
*
* @param moveBeforeThisPage - the destination of the move. If less than or equal to 1,
* the pages are moved to the beginning of the document. If larger than the number of pages
* in the destination document, the pages are moved to the end of the document.
* @param sourceDoc - source PDFDoc to move from
* @param startPage - start of the page number to move
* @param endPage - end of the page number to move
* @param flag - specifies insert options
* @param progress - A pointer to the progress interface. NULL if progress tracking is not required.
* @note MovePages function does not save sourceDoc. It merely delete pages in memeory. For permanent changes,
* PDFDoc::Save should be used to save sourceDoc after function exists.
*/
- (void)MovePages: (int)moveBeforeThisPage sourceDoc:  (PDFDoc*)sourceDoc startPage:  (int)startPage endPage:  (int)endPage flag:  (InsertFlag)flag;
/**
* Moves a range of pages from specified PDFDoc. Pages are deleted from source document after move.
*
* @param moveBeforeThisPage - the destination of the move. If less than or equal to 1,
* the pages are moved to the beginning of the document. If larger than the number of pages
* in the destination document, the pages are moved to the end of the document.
* @param sourceDoc - source PDFDoc to move from
* @param sourcePageSet - a collection of the page number to move
* @param flag - specifies insert options
* @param progress - A pointer to the progress interface. NULL if progress tracking is not required.
* @note MovePages function does not save sourceDoc. It merely delete pages in memeory. For permanent changes,
* PDFDoc::Save should be used to save sourceDoc after function exists.
*/
- (void)MovePagesWithPageSet: (int)moveBeforeThisPage sourceDoc:  (PDFDoc*)sourceDoc sourcePageSet:  (PageSet*)sourcePageSet flag:  (InsertFlag)flag;
/**
* Adds a page to the beginning of a document's page sequence.
* @param page - a page to prepend to the document
* Invalidates all PageIterators pointing to the document.
*/
- (void)PagePushFront: (Page*)page;
/**
* Adds a page to the end of a document's page sequence.
* @param page - a page to append to the document
* @note Invalidates all PageIterators pointing to the document.
*/
- (void)PagePushBack: (Page*)page;
/**
* The function imports a list of pages to this document. Although a list of pages
* can be imported using repeated calls to PageInsert(), PageImport will not import
* duplicate copies of resources that are shared across pages (such as fonts, images,
* colorspaces etc). Therefore this method is recommended when a page import list
* consists of several pages that share the same resources.
*
* @param pages A list of pages to import. All pages should belong to the same source document.
* @param import_bookmarks An optional flag specifying whether any bookmark items
* pointing to pages in the import list should be merged with the target (i.e. this)
* document.
*
* @return a list of imported pages. Note that imported pages are not placed in the
* document page sequence. This can be done using methods such as PageInsert(),
* PagePushBack(), etc.
*/
- (VectorPage*)ImportPages: (VectorPage*)pages import_bookmarks:  (BOOL)import_bookmarks;
/**
* Create a new, empty page in the document. You can use PageWriter to fill the
* page with new content. Finally the page should be inserted at specific
* place within document page sequence using PageInsert/PagePushFront/PagePushBack
* methods.
*
* @return A new, empty page.
*
* @note the new page still does not belong to document page sequence and should be
* subsequently placed at a specific location within the sequence.
*
* @param media_box A rectangle, expressed in default user space units, defining
* the boundaries of the physical medium on which the page is intended to be
* displayed or printed. A user space units is 1/72 of an inch. If media_box is
* not specified the default dimensions of the page are 8.5 x 11 inches (or
* 8.5*72, 11*72 units).
*
* <p>The following is a listing of some standard U.S. page sizes:</p>
*  <ul>
*    <li>Letter    = Rect(0, 0, 612, 792)
*    <li>Legal	    = Rect(0, 0, 612, 1008)
*    <li>Ledger	= Rect(0, 0, 1224, 792)
*    <li>Tabloid   = Rect(0, 0, 792, 1224)
*    <li>Executive	= Rect(0, 0, 522, 756)
* </ul>
*
* <p>The following is a listing of ISO standard page sizes:</p>
*  <ul>
*    <li> 4A0 = Rect(0, 0, 4768, 6741)
*    <li> 2A0 = Rect(0, 0, 3370, 4768)
*    <li> A0 =  Rect(0, 0, 2384, 3370)
*    <li> A1 =  Rect(0, 0, 1684, 2384)
*    <li> A2 =  Rect(0, 0, 1191, 1684)
*    <li> A3 =  Rect(0, 0, 842,  1191)
*    <li> A4 =  Rect(0, 0, 595,  842)
*    <li> A5 =  Rect(0, 0, 420,  595)
*    <li> A6 =  Rect(0, 0, 298,  420)
*    <li> A7 =  Rect(0, 0, 210,  298)
*    <li> A8 =  Rect(0, 0, 147,  210)
*    <li> A9 =  Rect(0, 0, 105,  147)
*    <li> A10 = Rect(0, 0, 74,   105)
*    <li> B0 =  Rect(0, 0, 2835, 4008)
*    <li> B1 =  Rect(0, 0, 2004, 2835)
*    <li> B2 =  Rect(0, 0, 1417, 2004)
*    <li> B3 =  Rect(0, 0, 1001, 1417)
*    <LI> B4 =  Rect(0, 0, 709,  1001)
*    <LI> B5 =  Rect(0, 0, 499,  709)
*    <LI> B6 =  Rect(0, 0, 354,  499)
*    <LI> B7 =  Rect(0, 0, 249,  354)
*    <LI> B8 =  Rect(0, 0, 176,  249)
*    <LI> B9 =  Rect(0, 0, 125,  176)
*    <li> B10 = Rect(0, 0, 88,   125)
*    <li> C0 =  Rect(0, 0, 2599, 3677)
*    <li> C1 =  Rect(0, 0, 1837, 2599)
*    <li> C2 =  Rect(0, 0, 1298, 1837)
*    <li> C3 =  Rect(0, 0, 918,  1298)
*    <li> C4 =  Rect(0, 0, 649,  918)
*    <li> C5 =  Rect(0, 0, 459,  649)
*    <li> C6 =  Rect(0, 0, 323,  459)
*    <li> C7 =  Rect(0, 0, 230,  323)
*    <li> C8 =  Rect(0, 0, 162,  230)
*    <li> C9 =  Rect(0, 0, 113,  162)
*    <li>C10 =  Rect(0, 0, 79,   113)
* </ul>
*/
- (Page*)PageCreate: (PDFRect*)media_box;
/**
* @return - the first Bookmark from the documents outline tree. If the
* Bookmark tree is empty the underlying SDF/Cos Object is null and returned
* Bookmark is not valid (i.e. Bookmark::IsValid() returns false).
*/
- (Bookmark*)GetFirstBookmark;
/**
* Adds/links the specified Bookmark to the root level of documents outline tree.
* @note parameter 'root_bookmark' must not be linked (must not be belong) to
* a bookmark tree.
*/
- (void)AddRootBookmark: (Bookmark*)root_bookmark;
/**
* @return - A dictionary representing the Cos root of the document (document's trailer)
*/
- (Obj*)GetTrailer;
/**
* @return - A dictionary representing the Cos root of the document (/Root entry
* within the trailer dictionary)
*/
- (Obj*)GetRoot;
/**
* @return - A dictionary representing the root of the low level page-tree
*/
- (Obj*)GetPages;
/**
* @return the number of pages in the document.
*/
- (int)GetPageCount;
/**
* An interactive form (sometimes referred to as an AcroForm) is a
* collection of fields for gathering information interactively from
* the user. A PDF document may contain any number of fields appearing
* on any combination of pages, all of which make up a single, global
* interactive form spanning the entire document.
*
* The following methods are used to access and manipulate Interactive form
* fields (sometimes referred to as AcroForms).
*
* @return an iterator to the first Field in the document.
*
* The list of all Fields present in the document can be traversed as follows:
* @code
* FieldIterator itr = pdfdoc.GetFieldIterator();
* for(; itr.HasNext(); itr.Next()) {
*   Field field = itr.Current();
*   Console.WriteLine("Field name: {0}", field.GetName());
*  }
* @endcode
*
* For a full sample, please refer to 'InteractiveForms' sample project.
*/
- (FieldIterator*)GetFieldIterator;
/**
* field_name - a string representing the fully qualified name of
* the field (e.g. "employee.name.first").
*
* @return a FieldIterator referring to an interactive Field
* or to invalid field if the field name was not found. If a given field name was
* not found itr.HasNext() will return false. For example:
*
* @code
* FieldIterator itr = pdfdoc.FieldFind("name");
* if (itr.HasNext()) {
*   Console.WriteLine("Field name: {0}", itr.Current().GetName());
* }
* else { ...field was not found... }
* @endcode
*/
- (FieldIterator*)GetFieldIteratorWithName: (NSString*)field_name;
- (TRNField*)GetField: (NSString*)field_name;
/**
* Create a new interactive form Field.
* @return the new form Field.
*
* @param field_name a string representing the fully qualified name of the
* field (e.g. "employee.name.first"). field_name must be either a unique name or
* equal to an existing terminal field name.

* @param type field type (e.g. Field::e_text, Field::e_button, etc.)
* @param field_value
* @param def_field_value
*
* @exception if 'field_name' is equal to an existing non-terminal field name an
* exception is thrown.
*/
- (TRNField*)FieldCreateWithObj: (NSString*)field_name type:  (FieldType)type field_value:  (Obj*)field_value def_field_value:  (Obj*)def_field_value;
- (TRNField*)FieldCreate: (NSString*)field_name type:  (FieldType)type field_value:  (Obj*)field_value;
- (TRNField*)FieldCreateWithString: (NSString*)field_name type:  (FieldType)type field_value:  (NSString*)field_value def_field_value:  (NSString*)def_field_value;
/**
* Regenerates the appearance stream for every widget annotation in the document
* Call this method if you modified field's value and would like to update
* field's appearances.
*/
- (void)RefreshFieldAppearances;
/**
* Flatten all annotations in the document.
* @param forms_only if false flatten all annotations, otherwise flatten
* only form fields.
*/
- (void)FlattenAnnotations: (BOOL)forms_only;
/**
* @return the AcroForm dictionary located in "/Root" or NULL if dictionary is not present.
*/
- (Obj*)GetAcroForm;
/**
* Extract form data and/or annotations to FDF
* @param flag - specifies extract options
* @return a pointer to the newly created FDF file with an interactive data.
*/
- (FDFDoc*)FDFExtract: (ExtractFlag)flag;
/**
* Import form data from FDF file to PDF interactive form.
* @param fdf_doc - a pointer to the FDF file
*/
- (void)FDFMerge: (FDFDoc*)fdf_doc;
/**
* @return Action that is triggered when the document is opened.
* The returned action can be either a destination or some other kind
* of Action (see Section 8.5, 'Actions' in PDF Reference Manual).
*
* @note if the document does not nave associated action the returned Action
* will be null (i.e. Action.IsValid() returns false)
*/
- (Action*)GetOpenAction;
/**
* Sets the Action that will be triggered when the document is opened.
*
* @param action A new Action that will be triggered when the document is opened.
* An example of such action is a GoTo Action that takes the user to a given
* location in the document.
*/
- (void)SetOpenAction: (Action*)action;
/**
* Associates a file attachment with the document.
*
* The file attachment will be displayed in the user interface of a viewer application
* (in Acrobat this is File Attachment tab). The function differs from
* Annot.CreateFileAttachment() because it associates the attachment with the
* whole document instead of an annotation on a specific page.
*
* @param file_key A key/name under which the attachment will be stored.
* @param embedded_file Embedded file stream
*
* @note Another way to associate a file attachment with the document is using SDF::NameTree:
* @code
*   SDF::NameTree names = SDF::NameTree::Create(doc, "EmbeddedFiles");
*   names.Put(file_key, file_keysz, embedded_file.GetSDFObj());
* @endcode
*/
- (void)AddFileAttachment: (NSString*)file_key embedded_file:  (FileSpec*)embedded_file;
/**
* @return the PageLabel that is in effect for the given page.
* If there is no label object in effect, this method returns an
* invalid page label object.
*
* @param page_num The page number. Because PDFNet indexes pages
* starting from 1, page_num must be larger than 0.
*/
- (PageLabel*)GetPageLabel: (int)page_num;
/**
* Attaches a label to a page. This establishes the numbering scheme
* for that page and all following it, until another page label is
* encountered. This label allows PDF producers to define a page
* numbering system other than the default.
*
* @param page_num The number of the page to label. If page_num is
* less than 1 or greater than the number of pages in the document,
* the method does nothing.
*/
- (void)SetPageLabel: (int)page_num label:  (PageLabel*)label;
/**
* Removes the page label that is attached to the specified page,
* effectively merging the specified range with the previous page
* label sequence.
*
* @param page_num The page from which the page label is removed.
* Because PDFNet indexes pages starting from 1, page_num must be
* larger than 0.
*/
- (void)RemovePageLabel: (int)page_num;
/**
* @return true if this document is marked as Tagged PDF, false otherwise.
*/
- (BOOL)IsTagged;
/**
* @return The document's logical structure tree root.
*/
- (STree*)GetStructTree;
/**
* @return true if the optional content (OC) feature is associated with
* the document. The document is considered to have optional content if
* there is an OCProperties dictionary in the document's catalog, and
* that dictionary has one or more entries in the OCGs array.
*/
- (BOOL)HasOC;
/**
* @return the Obj array that contains optional-content groups (OCGs) for
* the document, or NULL if the document does not contain any OCGs. The
* order of the groups is not guaranteed to be the creation order, and is
* not the same as the display order.
*/
- (Obj*)GetOCGs;
/**
* @return the default optional-content configuration for the document
* from the OCProperties D entry.
*/
- (Config*)GetOCGConfig;
/**
* AddHighlights is used to highlight text in a document using 'Adobe's Highlight
* File Format' (Technical Note #5172 ). The method will parse the character offset data
* and modify the current document by adding new highlight annotations.
*
* @param hilite a string representing the filename for the highlight file or
* or a data buffer containing XML data.
*
* @exception An exception will be thrown if the XML file is malformed or os out
* of sync with the document.
*/
- (void)AddHighlights: (NSString*)hilite;
/**
* The following list of methods is used to create SDF/Cos indirect objects.
*
* Unlike direct objects, indirect objects can be referenced by more than one
* object (i.e. indirect objects they can be shared).
*
*/
- (Obj*)CreateIndirectName: (NSString *)name;
- (Obj*)CreateIndirectArray;
- (Obj*)CreateIndirectBool: (BOOL)value;
- (Obj*)CreateIndirectDict;
- (Obj*)CreateIndirectNull;
- (Obj*)CreateIndirectNumber: (double)value;
- (Obj*)CreateIndirectString: (NSData*)value size:  (unsigned int)size;
- (Obj*)CreateIndirectStream: (FilterReader*)data filter_chain:  (Filter*)filter_chain;
/**
* @return document's SDF/Cos document
*/
- (SDFDoc*)GetSDFDoc;
/**
* Locks the document to prevent competing threads from accessing the document
* at the same time. Threads attempting to access the document will wait in
* suspended state until the thread that owns the lock calls doc.Unlock().
*/
- (void)Lock;
/**
* Removes the lock from the document.
*/
- (void)Unlock;
/**
* Try locking the document, waiting no longer than specified number of milliseconds.
* @return true if the document is locked for multi-threaded access, false otherwise.
*/
- (BOOL)TryLock: (int)milliseconds;
/**
* Locks the document to prevent competing write threads (using Lock()) from accessing the document
* at the same time. Other reader threads however, will be allowed to access the document.
* Threads attempting to obtain write access to the document will wait in
* suspended state until the thread that owns the lock calls doc.UnlockRead().
* Note: To avoid deadlocks obtaining a write lock while holding
* a read lock is not permitted and will throw an exception. If this situation is encountered
* please either unlock the read lock before the write lock is obtained
* or acquire a write lock (rather than read lock) in the first place.
*/
- (void)LockRead;
/**
* Removes the read lock from the document.
*/
- (void)UnlockRead;
/**
* Tries to obtain a read lock the document for <milliseconds> duration, and returns
* true if the lock was successfully acquired
*/
- (BOOL)TryLockRead: (int)milliseconds;
/**
* @return The filename of the document if the document is loaded from disk,
* or empty string if the document is not yet saved or is loaded from a memory
* buffer.
*/
- (NSString*)GetFileName;






@end


/**
* PDFRasterizer constructor and destructor
*/
- (id)initWithType: (RasterizerType)type;
@interface PDFRasterizer : NSObject
{


}




/**
* Draws the page into a given memory buffer.
*
* @note This method is available on all platforms and in all
* rasterizer implementations.	 *
*
* @param page The page to rasterize.
* @param in_out_image_buffer A pointer to a memory buffer. The buffer must contain
* at least (stride * height) bytes.
* @param width The width of the target image in pixels.
* @param height The height of the target image in pixels (the number of rows).
* @param stride Stride determines the physical width (in bytes) of one row in memory.
* If this value is negative the direction of the Y axis is inverted. The absolute
* value of stride is of importance, because it allows rendering in buffers where
* rows are padded in memory (e.g. in Windows bitmaps are padded on 4 byte boundaries).
* Besides allowing rendering on the whole buffer stride parameter can be used
* for rendering in a rectangular subset of a buffer.
* @param num_comps The number (4 or 5) representing the number of color components
* in the device color space. For BGR+Alpha set this parameter to 4, and for CMYK+Alpha use 5.
* If other values are set, exceptions will be thrown.
* @param demult - Specifies if the alpha is de-multiplied from the resulting color components.
* @param device_mtx Device transformation matrix that maps PDF page from PDF user space
* into device coordinate space (e.g. pixel space). PDF user space is represented in
* page units, where one unit corresponds to 1/72 of an inch.
* @param clip Optional parameter defining the clip region for the page. If the parameter
*  is null or is not specified, PDFRasterizer uses page's crop box as a default clip region.
* @param scrl_clp_regions Optional parameter reserved for a future use.
* @param cancel An optional variable that can be used to stop the rendering thread.
*
*
* Sample code:
* @code
*   float drawing_scale = 2:
*   Common::Matrix2D mtx(drawing_scale, 0, 0, drawing_scale, 0, 0);
*   PDF::Rect bbox(page.GetMediaBox());
*   bbox.Normalize();
*   int width = int(bbox.Width() * drawing_scale);
*   int height = int(bbox.Height() * drawing_scale);
*
*   // Stride is represented in bytes and is aligned on 4 byte
*   // boundary so that you can render directly to GDI bitmap.
*   // A negative value for stride can be used to flip the image
*   // upside down.
*   int comps = 4;  // for BGRA
*   int stride = ((width * comps + 3) / 4) * 4;
*
*   // buf is a memory buffer containing at least (stride*height) bytes.
* 	 memset(ptr, 0xFF, height*stride);  // Clear the background to opaque white paper color.
*
*   PDFRasterizer rast;
*   rast.Rasterize(page, buf, width, height, stride, 4, false, mtx);
* @endcode
*/
- (NSData*)Rasterize: (Page*)page width:  (int)width height:  (int)height stride:  (int)stride num_comps:  (int)num_comps demult:  (BOOL)demult device_mtx:  (Matrix2D*)device_mtx clip:  (PDFRect*)clip scrl_clp_regions:  (PDFRect*)scrl_clp_regions cancel:  (SWIGTYPE_p_bool*)cancel;
/**
* Enable or disable annotation and forms rendering. By default, annotations and forms
* are rendered.
*
* @param render_annots True to draw annotations, false otherwise.
*/
- (void)SetDrawAnnotations: (BOOL)render_annots;
/**
* Enable or disable highlighting form fields. Default is disabled.
*
* @param highlight_fields true to highlight, false otherwise.
*/
- (void)SetHighlightFields: (BOOL)highlight_fields;
/**
* Enable or disable anti-aliasing.
*
* Anti-Aliasing is a technique used to improve the visual
* quality of images when displaying them on low resolution
* devices (for example, low DPI computer monitors).
*
* @default Anti-aliasing is enabled by default.
*/
- (void)SetAntiAliasing: (BOOL)enable_aa;
/**
* Enable or disable path hinting.
*
* @param path_hinting if true path hinting is enabled. Path hinting is used to slightly
* adjust paths in order to avoid or alleviate artifacts of hair line cracks between
* certain graphical elements. This option is turned on by default.
*
*/
- (void)SetPathHinting: (BOOL)path_hinting;
/**
* Set thin line adjustment parameters.
*
* @param pixel_grid_fit if true (horizontal/vertical) thin lines will be snapped to
* integer pixel positions. This helps make thin lines look sharper and clearer. This
* option is turned off by default and it only works if path hinting is enabled.
*
* @param stroke_adjust if true auto stroke adjustment is enabled. Currently, this would
* make lines with sub-pixel width to be one-pixel wide. This option is turned on by default.
*/
- (void)SetThinLineAdjustment: (BOOL)pixel_grid_fit stroke_adjust:  (BOOL)stroke_adjust;
/**
* Enable or disable image smoothing.
*
* The rasterizer allows a tradeoff between rendering quality and rendering speed.
* This function can be used to indicate the preference between rendering speed and quality.
*
* @note image smoothing option has effect only if the source image has higher resolution
* that the output resolution of the image on the rasterized page. PDFNet automatically
* controls at what resolution/zoom factor, 'image smoothing' needs to take effect.
*
* @param smoothing_enabled True to enable image smoothing, false otherwise.
* @default image smoothing is enabled.
*/
- (void)SetImageSmoothing: (BOOL)smoothing_enabled;
/**
* Enables or disables caching. Caching can improve the rendering performance in cases
* where the same page will be drawn multiple times.
*
* @param enabled - if true PDFRasterizer will cache frequently used graphics objects.
*/
- (void)SetCaching: (BOOL)enabled;
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
- (void)SetGamma: (double)exp;
/**
* Sets the Optional Content Group (OCG) context that should be used when
*  rendering the page. This function can be used to selectively render optional
* content (such as PDF layers) based on the states of optional content groups
* in the given context.
*
* @param ctx Optional Content Group (OCG) context, or NULL if the rasterizer
* should render all content on the page.
*/
- (void)SetOCGContext: (Context*)ctx;
/**
* Tells the rasterizer to render the page 'print' mode. Certain page elements
* (such as annotations or OCG-s) are meant to be visible either on the screen or
* on the printed paper but not both. A common example, is the "Submit" button on
* electronic forms.
*
* @param is_printing set to true is the page should be rendered in print mode.
* @default By default, print mode flag is set to false.
*/
- (void)SetPrintMode: (BOOL)is_printing;
/**
* Enable or disable support for overprint and overprint simulation.
* Overprint is a device dependent feature and the results will vary depending on
* the output color space and supported colorants (i.e. CMYK, CMYK+spot, RGB, etc).
*
* @default By default overprint is only enabled for PDF/X files.
*
* @param op e_op_on: always enabled; e_op_off: always disabled; e_op_pdfx_on: enabled for PDF/X files only.
*/
- (void)SetOverprint: (OverprintPreviewMode)op;
/**
* Sets the error handling function to be called in case an error is encountered
* during page rendering.
*
* @param error_proc Error handling callback function (or delegate in .NET)
* @param data Custom data to be passed as a second parameter to 'error_proc'.
*/
- (void)SetErrorReportProc: (Callback*)instance;
/**
* Sets the core graphics library used for rasterization and
* rendering. Using this method it is possible to quickly switch
* between different implementations. By default, PDFNet uses a
* built-in, high-quality, and platform independent rasterizer.
*
* @param type Rasterizer type.
*/
- (void)SetRasterizerType: (RasterizerType)type;
/**
* @return the type of current rasterizer.
*/
- (RasterizerType)GetRasterizerType;



@end


@interface BitmapInfo : NSObject
{


}




- (void)setWidth: (int)value;
- (int)getWidth;
- (void)setHeight: (int)value;
- (int)getHeight;
- (void)setStride: (int)value;
- (int)getStride;
- (void)setDpi: (double)value;
- (double)getDpi;
- (NSData*)GetBuffer;
- (id)initWithW: (int)w h:  (int)h s:  (int)s d:  (double)d b:  (NSString *)b;
@end


/**
* PDFDraw contains methods for converting PDF pages to images and to Bitmap objects.
* Utility methods are provided to export PDF pages to various raster formats as well
* as to convert pages to GDI+ bitmaps for further manipulation or drawing.
*
* @note This class is available on all platforms supported by PDFNet.
*/
@interface PDFDraw : NSObject
{


}





/**
* PDFDraw constructor and destructor
*
* @param dpi - Default resolution used to rasterize pages. If the parameter is not
* specified, the initial resolution is 92 dots per inch. DPI parameter can be
* modified at any time using PDFDraw::SetDPI() method.
*/
- (id)initWithDpi: (double)dpi;
/**
* Sets the core graphics library used for rasterization and
* rendering. Using this method it is possible to quickly switch
* between different implementations. By default, PDFDraw uses
* the built-in, platform independent rasterizer.
*
* @param type Rasterizer type.
*/
- (void)SetRasterizerType: (RasterizerType)type;
/**
* Sets the output image resolution.
*
* DPI stands for Dots Per Inch. This parameter is used to specify the output
* image size and quality. A typical screen resolution for monitors these days is
* 92 DPI, but printers could use 200 DPI or more.
*
* @note The size of resulting image is a function of DPI and the dimensions of
* the source PDF page. For example, if DPI is 92 and page is 8 inches wide, the
* output bitmap will have 92*8 = 736 pixels per line. If you know the dimensions
* of the destination bitmap, but don't care about DPI of the image you can use
* pdfdraw.SetImageSize() instead.
*
* @note if you would like to rasterize extremely large bitmaps (e.g. with
* resolutions of 2000 DPI or more) it is not practical to use PDFDraw directly
* because of the memory required to store the entire image. In this case, you
* can use PDFRasterizer directly to generate the rasterized image in stripes or
* tiles.
*/
- (void)SetDPI: (double)dpi;
/**
* SetImageSize can be used instead of SetDPI() to adjust page  scaling so that
* image fits into a buffer of given dimensions.
*
* If this function is used, DPI will be calculated dynamically for each
* page so that every page fits into the buffer of given dimensions.
*
* @param width - The width of the image, in pixels/samples.
* @param height - The height of the image, in pixels/samples.
* @param preserve_aspect_ratio - True to preserve the aspect ratio, false
* otherwise. By default, preserve_aspect_ratio is true.
*/
- (void)SetImageSize: (int)width height:  (int)height preserve_aspect_ratio:  (BOOL)preserve_aspect_ratio;
/**
* Selects the page box/region to rasterize.
*
* @param region Page box to rasterize. By default, PDFDraw will rasterize
* page crop box.
*/
- (void)SetPageBox: (Box)region;
/**
* Flips the vertical (i.e. Y) axis of the image.
*
* @param flip_y true to flip the Y axis, false otherwise. For compatibility with
* most raster formats 'flip_y' is true by default.
*/
- (void)SetFlipYAxis: (BOOL)flip_y;
/**
* Sets the rotation value for this page.
*
* @note This method is used only for drawing purposes and it does not modify
* the document (unlike Page::SetRotate()).
*
* @param angle Rotation value to be set for a given page. Must be one
* of the Page::Rotate values.
*/
- (void)SetRotate: (Rotate)r;
/**
* Enable or disable annotation and forms rendering. By default, all annotations
* and form fields are rendered.
*
* @param render_annots True to draw annotations, false otherwise.
*/
- (void)SetDrawAnnotations: (BOOL)render_annots;
/**
* Enable or disable highlighting form fields. Default is disabled.
*
* @param highlight_fields true to highlight, false otherwise.
*/
- (void)SetHighlightFields: (BOOL)highlight_fields;
/**
* Enable or disable anti-aliasing.
*
* Anti-Aliasing is a technique used to improve the visual
* quality of images when displaying them on low resolution
* devices (for example, low DPI computer monitors).
*
* @default Anti-aliasing is enabled by default.
*/
- (void)SetAntiAliasing: (BOOL)enable_aa;
/**
* Enable or disable path hinting.
*
* @param path_hinting if true path hinting is enabled. Path hinting is used to slightly
* adjust paths in order to avoid or alleviate artifacts of hair line cracks between
* certain graphical elements. This option is turned on by default.
*
*/
- (void)SetPathHinting: (BOOL)path_hinting;
/**
* Set thin line adjustment parameters.
*
* @param pixel_grid_fit if true (horizontal/vertical) thin lines will be snapped to
* integer pixel positions. This helps make thin lines look sharper and clearer. This
* option is turned off by default and it only works if path hinting is enabled.
*
* @param stroke_adjust if true auto stroke adjustment is enabled. Currently, this would
* make lines with sub-pixel width to be one-pixel wide. This option is turned on by default.
*/
- (void)SetThinLineAdjustment: (BOOL)pixel_grid_fit stroke_adjust:  (BOOL)stroke_adjust;
/**
* Enable or disable image smoothing.
*
* The rasterizer allows a tradeoff between rendering quality and rendering speed.
* This function can be used to indicate the preference between rendering speed and quality.
*
* @note image smoothing option has effect only if the source image has higher resolution
* that the output resolution of the image on the rasterized page. PDFNet automatically
* controls at what resolution/zoom factor, 'image smoothing' needs to take effect.
*
* @param smoothing_enabled True to enable image smoothing, false otherwise.
* @default image smoothing is enabled.
*/
- (void)SetImageSmoothing: (BOOL)smoothing_enabled;
/**
* Enables or disables caching. Caching can improve the rendering performance in cases
* where the same page will be drawn multiple times.
*
* @param enabled - if true PDFRasterizer will cache frequently used graphics objects.
*/
- (void)SetCaching: (BOOL)enabled;
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
- (void)SetGamma: (double)exp;
/**
* Sets the Optional Content Group (OCG) context that should be used when
* rendering the page. This function can be used to selectively render optional
* content (such as PDF layers) based on the states of optional content groups
* in the given context.
*
* @param ctx Optional Content Group (OCG) context, or NULL if the rasterizer
* should render all content on the page.
*/
- (void)SetOCGContext: (Context*)ctx;
/**
* Tells the rasterizer to render the page 'print' mode. Certain page elements
* (such as annotations or OCG-s) are meant to be visible either on the screen or
* on the printed paper but not both. A common example, is the "Submit" button on
* electronic forms.
*
* @param is_printing set to true if the page should be rendered in print mode.
* @default By default, print mode flag is set to false.
*/
- (void)SetPrintMode: (BOOL)is_printing;
/**
* Sets the default color of the page backdrop.
*
* @default By default, the page color is white.
*
* @param r, the red component of the page backdrop color.
* @param g, the green component of the page backdrop color.
* @param b, the blue component of the page backdrop color.
*
* @note Only when the page backdrop is not set to transparent (SetPageTransparent), default
* page color is used.
*/
- (void)SetDefaultPageColor: (unsigned char)r g:  (unsigned char)g b:  (unsigned char)b;
/**
* Sets the page color to transparent.
*
* @default By default, PDFDraw assumes that the page is imposed directly on an
* opaque white surface. Some applications may need to impose the page on a different
* backdrop. In this case any pixels that are not covered during rendering will
* be transparent.
*
* @param is_transparent If true, page's backdrop color will be transparent.
* If false, the page's backdrop will be a opaque white.
*
* @note If page transparency is enabled, the alpha channel will be preserved when
* the image is exported as PNG, TIFF(when in RGB space), or RAW.
*/
- (void)SetPageTransparent: (BOOL)is_transparent;
/**
* Enable or disable support for overprint and overprint simulation.
* Overprint is a device dependent feature and the results will vary depending on
* the output color space and supported colorants (i.e. CMYK, CMYK+spot, RGB, etc).
*
* @default By default overprint is only enabled for PDF/X files.
*
* @param op e_op_on: always enabled; e_op_off: always disabled; e_op_pdfx_on: enabled for PDF/X files only.
*/
- (void)SetOverprint: (OverprintPreviewMode)op;
/**
* A utility method to export the given PDF page to an image file.
*
* @param page The source PDF page.
*
* @param filename - The name of the output image file. The filename should include
* the extension suffix (e.g. 'c:/output/myimage.png').
*
* @encoder format - The file format of the output image. Currently supported formats
* are:
*    - "RAW"   : RAW format. There are four possibilities:
*				  e_rgba - if transparent and color page;
*				  e_gray_alpha - if transparent and gray page;
*				  e_rgb - if opaque and color page;
*				  e_gray - if opaque and gray page.
*				NOTE that if page is set to be transparent (SetPageTransparent),
*				the output color channels are already multiplied by the alpha channel.
*    - "BMP"   : Bitmap image format (BMP)
*    - "JPEG"  : Joint Photographic Experts Group (JPEG) image format
*    - "PNG"   : 24-bit W3C Portable Network Graphics (PNG) image format
*    - "PNG8"  : 8-bit, palettized PNG format. The exported file size should be
*                smaller than the one generated using "PNG", possibly at the
*                expense of some image quality.
*    - "TIFF"  : Tag Image File Format (TIFF) image format.
*    - "TIFF8" : Tag Image File Format (TIFF) image format (with 8-bit palete).
*
* By default, the function exports to PNG.
*
* @param encoder_params - An optional SDF dictionary object containing key/value
* pairs representing optional encoder parameters. The following table list possible
* parameters for corresponding export filters:
*
*  <table border="1">
*	<tr>
*		<td>Parameter/Key</td>
*		<td>Output Format</td>
*		<td>Description/Value</td>
*		<td>Example</td>
*	</tr>
*	<tr>
*		<td>Quality</td>
*		<td>JPEG</td>
*		<td>The value for compression 'Quality' must be a number between 0 and 100
*			specifying the tradeoff between compression ratio and loss in image quality.
*			100 stands for best quality.</td>
*		<td>
*			<P style="Z-INDEX: 0">hint.PutNumber("Quality", 60);</P>
*			<P>See the Example 2 in PDFDraw sample project.</P>
*		</td>
*	</tr>
*	<tr>
*		<td>Dither</td>
*		<td>
*			PNG, PNG8, TIFF or TIFF8.</td>
*		<td>A boolean used to enable or disable dithering. Relevent only for when the image
*			is exported in palettized or monochrome mode.</td>
*		<td>hint.PutBool("Dither", true);</td>
*	</tr>
*	<tr>
*		<td>ColorSpace</td>
*		<td>PNG/TIFF for grayscale; TIFF for CMYK.</td>
*		<td>A name object used to select the rendering and export color space. Currently
*			supported values are "Gray", "RGB, and "CMYK". The output image format must
*			support specified color space, otherwise the parameter will be ignored. An
*			example of image format that supports CMYK is TIFF. Image formats that support
*			grayscale are PNG and TIFF. By default, the image is rendered and exported in
*			RGB color space.</td>
*		<td>hint.PutName("ColorSpace", "CMYK");</td>
*	</tr>
*	<tr>
*		<td>BPC</td>
*		<td>PNG or TIFF.</td>
*		<td>A number used to specify 'bits per pixel' in the output file. Currently
*			supported values are 1 and 8 (default is 8). To export monochrome (1 bit
*			per pixel) image, use 1 as the value of BPC parameter and use TIFF or PNG as the
*			export format for the image. By default, the image is not dithered when BPC is 1.
*			To enable dithering add 'Dither' option in the export hint.</td>
*		<td>hint.PutNumber("BPC", 1);</td>
*	</tr>
*  </table>
*/
- (void)ExportWithObj: (Page*)page filename:  (NSString*)filename format:  (NSString *)format encoder_params:  (Obj*)encoder_params;
/**
* Export the given PDF page to an image stream.
*
* @param page The source PDF page.
* @param stream - The output stream.
* @encoder format - The output image format. See the the overloaded method for details.
* @param encoder_params - Optional encoder parameters. See the the overloaded method for details.
*/
- (void)Export: (Page*)page filename:  (NSString*)filename format:  (NSString *)format;
/**
* Returns a GDI+ bitmap for the given page.
*
* @param page The source PDF page.
* @return GDI+ bitmap containing the rasterized image of the given page.
*
* @note this method is available on .NET platform.
*/
- (BitmapInfo*)GetBitmap: (Page*)page pix_fmt:  (PixelFormat)pix_fmt demult:  (BOOL)demult;
/**
* Sets the error handling function to be called in case an error is encountered
* during page rendering.
*
* @param error_proc Error handling callback function (or delegate in .NET)
* @param data Custom data to be passed as a second parameter to 'error_proc'.
*/
- (void)SetErrorReportProc: (Callback*)instance;



@end


/**
* PDFNet contains global library initialization, registration, configuration,
* and termination methods.
*
* @note there is only a single, static instance of PDFNet class. Initialization
* and termination methods need to be called only once per application session.
*/
@interface PDFNet : NSObject
{


}





/**
* Initializes PDFNet library.
* Initialize() is usually called once, during process initialization.
*
* @note it is unsafe to call any other PDFNet API without first initializing
* the library
*
* @param license_key Optional license key used to activate the product.
* If the license_key is not specified or is null, the product will work in the
* demo mode.
*
* @exception If the license_key is invalid, the function will throw an exception.
*/
+ (void)Initialize: (NSString *)license_key;
/**
* Sets the location of PDFNet resource file.
*
* @note Starting with v.4.5 PDFNet does not require a separate resource
* file (pdfnet.res) on all desktop/server platforms. As a result, this function
* is not longer required for proper PDFNet initialization. The function is still
* available on embedded systems and for backwards compatibility. The function can
* be also used to specify a default search path for ICC profiles, fonts, and other
* user defined resources.
*
* @param path - The default resource directory path.
* @return true if path is found, false otherwise.
*/
+ (BOOL)SetResourcesPath: (NSString*)path;
/**
* @return the location of PDFNet resources folder. Empty string means
* that resources are located in your application folder.
*/
+ (NSString*)GetResourcesPath;
/**
* @return PDFNet version number.
*/
+ (double)GetVersion;
/**
* ConnectToCloud() is used to connect PDFNet with your 'pay-as-you-go' account
* (http://www.pdftron.com/pdfnet/cloud).
*
* PDFTron Cloud is a 'pay-as-you-go' service that offers PDFTron document
* conversion and processing capabilities with minimal startup costs.
*
* PDFTron Cloud account allows applications to convert documents either on your
* own servers (e.g. using PDFNet SDK or DocPub CLI) or via PDFTron hosted REST
* service.
*
* Benefits of the self-hosted model are related to privacy and increased
* flexibility and speed from your own hardware infrastructure. On the other hand,
* self-hosted model may be more costly due to operation fees.
*
* @note Please note that in order to use ConnectToCloud() you need to have a
* valid Enterprise or Web CPU license for PDFNet. If you do not need additional
* functionality provided by PDFNet (e.g. you simply need to convert), please use
* DocPub CLI instead of PDFNet SDK.
*
* @note ConnectToCloud() should be called once, immediately after
* PDFNet.Initialize("...license key...").
*
* @param api_id Your API ID (i.e. username). You should receive this information
* via email after Cloud API service (https://api.pdftron.com) sign-up. You can also
* find your 'API ID' in the 'Account' section in your PDFTron Cloud account.

* @param api_secret (i.e. password). This information is provided together with
* 'api_id' and can also be retrieved from https://api.pdftron.com.
*
* @return CloudErrorCode will be returned. STATUS_OK if PDFNet successfully connected to your Cloud account.
*
* @exception If called before call to PDFNet.Initialized or in DEMO mode, the function will throw an exception.
*/
+ (CloudErrorCode)ConnectToCloud: (NSString *)api_id api_secret:  (NSString *)api_secret;
/**
* Used to set a specific Color Management System (CMS) for
* use during color conversion operators, image rendering, etc.
*
* @param t identifies the type of color management to use.
*/
+ (void)SetColorManagement: (CMSType)t;
/**
* Sets the default ICC color profile for DeviceCMYK color space.
*
* @note You can use this method to override default PDFNet settings.
* For more information on default color spaces please refer to
* section 'Default Color Spaces' in Chapter 4.5.4 of PDF Reference Manual.
*
* @exception the function will throw Exception if the ICC profile
* can't be found or if it fails to open.
*/
+ (void)SetDefaultDeviceCMYKProfile: (NSString*)icc_filename;
/**
* Sets the default ICC color profile for DeviceRGB color space.
*
* @note You can use this method to override default PDFNet settings.
* For more information on default color spaces please refer to
* section 'Default Color Spaces' in Chapter 4.5.4 of PDF Reference Manual.
*
* @exception the function will throw Exception if the ICC profile
* can't be found or if it fails to open.
*/
+ (void)SetDefaultDeviceRGBProfile: (NSString*)icc_filename;
/**
* Sets the default policy on using temporary files.
*
* @use_disk if parameter is true then new documents are allowed to create
* temporary files; otherwise all document contents will be stored in memory.
*/
+ (void)SetDefaultDiskCachingEnabled: (BOOL)use_disk;
/**
*
*  Sets the default parameters for the viewer cache.  Any subsequently created documents
*	will use these parameters.
*
*	@param max_cache_size - The maximum size, in bytes, of the entire document's page cache.
*	@param max_zoom_factor - The maximum zoom factor (in percent) supported by the cache.  (value is clamped to a minimum of 100)
*
*	@default By default, maximum cache size is 512 MB and maximum zoom factor is 1000%
*/
+ (void)SetViewerCache: (unsigned long)max_cache_size max_zoom_factor:  (unsigned long)max_zoom_factor;
/**
* AddFontSubst functions can be used to create font substitutes
* that can override default PDFNet font selection algorithm.
*
* These functions are useful in situations where referenced fonts
* are not present in the document and PDFNet font substitution
* algorithm is not producing desired results.
*
* AddFontSubst(fontname, fontpath) maps the given font name (i.e. 'BaseFont'
* entry from the font dictionary) to a font file.
*
* AddFontSubst(ordering, fontpath) maps the given character ordering (see
* Ordering entry in CIDSystemInfo dictionary; Section 5.6.2 in PDF Reference)
* to a font file. This method is less specific that the former variant of
* AddFontSubst, and can be used to override a range of missing fonts (or
* any missing font) with a predefined substitute.
*
* The following is an example of using these functions to provide user
* defined font substitutes:
*
* @code
* PDFNet::Initialize();
* PDFNet::SetResourcesPath("c:/myapp/resources");
* // Specify specific font mappings...
* PDFNet::AddFontSubst("MinionPro-Regular", "c:/myfonts/MinionPro-Regular.otf");
* PDFNet::AddFontSubst("Times-Roman", "c:/windows/fonts/times.ttf");
* PDFNet::AddFontSubst("Times-Italic", "c:/windows/fonts/timesi.ttf");
*
* // Specify more general font mappings...
* PDFNet::AddFontSubst(PDFNet::e_Identity, "c:/myfonts/arialuni.ttf");  // Arial Unicode MS
* PDFNet::AddFontSubst(PDFNet::e_Japan1, "c:/myfonts/KozMinProVI-Regular.otf");
* PDFNet::AddFontSubst(PDFNet::e_Japan2, "c:/myfonts/KozMinProVI-Regular.otf");
* PDFNet::AddFontSubst(PDFNet::e_Korea1, "c:/myfonts/AdobeSongStd-Light.otf");
* PDFNet::AddFontSubst(PDFNet::e_CNS1, "c:/myfonts/AdobeMingStd-Light.otf");
* PDFNet::AddFontSubst(PDFNet::e_GB1, "c:/myfonts/AdobeMyungjoStd-Medium.otf");
* ...
* PDFDoc doc("c:/my.pdf");
* ...
* @endcode
*/
+ (BOOL)AddFontSubstWithFontName: (NSString *)fontname fontpath:  (NSString*)fontpath;
+ (BOOL)AddFontSubstWithOrdering: (CharacterOrdering)ordering fontpath:  (NSString*)fontpath;
/**
* Set the location of temporary folder.
*
* This method is provided for applications that require tight control of
* the location where temporary files are created.
*/
+ (BOOL)SetTempPath: (NSString*)temp_path;
- (id)init;

@end


/**
* PDFView is a utility class that can be used for interactive rendering of PDF documents.
*
* In .NET environment PDFView is derived from System.Windows.Forms.Control and it can be
* used like a regular form (see PDFViewForm.cs in PDFView sample for C# for a concrete
* example).
*
* PDFView implements some essential features such as double-buffering, multi-threaded
* rendering, scrolling, zooming, and page navigation that are essential in interactive
* rendering applications (e.g. in client PDF viewing and editing applications).
*
* PDFView defines several coordinate spaces and it is important to understand their
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
* @note PDFView is available on all platforms supported by PDFNet.
*/
@interface PDFView : NSObject
{


}





/**
* PDFView constructor and destructor. Create PDFView without associating it to any
* document.
*/
- (id)init;
/**
* Associates this PDFView with a given PDF document.
*
* @param doc - A document to be displayed in the view.
*/
- (void)SetDoc: (PDFDoc*)doc;
/**
* Close the associated PDF document.
*/
- (void)CloseDoc;
/**
* @return Currently associated document with this PDFView.
*/
- (PDFDoc*)GetDoc;
/**
* Acquires a write lock on the currently open document,
* optionally canceling all threads accessing the document.
*/
- (void)DocLock: (BOOL)cancel_threads;
/**
* Releases the write lock from the currently open document.
*/
- (void)DocUnlock;
/**
* Try acquiring a write lock on the currently open document, waiting no
* longer than specified number of milliseconds.
* @return true if the document is locked for multi-threaded access, false otherwise.
*/
- (BOOL)DocTryLock: (int)milliseconds;
/**
* Locks the currently open document to prevent competing write threads
* (using Lock()) from accessing the document at the same time.
* Other reader threads however, will be allowed to access the document.
* Threads attempting to obtain write access to the document will wait in
* suspended state until the thread that owns the lock calls doc.UnlockRead().
* Note: To avoid deadlocks obtaining a write lock while holding
* a read lock is not permitted and will throw an exception. If this situation is encountered
* please either unlock the read lock before the write lock is obtained
* or acquire a write lock (rather than read lock) in the first place.
*/
- (void)DocLockRead;
/**
* Releases the read lock from the currently open document.
*/
- (void)DocUnlockRead;
/**
* Try acquiring a read lock on the current document, waiting no longer than specified
* number of milliseconds.
* @return true if the document is locked for multi-threaded access, false otherwise.
*/
- (BOOL)DocTryLockRead: (int)milliseconds;
/**
* Sets the current page presentation mode.
*
* @param mode - the new page presentation mode.
* @default The default PagePresentationMode is e_single_continuous.
*/
- (void)SetPagePresentationMode: (PagePresentationMode)mode;
/**
* @return the current page presentation mode.
*/
- (PagePresentationMode)GetPagePresentationMode;
/**
* @return the current page displayed in the view.
*/
- (int)GetCurrentPage;
/**
* @return the total number of pages in the document.
*/
- (int)GetPageCount;
/**
* Sets the current page to the first page in the document.
*
* @return true if successful, false otherwise.
*/
- (BOOL)GotoFirstPage;
/**
* Sets the current page to the last page in the document.
*
* @return true if successful, false otherwise.
*/
- (BOOL)GotoLastPage;
/**
* Sets the current page to the next page in the document.
*
* @return true if successful, false otherwise.
*/
- (BOOL)GotoNextPage;
/**
* Sets the current page to the previous page in the document.
*
* @return true if successful, false otherwise.
*/
- (BOOL)GotoPreviousPage;
/**
* Sets the current page to the given page.
*
* @return true if successful, false otherwise.
*/
- (BOOL)SetCurrentPage: (int)page_num;
/**
* Changes the viewing area to fit a rectangle rect on page page_num.
* Rectangle must be specified in page coordinates.
* This will adjust current page and zoom appropriately.
*
* @return true if successful, false otherwise.
*/
- (BOOL)ShowRect: (int)page_num rect:  (PDFRect*)rect;
/**
* Returns the current zoom factor.
*
* @return current zoom (or scaling) component used to display the page content.
*/
- (double)GetZoom;
/**
* Sets the zoom factor to a new value. The function zooms to a point at the
* center of the rendering buffer.
*
* @param zoom - new scaling component used to display the page content.
* @return true if successful, false otherwise.
*/
- (BOOL)SetZoom: (double)zoom;
/**
* Sets the zoom factor to a new value using the given pixel coordinate
* (x,y) as a zoom center, which will stay fixed on the screen.
*
* The zoom point (x,y) is represented in the screen space, which
* starts in the upper-left corner of the client window.
*
* Should you want to move (x, y) to the center of the client window, you can
* use the OnScroll() subsequently:
*
*
*		int x, y;
*		double zoom;
*		...
*		view.SetZoom(x, y, zoom);
*		int width = view.GetBufferWidth();
*		int height = view.GetBufferHeight();
*		int dx = (int)(x - (double)width/2 + 0.5);
*		int dy = (int)(y - (double)height/2 + 0.5);
*		view.OnScroll(dx, dy);
*
*
* @param x - the horizontal coordinate to zoom in.
* @param y - the vertical coordinate to zoom in.
* @param zoom - new scaling component used to display the page content.
* @return true if successful, false otherwise.
*/
- (BOOL)SetZoomWithCoord: (int)x y:  (int)y zoom:  (double)zoom;
/**
* Sets the zoom factor to a new value using the given pixel coordinate
* (x,y) to find an intersecting paragraph.
* The width of the paragraph helps to determine the zoom value, center
* of the paragraph is used as a zoom center.
* Paragraph has to contain more than one line and be wider than 1/5th of a page width.
* When called on a paragraph wider than current zoom level the new zoom level
* is set to fit the entire page(zoom out).
*
* The zoom point (x,y) is represented in the screen space, which
* starts in the upper-left corner of the client window.
*
* @param x - the horizontal coordinate to look for a text block.
* @param y - the vertical coordinate to look for a text block.
* @return true if successful, false if no paragraph intersects the given point.
*/
- (BOOL)SmartZoom: (int)x y:  (int)y;
/**
* Rotates all pages in the document 90 degrees clockwise.
*/
- (void)RotateClockwise;
/**
* Rotates all pages in the document 90 degrees counter-clockwise.
*/
- (void)RotateCounterClockwise;
/**
* @return  The current rotation of this PDFView.
*/
- (Rotate)GetRotation;
/**
* @return the number of the page located under the given screen
* coordinate. The positive number indicates a valid page, whereas
* number less than 1 means that no page was found.
*/
- (int)GetPageNumberFromScreenPt: (double)x y:  (double)y;
/**
* Converts a point expressed in screen space to a point in canvas space.
*/
- (PDFPoint*)ConvScreenPtToCanvasPt: (PDFPoint*)pt;
/**
* Converts a point expressed in canvas space to a point in screen space.
*/
- (PDFPoint*)ConvCanvasPtToScreenPt: (PDFPoint*)pt;
/**
* Converts a point expressed in canvas space to a point in a page space.
*
* @param page_num the page number for the page used as the origin of the destination
* coordinate system. Negative values are used to represent the current page.
* Pages are indexed starting from one.
*/
- (PDFPoint*)ConvCanvasPtToPagePt: (PDFPoint*)pt page_num:  (int)page_num;
/**
* Converts a point from a page space to point in canvas space.
*
* @param page_num the page number for the page used as the origin of the destination
* coordinate system. Negative values are used to represent the current page.
* Pages are indexed starting from one.
*/
- (PDFPoint*)ConvPagePtToCanvasPt: (PDFPoint*)pt page_num:  (int)page_num;
/**
* Converts a point expressed in screen space to a point in a page space.
*
* @param page_num the page number for the page used as the origin of the destination
* coordinate system. Negative values are used to represent the current page.
* Pages are indexed starting from one.
*/
- (PDFPoint*)ConvScreenPtToPagePt: (PDFPoint*)pt page_num:  (int)page_num;
/**
* Converts a point in a page space to a point in the screen space.
*
* @param page_num the page number for the page used as the origin of the destination
* coordinate system. Negative values are used to represent the current page.
* Pages are indexed starting from one.
*/
- (PDFPoint*)ConvPagePtToScreenPt: (PDFPoint*)pt page_num:  (int)page_num;
/**
* @return the device transformation matrix. The device transformation
* matrix maps the page coordinate system to screen (or device) coordinate
* system.
*
* @param page_num same as for PDFView.Conv???() methods.
*
* @note to obtain a transformation matrix that maps screen
* coordinates to page coordinates, you can invert the device matrix.
* For example:
* @code
*   Common::Matrix2D scr2page(pdfview.GetDeviceTransform());
*   scr2page.Inverse();
* @endcode
*/
- (Matrix2D*)GetDeviceTransform: (int)page_num;
/**
* Sets the error handling function to be called in case an error is encountered
* during page rendering.
*
* @param error_proc Error handling callback function (or delegate in .NET)
* @param data Custom data to be passed as a second parameter to 'error_proc'.
*/
- (void)SetErrorReportProc: (Callback*)instance;
/**
* Sets the callback function (i.e. a delegate) that is called whenever current
* page number changes. This can be used to update the current page number within
* GUI applications etc.
*
* @param curr_pagenum_proc Callback function (or a delegate in .NET).
* @param data Custom data to be passed as a second parameter to 'curr_pagenum_proc'.
*/
- (void)SetCurrentPageProc: (Callback*)instance;
/**
* Sets the callback function (i.e. a delegate) that is called whenever current
* zoom (magnification) changes. This can be used to update the current zoom number
* within GUI applications etc.
*
* @param curr_zoom_proc Callback function (or a delegate in .NET).
* @param data Custom data to be passed as a second parameter to 'curr_zoom_proc'.
*/
- (void)SetCurrentZoomProc: (Callback*)instance;
/**
* Returns the width of the scrollable space.
*/
- (double)GetCanvasWidth;
/**
* Returns the height of the scrollable space.
*/
- (double)GetCanvasHeight;
/**
* @return the current horizontal scroll position in the scrollable space.
*/
- (double)GetHScrollPos;
/**
* @return the current vertical scroll position in the scrollable space.
*/
- (double)GetVScrollPos;
/**
* Scrolls the contents of the rendering buffer 'pix_dx' horizontally and 'pix_dy' vertically.
*
* @param pix_dx horizontal scroll offset, in pixels
* @param pix_dy vertical scroll offset, in pixels
*/
- (void)OnScroll: (int)pix_dx pix_dy:  (int)pix_dy;
/**
* Sets the horizontal scroll position in scrollable space.
*
* @param the new horizontal scroll position. The position should be in the range
* between 0 and GetCanvasWidth().
*/
- (void)SetHScrollPos: (double)pos;
/**
* Sets the vertical scroll position in scrollable space.
*
* @param the new vertical scroll position. The position should be in the range
* between 0 and GetCanvasheight().
*
* Should you want to center to a location (px, py) expressed in a page space,
* you can use the following code:
*
*		//focus
*		view.SetCurrentPage(page_num);
*		view.ConvPagePtToScreenPt(px, py, page_num);
*		view.SetZoom((int)px, (int)py, view.GetZoom());
*
*		//center
*		int width = view.GetBufferWidth();
*		int height = view.GetBufferHeight();
*		int dx = (int)(px - (double)width/2 + 0.5);
*		int dy = (int)(py - (double)height/2 + 0.5);
*		view.OnScroll(dx, dy);
*
*/
- (void)SetVScrollPos: (double)pos;
/**
* Resize rendering buffer to new dimensions.
*
* @param width - The width of the target image in pixels.
* @param height - The height of the target image in pixels (the number of rows).
* @note this method is typically used only in PDFNet for C++
*/
- (void)OnSize: (int)width height:  (int)height;
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
* Cancels rendering in progress. If PDFView is not busy rendering the page,
* the function has no side effects.
*/
- (void)CancelRendering;
/**
* Redraws the contents of the buffer.
*/
- (void)Update;
/**
* Redraws the given area in the buffer.
* @param update The rectangle to update expressed in screen coordinates.
*/
- (void)UpdateWithRect: (PDFRect*)update;
/**
* Redraws the area covered with a given annotation.
* @param annot The annotation to update.
* @param page_num The page number on which the annotation is located.
*/
- (void)UpdateWithAnnot: (Annot*)annot page_num:  (int)page_num;
/**
* Updates the page layout within the view. This function must be called
* after document page sequence is modified (such as when a page is being
* added to or removed from a document) or after changes to page dimensions
* (e.g. after a page is rotated or resized).
*/
- (void)UpdatePageLayout;
/**
* Returns the pointer to the internal memory buffer containing the rasterized image
* of the given page. The buffer size is at least 'GetBufferHeight*GetBufferStride' bytes.
* The pixel data is stored in 8 bit per component, BGRA format.
*/
- (NSData*)GetBuffer;
/**
* Update the internal memory buffer that can be returned by GetBuffer(). Since PDFView may not
* necessarily update the buffer until it finishes rendering the current viewing area, it is
* required to call UpdateBuffer() to force PDFView to write the current rasterized contents
* to the buffer. This is important for, say, calling GetBuffer() in a different thread to
* implement progressive rendering.
*
* @note UpdateBuffer() ensures thread safety internally. In addition, PDFView calls
* UpdateBuffer() internally before the user-defined finishing-rendering
* callback function (specified by SetRenderFinishProc) is called, if applicable.
* this method is typically used only in PDFNet for C++.
*/
- (void)UpdateBuffer;
/**
* Returns the width of the rendering buffer in pixels.
* @note this method is typically used only in PDFNet for C++
*/
- (int)GetBufferWidth;
/**
* Returns the width of the rendering buffer in pixels.
* @note this method is typically used only in PDFNet for C++
*/
- (int)GetBufferHeight;
/**
* Returns the stride of the rendering buffer in pixels.
* @note this method is typically used only in PDFNet for C++
*/
- (int)GetBufferStride;
/**
* Enable or disable annotation and forms rendering. By default, all annotations
* and form fields are rendered.
*
* @param render_annots True to draw annotations, false otherwise.
*/
- (void)SetDrawAnnotations: (BOOL)render_annots;
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
* Gets the link info at a given point, specified in client space.
*
* @param x the x position in client space
* @param y the y position in client space
*
* @return the LinkInfo object with the link information or null if
* no link is found in the queried location.
*
* @note To get valid links, SetUrlExtraction(boolean) must be
* set to true before opening the document.
*/
- (SWIGTYPE_pdftron__PDF__PDFView__LinkInfo*)GetLinkAt: (int)x y:  (int)y;
/**
* Enable or disable highlighting form fields. Default is disabled.
*
* @param highlight_fields true to highlight, false otherwise.
*/
- (void)SetHighlightFields: (BOOL)highlight_fields;
/**
* Enable or disable anti-aliasing.
*
* Anti-Aliasing is a technique used to improve the visual
* quality of images when displaying them on low resolution
* devices (for example, low DPI computer monitors).
*
* @default Anti-aliasing is enabled by default.
*/
- (void)SetAntiAliasing: (BOOL)enable_aa;
/**
* Enable or disable path hinting.
*
* @param path_hinting if true path hinting is enabled. Path hinting is used to slightly
* adjust paths in order to avoid or alleviate artifacts of hair line cracks between
* certain graphical elements. This option is turned on by default.
*
*/
- (void)SetPathHinting: (BOOL)path_hinting;
/**
* Set thin line adjustment parameters.
*
* @param pixel_grid_fit if true (horizontal/vertical) thin lines will be snapped to
* integer pixel positions. This helps make thin lines look sharper and clearer. This
* option is turned off by default and it only works if path hinting is enabled.
*
* @param stroke_adjust if true auto stroke adjustment is enabled. Currently, this would
* make lines with sub-pixel width to be one-pixel wide. This option is turned on by default.
*/
- (void)SetThinLineAdjustment: (BOOL)pixel_grid_fit stroke_adjust:  (BOOL)stroke_adjust;
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
- (void)SetImageSmoothing: (BOOL)smoothing_enabled;
/**
* Enables of disables caching of images, fonts, and other resources. Disabling caching
* can lower memory requirements at the expense of rendering speed.
*
* @param enabled if true caching is enabled, if false caching is disabled.
* @default by default caching is enabled
*/
- (void)SetCaching: (BOOL)enabled;
/**
* Sets the core graphics library used for rasterization and
* rendering. Using this method it is possible to quickly switch
* between different implementations. By default, PDFNet uses a
* built-in, high-quality, and platform independent rasterizer.
*
* @param type Rasterizer type.
*/
- (void)SetRasterizerType: (RasterizerType)type;
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
- (void)SetGamma: (double)exp;
/**
* Enable or disable support for overprint and overprint simulation.
* Overprint is a device dependent feature and the results will vary depending on
* the output color space and supported colorants (i.e. CMYK, CMYK+spot, RGB, etc).
*
* @default By default overprint is only enabled for PDF/X files.
*
* @param op e_op_on: always enabled; e_op_off: always disabled; e_op_pdfx_on: enabled for PDF/X files only.
*/
- (void)SetOverprint: (OverprintPreviewMode)op;
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
- (void)SetOCGContext: (Context*)ctx;
/**
* @return the Optional Content Group (OCG) context associated with this
* PDFView, or NULL (i.e. context.IsValid()==false) if there is no OCG
* context associated with the view. If an OCG context associated with the
* view, optional content (such as PDF layers) will be selectively rendered
* based on the states of optional content groups in the given context.
*/
- (Context*)GetOCGContext;
/**
* Set a callback function that can be used to notify the client
* that PDFView is about to start rendering and modifying the contents
* of the rendering buffer.
*
* @param proc A callback function that will be called just before
* PDFView starts rendering.
* @param data Custom data to be passed as a parameter to 'proc'.
*
* @note this method is available only in the C++ SDK and not
* available in pre-packaged PDF viewing controls (.NET/Java/ActiveX).
*/
- (void)SetRenderBeginProc: (Callback*)instance;
/**
* Set a callback function that can be used to notify the client
* that PDFView finished rendering and modifying the contents
* of the rendering buffer.
*
* @param proc A callback function that will be called after PDFView
* is done with rendering.
* @param data Custom data to be passed as a parameter to 'proc'.
*
* @note this method is available only in the C++ SDK and is not
* available in pre-packaged PDF viewing controls (.NET/Java/ActiveX).
*/
- (void)SetRenderFinishProc: (Callback*)instance;
/**
* Sets the selection mode used for text highlighting.
* @param tm the text selection mode.
*/
- (void)SetTextSelectionMode: (TextSelectionMode)tm;
/**
* Selects text within the given region using the current text selection mode.
*
* @return true if some text was selected, false otherwise.
* @param x1, y1, x2, y2 - two points (screen coordinates, origin located at the upper-left corner of this view)
* defining the opposite corners of a selection rectangle.
*/
- (BOOL)SelectWithTextSelect: (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
/**
* Selects texts using structural mode.
*
* @return true if some texts were selected, false otherwise.
* @param (x1, y1), page1 - the first selection point (in page coordinates space) on page page1
* @param (x2, y2), page2 - the second selection point (in page coordinates space) on page page2
*/
- (BOOL)SelectWithStructure: (double)x1 y1:  (double)y1 page1:  (int)page1 x2:  (double)x2 y2:  (double)y2 page2:  (int)page2;
/**
* Selects texts identified by Highlights.
*
* @return true if some texts were selected, false otherwise.
* @param highlights - an instance of Highlights class.
*/
- (BOOL)SelectWithHighlights: (Highlights*)highlights;
/**
* Selects a region according to a Selection object
*
* @return true if some texts were selected, false otherwise.
* @param select - an instance of the Selection class
*/
- (BOOL)SelectWithSelection: (Selection*)select;
/**
* Selects text by searching for a given string of text.
*
* @return true if some text was selected, false otherwise.
* @param search_str -
* @param match_case -
* @param match_whole_word -
* @param search_up  -
* @param reg_exp  - use regular expressions
*/
- (BOOL)FindText: (NSString*)search_str match_case:  (BOOL)match_case match_whole_word:  (BOOL)match_whole_word search_up:  (BOOL)search_up reg_exp:  (BOOL)reg_exp;
/**
* Selects all text on the page.
*/
- (void)SelectAll;
/**
* @return return true if there is selection, false otherwise.
*/
- (BOOL)HasSelection;
/**
* Remove any text selection.
*/
- (void)ClearSelection;
/**
* @return Current text selection for a given page
*/
- (Selection*)GetSelection: (int)pagenum;
/**
* @return the first page number that has text selection on it.
* Useful when there are selections on multiple pages at the same time.
*/
- (int)GetSelectionBeginPage;
/**
* @return the last page number that has text selection on it.
* Useful when there are selections on multiple pages at the same time.
*/
- (int)GetSelectionEndPage;
/**
* @return returns true if given page number has any text selection on it.
* Useful when there are selections on multiple pages at the same time.
*/
- (BOOL)HasSelectionOnPage: (int)ipage;
/**
* Enables or disables drawing of a thin border around each page.
* @param border_visible - if true, the border will be visible.
*/
- (void)SetPageBorderVisibility: (BOOL)border_visible;
/**
* Enables or disables the transparency grid (check board pattern) to reflect
* page transparency.
* @param trans_grid_visible - if true, the grid is turned on.
*/
- (void)SetPageTransparencyGrid: (BOOL)trans_grid_visible;
/**
* Sets the default 'paper' color used to draw background of each page.
* @param r, g, b - RGB color specifying the default page color.
*/
- (void)SetDefaultPageColor: (unsigned char)r g:  (unsigned char)g b:  (unsigned char)b;
/**
* Sets the default background color used to paint the area surrounding each page.
* @param r, g, b - RGB color specifying the default background color.
* @param a - The alpha value of the background color. Default value is 255.
*/
- (void)SetBackgroundColor: (unsigned char)r g:  (unsigned char)g b:  (unsigned char)b a:  (unsigned char)a;
/**
* Sets the horizontal alignment used for rendering pages within the view.
* @param align an integer specifying the horizontal alignment. Depending
* of whether align is positive, negative, or zero - pages will be right,
* left or center aligned:
*   align<0  -> pages are left aligned.
*   align==0 -> pages are centered.
*   align>0  -> pages are right aligned.
*/
- (void)SetHorizontalAlign: (int)align;
/**
* Sets the vertical alignment used for rendering pages within the view.
* @param align an integer specifying the vertical alignment. Depending
* of whether align is positive, negative, or zero - pages will be bottom,
* top or center aligned:
*   align<0  -> pages are top aligned.
*   align==0 -> pages are centered.
*   align>0  -> pages are bottom aligned.
*/
- (void)SetVerticalAlign: (int)align;
/**
* Sets the vertical and horizontal padding and column spacing between adjacent pages in the view.
*
*
* @param horiz_space horizontal spacing (represented in pixels) between
* adjacent pages in the view. Default is 10.
* @param vert_space vertical spacing (represented in pixels) between adjacent
* pages in the view. Default is 10.
*/
- (void)SetPageSpacing: (int)horiz_col_space vert_col_space:  (int)vert_col_space horiz_pad:  (int)horiz_pad vert_pad:  (int)vert_pad;
/**
*	Sets the cache parameters of the page cache on disk (which caches content streams and
*	mipmapped images) for this specific document.  These parameters will override the default cache
*  parameters.  Note that if this function is called after the document has been rasterized, it has no
*  effect.
*
*  @param document - The document whose settings will be modified
*	@param max_cache_size - The maximum size, in bytes, of the entire document's page cache
*	@param max_zoom_factor - The maximum zoom factor (in percent) supported by the cache (value is clamped to a minimum of 100)
*
*/
+ (void)SetViewerCache: (SDFDoc*)document max_cache_size:  (unsigned long)max_cache_size max_zoom_factor:  (unsigned long)max_zoom_factor;

/**
* Gets the annotation at the (x, y) position expressed in screen coordinates
*
*
* @param x x coordinate of the screen point
* @param y y coordinate of the screen point
* @return the annotation at (x, y). If there is no annotation at (x, y), the returned annotation's IsValid method will return false.
*/
- (Annot*)GetAnnotationAt: (int)x y:  (int)y;
/**
* Sets the page viewing mode
*
* @param mode - the new page viewing mode.
* @default The default PageView mode is e_fit_width.
*/
- (void)SetPageViewMode: (PageViewMode)mode;
/**
* @return the current page viewing mode
*/
- (PageViewMode)GetPageViewMode;
/**
* Sets the reference page view mode. In a non-continous page presentation
* mode, the reference page view mode is used to determine the page view
* mode upon a page change event. For example, if the reference page view
* mode is set to e_fit_width, the new page coming in will
* be displayed with width-fit mode.
*
* @param mode
*            The reference page view mode to set. Valid values are
*            e_fit_page, e_fit_width, and
*            e_fit_height.
*/
- (void)SetPageRefViewMode: (PageViewMode)mode;
/**
* Gets the reference page view mode. See more details about reference
* page view mode in {@link #setPageRefViewMode(int)}.
*/
- (PageViewMode)GetPageRefViewMode;
/**
* Enables or disables thumbnail features.
*
* @param use_embedded Enables or disables using thumbnails embedded in the PDF document as a preview of the rendered page.
* @param generate_at_runtime Enables or disables generating thumbnails at runtime.
* @param use_persistent_cache Enables or disables storing thumbnails in a persistent cache on disk.
* @param thumb_max_side_length The maximum size, in pixels, of a dimension of generated thumbnails.  This value is also used to calculate the maximum size of a thumbnail when creating a persistent thumbnail cache; that size remains until the persistent cache is deleted.
* @param cache_directory_path A directory on disk in which the persistent thumbnail cache can be created.
* @param cache_data_file_size The size, in bytes, of the data file in which thumbnails are cached.  If the persistent cache is already present, and the existing file is smaller than this value, the data file size is increased.  If the value is 0, and use_persistent_cache is true, the persistent cache is deleted and all cached thumbnail state is gone.  In all other cases, the data file size remains the same.
*/
- (void)SetupThumbnails: (BOOL)use_embedded generate_at_runtime:  (BOOL)generate_at_runtime use_persistent_cache:  (BOOL)use_persistent_cache thumb_max_side_length:  (int)thumb_max_side_length cache_directory_path:  (NSString*)cache_directory_path cache_data_file_size:  (int)cache_data_file_size;
/**
* Retrieves the specified thumbnail from the persistent thumbnail
* cache on disk, then calling proc on the resulting thumbnail.
*
* @param page_num The page number of the thumbnail.
* @param proc A callback function that will be called after the thumbnail is retrieved, or if that retrieval fails.
* @param data Custom data to be passed as a parameter to 'proc'.
*/
- (void)GetThumbAsync: (int)page_num instance:  (Callback*)instance;
/**
* Sets the FindText handling function to be called once FindTextAsync is done,
* whether it was interrupted, canceled, or completed.
*
* @param instance A pointer to the Callback object
*/
- (void)SetFindTextHandler: (Callback*)instance;
/**
* Searches for the provided search string in the documents in a secondary thread,
* and calls FindTextAsyncHandler with the resulting selection.
*
* @param search_str The string to search for in the document
* @param match_case Set to true for case-sensitive search
* @param match_whole_word Set to true to match whole words only
* @param search_up Set to true to search up through the document
* @param reg_exp Set to true to interpret search_str as a regular expression
*
*/
- (void)FindTextAsync: (NSString*)search_str match_case:  (BOOL)match_case match_whole_word:  (BOOL)match_whole_word search_up:  (BOOL)search_up reg_exp:  (BOOL)reg_exp;
- (BOOL)DownloaderUpdatePage: (SWIGTYPE_TRN_PDFDoc*)doc page_num:  (unsigned int)page_num obj_num:  (unsigned int)obj_num;
- (void)DownloaderUpdateOutline: (SWIGTYPE_TRN_PDFDoc*)doc;
- (void)DownloaderUpdateThumb: (SWIGTYPE_TRN_PDFDoc*)doc page_num:  (unsigned int)page_num obj_num:  (unsigned int)obj_num;
- (void)DownloaderFinishedDownload: (SWIGTYPE_TRN_PDFDoc*)doc;
- (void)DownloaderInitialized: (SWIGTYPE_TRN_PDFDoc*)doc;
- (void)OpenURLAsync: (NSString *)url cache_file:  (NSString*)cache_file password:  (NSString *)password;
- (void)OpenURL: (NSString *)url password:  (NSString *)password no_ownership:  (BOOL)no_ownership;
- (void)OpenURLWithCache: (NSString *)url password:  (NSString *)password no_ownership:  (BOOL)no_ownership cache_file:  (NSString*)cache_file;
- (void)SetRightToLeftLanguage: (BOOL)flag;
- (void)PushViewingStates;
- (void)PopViewingStates: (BOOL)restore;
- (void)SetFreezeTile: (BOOL)freeze;
- (int)GetCurCanvasId;
- (void)GetPageRects: (PDFRect*)rect page_rects_info:  (NSMutableArray*)page_rects_info;
- (void)DoProgressiveRender;
- (int)GetCellSideLength;
- (double)GetPageVGap;
- (double)GetPageHGap;
- (void)RequestRender;
- (BOOL)IsValidTile: (int)canvasNumber cellNumber:  (int)cellNumber;
- (void)PurgeMemory;
- (void)SetMemInfo: (double)total_mem mem_cap:  (double)mem_cap;
- (void)ExecuteAction: (Action*)action;
- (void)SetWrapperCreateTileProc: (Callback*)instance;
- (void)SetWrapperRemoveTileProc: (Callback*)instance;


@end


/**
* 'pdftron.PDF.HTML2PDF' is an optional PDFNet Add-On utility class that can be
* used to convert HTML web pages into PDF documents by using an external
* module (html2pdf).
*
* The html2pdf modules can be downloaded from http: www.pdftron.com/pdfnet/downloads.html.
*
* Users can convert HTML pages to PDF using the following operations:
* - Simple one line static method to convert a single web page to PDF.
* - Convert HTML pages from URL or string, plus optional table of contents, in user defined order.
* - Optionally configure settings for proxy, images, java script, and more for each HTML page.
* - Optionally configure the PDF output, including page size, margins, orientation, and more.
* - Optionally add table of contents, including setting the depth and appearance.
*
* The following code converts a single webpage to pdf
*
* @code
* using namespace pdftron;
* using namespace PDF;
*
* PDFDoc pdfdoc;
* if ( HTML2PDF::Convert(pdfdoc, "http://www.gutenberg.org/wiki/Main_Page") )
*		pdfdoc.Save(outputFile, SDF::SDFDoc::e_remove_unused, NULL);
* @endcode
*
* The following code demonstrates how to convert multiple web pages into one pdf,
* excluding the background, and with lowered image quality to save space.
*
* @code
* using namespace pdftron;
* using namespace PDF;
*
* HTML2PDF converter;
* converter.SetImageQuality(25);
*
* HTML2PDF::WebPageSettings settings;
* settings.SetPrintBackground(false);
*
* converter.InsertFromURL("http://www.gutenberg.org/wiki/Main_Page", settings);
*
* PDFDoc pdfdoc;
* if ( converter.Convert(pdfdoc) )
*		pdfdoc.Save(outputFile, SDF::SDFDoc::e_remove_unused, NULL);
* @endcode
*/
@interface HTML2PDF : NSObject
{


}





/**
* Add a web page to be converted. A single URL typically
* results in many PDF pages.
* @param url - HTML page, or relative path to local HTML page
*/
- (void)InsertFromURL: (NSString*)url;
/**
* Add a web page to be converted. A single URL typically
* results in many PDF pages.
*
* @param url - HTML page, or relative path to local HTML page
* @param settings - How the web page should be loaded and converted
*/
- (void)InsertFromURLWithSettings: (NSString*)url settings:  (WebPageSettings*)settings;
/**
* Convert HTML encoded in string.
*
* @param html - String containing HTML code.
*/
- (void)InsertFromHtmlString: (NSString*)html;
/**
* Convert HTML encoded in string.
*
* @param html - String containing HTML code.
* @param settings - How the HTML content described in html is loaded.
*/
- (void)InsertFromHtmlStringWithSettings: (NSString*)html settings:  (WebPageSettings*)settings;
/**
* Add a table of contents to the produced PDF.
*/
- (void)InsertTOC;
/**
* Add a table of contents to the produced PDF.
*
* @param settings - Settings for the table of contents.
*/
- (void)InsertTOCWithSettings: (TOCSettings*)settings;
/**
* Convert HTML documents and append the results
* to doc.
*
* @pre html2pdf module must be located in the working directory, or
* with the PDFNetC library.
*
* @return true if successful, otherwise false. Use
* @ref GetHttpErrorCode for possible HTTP errors.
*
* @param doc - Target PDF to which converted HTML pages will
* be appended to.
*
* @note Use @ref InsertFromURL and @ref InsertFromHtmlString to
* add HTML documents to be converted.
*/
- (BOOL)Convert: (PDFDoc*)doc;
/**
* Return the largest HTTP error code encountered during conversion
*
* @return the largest HTTP code greater then or equal to 300 encountered during loading
* of any of the supplied objects, if no such error code is found 0 is returned.
*
* @note This function will only return a useful result after @ref Convert has been called.
*/
- (int)GetHTTPErrorCode;
/**
* Display HTML to PDF conversion progress, warnings, and errors, to stdout?
*
* @param quiet - If false, progress information is sent to stdout during conversion.
*
* @note You can get the final results using GetLog.
*/
- (void)SetQuiet: (BOOL)quiet;
/**
* Get results of conversion, including errors and warnings, in human readable form.
*
* @return String containing results of conversion.
*/
- (NSString*)GetLog;
/**
* Set the only location that PDFNet will look for the html2pdf module.
*
* @param path - A folder or file path. If non-empty, PDFNet will only
* look in path for the html2pdf module, otherwise it will search in
* the default locations for the module.
*/
+ (void)SetModulePath: (NSString*)path;	/**
* Default constructor.
*/
- (id)init;

/**
* Set paper size of output PDF
*
* @param size - Paper size to use for produced PDF.
*/
- (void)SetPaperSize: (SWIGTYPE_PrinterMode__PaperSize*)size;
/**
* Manually set the paper dimensions of the produced PDF.
*
* @param width - Width of the page, e.g. "4cm".
* @param height - Height of the page, eg. "12in".
*
* @note Supported units are mm, cm, m, in, pica(pc), pixel(px) and point(pt).
*/
- (void)SetPaperSizeWithWidthAndHeight: (NSString*)width height:  (NSString*)height;
/**
* Set page orientation for output PDF.
*
* @param enable - If true generated PDF pages will be orientated to
* landscape, otherwise orientation will be portrait.
*/
- (void)SetLandscape: (BOOL)enable;
/**
* Change the DPI explicitly for the output PDF.
*
* @param dpi - Dots per inch, e.g. 80.
*
* @attention This has no effect on X11 based systems.
* @note Results also depend on @ref SetSmartShrinking.
*/
- (void)SetDPI: (int)dpi;
/**
* Add bookmarks to the PDF?
*
* @param enable - If true bookmarks will be generated for the
* produced PDF.
* @param depth - Maximum depth of the outline (e.g. 4).
*/
- (void)SetOutline: (BOOL)enable depth:  (int)depth;
/**
* Save outline to a xml file?
*
* @param xml_file - Path of where xml data representing outline
* of produced PDF should be saved to.
*/
- (void)DumpOutline: (NSString*)xml_file;
/**
* Use loss less compression to create PDF?
*
* @param enable - If true loss less compression will be used to
* create PDF.
*/
- (void)SetPDFCompression: (BOOL)enable;
/**
* Set margins of generated PDF.
*
* param@ top - Size of the top margin, e.g. "2cm".
* param@ bottom - Size of the bottom margin, e.g. "2cm".
* param@ left - Size of the left margin, e.g. "2cm".
* param@ right - Size of the right margin, e.g. "2cm".
*
* @note Supported units are mm, cm, m, in, pica(pc), pixel(px) and point(pt).
*/
- (void)SetMargins: (NSString*)top bottom:  (NSString*)bottom left:  (NSString*)left right:  (NSString*)right;
/**
* Maximum DPI to use for images in the generated PDF.
*
* @param dpi - Maximum dpi of images in produced PDF, e.g. 80.
*/
- (void)SetImageDPI: (int)dpi;
/**
* JPEG compression factor to use when generating PDF.
*
* @param quality - Compression factor, e.g. 92.
*/
- (void)SetImageQuality: (int)quality;
/**
* Path of file used for loading and storing cookies.
*
* @param path - Path to file used for loading and storing cookies.
*/
- (void)SetCookieJar: (NSString*)path;



@end


/**
* Stamper is a utility class that can be used to stamp PDF pages with text, images,
* or vector art (including another PDF page) in only a few lines of code.
*
* Although Stamper is very simple to use compared to ElementBuilder/ElementWriter
* it is not as powerful or flexible. In case you need full control over PDF creation
* use ElementBuilder/ElementWriter to add new content to existing PDF pages as
* shown in the ElementBuilder sample project.
*/
@interface Stamper : NSObject
{


}





/**
* Stamper constructor
*
* @param size_type Specifies how the stamp will be sized
*		-e_relative_scale: Stamp size is relative to the size of the crop box of
*		the destination page. 'a' is a percentage of the width of the crop box
*		(e.g.: 0.5 is 50% of the width of the crop box) 'b' is a percentage of the
*		height of the crop box. If 'a' <= 0 then only b will be used. If 'b' <= 0
*		then only 'a' will be used.
*
*		-e_absolute_scale: Stamp size is explicitly set. 'a' sets the width of
*		of the stamp's bounding box. 'b' sets the height of the stamp's bounding
*		box. The width and height are constant, regardless of the size of the
*		destination page's bounding box.
*
*		-e_font_size: This type only applies to text stamps. 'a' sets the font
*		size. 'b' is ignored.
* @param a @see size_type
* @param b @see size_type
*/
- (id)initWithSize_type: (SizeType)size_type a:  (double)a b:  (double)b;
/**
* Stamps an image to the given destination document at the set of page numbers
*
* @param dest_doc The document being stamped
* @param src_img The image that is being stamped to the document
* @param dest_pages The set of pages in the document being stamped
*/
- (void)StampImage: (PDFDoc*)dest_doc src_img:  (Image*)src_img dest_pages:  (PageSet*)dest_pages;
/**
* Stamps a PDF page to the given destination document at the set of page numbers
*
* @param dest_doc The document being stamped
* @param src_page The page that is being stamped to the document
* @param dest_pages The set of pages in the document being stamped
*/
- (void)StampPage: (PDFDoc*)dest_doc src_page:  (Page*)src_page dest_pages:  (PageSet*)dest_pages;
/**
* Stamps text to the given destination document at the set of page numbers
*
* @param dest_doc The document being stamped
* @param src_txt The image that is being stamped to the document
* @param dest_pages The set of pages in the document being stamped
*/
- (void)StampText: (PDFDoc*)dest_doc src_txt:  (NSString*)src_txt dest_pages:  (PageSet*)dest_pages;
/**
*
* Defines the font of the stamp. (This only applies to text-based stamps)
*
* @param font The font of the text stamp
*/
- (void)SetFont: (Font*)font;
/**
* Sets the font color (This only effects text-based stamps)
*
* @param font_color The color of the font
*/
- (void)SetFontColor: (ColorPt*)color;
/**
* Sets the opacity value for the stamp
*
* @param opacity The opacity value of the stamp
*/
- (void)SetOpacity: (double)opacity;
/**
* Rotates the stamp by the given number of degrees
*
* @param rotation Rotation in degrees
*/
- (void)SetRotation: (double)rotation;
/**
* Specifies if the stamp is to be stamped in the background or the foreground.
*
* @param background A flag specifying if the stamp should be added
* as a background layer to the destination page
*/
- (void)SetAsBackground: (BOOL)background;
/**
* Specifies if the stamp is to be stamped as an annotation.
*
* @param annotation A flag specifying if the stamp should be added
* as an annotation or not
*
* @note Stamps created with this setting do not work with SetAsBackground,
* HasStamps, and DeleteStamps, if annotation is true.
*/
- (void)SetAsAnnotation: (BOOL)annotation;
/**
* @param on_screen Specifies if the watermark will be displayed on screen
*/
- (void)ShowsOnScreen: (BOOL)on_screen;
/**
* @param on_print Specifies if the watermark will be displayed when printed
*/
- (void)ShowsOnPrint: (BOOL)on_print;
/**
* Sets the horizontal and vertical position of the stamp.
*
* @see SetAlignment
*
* @param horizontal_distance Horizontal distance from left, right or center of crop box
* @param vert_dist Vertical distance from top, bottom or center of crop box
* @param percentage If true, horizontal_distance is a percentage of the crop
* box width (e.g.: 0.5 is 50% of the width of the crop box) and vertical_distance
* is a percentage of the crop box height. If false, horizontal_distance and
* vertical_distance is measured in points.
*/
- (void)SetPosition: (double)horizontal_distance vertical_distance:  (double)vertical_distance percentage:  (BOOL)percentage;
/**
* Sets the alignment for the x and y variables.
*
* @see SetPosition
*
* @param horizontal_alignment Can be set to e_left, e_center or e_right
*		e_left:	horizontal_distance measures the distance between the left edge of the stamp's
*			bounding box and the left edge of the crop box
*		e_center: horizontal_distance measures the distance between the horizontal bisector of the
*			stamp's bounding box and the horizontal bisector of the crop box
*		e_right: horizontal_distance measures the distance between the right edge of the stamp's
*			bounding box and the right edge of the crop box
*
* @param vert_alignment Can be set to e_top, e_center or e_bottom
*		e_bottom: vertical_distance measures the distance between the bottom edge of the stamp's
*			bounding box and the bottom edge of the crop box
*		e_center: vertical_distance measures the distance between the vertical bisector of the
*			stamp's bounding box and the vertical bisector of the crop box
*		e_top: vertical_distance measures the distance between the top edge of the stamp's
*			bounding box and the top edge of the crop box
*/
- (void)SetAlignment: (HorizontalAlignment)horizontal_alignment vertical_alignment:  (VerticalAlignment)vertical_alignment;
/**
* Sets the text alignment (note: this only applies to text watermarks)
*
* @param text_alignment Enumerator for text alignment (e_left, e_center, e_right)
*/
- (void)SetTextAlignment: (TextAlignment)text_alignment;
/**
* Sets the size of the stamp
*
* @param size_type Specifies how the stamp will be sized
*		-e_relative_scale: Stamp size is relative to the size of the crop box of
*		the destination page. 'a' is a percentage of the width of the crop box
*		(e.g.: 0.5 is 50% of the width of the crop box) 'b' is a percentage of the
*		height of the crop box. If 'a' <= 0 then only b will be used. If 'b' <= 0
*		then only 'a' will be used.
*
*		-e_absolute_scale: Stamp size is explicitly set. 'a' sets the width of
*		of the stamp's bounding box. 'b' sets the height of the stamp's bounding
*		box. The width and height are constant, regardless of the size of the
*		destination page's bounding box.
*
*		-e_font_size: This type only applies to text stamps. 'a' sets the font
*		size. 'b' is ignored.
*/
- (void)SetSize: (SizeType)size_type a:  (double)a b:  (double)b;
/**
* Deletes PDFTron stamps from document at given page numbers
*
* @param doc The document to delete stamps from
* @param page_set The set of pages to delete stamps from
*/
+ (void)DeleteStamps: (PDFDoc*)doc page_set:  (PageSet*)page_set;
/**
* Returns true if the given set of pages has at least one stamp
*
* @param doc The document that's being checked
* @param page_set The set of page that's being checked
*/
+ (BOOL)HasStamps: (PDFDoc*)doc page_set:  (PageSet*)page_set;



@end


/**
* TextExtractor is used to analyze a PDF page and extract words and logical
* structure within a given region. The resulting list of lines and words can
* be traversed element by element or accessed as a string buffer. The class
* also includes utility methods to extract PDF text as HTML or XML.
*
* Possible use case scenarios for TextExtractor include:
*  - Converting PDF pages to text or XML for content repurposing.
*  - Searching PDF pages for specific words or keywords.
*  - Indexing large PDF repositories for indexing or content
*    retrieval purposes (i.e. implementing a PDF search engine).
*  - Classifying or summarizing PDF documents based on their text content.
*  - Finding specific words for content editing purposes (such as splitting pages
*    based on keywords etc).
*
* The main task of TextExtractor is to interpret PDF pages and offer a
* simple to use API to:
*  - Normalize all text content to Unicode.
*  - Extract inferred logical structure (word by word, line by line,
*    or paragraph by paragraph).
*  - Extract positioning information for every line, word, or a glyph.
*  - Extract style information (such as information about the font, font size,
*    font styles, etc) for every line, word, or a glyph.
*  - Control the content analysis process. A number of options (such as
*    removal of text obscured by images) is available to let the user
*    direct the flow of content recognition algorithms that will meet their
*    requirements.
*  - Offer utility methods to convert PDF page content to text, XML, or HTML.
*
* Note: TextExtractor is analyzing only textual content of the page.
* This means that the rasterized (e.g. in scanned pages) or vectorized
* text (where glyphs are converted to path outlines) will not be recognized
* as text. Please note that it is still possible to extract this content
* using pdftron.PDF.ElementReader interface.
*
* In some cases TextExtractor may extract text that does not appear to
* be on the visible page (e.g. when text is obscured by an image or a
* rectangle). In these situations it is possible to use processing flags
* such as 'e_remove_hidden_text' and 'e_no_invisible_text' to remove
* hidden text.
*
* A sample use case (in C++):
*
* @code
* ... Initialize PDFNet ...
* PDFDoc doc(filein);
* doc.InitSecurityHandler();
* Page page = *doc.PageBegin();
* TextExtractor txt;
* txt.Begin(page, 0, TextExtractor::e_remove_hidden_text);
* UString text;
* txt.GetAsText(text);
* // or traverse words one by one...
* TextExtractor::Line line = txt.GetFirstLine(), lend;
* TextExtractor::Word word, wend;
* for (; line!=lend; line=line.GetNextLine()) ;
* @endcode
*
* A sample use case (in C#):
*
* @code
* ... Initialize PDFNet ...
* PDFDoc doc = new PDFDoc(filein);
* doc.InitSecurityHandler();
* Page page = doc.PageBegin().Current();
* TextExtractor txt = new TextExtractor();
* txt.Begin(page, 0, TextExtractor.ProcessingFlags.e_remove_hidden_text);
* string text = txt.GetAsText();
* // or traverse words one by one...
* TextExtractor.Word word;
* for (TextExtractor.Line line = txt.GetFirstLine(); line.IsValid(); line=line.GetNextLine()) ;
* @endcode
*
* For full sample code, please take a look at TextExtract sample project.
*/
@interface TextExtractor : NSObject
{


}





/**
* Constructor and destructor
*/
- (id)init;
/**
* Start reading the page.
*
* @param page Page to read.
* @param clip_ptr A pointer to the optional clipping rectangle. This
* parameter can be used to selectively read text from a given rectangle.
* @param flags A list of ProcessingFlags used to control text extraction
* algorithm.
*/
- (void)Begin: (Page*)page clip_ptr:  (PDFRect*)clip_ptr flags:  (unsigned int)flags;
/**
* @return the number of words on the page.
*/
- (int)GetWordCount;
/**
* Get all words in the current selection as a single string.
*
* @param out_str The string containing all words in the current
* selection. Words will be separated with space (i.e. ' ') or
* new line (i.e. '\n') characters.
*
* @param dehyphen If true, finds and removes hyphens that split words
* across two lines. Hyphens are often used a the end of lines as an
* indicator that a word spans two lines. Hyphen detection enables removal
* of hyphen character and merging of text runs to form a single word.
* This option has no effect on Tagged PDF files.
*/
- (NSString*)GetAsText: (BOOL)dehyphen;
/**
* Get all the characters that intersect an annotation.
*
* @param annot The annotation to intersect with.
*/
- (NSString*)GetTextUnderAnnot: (Annot*)annot;
/**
* Get text content in a form of an XML string.
*
* @param out_xml - The string containing XML output.
* @param xml_output_flags - flags controlling XML output. For more
* information, please see TextExtract::XMLOutputFlags.
*
* XML output will be encoded in UTF-8 and will have the following
* structure:
* @code
* <Page num="1 crop_box="0, 0, 612, 792" media_box="0, 0, 612, 792" rotate="0">
*  <Flow id="1">
*   <Para id="1">
*    <Line box="72, 708.075, 467.895, 10.02" style="font-family:Calibri; font-size:10.02; color: #000000;">
*      <Word box="72, 708.075, 30.7614, 10.02">PDFNet</Word>
*      <Word box="106.188, 708.075, 15.9318, 10.02">SDK</Word>
*      <Word box="125.617, 708.075, 6.22242, 10.02">is</Word>
*      ...
*    </Line>
*   </Para>
*  </Flow>
* </Page>
* @endcode
*
* The above XML output was generated by passing the following union of
* flags in the call to GetAsXML():
*   (TextExtractor::e_words_as_elements | TextExtractor::e_output_bbox | TextExtractor::e_output_style_info)
*
* In case 'xml_output_flags' was not specified, the default XML output
* would look as follows:
*
* <Page num="1 crop_box="0, 0, 612, 792" media_box="0, 0, 612, 792" rotate="0">
* <Flow id="1">
* <Para id="1">
*     <Line>PDFNet SDK is an amazingly comprehensive, high-quality PDF developer toolkit...</Line>
*     <Line>levels. Using the PDFNet PDF library, ...</Line>
*     ...
*   </Para>
*  </Flow>
* </Page>
* @endcode
*/
- (NSString*)GetAsXML: (unsigned int)xml_output_flags;
/**
* @return The number of lines of text on the selected page.
*/
- (int)GetNumLines;
/**
* @return The first line of text on the selected page.
*
* @note To traverse the list of all text lines on the page use line.GetNextLine().
* @note To traverse the list of all word on a given line use line.GetFirstWord().
*/
- (TextExtractorLine*)GetFirstLine;



@end


/**
* The result of running pdftron::PDF::TextSearch::Run()
*/
@interface SearchResult : NSObject
{


}





/**
* @return true if a match was found.
*/
- (BOOL)IsFound;
/**
* @return true if finished searching the entire document.
*/
- (BOOL)IsDocEnd;
/**
* @return true if finished searching a page.
*/
- (BOOL)IsPageEnd;
/**
* @return the number of the page with the match.
*/
- (int)GetPageNumber;
/**
* @return the string that matches the search pattern.
*/
- (NSString*)GetMatch;
/**
* @return the ambient string of the found string (computed only if
* 'e_ambient_string' is set).
*/
- (NSString*)GetAmbientString;
/**
* @return The Highlights info associated with the match (computed
* only if 'e_highlight' is set).
*/
- (Highlights*)GetHighlights;
- (id)init;

@end


/**
* TextSearch searches through a PDF document for a user-given search pattern.
* The current implementation supports both verbatim search and the search
* using regular expressions, whose detailed syntax can be found at:
*
* http://www.boost.org/doc/libs/release/libs/regex/doc/html/boost_regex/syntax/perl_syntax.html
*
* TextSearch also provides users with several useful search modes and extra
* information besides the found string that matches the pattern. TextSearch
* can either keep running until a matched string is found or be set to return
* periodically in order for the caller to perform any necessary updates
* (e.g., UI updates). It is also worth mentioning that the search modes can be
* changed on the fly while searching through a document.
*
* Possible use case scenarios for TextSearch include:
*  - Guide users of a PDF viewer (e.g. implemented by PDFViewCtrl) to places
*    where they are intersted in;
*  - Find interested PDF documents which contain certain patterns;
*  - Extract interested information (e.g., credit card numbers) from a set of files;
*  - Extract Highlight information (refer to the Highlights class for details) from
*    files for external use.
*
* Note:
*  - Since hyphens ('-') are frequently used in PDF documents to concatenate the two
*    broken pieces of a word at the end of a line, for example
*
*	  "TextSearch is powerful for finding patterns in PDF files; yes, it is really pow-
*     erful."
*
*    a search for "powerful" should return both instances. However, not all end-of-line
*    hyphens are hyphens added to connect a broken word; some of them could be "real"
*    hyphens. In addition, an input search pattern may also contain hyphens that complicate
*    the situation. To tackle this problem, the following conventions are adopted:
*
*    a)When in the verbatim search mode and the pattern contains no hyphen, a matching
*      string is returned if it is exactly the same or it contains end-of-line
*      or start-of-line hyphens. For example, as mentioned above, a search for "powerful"
*      would return both instances.
*    b)When in verbatim search mode and the pattern contains one or multiple hyphens, a
*      matching string is returned only if the string matches the pattern exactly. For
*      example, a search for "pow-erful" will only return the second instance, and a search
*      for "power-ful" will return nothing.
*    c)When searching using regular expressions, hyphens are not taken care implicitly.
*      Users should take care of it themselves. For example, in order to find both the
*      "powerful" instances, the input pattern can be "pow-;erful".
*
* A sample use case (in C++):
*
* @code
* //... Initialize PDFNet ...
* PDFDoc doc(filein);
* doc.InitSecurityHandler();
* int page_num;
* char buf[32];
* UString result_str, ambient_string;
* Highlights hlts;
* TextSearch txt_search;
* TextSearch::Mode mode = TextSearch::e_whole_word | TextSearch::e_page_stop;
* UString pattern( "joHn sMiTh" );
*
* //PDFDoc doesn't allow simultaneous access from different threads. If this
* //document could be used from other threads (e.g., the rendering thread inside
* //PDFView/PDFViewCtrl, if used), it is good practice to lock it.
* //Notice: don't forget to call doc.Unlock() to avoid deadlock.
* doc.Lock();
*
* txt_search.Begin( doc, pattern, mode );
* while ( true )
* ;
*
* //unlock the document to avoid deadlock.
* doc.UnLock();
* @endcode
*
*
* For a full sample, please take a look at the TextSearch sample project.
*/
@interface TextSearch : NSObject
{


}





/**
* Constructor and destructor.
*/
- (id)init;
/**
* Initialize for search process. This should be called before starting the actual search
* with method Run().
*
* @param doc the PDF document to search in.
* @param pattern the pattern to search for. When regular expression is used, it contains
*        the expression, and in verbatim mode, it is the exact string to search for.
* @param mode the mode of the search process.
* @param start_page the start page of the page range to search in. The default value is -1
*        indicating the range starts from the first page.
* @param end_page the end page of the page range to search in. The default value is -1
*        indicating the range ends at the last page.
* @return true if the initialization has succeeded.
*/
- (BOOL)Begin: (PDFDoc*)doc pattern:  (NSString*)pattern mode:  (unsigned int)mode start_page:  (int)start_page end_page:  (int)end_page;
/**
* Search the document and returns upon the following circumstances:
* a)Reached the end of the document;
* b)Reached the end of a page (if set to return by specifying mode 'e_page_stop' );
* c)Found an instance matching the search pattern.
*
* Note that this method should be called in a loop in order to find all matching instances;
* in other words, the search is conducted in an incremental fashion.
*/
- (SearchResult*)Run;
/**
* Set the current search pattern. Note that it is not necessary to call this method since
* the search pattern is already set when calling the Begin() method. This method is provided
* for users to change the search pattern while searching through a document.
*
* @param pattern the search pattern to set.
* @return true if the setting has succeeded.
*/
- (BOOL)SetPattern: (NSString*)pattern;
/**
* Retrieve the current search mode.
* @return the current search mode.
*/
- (unsigned int)GetMode;
/**
* Set the current search mode. For example, the following code turns on the regular
* expressions:
*
*	TextSearch ts;
*   ...
*   TextSearch::Mode mode = ts.GetMode();
*   mode |= TextSearch::e_reg_expression;
*   ts.SetMode(mode);
*   ...
*
* @param mode the search mode to set.
*/
- (void)SetMode: (unsigned int)mode;
/**
* Retrieve the number of the current page that is searched in.
* If the returned value is -1, it indicates the search process has not been initialized
* (e.g., Begin() is not called yet); if the returned value is 0, it indicates the search
* process has finished, and if the returned value is positive, it is a valid page number.
* @return the current page number.
*/
- (int)GetCurrentPage;



@end


/**
* Class used to customize the appearance of the optional redaction overlay.
*/
@interface Appearance : NSObject
{


}





/**
* If RedactionOverlay is set to true, Redactor will draw an overlay
* covering all redacted regions. The rest of properties in the
* Appearance class defines visual properties of the overlay.
* If false the overlay region will not be drawn.
*/
- (void)setRedactionOverlay: (BOOL)value;
- (BOOL)getRedactionOverlay;
/**
* PositiveOverlayColor defines the overlay background color in RGB color space for positive redactions.
*/
- (void)setPositiveOverlayColor: (SWIGTYPE_ColorPt*)value;
- (SWIGTYPE_ColorPt*)getPositiveOverlayColor;
/**
* NegativeOverlayColor defines the overlay background color in RGB color space for negative redactions.
*/
- (void)setNegativeOverlayColor: (SWIGTYPE_ColorPt*)value;
- (SWIGTYPE_ColorPt*)getNegativeOverlayColor;
/**
* Border specifies if the overlay will be surrounded by a border.
*/
- (void)setBorder: (BOOL)value;
- (BOOL)getBorder;
/**
* Specifies if the text (e.g. "Redacted" etc.) should be placed on
* top of the overlay. The remaining properties relate to the positioning,
* and styling of the overlay text.
*/
- (void)setUseOverlayText: (BOOL)value;
- (BOOL)getUseOverlayText;
/**
* Specifies the font used to represent the text in the overlay.
*/
- (void)setTextFont: (Font*)value;
- (Font*)getTextFont;
- (void)setMinFontSize: (double)value;
- (double)getMinFontSize;
/**
* Specifies the minimum and maximum font size used to represent the text in the overlay.
*/
- (void)setMaxFontSize: (double)value;
- (double)getMaxFontSize;
/**
* Specifies the color used to paint the text in the overlay (in RGB).
*/
- (void)setTextColor: (ColorPt*)value;
- (ColorPt*)getTextColor;
/**
* Specifies the horizontal text alignment in the overlay:
*   align<0  -> text will be left aligned.
*   align==0 -> text will be center aligned.
*   align>0  -> text will be right aligned.
*/
- (void)setHorizTextAlignment: (int)value;
- (int)getHorizTextAlignment;
/**
* Specifies the vertical text alignment in the overlay:
*   align<0  -> text will be top aligned.
*   align==0 -> text will be center aligned.
*   align>0  -> text will be bottom aligned.
*/
- (void)setVertTextAlignment: (int)value;
- (int)getVertTextAlignment;
- (id)init;

@end


/**
* PDF Redactor is a separately licensable Add-on that offers options to remove
* (not just covering or obscuring) content within a region of PDF.
* With printed pages, redaction involves blacking-out or cutting-out areas of
* the printed page. With electronic documents that use formats such as PDF,
* redaction typically involves removing sensitive content within documents for
* safe distribution to courts, patent and government institutions, the media,
* customers, vendors or any other audience with restricted access to the content.
*
* The redaction process in PDFNet consists of two steps:
*
*  a) Content identification: A user applies redact annotations that specify the
* pieces or regions of content that should be removed. The content for redaction
* can be identified either interactively (e.g. using 'pdftron.PDF.PDFViewCtrl'
* as shown in PDFView sample) or programmatically (e.g. using 'pdftron.PDF.TextSearch'
* or 'pdftron.PDF.TextExtractor'). Up until the next step is performed, the user
* can see, move and redefine these annotations.
*  b) Content removal: Using 'pdftron.PDF.Redactor.Redact()' the user instructs
* PDFNet to apply the redact regions, after which the content in the area specified
* by the redact annotations is removed. The redaction function includes number of
* options to control the style of the redaction overlay (including color, text,
* font, border, transparency, etc.).
*
* PDFTron Redactor makes sure that if a portion of an image, text, or vector graphics
* is contained in a redaction region, that portion of the image or path data is
* destroyed and is not simply hidden with clipping or image masks. PDFNet API can also
* be used to review and remove metadata and other content that can exist in a PDF
* document, including XML Forms Architecture (XFA) content and Extensible Metadata
* Platform (XMP) content.
*/
@interface Redactor : NSObject
{


}





/**
* Apply the redactions specified in red_array to the PDFDoc doc.
*
* @param doc - the document to redact
* @param red_arr - an array of redaction regions.
* @param app - optional parameter used to customize the appearance of the redaction overlay.
* @param ext_neg_mode - if true, negative redactions expand beyond the page to remove
* content from other pages in the document. if false, the redaction will be localized
* to the given page.
* @param page_coord_sys - if true, redaction coordinates are relative to the lower-left corner of the page,
* otherwise the redaction coordinates are defined in PDF user coordinate system (which may or may not coincide with
* page coordinates).
*/
+ (void)Redact: (PDFDoc*)doc red_arr:  (VectorRedaction*)red_arr app:  (Appearance*)app ext_neg_mode:  (BOOL)ext_neg_mode page_coord_sys:  (BOOL)page_coord_sys;
- (id)init;

@end



#endif // PDFNetOBJC_H


