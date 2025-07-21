#pragma once

#include <QtCore/QObject>
#include <QtCore/QLoggingCategory>
#include <QMqttClient>
#include <QMqttTopicName>
#include <QJsonObject>
#include <QtPositioning/QGeoCoordinate>

#include "MqttSettings.h"

Q_DECLARE_LOGGING_CATEGORY(VehicleTelemetryLog)

// #define DECLARE_TOPICS(...) \
// 	private: \
// 	enum TopicType { __VA_ARGS__ }; \
// 	struct Topic { \
// 		QString	name; \
// 		QJsonObject	message = QJsonObject(); \
// 		int	qos = 0; \
// 		bool retained = false; \
// 		bool isChanged = false; \
// 	}; \
// 	QList<Topic> _topics = QList<Topic>(MAX_COUNT_TOPICS); \
// 	// signals: \
//     // void vfrTopicChanged(); \
//     // void vehicleFastTopicChanged(); \
//     // void vehicleSlowTopicChanged(); \
//     // void nothingTopicChanged();

#define MAX_COUNT_TOPICS        4
#define VFR_HUD_TOPIC           "dron/VFR_HUD"
#define VEHICLE_FAST_TOPIC		"esp/rx/telem"
#define VEHICLE_SLOW_TOPIC      "esp/rx/telem2"
#define NOTHING_TOPIC           "nothing"

class VehicleTelemetry : public QObject
{
	Q_OBJECT

    Q_PROPERTY(int				vehicleFlashlight       READ	vehicleFlashlight       WRITE	setVehicleFlashlight        NOTIFY	vehicleSlowTopicChanged)
    Q_PROPERTY(bool				vehicleEngine           READ	vehicleEngine           WRITE	setVehicleEngine            NOTIFY	nothingTopicChanged) //?
    Q_PROPERTY(bool				vehicleWeight           READ	vehicleWeight           WRITE	setVehicleWeight            NOTIFY	nothingTopicChanged) //?
    Q_PROPERTY(bool				vehicleReset            READ	vehicleReset            WRITE	setVehicleReset             NOTIFY	nothingTopicChanged) //?
    Q_PROPERTY(int				vehicleBattery          READ	vehicleBattery          WRITE	setVehicleBattery           NOTIFY	vehicleSlowTopicChanged)
    Q_PROPERTY(int  			vehicleTemperature      READ	vehicleTemperature      WRITE	setVehicleTemperature       NOTIFY	vehicleSlowTopicChanged)
    Q_PROPERTY(bool				vehicleFan              READ	vehicleFan              WRITE	setVehicleFan               NOTIFY	nothingTopicChanged) //?
    Q_PROPERTY(int  			vehiclePower            READ	vehiclePower            WRITE	setVehiclePower             NOTIFY	vehicleFastTopicChanged)
    Q_PROPERTY(int				vehicleSignal           READ	vehicleSignal           WRITE	setVehicleSignal            NOTIFY	vehicleFastTopicChanged)
    Q_PROPERTY(bool				vehicleValve            READ	vehicleValve            WRITE	setVehicleValve             NOTIFY	nothingTopicChanged) //?
    Q_PROPERTY(int  			vehicleLeftFrequrence	READ	vehicleLeftFrequrence	WRITE	setVehicleLeftFrequrence	NOTIFY	vehicleFastTopicChanged)
    Q_PROPERTY(int  			vehicleRightFrequrence	READ	vehicleRightFrequrence	WRITE	setVehicleRightFrequrence	NOTIFY	vehicleFastTopicChanged)
    Q_PROPERTY(int				vehicleCameraSelect     READ    vehicleCameraSelect     WRITE   setVehicleCameraSelect      NOTIFY  vehicleSlowTopicChanged)
    Q_PROPERTY(int				vehicleAntennaPosition  READ    vehicleAntennaPosition  WRITE   setVehicleAntennaPosition   NOTIFY  vehicleSlowTopicChanged)

