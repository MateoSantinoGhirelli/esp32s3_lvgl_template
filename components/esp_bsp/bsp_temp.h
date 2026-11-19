#ifndef __BSP_TEMP_H__
#define __BSP_TEMP_H__

#include "esp_err.h"

/* Rango de medicion del sensor interno. El driver elige la mejor escala
 * para este rango (de -10 a 80 °C cubre el funcionamiento normal del chip). */
#define BSP_TEMP_RANGE_MIN   (-10)
#define BSP_TEMP_RANGE_MAX   (80)

#ifdef __cplusplus
extern "C" {
#endif

/** Instala y habilita el sensor de temperatura interno del ESP32-S3. */
esp_err_t bsp_temp_init(void);

/** Lee la temperatura del chip en °C. Devuelve ESP_ERR_INVALID_STATE si no se inicializo. */
esp_err_t bsp_temp_get_celsius(float *celsius);

#ifdef __cplusplus
}
#endif

#endif
