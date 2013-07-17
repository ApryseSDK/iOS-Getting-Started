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

typedef enum ReferencePos {  e_begin = SEEK_SET,
  e_end = SEEK_END,
  e_cur = SEEK_CUR}ReferencePos;

typedef enum OpenMode {  e_read_mode,
  e_write_mode,
  e_append_mode}OpenMode;

typedef enum FlattenThresholdFlag {  e_flattenthreshold_very_strict,
  e_flattenthreshold_strict,
  e_flattenthreshold_default,
  e_flattenthreshold_keep_most,
  e_flattenthreshold_keep_all}FlattenThresholdFlag;

typedef enum FlattenFlag {  e_flatten_off,
  e_flatten_simple,
  e_flatten_fast}FlattenFlag;

typedef enum AnnotationOutputFlag {  e_internal_xfdf,
  e_external_xfdf,
  e_flatten}AnnotationOutputFlag;

typedef enum ProxyType {  e_p_default,
  e_p_none,
  e_http,
  e_socks5}ProxyType;

typedef enum ErrorHandling {  e_abort,
  e_skip,
  e_ignore}ErrorHandling;

typedef enum CompressionMode {  e_retain,
  e_flate,
  e_jpeg,
  e_jpeg2000,
  e_none}CompressionMode;

typedef enum DownsampleMode {  e_off,
  e_default}DownsampleMode;

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

typedef enum SaveOptions {  e_incremental = 0x01,
  e_remove_unused = 0x02,
  e_hex_strings = 0x04,
  e_omit_xref = 0x08,
  e_linearized = 0x10,
  e_compatibility = 0x20}SaveOptions;

typedef enum ObjType {  e_null,
  e_bool,
  e_number,
  e_name,
  e_string,
  e_dict,
  e_array,
  e_stream}ObjType;

typedef enum Permission {  e_owner = 1,
  e_doc_open,
  e_doc_modify,
  e_print,
  e_print_high,
  e_extract_content,
  e_mod_annot,
  e_fill_forms,
  e_access_support,
  e_assemble_doc}Permission;

typedef enum AlgorithmType {  e_RC4_40 = 1,
  e_RC4_128,
  e_AES}AlgorithmType;

typedef enum OverloadedFunction {  has_CloneProc = 0x01,
  has_AuthProc = 0x02,
  has_AuthFailedProc = 0x04,
  has_GetAuthDataProc = 0x08,
  has_EditSecurDataProc = 0x10,
  has_FillEncDictProc = 0x20}OverloadedFunction;

typedef enum FunctionType {  e_sampled = 0,
  e_exponential = 2,
  e_stitching = 3,
  e_postscript = 4}FunctionType;

typedef enum ColorSpaceType {  e_device_gray,
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
  e_c_null}ColorSpaceType;

typedef enum Box {  e_media,
  e_crop,
  e_bleed,
  e_trim,
  e_art}Box;

typedef enum Rotate {  e_0,
  e_90,
  e_180,
  e_270}Rotate;

typedef enum GStateAttribute {  e_transform = 0,
  e_rendering_intent,
  e_stroke_cs,
  e_stroke_color,
  e_fill_cs,
  e_fill_color,
  e_line_width,
  e_line_cap,
  e_line_join,
  e_flatness,
  e_miter_limit,
  e_dash_pattern,
  e_char_spacing,
  e_word_spacing,
  e_horizontal_scale,
  e_leading,
  e_font,
  e_font_size,
  e_text_render_mode,
  e_text_rise,
  e_text_knockout,
  e_text_pos_offset,
  e_blend_mode,
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
  e_g_null}GStateAttribute;

typedef enum LineCap {  e_butt_cap = 0,
  e_round_cap,
  e_square_cap}LineCap;

typedef enum LineJoin {  e_miter_join = 0,
  e_round_join,
  e_bevel_join}LineJoin;

typedef enum TextRenderingMode {  e_fill_text = 0,
  e_stroke_text,
  e_fill_stroke_text,
  e_invisible_text,
  e_fill_clip_text,
  e_stroke_clip_text,
  e_fill_stroke_clip_text,
  e_clip_text}TextRenderingMode;

typedef enum RenderingIntent {  e_absolute_colorimetric,
  e_relative_colorimetric,
  e_saturation,
  e_perceptual}RenderingIntent;

typedef enum BlendMode {  e_bl_compatible = 0,
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
  e_bl_color}BlendMode;

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

typedef enum TextJustification {  e_left_justified,
  e_centered,
  e_right_justified}TextJustification;

typedef enum AnnotType {  e_Text,
  e_Link,
  e_FreeText,
  e_Line,
  e_Square,
  e_Circle,
  e_Polygon,
  e_Polyline,
  e_Highlight,
  e_Underline,
  e_Squiggly,
  e_StrikeOut,
  e_Stamp,
  e_Caret,
  e_Ink,
  e_Popup,
  e_FileAttachment,
  e_Sound,
  e_Movie,
  e_Widget,
  e_Screen,
  e_PrinterMark,
  e_TrapNet,
  e_Watermark,
  e_3D,
  e_Redact,
  e_Projection,
  e_RichMedia,
  e_Unknown}AnnotType;

typedef enum AnnotFlag {  e_invisible,
  e_hidden,
  e_print_annot,
  e_no_zoom,
  e_no_rotate,
  e_no_view,
  e_annot_read_only,
  e_locked,
  e_toggle_no_view,
  e_locked_contents}AnnotFlag;

typedef enum AnnotationState {  e_normal,
  e_rollover,
  e_down}AnnotationState;

typedef enum BorderEffect {  e_None,
  e_Cloudy}BorderEffect;

typedef enum FileIcon {  e_Graph,
  e_PushPin,
  e_Paperclip,
  e_Tag,
  e_fi_Unknown}FileIcon;

typedef enum FitType {  e_XYZ,
  e_Fit,
  e_FitH,
  e_FitV,
  e_FitR,
  e_FitB,
  e_FitBH,
  e_FitBV}FitType;

typedef enum ActionType {  e_GoTo,
  e_GoToR,
  e_GoToE,
  e_Launch,
  e_Thread,
  e_URI,
  e_a_sound,
  e_a_Movie,
  e_Hide,
  e_Named,
  e_SubmitForm,
  e_ResetForm,
  e_ImportData,
  e_JavaScript,
  e_SetOCGState,
  e_Rendition,
  e_Trans,
  e_GoTo3DView,
  e_RichMediaExecute,
  e_a_Unknown}ActionType;

typedef enum FormActionFlag {  e_exclude = 0,
  e_include_no_value_fields = 1,
  e_export_format = 2,
  e_get_method = 3,
  e_submit_coordinates = 4,
  e_xfdf = 5,
  e_include_append_saves = 6,
  e_include_annotations = 7,
  e_submit_pdf = 8,
  e_canonical_format = 9,
  e_excl_non_user_annots = 10,
  e_excl_F_key = 11,
  e_embed_form = 13}FormActionFlag;

typedef enum EndingStyle {  e_l_Square,
  e_l_Circle,
  e_Diamond,
  e_OpenArrow,
  e_ClosedArrow,
  e_Butt,
  e_ROpenArrow,
  e_RClosedArrow,
  e_Slash,
  e_l_None,
  e_l_Unknown}EndingStyle;

typedef enum LineIntentType {  e_LineArrow,
  e_LineDimension,
  e_l_null}LineIntentType;

typedef enum CapPos {  e_Inline,
  e_Top}CapPos;

typedef enum IntentName {  e_f_FreeText,
  e_FreeTextCallout,
  e_FreeTextTypeWriter,
  e_f_Unknown}IntentName;

typedef enum LinkHighlightingMode {  e_l_none,
  e_invert,
  e_outline,
  e_push}LinkHighlightingMode;

typedef enum PolyLineIntentType {  e_PolygonCloud,
  e_PolyLineDimension,
  e_PolygonDimension,
  e_p_Unknown}PolyLineIntentType;

typedef enum QuadForm {  e_LeftJustified,
  e_Centered,
  e_RightJustified,
  e_r_None}QuadForm;

typedef enum RubberStampIcon {  e_Approved,
  e_Experimental,
  e_NotApproved,
  e_AsIs,
  e_Expired,
  e_NotForPublicRelease,
  e_Confidential,
  e_Final,
  e_Sold,
  e_Departmental,
  e_ForComment,
  e_TopSecret,
  e_ForPublicRelease,
  e_Draft,
  e_r_Unknown}RubberStampIcon;

typedef enum ScreenIconCaptionRelation {  e_NoIcon,
  e_NoCaption,
  e_CBelowI,
  e_CAboveI,
  e_CRightILeft,
  e_CLeftIRight,
  e_COverlayI}ScreenIconCaptionRelation;

typedef enum ScreenScaleCondition {  e_Always,
  e_WhenBigger,
  e_WhenSmaller,
  e_Never}ScreenScaleCondition;

typedef enum ScreenScaleType {  e_Anamorphic,
  e_Proportional}ScreenScaleType;

typedef enum SoundIcon {  e_Speaker,
  e_Mic,
  e_s_Unknown}SoundIcon;

typedef enum TextIcon {  e_Comment,
  e_Key,
  e_Help,
  e_NewParagraph,
  e_Paragraph,
  e_Insert,
  e_Note,
  e_t_Unknown}TextIcon;

typedef enum WidgetHighlightingMode {  e_w_none,
  e_w_invert,
  e_w_outline,
  e_w_push,
  e_toggle}WidgetHighlightingMode;

typedef enum WidgetIconCaptionRelation {  e_w_NoIcon,
  e_w_NoCaption,
  e_w_CBelowI,
  e_w_CAboveI,
  e_w_CRightILeft,
  e_w_CLeftIRight,
  e_w_COverlayI}WidgetIconCaptionRelation;

typedef enum WidgetScaleCondition {  e_w_Always,
  e_w_WhenBigger,
  e_w_WhenSmaller,
  e_w_Never}WidgetScaleCondition;

typedef enum WidgetScaleType {  e_w_Anamorphic,
  e_w_Proportional}WidgetScaleType;

typedef enum OCDrawMode {  e_VisibleOC,
  e_AllOC,
  e_NoOC}OCDrawMode;

typedef enum VisibilityPolicyType {  e_AllOn,
  e_AnyOn,
  e_AnyOff,
  e_AllOff}VisibilityPolicyType;

typedef enum Conformance {  e_NoConformance = 0,
  e_Level1A,
  e_Level1B,
  e_Level2A,
  e_Level2B,
  e_Level2U,
  e_Level3A,
  e_Level3B,
  e_Level3U}Conformance;

typedef enum ErrorCode {  e_PDFA0_1_1 = 11,
  e_PDFA0_1_2 = 12,
  e_PDFA0_1_3 = 13,
  e_PDFA0_1_4 = 14,
  e_PDFA0_1_5 = 15,
  e_PDFA1_2_1 = 121,
  e_PDFA1_2_2 = 122,
  e_PDFA1_3_1 = 131,
  e_PDFA1_3_2 = 132,
  e_PDFA1_3_3 = 133,
  e_PDFA1_3_4 = 134,
  e_PDFA1_4_1 = 141,
  e_PDFA1_4_2 = 142,
  e_PDFA1_6_1 = 161,
  e_PDFA1_7_1 = 171,
  e_PDFA1_7_2 = 172,
  e_PDFA1_7_3 = 173,
  e_PDFA1_7_4 = 174,
  e_PDFA1_8_1 = 181,
  e_PDFA1_8_2 = 182,
  e_PDFA1_8_3 = 183,
  e_PDFA1_8_4 = 184,
  e_PDFA1_8_5 = 185,
  e_PDFA1_8_6 = 186,
  e_PDFA1_10_1 = 1101,
  e_PDFA1_11_1 = 1111,
  e_PDFA1_11_2 = 1112,
  e_PDFA1_12_1 = 1121,
  e_PDFA1_12_2 = 1122,
  e_PDFA1_12_3 = 1123,
  e_PDFA1_12_4 = 1124,
  e_PDFA1_12_5 = 1125,
  e_PDFA1_12_6 = 1126,
  e_PDFA1_13_1 = 1131,
  e_PDFA2_2_1 = 221,
  e_PDFA2_3_2 = 232,
  e_PDFA2_3_3 = 233,
  e_PDFA2_3_3_1 = 2331,
  e_PDFA2_3_3_2 = 2332,
  e_PDFA2_3_4_1 = 2341,
  e_PDFA2_4_1 = 241,
  e_PDFA2_4_2 = 242,
  e_PDFA2_4_3 = 243,
  e_PDFA2_4_4 = 244,
  e_PDFA2_5_1 = 251,
  e_PDFA2_5_2 = 252,
  e_PDFA2_6_1 = 261,
  e_PDFA2_7_1 = 271,
  e_PDFA2_8_1 = 281,
  e_PDFA2_9_1 = 291,
  e_PDFA2_10_1 = 2101,
  e_PDFA3_2_1 = 321,
  e_PDFA3_3_1 = 331,
  e_PDFA3_3_2 = 332,
  e_PDFA3_3_3_1 = 3331,
  e_PDFA3_3_3_2 = 3332,
  e_PDFA3_4_1 = 341,
  e_PDFA3_5_1 = 351,
  e_PDFA3_5_2 = 352,
  e_PDFA3_5_3 = 353,
  e_PDFA3_5_4 = 354,
  e_PDFA3_5_5 = 355,
  e_PDFA3_5_6 = 356,
  e_PDFA3_6_1 = 361,
  e_PDFA3_7_1 = 371,
  e_PDFA3_7_2 = 372,
  e_PDFA3_7_3 = 373,
  e_PDFA4_1 = 41,
  e_PDFA4_2 = 42,
  e_PDFA4_3 = 43,
  e_PDFA4_4 = 44,
  e_PDFA4_5 = 45,
  e_PDFA4_6 = 46,
  e_PDFA5_2_1 = 521,
  e_PDFA5_2_2 = 522,
  e_PDFA5_2_3 = 523,
  e_PDFA5_2_4 = 524,
  e_PDFA5_2_5 = 525,
  e_PDFA5_2_6 = 526,
  e_PDFA5_2_7 = 527,
  e_PDFA5_2_8 = 528,
  e_PDFA5_2_9 = 529,
  e_PDFA5_2_10 = 5210,
  e_PDFA5_2_11 = 5211,
  e_PDFA5_3_1 = 531,
  e_PDFA5_3_2_1 = 5321,
  e_PDFA5_3_2_2 = 5322,
  e_PDFA5_3_2_3 = 5323,
  e_PDFA5_3_2_4 = 5324,
  e_PDFA5_3_2_5 = 5325,
  e_PDFA5_3_3_1 = 5331,
  e_PDFA5_3_3_2 = 5332,
  e_PDFA5_3_3_3 = 5333,
  e_PDFA5_3_3_4 = 5334,
  e_PDFA5_3_4_0 = 5340,
  e_PDFA5_3_4_1 = 5341,
  e_PDFA5_3_4_2 = 5342,
  e_PDFA5_3_4_3 = 5343,
  e_PDFA6_1_1 = 611,
  e_PDFA6_1_2 = 612,
  e_PDFA6_2_1 = 621,
  e_PDFA6_2_2 = 622,
  e_PDFA6_2_3 = 623,
  e_PDFA7_2_1 = 721,
  e_PDFA7_2_2 = 722,
  e_PDFA7_2_3 = 723,
  e_PDFA7_2_4 = 724,
  e_PDFA7_2_5 = 725,
  e_PDFA7_3_1 = 731,
  e_PDFA7_3_2 = 732,
  e_PDFA7_3_3 = 733,
  e_PDFA7_3_4 = 734,
  e_PDFA7_3_5 = 735,
  e_PDFA7_3_6 = 736,
  e_PDFA7_3_7 = 737,
  e_PDFA7_3_8 = 738,
  e_PDFA7_3_9 = 739,
  e_PDFA7_5_1 = 751,
  e_PDFA7_8_1 = 781,
  e_PDFA7_8_2 = 782,
  e_PDFA7_8_3 = 783,
  e_PDFA7_8_4 = 784,
  e_PDFA7_8_5 = 785,
  e_PDFA7_8_6 = 786,
  e_PDFA7_8_7 = 787,
  e_PDFA7_8_8 = 788,
  e_PDFA7_8_9 = 789,
  e_PDFA7_8_10 = 7810,
  e_PDFA7_8_11 = 7811,
  e_PDFA7_8_12 = 7812,
  e_PDFA7_8_13 = 7813,
  e_PDFA7_8_14 = 7814,
  e_PDFA7_8_15 = 7815,
  e_PDFA7_8_16 = 7816,
  e_PDFA7_8_17 = 7817,
  e_PDFA7_8_18 = 7818,
  e_PDFA7_8_19 = 7819,
  e_PDFA7_8_20 = 7820,
  e_PDFA7_8_21 = 7821,
  e_PDFA7_8_22 = 7822,
  e_PDFA7_8_23 = 7823,
  e_PDFA7_8_24 = 7824,
  e_PDFA7_8_25 = 7825,
  e_PDFA7_8_26 = 7826,
  e_PDFA7_8_27 = 7827,
  e_PDFA7_8_28 = 7828,
  e_PDFA7_8_29 = 7829,
  e_PDFA7_8_30 = 7830,
  e_PDFA7_8_31 = 7831,
  e_PDFA7_11_1 = 7111,
  e_PDFA7_11_2 = 7112,
  e_PDFA7_11_3 = 7113,
  e_PDFA7_11_4 = 7114,
  e_PDFA7_11_5 = 7115,
  e_PDFA9_1 = 91,
  e_PDFA9_2 = 92,
  e_PDFA9_3 = 93,
  e_PDFA9_4 = 94,
  e_PDFA3_8_1 = 381,
  e_PDFA8_2_2 = 822,
  e_PDFA8_3_3_1 = 8331,
  e_PDFA8_3_3_2 = 8332,
  e_PDFA8_3_4_1 = 8341,
  e_PDFA1_2_3 = 123,
  e_PDFA1_10_2 = 1102,
  e_PDFA1_10_3 = 1103,
  e_PDFA1_12_10 = 11210,
  e_PDFA1_13_5 = 1135,
  e_PDFA2_3_10 = 2310,
  e_PDFA2_4_2_10 = 24220,
  e_PDFA2_4_2_11 = 24221,
  e_PDFA2_4_2_12 = 24222,
  e_PDFA2_4_2_13 = 24223,
  e_PDFA2_5_10 = 2510,
  e_PDFA2_5_11 = 2511,
  e_PDFA2_5_12 = 2512,
  e_PDFA2_8_3_1 = 2831,
  e_PDFA2_8_3_2 = 2832,
  e_PDFA2_8_3_3 = 2833,
  e_PDFA2_8_3_4 = 2834,
  e_PDFA2_8_3_5 = 2835,
  e_PDFA2_10_20 = 21020,
  e_PDFA2_10_21 = 21021,
  e_PDFA11_0_0 = 11000,
  e_PDFA6_2_11_8 = 62118,
  e_PDFA_LAST}ErrorCode;

