#include "../ui.h"

lv_obj_t *ui_scrSystem = NULL;
lv_obj_t *ui_lblSystemTitle = NULL;
lv_obj_t *ui_pnlSysInfo = NULL;
lv_obj_t *ui_lblChipValue = NULL;
lv_obj_t *ui_lblCpuValue = NULL;
lv_obj_t *ui_lblFlashValue = NULL;
lv_obj_t *ui_lblIdfValue = NULL;
lv_obj_t *ui_lblHeapValue = NULL;
lv_obj_t *ui_lblHeapMinValue = NULL;
lv_obj_t *ui_btnResetHeapMin = NULL;

#define SYS_ROW_HEIGHT  18

/* Fila "Titulo ........ valor" dentro del panel de informacion */
static lv_obj_t *create_info_row(int row, const char *caption)
{
    lv_obj_t *lbl_caption = lv_label_create(ui_pnlSysInfo);
    lv_obj_set_y(lbl_caption, row * SYS_ROW_HEIGHT);
    lv_obj_set_align(lbl_caption, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(lbl_caption, caption);
    lv_obj_set_style_text_color(lbl_caption, lv_color_hex(UI_COLOR_TEXT_DIM), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *lbl_value = lv_label_create(ui_pnlSysInfo);
    lv_obj_set_y(lbl_value, row * SYS_ROW_HEIGHT);
    lv_obj_set_align(lbl_value, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(lbl_value, "-");
    return lbl_value;
}

void ui_scrSystem_screen_init(void)
{
    ui_scrSystem = ui_create_screen();
    ui_lblSystemTitle = ui_create_title(ui_scrSystem, "Sistema");

    ui_pnlSysInfo = ui_create_panel(ui_scrSystem, 300, 6 * SYS_ROW_HEIGHT + 12);
    lv_obj_set_x(ui_pnlSysInfo, 0);
    lv_obj_set_y(ui_pnlSysInfo, 36);
    lv_obj_set_align(ui_pnlSysInfo, LV_ALIGN_TOP_MID);
    lv_obj_set_style_pad_hor(ui_pnlSysInfo, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblChipValue    = create_info_row(0, "Chip");
    ui_lblCpuValue     = create_info_row(1, "CPU");
    ui_lblFlashValue   = create_info_row(2, "Flash");
    ui_lblIdfValue     = create_info_row(3, "ESP-IDF");
    ui_lblHeapValue    = create_info_row(4, "Heap libre");
    ui_lblHeapMinValue = create_info_row(5, "Heap minimo");

    ui_btnResetHeapMin = ui_create_button(ui_scrSystem, LV_SYMBOL_LOOP "  Reset minimo", 160, -10, 158);
}
