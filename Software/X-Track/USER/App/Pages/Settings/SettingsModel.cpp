#include "SettingsModel.h"
#include <stdio.h>

using namespace Page;

void SettingsModel::Init()
{
    account = new Account("SettingsModel", DataProc::Center(), 0, this);

    account->Subscribe("SysConfig");
    account->Subscribe("StatusBar");
}

void SettingsModel::Deinit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

bool SettingsModel::GetSoundEnable() {
    DataProc::SysConfig_Info_t sysConfig;
    if (account->Pull("SysConfig", &sysConfig, sizeof(sysConfig)) != Account::RES_OK) {
        return true;
    }
    return sysConfig.soundEnable;
}

void SettingsModel::SetSoundEnable(bool soundEnable) {
    printf("setsound: %s\n", soundEnable ? "on" : "off");
}

void SettingsModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
{
    DataProc::StatusBar_Info_t info;
    DATA_PROC_INIT_STRUCT(info);

    info.cmd = DataProc::STATUS_BAR_CMD_SET_STYLE;
    info.param.style = style;

    account->Notify("StatusBar", &info, sizeof(info));
}
