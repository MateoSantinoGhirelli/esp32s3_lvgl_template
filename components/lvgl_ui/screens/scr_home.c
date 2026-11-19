#include "scr_home.h"
#include "screens.h"
#include "ui.h"
#include "bsp_battery.h"
#include "bsp_temp.h"
#include "esp_log.h"

static const char *TAG = "scr_home";

#define HOME_REFRESH_MS     1000

/* Bateria Li-ion: 3.30 V se toma como vacia y 4.20 V como llena.
 * Por debajo de 2.5 V asumimos que no hay bateria conectada. */
#define BATT_EMPTY_MV       3300
#define BATT_FULL_MV        4200
#define BATT_ABSENT_MV      2500

static lv_timer_t *s_refresh_timer = NULL;

/* ------------------------------------------------------------------ */
/* Lectura de datos y actualizacion de widgets                         */
/* ------------------------------------------------------------------ */

static int battery_percent_from_mv(int mv)
{
    if (mv <= BATT_EMPTY_MV) return 0;
    if (mv >= BATT_FULL_MV)  return 100;
    return (mv - BATT_EMPTY_MV) * 100 / (BATT_FULL_MV - BATT_EMPTY_MV);
}

static void refresh_battery(void)
{
    float volts = 0.0f;
    bsp_battery_get_voltage(&volts, NULL);
    int mv = (int)(volts * 1000.0f);

    lv_label_set_text_fmt(ui_lblBatteryVolt, "%d.%02d V", mv / 1000, (mv % 1000) / 10);

    if (mv < BATT_ABSENT_MV) {
        lv_arc_set_value(ui_arcBattery, 0);
        lv_label_set_text(ui_lblBatteryValue, "--%");
        return;
    }

    int pct = battery_percent_from_mv(mv);
    lv_arc_set_value(ui_arcBattery, pct);
    lv_label_set_text_fmt(ui_lblBatteryValue, "%d%%", pct);
}

static void refresh_temperature(void)
{
    float celsius = 0.0f;
    if (bsp_temp_get_celsius(&celsius) != ESP_OK) {
        lv_label_set_text(ui_lblTempValue, "--.- °C");
        return;
    }

    /* lv_label_set_text_fmt no soporta %f (LV_SPRINTF_USE_FLOAT = 0),
     * asi que se arma con enteros en decimas de grado. */
    int tenths = (int)(celsius * 10.0f + (celsius >= 0 ? 0.5f : -0.5f));
    const char *sign = (tenths < 0) ? "-" : "";
    if (tenths < 0) tenths = -tenths;
    lv_label_set_text_fmt(ui_lblTempValue, "%s%d.%d °C", sign, tenths / 10, tenths % 10);
}

static void refresh_all(void)
{
    refresh_battery();
    refresh_temperature();
}

static void on_refresh_timer(lv_timer_t *timer)
{
    (void)timer;
    refresh_all();
}

/* Al empezar a cargar Home ya mostramos datos reales (sin esperar al
 * primer tick de 1 s) y cuando termina de cargar arrancamos el timer. */
static void on_home_screen_event(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_SCREEN_LOAD_START) {
        refresh_all();
    } else if (code == LV_EVENT_SCREEN_LOADED) {
        lv_timer_reset(s_refresh_timer);
        lv_timer_resume(s_refresh_timer);
    }
}

/* ------------------------------------------------------------------ */

void scr_home_prepare(void)
{
    s_refresh_timer = lv_timer_create(on_refresh_timer, HOME_REFRESH_MS, NULL);
    lv_timer_pause(s_refresh_timer);

    lv_obj_add_event_cb(ui_scrHome, on_home_screen_event, LV_EVENT_SCREEN_LOAD_START, NULL);
    lv_obj_add_event_cb(ui_scrHome, on_home_screen_event, LV_EVENT_SCREEN_LOADED, NULL);
    ESP_LOGD(TAG, "prepare");
}

void scr_home_init(void)
{
    ESP_LOGD(TAG, "init");
}

void scr_home_uninit(void)
{
    /* Fuera de Home no hace falta leer nada */
    lv_timer_pause(s_refresh_timer);
    ESP_LOGD(TAG, "uninit");
}

void scr_home_step(void)
{
}