    Q_PROPERTY(bool				droneWinding            READ	droneWinding            WRITE	setDroneWinding             NOTIFY	nothingTopicChanged)
    Q_PROPERTY(int				droneControlMode        READ	droneControlMode        WRITE	setDroneControlMode         NOTIFY	nothingTopicChanged)
    Q_PROPERTY(float			droneHeight             READ	droneHeight             WRITE	setDroneHeight              NOTIFY	nothingTopicChanged)
    Q_PROPERTY(bool				droneLinkPower          READ	droneLinkPower          WRITE	setDroneLinkPower           NOTIFY	nothingTopicChanged)
    Q_PROPERTY(int				droneBattery            READ	droneBattery            WRITE	setDroneBattery             NOTIFY	nothingTopicChanged)
    Q_PROPERTY(float			droneRotate             READ	droneRotate             WRITE	setDroneRotate              NOTIFY	vfrTopicChanged)
    Q_PROPERTY(QGeoCoordinate	droneEditLocation       READ	droneEditLocation       WRITE	setDroneEditLocation        NOTIFY	nothingTopicChanged)

	struct Topic;

    enum TopicType { VFR = 0, VEHICLE_FAST, VEHICLE_SLOW, NOTHING };
public:
	explicit VehicleTelemetry(QObject *parent = nullptr);
	~VehicleTelemetry();

	static VehicleTelemetry* instance();

	Q_INVOKABLE void 	connect			(const QString& host, quint16 port, const QString& username = "", const QString& password = "");
	Q_INVOKABLE void 	disconnect		();
	Q_INVOKABLE void	restart			(const QString& host, quint16 port, const QString& username = "", const QString& password = "");

public:
    bool 			vehicleFlashlight			() const 		{ return _topics[VEHICLE_SLOW].message["beam"].toBool(); }
    bool 			vehicleEngine				() const 		{ return _topics[NOTHING].message["engine"].toBool(); }
    bool 			vehicleWeight				() const 		{ return _topics[NOTHING].message["weight"].toBool(); }
    bool 			vehicleReset				() const 		{ return _topics[NOTHING].message["reset"].toBool(); }
    int 			vehicleBattery				() const 		{ return _topics[VEHICLE_SLOW].message["battery_perc"].toInt(); }
    int 			vehicleTemperature			() const 		{ return _topics[VEHICLE_SLOW].message["temp_motor"].toInt(); }
    bool 			vehicleFan					() const 		{ return _topics[NOTHING].message["fan"].toBool(); }
    int 			vehiclePower				() const 		{ return _topics[VEHICLE_FAST].message["power"].toInt(); }
    int 			vehicleSignal				() const 		{ return _topics[VEHICLE_FAST].message["rssi_rc"].toInt(); }
    bool 			vehicleValve				() const 		{ return _topics[NOTHING].message["valve"].toBool(); }
    int 			vehicleLeftFrequrence		() const 		{ return _topics[VEHICLE_FAST].message["speed_motorL"].toInt(); }
    int 			vehicleRightFrequrence		() const 		{ return _topics[VEHICLE_FAST].message["speed_motorR"].toInt(); }
    int 			vehicleCameraSelect			() const 		{ return _topics[VEHICLE_SLOW].message["camera_select"].toInt(); }
    int 			vehicleAntennaPosition      () const 		{ return _topics[VEHICLE_SLOW].message["ant_pos"].toInt(); }

    bool			droneWinding				() const 		{ return _topics[NOTHING].message["winding"].toBool(); }
    int				droneControlMode			() const 		{ return _topics[NOTHING].message["controlMode"].toInt(); }
    float			droneHeight					() const 		{ return _topics[NOTHING].message["height"].toDouble(); }
    bool			droneLinkPower				() const 		{ return _topics[NOTHING].message["linkPower"].toBool(); }
    int				droneBattery				() const 		{ return _topics[NOTHING].message["battery"].toInt(); }
    float			droneRotate					() const 		{ return _topics[VFR].message["heading"].toDouble(); }
	QGeoCoordinate	droneEditLocation			() const 		{ return _getDataCoordinate(_topics[NOTHING].message["gpsLocation"].toObject()); }
	
