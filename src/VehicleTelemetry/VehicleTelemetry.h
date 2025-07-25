#pragma once

#include <QtCore/QObject>
#include <QtCore/QLoggingCategory>
#include <QMqttClient>
#include <QMqttTopicName>
#include <QJsonObject>
#include <QtPositioning/QGeoCoordinate>

#include "MqttSettings.h"
#include "helpers.h"

Q_DECLARE_LOGGING_CATEGORY(VehicleTelemetryLog)

class VehicleTelemetry : public QObject
{
	Q_OBJECT

    // Vehicle Fast topic parameters
    DECLARE_TOPIC_PARAM(int, vehiclePower, "power", 0, VEHICLE_FAST, Int)
    DECLARE_TOPIC_PARAM(int, vehicleSignal, "rssi_rc", 0, VEHICLE_FAST, Int)
    DECLARE_TOPIC_PARAM(int, vehicleLeftFrequrence, "speed_motorL", 0, VEHICLE_FAST, Int)
    DECLARE_TOPIC_PARAM(int, vehicleRightFrequrence, "speed_motorR", 0, VEHICLE_FAST, Int)

    // Vehicle Slow topic parameters
    DECLARE_TOPIC_PARAM(int, vehicleFlashlight, "beam", 0, VEHICLE_SLOW, Int)
    DECLARE_TOPIC_PARAM(int, vehicleBattery, "battery_perc", 0, VEHICLE_SLOW, Int)
    DECLARE_TOPIC_PARAM(int, vehicleTemperature, "temp_motor", 0, VEHICLE_SLOW, Int)
    DECLARE_TOPIC_PARAM(int, vehicleCameraSelect, "camera_select", 0, VEHICLE_SLOW, Int)
    DECLARE_TOPIC_PARAM(int, vehicleAntennaPosition, "ant_pos", 0, VEHICLE_SLOW, Int)

    // VFR topic parameters
    DECLARE_TOPIC_PARAM(float, droneRotate, "heading", 0.0f, VFR, Double)

    // Nothing topic parameters
    DECLARE_TOPIC_PARAM(bool, vehicleEngine, "engine", false, NOTHING, Bool)
    DECLARE_TOPIC_PARAM(bool, vehicleWeight, "weight", false, NOTHING, Bool)
    DECLARE_TOPIC_PARAM(bool, vehicleReset, "reset", false, NOTHING, Bool)
    DECLARE_TOPIC_PARAM(bool, vehicleFan, "fan", false, NOTHING, Bool)
    DECLARE_TOPIC_PARAM(bool, vehicleValve, "valve", false, NOTHING, Bool)
    DECLARE_TOPIC_PARAM(bool, droneWinding, "winding", false, NOTHING, Bool)
    DECLARE_TOPIC_PARAM(int, droneControlMode, "controlMode", 0, NOTHING, Int)
    DECLARE_TOPIC_PARAM(float, droneHeight, "height", 0.0f, NOTHING, Double)
    DECLARE_TOPIC_PARAM(bool, droneLinkPower, "linkPower", false, NOTHING, Bool)
    DECLARE_TOPIC_PARAM(int, droneBattery, "battery", 0, NOTHING, Int)

    //? Template topic parameters
    //? 1. Type; 2. Name; 3. JSON name; 4. Default value; 5. Topic; 6. To type (The type to convert the json object)
    // DECLARE_TOPIC_PARAM(int, customParam, "customParam", 0, CUSTOM_TOPIC, Int)

signals:
    //? Here we announce the topics
    DECLARE_TOPICS(VFR, VEHICLE_FAST, VEHICLE_SLOW, NOTHING, /* CUSTOM_TOPIC */)

private:
    void _initTopics() {
        INIT_TOPIC(VFR, "dron/VFR_HUD")
        INIT_TOPIC(VEHICLE_FAST, "esp/rx/telem")
        INIT_TOPIC(VEHICLE_SLOW, "esp/rx/telem2")
        INIT_TOPIC(NOTHING, "nothing")
        
        //? Template initialize topic
        //? 1. Topic name; 2. Topic path (MQTT)
        // INIT_TOPIC(CUSTOM_TOPIC, "custom")
    }

private:
    Q_PROPERTY(QGeoCoordinate droneEditLocation READ droneEditLocation WRITE setDroneEditLocation NOTIFY NOTHINGChanged)

	struct Topic;

public:
	explicit VehicleTelemetry(QObject *parent = nullptr);
	~VehicleTelemetry();

	static VehicleTelemetry* instance();

	Q_INVOKABLE void connect(const QString& host, quint16 port, const QString& username = "", const QString& password = "");
	Q_INVOKABLE void disconnect();
	Q_INVOKABLE void restart(const QString& host, quint16 port, const QString& username = "", const QString& password = "");

public:
	QGeoCoordinate droneEditLocation() const {
        const auto& msg = _topics[static_cast<int>(TopicType::NOTHING)].message;
        if (!msg.contains("gpsLocation")) {
            return QGeoCoordinate();
        }
        return _getDataCoordinate(msg["gpsLocation"].toObject());
    }

    void setDroneEditLocation(QGeoCoordinate value) {
        const auto& msg = _topics[static_cast<int>(TopicType::NOTHING)].message;
        QJsonObject json = _setDataCoordinate(value);
        if (!msg.contains("gpsLocation") || msg["gpsLocation"] != json) {
            msg["gpsLocation"] = json;
            _topics[static_cast<int>(TopicType::NOTHING)].isChanged = true;
            emit NOTHINGChanged();
        }
    }

private:
	QGeoCoordinate _getDataCoordinate(const QJsonObject& data) const;
	
	QJsonObject _setDataCoordinate(const QGeoCoordinate& value);

private slots:
	void _configChanged		();
	void _stateChanged		(QMqttClient::ClientState state);
	void _errorChanged		(QMqttClient::ClientError error);
	void _messageReceived	(const QByteArray &message, const QMqttTopicName &topicName);
	void _updateTelemetry	(Topic &topic);

private:
	struct Topic {
		QString	path;
		QJsonObject	message = QJsonObject();
		int	qos = 0;
		bool retained = false;
		bool isChanged = false;
	};

	QList<Topic>	_topics         = QList<Topic>(static_cast<int>(TopicType::_COUNT));
	QMqttClient* 	_mqttClient		= nullptr;
	MqttSettings*	_mqttSettings	= nullptr;
};
