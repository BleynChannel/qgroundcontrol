#pragma once

#include <QtCore/QObject>
#include <QtCore/QLoggingCategory>
#include <QMqttClient>
#include <QMqttTopicName>
#include <QJsonObject>
#include <QtPositioning/QGeoCoordinate>

#include "QGCToolbox.h"
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
//     // void _vfrTopicChanged(); \
//     // void _vehicleFastTopicChanged(); \
//     // void _vehicleSlowTopicChanged(); \
//     // void _nothingTopicChanged();

#define MAX_COUNT_TOPICS        4
#define VFR_HUD_TOPIC           "dron/VFR_HUD"
#define VEHICLE_FAST_TOPIC		"esp/rx/telem"
#define VEHICLE_SLOW_TOPIC      "esp/rx/telem2"
#define NOTHING_TOPIC           "nothing"

class VehicleTelemetry : public QGCTool
{
	Q_OBJECT

    Q_PROPERTY(int				vehicleFlashlight       READ	vehicleFlashlight       WRITE	setVehicleFlashlight        NOTIFY	_vehicleSlowTopicChanged)
    Q_PROPERTY(bool				vehicleEngine           READ	vehicleEngine           WRITE	setVehicleEngine            NOTIFY	_nothingTopicChanged) //?
    Q_PROPERTY(bool				vehicleWeight           READ	vehicleWeight           WRITE	setVehicleWeight            NOTIFY	_nothingTopicChanged) //?
    Q_PROPERTY(bool				vehicleReset            READ	vehicleReset            WRITE	setVehicleReset             NOTIFY	_nothingTopicChanged) //?
    Q_PROPERTY(int				vehicleBattery          READ	vehicleBattery          WRITE	setVehicleBattery           NOTIFY	_vehicleSlowTopicChanged)
    Q_PROPERTY(int  			vehicleTemperature      READ	vehicleTemperature      WRITE	setVehicleTemperature       NOTIFY	_vehicleSlowTopicChanged)
    Q_PROPERTY(bool				vehicleFan              READ	vehicleFan              WRITE	setVehicleFan               NOTIFY	_nothingTopicChanged) //?
    Q_PROPERTY(int  			vehiclePower            READ	vehiclePower            WRITE	setVehiclePower             NOTIFY	_vehicleFastTopicChanged)
    Q_PROPERTY(int				vehicleSignal           READ	vehicleSignal           WRITE	setVehicleSignal            NOTIFY	_vehicleFastTopicChanged)
    Q_PROPERTY(bool				vehicleValve            READ	vehicleValve            WRITE	setVehicleValve             NOTIFY	_nothingTopicChanged) //?
    Q_PROPERTY(int  			vehicleLeftFrequrence	READ	vehicleLeftFrequrence	WRITE	setVehicleLeftFrequrence	NOTIFY	_vehicleFastTopicChanged)
    Q_PROPERTY(int  			vehicleRightFrequrence	READ	vehicleRightFrequrence	WRITE	setVehicleRightFrequrence	NOTIFY	_vehicleFastTopicChanged)

    Q_PROPERTY(bool				droneWinding            READ	droneWinding            WRITE	setDroneWinding             NOTIFY	_nothingTopicChanged)
    Q_PROPERTY(int				droneControlMode        READ	droneControlMode        WRITE	setDroneControlMode         NOTIFY	_nothingTopicChanged)
    Q_PROPERTY(float			droneHeight             READ	droneHeight             WRITE	setDroneHeight              NOTIFY	_nothingTopicChanged)
    Q_PROPERTY(bool				droneLinkPower          READ	droneLinkPower          WRITE	setDroneLinkPower           NOTIFY	_nothingTopicChanged)
    Q_PROPERTY(int				droneBattery            READ	droneBattery            WRITE	setDroneBattery             NOTIFY	_nothingTopicChanged)
    Q_PROPERTY(float			droneRotate             READ	droneRotate             WRITE	setDroneRotate              NOTIFY	_vfrTopicChanged)
    Q_PROPERTY(QGeoCoordinate	droneEditLocation       READ	droneEditLocation       WRITE	setDroneEditLocation        NOTIFY	_nothingTopicChanged)

	struct Topic;

    enum TopicType { VFR = 0, VEHICLE_FAST, VEHICLE_SLOW, NOTHING };
public:
	VehicleTelemetry(QGCApplication* app, QGCToolbox* toolbox);
	virtual ~VehicleTelemetry();

