#include "scr_settings.h"
#include "screens.h"
#include "ui.h"
#include "bsp_display.h"
#include "screens_timeout.h"
#include "esp_log.h"

static const char *TAG = "scr_settings";

#define SCREEN_OFF_TIMEOUT_MS   30000

/* ------------------------------------------------------------------ */
/* Brillo                                                              */
/* ------------------------------------------------------------------ */

static void apply_brightness(int32_t percent)
{
    bsp_display_set_brightness((uint8_t)percent);
    lv_label_set_text_fmt(ui_lblBrightnessValue, "%d%%", (int)percent);
}

/* Se dispara mientras se arrastra el slider: el brillo cambia en vivo */
static void on_brightness_changed(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    apply_brightness(lv_slider_get_value(slider));
}

/* ------------------------------------------------------------------ */
/* Timeout de pantalla                                                 */
/* ------------------------------------------------------------------ */

static void apply_timeout(bool enabled)
{
    disp_timeout_set_off_ms(enabled ? SCREEN_OFF_TIMEOUT_MS : TIMEOUT_NEVER);
    ESP_LOGI(TAG, "screen timeout %s", enabled ? "on (30 s)" : "off");
}

static void on_timeout_switch_changed(lv_event_t *e)
{
    lv_obj_t *sw = lv_event_get_target(e);
    apply_timeout(lv_obj_has_state(sw, LV_STATE_CHECKED));
}

/* ------------------------------------------------------------------ */

void scr_settings_prepare(void)
{
    lv_obj_add_event_cb(ui_sldBrightness, on_brightness_changed, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_swTimeout, on_timeout_switch_changed, LV_EVENT_VALUE_CHANGED, NULL);

    /* __DATE__ y __TIME__ los pone el compilador al compilar este archivo */
    lv_label_set_text(ui_lblBuildDate, "Compilado: " __DATE__ " " __TIME__);
    ESP_LOGD(TAG, "prepare");
}

void scr_settings_init(void)
{
    /* El slider refleja el brillo real al entrar */
    int32_t current = bsp_display_get_brightness();
    lv_slider_set_value(ui_sldBrightness, current, LV_ANIM_OFF);
    lv_label_set_text_fmt(ui_lblBrightnessValue, "%d%%", (int)current);
    ESP_LOGD(TAG, "init");
}

void scr_settings_uninit(void)
{
    ESP_LOGD(TAG, "uninit");
}

void scr_settings_step(void)
{
}