typedef enum ContentItemType {  e_MCR,
  e_MCID,
  e_OBJR,
  e_c_Unknown}ContentItemType;

typedef enum PathSegmentType {  e_moveto = 1,
  e_lineto,
  e_cubicto,
  e_conicto,
  e_rect,
  e_closepath}PathSegmentType;

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

typedef enum Encoding {  e_IdentityH = 0,
  e_Indices}Encoding;

typedef enum FontType {  e_Type1,
  e_TrueType,
  e_MMType1,
  e_Type3,
  e_Type0,
  e_CIDType0,
  e_CIDType2}FontType;

typedef enum ShadingType {  e_function_shading,
  e_axial_shading,
  e_radial_shading,
  e_free_gouraud_shading,
  e_lattice_gouraud_shading,
  e_coons_shading,
  e_tensor_shading,
  e_s_null}ShadingType;

typedef enum PatternColorType {  e_uncolored_tiling_pattern,
  e_colored_tiling_pattern,
  e_shading,
  e_p_null}PatternColorType;

typedef enum TilingType {  e_constant_spacing,
  e_no_distortion,
  e_constant_spacing_fast_fill}TilingType;

typedef enum InputFilter {  e_i_none,
  e_i_jpeg,
  e_jp2,
  e_i_flate,
  e_g3,
  e_g4,
  e_ascii_hex}InputFilter;

typedef enum ElementType {  e_e_null,
  e_path,
  e_text_begin,
  e_text_obj,
  e_text_new_line,
  e_text_end,
  e_image,
  e_inline_image,
  e_e_shading,
  e_form,
  e_group_begin,
  e_group_end,
  e_marked_content_begin,
  e_marked_content_end,
  e_marked_content_point}ElementType;

typedef enum WriteMode {  e_underlay,
  e_overlay,
  e_replacement}WriteMode;

typedef enum Threshold {  e_threshold_very_strict,
  e_threshold_strict,
  e_threshold_default,
  e_threshold_keep_most,
  e_threshold_keep_all}Threshold;

typedef enum FlattenMode {  e_simple,
  e_fast}FlattenMode;

typedef enum PageLabelStyle {  e_decimal,
  e_roman_uppercase,
  e_roman_lowercase,
  e_alphabetic_uppercase,
  e_alphabetic_lowercase,
  e_pg_none}PageLabelStyle;

typedef enum PageSetFilter {  e_all,
  e_even,
  e_odd}PageSetFilter;

typedef enum PageMode {  e_UseNone,
  e_UseThumbs,
  e_UseBookmarks,
  e_FullScreen,
  e_UseOC,
  e_UseAttachments}PageMode;

typedef enum PageLayout {  e_Default,
  e_SinglePage,
  e_OneColumn,
  e_TwoColumnLeft,
  e_TwoColumnRight,
  e_TwoPageLeft,
  e_TwoPageRight}PageLayout;

typedef enum ViewerPref {  e_HideToolbar,
  e_HideMenubar,
  e_HideWindowUI,
  e_FitWindow,
  e_CenterWindow,
  e_DisplayDocTitle}ViewerPref;

typedef enum InsertFlag {  e_pd_none,
  e_insert_bookmark}InsertFlag;

typedef enum ExtractFlag {  e_forms_only,
  e_annots_only,
  e_both}ExtractFlag;

typedef enum DownloadedType {  e_downloadedtype_page = 0,
  e_downloadedtype_thumb,
  e_downloadedtype_named_dests,
  e_downloadedtype_outline,
  e_downloadedtype_finished,
  e_downloadedtype_failed,
  e_downloadedtype_opened}DownloadedType;

typedef enum RasterizerType {  e_BuiltIn,
  e_GDIPlus}RasterizerType;

typedef enum OverprintPreviewMode {  e_op_off = 0,
  e_op_on,
  e_op_pdfx_on}OverprintPreviewMode;

typedef enum PixelFormat {  e_rgba,
  e_bgra,
  e_rgb,
  e_bgr,
  e_gray,
  e_gray_alpha,
  e_cmyk}PixelFormat;

typedef enum CloudErrorCode {  STATUS_ERR,
  STATUS_OK,
  STATUS_NETWORK_ERR,
  STATUS_BAD_CREDENTIALS,
  STATUS_SERVICE_DOWN,
  STATUS_INVALID_OPERATION,
  STATUS_NUM}CloudErrorCode;

typedef enum CMSType {  e_lcms,
  e_icm,
  e_no_cms}CMSType;

typedef enum CharacterOrdering {  e_Identity = 0,
  e_Japan1 = 1,
  e_Japan2 = 2,
  e_GB1 = 3,
  e_CNS1 = 4,
  e_Korea1 = 5}CharacterOrdering;

typedef enum PagePresentationMode {  e_single_page = 1,
  e_single_continuous,
  e_facing,
  e_facing_continuous,
  e_facing_cover,
  e_facing_continuous_cover}PagePresentationMode;

typedef enum TextSelectionMode {  e_structural,
  e_rectangular}TextSelectionMode;

typedef enum PageViewMode {  e_fit_page = 0,
  e_fit_width,
  e_fit_height,
  e_zoom,
  PVM_SIZE}PageViewMode;

typedef enum SizeType {  e_relative_scale = 1,
  e_absolute_size = 2,
  e_s_font_size = 3}SizeType;

typedef enum HorizontalAlignment {  e_horizontal_left = -1,
  e_horizontal_center = 0,
  e_horizontal_right = 1}HorizontalAlignment;

typedef enum VerticalAlignment {  e_vertical_bottom = -1,
  e_vertical_center = 0,
  e_vertical_top = 1}VerticalAlignment;

typedef enum TextAlignment {  e_align_left = -1,
  e_align_center = 0,
  e_align_right = 1}TextAlignment;

typedef enum ProcessingFlags {  e_no_ligature_exp = 1,
  e_no_dup_remove = 2,
  e_punct_break = 4,
  e_remove_hidden_text = 8,
  e_no_invisible_text = 16}ProcessingFlags;

typedef enum XMLOutputFlags {  e_words_as_elements = 1,
  e_output_bbox = 2,
  e_output_style_info = 4}XMLOutputFlags;

typedef enum TextSearchModes {  e_reg_expression = 0x0001,
  e_case_sensitive = e_reg_expression << 1,
  e_whole_word = e_case_sensitive << 1,
  e_search_up = e_whole_word << 1,
  e_page_stop = e_search_up << 1,
  e_highlight = e_page_stop << 1,
  e_ambient_string = e_highlight << 1}TextSearchModes;



@interface Callback : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)RenderBeginEventProc;
+ (void)StaticRenderBeginEventProc: (SWIGTYPE_p_void*)data;
- (void)RenderFinishEventProc: (BOOL)cancelled;
+ (void)StaticRenderFinishEventProc: (SWIGTYPE_p_void*)data cancelled:  (BOOL)cancelled;
- (void)ErrorReportProc: (NSString *)message;
+ (void)StaticErrorReportProc: (NSString *)message data:  (SWIGTYPE_p_void*)data;
- (void)CurrentPageProc: (int)current_page num_pages:  (int)num_pages;
+ (void)StaticCurrentPageProc: (int)current_page num_pages:  (int)num_pages data:  (SWIGTYPE_p_void*)data;
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


@interface VectorObj : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (unsigned long)size;
- (unsigned long)capacity;
- (void)reserve: (unsigned long)n;
- (BOOL)isEmpty;
- (void)clear;
- (void)add: (Obj*)x;
- (Obj*)get: (int)i;
- (void)set: (int)i val:  (Obj*)val;
- (id)init;
@end


@interface VectorPage : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (unsigned long)size;
- (unsigned long)capacity;
- (void)reserve: (unsigned long)n;
- (BOOL)isEmpty;
- (void)clear;
- (void)add: (Page*)x;
- (Page*)get: (int)i;
- (void)set: (int)i val:  (Page*)val;
- (id)init;
@end


@interface VectorString : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (unsigned long)size;
- (unsigned long)capacity;
- (void)reserve: (unsigned long)n;
- (BOOL)isEmpty;
- (void)clear;
- (void)add: (NSString*)x;
- (NSString*)get: (int)i;
- (void)set: (int)i val:  (NSString*)val;
- (id)init;
@end


@interface VectorRedaction : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (unsigned long)size;
- (unsigned long)capacity;
- (void)reserve: (unsigned long)n;
- (BOOL)isEmpty;
- (void)clear;
- (void)add: (Redaction*)x;
- (Redaction*)get: (int)i;
- (void)set: (int)i val:  (Redaction*)val;
- (id)init;
@end


@interface VectorQuadPoint : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (unsigned long)size;
- (unsigned long)capacity;
- (void)reserve: (unsigned long)n;
- (BOOL)isEmpty;
- (void)clear;
- (void)add: (QuadPoint*)x;
- (QuadPoint*)get: (int)i;
- (void)set: (int)i val:  (QuadPoint*)val;
- (id)init;
@end


@interface TRN_matrix2d : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
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
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
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
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
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
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
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
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)setX: (double)value;
- (double)getX;
- (void)setY: (double)value;
- (double)getY;
- (id)init;
@end


@interface TRN_quadpoint : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
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
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (id)init;- (id)initWithPx: (double)px py:  (double)py;
@end


@interface Matrix2D : TRN_matrix2d
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Set: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
- (void)Concat: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
- (PDFPoint*)Mult: (PDFPoint*)pt;
- (Matrix2D*)Inverse;
- (void)Translate: (double)h v:  (double)v;
- (void)Scale: (double)h v:  (double)v;
+ (Matrix2D*)ZeroMatrix;
+ (Matrix2D*)IdentityMatrix;
+ (Matrix2D*)RotationMatrix: (double)angle;
- (id)initWithA: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
@end


@interface GSChangesIterator : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Destroy;
- (void)Next;
- (int)Current;
- (BOOL)HasNext;
- (id)init;
@end


@interface UInt32Iterator : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Destroy;
- (void)Next;
- (SWIGTYPE_p_unsigned_int*)Current;
- (BOOL)HasNext;
- (id)init;
@end


@interface CharIterator : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Destroy;
- (void)Next;
- (TRN_chardata*)Current;
- (BOOL)HasNext;
- (id)init;
@end


@interface Filter : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)AttachFilter: (Filter*)attach_filter;
- (Filter*)ReleaseAttachedFilter;
- (Filter*)GetAttachedFilter;
- (Filter*)GetSourceFilter;
- (NSString *)GetName;
- (NSString *)GetDecodeName;
- (unsigned long)Size;
- (void)Consume: (unsigned long)num_bytes;
- (unsigned long)Count;
- (unsigned long)SetCount: (unsigned long)new_count;
- (void)SetStreamLength: (unsigned long)bytes;
- (void)Flush;
- (void)FlushAll;
- (BOOL)IsInputFilter;
- (BOOL)CanSeek;
- (void)Seek: (long)offset origin:  (ReferencePos)origin;
- (long)Tell;
- (Filter*)CreateInputIterator;
- (NSString*)GetFilePath;
- (void)Destroy;
- (void)WriteToFile: (NSString*)path append:  (BOOL)append;
- (id)init;
@end


@interface ASCII85Encode : Filter
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (id)initWithInput_filter: (Filter*)input_filter line_width:  (int)line_width buf_sz:  (unsigned long)buf_sz;
@end


@interface FilterReader : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (int)Get;
- (int)Peek;
- (NSData*)Read: (unsigned long)buf_size;
- (void)AttachFilter: (Filter*)filter;
- (Filter*)GetAttachedFilter;
- (void)Seek: (long)offset origin:  (ReferencePos)origin;
- (long)Tell;
- (unsigned long)Count;
- (void)Flush;
- (void)FlushAll;
- (id)init;- (id)initWithFilter: (Filter*)filter;
@end


@interface FilterWriter : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)WriteUChar: (unsigned char)ch;
- (void)WriteInt16: (short)num;
- (void)WriteUInt16: (unsigned short)num;
- (void)WriteInt32: (int)num;
- (void)WriteUInt32: (unsigned int)num;
- (void)WriteInt64: (long long)num;
- (void)WriteUInt64: (unsigned long long)num;
- (void)WriteString: (NSString*)str;
- (void)WriteFilter: (FilterReader*)reader;
- (void)WriteLine: (NSString *)line eol:  (char)eol;
- (unsigned long)WriteBuffer: (NSData*)buf;
- (void)AttachFilter: (Filter*)filter;
- (Filter*)GetAttachedFilter;
- (void)Seek: (long)offset origin:  (ReferencePos)origin;
- (long)Tell;
- (unsigned long)Count;
- (void)Flush;
- (void)FlushAll;
- (id)init;- (id)initWithFilter: (Filter*)filter;
@end


@interface FlateEncode : Filter
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (id)initWithInput_filter: (Filter*)input_filter compression_level:  (int)compression_level buf_sz:  (unsigned long)buf_sz;
@end


@interface MappedFile : Filter
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (BOOL)Equivalent: (NSString*)ph1 ph2:  (NSString*)ph2;
- (unsigned long)FileSize;
- (id)initWithFilename: (NSString*)filename;
@end


@interface Redaction : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Destroy;
- (void)setMp_imp: (SWIGTYPE_TRN_Redaction*)value;
- (SWIGTYPE_TRN_Redaction*)getMp_imp;
- (id)initWithPage_num: (int)page_num bbox:  (PDFRect*)bbox negative:  (BOOL)negative text:  (NSString*)text;
@end


@interface SVGOutputOptions : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetEmbedImages: (BOOL)embed_images;
- (void)SetNoFonts: (BOOL)no_fonts;
- (void)SetNoUnicode: (BOOL)no_unicode;
- (void)SetIndividualCharPlacement: (BOOL)individual_char_placement;
- (void)SetRemoveCharPlacement: (BOOL)remove_char_placement;
- (id)init;
@end


@interface XPSOutputCommonOptions : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetPrintMode: (BOOL)print_mode;
- (void)SetDPI: (unsigned int)dpi;
- (void)SetRenderPages: (BOOL)render;
- (void)SetThickenLines: (BOOL)thicken;
- (id)init;
@end


@interface XPSOutputOptions : XPSOutputCommonOptions
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetOpenXps: (BOOL)openxps;
- (id)init;
@end


@interface XODOutputOptions : XPSOutputCommonOptions
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetOutputThumbnails: (BOOL)include_thumbs;
- (void)SetThumbnailSize: (unsigned int)size;
- (void)SetElementLimit: (unsigned int)element_limit;
- (void)SetOpacityMaskWorkaround: (BOOL)opacity_render;
- (void)SetMaximumImagePixels: (unsigned int)max_pixels;
- (void)SetFlattenContent: (FlattenFlag)flatten;
- (void)SetPreferJPG: (BOOL)prefer_jpg;
- (void)SetSilverlightTextWorkaround: (BOOL)workaround;
- (void)SetAnnotationOutput: (AnnotationOutputFlag)annot_output;
- (void)SetExternalParts: (BOOL)generate;
- (void)SetEncryptPassword: (NSString *)pass;
- (id)init;
@end


@interface HTMLOutputOptions : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetPreferJPG: (BOOL)prefer_jpg;
- (void)SetDPI: (unsigned int)dpi;
- (void)SetMaximumImagePixels: (unsigned int)max_pixels;
- (void)SetReflow: (BOOL)reflow;
- (void)SetScale: (double)scale;
- (id)init;
@end


@interface EPUBOutputOptions : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetExpanded: (BOOL)expanded;
- (void)SetReuseCover: (BOOL)reuse;
- (id)init;
@end


@interface Proxy : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetType: (ProxyType)type;
- (void)SetHost: (NSString*)host;
- (void)SetPort: (int)port;
- (void)SetUsername: (NSString*)username;
- (void)SetPassword: (NSString*)password;
- (void)Destroy;
- (void)setMp_impl: (SWIGTYPE_TRN_HTML2PDF_Proxy*)value;
- (SWIGTYPE_TRN_HTML2PDF_Proxy*)getMp_impl;
- (id)init;
@end


