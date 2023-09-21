#include "SettingsModel.h"
#include "Config/Config.h"
#include <stdio.h>

using namespace Page;

void SettingsModel::Init()
{
    account = new Account("SettingsModel", DataProc::Center(), 0, this);

    account->Subscribe("SysConfig");
    account->Subscribe("Storage");
    account->Subscribe("SportStatus");
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
        return CONFIG_SYSTEM_SOUND_ENABLE_DEFAULT;
    }
    return sysConfig.soundEnable;
}

void SettingsModel::SetSoundEnable(bool soundEnable) {
    DataProc::SysConfig_Info_t sysConfig;
    DATA_PROC_INIT_STRUCT(sysConfig);
    sysConfig.cmd = DataProc::SYSCONFIG_CMD_MOD_SOUND;
    sysConfig.soundEnable = soundEnable;
    account->Notify("SysConfig", &sysConfig, sizeof(sysConfig));
}

int SettingsModel::GetWeight() {
    HAL::SportStatus_Info_t sportStatus;
    if (account->Pull("SportStatus", &sportStatus, sizeof(sportStatus)) != Account::RES_OK) {
        return CONFIG_WEIGHT_DEFAULT;
    }
    return (int)sportStatus.weight;
}

void SettingsModel::SetWeight(int weight) {
    DataProc::SportStatus_Info_t info;
    DATA_PROC_INIT_STRUCT(info);
    info.cmd = DataProc::SportStatus_CMD_MOD_WEIGHT;
    info.weight = weight;
    account->Notify("SportStatus", &info, sizeof(info));
}

void SettingsModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
{
    DataProc::StatusBar_Info_t info;
    DATA_PROC_INIT_STRUCT(info);

    info.cmd = DataProc::STATUS_BAR_CMD_SET_STYLE;
    info.param.style = style;

    account->Notify("StatusBar", &info, sizeof(info));
}
