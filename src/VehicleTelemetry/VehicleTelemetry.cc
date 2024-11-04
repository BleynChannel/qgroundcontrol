#include "VehicleTelemetry.h"
#include "SettingsManager.h"

#include <QtQml/QQmlEngine>
#include <QMqttTopicName>
#include <QMqttTopicFilter>
#include <QGCLoggingCategory.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

QGC_LOGGING_CATEGORY(VehicleTelemetryLog, "VehicleTelemetryLog")

VehicleTelemetry::VehicleTelemetry(QGCApplication* app, QGCToolbox* toolbox)
	: QGCTool(app, toolbox)
	, _mqttClient(new QMqttClient())
{
	QObject::connect(_mqttClient, &QMqttClient::stateChanged, this, &VehicleTelemetry::_stateChanged);
	QObject::connect(_mqttClient, &QMqttClient::errorChanged, this, &VehicleTelemetry::_errorChanged);
	QObject::connect(_mqttClient, &QMqttClient::messageReceived, this, &VehicleTelemetry::_messageReceived);
	
	QObject::connect(this, &VehicleTelemetry::_dataTopicChanged, [this]() { _updateTelemetry(_topics[VehicleTelemetry::DATA]); });

	_initTopics();
}

VehicleTelemetry::~VehicleTelemetry()
{
	this->disconnect();
	delete _mqttClient;
}

void
VehicleTelemetry::setToolbox(QGCToolbox *toolbox)
{
	QGCTool::setToolbox(toolbox);
	QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
	qmlRegisterUncreatableType<VehicleTelemetry>("QGroundControl.VehicleTelemetry", 1, 0, "VehicleTelemetry", "Reference only");

	_mqttSettings = toolbox->settingsManager()->mqttSettings();
	QObject::connect(_mqttSettings,   &MqttSettings::mqttConfiguredChanged, this, &VehicleTelemetry::_configChanged);

	this->connect(
		_mqttSettings->hostname()->rawValue().toString(), 
		_mqttSettings->port()->rawValue().toInt(), 
		_mqttSettings->username()->rawValue().toString(), 
		_mqttSettings->password()->rawValue().toString());
}

void
VehicleTelemetry::connect(const QString& host, quint16 port, const QString& username, const QString& password)
{
	_mqttClient->setHostname(host);
	_mqttClient->setPort(port);
	_mqttClient->setUsername(username);
	_mqttClient->setPassword(password);
	_mqttClient->connectToHost();
}

void
VehicleTelemetry::disconnect()
{
	_mqttClient->disconnectFromHost();
}

void
VehicleTelemetry::restart(const QString& host, quint16 port, const QString& username, const QString& password)
{
	this->disconnect();
	this->connect(host, port, username, password);
}

void
VehicleTelemetry::_initTopics()
{
	// Data Topic
	_topics[VehicleTelemetry::DATA].name = QString(DATA_TOPIC);
	_topics[VehicleTelemetry::DATA].message["flashlight"] = false;
	_topics[VehicleTelemetry::DATA].message["engine"] = false;
	_topics[VehicleTelemetry::DATA].message["weight"] = false;
	_topics[VehicleTelemetry::DATA].message["reset"] = false;
	_topics[VehicleTelemetry::DATA].message["battery"] = 0;
	_topics[VehicleTelemetry::DATA].message["temperature"] = 0.f;
	_topics[VehicleTelemetry::DATA].message["fan"] = false;
	_topics[VehicleTelemetry::DATA].message["power"] = 0.f;
	_topics[VehicleTelemetry::DATA].message["signal"] = 0;
	_topics[VehicleTelemetry::DATA].message["valve"] = false;
	_topics[VehicleTelemetry::DATA].message["frequrence"] = 0.f;
}

void
VehicleTelemetry::_configChanged()
{
	this->restart(
		_mqttSettings->hostname()->rawValue().toString(), 
		static_cast<quint16>(_mqttSettings->port()->rawValue().toInt()), 
		_mqttSettings->username()->rawValue().toString(), 
		_mqttSettings->password()->rawValue().toString());
}

