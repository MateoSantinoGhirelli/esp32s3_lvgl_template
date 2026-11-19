#ifndef _UI_SCRSYSTEM_H
#define _UI_SCRSYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// SCREEN: ui_scrSystem
void ui_scrSystem_screen_init(void);
extern lv_obj_t *ui_scrSystem;
extern lv_obj_t *ui_lblSystemTitle;
extern lv_obj_t *ui_pnlSysInfo;
extern lv_obj_t *ui_lblChipValue;
extern lv_obj_t *ui_lblCpuValue;
extern lv_obj_t *ui_lblFlashValue;
extern lv_obj_t *ui_lblIdfValue;
extern lv_obj_t *ui_lblHeapValue;
extern lv_obj_t *ui_lblHeapMinValue;
extern lv_obj_t *ui_btnResetHeapMin;

#ifdef __cplusplus
}
#endif

#endif
