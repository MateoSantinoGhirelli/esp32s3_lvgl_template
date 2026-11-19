#include "scr_settings.h"
#include "screens.h"
#include "ui.h"
#include "bsp_display.h"
#include "screens_timeout.h"
#include "esp_log.h"

static const char *TAG = "scr_settings";

#define SCREEN_OFF_TIMEOUT_MS   30000

/* Valores por defecto (los mismos con los que arranca la placa) */
#define DEFAULT_BRIGHTNESS      100
#define DEFAULT_TIMEOUT_ON      false

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
/* Restaurar valores por defecto                                       */
/* ------------------------------------------------------------------ */

void scr_settings_restore_defaults(void)
{
    /* lv_slider_set_value y lv_obj_*_state no disparan VALUE_CHANGED,
     * por eso se aplican los valores a mano ademas de mover los widgets. */
    lv_slider_set_value(ui_sldBrightness, DEFAULT_BRIGHTNESS, LV_ANIM_ON);
    apply_brightness(DEFAULT_BRIGHTNESS);

    if (DEFAULT_TIMEOUT_ON) {
        lv_obj_add_state(ui_swTimeout, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(ui_swTimeout, LV_STATE_CHECKED);
    }
    apply_timeout(DEFAULT_TIMEOUT_ON);
    ESP_LOGI(TAG, "defaults restored");
}

static void on_restore_clicked(lv_event_t *e)
{
    (void)e;
    scr_settings_restore_defaults();
}

/* ------------------------------------------------------------------ */

void scr_settings_prepare(void)
{
    lv_obj_add_event_cb(ui_sldBrightness, on_brightness_changed, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_swTimeout, on_timeout_switch_changed, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_btnRestore, on_restore_clicked, LV_EVENT_CLICKED, NULL);

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
