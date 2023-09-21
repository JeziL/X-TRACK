#ifndef __SETTINGS_VIEW_H
#define __SETTINGS_VIEW_H

#include "../Page.h"

namespace Page
{

class SettingsView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    typedef struct
    {
        lv_obj_t* cont;
        lv_obj_t* settingLabel;
        lv_obj_t* settingControl;
    } item_t;

    struct
    {
        item_t sound;
        item_t weight;
        item_t arrowTheme;
        item_t backBtn;
    } ui;

public:
    void SetSound(
        bool soundOn
    );
    void SetWeight(
        int weight
    );
    void SetArrowTheme(
        const char* theme
    );

private:
    struct
    {
        lv_style_t label;
    } style;

private:
    void Group_Init();
    void Style_Init();
    void Style_Reset();
    void Item_Create(
        item_t*     item,
        lv_obj_t*   par,
        const char* labelText
    );
};

}

#endif // !__VIEW_H
