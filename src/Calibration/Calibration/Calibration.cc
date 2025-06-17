#include "Calibration.h"

#include <QThread>
#include <QtQml/QQmlEngine>
#include <QGCLoggingCategory.h>

QGC_LOGGING_CATEGORY(CalibrationLog, "CalibrationLog")

#define SSH_HOST "192.168.137.11"
#define SSH_PORT 22
#define SSH_USER "orangepi"
// #define SSH_HOST "localhost"
// #define SSH_PORT 22
// #define SSH_USER "bleyn"

Calibration::Calibration(QGCApplication* app, QGCToolbox* toolbox)
	: QGCTool(app, toolbox)
{
	session = new ssh::Session();
	sessionThread = new QThread();

	try {
		session->setOption(SSH_OPTIONS_HOST, SSH_HOST);
		session->setOption(SSH_OPTIONS_PORT, SSH_PORT);
		session->setOption(SSH_OPTIONS_USER, SSH_USER);
		session->setOption(SSH_OPTIONS_PUBKEY_AUTH, 1);
	} catch (ssh::SshException e) {
		qCCritical(CalibrationLog) << "Calibration::Calibration: " << e.getCode() << ": " << e.getError();
	}
}

Calibration::~Calibration()
{
	QObject::connect(sessionThread, &QThread::finished, [this] {
		delete sessionThread;
		delete session;
	});
	disconnect();
}

void
Calibration::setToolbox(QGCToolbox *toolbox)
{
	QGCTool::setToolbox(toolbox);
	QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
	qmlRegisterUncreatableType<Calibration>("QGroundControl.Calibration", 1, 0, "Calibration", "Reference only");

	// connect();
}

void Calibration::connect()
{
	if (_connected || sessionThread->isRunning()) return;

	SessionWorker* worker = new SessionWorker(session);
	worker->moveToThread(sessionThread);

	QObject::connect(sessionThread, &QThread::started, worker, &SessionWorker::connect);
	_connectingWorker(worker);

	sessionThread->start();
}

void Calibration::disconnect()
{
	if (sessionThread->isRunning()) return;

	SessionWorker* worker = new SessionWorker(session);
	worker->moveToThread(sessionThread);

	QObject::connect(sessionThread, &QThread::started, worker, &SessionWorker::disconnect);
	_connectingWorker(worker);

	sessionThread->start();
}

void Calibration::reconnect()
{
	if (sessionThread->isRunning()) return;

	SessionWorker* worker = new SessionWorker(session);
	worker->moveToThread(sessionThread);

	QObject::connect(sessionThread, &QThread::started, worker, &SessionWorker::reconnect);
	_connectingWorker(worker);

	sessionThread->start();
}

void Calibration::exec(QString command)
{
	try {
		ssh::Channel channel = ssh::Channel(*session);
		channel.openSession();
		qCDebug(CalibrationLog) << "Channel openned";

		channel.requestExec(command.toStdString().c_str());

		channel.close();
		qCDebug(CalibrationLog) << "Channel closed";
	} catch (ssh::SshException e) {
		qCCritical(CalibrationLog) << "Calibration::exec(" << command.toStdString().c_str() << "): " << e.getCode() << ": " << e.getError();
	}
}

QString Calibration::execRead(QString command, int timeout)
{
	char buffer[256];
	int nbytes;
	QByteArray data = QByteArray();
	try {
		ssh::Channel channel = ssh::Channel(*session);
		channel.openSession();
		qCDebug(CalibrationLog) << "Channel openned";

		channel.requestExec(command.toStdString().c_str());

		qCDebug(CalibrationLog) << "Read starting...";
		
		nbytes = channel.read(buffer, sizeof(buffer), timeout);
		while (nbytes > 0 || nbytes == SSH_AGAIN) {
			if (nbytes == SSH_AGAIN) {
				qCWarning(CalibrationLog) << "Timeout read data";
			} else {
				data.append(buffer, nbytes);
			}

			nbytes = channel.read(buffer, sizeof(buffer), timeout);
		}

		if (nbytes == SSH_ERROR) {
			qCCritical(CalibrationLog) << "Error: " << session->getError();
			return "";
		}

		qCDebug(CalibrationLog) << "Read finished!";

		channel.close();
		qCDebug(CalibrationLog) << "Channel closed";
	} catch (ssh::SshException e) {
		qCCritical(CalibrationLog) << "Calibration::execRead('" << command.toStdString().c_str() << "'): " << e.getCode() << ": " << e.getError();
		return "";
	}
	
	return data;
}

