/*******************************************************************************
 * Size: 12 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ICONS
#define ICONS 1
#endif

#if ICONS

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0041 "A" */
    0x0, 0x0, 0x8, 0x80, 0x0, 0x0, 0x0, 0x0,
    0x8e, 0xe9, 0x0, 0x0, 0x0, 0x8, 0xe2, 0x2e,
    0x90, 0x0, 0x0, 0x8e, 0x20, 0x2, 0xe9, 0x0,
    0x8, 0xe2, 0x0, 0x0, 0x2d, 0x90, 0x8e, 0x20,
    0x0, 0x0, 0x1, 0xd9, 0x82, 0x20, 0x0, 0x0,
    0x2, 0x18, 0x2, 0xf0, 0x0, 0x0, 0xf, 0x20,
    0x3, 0xf0, 0x0, 0x0, 0xf, 0x30, 0x3, 0xf0,
    0x0, 0x0, 0xf, 0x30, 0x3, 0xf0, 0x0, 0x0,
    0xf, 0x30, 0x2, 0xff, 0xff, 0xff, 0xff, 0x20,
    0x0, 0x23, 0x33, 0x33, 0x32, 0x0,

    /* U+0042 "B" */
    0xef, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf5, 0x22,
    0x22, 0x22, 0x22, 0x5f, 0xf3, 0x76, 0x1f, 0xf1,
    0x0, 0x2f, 0xf3, 0x66, 0x2, 0x20, 0x0, 0x2f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x22, 0x22,
    0x2a, 0xa2, 0x22, 0x21, 0x0, 0x0, 0x9, 0x90,
    0x0, 0x0, 0x0, 0x0, 0x9, 0x90, 0x0, 0x0,
    0xa, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x1, 0x22,
    0x22, 0x22, 0x22, 0x10,

    /* U+0043 "C" */
    0x0, 0xa6, 0x0, 0x0, 0x6a, 0x0, 0xa, 0xd1,
    0x0, 0x0, 0x1d, 0xa0, 0xad, 0x10, 0x9, 0x90,
    0x1, 0xda, 0xad, 0x10, 0x9, 0x90, 0x1, 0xda,
    0xa, 0xd1, 0x0, 0x0, 0x1d, 0xa0, 0x0, 0xa6,
    0x0, 0x0, 0x7a, 0x0,

    /* U+0044 "D" */
    0xef, 0xff, 0xe9, 0x10, 0x2c, 0xfe, 0x35, 0x8c,
    0xff, 0xf6, 0x0, 0xbf, 0x0, 0x0, 0x3b, 0xff,
    0x90, 0xc, 0xfd, 0x94, 0x0, 0x6f, 0xf9, 0x2,
    0xff, 0xff, 0xc2, 0x4, 0xff, 0x60, 0x1, 0x6d,
    0xff, 0x50, 0x6f, 0xf1, 0x10, 0x0, 0x9f, 0xf3,
    0xb, 0xf9, 0xfe, 0x80, 0x9, 0xfd, 0x2, 0xff,
    0xff, 0xfc, 0x0, 0xdf, 0x60, 0xcf, 0xff, 0xff,
    0x90, 0x6f, 0xb0, 0x6f, 0xff, 0xff, 0xf0, 0x1f,
    0xf0, 0x4f, 0xef, 0xff, 0xf3, 0xf, 0xf1, 0x2e,

    /* U+0045 "E" */
    0x0, 0x7f, 0xff, 0xf2, 0x0, 0x0, 0x0, 0x0,
    0x25, 0xff, 0x30, 0x0, 0x0, 0x0, 0x2, 0xe8,
    0xf3, 0x0, 0x0, 0x0, 0x2, 0xe8, 0xf, 0x30,
    0x0, 0x0, 0x2, 0xe8, 0x0, 0xb1, 0x0, 0x0,
    0x1, 0xe9, 0x0, 0x0, 0x0, 0x7, 0xd0, 0xc9,
    0x0, 0x0, 0x0, 0x6, 0xf3, 0x2, 0x0, 0x0,
    0x80, 0x6, 0xf3, 0x0, 0x0, 0x0, 0x2f, 0x6,
    0xf4, 0x0, 0x0, 0x0, 0x2, 0xf5, 0xf4, 0x0,
    0x0, 0x0, 0x0, 0x2f, 0xf4, 0x0, 0x0, 0x0,
    0x0, 0x2, 0xff, 0xff, 0x70, 0x0, 0x0, 0x0,
    0x2, 0x22, 0x20, 0x0, 0x0,

    /* U+0046 "F" */
    0x0, 0x3d, 0xff, 0xff, 0xd3, 0x0, 0x0, 0xc6,
    0x0, 0x0, 0x5c, 0x0, 0x1, 0xf0, 0x0, 0x0,
    0xf, 0x10, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xfc,
    0xf, 0x5, 0x0, 0x0, 0x50, 0xf0, 0xf, 0x5f,
    0x40, 0x3, 0xf6, 0xf0, 0xf, 0x5, 0x0, 0x0,
    0x50, 0xf0, 0xf, 0xff, 0xff, 0xff, 0xff, 0xf0,
    0xf, 0xf4, 0x0, 0x0, 0x3f, 0xf0, 0x4, 0x60,
    0x0, 0x0, 0x6, 0x40,

    /* U+0047 "G" */
    0x6e, 0xff, 0xff, 0xff, 0xf8, 0x0, 0xe7, 0x33,
    0x33, 0x33, 0x4f, 0x10, 0xf3, 0x0, 0x0, 0x0,
    0xf, 0xfb, 0xf3, 0x0, 0x0, 0x0, 0x1, 0x5f,
    0xf3, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xf3, 0x0,
    0x0, 0x0, 0xe, 0xfd, 0xf4, 0x0, 0x0, 0x0,
    0x1f, 0x40, 0x9f, 0xff, 0xff, 0xff, 0xfb, 0x0,
    0x1, 0x33, 0x33, 0x33, 0x20, 0x0,

    /* U+0048 "H" */
    0x0, 0x0, 0x0, 0x2c, 0x70, 0x0, 0x0, 0x7,
    0xff, 0x50, 0x0, 0x2, 0xce, 0x6f, 0x10, 0x0,
    0x7f, 0xa1, 0x5d, 0x0, 0x2c, 0xe4, 0x0, 0x9a,
    0x0, 0xbf, 0x81, 0x0, 0xbe, 0x60, 0x7, 0xec,
    0x0, 0x7, 0xfb, 0x0, 0x89, 0x0, 0x6f, 0xb2,
    0x0, 0xc6, 0x1b, 0xf6, 0x0, 0x0, 0xf7, 0xec,
    0x20, 0x0, 0x4, 0xff, 0x70, 0x0, 0x0, 0x6,
    0xc2, 0x0, 0x0, 0x0,

    /* U+004A "J" */
    0x1c, 0xff, 0xfe, 0x40, 0x0, 0x0, 0x5, 0xff,
    0xff, 0xfa, 0x0, 0x0, 0x0, 0x5f, 0x50, 0xcf,
    0xa0, 0x1, 0x0, 0x5, 0xf3, 0xe, 0xfa, 0x0,
    0x95, 0x60, 0x5f, 0x10, 0xa, 0xa0, 0x2d, 0xcc,
    0x5, 0xf0, 0x2, 0xfa, 0x3, 0xff, 0xf0, 0x5f,
    0xf5, 0xaf, 0xa0, 0xb, 0xf8, 0x5, 0xff, 0x4f,
    0xff, 0xd2, 0x1d, 0x0, 0x5f, 0xfd, 0xff, 0xa7,
    0xa1, 0xd0, 0x5, 0xff, 0xff, 0xfa, 0x3c, 0x3d,
    0x0, 0x39, 0x99, 0x99, 0x60, 0xbf, 0x60, 0xf,
    0xff, 0xff, 0xff, 0x40, 0x0, 0x0, 0x78, 0x88,
    0x88, 0x82, 0x0, 0x0, 0x0,

    /* U+004B "K" */
    0x0, 0x0, 0x1c, 0xf8, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x6f,
    0xff, 0x10, 0x0, 0x0, 0x0, 0x0, 0x8b, 0x50,
    0x0, 0x0, 0x0, 0x2, 0x50, 0x2, 0x90, 0x0,
    0x0, 0x0, 0xde, 0x0, 0x4f, 0x70, 0x0, 0x0,
    0x4f, 0x60, 0x0, 0xce, 0x0, 0x0, 0x0, 0x60,
    0x0, 0x2, 0x50, 0x0, 0x3b, 0xa1, 0x0, 0x0,
    0x4, 0xb9, 0xd, 0xff, 0xa0, 0x79, 0x40, 0xff,
    0xf7, 0xef, 0xfb, 0xe, 0xf8, 0x1f, 0xff, 0x85,
    0xed, 0x30, 0x0, 0x0, 0x7f, 0xc1
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 96, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 192, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 78, .adv_w = 192, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 192, .box_w = 12, .box_h = 6, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 174, .adv_w = 192, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 192, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 331, .adv_w = 192, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 192, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 445, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 193, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 202, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x2a, 0x2b
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 44, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 11, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t icons = {
#else
lv_font_t icons = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if ICONS*/
