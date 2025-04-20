#include "Calibration.h"

#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QtQml/QQmlEngine>
#include <QGCLoggingCategory.h>

QGC_LOGGING_CATEGORY(CalibrationLog, "CalibrationLog")

// Конструктор с правильной сигнатурой
Calibration::Calibration(QGCApplication* app, QGCToolbox* toolbox)
    : QGCTool(app, toolbox) // Вызов базового конструктора QGCTool
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    qmlRegisterUncreatableType<Calibration>("QGroundControl.Calibration", 1, 0, "Calibration", "Reference only");
}

// Реализация метода setToolbox
void Calibration::setToolbox(QGCToolbox* toolbox) {
    QGCTool::setToolbox(toolbox); // Вызов базового метода
}

void Calibration::launchCalibrationApp() {
    // Путь к домашней директории /home/arch
    QString appPath = "/home/arch/Drone_Calibration-x86_64.AppImage";

    // Проверка существования файла
    if (!QFile::exists(appPath)) {
        qCCritical(CalibrationLog) << "Файл не найден: " << appPath;
        return;
    }

    QProcess* process = new QProcess(this);
    process->start(appPath);
}