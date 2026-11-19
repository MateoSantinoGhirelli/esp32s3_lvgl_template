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
 *
 * Las pantallas dejan libres los ultimos UI_NAVBAR_HEIGHT px: ahi va la
 * barra de navegacion, que se crea por codigo sobre lv_layer_top().
 */

#include "lvgl.h"

#include "screens/ui_scrHome.h"
#include "screens/ui_scrSystem.h"
#include "screens/ui_scrSettings.h"

/* Colores de la app */
#define UI_COLOR_BG        0x101418
#define UI_COLOR_PANEL     0x1C222B
#define UI_COLOR_TEXT_DIM  0x8A94A6
#define UI_COLOR_ACCENT    0x4FC3F7

#define UI_NAVBAR_HEIGHT   40

void ui_init(void);

/* Helpers compartidos por las pantallas (equivalen a ui_helpers de SquareLine) */
lv_obj_t *ui_create_screen(void);
lv_obj_t *ui_create_title(lv_obj_t *parent, const char *text);
lv_obj_t *ui_create_panel(lv_obj_t *parent, lv_coord_t w, lv_coord_t h);
lv_obj_t *ui_create_button(lv_obj_t *parent, const char *text, lv_coord_t w, lv_coord_t x, lv_coord_t y);

#ifdef __cplusplus
}
#endif

#endif
