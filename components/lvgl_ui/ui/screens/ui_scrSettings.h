#ifndef _UI_SCRSETTINGS_H
#define _UI_SCRSETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// SCREEN: ui_scrSettings
void ui_scrSettings_screen_init(void);
extern lv_obj_t *ui_scrSettings;
extern lv_obj_t *ui_lblSettingsTitle;
extern lv_obj_t *ui_lblBrightnessCaption;
extern lv_obj_t *ui_sldBrightness;
extern lv_obj_t *ui_lblBrightnessValue;
extern lv_obj_t *ui_lblTimeoutCaption;
extern lv_obj_t *ui_swTimeout;
extern lv_obj_t *ui_lblBuildDate;
extern lv_obj_t *ui_btnRestore;

#ifdef __cplusplus
}
#endif

#endif
