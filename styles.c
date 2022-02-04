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

    lv_theme_t *th = lv_theme_basic_init(lv_disp_get_default());
    lv_disp_set_theme(lv_disp_get_default(), th);

    lv_style_init(&mainIconStyle);
    lv_style_set_text_font(&mainIconStyle, &icons);
    lv_style_set_pad_ver(&mainIconStyle, 2);
    lv_style_set_pad_hor(&mainIconStyle, 3);
    lv_style_set_text_color(&mainIconStyle, lv_palette_main(LV_PALETTE_GREY));

    lv_style_set_bg_opa(&mainIconStyle, LV_OPA_COVER);

    lv_style_set_bg_color(&mainIconStyle, lv_color_make(0x30, 0x30, 0x30));
    lv_style_set_bg_color(&mainIconStyle, lv_color_make(0x3d, 0x6b, 0xdc));

    lv_style_init(&noBorderStyle);
    lv_style_set_pad_all(&noBorderStyle, 0);
    lv_style_set_pad_top(&noBorderStyle, 0);
    // lv_style_set_pad_inner(&noBorderStyle, 2);
    lv_style_set_border_width(&noBorderStyle, 0);
    lv_style_set_bg_opa(&noBorderStyle, 0);

    lv_style_init(&smallInfoLabelStyle);
    lv_style_set_text_font(&smallInfoLabelStyle, &FiraSansMedium10);
    lv_style_set_text_color(&smallInfoLabelStyle, lv_color_white());

    lv_style_init(&statusChipStyle);
    lv_style_set_pad_all(&statusChipStyle, 2);
    lv_style_set_bg_color(&statusChipStyle, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_bg_opa(&statusChipStyle, LV_OPA_COVER);
    lv_style_set_text_font(&statusChipStyle, &FivePixel);
    lv_style_set_radius(&statusChipStyle, 2);
    lv_style_set_text_color(&statusChipStyle, lv_color_white());

    lv_style_init(&largeInfoLabelStyle);
    lv_style_set_text_font(&largeInfoLabelStyle, &FiraSansMedium13);
    lv_style_set_text_color(&largeInfoLabelStyle, lv_color_white());
    /*
        // fudge the fonts for slightly tighter lines
        ((lv_font_t *) &FiraSansMedium10)->line_height = 12;
        ((lv_font_t *) &FiraSansMedium13)->line_height = 13;
        ((lv_font_t *) &IBMPlexSansMedium13)->line_height = 12;
        */
  }
}
