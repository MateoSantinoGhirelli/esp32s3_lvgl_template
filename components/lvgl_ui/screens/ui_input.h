#ifndef __UI_INPUT_H__
#define __UI_INPUT_H__

#include "lvgl.h"

/**
 * Boton fisico como dispositivo de entrada LVGL.
 *
 * Camino de un click en el boton BOOT:
 *   1. espressif/button detecta el click en SU tarea (esp_timer)
 *      -> on_button_click() solo encola UI_UPDATE_BUTTON_CLICK (sin lv_*).
 *   2. El timer LVGL vacia la cola y llama a ui_input_post_enter().
 *   3. El keypad LVGL (lv_indev) lee un ENTER en su proximo read_cb.
 *   4. El grupo (lv_group) entrega el ENTER al objeto enfocado, que recibe
 *      LV_EVENT_CLICKED igual que si se lo tocara con el dedo.
 *
 * Cada pantalla elige en su init() que boton recibe el ENTER, por eso la
 * accion depende de la pantalla activa.
 */

/** Crea el keypad + grupo y engancha el callback del boton. Contexto LVGL. */
void ui_input_init(void);

/** Objeto que recibe el ENTER del boton fisico en la pantalla actual. */
void ui_input_set_action(lv_obj_t *obj);

/** Marca un ENTER pendiente. Solo desde contexto LVGL (handler de la cola). */
void ui_input_post_enter(void);

#endif