void
VehicleTelemetry::_stateChanged(QMqttClient::ClientState state)
{
	switch (state) {
	case QMqttClient::Connecting:
		qCDebug(VehicleTelemetryLog) << "Connecting to" 
			<< "Host:" << _mqttClient->hostname() << ';'
			<< "Port:" << _mqttClient->port() << ';'
			<< "Username:" << _mqttClient->username() << ';'
			<< "Password:" << _mqttClient->password() << ';';
		break;
	case QMqttClient::Connected:
		qCDebug(VehicleTelemetryLog) << "Connected";

		if (!_mqttClient->subscribe(QString(DATA_TOPIC))) {
			qCWarning(VehicleTelemetryLog) << "Failed to subscribe to '" << DATA_TOPIC << "'";
		}
		
		break;
	case QMqttClient::Disconnected:
		qCDebug(VehicleTelemetryLog) << "Disconnected";
		break;
	}
}

void
VehicleTelemetry::_errorChanged(QMqttClient::ClientError error)
{
	switch (error) {
	case QMqttClient::NoError:
		qCWarning(VehicleTelemetryLog) << "No error occurred.";
		break;
	case QMqttClient::InvalidProtocolVersion:
		qCWarning(VehicleTelemetryLog) << "The broker does not accept a connection using the specified protocol version.";
		break;
	case QMqttClient::IdRejected:
		qCWarning(VehicleTelemetryLog) << "The client ID is malformed. This might be related to its length.";
		break;
	case QMqttClient::ServerUnavailable:
		qCWarning(VehicleTelemetryLog) << "The network connection has been established, but the service is unavailable on the broker side.";
		break;
	case QMqttClient::BadUsernameOrPassword:
		qCWarning(VehicleTelemetryLog) << "The data in the username or password is malformed.";
		break;
	case QMqttClient::NotAuthorized:
		qCWarning(VehicleTelemetryLog) << "The client is not authorized to connect.";
		break;
	case QMqttClient::TransportInvalid:
		qCWarning(VehicleTelemetryLog) << "The underlying transport caused an error. For example, the connection might have been interrupted unexpectedly.";
		break;
	case QMqttClient::ProtocolViolation:
		qCWarning(VehicleTelemetryLog) << "The client encountered a protocol violation, and therefore closed the connection.";
		break;
	case QMqttClient::UnknownError:
		qCWarning(VehicleTelemetryLog) << "An unknown error occurred.";
		break;
	case QMqttClient::Mqtt5SpecificError:
		qCWarning(VehicleTelemetryLog) << "The error is related to MQTT protocol level 5. A reason code might provide more details.";
		break;
	}
}

void
VehicleTelemetry::_messageReceived(const QByteArray &message, const QMqttTopicName &topicName)
{
	VehicleTelemetry::Topic *topic = nullptr;
	for (int i = 0; i < MAX_COUNT_TOPICS; i++) {
		if (_topics[i].name == topicName) {
			topic = &_topics[i];
			break;
		}
	}

	if (topic) {
		if (topic->isChanged) {
			topic->isChanged = false;
			return;
		}

		qCDebug(VehicleTelemetryLog) << "Message received from '" << topic->name << "':" << message;

		// Parsing Json message to propertys
		QJsonDocument doc = QJsonDocument::fromJson(message);
		
		if (!doc.isNull()) {
			QJsonObject json = doc.object();

			topic->message = json;
			topic->isChanged = true;

			// Emit signals
			if (topic->name == DATA_TOPIC) {
				emit _dataTopicChanged();
			}
		} else {
			// Handle the case when the JSON document is null (i.e., the message is not valid JSON)
			qCWarning(VehicleTelemetryLog) << "Invalid JSON message: " << message;
		}
	}
}

void
VehicleTelemetry::_updateTelemetry(Topic &topic)
{
	if (topic.isChanged) {
		topic.isChanged = false;
		return;
	}

	if (_mqttClient && _mqttClient->state() == QMqttClient::Connected) {
		QJsonDocument doc = QJsonDocument();
		doc.setObject(topic.message);

		//TODO: add qos and retain
		if (_mqttClient->publish(QMqttTopicName(topic.name), doc.toJson()) == -1) {
			qCWarning(VehicleTelemetryLog) << "Failed to publish message from '" << topic.name << "'";
		}

		topic.isChanged = true;
	}
}