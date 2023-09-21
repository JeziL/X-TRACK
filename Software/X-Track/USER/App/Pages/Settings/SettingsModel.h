#ifndef __SETTINGS_MODEL_H
#define __SETTINGS_MODEL_H

#include "Common/DataProc/DataProc.h"

namespace Page
{

class SettingsModel
{
public:
    void Init();
    void Deinit();

    bool GetSoundEnable();
    void SetSoundEnable(bool soundEnable);

    void SetStatusBarStyle(DataProc::StatusBar_Style_t style);

private:
    Account* account;

private:

};

}

#endif
