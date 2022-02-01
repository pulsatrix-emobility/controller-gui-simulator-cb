#include "styles.h"

#include <stdarg.h>

bool _stylesInitialized = false;
lv_style_t mainIconStyle;
lv_style_t noBorderStyle;
lv_style_t smallInfoLabelStyle;
lv_style_t largeInfoLabelStyle;

void initStyles() {
  if (!_stylesInitialized) {
    _stylesInitialized = true;

    lv_style_init(&mainIconStyle);
    lv_style_set_text_font(&mainIconStyle, LV_STATE_DEFAULT, &Icons24);
    lv_style_set_text_color(&mainIconStyle, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_style_set_text_color(&mainIconStyle, LV_STATE_CHECKED, COLOR_PULSATRIX_MINT);
    lv_style_set_border_width(&mainIconStyle, LV_STATE_FOCUSED, 2);
    lv_style_set_border_color(&mainIconStyle, LV_STATE_FOCUSED, LV_COLOR_YELLOW);

    lv_style_init(&noBorderStyle);
    lv_style_set_pad_all(&noBorderStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_top(&noBorderStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_inner(&noBorderStyle, LV_STATE_DEFAULT, 2);
    lv_style_set_border_width(&noBorderStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_opa(&noBorderStyle, LV_STATE_DEFAULT, 0);

    lv_style_init(&smallInfoLabelStyle);
    lv_style_set_text_font(&smallInfoLabelStyle, LV_STATE_DEFAULT, &RobotoMedium10);
    lv_style_set_text_color(&smallInfoLabelStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    lv_style_init(&largeInfoLabelStyle);
    lv_style_set_text_font(&largeInfoLabelStyle, LV_STATE_DEFAULT, &RobotoMedium14);
    lv_style_set_text_color(&largeInfoLabelStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  }
}
