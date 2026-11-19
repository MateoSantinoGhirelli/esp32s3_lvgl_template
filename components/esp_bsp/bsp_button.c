#include "bsp_button.h"

#include "button_gpio.h"
#include "esp_check.h"
#include "esp_log.h"

static const char *TAG = "bsp_button";

static button_handle_t s_button = NULL;

esp_err_t bsp_button_init(void)
{
    /* Tiempos en 0 = valores por defecto del componente (menuconfig) */
    const button_config_t btn_cfg = {
        .long_press_time = 0,
        .short_press_time = 0,
    };
    const button_gpio_config_t gpio_cfg = {
        .gpio_num = BSP_PIN_BUTTON,
        .active_level = BSP_BUTTON_ACTIVE_LEVEL,
        .enable_power_save = false,
        .disable_pull = false,
    };
    ESP_RETURN_ON_ERROR(iot_button_new_gpio_device(&btn_cfg, &gpio_cfg, &s_button), TAG, "button create failed");
    ESP_LOGI(TAG, "Button ready on GPIO%d", BSP_PIN_BUTTON);
    return ESP_OK;
}

button_handle_t bsp_button_get_handle(void)
{
    return s_button;
}
