#include "scr_system.h"
#include "screens.h"
#include "ui.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_private/esp_clk.h"

static const char *TAG = "scr_system";

#define SYSTEM_REFRESH_MS   1000

static lv_timer_t *s_refresh_timer = NULL;

/* Minimo de heap libre visto desde el arranque o desde el ultimo reset.
 * Lo llevamos nosotros porque esp_get_minimum_free_heap_size() no se
 * puede reiniciar. */
static uint32_t s_heap_min = UINT32_MAX;

/* Bytes -> "123.4 KB" (sin floats: lv_label_set_text_fmt no soporta %f) */
static void set_kb_label(lv_obj_t *label, uint32_t bytes)
{
    uint32_t tenths_kb = (bytes * 10U) / 1024U;
    lv_label_set_text_fmt(label, "%u.%u KB", (unsigned)(tenths_kb / 10), (unsigned)(tenths_kb % 10));
}

/* Datos que no cambian mientras corre el programa: se cargan una vez */
static void load_static_info(void)
{
    esp_chip_info_t info;
    esp_chip_info(&info);
    const char *model = (info.model == CHIP_ESP32S3) ? "ESP32-S3" : "ESP32";
    /* revision viene como MXX: 2 -> v0.2, 101 -> v1.1 */
    lv_label_set_text_fmt(ui_lblChipValue, "%s v%d.%d, %d nucleos",
                          model, info.revision / 100, info.revision % 100, info.cores);

    uint32_t flash_size = 0;
    if (esp_flash_get_size(NULL, &flash_size) == ESP_OK) {
        lv_label_set_text_fmt(ui_lblFlashValue, "%u MB", (unsigned)(flash_size / (1024U * 1024U)));
    }

    lv_label_set_text(ui_lblIdfValue, esp_get_idf_version());
}

/* Datos que cambian: frecuencia de CPU y heap */
static void refresh_dynamic_info(void)
{
    lv_label_set_text_fmt(ui_lblCpuValue, "%d MHz", esp_clk_cpu_freq() / 1000000);

    uint32_t heap_free = esp_get_free_heap_size();
    if (heap_free < s_heap_min) {
        s_heap_min = heap_free;
    }
    set_kb_label(ui_lblHeapValue, heap_free);
    set_kb_label(ui_lblHeapMinValue, s_heap_min);
}

void scr_system_reset_heap_min(void)
{
    s_heap_min = esp_get_free_heap_size();
    set_kb_label(ui_lblHeapMinValue, s_heap_min);
    ESP_LOGI(TAG, "heap min reset to %u bytes", (unsigned)s_heap_min);
}

static void on_reset_heap_clicked(lv_event_t *e)
{
    (void)e;
    scr_system_reset_heap_min();
}

static void on_refresh_timer(lv_timer_t *timer)
{
    (void)timer;
    refresh_dynamic_info();
}

void scr_system_prepare(void)
{
    load_static_info();

    s_refresh_timer = lv_timer_create(on_refresh_timer, SYSTEM_REFRESH_MS, NULL);
    lv_timer_pause(s_refresh_timer);

    lv_obj_add_event_cb(ui_btnResetHeapMin, on_reset_heap_clicked, LV_EVENT_CLICKED, NULL);
    ESP_LOGD(TAG, "prepare");
}

void scr_system_init(void)
{
    refresh_dynamic_info();
    lv_timer_resume(s_refresh_timer);
    ESP_LOGD(TAG, "init");
}

void scr_system_uninit(void)
{
    lv_timer_pause(s_refresh_timer);
    ESP_LOGD(TAG, "uninit");
}

void scr_system_step(void)
{
}
