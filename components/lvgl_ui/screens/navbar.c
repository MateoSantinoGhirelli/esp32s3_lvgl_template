#include "navbar.h"
#include "ui.h"
#include "esp_log.h"

static const char *TAG = "navbar";

/* Mismo orden que ui_screens_t */
static const char *s_btn_texts[SCREEN_MAX] = {
    [SCREEN_HOME]     = LV_SYMBOL_HOME " Inicio",
    [SCREEN_SYSTEM]   = LV_SYMBOL_LIST " Sistema",
    [SCREEN_SETTINGS] = LV_SYMBOL_SETTINGS " Ajustes",
};

static lv_obj_t *s_bar = NULL;
static lv_obj_t *s_btns[SCREEN_MAX];

static void on_nav_btn_clicked(lv_event_t *e)
{
    ui_screens_t target = (ui_screens_t)(uintptr_t)lv_event_get_user_data(e);
    ui_screens_navigate(target);
}

void navbar_create(void)
{
    s_bar = lv_obj_create(lv_layer_top());
    lv_obj_set_size(s_bar, LV_PCT(100), UI_NAVBAR_HEIGHT);
    lv_obj_align(s_bar, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_clear_flag(s_bar, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(s_bar, 0, 0);
    lv_obj_set_style_border_width(s_bar, 0, 0);
    lv_obj_set_style_bg_color(s_bar, lv_color_hex(UI_COLOR_PANEL), 0);
    lv_obj_set_style_pad_all(s_bar, 4, 0);
    lv_obj_set_flex_flow(s_bar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(s_bar, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    for (int i = 0; i < SCREEN_MAX; i++) {
        lv_obj_t *btn = lv_btn_create(s_bar);
        lv_obj_set_size(btn, 98, UI_NAVBAR_HEIGHT - 8);
        lv_obj_set_style_shadow_width(btn, 0, 0);
        /* Inactivo: transparente con texto gris. Activo (CHECKED): color de acento */
        lv_obj_set_style_bg_opa(btn, LV_OPA_TRANSP, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(btn, lv_color_hex(UI_COLOR_TEXT_DIM), LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(btn, lv_color_hex(UI_COLOR_ACCENT), LV_STATE_CHECKED);
        lv_obj_set_style_text_color(btn, lv_color_hex(UI_COLOR_BG), LV_STATE_CHECKED);

        lv_obj_t *lbl = lv_label_create(btn);
        lv_label_set_text(lbl, s_btn_texts[i]);
        lv_obj_center(lbl);

        lv_obj_add_event_cb(btn, on_nav_btn_clicked, LV_EVENT_CLICKED, (void *)(uintptr_t)i);
        s_btns[i] = btn;
    }
    ESP_LOGD(TAG, "created");
}

void navbar_set_active(ui_screens_t screen)
{
    for (int i = 0; i < SCREEN_MAX; i++) {
        if (i == (int)screen) {
            lv_obj_add_state(s_btns[i], LV_STATE_CHECKED);
        } else {
            lv_obj_clear_state(s_btns[i], LV_STATE_CHECKED);
        }
    }
}
