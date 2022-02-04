#pragma once

#include <lvgl.h>

LV_IMG_DECLARE(pulsatrixLogo);

#define COLOR_LIGHT_RED             lv_color_make(0xFF, 0x40, 0x40)
#define COLOR_LIGHT_GREEN           lv_color_make(0x40, 0xFF, 0x40)
#define COLOR_PULSATRIX_MINT        lv_color_make(0x05, 0xD6, 0x72)
#define COLOR_PULSATRIX_DARK_PURPLE lv_color_make(0x3A, 0x01, 0x3F)

#ifdef __cplusplus
extern "C" {
#endif

extern lv_style_t mainIconStyle;
extern lv_style_t noBorderStyle;
extern lv_style_t smallInfoLabelStyle;
extern lv_style_t largeInfoLabelStyle;
extern lv_style_t statusChipStyle;

extern void initStyles();

#ifdef __cplusplus
}
#endif
