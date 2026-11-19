#ifndef _UI_SCRHOME_H
#define _UI_SCRHOME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// SCREEN: ui_scrHome
void ui_scrHome_screen_init(void);
extern lv_obj_t *ui_scrHome;
extern lv_obj_t *ui_lblHomeTitle;
extern lv_obj_t *ui_pnlStatus;
extern lv_obj_t *ui_lblStatus;
extern lv_obj_t *ui_arcBattery;
extern lv_obj_t *ui_lblBatteryValue;
extern lv_obj_t *ui_lblBatteryCaption;
extern lv_obj_t *ui_pnlTemp;
extern lv_obj_t *ui_lblTempCaption;
extern lv_obj_t *ui_lblTempValue;
extern lv_obj_t *ui_pnlUptime;
extern lv_obj_t *ui_lblUptimeCaption;
extern lv_obj_t *ui_lblUptimeValue;
extern lv_obj_t *ui_btnRefresh;

#ifdef __cplusplus
}
#endif

#endif
