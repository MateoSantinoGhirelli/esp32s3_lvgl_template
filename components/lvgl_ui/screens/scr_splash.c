#include "scr_splash.h"
#include "screens.h"
#include "ui.h"
#include "bsp_lvgl.h"
#include "esp_log.h"

static const char *TAG = "scr_splash";

#define SPLASH_FADE_MS      800     /* fade-in de la retroiluminacion */
#define SPLASH_DOTS_MS      1600    /* ciclo completo "" -> "..." */

/* ------------------------------------------------------------------ */
/* Animacion de puntos suspensivos                                     */
/* ------------------------------------------------------------------ */

static int32_t s_dots_shown = -1;

/* lv_anim va de 0 a 4 en SPLASH_DOTS_MS y se repite; con value % 4
 * obtenemos 0, 1, 2, 3 puntos. Solo tocamos el label cuando cambia. */
static void dots_anim_cb(void *var, int32_t value)
{
    int32_t dots = value % 4;
    if (dots == s_dots_shown) {
        return;
    }
    s_dots_shown = dots;

    static const char *texts[] = { "Iniciando", "Iniciando.", "Iniciando..", "Iniciando..." };
    lv_label_set_text((lv_obj_t *)var, texts[dots]);
}

static void start_dots_anim(void)
{
    s_dots_shown = -1;

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, ui_lblLoading);
    lv_anim_set_exec_cb(&a, dots_anim_cb);
    lv_anim_set_values(&a, 0, 4);
    lv_anim_set_time(&a, SPLASH_DOTS_MS);
    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}

/* ------------------------------------------------------------------ */

void scr_splash_prepare(void)
{
    ESP_LOGD(TAG, "prepare");
}

void scr_splash_init(void)
{
    /* El splash es la primera pantalla: ui_init() la carga antes de que
     * prepare() registre callbacks, asi que sus eventos SCREEN_LOAD_* ya
     * pasaron. Por eso las animaciones arrancan aca, en init(). */
    bsp_lvgl_backlight_fade(0, 100, SPLASH_FADE_MS);
    start_dots_anim();
    ESP_LOGI(TAG, "splash started");
}

void scr_splash_uninit(void)
{
    lv_anim_del(ui_lblLoading, dots_anim_cb);
    ESP_LOGD(TAG, "uninit");
}

void scr_splash_step(void)
{
}