@interface WebPageSettings : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetPrintBackground: (BOOL)background;
- (void)SetLoadImages: (BOOL)load;
- (void)SetAllowJavaScript: (BOOL)enable;
- (void)SetSmartShrinking: (BOOL)enable;
- (void)SetMinimumFontSize: (int)size;
- (void)SetDefaultEncoding: (NSString*)encoding;
- (void)SetUserStyleSheet: (NSString*)url;
- (void)SetAllowPlugins: (BOOL)enable;
- (void)SetPrintMediaType: (BOOL)print;
- (void)SetIncludeInOutline: (BOOL)include;
- (void)SetUsername: (NSString*)username;
- (void)SetPassword: (NSString*)password;
- (void)SetJavaScriptDelay: (int)msec;
- (void)SetZoom: (double)zoom;
- (void)SetBlockLocalFileAccess: (BOOL)block;
- (void)SetStopSlowScripts: (BOOL)stop;
- (void)SetDebugJavaScriptOutput: (BOOL)forward;
- (void)SetLoadErrorHandling: (ErrorHandling)type;
- (void)SetExternalLinks: (BOOL)convert;
- (void)SetInternalLinks: (BOOL)convert;
- (void)SetProduceForms: (BOOL)forms;
- (void)SetProxy: (Proxy*)proxy;
- (void)Destroy;
- (void)setMp_impl: (SWIGTYPE_TRN_HTML2PDF_WebPageSettings*)value;
- (SWIGTYPE_TRN_HTML2PDF_WebPageSettings*)getMp_impl;
- (id)init;
@end


@interface TOCSettings : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetDottedLines: (BOOL)enable;
- (void)SetLinks: (BOOL)enable;
- (void)SetCaptionText: (NSString*)caption;
- (void)SetLevelIndentation: (int)indentation;
- (void)SetTextSizeShrink: (double)shrink;
- (void)SetXsl: (NSString*)style_sheet;
- (void)Destroy;
- (void)setMp_impl: (SWIGTYPE_TRN_HTML2PDF_TOCSettings*)value;
- (SWIGTYPE_TRN_HTML2PDF_TOCSettings*)getMp_impl;
- (id)init;
@end


@interface TextSettings : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SubsetFonts: (BOOL)subset;
- (void)EmbedFonts: (BOOL)embed;
- (id)init;
@end


@interface ImageSettings : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetImageDPI: (double)maximum resampling:  (double)resampling;
- (void)SetCompressionMode: (CompressionMode)mode;
- (void)SetDownsampleMode: (DownsampleMode)mode;
- (void)SetQuality: (unsigned int)quality;
- (void)ForceRecompression: (BOOL)force;
- (void)ForceChanges: (BOOL)force;
- (id)init;
@end


@interface MonoImageSettings : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetImageDPI: (double)maximum resampling:  (double)resampling;
- (void)SetCompressionMode: (MonoCompressionMode)mode;
- (void)SetDownsampleMode: (MonoDownsampleMode)mode;
- (void)ForceRecompression: (BOOL)force;
- (void)ForceChanges: (BOOL)force;
- (id)init;
@end


@interface OptimizerSettings : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetColorImageSettings: (ImageSettings*)settings;
- (void)SetGrayscaleImageSettings: (ImageSettings*)settings;
- (void)SetMonoImageSettings: (MonoImageSettings*)settings;
- (void)SetTextSettings: (TextSettings*)settings;
- (void)setM_color_image_settings: (ImageSettings*)value;
- (ImageSettings*)getM_color_image_settings;
- (void)setM_grayscale_image_settings: (ImageSettings*)value;
- (ImageSettings*)getM_grayscale_image_settings;
- (void)setM_mono_image_settings: (MonoImageSettings*)value;
- (MonoImageSettings*)getM_mono_image_settings;
- (void)setM_text_settings: (TextSettings*)value;
- (TextSettings*)getM_text_settings;
- (id)init;
@end


@interface TextExtractorStyle : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (Obj*)GetFont;
- (NSString*)GetFontName;
- (double)GetFontSize;
- (int)GetWeight;
- (BOOL)IsItalic;
- (BOOL)IsSerif;
- (NSMutableArray*)GetColor;
- (void)setMp_style: (SWIGTYPE_TRN_TextExtractorStyle*)value;
- (SWIGTYPE_TRN_TextExtractorStyle*)getMp_style;
- (id)init;
@end


@interface Highlight : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)setPage_num: (int)value;
- (int)getPage_num;
- (void)setPosition: (int)value;
- (int)getPosition;
- (void)setLength: (int)value;
- (int)getLength;
- (id)init;- (id)initWithPg: (int)pg pos:  (int)pos len:  (int)len;
@end


@interface BorderStyle : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Destroy;
- (BdStyle)GetStyle;
- (void)SetStyle: (BdStyle)style;
- (double)GetHR;
- (void)SetHR: (double)hr;
- (double)GetVR;
- (void)SetVR: (double)vr;
- (double)GetWidth;
- (void)SetWidth: (double)width;
- (NSMutableArray*)GetDash;
- (void)SetDash: (NSMutableArray*)dash;
- (id)initWithS: (BdStyle)s b_width:  (double)b_width b_hr:  (double)b_hr b_vr:  (double)b_vr;- (id)initWithS: (BdStyle)s b_width:  (double)b_width b_hr:  (double)b_hr b_vr:  (double)b_vr b_dash:  (NSMutableArray*)b_dash;
@end


@interface SDFDoc : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Close;
- (BOOL)IsEncrypted;
- (BOOL)InitSecurityHandler;
- (BOOL)InitStdSecurityHandler: (NSString *)password password_sz:  (int)password_sz;
- (BOOL)IsModified;
- (BOOL)IsFullSaveRequired;
- (Obj*)GetTrailer;
- (Obj*)GetObj: (unsigned int)obj_num;
- (Obj*)ImportObj: (Obj*)obj deep_copy:  (BOOL)deep_copy;
- (VectorObj*)ImportObjs: (VectorObj*)obj_list;
- (unsigned int)XRefSize;
- (void)ClearMarks;
- (void)SaveSDFDocToFile: (NSString*)path flags:  (unsigned int)flags header:  (NSString *)header;
- (NSData*)SaveSDFDocToBuf: (unsigned int)flags header:  (NSString *)header;
- (void)Save: (Filter*)stream flags:  (unsigned int)flags header:  (NSString *)header;
- (NSString *)GetHeader;
- (SecurityHandler*)GetSecurityHandler;
- (void)SetSecurityHandler: (SecurityHandler*)handler;
- (void)RemoveSecurity;
- (void)Swap: (unsigned int)obj_num1 obj_num2:  (unsigned int)obj_num2;
- (Obj*)CreateIndirectName: (NSString *)name;
- (Obj*)CreateIndirectArray;
- (Obj*)CreateIndirectBool: (BOOL)value;
- (Obj*)CreateIndirectDict;
- (Obj*)CreateIndirectNull;
- (Obj*)CreateIndirectNumber: (double)value;
- (Obj*)CreateIndirectString: (NSData*)value size:  (unsigned int)size;
- (Obj*)CreateIndirectStringWithStr: (NSString*)str;
- (Obj*)CreateIndirectStreamWithFilterReader: (FilterReader*)data filter_chain:  (Filter*)filter_chain;
- (Obj*)CreateIndirectStream: (FilterReader*)data;
- (Obj*)CreateIndirectStreamWithbuf: (NSString *)data data_size:  (unsigned long)data_size filter_chain:  (Filter*)filter_chain;
- (BOOL)IsLinearized;
- (Obj*)GetLinearizationDict;
- (Obj*)GetHintStream;
- (void)Lock;
- (void)Unlock;
- (BOOL)TryLock: (int)milliseconds;
- (void)LockRead;
- (void)UnlockRead;
- (BOOL)TryLockRead: (int)milliseconds;
- (NSString*)GetFileName;
- (void)EnableDiskCaching: (BOOL)use_cache_flag;
- (id)init;- (id)initWithFilepath: (NSString*)filepath;- (id)initWithStream: (Filter*)stream;- (id)initWithBuf: (NSData*)buf buf_size:  (unsigned long)buf_size;
@end


