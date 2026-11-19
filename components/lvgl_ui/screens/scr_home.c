#include "scr_home.h"
#include "screens.h"
#include "ui.h"
#include "bsp_battery.h"
#include "bsp_temp.h"
#include "esp_log.h"
#include "esp_timer.h"

static const char *TAG = "scr_home";

#define HOME_REFRESH_MS     1000

/* Bateria Li-ion: 3.30 V se toma como vacia y 4.20 V como llena.
 * Por debajo de 2.5 V asumimos que no hay bateria conectada. */
#define BATT_EMPTY_MV       3300
#define BATT_FULL_MV        4200
#define BATT_ABSENT_MV      2500

/* Umbrales de color del arco (en %) */
#define BATT_LOW_PCT        20
#define BATT_MID_PCT        50

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

/* Verde > 50 %, amarillo entre 20 y 50 %, rojo < 20 % */
static void set_battery_color(int pct)
{
    lv_palette_t palette = LV_PALETTE_GREEN;
    if (pct < BATT_LOW_PCT) {
        palette = LV_PALETTE_RED;
    } else if (pct < BATT_MID_PCT) {
        palette = LV_PALETTE_AMBER;
    }
    lv_obj_set_style_arc_color(ui_arcBattery, lv_palette_main(palette), LV_PART_INDICATOR | LV_STATE_DEFAULT);
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
    set_battery_color(pct);
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

static void refresh_uptime(void)
{
    /* esp_timer_get_time() devuelve microsegundos desde el arranque */
    uint32_t total_s = (uint32_t)(esp_timer_get_time() / 1000000ULL);
    uint32_t h = total_s / 3600;
    uint32_t m = (total_s / 60) % 60;
    uint32_t s = total_s % 60;
    lv_label_set_text_fmt(ui_lblUptimeValue, "%02u:%02u:%02u", (unsigned)h, (unsigned)m, (unsigned)s);
}

static void refresh_all(void)
{
    refresh_battery();
    refresh_temperature();
    refresh_uptime();
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
