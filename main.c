#include <stdlib.h>
#include <unistd.h>

#include "lvgl/lvgl.h"
#include "lv_drivers/win_drv.h"
#include "lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"
#include "lv_font.h"

#include <windows.h>

#include "styles.h"

static void hal_init(void);

static int tick_thread(void *data);

void init_main_screen() {
    lv_obj_t *screen = NULL;
    lv_obj_t *iconRow;

    screen = lv_cont_create(NULL, NULL);
    lv_cont_set_layout(screen, LV_LAYOUT_COLUMN_MID);
    lv_obj_add_style(screen, LV_OBJ_PART_MAIN, &noBorderStyle);
    lv_obj_set_style_local_bg_color(screen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_style_local_bg_opa(screen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);

    lv_obj_set_style_local_bg_grad_dir(screen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_obj_set_style_local_bg_color(screen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_style_local_bg_grad_color(screen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, COLOR_PULSATRIX_DARK_PURPLE);
    lv_obj_set_style_local_bg_main_stop(screen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 80);
    lv_obj_set_style_local_bg_grad_stop(screen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 220);

    // icon row
    iconRow = lv_cont_create(screen, NULL);
    lv_cont_set_layout(iconRow, LV_LAYOUT_ROW_MID);
    lv_cont_set_fit2(iconRow, LV_FIT_PARENT, LV_FIT_TIGHT);
    lv_obj_add_style(iconRow, LV_OBJ_PART_MAIN, &noBorderStyle);
    lv_obj_set_style_local_bg_color(iconRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x30, 0x30, 0x30));
    lv_obj_set_style_local_bg_opa(iconRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_obj_set_style_local_radius(iconRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);

    lv_obj_t *nameLabel;
    lv_obj_t *statusLabel;
    lv_obj_t *amperageLabel;
    lv_obj_t *maxAmperageLabel;
    lv_obj_t *powerLabel;
    lv_obj_t *maxPowerLabel;
    lv_obj_t *energyLabel;
    lv_obj_t *durationLabel;

    // info row
    lv_obj_t *page = lv_cont_create(screen, NULL);
    lv_cont_set_layout(page, LV_LAYOUT_COLUMN_LEFT);
    lv_cont_set_fit2(page, LV_FIT_PARENT, LV_FIT_TIGHT);
    lv_obj_add_style(page, LV_OBJ_PART_MAIN, &noBorderStyle);

#define MAKE_LABEL(name, parent, style, defaultText) \
  name = lv_label_create(parent, NULL);              \
  lv_obj_add_style(name, LV_OBJ_PART_MAIN, &(style));  \
  lv_label_set_text_static(name, defaultText);

    MAKE_LABEL(nameLabel, page, smallInfoLabelStyle, "Ladepunkt @ Demo");
    lv_obj_set_width_fit(nameLabel, lv_obj_get_width(page));
    // lv_label_set_long_mode(nameLabel, LV_LABEL_LONG_DOT);

    MAKE_LABEL(statusLabel, page, largeInfoLabelStyle, "Standby (A1)");

    lv_obj_t *row = lv_cont_create(page, NULL);
    lv_cont_set_layout(row, LV_LAYOUT_ROW_TOP);
    lv_cont_set_fit2(row, LV_FIT_PARENT, LV_FIT_TIGHT);
    lv_obj_add_style(row, LV_OBJ_PART_MAIN, &noBorderStyle);

    lv_obj_t *col1 = lv_cont_create(row, NULL);
    lv_cont_set_layout(col1, LV_LAYOUT_COLUMN_LEFT);
    lv_cont_set_fit(col1, LV_FIT_TIGHT);
    lv_obj_add_style(col1, LV_OBJ_PART_MAIN, &noBorderStyle);

    // create small gap column
    lv_obj_t *col2 = lv_cont_create(row, NULL);
    lv_cont_set_layout(col2, LV_LAYOUT_OFF);
    lv_obj_add_style(col2, LV_OBJ_PART_MAIN, &noBorderStyle);
    lv_obj_set_size(col2, 10, 4);

    // create column for MAX label
    col2 = lv_cont_create(row, NULL);
    lv_cont_set_layout(col2, LV_LAYOUT_OFF);
    lv_cont_set_fit(col2, LV_FIT_TIGHT);
    lv_obj_add_style(col2, LV_OBJ_PART_MAIN, &noBorderStyle);
    lv_obj_set_style_local_bg_opa(col2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_obj_set_style_local_bg_color(col2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x30, 0x30, 0x30));
    lv_obj_set_style_local_radius(col2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 1);

    // "MAX" label - FIXME: replace with image
    lv_obj_t *maxLabel = lv_label_create(col2, NULL);
    lv_obj_set_style_local_text_font(maxLabel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_8);
    lv_obj_set_style_local_text_color(maxLabel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_align(maxLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 3);
    lv_label_set_text_static(maxLabel, "M");
    lv_obj_t *ref = maxLabel;
    maxLabel = lv_label_create(col2, NULL);
    lv_obj_set_style_local_text_font(maxLabel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_8);
    lv_obj_set_style_local_text_color(maxLabel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_align(maxLabel, ref, LV_ALIGN_OUT_BOTTOM_LEFT, 1, 1);
    lv_label_set_text_static(maxLabel, "A");
    ref = maxLabel;
    maxLabel = lv_label_create(col2, NULL);
    lv_obj_set_style_local_text_font(maxLabel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_8);
    lv_obj_set_style_local_text_color(maxLabel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_align(maxLabel, ref, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 1);
    lv_label_set_text_static(maxLabel, "X");

    lv_obj_t *col3 = lv_cont_create(row, NULL);
    lv_cont_set_layout(col3, LV_LAYOUT_COLUMN_LEFT);
    lv_cont_set_fit(col3, LV_FIT_TIGHT);
    lv_obj_add_style(col3, LV_OBJ_PART_MAIN, &noBorderStyle);

    MAKE_LABEL(amperageLabel, col1, largeInfoLabelStyle, "I: 0.0 A, 0 ph ");
    MAKE_LABEL(maxAmperageLabel, col3, largeInfoLabelStyle, "0.0 A");

    MAKE_LABEL(powerLabel, col1, largeInfoLabelStyle, "P: 0.0 kW");
    MAKE_LABEL(maxPowerLabel, col3, largeInfoLabelStyle, "0.0 kW");

    MAKE_LABEL(energyLabel, page, largeInfoLabelStyle, "E: 0.00 kWh");
    MAKE_LABEL(durationLabel, page, smallInfoLabelStyle, "uptime: 0d 00:12:34s");

    lv_obj_set_style_local_text_color(statusLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, COLOR_LIGHT_GREEN);

    lv_obj_set_style_local_text_font(durationLabel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &RobotoMonoMedium10);
    lv_label_set_long_mode(durationLabel, LV_LABEL_LONG_SROLL_CIRC);

    lv_obj_t *icon = lv_label_create(iconRow, NULL);
    lv_label_set_text_static(icon, "R");
    lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
    lv_obj_add_state(icon, LV_STATE_CHECKED);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow, NULL);
    lv_label_set_text_static(icon, "T");
    lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
    lv_obj_add_state(icon, LV_STATE_CHECKED);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow, NULL);
    lv_label_set_text_static(icon, "Q");
    lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
    lv_obj_add_state(icon, LV_STATE_CHECKED);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow, NULL);
    lv_label_set_text_static(icon, "V");
    lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
    lv_obj_add_state(icon, LV_STATE_CHECKED);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow, NULL);
    lv_label_set_text_static(icon, "]");
    lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
    lv_obj_set_parent(icon, iconRow);

    icon = lv_label_create(iconRow, NULL);
    lv_label_set_text_static(icon, "U");
    lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
    lv_obj_set_parent(icon, iconRow);

    lv_obj_align(page, iconRow, LV_ALIGN_OUT_TOP_MID, 0, 0);
    lv_obj_set_hidden(page, false);

    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, false);
}

void init_root() {
    // fudge the fonts for slightly tighter lines
    RobotoMedium10.line_height = 12;
    RobotoMedium14.line_height = 16;
    RobotoMonoMedium10.line_height = 12;

    // Theme
    lv_theme_t *th = lv_theme_material_init(LV_THEME_DEFAULT_COLOR_PRIMARY, LV_THEME_DEFAULT_COLOR_SECONDARY,
                                            LV_THEME_DEFAULT_FLAG,
                                            &RobotoMedium14, &RobotoMedium14, &RobotoMedium14, &RobotoMedium14);
    lv_theme_set_act(th);

    initStyles();

    // make dummy screen
    lv_obj_t *dummyScreen = lv_cont_create(NULL, NULL);
    lv_obj_add_style(dummyScreen, LV_OBJ_PART_MAIN, &noBorderStyle);
    lv_obj_set_style_local_bg_grad_dir(dummyScreen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_obj_set_style_local_bg_color(dummyScreen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_style_local_bg_grad_color(dummyScreen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, COLOR_PULSATRIX_DARK_PURPLE);
    lv_obj_set_style_local_bg_main_stop(dummyScreen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 80);
    lv_obj_set_style_local_bg_grad_stop(dummyScreen, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 220);

    lv_obj_t *label = lv_label_create(dummyScreen, NULL);
    lv_label_set_text(label, "Hello!");

    lv_scr_load(dummyScreen);
}

#if WIN32

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif // WIN32
{
    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL for LittlevGL*/
    hal_init();

    /*Check the themes too*/
    lv_disp_set_default(lv_windows_disp);

    /*Run the v7 demo*/
    // lv_demo_widgets();
    init_root();
    init_main_screen();

#if WIN32
    while (!lv_win_exit_flag) {
#else
        while(1) {
#endif // WIN32
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(1000);       /*Just to let the system breath*/
    }
    return 0;
}

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics library
 */
static void hal_init(void) {
#if !WIN32
    /* Add a display
     * Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    monitor_init();
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.disp_flush = monitor_flush;
    disp_drv.disp_fill = monitor_fill;
    disp_drv.disp_map = monitor_map;
    lv_disp_drv_register(&disp_drv);

    /* Add the mouse (or touchpad) as input device
     * Use the 'mouse' driver which reads the PC's mouse*/
    mouse_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);          /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read = mouse_read;         /*This function will be called periodically (by the library) to get the mouse position and state*/
    lv_indev_drv_register(&indev_drv);

    /* Tick init.
     * You have to call 'lv_tick_handler()' in every milliseconds
     * Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", NULL);
#else
    /* This sets up some timers to handle everything. */
    windrv_init();
#endif
}

#if !WIN32
/**
 * A task to measure the elapsed time for LittlevGL
 * @param data unused
 * @return never return
 */
static int tick_thread(void *data)
{
    while(1) {
        lv_tick_inc(1);
        SDL_Delay(1);   /*Sleep for 1 millisecond*/
    }

    return 0;
}
#endif
