#include "../ui.h"

lv_obj_t *ui_scrHome = NULL;
lv_obj_t *ui_lblHomeTitle = NULL;
lv_obj_t *ui_arcBattery = NULL;
lv_obj_t *ui_lblBatteryValue = NULL;
lv_obj_t *ui_lblBatteryCaption = NULL;
lv_obj_t *ui_lblBatteryVolt = NULL;
lv_obj_t *ui_pnlTemp = NULL;
lv_obj_t *ui_lblTempCaption = NULL;
lv_obj_t *ui_lblTempValue = NULL;
lv_obj_t *ui_pnlUptime = NULL;
lv_obj_t *ui_lblUptimeCaption = NULL;
lv_obj_t *ui_lblUptimeValue = NULL;

/* Panel con titulo chico arriba y valor grande abajo (temperatura y uptime) */
static lv_obj_t *create_value_panel(lv_obj_t *parent, lv_coord_t y, const char *caption,
                                    lv_obj_t **lbl_caption, lv_obj_t **lbl_value)
{
    lv_obj_t *pnl = lv_obj_create(parent);
    lv_obj_set_width(pnl, 150);
    lv_obj_set_height(pnl, 72);
    lv_obj_set_x(pnl, -12);
    lv_obj_set_y(pnl, y);
    lv_obj_set_align(pnl, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(pnl, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(pnl, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(pnl, lv_color_hex(UI_COLOR_PANEL), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(pnl, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(pnl, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(pnl, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    *lbl_caption = lv_label_create(pnl);
    lv_obj_set_align(*lbl_caption, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(*lbl_caption, caption);
    lv_obj_set_style_text_color(*lbl_caption, lv_color_hex(UI_COLOR_TEXT_DIM), LV_PART_MAIN | LV_STATE_DEFAULT);

    *lbl_value = lv_label_create(pnl);
    lv_obj_set_align(*lbl_value, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_set_style_text_font(*lbl_value, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    return pnl;
}

void ui_scrHome_screen_init(void)
{
    ui_scrHome = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_scrHome, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_scrHome, lv_color_hex(UI_COLOR_BG), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scrHome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblHomeTitle = lv_label_create(ui_scrHome);
    lv_obj_set_x(ui_lblHomeTitle, 12);
    lv_obj_set_y(ui_lblHomeTitle, 10);
    lv_obj_set_align(ui_lblHomeTitle, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(ui_lblHomeTitle, "S3 Monitor");
    lv_obj_set_style_text_color(ui_lblHomeTitle, lv_color_hex(UI_COLOR_ACCENT), LV_PART_MAIN | LV_STATE_DEFAULT);

    /* Arco de bateria: 270 grados con la abertura hacia abajo, sin perilla
     * y no clickeable (es solo un indicador). */
    ui_arcBattery = lv_arc_create(ui_scrHome);
    lv_obj_set_width(ui_arcBattery, 140);
    lv_obj_set_height(ui_arcBattery, 140);
    lv_obj_set_x(ui_arcBattery, 14);
    lv_obj_set_y(ui_arcBattery, 14);
    lv_obj_set_align(ui_arcBattery, LV_ALIGN_LEFT_MID);
    lv_arc_set_range(ui_arcBattery, 0, 100);
    lv_arc_set_value(ui_arcBattery, 0);
    lv_arc_set_bg_angles(ui_arcBattery, 135, 45);
    lv_obj_clear_flag(ui_arcBattery, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_remove_style(ui_arcBattery, NULL, LV_PART_KNOB);
    lv_obj_set_style_arc_width(ui_arcBattery, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_arcBattery, lv_color_hex(UI_COLOR_PANEL), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_arcBattery, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_arcBattery, lv_palette_main(LV_PALETTE_GREEN), LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_lblBatteryValue = lv_label_create(ui_arcBattery);
    lv_obj_set_y(ui_lblBatteryValue, -6);
    lv_obj_set_align(ui_lblBatteryValue, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblBatteryValue, "--%");
    lv_obj_set_style_text_font(ui_lblBatteryValue, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblBatteryCaption = lv_label_create(ui_arcBattery);
    lv_obj_set_y(ui_lblBatteryCaption, 20);
    lv_obj_set_align(ui_lblBatteryCaption, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblBatteryCaption, "Bateria");
    lv_obj_set_style_text_color(ui_lblBatteryCaption, lv_color_hex(UI_COLOR_TEXT_DIM), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblBatteryVolt = lv_label_create(ui_arcBattery);
    lv_obj_set_align(ui_lblBatteryVolt, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_lblBatteryVolt, "-.-- V");
    lv_obj_set_style_text_color(ui_lblBatteryVolt, lv_color_hex(UI_COLOR_TEXT_DIM), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pnlTemp = create_value_panel(ui_scrHome, 44, "Temperatura CPU", &ui_lblTempCaption, &ui_lblTempValue);
    lv_label_set_text(ui_lblTempValue, "--.- °C");

    ui_pnlUptime = create_value_panel(ui_scrHome, 128, "Tiempo activo", &ui_lblUptimeCaption, &ui_lblUptimeValue);
    lv_label_set_text(ui_lblUptimeValue, "00:00:00");
}
