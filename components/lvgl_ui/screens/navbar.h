#ifndef __NAVBAR_H__
#define __NAVBAR_H__

#include "screens.h"

/**
 * Barra de navegacion inferior persistente.
 *
 * Se crea UNA sola vez sobre lv_layer_top(), que se dibuja encima de
 * cualquier pantalla, asi no hay que duplicarla en cada screen (un objeto
 * LVGL solo puede tener un padre). Por eso no esta en ui/: SquareLine no
 * genera objetos en el layer top.
 */
void navbar_create(void);

/** Resalta el boton de la pantalla activa. Lo llama ui_screens_step(). */
void navbar_set_active(ui_screens_t screen);

#endif
