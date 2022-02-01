#pragma once

#include <lvgl.h>

LV_IMG_DECLARE(pulsatrixLogo);
LV_FONT_DECLARE(Icons12);
LV_FONT_DECLARE(Icons24);
LV_FONT_DECLARE(RobotoMedium14);
LV_FONT_DECLARE(RobotoMedium10);
LV_FONT_DECLARE(RobotoMonoMedium10);

#define COLOR_LIGHT_RED             LV_COLOR_MAKE(0xFF, 0x40, 0x40)
#define COLOR_LIGHT_GREEN           LV_COLOR_MAKE(0x40, 0xFF, 0x40)
#define COLOR_PULSATRIX_MINT        LV_COLOR_MAKE(0x05, 0xD6, 0x72)
#define COLOR_PULSATRIX_DARK_PURPLE LV_COLOR_MAKE(0x3A, 0x01, 0x3F)

#ifdef __cplusplus
extern "C" {
#endif

extern lv_style_t mainIconStyle;
extern lv_style_t noBorderStyle;
extern lv_style_t smallInfoLabelStyle;
extern lv_style_t largeInfoLabelStyle;

extern void initStyles();

#ifdef __cplusplus
}
#endif
