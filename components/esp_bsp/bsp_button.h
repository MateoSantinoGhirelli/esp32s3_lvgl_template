#ifndef __BSP_BUTTON_H__
#define __BSP_BUTTON_H__

#include "esp_err.h"
#include "driver/gpio.h"
#include "iot_button.h"

/* Boton BOOT de la placa (activo en bajo, tiene pull-up) */
#define BSP_PIN_BUTTON            GPIO_NUM_0
#define BSP_BUTTON_ACTIVE_LEVEL   0

#ifdef __cplusplus
extern "C" {
#endif

/** Crea el boton con el componente espressif/button (antirrebote incluido). */
esp_err_t bsp_button_init(void);

/** Handle para registrar callbacks (iot_button_register_cb). NULL si no se inicializo. */
button_handle_t bsp_button_get_handle(void);

#ifdef __cplusplus
}
#endif

#endif
