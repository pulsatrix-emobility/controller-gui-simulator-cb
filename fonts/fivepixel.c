/*******************************************************************************
 * Size: 5 px
 * Bpp: 1
 * Opts:
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef FIVEPIXEL
#define FIVEPIXEL 1
#endif

#if FIVEPIXEL

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
        /* U+0020 " " */
        0x0,

        /* U+0030 "0" */
        0xf6, 0xde,

        /* U+0031 "1" */
        0xd5, 0x40,

        /* U+0032 "2" */
        0xe7, 0xce,

        /* U+0033 "3" */
        0xe5, 0x1e,

        /* U+0034 "4" */
        0xb7, 0x92,

        /* U+0035 "5" */
        0xf3, 0x9e,

        /* U+0036 "6" */
        0xf3, 0xde,

        /* U+0037 "7" */
        0xe5, 0x28,

        /* U+0038 "8" */
        0xf5, 0x5e,

        /* U+0039 "9" */
        0xf7, 0x9e,

        /* U+0041 "A" */
        0xf6, 0xfa,

        /* U+0042 "B" */
        0xf7, 0x5e,

        /* U+0043 "C" */
        0xf6, 0x5e,

        /* U+0044 "D" */
        0xf6, 0xde,

        /* U+0045 "E" */
        0xf3, 0xce,

        /* U+0046 "F" */
        0xf3, 0xc8,

        /* U+0047 "G" */
        0xf2, 0xde,

        /* U+0048 "H" */
        0xb7, 0xda,

        /* U+0049 "I" */
        0xe9, 0x2e,

        /* U+004A "J" */
        0x24, 0xde,

        /* U+004B "K" */
        0xb7, 0xda,

        /* U+004C "L" */
        0x92, 0x4e,

        /* U+004D "M" */
        0xfd, 0x6b, 0x5a, 0x80,

        /* U+004E "N" */
        0xf6, 0xda,

        /* U+004F "O" */
        0xf6, 0xde,

        /* U+0050 "P" */
        0xf7, 0xc8,

        /* U+0051 "Q" */
        0xf6, 0xfe,

        /* U+0052 "R" */
        0xf7, 0xda,

        /* U+0053 "S" */
        0xf3, 0x9e,

        /* U+0054 "T" */
        0xe9, 0x24,

        /* U+0055 "U" */
        0xb6, 0xde,

        /* U+0056 "V" */
        0xb6, 0xd4,

        /* U+0057 "W" */
        0xad, 0x6b, 0x5f, 0x80,

        /* U+0058 "X" */
        0xb5, 0x5a,

        /* U+0059 "Y" */
        0xb5, 0x24,

        /* U+005A "Z" */
        0xe5, 0x4e
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
        {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
        {.bitmap_index = 0, .adv_w = 16+10, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 1, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 3, .adv_w = 32+10, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 5, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 7, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 9, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 11, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 13, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 15, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 17, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 19, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 21, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 23, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 25, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 27, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 29, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 31, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 33, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 35, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 37, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 39, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 41, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 43, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 45, .adv_w = 80+10, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 49, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 51, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 53, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 55, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 57, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 59, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 61, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 63, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 65, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 67, .adv_w = 80+10, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 71, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 73, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
        {.bitmap_index = 75, .adv_w = 48+10, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
        {
                {
                        .range_start = 32, .range_length = 1, .glyph_id_start = 1,
                        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
                },
                {
                        .range_start = 48, .range_length = 10, .glyph_id_start = 2,
                        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
                },
                {
                        .range_start = 65, .range_length = 26, .glyph_id_start = 12,
                        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
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
        .cmap_num = 3,
        .bpp = 1,
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
const lv_font_t fivepixel = {
#else
lv_font_t fivepixel = {
#endif
        .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
        .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
        .line_height = 5,          /*The maximum line height required by the font*/
        .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
        .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
        .underline_position = 0,
        .underline_thickness = 0,
#endif
        .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FIVEPIXEL*/

