#include "SettingsView.h"

using namespace Page;

#define ITEM_HEIGHT_MIN   48
#define ITEM_VER_PAD      32
#define ITEM_HOR_PAD      20
#define ITEM_COLUMN_PAD   16

void SettingsView::Create(lv_obj_t* root)
{
    lv_obj_set_style_pad_ver(root, ITEM_VER_PAD, 0);
    lv_obj_set_style_pad_hor(root, ITEM_HOR_PAD, 0);
    lv_obj_set_flex_flow(root, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        root,
        LV_FLEX_ALIGN_START,
        LV_FLEX_ALIGN_START,
        LV_FLEX_ALIGN_CENTER
    );

    Style_Init();

    /* Item Sound */
    Item_Create(&ui.sound, root, "Sound");
    lv_obj_t* ctrl = lv_switch_create(ui.sound.cont);
    lv_obj_set_size(ctrl, 42, 24);
    lv_obj_set_style_bg_color(ctrl, lv_color_hex(0xff931e), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_align(ctrl, LV_ALIGN_LEFT_MID, 0, 0);
    ui.sound.settingControl = ctrl;

    /* Item Weight */
    Item_Create(&ui.weight, root, "Weight (kg)");
    ctrl = lv_spinbox_create(ui.weight.cont);
    lv_spinbox_set_range(ctrl, 40, 150);
    lv_spinbox_set_digit_format(ctrl, 3, 0);
    lv_spinbox_step_prev(ctrl);
    lv_obj_set_width(ctrl, 80);
    lv_obj_align(ctrl, LV_ALIGN_LEFT_MID, 0, 0);
    ui.weight.settingControl = ctrl;

    /* Item ArrowTheme */
    Item_Create(&ui.arrowTheme, root, "Arrow theme");
    ctrl = lv_dropdown_create(ui.arrowTheme.cont);
    lv_dropdown_set_options(ctrl,
        "default\n"
        "dark\n"
        "light\n"
        "malfoy\n"
        "malfoy_head"
    );
    lv_obj_set_width(ctrl, 100);
    lv_obj_align(ctrl, LV_ALIGN_LEFT_MID, 0, 0);
    ui.arrowTheme.settingControl = ctrl;

    /* Item BackBtn */
    Item_Create(&ui.backBtn, root, "");
    ctrl = lv_obj_create(ui.backBtn.cont);
    lv_obj_remove_style_all(ctrl);
    lv_obj_set_size(ctrl, LV_HOR_RES - 2 * (ITEM_HOR_PAD + ITEM_COLUMN_PAD), 32);
    lv_obj_clear_flag(ctrl, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_img_src(ctrl, ResourcePool::GetImage("back"), 0);
    lv_obj_set_style_bg_opa(ctrl, LV_OPA_COVER, 0);
    lv_obj_set_style_width(ctrl, 45, LV_STATE_PRESSED);
    lv_obj_set_style_height(ctrl, 25, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ctrl, lv_color_hex(0x666666), 0);
    lv_obj_set_style_bg_color(ctrl, lv_color_hex(0xbbbbbb), LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ctrl, lv_color_hex(0xff931e), LV_STATE_FOCUSED);
    lv_obj_set_style_radius(ctrl, 9, 0);
    ui.backBtn.settingControl = ctrl;

    Group_Init();
}

void SettingsView::Group_Init()
{
    lv_group_t* group = lv_group_get_default();
    lv_group_set_wrap(group, true);

    item_t* item_grp = ((item_t*)&ui);

    /* Reverse adding to group makes encoder operation more comfortable */
    for (int i = sizeof(ui) / sizeof(item_t) - 1; i >= 0; i--)
    {
        lv_group_add_obj(group, item_grp[i].settingControl);
    }

    lv_group_focus_obj(item_grp[0].settingControl);
}

void SettingsView::Delete()
{
    lv_group_set_focus_cb(lv_group_get_default(), nullptr);
    Style_Reset();
}

void SettingsView::Style_Init()
{
    lv_style_init(&style.label);
    lv_style_set_text_font(&style.label, ResourcePool::GetFont("bahnschrift_13"));
    lv_style_set_text_color(&style.label, lv_color_hex(0x999999));
}

void SettingsView::Style_Reset()
{
    lv_style_reset(&style.label);
}

void SettingsView::Item_Create(
    item_t* item,
    lv_obj_t* par,
    const char* labelText
)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_enable_style_refresh(false);
    lv_obj_remove_style_all(cont);
    lv_obj_set_width(cont, LV_HOR_RES - 2 * ITEM_HOR_PAD);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(
        cont,
        LV_FLEX_ALIGN_START,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER
    );
    lv_obj_set_style_pad_column(cont, ITEM_COLUMN_PAD, 0);

    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    item->cont = cont;

    /* label */
    lv_obj_t* label = lv_label_create(cont);
    lv_obj_enable_style_refresh(false);
    lv_label_set_text(label, labelText);
    lv_obj_add_style(label, &style.label, 0);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 0, 0);
    item->settingLabel = label;

    lv_obj_move_foreground(label);
    lv_obj_enable_style_refresh(true);

    /* get real max height */
    lv_obj_update_layout(item->settingLabel);
    lv_coord_t height = lv_obj_get_height(item->settingLabel);
    height = LV_MAX(height, ITEM_HEIGHT_MIN);
    lv_obj_set_height(cont, height);
}

void SettingsView::SetSound(bool soundEnable) {
    if (soundEnable) {
        lv_obj_add_state(ui.sound.settingControl, LV_STATE_CHECKED);
    }
    else {
        lv_obj_clear_state(ui.sound.settingControl, LV_STATE_CHECKED);
    } 
}

void SettingsView::SetWeight(int weight) {
    lv_spinbox_set_value(ui.weight.settingControl, weight);
}

void SettingsView::SetArrowTheme(const char* theme) {
    const char* options = lv_dropdown_get_options(ui.arrowTheme.settingControl);
    // find corresponding option index
    // by ChatGPT
    const char* ptr = options;
    const char* sub_ptr = theme;
    uint16_t index = 0;
    while (*ptr) {
        if (*ptr == *sub_ptr) {
            // matched, continue compare
            ptr++;
            sub_ptr++;

            if (*sub_ptr == '\0') {
                // theme totally matched
                break;
            }
        }
        else if (*ptr == '\n') {
            // new line, theme ptr reset
            index++;
            sub_ptr = theme;
            ptr++;
        }
        else {
            // not matched, try next character
            ptr++;
        }
    }
    if (index >= lv_dropdown_get_option_cnt(ui.arrowTheme.settingControl)) index = 0;
    lv_dropdown_set_selected(ui.arrowTheme.settingControl, index);
}