    void 	setVehicleFlashlight        (bool value) 	{ _topics[VEHICLE_SLOW].message["beam"] = value; emit vehicleSlowTopicChanged(); }
    void 	setVehicleEngine            (bool value) 	{ _topics[NOTHING].message["engine"] = value; emit nothingTopicChanged(); }
    void 	setVehicleWeight            (bool value) 	{ _topics[NOTHING].message["weight"] = value; emit nothingTopicChanged(); }
    void 	setVehicleReset             (bool value) 	{ _topics[NOTHING].message["reset"] = value; emit nothingTopicChanged(); }
    void 	setVehicleBattery           (int value) 	{ _topics[VEHICLE_SLOW].message["battery_perc"] = value; emit vehicleSlowTopicChanged(); }
    void 	setVehicleTemperature       (int value) 	{ _topics[VEHICLE_SLOW].message["temp_motor"] = value; emit vehicleSlowTopicChanged(); }
    void 	setVehicleFan               (bool value) 	{ _topics[NOTHING].message["fan"] = value; emit nothingTopicChanged(); }
    void 	setVehiclePower             (int value) 	{ _topics[VEHICLE_FAST].message["power"] = value; emit vehicleFastTopicChanged(); }
    void 	setVehicleSignal            (int value) 	{ _topics[VEHICLE_FAST].message["rssi_rc"] = value; emit vehicleFastTopicChanged(); }
    void 	setVehicleValve             (bool value) 	{ _topics[NOTHING].message["valve"] = value; emit nothingTopicChanged(); }
    void 	setVehicleLeftFrequrence	(int value) 	{ _topics[VEHICLE_FAST].message["speed_motorL"] = value; emit vehicleFastTopicChanged(); }
    void 	setVehicleRightFrequrence	(int value) 	{ _topics[VEHICLE_FAST].message["speed_motorR"] = value; emit vehicleFastTopicChanged(); }
    void 	setVehicleCameraSelect      (int value) 	{ _topics[VEHICLE_SLOW].message["camera_select"] = value; emit vehicleSlowTopicChanged(); }
    void 	setVehicleAntennaPosition   (int value) 	{ _topics[VEHICLE_SLOW].message["ant_pos"] = value; emit vehicleSlowTopicChanged(); }

    void 	setDroneWinding             (bool value) 			{ _topics[NOTHING].message["winding"] = value; emit nothingTopicChanged(); }
    void 	setDroneControlMode         (int value) 			{ _topics[NOTHING].message["controlMode"] = value; emit nothingTopicChanged(); }
    void 	setDroneHeight              (float value) 			{ _topics[NOTHING].message["height"] = value; emit nothingTopicChanged(); }
    void 	setDroneLinkPower           (bool value) 			{ _topics[NOTHING].message["linkPower"] = value; emit nothingTopicChanged(); }
    void 	setDroneBattery             (int value) 			{ _topics[NOTHING].message["battery"] = value; emit nothingTopicChanged(); }
    void 	setDroneRotate              (float value) 			{ _topics[VFR].message["heading"] = value; emit vfrTopicChanged(); }
	void 	setDroneEditLocation        (QGeoCoordinate value) 	{ _topics[NOTHING].message["gpsLocation"] = _setDataCoordinate(value); emit nothingTopicChanged(); }

private:
	void _initTopics();

	QGeoCoordinate 	_getDataCoordinate	(const QJsonObject& data)	const;
	
	QJsonObject 	_setDataCoordinate	(const QGeoCoordinate& value);

signals:
    void vfrTopicChanged();
    void vehicleFastTopicChanged();
    void vehicleSlowTopicChanged();
    void nothingTopicChanged();

private slots:
	void _configChanged		();
	void _stateChanged		(QMqttClient::ClientState state);
	void _errorChanged		(QMqttClient::ClientError error);
	void _messageReceived	(const QByteArray &message, const QMqttTopicName &topicName);
	void _updateTelemetry	(Topic &topic);

private:
	struct Topic {
		QString	name;
		QJsonObject	message = QJsonObject();
		int	qos = 0;
		bool retained = false;
		bool isChanged = false;
	};
	QList<Topic>		_topics = QList<Topic>(MAX_COUNT_TOPICS);

protected:
	QMqttClient* 	_mqttClient		= nullptr;
	MqttSettings*	_mqttSettings	= nullptr;
};
