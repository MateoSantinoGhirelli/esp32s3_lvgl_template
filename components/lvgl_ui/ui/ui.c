#include "ui.h"

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match the project settings"
#endif
#if LV_COLOR_16_SWAP != 0
    #error "LV_COLOR_16_SWAP should be 0 (the swap is done by the LCD driver)"
#endif

///////////////////// HELPERS ////////////////////

lv_obj_t *ui_create_screen(void)
{
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(scr, lv_color_hex(UI_COLOR_BG), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    return scr;
}

lv_obj_t *ui_create_title(lv_obj_t *parent, const char *text)
{
    lv_obj_t *lbl = lv_label_create(parent);
    lv_obj_set_x(lbl, 12);
    lv_obj_set_y(lbl, 10);
    lv_obj_set_align(lbl, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(lbl, text);
    lv_obj_set_style_text_color(lbl, lv_color_hex(UI_COLOR_ACCENT), LV_PART_MAIN | LV_STATE_DEFAULT);
    return lbl;
}

lv_obj_t *ui_create_panel(lv_obj_t *parent, lv_coord_t w, lv_coord_t h)
{
    lv_obj_t *pnl = lv_obj_create(parent);
    lv_obj_set_width(pnl, w);
    lv_obj_set_height(pnl, h);
    lv_obj_clear_flag(pnl, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(pnl, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(pnl, lv_color_hex(UI_COLOR_PANEL), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(pnl, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(pnl, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(pnl, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    return pnl;
}

lv_obj_t *ui_create_button(lv_obj_t *parent, const char *text, lv_coord_t w, lv_coord_t x, lv_coord_t y)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_width(btn, w);
    lv_obj_set_height(btn, 34);
    lv_obj_set_x(btn, x);
    lv_obj_set_y(btn, y);
    lv_obj_set_align(btn, LV_ALIGN_TOP_RIGHT);

    lv_obj_t *lbl = lv_label_create(btn);
    lv_obj_set_align(lbl, LV_ALIGN_CENTER);
    lv_label_set_text(lbl, text);
    return btn;
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE),
                                              lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    ui_scrHome_screen_init();
    ui_scrSystem_screen_init();
    ui_scrSettings_screen_init();

    lv_disp_load_scr(ui_scrHome);
}
