#pragma once

#include <libssh/libsshpp.hpp>
#include <QtCore/QObject>
#include <QtCore/QLoggingCategory>

#include "QGCToolbox.h"

Q_DECLARE_LOGGING_CATEGORY(CalibrationLog)

class SessionWorker;
class ExecWorker;
class ExecHandler;

class Calibration : public QGCTool
{
	Q_OBJECT

    Q_PROPERTY(bool		connected	READ	connected	NOTIFY	connectedChanged)

public:
	Calibration(QGCApplication* app, QGCToolbox* toolbox);
	virtual ~Calibration();

	void setToolbox(QGCToolbox *toolbox) override;

	Q_INVOKABLE void			connect();
	Q_INVOKABLE void			disconnect();
	Q_INVOKABLE void			reconnect();

	Q_INVOKABLE void			exec(QString command);
	Q_INVOKABLE QString			execRead(QString command, int timeout = -1); //! Block thread!
	Q_INVOKABLE ExecHandler*	execReadThread(QString command);

public slots:
	bool 		connected()		{ return _connected; };

private slots:
	void setConnected(bool connected) 				{ _connected = connected; emit connectedChanged(); }
	
	void _connectingWorker(SessionWorker* worker);

signals:
	void connectedChanged();

private:
	ssh::Session*	session			= nullptr;
	QThread*		sessionThread	= nullptr;
	
	bool			_connected		= false;
};

class SessionWorker : public QObject
{
	Q_OBJECT

public:
	SessionWorker(ssh::Session* session);

public slots:
	void connect();
	void disconnect();
	void reconnect();

private:
	void _connect();
	void _disconnect();

signals:
	void finished();
	void setConnected(bool connected);
	
private:
	ssh::Session* session	= nullptr;
};

class ExecHandler : public QObject
{
	Q_OBJECT

	friend Calibration;
private:
	ExecHandler(ExecWorker* worker);

	void _finished() { emit finished(); }
	void _read(QByteArray buffer) { emit read(buffer); }

public slots:
	void stop();

signals:
	void finished();
	void read(QByteArray buffer);

private:
	ExecWorker*		worker	= nullptr;
};

class ExecWorker : public QObject
{
	Q_OBJECT

public:
	ExecWorker(ssh::Session* session, QString command);

public slots:
	void exec();
	void stop();

signals:
	void finished();
	void read(QByteArray buffer);

private:
	ssh::Session* 	session	= nullptr;
	ssh::Channel*	channel = nullptr;
	QString			command = "";
};