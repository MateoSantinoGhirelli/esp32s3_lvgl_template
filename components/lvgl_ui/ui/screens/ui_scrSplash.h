#ifndef _UI_SCRSPLASH_H
#define _UI_SCRSPLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// SCREEN: ui_scrSplash
void ui_scrSplash_screen_init(void);
extern lv_obj_t *ui_scrSplash;
extern lv_obj_t *ui_lblAppName;
extern lv_obj_t *ui_lblLoading;
extern lv_obj_t *ui_lblTapHint;

#ifdef __cplusplus
}
#endif

#endif
