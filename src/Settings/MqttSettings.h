#pragma once

#include "SettingsGroup.h"

class MqttSettings : public SettingsGroup
{
    Q_OBJECT
public:
    MqttSettings(QObject* parent = nullptr);

    DEFINE_SETTING_NAME_GROUP()

    DEFINE_SETTINGFACT(hostname)
    DEFINE_SETTINGFACT(port)
    DEFINE_SETTINGFACT(username)
    DEFINE_SETTINGFACT(password)
	
signals:
	void mqttConfiguredChanged	();

private slots:
	void _configChanged			(QVariant value);
};