@interface Obj : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (ObjType)GetType;
- (BOOL)IsBool;
- (BOOL)IsNumber;
- (BOOL)IsNull;
- (BOOL)IsString;
- (BOOL)IsName;
- (BOOL)IsIndirect;
- (BOOL)IsContainer;
- (BOOL)IsDict;
- (BOOL)IsArray;
- (BOOL)IsStream;
- (SDFDoc*)GetDoc;
- (void)Write: (FilterWriter*)stream;
- (unsigned long)Size;
- (unsigned int)GetObjNum;
- (unsigned short)GetGenNum;
- (unsigned long)GetOffset;
- (BOOL)IsFree;
- (void)SetMark: (BOOL)mark;
- (BOOL)IsMarked;
- (BOOL)IsLoaded;
- (BOOL)IsValid;
- (BOOL)GetBool;
- (void)SetBool: (BOOL)b;
- (double)GetNumber;
- (void)SetNumber: (double)n;
- (NSData*)GetBuffer;
- (NSString*)GetAsPDFText;
- (void)SetString: (NSData*)value size:  (unsigned long)size;
- (void)SetStringWithStr: (NSString*)str;
- (NSString *)GetName;
- (void)SetName: (NSString *)name;
- (DictIterator*)GetDictIterator;
- (DictIterator*)Find: (NSString *)key;
- (Obj*)FindObj: (NSString *)key;
- (DictIterator*)Get: (NSString *)key;
- (Obj*)PutName: (NSString *)key name:  (NSString *)name;
- (Obj*)PutArray: (NSString *)key;
- (Obj*)PutBool: (NSString *)key value:  (BOOL)value;
- (Obj*)PutDict: (NSString *)key;
- (Obj*)PutNumber: (NSString *)key value:  (double)value;
- (Obj*)PutString: (NSString *)key value:  (NSString *)value;
- (Obj*)PutStringWithSize: (NSString *)key value:  (NSString *)value size:  (int)size;
- (Obj*)PutText: (NSString *)key value:  (NSString*)value;
- (void)PutNull: (NSString *)key;
- (Obj*)Put: (NSString *)key obj:  (Obj*)obj;
- (Obj*)PutRect: (NSString *)key x1:  (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
- (Obj*)PutMatrix: (NSString *)key value:  (Matrix2D*)value;
- (void)EraseDictElementWithKey: (NSString *)key;
- (void)EraseDictElementWithPos: (DictIterator*)pos;
- (BOOL)Rename: (NSString *)old_key new_key:  (NSString *)new_key;
- (Obj*)GetAt: (unsigned long)index;
- (Obj*)InsertName: (unsigned long)pos name:  (NSString *)name;
- (Obj*)InsertArray: (unsigned long)pos;
- (Obj*)InsertBool: (unsigned long)pos value:  (BOOL)value;
- (Obj*)InsertDict: (unsigned long)pos;
- (Obj*)InsertNumber: (unsigned long)pos value:  (double)value;
- (Obj*)InsertString: (unsigned long)pos value:  (NSString *)value;
- (Obj*)InsertStringWithSize: (unsigned long)pos value:  (NSString *)value size:  (int)size;
- (Obj*)InsertText: (unsigned long)pos value:  (NSString*)value;
- (Obj*)InsertNull: (unsigned long)pos;
- (Obj*)Insert: (unsigned long)pos obj:  (Obj*)obj;
- (Obj*)InsertRect: (unsigned long)pos x1:  (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
- (Obj*)InsertMatrix: (unsigned long)pos value:  (Matrix2D*)value;
- (Obj*)PushBackName: (NSString *)name;
- (Obj*)PushBackArray;
- (Obj*)PushBackBool: (BOOL)value;
- (Obj*)PushBackDict;
- (Obj*)PushBackNumber: (double)value;
- (Obj*)PushBackString: (NSString *)value;
- (Obj*)PushBackStringWithSize: (NSString *)value size:  (int)size;
- (Obj*)PushBackText: (NSString*)value;
- (Obj*)PushBackNull;
- (Obj*)PushBack: (Obj*)obj;
- (Obj*)PushBackRect: (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
- (Obj*)PushBackMatrix: (Matrix2D*)value;
- (void)EraseAt: (unsigned long)pos;
- (unsigned long)GetRawStreamLength;
- (Filter*)GetRawStream: (BOOL)decrypt;
- (Filter*)GetDecodedStream;
- (void)SetStreamData: (NSString *)data data_size:  (unsigned long)data_size filter_chain:  (Filter*)filter_chain;
- (BOOL)IsEqual: (Obj*)to;
- (id)init;
@end


@interface DictIterator : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Next;
- (Obj*)Key;
- (Obj*)Value;
- (BOOL)HasNext;
- (void)Destroy;
- (id)initWithC: (DictIterator*)c;
@end


@interface SecurityHandler : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (BOOL)GetPermission: (Permission)p;
- (int)GetKeyLength;
- (int)GetEncryptionAlgorithmID;
- (NSString *)GetHandlerDocName;
- (BOOL)IsModified;
- (void)SetModified: (BOOL)is_modified;
- (void)ChangeUserPassword: (NSString *)password;
- (void)ChangeUserPasswordWithLength: (NSString *)password pwd_length:  (unsigned long)pwd_length;
- (NSString *)GetUserPassword;
- (unsigned long)GetUserPasswordSize;
- (void)ChangeMasterPassword: (NSString *)password;
- (void)ChangeMasterPasswordWithLength: (NSString *)password pwd_length:  (unsigned long)pwd_length;
- (NSString *)GetMasterPassword;
- (unsigned long)GetMasterPasswordSize;
- (void)SetPermission: (Permission)perm value:  (BOOL)value;
- (void)ChangeRevisionNumber: (int)rev_num;
- (void)SetEncryptMetadata: (BOOL)encrypt_metadata;
- (int)GetRevisionNumber;
- (BOOL)IsUserPasswordRequired;
- (BOOL)IsMasterPasswordRequired;
- (BOOL)IsAES;
- (BOOL)IsAESWithStream: (Obj*)stream;
- (BOOL)IsRC4;
- (void)AuthorizeFailed;
- (BOOL)Authorize: (Permission)p;
- (BOOL)GetAuthorizationData: (Permission)req_opr;
- (BOOL)EditSecurityData: (SDFDoc*)doc;
- (Obj*)FillEncryptDict: (SDFDoc*)doc;
- (SecurityHandler*)Clone: (SWIGTYPE_TRN_SecurityHandler*)base;
- (void)InitPassword: (NSString *)password;
- (void)InitPasswordWithLength: (NSString *)password pwd_length:  (unsigned long)pwd_length;
- (void)SetDerived: (unsigned int)overloaded_funct;
- (SecurityHandler*)GetDerived;
- (id)initWithCrypt_type: (AlgorithmType)crypt_type;- (id)initWithName: (NSString *)name key_len:  (int)key_len enc_code:  (int)enc_code;- (id)init;
@end


@interface NameTree : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (NameTree*)Create: (SDFDoc*)doc name:  (NSString*)name;
+ (NameTree*)Find: (SDFDoc*)doc name:  (NSString*)name;
- (BOOL)IsValid;
- (DictIterator*)GetNameIteratorWithKey: (NSData*)key key_sz:  (int)key_sz;
- (DictIterator*)GetIterator;
- (Obj*)GetValue: (NSData*)key key_sz:  (int)key_sz;
- (void)Put: (NSData*)key key_sz:  (int)key_sz value:  (Obj*)value;
- (void)EraseNameTreeEntryWithKey: (NSData*)key key_sz:  (int)key_sz;
- (void)EraseNameTreeEntryWithPos: (DictIterator*)pos;
- (Obj*)GetSDFObj;
- (id)initWithName_tree: (Obj*)name_tree;
@end


@interface NumberTree : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (BOOL)IsValid;
- (DictIterator*)GetNumberIteratorWithKey: (int)key;
- (DictIterator*)GetIterator;
- (Obj*)GetValue: (int)key;
- (void)Put: (int)key value:  (Obj*)value;
- (void)EraseNumberTreeEntryWithKey: (int)key;
- (void)EraseNumberTreeEntryWithPos: (DictIterator*)pos;
- (Obj*)GetSDFObj;
- (id)initWithNumber_tree: (Obj*)number_tree;
@end


@interface ObjSet : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (Obj*)CreateName: (NSString *)name;
- (Obj*)CreateArray;
- (Obj*)CreateBool: (BOOL)value;
- (Obj*)CreateDict;
- (Obj*)CreateNull;
- (Obj*)CreateNumber: (double)value;
- (Obj*)CreateString: (NSString*)value;
- (void)Destroy;
- (id)init;
@end



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



@interface Function : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (FunctionType)GetType;
- (int)GetInputCardinality;
- (int)GetOutputCardinality;
- (NSMutableArray*)Eval: (NSMutableArray*)in_arr;
- (Obj*)GetSDFObj;
- (void)Destroy;
- (id)initWithFunct_dict: (Obj*)funct_dict;
@end


@interface ColorPt : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Set: (double)x y:  (double)y z:  (double)z w:  (double)w;
- (void)SetTintWithIndex: (int)colorant_index colorant_value:  (double)colorant_value;
- (double)Get: (int)colorant_index;
- (void)SetColorantNum: (int)num;
- (void)Destroy;
- (id)initWithX: (double)x y:  (double)y z:  (double)z w:  (double)w;
@end


@interface ColorSpace : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (ColorSpace*)CreateDeviceGray;
+ (ColorSpace*)CreateDeviceRGB;
+ (ColorSpace*)CreateDeviceCMYK;
+ (ColorSpace*)CreatePattern;
+ (ColorSpace*)CreateICCWithString: (SDFDoc*)doc filepath:  (NSString*)filepath;
+ (ColorSpace*)CreateICCWithStream: (SDFDoc*)doc stm:  (Filter*)stm;
+ (ColorSpace*)CreateICCWithBuf: (SDFDoc*)doc buf:  (NSData*)buf buf_sz:  (unsigned long)buf_sz;
- (ColorSpaceType)GetType;
- (Obj*)GetSDFObj;
- (int)GetComponentNum;
- (void)InitColor: (ColorPt*)out_colorants;
- (void)InitComponentRanges: (NSMutableArray*)out_decode_low out_decode_range:  (NSMutableArray*)out_decode_range;
- (ColorPt*)Convert2Gray: (ColorPt*)in_color;
- (ColorPt*)Convert2RGB: (ColorPt*)in_color;
- (ColorPt*)Convert2CMYK: (ColorPt*)in_color;
- (ColorSpace*)GetAlternateColorSpace;
- (ColorSpace*)GetBaseColorSpace;
- (int)GetHighVal;
- (ColorPt*)GetBaseColor: (unsigned char)color_idx;
- (BOOL)IsNone;
- (BOOL)IsAll;
- (Function*)GetTintFunction;
- (void)Destroy;
- (id)initWithColor_space: (Obj*)color_space;
@end


@interface PDFRect : TRN_rect
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Attach: (Obj*)rect;
- (BOOL)Update: (Obj*)rect;
- (void)Set: (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
- (double)Width;
- (double)Height;
- (BOOL)Contains: (double)x y:  (double)y;
- (BOOL)IntersectRect: (PDFRect*)rect1 rect2:  (PDFRect*)rect2;
- (void)Normalize;
- (void)InflateWithAmount: (double)amount;
- (void)InflateWithXY: (double)x y:  (double)y;
- (double)GetX1;
- (double)GetY1;
- (double)GetX2;
- (double)GetY2;
- (void)SetX1: (double)x1;
- (void)SetY1: (double)y1;
- (void)SetX2: (double)x2;
- (void)SetY2: (double)y2;
- (id)init;- (id)initWithRect: (Obj*)rect;- (id)initWithX1: (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
@end


@interface Word : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (int)GetNumGlyphs;
- (PDFRect*)GetBBox;
- (NSMutableArray*)GetQuad;
- (NSMutableArray*)GetGlyphQuad: (int)glyph_idx;
- (TextExtractorStyle*)GetCharStyle: (int)char_idx;
- (TextExtractorStyle*)GetStyle;
- (int)GetStringLen;
- (NSString*)GetString;
- (Word*)GetNextWord;
- (int)GetCurrentNum;
- (BOOL)IsValid;
- (void)setMp_word: (SWIGTYPE_TRN_TextExtractorWord*)value;
- (SWIGTYPE_TRN_TextExtractorWord*)getMp_word;
- (id)init;
@end


@interface TextExtractorLine : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (int)GetNumWords;
- (BOOL)IsSimpleLine;
- (PDFRect*)GetBBox;
- (NSMutableArray*)GetQuad;
- (Word*)GetFirstWord;
- (Word*)GetWord: (int)word_idx;
- (TextExtractorLine*)GetNextLine;
- (int)GetCurrentNum;
- (TextExtractorStyle*)GetStyle;
- (int)GetParagraphID;
- (int)GetFlowID;
- (BOOL)EndsWithHyphen;
- (BOOL)IsValid;
- (void)setMp_line: (SWIGTYPE_TRN_TextExtractorLine*)value;
- (SWIGTYPE_TRN_TextExtractorLine*)getMp_line;
- (id)initWithImpl: (SWIGTYPE_TRN_TextExtractorLine*)impl;
@end


@interface Page : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (BOOL)IsValid;
- (int)GetIndex;
- (PDFRect*)GetBox: (Box)type;
- (void)SetBox: (Box)type box:  (PDFRect*)box;
- (PDFRect*)GetCropBox;
- (void)SetCropBox: (PDFRect*)box;
- (PDFRect*)GetMediaBox;
- (void)SetMediaBox: (PDFRect*)box;
- (PDFRect*)GetVisibleContentBox;
- (Rotate)GetRotation;
- (void)SetRotation: (Rotate)angle;
- (double)GetPageWidth: (Box)box_type;
- (double)GetPageHeight: (Box)box_type;
- (Matrix2D*)GetDefaultMatrix: (BOOL)flip_y box_type:  (Box)box_type angle:  (Rotate)angle;
- (Obj*)GetAnnots;
- (unsigned int)GetNumAnnots;
- (Annot*)GetAnnot: (unsigned int)index;
- (void)AnnotInsert: (unsigned int)pos annot:  (Annot*)annot;
- (void)AnnotPushBack: (Annot*)annot;
- (void)AnnotPushFront: (Annot*)annot;
- (void)AnnotRemoveWithAnnot: (Annot*)annot;
- (void)AnnotRemoveWithIndex: (unsigned int)index;
- (void)Scale: (double)scale;
- (void)FlattenField: (TRNField*)filed;
- (BOOL)HasTransition;
- (double)GetUserUnitSize;
- (void)SetUserUnitSize: (double)unit_size;
- (Obj*)GetResourceDict;
- (Obj*)GetContents;
- (Obj*)GetSDFObj;
- (Obj*)FindInheritedAttribute: (NSString *)attrib;
- (Obj*)GetThumb;
- (id)initWithPage_dict: (Obj*)page_dict;
@end


@interface PageIterator : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Destroy;
- (void)Next;
- (Page*)Current;
- (BOOL)HasNext;
- (id)init;
@end


@interface Date : TRN_date
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (BOOL)IsValid;
- (void)SetCurrentTime;
- (void)Attach: (Obj*)d;
- (BOOL)Update: (Obj*)d;
- (unsigned short)GetYear;
- (unsigned char)GetMonth;
- (unsigned char)GetDay;
- (unsigned char)GetHour;
- (unsigned char)GetMinute;
- (unsigned char)GetSecond;
- (unsigned char)GetUT;
- (unsigned char)GetUTHour;
- (unsigned char)GetUTMin;
- (id)init;- (id)initWithD: (Obj*)d;- (id)initWithYear: (unsigned short)year month:  (char)month day:  (char)day hour:  (char)hour minute:  (char)minute second:  (char)second;
@end


@interface GState : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (Matrix2D*)GetTransform;
- (ColorSpace*)GetStrokeColorSpace;
- (ColorSpace*)GetFillColorSpace;
- (ColorPt*)GetStrokeColor;
- (PatternColor*)GetStrokePattern;
- (ColorPt*)GetFillColor;
- (PatternColor*)GetFillPattern;
- (double)GetFlatness;
- (LineCap)GetLineCap;
- (LineJoin)GetLineJoin;
- (double)GetLineWidth;
- (double)GetMiterLimit;
- (NSMutableArray*)GetDashes;
- (double)GetPhase;
- (double)GetCharSpacing;
- (double)GetWordSpacing;
- (double)GetHorizontalScale;
- (double)GetLeading;
- (Font*)GetFont;
- (double)GetFontSize;
- (TextRenderingMode)GetTextRenderMode;
- (double)GetTextRise;
- (BOOL)IsTextKnockout;
- (RenderingIntent)GetRenderingIntent;
+ (RenderingIntent)GetRenderingIntentType: (NSString *)name;
- (BlendMode)GetBlendMode;
- (double)GetFillOpacity;
- (double)GetStrokeOpacity;
- (BOOL)GetAISFlag;
- (Obj*)GetSoftMask;
- (Matrix2D*)GetSoftMaskTransform;
- (BOOL)GetStrokeOverprint;
- (BOOL)GetFillOverprint;
- (int)GetOverprintMode;
- (BOOL)GetAutoStrokeAdjust;
- (double)GetSmoothnessTolerance;
- (Obj*)GetTransferFunct;
- (Obj*)GetBlackGenFunct;
- (Obj*)GetUCRFunct;
- (Obj*)GetHalftone;
- (void)SetTransformWithMatrix: (Matrix2D*)mtx;
- (void)SetTransform: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
- (void)ConcatWithMatrix: (Matrix2D*)mtx;
- (void)Concat: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
- (void)SetStrokeColorSpace: (ColorSpace*)cs;
- (void)SetFillColorSpace: (ColorSpace*)cs;
- (void)SetStrokeColorWithColorPt: (ColorPt*)c;
- (void)SetStrokeColorWithPattern: (PatternColor*)pattern;
- (void)SetStrokeColorWithPatternAndColorPt: (PatternColor*)pattern c:  (ColorPt*)c;
- (void)SetFillColorWithColorPt: (ColorPt*)c;
- (void)SetFillColorWithPattern: (PatternColor*)pattern;
- (void)SetFillColorWithPatternAndColorPt: (PatternColor*)pattern c:  (ColorPt*)c;
- (void)SetFlatness: (double)flatness;
- (void)SetLineCap: (LineCap)cap;
- (void)SetLineJoin: (LineJoin)join;
- (void)SetLineWidth: (double)width;
- (void)SetMiterLimit: (double)miter_limit;
- (void)SetDashPattern: (NSMutableArray*)dash_array phase:  (double)phase;
- (void)SetCharSpacing: (double)char_spacing;
- (void)SetWordSpacing: (double)word_spacing;
- (void)SetHorizontalScale: (double)hscale;
- (void)SetLeading: (double)leading;
- (void)SetFont: (Font*)font font_sz:  (double)font_sz;
- (void)SetTextRenderMode: (TextRenderingMode)rmode;
- (void)SetTextRise: (double)rise;
- (void)SetTextKnockout: (BOOL)knockout;
- (void)SetRenderingIntent: (RenderingIntent)intent;
- (void)SetBlendMode: (BlendMode)BM;
- (void)SetFillOpacity: (double)ca;
- (void)SetStrokeOpacity: (double)CA;
- (void)SetAISFlag: (BOOL)AIS;
- (void)SetSoftMask: (Obj*)SM;
- (void)SetStrokeOverprint: (BOOL)OP;
- (void)SetFillOverprint: (BOOL)op;
- (void)SetOverprintMode: (int)OPM;
- (void)SetAutoStrokeAdjust: (BOOL)SA;
- (void)SetSmoothnessTolerance: (double)SM;
- (void)SetBlackGenFunct: (Obj*)BG;
- (void)SetUCRFunct: (Obj*)UCR;
- (void)SetTransferFunct: (Obj*)TR;
- (void)SetHalftone: (Obj*)HT;
- (id)init;
@end


@interface TRNField : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (BOOL)IsValid;
- (FieldType)GetType;
- (Obj*)GetValue;
- (NSString*)GetValueAsString;
- (BOOL)GetValueAsBool;
- (void)SetValueWithString: (NSString*)value;
- (void)SetValueWithObj: (Obj*)value;
- (void)SetValue: (NSString *)value;
- (void)SetValueWithBool: (BOOL)value;
- (void)RefreshAppearance;
- (void)EraseAppearance;
- (Obj*)GetDefaultValue;
- (NSString*)GetDefaultValueAsString;
- (NSString*)GetName;
- (NSString*)GetPartialName;
- (void)Rename: (NSString*)field_name;
- (BOOL)IsAnnot;
- (BOOL)GetFlag: (FieldFlag)flag;
- (void)SetFlag: (FieldFlag)flag value:  (BOOL)value;
- (TextJustification)GetJustification;
- (void)SetJustification: (TextJustification)j;
- (void)SetMaxLen: (int)max_len;
- (int)GetOptCount;
- (NSString*)GetOpt: (int)index;
- (int)GetMaxLen;
- (GState*)GetDefaultAppearance;
- (void)Flatten: (Page*)page;
- (PDFRect*)GetUpdateRect;
- (Obj*)FindInheritedAttribute: (NSString *)attrib;
- (Obj*)GetSDFObj;
- (void)Destroy;
- (Obj*)UseSignatureHandler: (SignatureHandlerId)signature_handler_id;
- (id)initWithField_dict: (Obj*)field_dict;
@end


@interface FieldIterator : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Destroy;
- (void)Next;
- (TRNField*)Current;
- (BOOL)HasNext;
- (id)init;
@end


@interface FileSpec : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (FileSpec*)Create: (SDFDoc*)doc path:  (NSString*)path embed:  (BOOL)embed;
+ (FileSpec*)CreateURL: (SDFDoc*)doc url:  (NSString *)url;
- (BOOL)IsValid;
- (BOOL)Export: (NSString*)save_as;
- (Filter*)GetFileData;
- (NSString*)GetFilePath;
- (void)SetDesc: (NSString*)desc;
- (Obj*)GetSDFObj;
- (id)initWithF: (Obj*)f;
@end


@interface Annot : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Annot*)Create: (SDFDoc*)doc type:  (AnnotType)type pos:  (PDFRect*)pos;
- (BOOL)IsValid;
- (Obj*)GetSDFObj;
- (AnnotType)GetType;
- (PDFRect*)GetRect;
- (BOOL)IsMarkup;
- (void)SetRect: (PDFRect*)p;
- (Page*)GetPage;
- (void)SetPage: (Page*)page;
- (Obj*)GetUniqueID;
- (void)SetUniqueID: (NSString *)id id_buf_sz:  (int)id_buf_sz;
- (Date*)GetDate;
- (void)SetDate: (Date*)date;
- (BOOL)GetFlag: (AnnotFlag)flag;
- (void)SetFlag: (AnnotFlag)flag value:  (BOOL)value;
- (BorderStyle*)GetBorderStyle;
- (void)SetBorderStyle: (BorderStyle*)bs oldStyleOnly:  (BOOL)oldStyleOnly;
- (Obj*)GetAppearance: (AnnotationState)annot_state app_state:  (NSString *)app_state;
- (void)SetAppearance: (Obj*)app_stream annot_state:  (AnnotationState)annot_state app_state:  (NSString *)app_state;
- (void)RemoveAppearance: (AnnotationState)annot_state app_state:  (NSString *)app_state;
- (void)Flatten: (Page*)page;
- (NSString *)GetActiveAppearanceState;
- (void)SetActiveAppearanceState: (NSString *)astate;
- (ColorPt*)GetColorAsRGB;
- (ColorPt*)GetColorAsCMYK;
- (ColorPt*)GetColorAsGray;
- (int)GetColorCompNum;
- (void)SetColor: (ColorPt*)c comp_num:  (int)comp_num;
- (int)GetStructParent;
- (void)SetStructParent: (int)keyval;
- (Obj*)GetOptionalContent;
- (void)SetOptionalContent: (Obj*)oc;
- (void)SetContents: (NSString*)contents;
- (NSString*)GetContents;
- (void)RefreshAppearance;
- (void)Resize: (PDFRect*)newrect;
- (id)initWithD: (Obj*)d;
@end


@interface Popup : Annot
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Popup*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (Annot*)GetParent;
- (void)SetParent: (Annot*)parent;
- (BOOL)IsOpen;
- (void)SetOpen: (BOOL)is_open;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface Markup : Annot
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (NSString*)GetTitle;
- (void)SetTitle: (NSString*)title;
- (Popup*)GetPopup;
- (void)SetPopup: (Popup*)bs;
- (double)GetOpacity;
- (void)SetOpacity: (double)op;
- (NSString*)GetSubject;
- (void)SetSubject: (NSString*)subj;
- (Date*)GetCreationDates;
- (void)SetCreationDates: (Date*)dt;
- (BorderEffect)GetBorderEffect;
- (void)SetBorderEffect: (BorderEffect)effect;
- (double)GetBorderEffectIntensity;
- (void)SetBorderEffectIntensity: (double)intensity;
- (ColorPt*)GetInteriorColor;
- (int)GetInteriorColorCompNum;
- (void)SetInteriorColor: (ColorPt*)c CompNum:  (int)CompNum;
- (PDFRect*)GetContentRect;
- (void)SetContentRect: (PDFRect*)cr;
- (PDFRect*)GetPadding;
- (void)SetPaddingWithRect: (PDFRect*)rd;
- (void)SetPadding: (double)x;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface FileAttachment : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (FileAttachment*)CreateFileAttchWithFileSpec: (SDFDoc*)doc pos:  (PDFRect*)pos fs:  (FileSpec*)fs icon_name:  (FileIcon)icon_name;
+ (FileAttachment*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos fs:  (FileSpec*)fs;
+ (FileAttachment*)CreateFileAttchWithPath: (SDFDoc*)doc pos:  (PDFRect*)pos path:  (NSString*)path icon_name:  (FileIcon)icon_name;
+ (FileAttachment*)CreateFileAttchWithIconName: (SDFDoc*)doc pos:  (PDFRect*)pos path:  (NSString*)path icon_name:  (NSString *)icon_name;
- (FileSpec*)GetFileSpec;
- (void)SetFileSpec: (FileSpec*)file;
- (BOOL)Export: (NSString*)save_as;
- (FileIcon)GetIcon;
- (void)SetIcon: (FileIcon)type;
- (NSString *)GetIconName;
- (void)SetIconName: (NSString *)icon;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface QuadPoint : TRN_quadpoint
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (id)init;- (id)initWithP11: (PDFPoint*)p11 p22:  (PDFPoint*)p22 p33:  (PDFPoint*)p33 p44:  (PDFPoint*)p44;- (id)initWithR: (PDFRect*)r;
@end


@interface TextMarkup : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (int)GetQuadPointCount;
- (QuadPoint*)GetQuadPoint: (int)idx;
- (void)SetQuadPoint: (int)idx qp:  (QuadPoint*)qp;
- (id)initWithD: (Obj*)d;- (id)initWithAnn: (Annot*)ann;
@end


@interface Ink : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Ink*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (int)GetPathCount;
- (int)GetPointCount: (unsigned int)pathindex;
- (PDFPoint*)GetPoint: (unsigned int)pathindex pointindex:  (unsigned int)pointindex;
- (void)SetPoint: (unsigned int)pathindex pointindex:  (unsigned int)pointindex pt:  (PDFPoint*)pt;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface Destination : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Destination*)CreateXYZ: (Page*)page left:  (double)left top:  (double)top zoom:  (double)zoom;
+ (Destination*)CreateFit: (Page*)page;
+ (Destination*)CreateFitH: (Page*)page top:  (double)top;
+ (Destination*)CreateFitV: (Page*)page left:  (double)left;
+ (Destination*)CreateFitR: (Page*)page left:  (double)left bottom:  (double)bottom right:  (double)right top:  (double)top;
+ (Destination*)CreateFitB: (Page*)page;
+ (Destination*)CreateFitBH: (Page*)page top:  (double)top;
+ (Destination*)CreateFitBV: (Page*)page left:  (double)left;
- (BOOL)IsValid;
- (FitType)GetFitType;
- (Page*)GetPage;
- (void)SetPage: (Page*)page;
- (Obj*)GetSDFObj;
- (Obj*)GetExplicitDestObj;
- (id)initWithDest: (Obj*)dest;
@end


@interface Action : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Action*)CreateGoto: (Destination*)dest;
+ (Action*)CreateGotoWithNamedDestination: (NSData*)key key_sz:  (int)key_sz dest:  (Destination*)dest;
+ (Action*)CreateGotoRemote: (FileSpec*)file page_num:  (int)page_num;
+ (Action*)CreateGotoRemoteWithNewWindow: (FileSpec*)file page_num:  (int)page_num new_window:  (BOOL)new_window;
+ (Action*)CreateURI: (SDFDoc*)doc uri:  (NSString *)uri;
+ (Action*)CreateSubmitForm: (FileSpec*)url;
+ (Action*)CreateLaunch: (SDFDoc*)doc path:  (NSString *)path;
+ (Action*)CreateHideField: (SDFDoc*)doc list_length:  (int)list_length field_list:  (NSMutableArray*)field_list;
+ (Action*)CreateImportData: (SDFDoc*)doc path:  (NSString *)path;
+ (Action*)CreateResetForm: (SDFDoc*)doc;
+ (Action*)CreateJavaScript: (SDFDoc*)doc script:  (NSString *)script;
- (BOOL)IsValid;
- (ActionType)GetType;
- (void)Execute;
- (Obj*)GetNext;
- (Destination*)GetDest;
- (BOOL)GetFormActionFlag: (FormActionFlag)flag;
- (void)SetFormActionFlag: (FormActionFlag)flag value:  (BOOL)value;
- (Obj*)GetSDFObj;
- (id)initWithIn_obj: (Obj*)in_obj;
@end


@interface FDFField : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (Obj*)GetValue;
- (void)SetValue: (Obj*)value;
- (NSString*)GetName;
- (NSString*)GetPartialName;
- (Obj*)GetSDFObj;
- (Obj*)FindAttribute: (NSString *)attrib;
- (id)initWithField_dict: (Obj*)field_dict fdf_dict:  (Obj*)fdf_dict;
@end


@interface FDFFieldIterator : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Destroy;
- (void)Next;
- (FDFField*)Current;
- (BOOL)HasNext;
- (id)init;
@end


@interface FDFDoc : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Close;
- (BOOL)IsModified;
- (void)SaveFDFDocToFile: (NSString*)path;
- (NSData*)SaveFDFDocToBuf;
- (Obj*)GetTrailer;
- (Obj*)GetRoot;
- (Obj*)GetFDF;
- (NSString*)GetPDFFileName;
- (void)SetPDFFileName: (NSString*)filepath;
- (Obj*)GetID;
- (void)SetID: (Obj*)id;
- (FDFFieldIterator*)GetFieldIterator;
- (FDFFieldIterator*)GetFieldIteratorWithFieldName: (NSString*)field_name;
- (FDFField*)GetField: (NSString*)field_name;
- (FDFField*)FieldCreateWithObj: (NSString*)field_name type:  (FieldType)type field_value:  (Obj*)field_value;
- (FDFField*)FieldCreate: (NSString*)field_name type:  (FieldType)type;
- (FDFField*)FieldCreateWithString: (NSString*)field_name type:  (FieldType)type field_value:  (NSString*)field_value;
- (SDFDoc*)GetSDFDoc;
+ (FDFDoc*)CreateFromXFDF: (NSString*)filepath;
- (void)SaveAsXFDF: (NSString*)filepath;
- (void)MergeAnnots: (NSString*)command_file permitted_user:  (NSString*)permitted_user;
- (id)init;- (id)initWithSdfdoc: (SDFDoc*)sdfdoc;- (id)initWithFilepath: (NSString*)filepath;- (id)initWithStream: (Filter*)stream;
@end


@interface Caret : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Caret*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
+ (Caret*)CreateWithPadding: (SDFDoc*)doc pos:  (PDFRect*)pos padding:  (PDFRect*)padding;
- (NSString *)GetSymbol;
- (void)SetSymbol: (NSString *)symbol;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface Circle : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Circle*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface HighlightAnnot : TextMarkup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (HighlightAnnot*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (id)initWithD: (Obj*)d;- (id)initWithAnn: (Annot*)ann;
@end


@interface LineAnnot : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (LineAnnot*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (PDFPoint*)GetStartPoint;
- (void)SetStartPoint: (PDFPoint*)sp;
- (PDFPoint*)GetEndPoint;
- (void)SetEndPoint: (PDFPoint*)ep;
- (EndingStyle)GetStartStyle;
- (void)SetStartStyle: (EndingStyle)sst;
- (EndingStyle)GetEndStyle;
- (void)SetEndStyle: (EndingStyle)est;
- (double)GetLeaderLineLength;
- (void)SetLeaderLineLength: (double)ll;
- (double)GetLeaderLineExtensionLength;
- (void)SetLeaderLineExtensionLength: (double)ll;
- (BOOL)GetShowCaption;
- (void)SetShowCaption: (BOOL)showCaption;
- (LineIntentType)GetIntentType;
- (void)SetIntentType: (LineIntentType)style;
- (double)GetLeaderLineOffset;
- (void)SetLeaderLineOffset: (double)ll;
- (CapPos)GetCaptionPosition;
- (void)SetCaptionPosition: (CapPos)style;
- (double)GetTextHOffset;
- (void)SetTextHOffset: (double)offset;
- (double)GetTextVOffset;
- (void)SetTextVOffset: (double)offset;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface FreeText : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (FreeText*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (NSString*)GetDefaultAppearance;
- (void)SetDefaultAppearance: (NSString *)app_str;
- (int)GetQuaddingFormat;
- (void)SetQuaddingFormat: (int)app_qform;
- (PDFPoint*)GetCalloutLinePoint1;
- (PDFPoint*)GetCalloutLinePoint2;
- (PDFPoint*)GetCalloutLinePoint3;
- (void)SetCalloutLinePointsWithKneePoint: (PDFPoint*)p1 p2:  (PDFPoint*)p2 p3:  (PDFPoint*)p3;
- (void)SetCalloutLinePoints: (PDFPoint*)p1 p2:  (PDFPoint*)p2;
- (IntentName)GetIntentName;
- (void)SetIntentName: (IntentName)mode;
- (EndingStyle)GetEndingStyle;
- (void)SetEndingStyle: (EndingStyle)est;
- (void)SetEndingStyleWithString: (NSString *)est;
- (void)SetTextColor: (ColorPt*)color col_comp:  (int)col_comp;
- (ColorPt*)GetTextColor;
- (int)GetTextColorCompNum;
- (void)SetLineColor: (ColorPt*)color col_comp:  (int)col_comp;
- (ColorPt*)GetLineColor;
- (int)GetLineColorCompNum;
- (void)SetFontSize: (double)font_size;
- (double)GetFontSize;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface Link : Annot
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Link*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
+ (Link*)CreateWithAction: (SDFDoc*)doc pos:  (PDFRect*)pos action:  (Action*)action;
- (void)RemoveAction;
- (Action*)GetAction;
- (void)SetAction: (Action*)action;
- (LinkHighlightingMode)GetHighlightingMode;
- (void)SetHighlightingMode: (LinkHighlightingMode)mode;
- (int)GetQuadPointCount;
- (QuadPoint*)GetQuadPoint: (int)idx;
- (void)SetQuadPoint: (int)idx qp:  (QuadPoint*)qp;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface Movie : Annot
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Movie*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (NSString*)GetTitle;
- (void)SetTitle: (NSString*)title;
- (BOOL)IsToBePlayed;
- (void)SetToBePlayed: (BOOL)isplay;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface PolyLine : LineAnnot
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (PolyLine*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (int)GetVertexCount;
- (PDFPoint*)GetVertex: (int)idx;
- (void)SetVertex: (int)idx pt:  (PDFPoint*)pt;
- (PolyLineIntentType)GetIntentName;
- (void)SetIntentName: (PolyLineIntentType)mode;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface PDFPolygon : PolyLine
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (PDFPolygon*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface RedactionAnnot : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (RedactionAnnot*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (int)GetQuadPointCount;
- (QuadPoint*)GetQuadPoint: (int)idx;
- (void)SetQuadPoint: (int)idx qp:  (QuadPoint*)qp;
- (Obj*)GetAppFormXO;
- (void)SetAppFormXO: (Obj*)formxo;
- (NSString*)GetOverlayText;
- (void)SetOverlayText: (NSString*)title;
- (BOOL)GetUseRepeat;
- (void)SetUseRepeat: (BOOL)repeat;
- (NSString*)GetOverlayTextAppearance;
- (void)SetOverlayTextAppearance: (NSString*)app;
- (QuadForm)GetQuadForm;
- (void)SetQuadForm: (QuadForm)form;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface RubberStamp : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (RubberStamp*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos icon:  (RubberStampIcon)icon;
- (RubberStampIcon)GetIcon;
- (void)SetRubberStampIconType: (RubberStampIcon)type;
- (void)SetIcon;
- (NSString *)GetIconName;
- (void)SetRubberStampIconName: (NSString *)icon;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface Screen : Annot
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Screen*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (NSString*)GetTitle;
- (void)SetTitle: (NSString*)title;
- (Action*)GetAction;
- (void)SetAction: (Action*)action;
- (Obj*)GetTriggerAction;
- (void)SetTriggerAction: (Obj*)action;
- (int)GetRotation;
- (void)SetRotation: (int)rot;
- (int)GetBorderColorCompNum;
- (ColorPt*)GetBorderColor;
- (void)SetBorderColor: (ColorPt*)c CompNum:  (int)CompNum;
- (int)GetBackgroundColorCompNum;
- (ColorPt*)GetBackgroundColor;
- (void)SetBackgroundColor: (ColorPt*)c CompNum:  (int)CompNum;
- (NSString*)GetStaticCaptionText;
- (void)SetStaticCaptionText: (NSString*)ct;
- (NSString*)GetRolloverCaptionText;
- (void)SetRolloverCaptionText: (NSString*)ct;
- (NSString*)GetMouseDownCaptionText;
- (void)SetMouseDownCaptionText: (NSString*)ct;
- (Obj*)GetStaticIcon;
- (void)SetStaticIcon: (Obj*)ic;
- (Obj*)GetRolloverIcon;
- (void)SetRolloverIcon: (Obj*)ic;
- (Obj*)GetMouseDownIcon;
- (void)SetMouseDownIcon: (Obj*)ic;
- (ScreenIconCaptionRelation)GetIconCaptionRelation;
- (void)SetIconCaptionRelation: (ScreenIconCaptionRelation)icr;
- (ScreenScaleCondition)GetScaleCondition;
- (void)SetScaleCondition: (ScreenScaleCondition)sd;
- (ScreenScaleType)GetScaleType;
- (void)SetScaleType: (ScreenScaleType)st;
- (double)GetHIconLeftOver;
- (void)SetHIconLeftOver: (double)hl;
- (double)GetVIconLeftOver;
- (void)SetVIconLeftOver: (double)vl;
- (BOOL)GetFitFull;
- (void)SetFitFull: (BOOL)ff;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface Sound : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Sound*)CreateSoundWithRect: (SDFDoc*)doc pos:  (PDFRect*)pos icon:  (SoundIcon)icon;
+ (Sound*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
+ (Sound*)CreateSoundWithPoint: (SDFDoc*)doc pos:  (PDFPoint*)pos icon:  (SoundIcon)icon;
- (Obj*)GetSoundStream;
- (void)SetSoundStream: (Obj*)sound_stream;
- (SoundIcon)GetIcon;
- (void)SetSoundIconType: (SoundIcon)type;
- (void)SetIcon;
- (NSString *)GetIconName;
- (void)SetSoundIconName: (NSString *)type;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface Square : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Square*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface Squiggly : TextMarkup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Squiggly*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (id)initWithD: (Obj*)d;- (id)initWithAnn: (Annot*)ann;
@end


@interface StrikeOut : TextMarkup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (StrikeOut*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (id)initWithD: (Obj*)d;- (id)initWithAnn: (Annot*)ann;
@end


@interface Text : Markup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Text*)CreateTextWithRect: (SDFDoc*)doc pos:  (PDFRect*)pos contents:  (NSString*)contents;
+ (Text*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
+ (Text*)CreateTextWithPoint: (SDFDoc*)doc pos:  (PDFPoint*)pos contents:  (NSString*)contents;
- (BOOL)IsOpen;
- (void)SetOpen: (BOOL)isopen;
- (TextIcon)GetIcon;
- (NSString *)GetIconName;
- (void)SetTextIconType: (TextIcon)icon;
- (void)SetIcon;
- (void)SetTextIconName: (NSString *)icon;
- (NSString*)GetState;
- (void)SetState: (NSString*)state;
- (NSString*)GetStateModel;
- (void)SetStateModel: (NSString*)sm;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithMku: (Annot*)mku;
@end


@interface Underline : TextMarkup
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Underline*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (id)initWithD: (Obj*)d;- (id)initWithAnn: (Annot*)ann;
@end


@interface Watermark : Annot
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Watermark*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface Widget : Annot
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Widget*)Create: (SDFDoc*)doc pos:  (PDFRect*)pos field:  (TRNField*)field;
- (TRNField*)GetField;
- (WidgetHighlightingMode)GetHighlightingMode;
- (void)SetHighlightingMode: (WidgetHighlightingMode)mode;
- (Action*)GetAction;
- (void)SetAction: (Action*)action;
- (Obj*)GetTriggerAction;
- (void)SetTriggerAction: (Obj*)action;
- (int)GetRotation;
- (void)SetRotation: (int)rot;
- (int)GetBorderColorCompNum;
- (ColorPt*)GetBorderColor;
- (void)SetBorderColor: (ColorPt*)c CompNum:  (int)CompNum;
- (int)GetBackgroundColorCompNum;
- (ColorPt*)GetBackgroundColor;
- (void)SetBackgroundColor: (ColorPt*)c CompNum:  (int)CompNum;
- (NSString*)GetStaticCaptionText;
- (void)SetStaticCaptionText: (NSString*)ct;
- (NSString*)GetRolloverCaptionText;
- (void)SetRolloverCaptionText: (NSString*)ct;
- (NSString*)GetMouseDownCaptionText;
- (void)SetMouseDownCaptionText: (NSString*)ct;
- (Obj*)GetStaticIcon;
- (void)SetStaticIcon: (Obj*)ic;
- (Obj*)GetRolloverIcon;
- (void)SetRolloverIcon: (Obj*)ic;
- (Obj*)GetMouseDownIcon;
- (void)SetMouseDownIcon: (Obj*)ic;
- (WidgetIconCaptionRelation)GetIconCaptionRelation;
- (void)SetIconCaptionRelation: (WidgetIconCaptionRelation)icr;
- (WidgetScaleCondition)GetScaleCondition;
- (void)SetScaleCondition: (WidgetScaleCondition)sd;
- (WidgetScaleType)GetScaleType;
- (void)SetScaleType: (WidgetScaleType)st;
- (double)GetHIconLeftOver;
- (void)SetHIconLeftOver: (double)hl;
- (double)GetVIconLeftOver;
- (void)SetVIconLeftOver: (double)vl;
- (BOOL)GetFitFull;
- (void)SetFitFull: (BOOL)ff;
- (id)initWithD: (Obj*)d;- (id)init;- (id)initWithAnn: (Annot*)ann;
@end


@interface Config : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Config*)Create: (PDFDoc*)doc default_config:  (BOOL)default_config;
- (BOOL)IsValid;
- (Obj*)GetOrder;
- (void)SetOrder: (Obj*)ocgs_array;
- (NSString*)GetName;
- (void)SetName: (NSString*)name;
- (NSString*)GetCreator;
- (void)SetCreator: (NSString*)name;
- (NSString *)GetInitBaseState;
- (Obj*)GetInitOnStates;
- (Obj*)GetInitOffStates;
- (void)SetInitBaseState: (NSString *)state;
- (void)SetInitOnStates: (Obj*)on_array;
- (void)SetInitOffStates: (Obj*)off_array;
- (Obj*)GetIntent;
- (void)SetIntent: (Obj*)intent;
- (Obj*)GetLockedOCGs;
- (void)SetLockedOCGs: (Obj*)locked_ocg_array;
- (Obj*)GetSDFObj;
- (id)initWithOcg_config: (Obj*)ocg_config;
@end


@interface Group : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Group*)Create: (PDFDoc*)doc name:  (NSString*)name;
- (BOOL)IsValid;
- (NSString*)GetName;
- (void)SetName: (NSString*)name;
- (BOOL)GetCurrentState: (Context*)context;
- (void)SetCurrentState: (Context*)context state:  (BOOL)state;
- (BOOL)GetInitialState: (Config*)config;
- (void)SetInitialState: (Config*)config state:  (BOOL)state;
- (Obj*)GetIntent;
- (void)SetIntent: (Obj*)intent;
- (BOOL)IsLocked: (Config*)config;
- (void)SetLocked: (Config*)config locked:  (BOOL)locked;
- (BOOL)HasUsage;
- (Obj*)GetUsage: (NSString *)key;
- (Obj*)GetSDFObj;
- (id)initWithOcg: (Obj*)ocg;
@end


@interface Context : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (BOOL)IsValid;
- (BOOL)GetState: (Group*)group;
- (void)SetState: (Group*)group state:  (BOOL)state;
- (void)ResetStates: (BOOL)all_on;
- (void)SetNonOCDrawing: (BOOL)draw_non_OC;
- (BOOL)GetNonOCDrawing;
- (void)SetOCDrawMode: (OCDrawMode)oc_draw_mode;
- (OCDrawMode)GetOCMode;
- (void)Destroy;
- (id)initWithConfig: (Config*)config;
@end


@interface OCMD : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (OCMD*)Create: (PDFDoc*)doc ocgs:  (Obj*)ocgs vis_policy:  (VisibilityPolicyType)vis_policy;
- (BOOL)IsValid;
- (Obj*)GetOCGs;
- (VisibilityPolicyType)GetVisibilityPolicy;
- (void)SetVisibilityPolicy: (VisibilityPolicyType)vis_policy;
- (Obj*)GetVisibilityExpression;
- (BOOL)IsCurrentlyVisible: (Context*)context;
- (Obj*)GetSDFObj;
- (id)initWithOcmd: (Obj*)ocmd;
@end


@interface PDFACompliance : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SaveAsFile: (NSString*)file_path linearized:  (BOOL)linearized;
- (void)SaveAs: (NSString*)file_path;
- (NSData*)SaveAsMemBuf: (BOOL)linearized;
- (unsigned long)GetErrorCount;
- (ErrorCode)GetError: (unsigned long)idx;
- (unsigned long)GetRefObjCount: (ErrorCode)id;
- (unsigned long)GetRefObj: (ErrorCode)id obj_idx:  (unsigned long)obj_idx;
+ (NSString *)GetPDFAErrorMessage: (ErrorCode)id;
- (void)Destroy;
- (id)initWithConvert: (BOOL)convert file_path:  (NSString*)file_path password:  (NSString *)password conf:  (Conformance)conf exceptions:  (int)exceptions num_exceptions:  (int)num_exceptions max_ref_objs:  (int)max_ref_objs first_stop:  (BOOL)first_stop;- (id)initWithConvert: (BOOL)convert file_path:  (NSString*)file_path password:  (NSString *)password conf:  (Conformance)conf exceptions:  (int)exceptions num_exceptions:  (int)num_exceptions max_ref_objs:  (int)max_ref_objs;- (id)initWithConvert: (BOOL)convert buf:  (NSString *)buf buf_size:  (unsigned long)buf_size password:  (NSString *)password conf:  (Conformance)conf exceptions:  (int)exceptions num_exceptions:  (int)num_exceptions max_ref_objs:  (int)max_ref_objs first_stop:  (BOOL)first_stop;
@end


@interface AttrObj : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (NSString *)GetOwner;
- (Obj*)GetSDFObj;
- (id)initWithDict: (Obj*)dict;
@end


@interface ClassMap : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (BOOL)IsValid;
- (Obj*)GetSDFObj;
- (id)initWithDict: (Obj*)dict;
@end


@interface ContentItem : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (ContentItemType)GetType;
- (SElement*)GetParent;
- (Page*)GetPage;
- (Obj*)GetSDFObj;
- (int)GetMCID;
- (Obj*)GetContainingStm;
- (Obj*)GetStmOwner;
- (Obj*)GetRefObj;
- (id)initWithArg0: (ContentItem*)arg0;
@end


@interface RoleMap : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (BOOL)IsValid;
- (NSString *)GetDirectMap: (NSString *)type;
- (Obj*)GetSDFObj;
- (id)initWithDict: (Obj*)dict;
@end


@interface STree : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (STree*)Create: (PDFDoc*)doc;
- (void)Insert: (SElement*)kid insert_before:  (int)insert_before;
- (BOOL)IsValid;
- (int)GetNumKids;
- (SElement*)GetKid: (int)index;
- (SElement*)GetElement: (NSString *)id_buf id_buf_sz:  (int)id_buf_sz;
- (RoleMap*)GetRoleMap;
- (ClassMap*)GetClassMap;
- (Obj*)GetSDFObj;
- (id)initWithStruct_dict: (Obj*)struct_dict;
@end


@interface SElement : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (SElement*)Create: (PDFDoc*)doc struct_type:  (NSString *)struct_type;
- (void)Insert: (SElement*)kid insert_before:  (int)insert_before;
- (int)CreateContentItem: (PDFDoc*)doc page:  (Page*)page insert_before:  (int)insert_before;
- (BOOL)IsValid;
- (NSString *)GetType;
- (int)GetNumKids;
- (BOOL)IsContentItem: (int)index;
- (ContentItem*)GetAsContentItem: (int)index;
- (SElement*)GetAsStructElem: (int)index;
- (SElement*)GetParent;
- (STree*)GetStructTreeRoot;
- (BOOL)HasTitle;
- (NSString*)GetTitle;
- (Obj*)GetID;
- (BOOL)HasActualText;
- (NSString*)GetActualText;
- (BOOL)HasAlt;
- (NSString*)GetAlt;
- (Obj*)GetSDFObj;
- (id)initWithDict: (Obj*)dict;
@end


@interface Bookmark : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Bookmark*)Create: (PDFDoc*)in_doc in_title:  (NSString*)in_title;
- (BOOL)IsValid;
- (BOOL)HasChildren;
- (Bookmark*)GetNext;
- (Bookmark*)GetPrev;
- (Bookmark*)GetFirstChild;
- (Bookmark*)GetLastChild;
- (Bookmark*)GetParent;
- (Bookmark*)Find: (NSString*)in_title;
- (Bookmark*)AddChildWithTitle: (NSString*)in_title;
- (Bookmark*)AddChildWithBookmark: (Bookmark*)in_bookmark;
- (Bookmark*)AddNextWithTitle: (NSString*)in_title;
- (void)AddNextWithBookmark: (Bookmark*)in_bookmark;
- (Bookmark*)AddPrevWithTitle: (NSString*)in_title;
- (void)AddPrevWithBookmark: (Bookmark*)in_bookmark;
- (void)Delete;
- (void)Unlink;
- (int)GetIndent;
- (BOOL)IsOpen;
- (void)SetOpen: (BOOL)in_open;
- (int)GetOpenCount;
- (NSString*)GetTitle;
- (Obj*)GetTitleObj;
- (void)SetTitle: (NSString*)title;
- (Action*)GetAction;
- (void)SetAction: (Action*)in_action;
- (void)RemoveAction;
- (int)GetFlags;
- (void)SetFlags: (int)in_flags;
- (NSMutableArray*)GetColor;
- (void)SetColor: (double)in_r in_g:  (double)in_g in_b:  (double)in_b;
- (Obj*)GetSDFObj;
- (id)init;- (id)initWithIn_bookmark_dict: (Obj*)in_bookmark_dict;
@end


@interface ContentReplacer : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)AddImage: (PDFRect*)target_region replacement_image:  (Obj*)replacement_image;
- (void)AddText: (PDFRect*)target_region replacement_text:  (NSString*)replacement_text;
- (void)AddString: (NSString*)template_text replacement_text:  (NSString*)replacement_text;
- (void)Process: (Page*)page;
- (void)Destroy;
- (id)init;
@end


@interface Convert : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (void)FromXpsWithFilename: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
+ (void)FromXpsWithBuffer: (PDFDoc*)in_pdfdoc buf:  (NSString *)buf buf_sz:  (unsigned long)buf_sz;
+ (void)FromEmf: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
+ (void)ToEmfWithPDFDoc: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
+ (void)ToEmfWithPage: (Page*)in_page in_filename:  (NSString*)in_filename;
+ (void)ToSvgWithPDFDoc: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename in_options:  (SVGOutputOptions*)in_options;
+ (void)ToSvg: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
+ (void)ToSvgWithPage: (Page*)in_page in_filename:  (NSString*)in_filename in_options:  (SVGOutputOptions*)in_options;
+ (void)ToXpsWithPDFDoc: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename options:  (XPSOutputOptions*)options;
+ (void)ToXps: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
+ (void)ToXpsWithFilename: (NSString*)in_inputFilename in_outputFilename:  (NSString*)in_outputFilename options:  (XPSOutputOptions*)options;
+ (void)ToXodWithFilename: (NSString*)in_filename out_filename:  (NSString*)out_filename options:  (XODOutputOptions*)options;
+ (void)ToXod: (NSString*)in_filename out_filename:  (NSString*)out_filename;
+ (void)ToXodWithPDFDoc: (PDFDoc*)in_pdfdoc out_filename:  (NSString*)out_filename options:  (XODOutputOptions*)options;
+ (void)ToHtmlWithFilename: (NSString*)in_filename out_path:  (NSString*)out_path options:  (HTMLOutputOptions*)options;
+ (void)ToHtml: (NSString*)in_filename out_path:  (NSString*)out_path;
+ (void)ToHtmlWithPDFDoc: (PDFDoc*)in_pdfdoc out_path:  (NSString*)out_path options:  (HTMLOutputOptions*)options;
+ (void)ToEpubWithFilename: (NSString*)in_filename out_path:  (NSString*)out_path html_options:  (HTMLOutputOptions*)html_options epub_options:  (EPUBOutputOptions*)epub_options;
+ (void)ToEpub: (NSString*)in_filename out_path:  (NSString*)out_path html_options:  (HTMLOutputOptions*)html_options;
+ (void)ToEpubWithPDFDoc: (PDFDoc*)in_pdfdoc out_path:  (NSString*)out_path html_options:  (HTMLOutputOptions*)html_options epub_options:  (EPUBOutputOptions*)epub_options;
+ (Filter*)ToXodWithFilenameToStream: (NSString*)in_filename options:  (XODOutputOptions*)options;
+ (Filter*)ToXodWithPDFDocToStream: (PDFDoc*)in_pdfdoc options:  (XODOutputOptions*)options;
+ (void)ToPdf: (PDFDoc*)in_pdfdoc in_filename:  (NSString*)in_filename;
+ (BOOL)RequiresPrinter: (NSString*)in_filename;

@end


@interface PathData : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetOperators: (NSData*)operators;
- (void)SetPoints: (NSMutableArray*)points;
- (NSData*)GetOperators;
- (NSMutableArray*)GetPoints;
- (BOOL)IsDefined;
- (id)init;
@end


@interface Font : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Font*)Create: (SDFDoc*)doc type:  (StandardType1Font)type embed:  (BOOL)embed;
+ (Font*)CreateTrueTypeFont: (SDFDoc*)doc font_path:  (NSString*)font_path embed:  (BOOL)embed subset:  (BOOL)subset;
+ (Font*)CreateCIDTrueTypeFont: (SDFDoc*)doc font_path:  (NSString*)font_path embed:  (BOOL)embed subset:  (BOOL)subset encoding:  (Encoding)encoding;
+ (Font*)CreateFromFont: (SDFDoc*)doc from:  (Font*)from char_set:  (NSString*)char_set;
+ (Font*)CreateFromName: (SDFDoc*)doc name:  (NSString *)name char_set:  (NSString*)char_set;
+ (Font*)CreateType1Font: (SDFDoc*)doc font_path:  (NSString*)font_path embed:  (BOOL)embed;
- (FontType)GetType;
- (BOOL)IsSimple;
- (Obj*)GetSDFObj;
- (Obj*)GetDescriptor;
- (NSString *)GetName;
- (NSString *)GetFamilyName;
- (BOOL)IsFixedWidth;
- (BOOL)IsSerif;
- (BOOL)IsSymbolic;
- (BOOL)IsItalic;
- (BOOL)IsAllCap;
- (BOOL)IsForceBold;
- (BOOL)IsHorizontalMode;
- (double)GetWidth: (unsigned int)char_code;
- (double)GetMaxWidth;
- (double)GetMissingWidth;
- (UInt32Iterator*)GetCharCodeIterator;
- (PathData*)GetGlyphPath: (unsigned int)char_code conics2cubics:  (BOOL)conics2cubics transform:  (Matrix2D*)transform;
- (NSString*)MapToUnicode: (unsigned int)char_code;
- (BOOL)IsEmbedded;
- (NSString *)GetEmbeddedFontName;
- (Obj*)GetEmbeddedFont;
- (int)GetEmbeddedFontBufSize;
- (unsigned short)GetUnitsPerEm;
- (PDFRect*)GetBBox;
- (double)GetAscent;
- (double)GetDescent;
- (int)GetStandardType1FontType;
- (BOOL)IsCFF;
- (Matrix2D*)GetType3FontMatrix;
- (Obj*)GetType3GlyphStream: (unsigned int)char_code;
- (NSMutableArray*)GetVerticalAdvance: (unsigned int)char_code;
- (Font*)GetDescendant;
- (unsigned int)MapToCID: (unsigned int)char_code;
- (void)Destroy;
- (id)initWithFont_dict: (Obj*)font_dict;
@end


@interface Shading : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (ShadingType)GetType;
- (Obj*)GetSDFObj;
- (ColorSpace*)GetBaseColorSpace;
- (BOOL)HasBBox;
- (PDFRect*)GetBBox;
- (BOOL)HasBackground;
- (ColorPt*)GetBackground;
- (BOOL)GetAntialias;
- (double)GetParamStart;
- (double)GetParamEnd;
- (BOOL)IsExtendStart;
- (BOOL)IsExtendEnd;
- (ColorPt*)GetColorForAxialOrRadial: (double)t;
- (NSMutableArray*)GetCoordsAxial;
- (NSMutableArray*)GetCoordsRadial;
- (NSMutableArray*)GetDomain;
- (Matrix2D*)GetMatrix;
- (ColorPt*)GetColorForFunction: (double)t1 t2:  (double)t2;
- (void)Destroy;
- (id)initWithShading_dict: (Obj*)shading_dict;
@end


@interface PatternColor : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (PatternColorType)GetType;
- (Obj*)GetSDFObj;
- (Matrix2D*)GetMatrix;
- (Shading*)GetShading;
- (TilingType)GetTilingType;
- (PDFRect*)GetBBox;
- (double)GetXStep;
- (double)GetYStep;
- (void)Destroy;
- (id)initWithPattern: (Obj*)pattern;
@end


@interface Image : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (Image*)CreateWithFile: (SDFDoc*)doc filename:  (NSString*)filename encoder_hints:  (Obj*)encoder_hints;
+ (Image*)Create: (SDFDoc*)doc filename:  (NSString*)filename;
+ (Image*)CreateWithData: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height bpc:  (int)bpc color_space:  (ColorSpace*)color_space encoder_hints:  (Obj*)encoder_hints;
+ (Image*)CreateWithFilterData: (SDFDoc*)doc image_data:  (FilterReader*)image_data width:  (int)width height:  (int)height bpc:  (int)bpc color_space:  (ColorSpace*)color_space encoder_hints:  (Obj*)encoder_hints;
+ (Image*)CreateImageMaskWithBuffer: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height encoder_hints:  (Obj*)encoder_hints;
+ (Image*)CreateImageMask: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height;
+ (Image*)CreateImageMaskWithStream: (SDFDoc*)doc image_data:  (FilterReader*)image_data width:  (int)width height:  (int)height encoder_hints:  (Obj*)encoder_hints;
+ (Image*)CreateSoftMaskWithBuffer: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height bpc:  (int)bpc encoder_hints:  (Obj*)encoder_hints;
+ (Image*)CreateSoftMask: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height bpc:  (int)bpc;
+ (Image*)CreateSoftMaskWithStream: (SDFDoc*)doc image_data:  (FilterReader*)image_data width:  (int)width height:  (int)height bpc:  (int)bpc encoder_hints:  (Obj*)encoder_hints;
+ (Image*)CreateWithBufferAndFormat: (SDFDoc*)doc image_data:  (NSString *)image_data image_data_size:  (unsigned long)image_data_size width:  (int)width height:  (int)height bpc:  (int)bpc color_space:  (ColorSpace*)color_space input_format:  (InputFilter)input_format;
+ (Image*)CreateWithStreamAndFormat: (SDFDoc*)doc image_data:  (FilterReader*)image_data width:  (int)width height:  (int)height bpc:  (int)bpc color_space:  (ColorSpace*)color_space input_format:  (InputFilter)input_format;
- (Obj*)GetSDFObj;
- (BOOL)IsValid;
- (Filter*)GetImageData;
- (int)GetImageDataSize;
- (ColorSpace*)GetImageColorSpace;
- (int)GetImageWidth;
- (int)GetImageHeight;
- (Obj*)GetDecodeArray;
- (int)GetBitsPerComponent;
- (int)GetComponentNum;
- (BOOL)IsImageMask;
- (BOOL)IsImageInterpolate;
- (Obj*)GetMask;
- (void)SetMaskWithImage: (Image*)image_mask;
- (void)SetMaskWithColor: (Obj*)mask;
- (Obj*)GetSoftMask;
- (void)SetSoftMask: (Image*)soft_mask;
- (RenderingIntent)GetImageRenderingIntent;
- (int)ExportToFile: (NSString*)filename;
- (int)ExportToStream: (FilterWriter*)writer;
- (void)ExportAsTiffFile: (NSString*)filename;
- (void)ExportAsTiffStream: (FilterWriter*)writer;
- (void)ExportAsPngFile: (NSString*)filename;
- (void)ExportAsPngStream: (FilterWriter*)writer;
- (id)initWithImage_xobject: (Obj*)image_xobject;
@end


@interface Element : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (ElementType)GetType;
- (GState*)GetGState;
- (Matrix2D*)GetCTM;
- (PDFRect*)GetBBox;
- (SElement*)GetParentStructElement;
- (int)GetStructMCID;
- (BOOL)IsOCVisible;
- (BOOL)IsClippingPath;
- (BOOL)IsStroked;
- (BOOL)IsFilled;
- (BOOL)IsWindingFill;
- (BOOL)IsClipWindingFill;
- (PathData*)GetPathData;
- (void)SetPathData: (PathData*)data;
- (void)SetPathClip: (BOOL)clip;
- (void)SetPathStroke: (BOOL)stroke;
- (void)SetPathFill: (BOOL)fill;
- (void)SetWindingFill: (BOOL)winding_rule;
- (void)SetClipWindingFill: (BOOL)winding_rule;
- (Obj*)GetXObject;
- (Filter*)GetImageData;
- (int)GetImageDataSize;
- (ColorSpace*)GetImageColorSpace;
- (int)GetImageWidth;
- (int)GetImageHeight;
- (Obj*)GetDecodeArray;
- (int)GetBitsPerComponent;
- (int)GetComponentNum;
- (BOOL)IsImageMask;
- (BOOL)IsImageInterpolate;
- (Obj*)GetMask;
- (RenderingIntent)GetImageRenderingIntent;
- (NSString*)GetTextString;
- (NSData*)GetTextData;
- (unsigned int)GetTextDataSize;
- (Matrix2D*)GetTextMatrix;
- (CharIterator*)GetCharIterator;
- (double)GetTextLength;
- (double)GetPosAdjustment;
- (PDFPoint*)GetNewTextLineOffset;
- (void)SetNewTextLineOffset: (double)dx dy:  (double)dy;
- (BOOL)HasTextMatrix;
- (void)SetTextData: (NSData*)text_data text_data_size:  (int)text_data_size;
- (void)SetTextMatrixWithMatrix2D: (Matrix2D*)mtx;
- (void)SetTextMatrix: (double)a b:  (double)b c:  (double)c d:  (double)d h:  (double)h v:  (double)v;
- (void)SetPosAdjustment: (double)adjust;
- (void)UpdateTextMetrics;
- (Shading*)GetShading;
- (Obj*)GetMCPropertyDict;
- (Obj*)GetMCTag;
- (id)init;
@end


@interface ElementBuilder : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Reset: (GState*)gs;
- (Element*)CreateImage: (Image*)img;
- (Element*)CreateImageWithMatrix: (Image*)img mtx:  (Matrix2D*)mtx;
- (Element*)CreateImageWithCornerAndScale: (Image*)img x:  (double)x y:  (double)y hscale:  (double)hscale vscale:  (double)vscale;
- (Element*)CreateGroupBegin;
- (Element*)CreateGroupEnd;
- (Element*)CreateShading: (Shading*)sh;
- (Element*)CreateFormWithObj: (Obj*)form;
- (Element*)CreateFormWithPage: (Page*)page;
- (Element*)CreateFormWithPageAndDestination: (Page*)page doc:  (PDFDoc*)doc;
- (Element*)CreateTextBeginWithFont: (Font*)font font_sz:  (double)font_sz;
- (Element*)CreateTextBegin;
- (Element*)CreateTextEnd;
- (Element*)CreateTextRunWithFont: (NSString *)text_data font:  (Font*)font font_sz:  (double)font_sz;
- (Element*)CreateTextRun: (NSString *)text_data;
- (Element*)CreateUnicodeTextRun: (unsigned short*)text_data text_data_sz:  (unsigned int)text_data_sz;
- (Element*)CreateTextNewLineWithOffset: (double)dx dy:  (double)dy;
- (Element*)CreateTextNewLine;
- (Element*)CreatePath: (NSMutableArray*)points seg_types:  (NSData*)seg_types;
- (Element*)CreateRect: (double)x y:  (double)y width:  (double)width height:  (double)height;
- (Element*)CreateEllipse: (double)cx cy:  (double)cy rx:  (double)rx ry:  (double)ry;
- (void)PathBegin;
- (Element*)PathEnd;
- (void)MoveTo: (double)x y:  (double)y;
- (void)LineTo: (double)x y:  (double)y;
- (void)CurveTo: (double)cx1 cy1:  (double)cy1 cx2:  (double)cx2 cy2:  (double)cy2 x2:  (double)x2 y2:  (double)y2;
- (void)ArcToWithParam: (double)x y:  (double)y width:  (double)width height:  (double)height start:  (double)start extent:  (double)extent;
- (void)ArcToEndPt: (double)xr yr:  (double)yr rx:  (double)rx isLargeArc:  (BOOL)isLargeArc sweep:  (BOOL)sweep endX:  (double)endX endY:  (double)endY;
- (void)Ellipse: (double)cx cy:  (double)cy rx:  (double)rx ry:  (double)ry;
- (void)Rect: (double)x y:  (double)y width:  (double)width height:  (double)height;
- (void)ClosePath;
- (void)Destroy;
- (id)init;
@end


@interface ElementReader : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)ReaderBeginWithPage: (Page*)page ocg_context:  (Context*)ocg_context;
- (void)Begin: (Page*)page;
- (void)ReaderBeginWithSDFObj: (Obj*)content_stream resource_dict:  (Obj*)resource_dict ocg_context:  (Context*)ocg_context;
- (Element*)Next;
- (Element*)Current;
- (void)FormBegin;
- (void)PatternBegin: (BOOL)fill_pattern reset_ctm_tfm:  (BOOL)reset_ctm_tfm;
- (void)Type3FontBegin: (TRN_chardata*)char_data resource_dict:  (Obj*)resource_dict;
- (BOOL)End;
- (GSChangesIterator*)GetChangesIterator;
- (BOOL)IsChanged: (GStateAttribute)attrib;
- (void)ClearChangeList;
- (void)AppendResource: (Obj*)res;
- (Obj*)GetFont: (NSString *)name;
- (Obj*)GetXObject: (NSString *)name;
- (Obj*)GetShading: (NSString *)name;
- (Obj*)GetColorSpace: (NSString *)name;
- (Obj*)GetPattern: (NSString *)name;
- (Obj*)GetExtGState: (NSString *)name;
- (void)Destroy;
- (id)init;
@end


@interface ElementWriter : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)WriterBeginWithPage: (Page*)page placement:  (WriteMode)placement page_coord_sys:  (BOOL)page_coord_sys compress:  (BOOL)compress;
- (void)Begin: (Page*)page placement:  (WriteMode)placement page_coord_sys:  (BOOL)page_coord_sys;
- (void)WriterBeginWithSDFDoc: (SDFDoc*)doc compress:  (BOOL)compress;
- (void)WriterBeginWithSDFObj: (Obj*)stream_obj_to_update compress:  (BOOL)compress;
- (Obj*)End;
- (void)WriteElement: (Element*)element;
- (void)WritePlacedElement: (Element*)element;
- (void)Flush;
- (void)WriteBuffer: (NSData*)data;
- (void)WriteString: (NSString *)str;
- (void)Destroy;
- (id)init;
@end


@interface Flattener : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetDPI: (unsigned int)dpi;
- (void)SetMaximumImagePixels: (unsigned int)max_pixels;
- (void)SetPreferJPG: (BOOL)jpg;
- (void)SetThreshold: (Threshold)threshold;
- (void)Process: (PDFDoc*)doc mode:  (FlattenMode)mode;
- (void)Destroy;
- (id)init;
@end


@interface LinkInfo : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)setRect: (PDFRect*)value;
- (PDFRect*)getRect;
- (void)setUrl: (SWIGTYPE_p_pdftron__UString*)value;
- (SWIGTYPE_p_pdftron__UString*)getUrl;
- (id)init;
@end


@interface Image2RGB : Filter
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (id)initWithImage_element: (Element*)image_element;- (id)initWithImage_xobject: (Obj*)image_xobject;- (id)initWithImage: (Image*)image;
@end


@interface Image2RGBA : Filter
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (id)initWithImage_element: (Element*)image_element premultiply:  (BOOL)premultiply;- (id)initWithImage_element: (Element*)image_element;- (id)initWithImage_xobject: (Obj*)image_xobject premultiply:  (BOOL)premultiply;- (id)initWithImage: (Image*)image premultiply:  (BOOL)premultiply;
@end


@interface Highlights : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Load: (NSString*)file_name;
- (void)Save: (NSString*)file_name;
- (void)Add: (Highlights*)hlts;
- (void)Clear;
- (void)Begin: (PDFDoc*)doc;
- (BOOL)HasNext;
- (void)Next;
- (int)GetCurrentPageNumber;
- (VectorQuadPoint*)GetCurrentQuads;
- (void)Destroy;
- (id)init;
@end


@interface Selection : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (int)GetPageNum;
- (VectorQuadPoint*)GetQuads;
- (NSString*)GetAsUnicode;
- (NSString *)GetAsHtml;
- (id)init;
@end


@interface Optimizer : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (void)Optimize: (PDFDoc*)doc settings:  (OptimizerSettings*)settings;

@end


@interface PageLabel : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (PageLabel*)Create: (SDFDoc*)doc style:  (PageLabelStyle)style prefix:  (NSString*)prefix start_at:  (int)start_at;
- (BOOL)IsValid;
- (NSString*)GetLabelTitle: (int)page_num;
- (void)SetStyle: (PageLabelStyle)style;
- (PageLabelStyle)GetStyle;
- (NSString*)GetPrefix;
- (void)SetPrefix: (NSString*)prefix;
- (int)GetStart;
- (void)SetStart: (int)start_at;
- (int)GetFirstPageNum;
- (int)GetLastPageNum;
- (Obj*)GetSDFObj;
- (id)initWithL: (Obj*)l first_page:  (int)first_page last_page:  (int)last_page;
@end


@interface PageSet : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)AddPage: (int)one_page;
- (void)AddRange: (int)range_start range_end:  (int)range_end filter:  (PageSetFilter)filter;
- (void)Destroy;
- (id)init;- (id)initWithOne_page: (int)one_page;- (id)initWithRange_start: (int)range_start range_end:  (int)range_end filter:  (PageSetFilter)filter;
@end


@interface PDFDocInfo : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (NSString*)GetTitle;
- (Obj*)GetTitleObj;
- (void)SetTitle: (NSString*)title;
- (NSString*)GetAuthor;
- (Obj*)GetAuthorObj;
- (void)SetAuthor: (NSString*)author;
- (NSString*)GetSubject;
- (Obj*)GetSubjectObj;
- (void)SetSubject: (NSString*)subject;
- (NSString*)GetKeywords;
- (Obj*)GetKeywordsObj;
- (void)SetKeywords: (NSString*)keywords;
- (NSString*)GetCreator;
- (Obj*)GetCreatorObj;
- (void)SetCreator: (NSString*)creator;
- (NSString*)GetProducer;
- (Obj*)GetProducerObj;
- (void)SetProducer: (NSString*)producer;
- (Date*)GetCreationDate;
- (void)SetCreationDate: (Date*)creation_date;
- (Date*)GetModDate;
- (void)SetModDate: (Date*)mod_date;
- (Obj*)GetSDFObj;
- (id)initWithTr: (Obj*)tr;
@end


@interface PDFDocViewPrefs : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetInitialPage: (Destination*)dest;
- (void)SetPageMode: (PageMode)mode;
- (PageMode)GetPageMode;
- (void)SetLayoutMode: (PageLayout)layout;
- (PageLayout)GetLayoutMode;
- (void)SetPref: (ViewerPref)pref value:  (BOOL)value;
- (BOOL)GetPref: (ViewerPref)pref;
- (void)SetNonFullScreenPageMode: (PageMode)mode;
- (PageMode)GetNonFullScreenPageMode;
- (void)SetDirection: (BOOL)left_to_right;
- (BOOL)GetDirection;
- (void)SetViewArea: (Box)box;
- (Box)GetViewArea;
- (void)SetViewClip: (Box)box;
- (Box)GetViewClip;
- (void)SetPrintArea: (Box)box;
- (Box)GetPrintArea;
- (void)SetPrintClip: (Box)box;
- (Box)GetPrintClip;
- (Obj*)GetSDFObj;
- (id)initWithTr: (Obj*)tr;
@end


@interface PDFDoc : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Close;
- (BOOL)IsEncrypted;
- (BOOL)InitSecurityHandler;
- (BOOL)InitStdSecurityHandlerWithPassword: (NSString *)password password_sz:  (int)password_sz;
- (BOOL)InitStdSecurityHandler: (NSString *)password;
- (SecurityHandler*)GetSecurityHandler;
- (void)SetSecurityHandler: (SecurityHandler*)handler;
- (void)RemoveSecurity;
- (BOOL)HasSignatures;
- (SignatureHandlerId)AddSignatureHandler: (SignatureHandler*)signature_handler;
- (void)RemoveSignatureHandler: (unsigned long)signature_handler_id;
- (SignatureHandler*)GetSignatureHandler: (SignatureHandlerId)signature_handler_id;
- (PDFDocInfo*)GetDocInfo;
- (PDFDocViewPrefs*)GetViewPrefs;
- (BOOL)IsModified;
- (BOOL)IsLinearized;
- (void)SaveToFile: (NSString*)path flags:  (unsigned int)flags;
- (NSData*)SaveToBuf: (unsigned int)flags;
- (void)Save: (Filter*)stream flags:  (unsigned int)flags;
- (PageIterator*)GetPageIterator: (unsigned int)page_number;
- (Page*)GetPage: (unsigned int)page_number;
- (void)PageRemove: (PageIterator*)page_itr;
- (void)PageInsert: (PageIterator*)where page:  (Page*)page;
- (void)InsertPages: (int)insertBeforeThisPage sourceDoc:  (PDFDoc*)sourceDoc startPage:  (int)startPage endPage:  (int)endPage flag:  (InsertFlag)flag;
- (void)InsertPagesWithPageSet: (int)insertBeforeThisPage sourceDoc:  (PDFDoc*)sourceDoc sourcePageSet:  (PageSet*)sourcePageSet flag:  (InsertFlag)flag;
- (void)MovePages: (int)moveBeforeThisPage sourceDoc:  (PDFDoc*)sourceDoc startPage:  (int)startPage endPage:  (int)endPage flag:  (InsertFlag)flag;
- (void)MovePagesWithPageSet: (int)moveBeforeThisPage sourceDoc:  (PDFDoc*)sourceDoc sourcePageSet:  (PageSet*)sourcePageSet flag:  (InsertFlag)flag;
- (void)PagePushFront: (Page*)page;
- (void)PagePushBack: (Page*)page;
- (VectorPage*)ImportPages: (VectorPage*)pages import_bookmarks:  (BOOL)import_bookmarks;
- (Page*)PageCreate: (PDFRect*)media_box;
- (Bookmark*)GetFirstBookmark;
- (void)AddRootBookmark: (Bookmark*)root_bookmark;
- (Obj*)GetTrailer;
- (Obj*)GetRoot;
- (Obj*)GetPages;
- (int)GetPageCount;
- (FieldIterator*)GetFieldIterator;
- (FieldIterator*)GetFieldIteratorWithName: (NSString*)field_name;
- (TRNField*)GetField: (NSString*)field_name;
- (TRNField*)FieldCreateWithObj: (NSString*)field_name type:  (FieldType)type field_value:  (Obj*)field_value def_field_value:  (Obj*)def_field_value;
- (TRNField*)FieldCreate: (NSString*)field_name type:  (FieldType)type field_value:  (Obj*)field_value;
- (TRNField*)FieldCreateWithString: (NSString*)field_name type:  (FieldType)type field_value:  (NSString*)field_value def_field_value:  (NSString*)def_field_value;
- (void)RefreshFieldAppearances;
- (void)FlattenAnnotations: (BOOL)forms_only;
- (Obj*)GetAcroForm;
- (FDFDoc*)FDFExtract: (ExtractFlag)flag;
- (void)FDFMerge: (FDFDoc*)fdf_doc;
- (Action*)GetOpenAction;
- (void)SetOpenAction: (Action*)action;
- (void)AddFileAttachment: (NSString*)file_key embedded_file:  (FileSpec*)embedded_file;
- (PageLabel*)GetPageLabel: (int)page_num;
- (void)SetPageLabel: (int)page_num label:  (PageLabel*)label;
- (void)RemovePageLabel: (int)page_num;
- (BOOL)IsTagged;
- (STree*)GetStructTree;
- (BOOL)HasOC;
- (Obj*)GetOCGs;
- (Config*)GetOCGConfig;
- (void)AddHighlights: (NSString*)hilite;
- (Obj*)CreateIndirectName: (NSString *)name;
- (Obj*)CreateIndirectArray;
- (Obj*)CreateIndirectBool: (BOOL)value;
- (Obj*)CreateIndirectDict;
- (Obj*)CreateIndirectNull;
- (Obj*)CreateIndirectNumber: (double)value;
- (Obj*)CreateIndirectString: (NSData*)value size:  (unsigned int)size;
- (Obj*)CreateIndirectStream: (FilterReader*)data filter_chain:  (Filter*)filter_chain;
- (SDFDoc*)GetSDFDoc;
- (void)Lock;
- (void)Unlock;
- (BOOL)TryLock: (int)milliseconds;
- (void)LockRead;
- (void)UnlockRead;
- (BOOL)TryLockRead: (int)milliseconds;
- (NSString*)GetFileName;
- (id)init;- (id)initWithSdfdoc: (SDFDoc*)sdfdoc;- (id)initWithFilepath: (NSString*)filepath;- (id)initWithStream: (Filter*)stream;- (id)initWithBuf: (NSData*)buf buf_size:  (unsigned long)buf_size;
@end


@interface PDFRasterizer : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (NSData*)Rasterize: (Page*)page width:  (int)width height:  (int)height stride:  (int)stride num_comps:  (int)num_comps demult:  (BOOL)demult device_mtx:  (Matrix2D*)device_mtx clip:  (PDFRect*)clip scrl_clp_regions:  (PDFRect*)scrl_clp_regions cancel:  (SWIGTYPE_p_bool*)cancel;
- (void)SetDrawAnnotations: (BOOL)render_annots;
- (void)SetHighlightFields: (BOOL)highlight_fields;
- (void)SetAntiAliasing: (BOOL)enable_aa;
- (void)SetPathHinting: (BOOL)path_hinting;
- (void)SetThinLineAdjustment: (BOOL)pixel_grid_fit stroke_adjust:  (BOOL)stroke_adjust;
- (void)SetImageSmoothing: (BOOL)smoothing_enabled;
- (void)SetCaching: (BOOL)enabled;
- (void)SetGamma: (double)exp;
- (void)SetOCGContext: (Context*)ctx;
- (void)SetPrintMode: (BOOL)is_printing;
- (void)SetOverprint: (OverprintPreviewMode)op;
- (void)SetErrorReportProc: (Callback*)instance;
- (void)SetRasterizerType: (RasterizerType)type;
- (RasterizerType)GetRasterizerType;
- (void)Destroy;
- (id)initWithType: (RasterizerType)type;
@end


@interface BitmapInfo : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
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


@interface PDFDraw : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetRasterizerType: (RasterizerType)type;
- (void)SetDPI: (double)dpi;
- (void)SetImageSize: (int)width height:  (int)height preserve_aspect_ratio:  (BOOL)preserve_aspect_ratio;
- (void)SetPageBox: (Box)region;
- (void)SetFlipYAxis: (BOOL)flip_y;
- (void)SetRotate: (Rotate)r;
- (void)SetDrawAnnotations: (BOOL)render_annots;
- (void)SetHighlightFields: (BOOL)highlight_fields;
- (void)SetAntiAliasing: (BOOL)enable_aa;
- (void)SetPathHinting: (BOOL)path_hinting;
- (void)SetThinLineAdjustment: (BOOL)pixel_grid_fit stroke_adjust:  (BOOL)stroke_adjust;
- (void)SetImageSmoothing: (BOOL)smoothing_enabled;
- (void)SetCaching: (BOOL)enabled;
- (void)SetGamma: (double)exp;
- (void)SetOCGContext: (Context*)ctx;
- (void)SetPrintMode: (BOOL)is_printing;
- (void)SetDefaultPageColor: (unsigned char)r g:  (unsigned char)g b:  (unsigned char)b;
- (void)SetPageTransparent: (BOOL)is_transparent;
- (void)SetOverprint: (OverprintPreviewMode)op;
- (void)ExportWithObj: (Page*)page filename:  (NSString*)filename format:  (NSString *)format encoder_params:  (Obj*)encoder_params;
- (void)Export: (Page*)page filename:  (NSString*)filename format:  (NSString *)format;
- (BitmapInfo*)GetBitmap: (Page*)page pix_fmt:  (PixelFormat)pix_fmt demult:  (BOOL)demult;
- (void)SetErrorReportProc: (Callback*)instance;
- (void)Destroy;
- (id)initWithDpi: (double)dpi;
@end


@interface PDFNet : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (void)Initialize: (NSString *)license_key;
+ (BOOL)SetResourcesPath: (NSString*)path;
+ (NSString*)GetResourcesPath;
+ (double)GetVersion;
+ (CloudErrorCode)ConnectToCloud: (NSString *)api_id api_secret:  (NSString *)api_secret;
+ (void)SetColorManagement: (CMSType)t;
+ (void)SetDefaultDeviceCMYKProfile: (NSString*)icc_filename;
+ (void)SetDefaultDeviceRGBProfile: (NSString*)icc_filename;
+ (void)SetDefaultDiskCachingEnabled: (BOOL)use_disk;
+ (void)SetViewerCache: (unsigned long)max_cache_size max_zoom_factor:  (unsigned long)max_zoom_factor;
+ (BOOL)AddFontSubstWithFontName: (NSString *)fontname fontpath:  (NSString*)fontpath;
+ (BOOL)AddFontSubstWithOrdering: (CharacterOrdering)ordering fontpath:  (NSString*)fontpath;
+ (BOOL)SetTempPath: (NSString*)temp_path;
- (id)init;
@end


@interface PDFView : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)SetDoc: (PDFDoc*)doc;
- (void)CloseDoc;
- (PDFDoc*)GetDoc;
- (void)DocLock: (BOOL)cancel_threads;
- (void)DocUnlock;
- (BOOL)DocTryLock: (int)milliseconds;
- (void)DocLockRead;
- (void)DocUnlockRead;
- (BOOL)DocTryLockRead: (int)milliseconds;
- (void)SetPagePresentationMode: (PagePresentationMode)mode;
- (PagePresentationMode)GetPagePresentationMode;
- (int)GetCurrentPage;
- (int)GetPageCount;
- (BOOL)GotoFirstPage;
- (BOOL)GotoLastPage;
- (BOOL)GotoNextPage;
- (BOOL)GotoPreviousPage;
- (BOOL)SetCurrentPage: (int)page_num;
- (BOOL)ShowRect: (int)page_num rect:  (PDFRect*)rect;
- (double)GetZoom;
- (BOOL)SetZoom: (double)zoom;
- (BOOL)SetZoomWithCoord: (int)x y:  (int)y zoom:  (double)zoom;
- (BOOL)SmartZoom: (int)x y:  (int)y;
- (void)RotateClockwise;
- (void)RotateCounterClockwise;
- (Rotate)GetRotation;
- (int)GetPageNumberFromScreenPt: (double)x y:  (double)y;
- (PDFPoint*)ConvScreenPtToCanvasPt: (PDFPoint*)pt;
- (PDFPoint*)ConvCanvasPtToScreenPt: (PDFPoint*)pt;
- (PDFPoint*)ConvCanvasPtToPagePt: (PDFPoint*)pt page_num:  (int)page_num;
- (PDFPoint*)ConvPagePtToCanvasPt: (PDFPoint*)pt page_num:  (int)page_num;
- (PDFPoint*)ConvScreenPtToPagePt: (PDFPoint*)pt page_num:  (int)page_num;
- (PDFPoint*)ConvPagePtToScreenPt: (PDFPoint*)pt page_num:  (int)page_num;
- (Matrix2D*)GetDeviceTransform: (int)page_num;
- (void)SetErrorReportProc: (Callback*)instance;
- (void)SetCurrentPageProc: (Callback*)instance;
- (void)SetCurrentZoomProc: (Callback*)instance;
- (double)GetCanvasWidth;
- (double)GetCanvasHeight;
- (double)GetHScrollPos;
- (double)GetVScrollPos;
- (void)OnScroll: (int)pix_dx pix_dy:  (int)pix_dy;
- (void)SetHScrollPos: (double)pos;
- (void)SetVScrollPos: (double)pos;
- (void)OnSize: (int)width height:  (int)height;
- (BOOL)IsFinishedRendering: (BOOL)visible_region_only;
- (void)CancelRendering;
- (void)Update;
- (void)UpdateWithRect: (PDFRect*)update;
- (void)UpdateWithAnnot: (Annot*)annot page_num:  (int)page_num;
- (void)UpdatePageLayout;
- (NSData*)GetBuffer;
- (void)UpdateBuffer;
- (int)GetBufferWidth;
- (int)GetBufferHeight;
- (int)GetBufferStride;
- (void)SetDrawAnnotations: (BOOL)render_annots;
- (void)SetUrlExtraction: (BOOL)enabled;
- (SWIGTYPE_pdftron__PDF__PDFView__LinkInfo*)GetLinkAt: (int)x y:  (int)y;
- (void)SetHighlightFields: (BOOL)highlight_fields;
- (void)SetAntiAliasing: (BOOL)enable_aa;
- (void)SetPathHinting: (BOOL)path_hinting;
- (void)SetThinLineAdjustment: (BOOL)pixel_grid_fit stroke_adjust:  (BOOL)stroke_adjust;
- (void)SetImageSmoothing: (BOOL)smoothing_enabled;
- (void)SetCaching: (BOOL)enabled;
- (void)SetRasterizerType: (RasterizerType)type;
- (void)SetGamma: (double)exp;
- (void)SetOverprint: (OverprintPreviewMode)op;
- (void)SetOCGContext: (Context*)ctx;
- (Context*)GetOCGContext;
- (void)SetRenderBeginProc: (Callback*)instance;
- (void)SetRenderFinishProc: (Callback*)instance;
- (void)SetTextSelectionMode: (TextSelectionMode)tm;
- (BOOL)SelectWithTextSelect: (double)x1 y1:  (double)y1 x2:  (double)x2 y2:  (double)y2;
- (BOOL)SelectWithStructure: (double)x1 y1:  (double)y1 page1:  (int)page1 x2:  (double)x2 y2:  (double)y2 page2:  (int)page2;
- (BOOL)SelectWithHighlights: (Highlights*)highlights;
- (BOOL)SelectWithSelection: (Selection*)select;
- (BOOL)FindText: (NSString*)search_str match_case:  (BOOL)match_case match_whole_word:  (BOOL)match_whole_word search_up:  (BOOL)search_up reg_exp:  (BOOL)reg_exp;
- (void)SelectAll;
- (BOOL)HasSelection;
- (void)ClearSelection;
- (Selection*)GetSelection: (int)pagenum;
- (int)GetSelectionBeginPage;
- (int)GetSelectionEndPage;
- (BOOL)HasSelectionOnPage: (int)ipage;
- (void)SetPageBorderVisibility: (BOOL)border_visible;
- (void)SetPageTransparencyGrid: (BOOL)trans_grid_visible;
- (void)SetDefaultPageColor: (unsigned char)r g:  (unsigned char)g b:  (unsigned char)b;
- (void)SetBackgroundColor: (unsigned char)r g:  (unsigned char)g b:  (unsigned char)b a:  (unsigned char)a;
- (void)SetHorizontalAlign: (int)align;
- (void)SetVerticalAlign: (int)align;
- (void)SetPageSpacing: (int)horiz_col_space vert_col_space:  (int)vert_col_space horiz_pad:  (int)horiz_pad vert_pad:  (int)vert_pad;
+ (void)SetViewerCache: (SDFDoc*)document max_cache_size:  (unsigned long)max_cache_size max_zoom_factor:  (unsigned long)max_zoom_factor;
- (void)Destroy;
- (Annot*)GetAnnotationAt: (int)x y:  (int)y;
- (void)SetPageViewMode: (PageViewMode)mode;
- (PageViewMode)GetPageViewMode;
- (void)SetPageRefViewMode: (PageViewMode)mode;
- (PageViewMode)GetPageRefViewMode;
- (void)SetupThumbnails: (BOOL)use_embedded generate_at_runtime:  (BOOL)generate_at_runtime use_persistent_cache:  (BOOL)use_persistent_cache thumb_max_side_length:  (int)thumb_max_side_length cache_directory_path:  (NSString*)cache_directory_path cache_data_file_size:  (int)cache_data_file_size;
- (void)GetThumbAsync: (int)page_num instance:  (Callback*)instance;
- (void)SetFindTextHandler: (Callback*)instance;
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
- (id)init;
@end


