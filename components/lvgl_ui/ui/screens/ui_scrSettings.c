#include "../ui.h"

lv_obj_t *ui_scrSettings = NULL;
lv_obj_t *ui_lblSettingsTitle = NULL;
lv_obj_t *ui_lblBrightnessCaption = NULL;
lv_obj_t *ui_sldBrightness = NULL;
lv_obj_t *ui_lblBrightnessValue = NULL;
lv_obj_t *ui_lblTimeoutCaption = NULL;
lv_obj_t *ui_swTimeout = NULL;
lv_obj_t *ui_lblBuildDate = NULL;
lv_obj_t *ui_btnRestore = NULL;

void ui_scrSettings_screen_init(void)
{
    ui_scrSettings = ui_create_screen();
    ui_lblSettingsTitle = ui_create_title(ui_scrSettings, "Ajustes");

    /* Fila de brillo: titulo - slider - porcentaje */
    ui_lblBrightnessCaption = lv_label_create(ui_scrSettings);
    lv_obj_set_x(ui_lblBrightnessCaption, 12);
    lv_obj_set_y(ui_lblBrightnessCaption, 48);
    lv_obj_set_align(ui_lblBrightnessCaption, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(ui_lblBrightnessCaption, "Brillo");

    ui_sldBrightness = lv_slider_create(ui_scrSettings);
    lv_obj_set_width(ui_sldBrightness, 160);
    lv_obj_set_height(ui_sldBrightness, 10);
    lv_obj_set_x(ui_sldBrightness, 84);
    lv_obj_set_y(ui_sldBrightness, 52);
    lv_obj_set_align(ui_sldBrightness, LV_ALIGN_TOP_LEFT);
    lv_slider_set_range(ui_sldBrightness, 5, 100);
    lv_slider_set_value(ui_sldBrightness, 100, LV_ANIM_OFF);

    ui_lblBrightnessValue = lv_label_create(ui_scrSettings);
    lv_obj_set_x(ui_lblBrightnessValue, -12);
    lv_obj_set_y(ui_lblBrightnessValue, 48);
    lv_obj_set_align(ui_lblBrightnessValue, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_lblBrightnessValue, "100%");

    /* Fila de timeout de pantalla */
    ui_lblTimeoutCaption = lv_label_create(ui_scrSettings);
    lv_obj_set_x(ui_lblTimeoutCaption, 12);
    lv_obj_set_y(ui_lblTimeoutCaption, 92);
    lv_obj_set_align(ui_lblTimeoutCaption, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(ui_lblTimeoutCaption, "Apagar pantalla a los 30 s");

    ui_swTimeout = lv_switch_create(ui_scrSettings);
    lv_obj_set_width(ui_swTimeout, 50);
    lv_obj_set_height(ui_swTimeout, 26);
    lv_obj_set_x(ui_swTimeout, -12);
    lv_obj_set_y(ui_swTimeout, 88);
    lv_obj_set_align(ui_swTimeout, LV_ALIGN_TOP_RIGHT);

    ui_lblBuildDate = lv_label_create(ui_scrSettings);
    lv_obj_set_x(ui_lblBuildDate, 12);
    lv_obj_set_y(ui_lblBuildDate, 130);
    lv_obj_set_align(ui_lblBuildDate, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(ui_lblBuildDate, "Compilado: -");
    lv_obj_set_style_text_color(ui_lblBuildDate, lv_color_hex(UI_COLOR_TEXT_DIM), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btnRestore = ui_create_button(ui_scrSettings, LV_SYMBOL_REFRESH "  Restaurar", 160, -10, 158);
}
