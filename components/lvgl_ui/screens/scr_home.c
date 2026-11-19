#include "scr_home.h"
#include "screens.h"
#include "ui.h"
#include "ui_input.h"
#include "bsp_battery.h"
#include "bsp_temp.h"
#include "esp_log.h"
#include "esp_timer.h"

static const char *TAG = "scr_home";

#define HOME_REFRESH_MS     1000

/* Bateria Li-ion: 3.30 V vacia, 4.20 V llena, < 2.5 V = sin bateria */
#define BATT_EMPTY_MV       3300
#define BATT_FULL_MV        4200
#define BATT_ABSENT_MV      2500
#define BATT_LOW_PCT        20
#define BATT_MID_PCT        50

/* Estado general segun la temperatura del chip (°C) */
#define TEMP_ALERT_C        55
#define TEMP_CRITICAL_C     70

static lv_timer_t *s_refresh_timer = NULL;

/* ------------------------------------------------------------------ */
/* Lectura de datos                                                    */
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

    if (mv < BATT_ABSENT_MV) {
        lv_arc_set_value(ui_arcBattery, 0);
        lv_label_set_text(ui_lblBatteryValue, "--%");
        return;
    }

    int pct = battery_percent_from_mv(mv);
    lv_arc_set_value(ui_arcBattery, pct);
    lv_label_set_text_fmt(ui_lblBatteryValue, "%d%%", pct);

    lv_palette_t palette = LV_PALETTE_GREEN;
    if (pct < BATT_LOW_PCT) {
        palette = LV_PALETTE_RED;
    } else if (pct < BATT_MID_PCT) {
        palette = LV_PALETTE_AMBER;
    }
    lv_obj_set_style_arc_color(ui_arcBattery, lv_palette_main(palette), LV_PART_INDICATOR | LV_STATE_DEFAULT);
}

/* Icono, texto y color del indicador de estado de la esquina */
static void set_status(float celsius)
{
    const char *text = LV_SYMBOL_OK "  NORMAL";
    lv_palette_t palette = LV_PALETTE_GREEN;

    if (celsius >= TEMP_CRITICAL_C) {
        text = LV_SYMBOL_CLOSE "  CRITICO";
        palette = LV_PALETTE_RED;
    } else if (celsius >= TEMP_ALERT_C) {
        text = LV_SYMBOL_WARNING "  ALERTA";
        palette = LV_PALETTE_AMBER;
    }

    lv_label_set_text(ui_lblStatus, text);
    lv_obj_set_style_bg_color(ui_pnlStatus, lv_palette_main(palette), LV_PART_MAIN | LV_STATE_DEFAULT);
    /* El valor de temperatura toma el mismo color salvo en estado normal */
    lv_obj_set_style_text_color(ui_lblTempValue,
                                (palette == LV_PALETTE_GREEN) ? lv_color_white() : lv_palette_main(palette),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void refresh_temperature(void)
{
    float celsius = 0.0f;
    if (bsp_temp_get_celsius(&celsius) != ESP_OK) {
        lv_label_set_text(ui_lblTempValue, "--.- °C");
        return;
    }
    set_status(celsius);

    /* lv_label_set_text_fmt no soporta %f, se arma en decimas de grado */
    int tenths = (int)(celsius * 10.0f + (celsius >= 0 ? 0.5f : -0.5f));
    const char *sign = (tenths < 0) ? "-" : "";
    if (tenths < 0) tenths = -tenths;
    lv_label_set_text_fmt(ui_lblTempValue, "%s%d.%d °C", sign, tenths / 10, tenths % 10);
}

static void refresh_uptime(void)
{
    uint32_t total_s = (uint32_t)(esp_timer_get_time() / 1000000ULL);
    lv_label_set_text_fmt(ui_lblUptimeValue, "%02u:%02u:%02u",
                          (unsigned)(total_s / 3600), (unsigned)((total_s / 60) % 60), (unsigned)(total_s % 60));
}

/* ------------------------------------------------------------------ */

void scr_home_force_refresh(void)
{
    refresh_battery();
    refresh_temperature();
    refresh_uptime();
    /* Reinicia la cuenta para que el proximo tick sea 1 s despues */
    lv_timer_reset(s_refresh_timer);
}

static void on_refresh_timer(lv_timer_t *timer)
{
    (void)timer;
    scr_home_force_refresh();
}

static void on_refresh_clicked(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "manual refresh");
    scr_home_force_refresh();
}

void scr_home_prepare(void)
{
    s_refresh_timer = lv_timer_create(on_refresh_timer, HOME_REFRESH_MS, NULL);
    lv_timer_pause(s_refresh_timer);

    lv_obj_add_event_cb(ui_btnRefresh, on_refresh_clicked, LV_EVENT_CLICKED, NULL);
    ESP_LOGD(TAG, "prepare");
}

void scr_home_init(void)
{
    /* El boton fisico hace "click" sobre ui_btnRefresh en esta pantalla */
    ui_input_set_action(ui_btnRefresh);
    scr_home_force_refresh();
    lv_timer_resume(s_refresh_timer);
    ESP_LOGD(TAG, "init");
}

void scr_home_uninit(void)
{
    lv_timer_pause(s_refresh_timer);
    ESP_LOGD(TAG, "uninit");
}

void scr_home_step(void)
{
}