@interface HTML2PDF : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)InsertFromURL: (NSString*)url;
- (void)InsertFromURLWithSettings: (NSString*)url settings:  (WebPageSettings*)settings;
- (void)InsertFromHtmlString: (NSString*)html;
- (void)InsertFromHtmlStringWithSettings: (NSString*)html settings:  (WebPageSettings*)settings;
- (void)InsertTOC;
- (void)InsertTOCWithSettings: (TOCSettings*)settings;
- (BOOL)Convert: (PDFDoc*)doc;
- (int)GetHTTPErrorCode;
- (void)SetQuiet: (BOOL)quiet;
- (NSString*)GetLog;
+ (void)SetModulePath: (NSString*)path;
- (void)SetPaperSize: (SWIGTYPE_PrinterMode__PaperSize*)size;
- (void)SetPaperSizeWithWidthAndHeight: (NSString*)width height:  (NSString*)height;
- (void)SetLandscape: (BOOL)enable;
- (void)SetDPI: (int)dpi;
- (void)SetOutline: (BOOL)enable depth:  (int)depth;
- (void)DumpOutline: (NSString*)xml_file;
- (void)SetPDFCompression: (BOOL)enable;
- (void)SetMargins: (NSString*)top bottom:  (NSString*)bottom left:  (NSString*)left right:  (NSString*)right;
- (void)SetImageDPI: (int)dpi;
- (void)SetImageQuality: (int)quality;
- (void)SetCookieJar: (NSString*)path;
- (void)Destroy;
- (id)init;
@end


