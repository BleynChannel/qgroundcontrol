#include "MqttSettings.h"

#include <QtQml/QQmlEngine>

DECLARE_SETTINGGROUP(Mqtt, "Mqtt")
{
    qmlRegisterUncreatableType<MqttSettings>("QGroundControl.SettingsManager", 1, 0, "MqttSettings", "Reference only");
}

DECLARE_SETTINGSFACT_NO_FUNC(MqttSettings, hostname)
{
    if (!_hostnameFact) {
        _hostnameFact = _createSettingsFact(hostnameName);
        connect(_hostnameFact, &Fact::valueChanged, this, &MqttSettings::_configChanged);
    }
    return _hostnameFact;
}

DECLARE_SETTINGSFACT_NO_FUNC(MqttSettings, port)
{
    if (!_portFact) {
        _portFact = _createSettingsFact(portName);
        connect(_portFact, &Fact::valueChanged, this, &MqttSettings::_configChanged);
    }
    return _portFact;
}

DECLARE_SETTINGSFACT_NO_FUNC(MqttSettings, username)
{
	if (!_usernameFact) {
		_usernameFact = _createSettingsFact(usernameName);
		connect(_usernameFact, &Fact::valueChanged, this, &MqttSettings::_configChanged);
	}
	return _usernameFact;
}

DECLARE_SETTINGSFACT_NO_FUNC(MqttSettings, password)
{
	if (!_passwordFact) {
		_passwordFact = _createSettingsFact(passwordName);
		connect(_passwordFact, &Fact::valueChanged, this, &MqttSettings::_configChanged);
	}
	return _passwordFact;
}

void
MqttSettings::_configChanged(QVariant)
{
    emit mqttConfiguredChanged();
}
