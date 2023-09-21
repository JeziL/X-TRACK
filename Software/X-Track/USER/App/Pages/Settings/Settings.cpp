#include "Settings.h"
#include "../App/Version.h"

using namespace Page;

Settings::Settings()
{
}

Settings::~Settings()
{

}

void Settings::onCustomAttrConfig()
{

}

void Settings::onViewLoad()
{
    Model.Init();
    View.Create(_root);
    AttachEvent(_root);

    SettingsView::item_t* item_grp = ((SettingsView::item_t*)&View.ui);

    for (int i = 0; i < sizeof(View.ui) / sizeof(SettingsView::item_t); i++)
    {
        AttachEvent(item_grp[i].settingControl);
    }
}

void Settings::onViewDidLoad()
{

}

void Settings::onViewWillAppear()
{
    Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_BLACK);

    timer = lv_timer_create(onTimerUpdate, 1000, this);
    lv_timer_ready(timer);

    lv_obj_fade_in(_root, 300, 0);
}

void Settings::onViewDidAppear()
{
    lv_group_t* group = lv_group_get_default();
    LV_ASSERT_NULL(group);
    View.onFocus(group);

    View.SetSound(Model.GetSoundEnable());
    View.SetWeight(Model.GetWeight());
}

void Settings::onViewWillDisappear()
{
    lv_obj_fade_out(_root, 300, 0);
}

void Settings::onViewDidDisappear()
{
    lv_timer_del(timer);
}

void Settings::onViewUnload()
{
    View.Delete();
    Model.Deinit();
}

void Settings::onViewDidUnload()
{

}

void Settings::AttachEvent(lv_obj_t* obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Settings::Update()
{

}

void Settings::onTimerUpdate(lv_timer_t* timer)
{
    Settings* instance = (Settings*)timer->user_data;

    instance->Update();
}

void Settings::onEvent(lv_event_t* event)
{
    Settings* instance = (Settings*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    // Sound switch changed
    if (obj == instance->View.ui.sound.settingControl && code == LV_EVENT_VALUE_CHANGED) {
        instance->Model.SetSoundEnable(lv_obj_has_state(obj, LV_STATE_CHECKED));
    }

    // Weight spinbox changed
    if (obj == instance->View.ui.weight.settingControl && code == LV_EVENT_VALUE_CHANGED) {
        instance->Model.SetWeight(lv_spinbox_get_value(obj));
    }

    if (code == LV_EVENT_PRESSED)
    {
        if (obj == instance->View.ui.backBtn.settingControl)
        {
            instance->_Manager->Pop();
        }
    }

    if (obj == instance->_root)
    {
        if (code == LV_EVENT_LEAVE)
        {
            instance->_Manager->Pop();
        }
    }
}
