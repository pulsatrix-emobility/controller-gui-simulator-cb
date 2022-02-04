#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

#include "lv_demos/src/lv_demo_widgets/lv_demo_widgets.h"
#include "lv_drivers/win32drv/win32drv.h"
#include "lvgl/lvgl.h"
#include "styles.h"

static void hal_init(void);

static int tick_thread(void *data);

static void opa_anim(void *bg, int32_t v) {
  lv_obj_t **objs = bg;
  lv_obj_set_style_bg_opa(objs[0], v, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(objs[1], v, LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(objs[1], v, LV_STATE_DEFAULT);
}

lv_obj_t *makeStatusRow(lv_obj_t *screen) {  // status row
  lv_obj_t *statusRow = lv_obj_create(screen);
  lv_obj_set_layout(statusRow, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(statusRow, LV_FLEX_FLOW_ROW);
  lv_obj_set_style_bg_color(statusRow, lv_palette_main(LV_PALETTE_CYAN), LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(statusRow, 0, LV_STATE_DEFAULT);

  lv_obj_set_style_border_color(statusRow, lv_color_make(0x3d, 0x6b, 0xdc), LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(statusRow, 1, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(statusRow, LV_BORDER_SIDE_BOTTOM, LV_STATE_DEFAULT);

  lv_obj_t *heartBeat = lv_obj_create(statusRow);
  lv_obj_set_size(heartBeat, 7, 7);
  lv_obj_add_style(heartBeat, &statusChipStyle, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(heartBeat, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(heartBeat, lv_palette_main(LV_PALETTE_GREEN), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(heartBeat, 3, LV_STATE_DEFAULT);

  lv_obj_t *timeLabel = lv_label_create(statusRow);
  lv_obj_add_style(timeLabel, &statusChipStyle, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(timeLabel, LV_OPA_TRANSP, LV_STATE_DEFAULT);
  lv_label_set_text(timeLabel, "123d 14:23:22");
  lv_obj_set_flex_grow(timeLabel, 1);

  lv_obj_t *ethLabel = lv_label_create(statusRow);
  lv_obj_add_style(ethLabel, &statusChipStyle, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ethLabel, lv_palette_main(LV_PALETTE_ORANGE), LV_STATE_DEFAULT);
  lv_label_set_text(ethLabel, "ETH");

  lv_obj_t *ipLabel = lv_label_create(statusRow);
  lv_obj_add_style(ipLabel, &statusChipStyle, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ipLabel, lv_palette_main(LV_PALETTE_ORANGE), LV_STATE_DEFAULT);
  lv_label_set_text(ipLabel, "IP");

  lv_obj_t *mqttLabel = lv_label_create(statusRow);
  lv_obj_add_style(mqttLabel, &statusChipStyle, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(mqttLabel, lv_palette_main(LV_PALETTE_GREEN), LV_STATE_DEFAULT);
  lv_label_set_text(mqttLabel, "MQTT");

  return statusRow;
}

void init_main_screen() {
  lv_obj_t *root = lv_obj_create(NULL);
  lv_obj_set_pos(root, 0, 0);
  lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);

  lv_obj_t *screen = lv_obj_create(root);
  lv_obj_set_pos(screen, 0, 0);
  lv_obj_set_size(screen, LV_HOR_RES, LV_VER_RES);
  lv_obj_add_style(screen, &noBorderStyle, LV_STATE_DEFAULT);
  lv_obj_set_layout(screen, LV_LAYOUT_FLEX);
  lv_obj_set_style_bg_color(screen, lv_palette_main(LV_PALETTE_GREEN), LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_STATE_DEFAULT);

  // lv_obj_set_style_bg_grad_dir(screen, LV_GRAD_DIR_VER);
  lv_obj_set_style_bg_color(screen, lv_color_black(), LV_STATE_DEFAULT);

  lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(screen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
  // lv_obj_set_style_bg_grad_color(screen, COLOR_PULSATRIX_DARK_PURPLE);
    // lv_obj_set_style_bg_main_stop(screen, 80);
    // lv_obj_set_style_bg_grad_stop(screen, 220);
    lv_obj_t *statusRow = makeStatusRow(screen);

    if(0) {
    // icon row
    lv_obj_t *iconRow = lv_obj_create(screen);
    lv_obj_set_layout(iconRow, LV_LAYOUT_FLEX);
    lv_obj_add_style(iconRow, &noBorderStyle, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(iconRow, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(iconRow, lv_color_make(0x3d, 0x6b, 0xdc), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(iconRow, 1, LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(iconRow, LV_BORDER_SIDE_TOP, LV_STATE_DEFAULT);

    lv_obj_t *icon = lv_label_create(iconRow);
    lv_label_set_text_static(icon, "A");
    lv_obj_add_style(icon, &mainIconStyle, LV_STATE_DEFAULT);
    lv_obj_add_state(icon, LV_STATE_CHECKED);
    lv_obj_add_state(icon, LV_STATE_FOCUSED);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow);
    lv_label_set_text_static(icon, "B");
    lv_obj_add_style(icon, &mainIconStyle, LV_STATE_DEFAULT);
    lv_obj_add_state(icon, LV_STATE_CHECKED);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow);
    lv_label_set_text_static(icon, "C");
    lv_obj_add_style(icon, &mainIconStyle, LV_STATE_DEFAULT);
    lv_obj_add_state(icon, LV_STATE_CHECKED);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow);
    lv_label_set_text_static(icon, "D");
    lv_obj_add_style(icon, &mainIconStyle, LV_STATE_DEFAULT);
    lv_obj_add_state(icon, LV_STATE_CHECKED);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow);
    lv_label_set_text_static(icon, "E");
    lv_obj_add_style(icon, &mainIconStyle, LV_STATE_DEFAULT);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow);
    lv_label_set_text_static(icon, "F");
    lv_obj_add_style(icon, &mainIconStyle, LV_STATE_DEFAULT);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow);
    lv_label_set_text_static(icon, "G");
    lv_obj_add_style(icon, &mainIconStyle, LV_STATE_DEFAULT);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow);
    lv_label_set_text_static(icon, "K");
    lv_obj_add_style(icon, &mainIconStyle, LV_STATE_DEFAULT);
    lv_obj_set_parent(icon, iconRow);

    lv_obj_align(iconRow, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_t *nameLabel;
    lv_obj_t *statusLabel;
    lv_obj_t *amperageLabel;
    lv_obj_t *maxAmperageLabel;
    lv_obj_t *powerLabel;
    lv_obj_t *maxPowerLabel;
    lv_obj_t *energyLabel;
    lv_obj_t *durationLabel;

    // the page
    lv_obj_t *page = lv_obj_create(screen);
    lv_obj_align(page, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_coord_t w = lv_obj_get_width(screen);
    lv_coord_t h = lv_obj_get_height(screen) - (lv_obj_get_height(statusRow) + lv_obj_get_height(iconRow));
    lv_obj_set_size(page, w, h);

    lv_obj_set_style_pad_top(page, 2, LV_STATE_DEFAULT);
    lv_obj_set_layout(page, LV_LAYOUT_FLEX);
    lv_obj_add_style(page, &noBorderStyle, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(page, lv_color_make(0x03, 0x1d, 0x78), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(page, LV_OPA_COVER, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(page, 0, LV_STATE_DEFAULT);

    lv_obj_t *row = lv_obj_create(page);
    lv_obj_set_layout(row, LV_LAYOUT_FLEX);
    lv_obj_add_style(row, &noBorderStyle, LV_STATE_DEFAULT);

#define MAKE_LABEL(name, parent, style, defaultText)  \
  name = lv_label_create(parent);                     \
  lv_obj_add_style(name, &(style), LV_STATE_DEFAULT); \
  lv_label_set_text_static(name, defaultText);

    lv_obj_t *symbolLabel;
    MAKE_LABEL(symbolLabel, row, smallInfoLabelStyle, "J");
    lv_obj_set_style_text_font(symbolLabel, &icons, LV_STATE_DEFAULT);

    MAKE_LABEL(nameLabel, row, smallInfoLabelStyle, "Ladepunkt 1 @ Demo");
    lv_obj_align(nameLabel, LV_ALIGN_OUT_RIGHT_MID, 4, -2);
    lv_obj_set_style_pad_ver(nameLabel, 2, LV_STATE_DEFAULT);

    MAKE_LABEL(statusLabel, page, largeInfoLabelStyle, "Standby (A1)");

    row = lv_obj_create(page);
    lv_obj_set_layout(row, LV_LAYOUT_FLEX);
    lv_obj_add_style(row, &noBorderStyle, LV_STATE_DEFAULT);

    // amperage
    lv_obj_t *amperageUnit;
    MAKE_LABEL(amperageUnit, row, largeInfoLabelStyle, "I  ");
    lv_obj_set_style_text_font(amperageUnit, &IBMPlexSansMedium13, LV_STATE_DEFAULT);
    lv_obj_align(amperageUnit, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    MAKE_LABEL(amperageLabel, row, largeInfoLabelStyle, "0.0 A, 0 ph ");
    lv_obj_align(amperageLabel, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 0);

    MAKE_LABEL(maxAmperageLabel, row, smallInfoLabelStyle, "0.0 A max");
    lv_obj_align(maxAmperageLabel, LV_ALIGN_BOTTOM_RIGHT, -2, -1);

    row = lv_obj_create(page);
    lv_obj_set_layout(row, LV_LAYOUT_FLEX);
    lv_obj_add_style(row, &noBorderStyle, LV_STATE_DEFAULT);

    // power
    lv_obj_t *powerUnit;
    MAKE_LABEL(powerUnit, row, largeInfoLabelStyle, "P ");
    lv_obj_set_style_text_font(powerUnit, &IBMPlexSansMedium13, LV_STATE_DEFAULT);
    lv_obj_align(powerUnit, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    MAKE_LABEL(powerLabel, row, largeInfoLabelStyle, "0.0 kW");
    lv_obj_align(powerLabel, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, 0);

    MAKE_LABEL(maxPowerLabel, row, smallInfoLabelStyle, "0.0 kW max");
    lv_obj_align(maxPowerLabel, LV_ALIGN_BOTTOM_RIGHT, -2, -1);

    row = lv_obj_create(page);
    lv_obj_set_layout(row, LV_LAYOUT_FLEX);
    lv_obj_add_style(row, &noBorderStyle, LV_STATE_DEFAULT);

    lv_obj_t *energyUnit;
    MAKE_LABEL(energyUnit, row, largeInfoLabelStyle, "E ");
    lv_obj_set_style_text_font(energyUnit, &IBMPlexSansMedium13, LV_STATE_DEFAULT);
    lv_obj_align(energyUnit, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    MAKE_LABEL(energyLabel, row, largeInfoLabelStyle, "0.00 kWh");
    lv_obj_align(energyLabel, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, 0);

    MAKE_LABEL(durationLabel, page, smallInfoLabelStyle, "charging: 0d 00:12:34s");

    lv_obj_set_style_text_color(statusLabel, COLOR_LIGHT_GREEN, LV_STATE_DEFAULT);

    lv_obj_set_style_pad_ver(durationLabel, 2, LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(durationLabel, &FiraSansMedium10, LV_STATE_DEFAULT);
    lv_label_set_long_mode(durationLabel, LV_LABEL_LONG_SCROLL_CIRCULAR);
  }

  // lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, false);
  lv_scr_load(root);

  /* Create a full-screen background */
//  static lv_style_t style_modal;
//  lv_style_init(&style_modal);
//  lv_style_set_bg_color(&style_modal, lv_color_black());
//  lv_style_set_bg_opa(&style_modal, LV_OPA_TRANSP);
//
//  /* Create a base object for the modal background */
//  lv_obj_t *background = lv_obj_create(root);
//  lv_obj_add_style(background, &style_modal, LV_STATE_DEFAULT);
//  lv_obj_set_pos(background, 0, 0);
//  lv_obj_set_size(background, LV_HOR_RES, LV_VER_RES);
  // lv_obj_set_style_bg_color(background,LV_COLOR_WHITE);
  // lv_obj_set_style_bg_opa(background, LV_OPA_90);

  /* Create the message box as a child of the modal background */
  /* Halo-Effekt
  lv_obj_t *mbox = lv_label_create(background);
  lv_obj_set_style_text_color(mbox,LV_COLOR_WHITE);
  lv_obj_set_style_bg_color(mbox,lv_color_make(20,20,20));
  lv_obj_set_style_bg_opa(mbox,LV_OPA_COVER);
  lv_obj_set_style_pad_hor(mbox,20);
  lv_obj_set_style_pad_ver(mbox,10);
  lv_obj_set_style_radius(mbox,10);
  lv_obj_set_style_shadow_color(mbox, LV_COLOR_WHITE);
  lv_obj_set_style_shadow_width(mbox, 30);
  lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(mbox, "Hello");
  */

//  lv_obj_t *mbox = lv_label_create(background);
//  lv_obj_set_style_text_color(mbox, lv_color_white(), LV_STATE_DEFAULT);
//  lv_obj_set_style_bg_color(mbox, lv_color_black(), LV_STATE_DEFAULT);
//  lv_obj_set_style_bg_opa(mbox, LV_OPA_60, LV_STATE_DEFAULT);
//  lv_obj_set_style_pad_hor(mbox, 20, LV_STATE_DEFAULT);
//  lv_obj_set_style_pad_ver(mbox, 10, LV_STATE_DEFAULT);
//  lv_obj_set_style_radius(mbox, 10, LV_STATE_DEFAULT);
//  lv_label_set_text(mbox, "Main screen");
//  lv_obj_align(mbox, LV_ALIGN_CENTER, 0, 0);
//
//  /*
//  lv_obj_set_style_pad_all(mbox, LV_MSGBOX_PART_BG, 0);
//  lv_obj_set_style_pad_all(mbox, 0);
//  lv_obj_set_style_pad_all(mbox, 0);
//  lv_obj_set_style_pad_inner(mbox, 0);
//  lv_obj_set_style_pad_inner(mbox, 0);
//  lv_obj_set_style_pad_inner(mbox, LV_MSGBOX_PART_BG, 0);
//  lv_msgbox_set_text(mbox, "Hello!");
//  lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);
//   */
//
//  /* Fade the message box in with an animation */
//  static lv_obj_t *objs[2];
//  objs[0] = background;
//  objs[1] = mbox;
//
//  lv_anim_t a;
//  lv_anim_init(&a);
//  lv_anim_set_var(&a, objs);
//  lv_anim_set_time(&a, 1500);
//  lv_anim_set_playback_delay(&a, 500);
//  lv_anim_set_values(&a, LV_OPA_60, LV_OPA_0);
//  lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) opa_anim);
//  lv_anim_start(&a);

  // lv_label_set_text(info, in_msg_info);
  // lv_obj_align(info, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 5, -5);
}

void init_root() {
  initStyles();

  // make dummy screen
  lv_obj_t *dummyScreen = lv_obj_create(NULL);

  lv_obj_t *label = lv_label_create(dummyScreen);
  lv_label_set_text(label, "Hello!");

  lv_scr_load(dummyScreen);
}

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);
static int tick_thread(void *data);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow) {
  /*Initialize LittlevGL*/
  lv_init();

  /*Initialize the HAL for LittlevGL*/
  lv_win32_init(hInstance, SW_SHOWNORMAL, 160, 128, NULL);

  /*Output prompt information to the console, you can also use printf() to print directly*/
  LV_LOG_USER("LVGL initialization completed!");

  /*Run the demo*/
  init_root();
  init_main_screen();

  while (!lv_win32_quit_signal) {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_task_handler();
    usleep(10000); /*Just to let the system breath*/
  }

  LV_LOG_USER("exiting!");

  return 0;
}
