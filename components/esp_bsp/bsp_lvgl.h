#ifndef __BSP_LVGL_H__
#define __BSP_LVGL_H__

#include "esp_err.h"
#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t bsp_lvgl_init(void);
lv_disp_t *bsp_lvgl_get_display(void);
lv_indev_t *bsp_lvgl_get_touch_indev(void);

/**
 * Fade de la retroiluminacion de `from` a `to` (0-100 %) en `time_ms`.
 * Usa lv_anim, asi que hay que llamarla desde contexto LVGL
 * (callback, timer LVGL o con el lock tomado).
 */
void bsp_lvgl_backlight_fade(uint8_t from, uint8_t to, uint32_t time_ms);

/* Optional: register LVGL FatFS driver (call after bsp_sdcard_init) */
void bsp_lv_fs_fatfs_init(void);

#ifdef __cplusplus
}
#endif

#endif
