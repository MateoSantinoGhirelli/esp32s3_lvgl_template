#include "ui_input.h"
#include "screens_update.h"
#include "bsp_button.h"
#include "esp_log.h"

static const char *TAG = "ui_input";

static lv_group_t *s_group = NULL;
static lv_indev_t *s_keypad = NULL;

/* Solo se toca desde contexto LVGL (handler de la cola y read_cb) */
static bool s_enter_pending = false;

/* ------------------------------------------------------------------ */

/* Corre en la tarea de esp_timer del componente button, NO en LVGL:
 * prohibido llamar lv_*. Solo encola el comando. */
static void on_button_click(void *button_handle, void *usr_data)
{
    (void)button_handle;
    (void)usr_data;
    ui_update_cmd(UI_UPDATE_BUTTON_CLICK, NULL);
}

/* Keypad virtual: reporta ENTER apretado durante una lectura y suelto en
 * la siguiente. Al soltarse, LVGL manda LV_EVENT_CLICKED al objeto enfocado. */
static void keypad_read_cb(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    (void)drv;
    data->key = LV_KEY_ENTER;
    if (s_enter_pending) {
        s_enter_pending = false;
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

/* ------------------------------------------------------------------ */

void ui_input_init(void)
{
    s_group = lv_group_create();

    static lv_indev_drv_t keypad_drv;
    lv_indev_drv_init(&keypad_drv);
    keypad_drv.type = LV_INDEV_TYPE_KEYPAD;
    keypad_drv.read_cb = keypad_read_cb;
    s_keypad = lv_indev_drv_register(&keypad_drv);
    lv_indev_set_group(s_keypad, s_group);

    button_handle_t btn = bsp_button_get_handle();
    if (btn == NULL) {
        ESP_LOGW(TAG, "physical button not initialized");
        return;
    }
    ESP_ERROR_CHECK(iot_button_register_cb(btn, BUTTON_SINGLE_CLICK, NULL, on_button_click, NULL));
    ESP_LOGI(TAG, "physical button mapped to LVGL keypad");
}

void ui_input_set_action(lv_obj_t *obj)
{
    lv_group_remove_all_objs(s_group);
    if (obj != NULL) {
        lv_group_add_obj(s_group, obj);
        lv_group_focus_obj(obj);
    }
}

void ui_input_post_enter(void)
{
    s_enter_pending = true;
}