	void setToolbox(QGCToolbox *toolbox) override;

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

    bool			droneWinding				() const 		{ return _topics[NOTHING].message["winding"].toBool(); }
    int				droneControlMode			() const 		{ return _topics[NOTHING].message["controlMode"].toInt(); }
    float			droneHeight					() const 		{ return _topics[NOTHING].message["height"].toDouble(); }
    bool			droneLinkPower				() const 		{ return _topics[NOTHING].message["linkPower"].toBool(); }
    int				droneBattery				() const 		{ return _topics[NOTHING].message["battery"].toInt(); }
    float			droneRotate					() const 		{ return _topics[VFR].message["heading"].toDouble(); }
	QGeoCoordinate	droneEditLocation			() const 		{ return _getDataCoordinate(_topics[NOTHING].message["gpsLocation"].toObject()); }
	
    void 	setVehicleFlashlight        (bool value) 	{ _topics[VEHICLE_SLOW].message["beam"] = value; emit _vehicleSlowTopicChanged(); }
    void 	setVehicleEngine            (bool value) 	{ _topics[NOTHING].message["engine"] = value; emit _nothingTopicChanged(); }
    void 	setVehicleWeight            (bool value) 	{ _topics[NOTHING].message["weight"] = value; emit _nothingTopicChanged(); }
    void 	setVehicleReset             (bool value) 	{ _topics[NOTHING].message["reset"] = value; emit _nothingTopicChanged(); }
    void 	setVehicleBattery           (int value) 	{ _topics[VEHICLE_SLOW].message["battery_perc"] = value; emit _vehicleSlowTopicChanged(); }
    void 	setVehicleTemperature       (int value) 	{ _topics[VEHICLE_SLOW].message["temp_motor"] = value; emit _vehicleSlowTopicChanged(); }
    void 	setVehicleFan               (bool value) 	{ _topics[NOTHING].message["fan"] = value; emit _nothingTopicChanged(); }
    void 	setVehiclePower             (int value) 	{ _topics[VEHICLE_FAST].message["power"] = value; emit _vehicleFastTopicChanged(); }
    void 	setVehicleSignal            (int value) 	{ _topics[VEHICLE_FAST].message["rssi_rc"] = value; emit _vehicleFastTopicChanged(); }
    void 	setVehicleValve             (bool value) 	{ _topics[NOTHING].message["valve"] = value; emit _nothingTopicChanged(); }
    void 	setVehicleLeftFrequrence	(int value) 	{ _topics[VEHICLE_FAST].message["speed_motorL"] = value; emit _vehicleFastTopicChanged(); }
    void 	setVehicleRightFrequrence	(int value) 	{ _topics[VEHICLE_FAST].message["speed_motorR"] = value; emit _vehicleFastTopicChanged(); }

    void 	setDroneWinding             (bool value) 			{ _topics[NOTHING].message["winding"] = value; emit _nothingTopicChanged(); }
    void 	setDroneControlMode         (int value) 			{ _topics[NOTHING].message["controlMode"] = value; emit _nothingTopicChanged(); }
    void 	setDroneHeight              (float value) 			{ _topics[NOTHING].message["height"] = value; emit _nothingTopicChanged(); }
    void 	setDroneLinkPower           (bool value) 			{ _topics[NOTHING].message["linkPower"] = value; emit _nothingTopicChanged(); }
    void 	setDroneBattery             (int value) 			{ _topics[NOTHING].message["battery"] = value; emit _nothingTopicChanged(); }
    void 	setDroneRotate              (float value) 			{ _topics[VFR].message["heading"] = value; emit _vfrTopicChanged(); }
	void 	setDroneEditLocation        (QGeoCoordinate value) 	{ _topics[NOTHING].message["gpsLocation"] = _setDataCoordinate(value); emit _nothingTopicChanged(); }

private:
	void _initTopics();

	QGeoCoordinate 	_getDataCoordinate	(const QJsonObject& data)	const;
	
	QJsonObject 	_setDataCoordinate	(const QGeoCoordinate& value);

signals:
    void _vfrTopicChanged();
    void _vehicleFastTopicChanged();
    void _vehicleSlowTopicChanged();
    void _nothingTopicChanged();

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
