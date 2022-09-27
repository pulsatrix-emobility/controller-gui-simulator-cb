#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

#include "lv_drivers/win_drv.h"
#include "lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"
#include "lv_font.h"
#include "lvgl/lvgl.h"
#include "styles.h"

static void hal_init(void);

static int tick_thread(void *data);

static void opa_anim(void *bg, lv_anim_value_t v) {
  lv_obj_t *mbox = bg;
  lv_obj_set_style_local_bg_opa(mbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, v);
  lv_obj_set_style_local_text_opa(mbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, v);
}

lv_obj_t *makeStatusChip(lv_obj_t *parent, char *text, lv_color_t color) {
  lv_obj_t *chip = lv_label_create(parent, NULL);
  lv_obj_add_style(chip, LV_OBJ_PART_MAIN, &statusChipStyle);
  lv_obj_set_style_local_bg_color(chip, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color);
  lv_label_set_text_static(chip, text);
  return chip;
}

lv_obj_t *makeStatusRow(lv_obj_t *parent) {  // status row
  lv_obj_t *statusRow = lv_cont_create(parent, NULL);
  lv_obj_add_style(statusRow, LV_OBJ_PART_MAIN, &noBorderStyle);
  lv_obj_align(statusRow, parent, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_cont_set_layout(statusRow, LV_LAYOUT_OFF);
  lv_obj_set_style_local_pad_bottom(statusRow, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 3);

  lv_obj_set_style_local_border_color(statusRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x3d, 0x6b, 0xdc));
  lv_obj_set_style_local_border_width(statusRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 1);
  lv_obj_set_style_local_border_side(statusRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_BORDER_SIDE_BOTTOM);

  lv_obj_t *statusRowLeft = lv_cont_create(statusRow, NULL);
  lv_cont_set_layout(statusRowLeft, LV_LAYOUT_ROW_MID);
  lv_cont_set_fit2(statusRowLeft, LV_FIT_TIGHT, LV_FIT_TIGHT);
  lv_obj_add_style(statusRowLeft, LV_OBJ_PART_MAIN, &noBorderStyle);

  lv_obj_t *heartBeat = lv_obj_create(statusRowLeft, NULL);
  lv_obj_set_size(heartBeat, 7, 7);
  lv_obj_add_style(heartBeat, LV_OBJ_PART_MAIN, &statusChipStyle);
  lv_obj_set_style_local_bg_color(heartBeat, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GREEN);
  lv_obj_set_style_local_radius(heartBeat, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 3);

  lv_obj_t *timeLabel = lv_label_create(statusRowLeft, NULL);
  lv_obj_add_style(timeLabel, LV_OBJ_PART_MAIN, &statusChipStyle);
  lv_obj_set_style_local_bg_opa(timeLabel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
  lv_label_set_text(timeLabel, "123d 14:23:22");

  lv_obj_t *statusRowRight = lv_cont_create(statusRow, NULL);
  lv_cont_set_layout(statusRowRight, LV_LAYOUT_ROW_MID);
  lv_cont_set_fit2(statusRowRight, LV_FIT_TIGHT, LV_FIT_TIGHT);
  lv_obj_add_style(statusRowRight, LV_OBJ_PART_MAIN, &noBorderStyle);

  makeStatusChip(statusRowRight, "ETH", LV_COLOR_GREEN);
  makeStatusChip(statusRowRight, "IP", LV_COLOR_ORANGE);
  makeStatusChip(statusRowRight, "MQTT", LV_COLOR_GRAY);

  // yeah, this is weird, but the only way to make this work in layout=off.
  lv_obj_align(statusRowLeft, statusRow, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_obj_align(statusRowRight, statusRow, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
  lv_cont_set_fit2(statusRow, LV_FIT_PARENT, LV_FIT_TIGHT);
  lv_obj_align(statusRowLeft, statusRow, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_obj_align(statusRowRight, statusRow, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

  return statusRow;
}

void createMainPage(lv_obj_t *page) {
  lv_obj_t *nameLabel;
  lv_obj_t *statusLabel;
  lv_obj_t *amperageLabel;
  lv_obj_t *maxAmperageLabel;
  lv_obj_t *powerLabel;
  lv_obj_t *maxPowerLabel;
  lv_obj_t *energyLabel;
  lv_obj_t *durationLabel;

  lv_obj_t *row = lv_cont_create(page, NULL);
  lv_cont_set_layout(row, LV_LAYOUT_OFF);
  lv_cont_set_fit2(row, LV_FIT_PARENT, LV_FIT_TIGHT);
  lv_obj_add_style(row, LV_OBJ_PART_MAIN, &noBorderStyle);

#define MAKE_LABEL(name, parent, style, defaultText)  \
  name = lv_label_create(parent, NULL);               \
  lv_obj_add_style(name, LV_OBJ_PART_MAIN, &(style)); \
  lv_label_set_text_static(name, defaultText);

  lv_obj_t *symbolLabel;
  MAKE_LABEL(symbolLabel, row, smallInfoLabelStyle, "J");
  lv_obj_set_style_local_text_font(symbolLabel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &icons);

  MAKE_LABEL(nameLabel, row, smallInfoLabelStyle, "Ladepunkt 1 @ Demo");
  lv_obj_set_width_fit(nameLabel, lv_obj_get_width(page));
  lv_obj_align(nameLabel, symbolLabel, LV_ALIGN_OUT_RIGHT_MID, 4, -2);
  lv_obj_set_style_local_pad_ver(nameLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 2);

  MAKE_LABEL(statusLabel, page, largeInfoLabelStyle, "Standby (A1)");

  row = lv_cont_create(page, NULL);
  lv_cont_set_layout(row, LV_LAYOUT_OFF);
  lv_cont_set_fit2(row, LV_FIT_PARENT, LV_FIT_TIGHT);
  lv_obj_add_style(row, LV_OBJ_PART_MAIN, &noBorderStyle);

  // amperage
  lv_obj_t *amperageUnit;
  MAKE_LABEL(amperageUnit, row, largeInfoLabelStyle, "I  ");
  lv_obj_set_style_local_text_font(amperageUnit, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &IBMPlexSansMedium13);
  lv_obj_align(amperageUnit, row, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

  MAKE_LABEL(amperageLabel, row, largeInfoLabelStyle, "0.0 A, 0 ph ");
  lv_obj_align(amperageLabel, amperageUnit, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, 0);

  MAKE_LABEL(maxAmperageLabel, row, smallInfoLabelStyle, "0.0 A max");
  lv_obj_align(maxAmperageLabel, row, LV_ALIGN_IN_BOTTOM_RIGHT, -2, -1);
  lv_obj_set_auto_realign(maxAmperageLabel, true);

  row = lv_cont_create(page, NULL);
  lv_cont_set_layout(row, LV_LAYOUT_OFF);
  lv_cont_set_fit2(row, LV_FIT_PARENT, LV_FIT_TIGHT);
  lv_obj_add_style(row, LV_OBJ_PART_MAIN, &noBorderStyle);

  // power
  lv_obj_t *powerUnit;
  MAKE_LABEL(powerUnit, row, largeInfoLabelStyle, "P ");
  lv_obj_set_style_local_text_font(powerUnit, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &IBMPlexSansMedium13);
  lv_obj_align(powerUnit, row, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

  MAKE_LABEL(powerLabel, row, largeInfoLabelStyle, "0.0 kW");
  lv_obj_align(powerLabel, powerUnit, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, 0);

  MAKE_LABEL(maxPowerLabel, row, smallInfoLabelStyle, "0.0 kW max");
  lv_obj_align(maxPowerLabel, row, LV_ALIGN_IN_BOTTOM_RIGHT, -2, -1);

  row = lv_cont_create(page, NULL);
  lv_cont_set_layout(row, LV_LAYOUT_OFF);
  lv_cont_set_fit2(row, LV_FIT_PARENT, LV_FIT_TIGHT);
  lv_obj_add_style(row, LV_OBJ_PART_MAIN, &noBorderStyle);

  lv_obj_t *energyUnit;
  MAKE_LABEL(energyUnit, row, largeInfoLabelStyle, "E ");
  lv_obj_set_style_local_text_font(energyUnit, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &IBMPlexSansMedium13);
  lv_obj_align(energyUnit, row, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

  MAKE_LABEL(energyLabel, row, largeInfoLabelStyle, "0.00 kWh");
  lv_obj_align(energyLabel, energyUnit, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, 0);

  MAKE_LABEL(durationLabel, page, smallInfoLabelStyle, "charging: 0d 00:12:34s");

  lv_obj_set_style_local_text_color(statusLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, COLOR_LIGHT_GREEN);

  lv_obj_set_style_local_pad_ver(durationLabel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2);
  lv_obj_set_style_local_text_font(durationLabel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &FiraSansMedium10);
  lv_label_set_long_mode(durationLabel, LV_LABEL_LONG_SROLL_CIRC);
}

#define MAKE_INFO(name, label, defaultText)                              \
  lv_obj_t *name##Label = lv_label_create(col1, NULL);                   \
  lv_obj_add_style(name##Label, LV_OBJ_PART_MAIN, &smallInfoLabelStyle); \
  lv_label_set_text_static(name##Label, label);                          \
                                                                         \
  name = lv_label_create(col2, NULL);                                    \
  lv_label_set_align(name, LV_LABEL_ALIGN_RIGHT);                        \
  lv_obj_add_style(name, LV_OBJ_PART_MAIN, &smallInfoLabelStyle);        \
  lv_label_set_text_static(name, defaultText);

void makeLeaderSection(lv_obj_t *page) {
  lv_obj_t *leaderView = lv_cont_create(page, NULL);
  lv_obj_add_style(leaderView, LV_CONT_PART_MAIN, &noBorderStyle);
  lv_obj_set_style_local_border_width(leaderView, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 1);
  lv_obj_set_style_local_border_side(leaderView, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_BORDER_SIDE_TOP);
  lv_obj_set_style_local_border_color(leaderView, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);

  lv_cont_set_fit2(leaderView, LV_FIT_PARENT, LV_FIT_TIGHT);

  lv_obj_t *col1 = lv_cont_create(leaderView, NULL);
  lv_cont_set_layout(col1, LV_LAYOUT_COLUMN_LEFT);
  lv_cont_set_fit(col1, LV_FIT_PARENT);
  lv_obj_add_style(col1, LV_OBJ_PART_MAIN, &noBorderStyle);
  lv_obj_set_style_local_pad_ver(col1, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 4);

  lv_obj_t *col2 = lv_cont_create(leaderView, NULL);
  lv_cont_set_layout(col2, LV_LAYOUT_COLUMN_RIGHT);
  lv_cont_set_fit(col2, LV_FIT_PARENT);
  lv_obj_add_style(col2, LV_OBJ_PART_MAIN, &noBorderStyle);
  lv_obj_set_style_local_pad_ver(col2, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 4);

  lv_obj_t *gridLabel;
  MAKE_INFO(gridLabel, "Grid", "123/212/123 A");

  lv_obj_t *chargingLabel;
  MAKE_INFO(chargingLabel, "Charging", "999 kW, 123/212/123 A");

  lv_obj_t *budgetLabel;
  MAKE_INFO(budgetLabel, "Budget", "999 kW, 123/212/123 A");

  lv_cont_set_fit2(leaderView, LV_FIT_PARENT, LV_FIT_TIGHT);

  lv_obj_t *allocFactorsTable = lv_table_create(page, NULL);
  lv_obj_add_style(allocFactorsTable, LV_OBJ_PART_MAIN, &noBorderStyle);
  lv_obj_add_style(allocFactorsTable, LV_TABLE_PART_BG, &noBorderStyle);
  lv_obj_add_style(allocFactorsTable, LV_TABLE_PART_CELL1, &noBorderStyle);
  lv_obj_set_style_local_text_font(allocFactorsTable, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, &FiraSansMedium10);
  lv_obj_set_style_local_text_color(allocFactorsTable, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, LV_COLOR_WHITE);

  lv_obj_add_style(allocFactorsTable, LV_TABLE_PART_CELL2, &noBorderStyle);
  lv_obj_set_style_local_text_font(allocFactorsTable, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, &FiraSansMedium10);
  lv_obj_set_style_local_text_color(allocFactorsTable, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, LV_COLOR_BLUE);
  lv_obj_set_style_local_bg_color(allocFactorsTable, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  lv_obj_set_style_local_bg_opa(allocFactorsTable, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, LV_OPA_COVER);

  lv_table_set_row_cnt(allocFactorsTable, 3);
  lv_table_set_col_cnt(allocFactorsTable, 3);

  lv_table_set_col_width(allocFactorsTable, 0, 40);
  lv_table_set_col_width(allocFactorsTable, 1, 80);
  lv_table_set_col_width(allocFactorsTable, 2, 40);

  lv_table_set_cell_type(allocFactorsTable, 0, 0, 2);
  lv_table_set_cell_type(allocFactorsTable, 0, 1, 2);
  lv_table_set_cell_type(allocFactorsTable, 0, 2, 2);

  for (int r = 0; r < 3; r++)
    for (int c = 0; c < 3; c++)
      lv_table_set_cell_align(allocFactorsTable, r, c, LV_LABEL_ALIGN_RIGHT);

  lv_table_set_cell_value(allocFactorsTable, 0, 0, "Priority");
  lv_table_set_cell_value(allocFactorsTable, 0, 1, "Request (A)");
  lv_table_set_cell_value(allocFactorsTable, 0, 2, "Factor");
  lv_table_set_cell_value(allocFactorsTable, 1, 0, "5");
  lv_table_set_cell_value(allocFactorsTable, 1, 1, "123/212/123");
  lv_table_set_cell_value(allocFactorsTable, 1, 2, "1.0");
  lv_table_set_cell_value(allocFactorsTable, 2, 0, "5");
  lv_table_set_cell_value(allocFactorsTable, 2, 1, "123/212/123");
  lv_table_set_cell_value(allocFactorsTable, 2, 2, "1.0");
}

void makeFollowerSection(lv_obj_t *page) {
  lv_obj_t *followerView = lv_cont_create(page, NULL);
  lv_obj_add_style(followerView, LV_CONT_PART_MAIN, &noBorderStyle);
  lv_obj_set_style_local_border_width(followerView, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 1);
  lv_obj_set_style_local_border_side(followerView, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_BORDER_SIDE_TOP);
  lv_obj_set_style_local_border_color(followerView, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);

  lv_cont_set_layout(followerView, LV_LAYOUT_OFF);
  lv_cont_set_fit(followerView, LV_FIT_NONE);
  lv_obj_set_width(followerView, lv_obj_get_width(page));
  lv_obj_set_height(followerView, lv_obj_get_height(page));

  lv_obj_t *col1 = lv_cont_create(followerView, NULL);
  lv_cont_set_layout(col1, LV_LAYOUT_COLUMN_LEFT);
  lv_cont_set_fit(col1, LV_FIT_PARENT);
  lv_obj_add_style(col1, LV_OBJ_PART_MAIN, &noBorderStyle);
  lv_obj_set_style_local_pad_ver(col1, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 4);

  lv_obj_t *col2 = lv_cont_create(followerView, NULL);
  lv_cont_set_layout(col2, LV_LAYOUT_COLUMN_RIGHT);
  lv_cont_set_fit(col2, LV_FIT_PARENT);
  lv_obj_add_style(col2, LV_OBJ_PART_MAIN, &noBorderStyle);
  lv_obj_set_style_local_pad_ver(col2, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 4);

  lv_obj_t *phaseLabel;
  MAKE_INFO(phaseLabel, "Phase", "INACTIVE");

  lv_obj_t *ampHistoryLabel;
  MAKE_INFO(ampHistoryLabel, "Amperge max, avg", "11.1, 14.2 A");

  lv_obj_t *estimatedMaxLabel;
  MAKE_INFO(estimatedMaxLabel, "Estimated charger max.", "123 A");

  lv_obj_t *requestLabel;
  MAKE_INFO(requestLabel, "Request", "123 A on L1 L2 L3");

  lv_obj_t *allocationLabel;
  MAKE_INFO(allocationLabel, "Allocation", "123 A");
}

void createTeamPage(lv_obj_t *page) {
  lv_obj_t *teamStateLabel = lv_label_create(page, NULL);
  lv_label_set_align(teamStateLabel, LV_LABEL_ALIGN_LEFT);
  lv_obj_add_style(teamStateLabel, LV_OBJ_PART_MAIN, &smallInfoLabelStyle);
  lv_label_set_text_static(teamStateLabel, "Leader (group size 999 of 999)");

  // makeLeaderSection(page);
  makeFollowerSection(page);
}

void init_main_screen() {
  lv_obj_t *screen = lv_obj_create(NULL, NULL);
  lv_obj_reset_style_list(screen, LV_OBJ_PART_MAIN);
  lv_obj_set_pos(screen, 0, 0);
  lv_obj_set_size(screen, LV_HOR_RES, LV_VER_RES);

  lv_obj_t *main = lv_cont_create(screen, NULL);
  lv_obj_set_pos(main, 0, 0);
  lv_obj_set_size(main, LV_HOR_RES, LV_VER_RES);
  lv_obj_set_style_local_pad_inner(main, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 0);
  lv_obj_add_style(main, LV_OBJ_PART_MAIN, &noBorderStyle);
  lv_obj_set_style_local_bg_opa(main, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
  lv_obj_set_style_local_bg_color(main, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);

  lv_obj_t *statusRow = makeStatusRow(main);

  // icon row
  lv_obj_t *iconRow = lv_cont_create(main, NULL);
  lv_cont_set_layout(iconRow, LV_LAYOUT_ROW_MID);
  lv_cont_set_fit2(iconRow, LV_FIT_PARENT, LV_FIT_TIGHT);
  lv_obj_add_style(iconRow, LV_OBJ_PART_MAIN, &noBorderStyle);
  lv_obj_set_style_local_pad_inner(iconRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2);
  lv_obj_set_style_local_border_color(iconRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x3d, 0x6b, 0xdc));
  lv_obj_set_style_local_border_width(iconRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 1);
  lv_obj_set_style_local_border_side(iconRow, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_BORDER_SIDE_TOP);

  lv_obj_t *icon = lv_label_create(iconRow, NULL);
  lv_label_set_text_static(icon, "A");
  lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
  lv_obj_add_state(icon, LV_STATE_CHECKED);
  lv_obj_add_state(icon, LV_STATE_FOCUSED);
  lv_obj_set_parent(icon, iconRow);

  icon = lv_label_create(iconRow, NULL);
  lv_label_set_text_static(icon, "B");
  lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
  lv_obj_add_state(icon, LV_STATE_CHECKED);
  lv_obj_set_parent(icon, iconRow);

  icon = lv_label_create(iconRow, NULL);
  lv_label_set_text_static(icon, "C");
  lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
  lv_obj_add_state(icon, LV_STATE_CHECKED);
  lv_obj_set_parent(icon, iconRow);

  icon = lv_label_create(iconRow, NULL);
  lv_label_set_text_static(icon, "D");
  lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
  lv_obj_add_state(icon, LV_STATE_CHECKED);
  lv_obj_set_parent(icon, iconRow);

  icon = lv_label_create(iconRow, NULL);
  lv_label_set_text_static(icon, "E");
  lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
  lv_obj_set_parent(icon, iconRow);

  icon = lv_label_create(iconRow, NULL);
  lv_label_set_text_static(icon, "F");
  lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
  lv_obj_set_parent(icon, iconRow);

  icon = lv_label_create(iconRow, NULL);
  lv_label_set_text_static(icon, "G");
  lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
  lv_obj_set_parent(icon, iconRow);

  icon = lv_label_create(iconRow, NULL);
  lv_label_set_text_static(icon, "K");
  lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &mainIconStyle);
  lv_obj_set_parent(icon, iconRow);

  lv_obj_align(iconRow, main, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

  // the page
  lv_obj_t *page = lv_cont_create(main, NULL);
  lv_obj_align(page, statusRow, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  lv_coord_t w = lv_obj_get_width(main);
  lv_coord_t h = lv_obj_get_height(main) - (lv_obj_get_height(statusRow) + lv_obj_get_height(iconRow));
  lv_obj_set_size(page, w, h);
  printf("%d - (%d + %d) = %d", lv_obj_get_height(main), lv_obj_get_height(statusRow), lv_obj_get_height(iconRow), h);
  printf("page size %d %d", lv_obj_get_width_margin(page), lv_obj_get_height_margin(page));

  lv_obj_set_style_local_pad_top(page, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2);
  lv_cont_set_layout(page, LV_LAYOUT_COLUMN_LEFT);
  lv_cont_set_fit2(page, LV_FIT_PARENT, LV_FIT_NONE);
  lv_obj_add_style(page, LV_OBJ_PART_MAIN, &noBorderStyle);
  lv_obj_set_style_local_bg_color(page, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x03, 0x1d, 0x78));
  lv_obj_set_style_local_bg_opa(page, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);

  // createMainPage(page);
  createTeamPage(page);

  lv_scr_load(screen);

  /* Create a base object for the modal background */
  lv_obj_t *background = lv_obj_create(screen, NULL);
  lv_obj_reset_style_list(background, LV_OBJ_PART_MAIN);
  lv_obj_set_pos(background, 0, 0);
  lv_obj_set_style_local_bg_color(background, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
  lv_obj_set_style_local_bg_opa(background, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_50);
  lv_obj_set_size(background, LV_HOR_RES, LV_VER_RES);

  lv_obj_t *mbox = lv_label_create(background, NULL);
  lv_obj_set_style_local_text_color(mbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  lv_obj_set_style_local_bg_color(mbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
  lv_obj_set_style_local_bg_opa(mbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_60);
  lv_obj_set_style_local_pad_hor(mbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 20);
  lv_obj_set_style_local_pad_ver(mbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 10);
  lv_obj_set_style_local_radius(mbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 10);
  lv_label_set_text(mbox, "Home");
  lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);

  /* Fade the message box in with an animation */
  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, mbox);
  lv_anim_set_time(&a, 300);
  lv_anim_set_delay(&a, 700);
  lv_anim_set_values(&a, LV_OPA_60, LV_OPA_0);
  lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) opa_anim);
  lv_anim_start(&a);

  lv_obj_t *errorModal = lv_cont_create(background, NULL);
  lv_cont_set_layout(errorModal, LV_LAYOUT_CENTER);
  lv_obj_set_style_local_bg_color(errorModal, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
  lv_obj_set_style_local_pad_hor(errorModal, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 10);
  lv_obj_set_style_local_pad_ver(errorModal, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 10);
  lv_obj_set_size(errorModal, lv_obj_get_width(background) - 20, lv_obj_get_height(background) - 20);
  lv_obj_align(errorModal, NULL, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *title = lv_label_create(errorModal, NULL);
  lv_obj_set_style_local_text_color(title, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  lv_label_set_text_static(title, "Oooopsie!");
  lv_obj_set_style_local_text_font(title, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &FiraSansMedium13);

  lv_obj_t *body = lv_label_create(errorModal, NULL);
  // lv_obj_set_style_local_margin_hor(body, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 20);
  lv_obj_set_style_local_text_color(body, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  lv_label_set_long_mode(body, LV_LABEL_LONG_BREAK);
  lv_label_set_text_static(body, "Some really bad shit happened. You will certainly not like this!");
  lv_obj_set_style_local_text_font(body, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &FiraSansMedium10);
  lv_obj_set_width(body, lv_obj_get_width(errorModal)-40);
}

void init_root() {
  // Theme
  lv_theme_t *th = lv_theme_template_init(LV_THEME_DEFAULT_COLOR_PRIMARY, LV_THEME_DEFAULT_COLOR_SECONDARY, LV_THEME_DEFAULT_FLAG,
                                          &FiraSansMedium13, &FiraSansMedium13, &FiraSansMedium13, &FiraSansMedium13);
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
int main(int argc, char **argv)
#endif  // WIN32
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
  while (1) {
#endif  // WIN32
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_task_handler();
    usleep(1000); /*Just to let the system breath*/
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
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.disp_flush = monitor_flush;
  disp_drv.disp_fill = monitor_fill;
  disp_drv.disp_map = monitor_map;
  lv_disp_drv_register(&disp_drv);

  /* Add the mouse (or touchpad) as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
  mouse_init();
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv); /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read = mouse_read; /*This function will be called periodically (by the library) to get the mouse position and state*/
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
static int tick_thread(void *data) {
  while (1) {
    lv_tick_inc(1);
    SDL_Delay(1); /*Sleep for 1 millisecond*/
  }

  return 0;
}
#endif