@interface Stamper : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)StampImage: (PDFDoc*)dest_doc src_img:  (Image*)src_img dest_pages:  (PageSet*)dest_pages;
- (void)StampPage: (PDFDoc*)dest_doc src_page:  (Page*)src_page dest_pages:  (PageSet*)dest_pages;
- (void)StampText: (PDFDoc*)dest_doc src_txt:  (NSString*)src_txt dest_pages:  (PageSet*)dest_pages;
- (void)SetFont: (Font*)font;
- (void)SetFontColor: (ColorPt*)color;
- (void)SetOpacity: (double)opacity;
- (void)SetRotation: (double)rotation;
- (void)SetAsBackground: (BOOL)background;
- (void)SetAsAnnotation: (BOOL)annotation;
- (void)ShowsOnScreen: (BOOL)on_screen;
- (void)ShowsOnPrint: (BOOL)on_print;
- (void)SetPosition: (double)horizontal_distance vertical_distance:  (double)vertical_distance percentage:  (BOOL)percentage;
- (void)SetAlignment: (HorizontalAlignment)horizontal_alignment vertical_alignment:  (VerticalAlignment)vertical_alignment;
- (void)SetTextAlignment: (TextAlignment)text_alignment;
- (void)SetSize: (SizeType)size_type a:  (double)a b:  (double)b;
+ (void)DeleteStamps: (PDFDoc*)doc page_set:  (PageSet*)page_set;
+ (BOOL)HasStamps: (PDFDoc*)doc page_set:  (PageSet*)page_set;
- (void)Destroy;
- (id)initWithSize_type: (SizeType)size_type a:  (double)a b:  (double)b;
@end


