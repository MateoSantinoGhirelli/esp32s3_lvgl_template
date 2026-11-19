#include "../ui.h"

lv_obj_t *ui_scrSplash = NULL;
lv_obj_t *ui_lblAppName = NULL;
lv_obj_t *ui_lblLoading = NULL;
lv_obj_t *ui_lblTapHint = NULL;

void ui_scrSplash_screen_init(void)
{
    ui_scrSplash = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_scrSplash, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_scrSplash, lv_color_hex(UI_COLOR_BG), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scrSplash, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblAppName = lv_label_create(ui_scrSplash);
    lv_obj_set_width(ui_lblAppName, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_lblAppName, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_lblAppName, 0);
    lv_obj_set_y(ui_lblAppName, -24);
    lv_obj_set_align(ui_lblAppName, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblAppName, "S3 Monitor");
    lv_obj_set_style_text_color(ui_lblAppName, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lblAppName, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);

    /* Ancho fijo y texto alineado a la izquierda: asi los puntos se agregan
     * sin que "Iniciando" se mueva de lugar. */
    ui_lblLoading = lv_label_create(ui_scrSplash);
    lv_obj_set_width(ui_lblLoading, 96);
    lv_obj_set_height(ui_lblLoading, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_lblLoading, 8);
    lv_obj_set_y(ui_lblLoading, 14);
    lv_obj_set_align(ui_lblLoading, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblLoading, "Iniciando");
    lv_obj_set_style_text_align(ui_lblLoading, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_lblLoading, lv_color_hex(UI_COLOR_ACCENT), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblTapHint = lv_label_create(ui_scrSplash);
    lv_obj_set_width(ui_lblTapHint, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_lblTapHint, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_lblTapHint, 0);
    lv_obj_set_y(ui_lblTapHint, -16);
    lv_obj_set_align(ui_lblTapHint, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_lblTapHint, "Toca la pantalla para continuar");
    lv_obj_set_style_text_color(ui_lblTapHint, lv_color_hex(UI_COLOR_TEXT_DIM), LV_PART_MAIN | LV_STATE_DEFAULT);
}
