#ifndef _UI_H
#define _UI_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * UI de "S3 Monitor".
 *
 * Escrita a mano siguiendo la misma estructura que genera un export de
 * SquareLine Studio (ui.c/ui.h + un archivo por pantalla en screens/).
 * Solo construye los widgets: los eventos y la logica viven en
 * components/lvgl_ui/screens/scr_*.c, igual que con un export real.
 */

#include "lvgl.h"

#include "screens/ui_scrSplash.h"
#include "screens/ui_scrHome.h"

/* Colores de la app */
#define UI_COLOR_BG        0x101418
#define UI_COLOR_PANEL     0x1C222B
#define UI_COLOR_TEXT_DIM  0x8A94A6
#define UI_COLOR_ACCENT    0x4FC3F7

void ui_init(void);

#ifdef __cplusplus
}
#endif

#endif