@interface TextExtractor : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)Begin: (Page*)page clip_ptr:  (PDFRect*)clip_ptr flags:  (unsigned int)flags;
- (int)GetWordCount;
- (NSString*)GetAsText: (BOOL)dehyphen;
- (NSString*)GetTextUnderAnnot: (Annot*)annot;
- (NSString*)GetAsXML: (unsigned int)xml_output_flags;
- (int)GetNumLines;
- (TextExtractorLine*)GetFirstLine;
- (void)Destroy;
- (id)init;
@end


@interface SearchResult : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (BOOL)IsFound;
- (BOOL)IsDocEnd;
- (BOOL)IsPageEnd;
- (int)GetPageNumber;
- (NSString*)GetMatch;
- (NSString*)GetAmbientString;
- (Highlights*)GetHighlights;
- (id)init;
@end


@interface TextSearch : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (BOOL)Begin: (PDFDoc*)doc pattern:  (NSString*)pattern mode:  (unsigned int)mode start_page:  (int)start_page end_page:  (int)end_page;
- (SearchResult*)Run;
- (BOOL)SetPattern: (NSString*)pattern;
- (unsigned int)GetMode;
- (void)SetMode: (unsigned int)mode;
- (int)GetCurrentPage;
- (void)Destroy;
- (id)init;
@end


