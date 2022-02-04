#include "styles.h"

#include <stdarg.h>

bool _stylesInitialized = false;
lv_style_t mainIconStyle;
lv_style_t noBorderStyle;
lv_style_t smallInfoLabelStyle;
lv_style_t largeInfoLabelStyle;

lv_style_t statusChipStyle;

void initStyles() {
  if (!_stylesInitialized) {
    _stylesInitialized = true;

    lv_style_init(&noBorderStyle);
    lv_style_set_pad_all(&noBorderStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_top(&noBorderStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_inner(&noBorderStyle, LV_STATE_DEFAULT, 2);
    lv_style_set_border_width(&noBorderStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_opa(&noBorderStyle, LV_STATE_DEFAULT, 0);

    // Icons
    lv_style_init(&mainIconStyle);
    lv_style_copy(&noBorderStyle, &mainIconStyle);
    lv_style_set_text_font(&mainIconStyle, LV_STATE_DEFAULT, &icons);
    lv_style_set_pad_ver(&mainIconStyle, LV_STATE_DEFAULT, 2);
    lv_style_set_margin_top(&mainIconStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_pad_hor(&mainIconStyle, LV_STATE_DEFAULT, 3);
    lv_style_set_text_color(&mainIconStyle, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_style_set_text_color(&mainIconStyle, LV_STATE_CHECKED, LV_COLOR_WHITE);

    lv_style_set_bg_opa(&mainIconStyle, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&mainIconStyle, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x30, 0x30, 0x30));
    lv_style_set_bg_color(&mainIconStyle, LV_STATE_FOCUSED, LV_COLOR_MAKE(0x3d, 0x6b, 0xdc));

    // info labels
    lv_style_init(&smallInfoLabelStyle);
    lv_style_set_text_font(&smallInfoLabelStyle, LV_STATE_DEFAULT, &FiraSansMedium10);
    lv_style_set_text_color(&smallInfoLabelStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    lv_style_init(&largeInfoLabelStyle);
    lv_style_set_text_font(&largeInfoLabelStyle, LV_STATE_DEFAULT, &FiraSansMedium13);
    lv_style_set_text_color(&largeInfoLabelStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    // status chips
    lv_style_init(&statusChipStyle);
    lv_style_set_pad_all(&statusChipStyle, LV_STATE_DEFAULT, 2);
    lv_style_set_bg_color(&statusChipStyle, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_style_set_bg_opa(&statusChipStyle, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_text_font(&statusChipStyle, LV_STATE_DEFAULT, &FivePixel);
    lv_style_set_radius(&statusChipStyle, LV_STATE_DEFAULT, 2);
    lv_style_set_text_color(&statusChipStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    // fudge the fonts for slightly tighter lines
    FiraSansMedium10.line_height = 12;
    FiraSansMedium13.line_height = 13;
    IBMPlexSansMedium13.line_height = 12;
  }
}
