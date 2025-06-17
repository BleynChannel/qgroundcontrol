#pragma once

#include <QtCore/QObject>
#include <QtCore/QLoggingCategory>
#include <QMqttClient>
#include <QMqttTopicName>
#include <QJsonObject>

#include "QGCToolbox.h"
#include "MqttSettings.h"

Q_DECLARE_LOGGING_CATEGORY(VehicleTelemetryLog)

#define MAX_COUNT_TOPICS 1
#define DATA_TOPIC "data"

class VehicleTelemetry : public QGCTool
{
	Q_OBJECT

	Q_PROPERTY(bool		vehicleFlashlight	READ	vehicleFlashlight	WRITE	setVehicleFlashlight	NOTIFY	_dataTopicChanged)
	Q_PROPERTY(bool		vehicleEngine		READ	vehicleEngine		WRITE	setVehicleEngine		NOTIFY	_dataTopicChanged)
	Q_PROPERTY(bool		vehicleWeight		READ	vehicleWeight		WRITE	setVehicleWeight		NOTIFY	_dataTopicChanged)
	Q_PROPERTY(bool		vehicleReset		READ	vehicleReset		WRITE	setVehicleReset			NOTIFY	_dataTopicChanged)
	Q_PROPERTY(int		vehicleBattery		READ	vehicleBattery		WRITE	setVehicleBattery		NOTIFY	_dataTopicChanged)
	Q_PROPERTY(float	vehicleTemperature	READ	vehicleTemperature	WRITE	setVehicleTemperature	NOTIFY	_dataTopicChanged)
	Q_PROPERTY(bool		vehicleFan			READ	vehicleFan			WRITE	setVehicleFan			NOTIFY	_dataTopicChanged)
	Q_PROPERTY(float	vehiclePower		READ	vehiclePower		WRITE	setVehiclePower			NOTIFY	_dataTopicChanged)
	Q_PROPERTY(int		vehicleSignal		READ	vehicleSignal		WRITE	setVehicleSignal		NOTIFY	_dataTopicChanged)
	Q_PROPERTY(bool		vehicleValve		READ	vehicleValve		WRITE	setVehicleValve			NOTIFY	_dataTopicChanged)
	Q_PROPERTY(float	vehicleFrequrence	READ	vehicleFrequrence	WRITE	setVehicleFrequrence	NOTIFY	_dataTopicChanged)

	struct Topic;

	enum TopicType { DATA = 0 };
public:
	VehicleTelemetry(QGCApplication* app, QGCToolbox* toolbox);
	virtual ~VehicleTelemetry();

	void setToolbox(QGCToolbox *toolbox) override;

	Q_INVOKABLE void 	connect			(const QString& host, quint16 port, const QString& username = "", const QString& password = "");
	Q_INVOKABLE void 	disconnect		();
	Q_INVOKABLE void	restart			(const QString& host, quint16 port, const QString& username = "", const QString& password = "");

public:
	bool 	vehicleFlashlight		() const 		{ return _topics[DATA].message["flashlight"].toBool(); }
	bool 	vehicleEngine			() const 		{ return _topics[DATA].message["engine"].toBool(); }
	bool 	vehicleWeight			() const 		{ return _topics[DATA].message["weight"].toBool(); }
	bool 	vehicleReset			() const 		{ return _topics[DATA].message["reset"].toBool(); }
	int 	vehicleBattery			() const 		{ return _topics[DATA].message["battery"].toInt(); }
	float	vehicleTemperature		() const 		{ return _topics[DATA].message["temperature"].toDouble(); }
	bool 	vehicleFan				() const 		{ return _topics[DATA].message["fan"].toBool(); }
	float	vehiclePower			() const 		{ return _topics[DATA].message["power"].toDouble(); }
	int 	vehicleSignal			() const 		{ return _topics[DATA].message["signal"].toInt(); }
	bool 	vehicleValve			() const 		{ return _topics[DATA].message["valve"].toBool(); }
	float	vehicleFrequrence		() const 		{ return _topics[DATA].message["frequrence"].toDouble(); }
	
	void 	setVehicleFlashlight	(bool value) 	{ _topics[DATA].message["flashlight"] = value; emit _dataTopicChanged(); }
	void 	setVehicleEngine		(bool value) 	{ _topics[DATA].message["engine"] = value; emit _dataTopicChanged(); }
	void 	setVehicleWeight		(bool value) 	{ _topics[DATA].message["weight"] = value; emit _dataTopicChanged(); }
	void 	setVehicleReset			(bool value) 	{ _topics[DATA].message["reset"] = value; emit _dataTopicChanged(); }
	void 	setVehicleBattery		(int value) 	{ _topics[DATA].message["battery"] = value; emit _dataTopicChanged(); }
	void 	setVehicleTemperature	(float value) 	{ _topics[DATA].message["temperature"] = value; emit _dataTopicChanged(); }
	void 	setVehicleFan			(bool value) 	{ _topics[DATA].message["fan"] = value; emit _dataTopicChanged(); }
	void 	setVehiclePower			(float value) 	{ _topics[DATA].message["power"] = value; emit _dataTopicChanged(); }
	void 	setVehicleSignal		(int value) 	{ _topics[DATA].message["signal"] = value; emit _dataTopicChanged(); }
	void 	setVehicleValve			(bool value) 	{ _topics[DATA].message["valve"] = value; emit _dataTopicChanged(); }
	void 	setVehicleFrequrence	(float value) 	{ _topics[DATA].message["frequrence"] = value; emit _dataTopicChanged(); }

private:
	void _initTopics();

	signals:
	void _dataTopicChanged();

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