@interface Appearance : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
- (void)setRedactionOverlay: (BOOL)value;
- (BOOL)getRedactionOverlay;
- (void)setPositiveOverlayColor: (SWIGTYPE_ColorPt*)value;
- (SWIGTYPE_ColorPt*)getPositiveOverlayColor;
- (void)setNegativeOverlayColor: (SWIGTYPE_ColorPt*)value;
- (SWIGTYPE_ColorPt*)getNegativeOverlayColor;
- (void)setBorder: (BOOL)value;
- (BOOL)getBorder;
- (void)setUseOverlayText: (BOOL)value;
- (BOOL)getUseOverlayText;
- (void)setTextFont: (Font*)value;
- (Font*)getTextFont;
- (void)setMinFontSize: (double)value;
- (double)getMinFontSize;
- (void)setMaxFontSize: (double)value;
- (double)getMaxFontSize;
- (void)setTextColor: (ColorPt*)value;
- (ColorPt*)getTextColor;
- (void)setHorizTextAlignment: (int)value;
- (int)getHorizTextAlignment;
- (void)setVertTextAlignment: (int)value;
- (int)getVertTextAlignment;
- (id)init;
@end


@interface Redactor : NSObject
{
	void *swigCPtr;
	BOOL swigCMemOwn;
}
- (void*)getCptr;
- (id)initWithCptr: (void*) cptr;
- (void)setSwigCMemOwn: (BOOL) own;
- (void)dealloc;
+ (void)Redact: (PDFDoc*)doc red_arr:  (VectorRedaction*)red_arr app:  (Appearance*)app ext_neg_mode:  (BOOL)ext_neg_mode page_coord_sys:  (BOOL)page_coord_sys;
- (id)init;
@end



#endif // PDFNetOBJC_H

