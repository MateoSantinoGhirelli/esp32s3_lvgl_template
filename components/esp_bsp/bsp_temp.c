#include "bsp_temp.h"

#include "driver/temperature_sensor.h"
#include "esp_check.h"
#include "esp_log.h"

static const char *TAG = "bsp_temp";

static temperature_sensor_handle_t s_temp_handle = NULL;

esp_err_t bsp_temp_init(void)
{
    temperature_sensor_config_t cfg = TEMPERATURE_SENSOR_CONFIG_DEFAULT(BSP_TEMP_RANGE_MIN, BSP_TEMP_RANGE_MAX);
    ESP_RETURN_ON_ERROR(temperature_sensor_install(&cfg, &s_temp_handle), TAG, "install failed");
    ESP_RETURN_ON_ERROR(temperature_sensor_enable(s_temp_handle), TAG, "enable failed");
    ESP_LOGI(TAG, "Temperature sensor ready (%d..%d C)", BSP_TEMP_RANGE_MIN, BSP_TEMP_RANGE_MAX);
    return ESP_OK;
}

esp_err_t bsp_temp_get_celsius(float *celsius)
{
    if (s_temp_handle == NULL || celsius == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    return temperature_sensor_get_celsius(s_temp_handle, celsius);
}