ExecHandler* Calibration::execReadThread(QString command)
{
	QThread* thread = new QThread();
	ExecWorker* worker = new ExecWorker(session, command);
	worker->moveToThread(thread);
	
	ExecHandler* handler = new ExecHandler(worker);

	QObject::connect(thread, &QThread::started, worker, &ExecWorker::exec);
	QObject::connect(worker, &ExecWorker::finished, handler, &ExecHandler::_finished);
	QObject::connect(worker, &ExecWorker::read, handler, &ExecHandler::_read);
	QObject::connect(worker, &ExecWorker::finished, thread, &QThread::quit);
	QObject::connect(thread, &QThread::finished, worker, &QObject::deleteLater);
	QObject::connect(thread, &QThread::finished, handler, &QObject::deleteLater);
	QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);
	QObject::connect(sessionThread, &QThread::finished, thread, &QThread::quit);

	thread->start();
	return handler;
}

void Calibration::_connectingWorker(SessionWorker* worker)
{
	QObject::connect(worker, &SessionWorker::finished, sessionThread, &QThread::quit);
	QObject::connect(worker, &SessionWorker::setConnected, this, &Calibration::setConnected);
	QObject::connect(worker, &SessionWorker::finished, worker, &QObject::deleteLater);
}

SessionWorker::SessionWorker(ssh::Session* session)
	: session(session)
{
}

void SessionWorker::connect()
{
	_connect();
	emit finished();
}

void SessionWorker::disconnect()
{
	_disconnect();
	emit finished();
}

void SessionWorker::reconnect()
{
	_disconnect();
	_connect();
	emit finished();
}

void SessionWorker::_connect()
{
	int code = SSH_AGAIN;
	do {
		try {		
			session->connect();
			session->userauthPublickeyAuto();
			setConnected(true);
			qCDebug(CalibrationLog) << "Session connected";
		} catch (ssh::SshException e) {
			qCCritical(CalibrationLog) << "Calibration::connect: " << e.getCode() << ": " << e.getError();
			code = e.getCode();
		}
	} while (code != SSH_AGAIN);
}

void SessionWorker::_disconnect()
{
	try {
		session->disconnect();
		setConnected(false);
		qCDebug(CalibrationLog) << "Disconnected";
	} catch (ssh::SshException e) {
		qCCritical(CalibrationLog) << "Calibration::disconnect: " << e.getCode() << ": " << e.getError();
	}
}

ExecHandler::ExecHandler(ExecWorker* worker)
	: worker(worker)
{
}

void ExecHandler::stop()
{
	worker->stop();
}

ExecWorker::ExecWorker(ssh::Session* session, QString command)
	: session(session)
	, command(command)
{
}

void ExecWorker::exec()
{
	char buffer[256];
	int nbytes;
	QByteArray data = QByteArray();
	try {
		channel = new ssh::Channel(*session);
		channel->openSession();
		qCDebug(CalibrationLog) << "Channel openned";

		channel->requestExec(command.toStdString().c_str());

		qCDebug(CalibrationLog) << "Read starting...";
		
		// channel->isOpen() && !channel->isEof()
		while (true) {
			nbytes = channel->readNonblocking(buffer, sizeof(buffer));

			if (nbytes < 0) {
				if (nbytes == SSH_ERROR) {
					qCCritical(CalibrationLog) << "Error: " << nbytes;
					channel->close();
					emit finished();
					return;
				}

				break;
			} else if (nbytes > 0) {
				data.append(buffer, nbytes);
				emit read(data);
				data.clear();
			}
		}

		qCDebug(CalibrationLog) << "Read finished!";

		channel->close();
		delete channel;
		qCDebug(CalibrationLog) << "Channel closed";
	} catch (ssh::SshException e) {
		qCCritical(CalibrationLog) << "Calibration::execReadThread('" << command.toStdString().c_str() << "'): " << e.getCode() << ": " << e.getError();
	}

	emit finished();
}

void ExecWorker::stop()
{
	channel->close();
}