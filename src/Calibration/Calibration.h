#pragma once

#include <QtCore/QObject>
#include <QtCore/QProcess>
#include <QtCore/QLoggingCategory>

#include "QGCToolbox.h" 
#include "QGCApplication.h" // Если нужно доступ к QGCApplication

Q_DECLARE_LOGGING_CATEGORY(CalibrationLog)

class Calibration : public QGCTool // Наследуемся от QGCTool, а не QObject
{
    Q_OBJECT

public:
    explicit Calibration(QGCApplication* app, QGCToolbox* toolbox); // Исправленная сигнатура конструктора
    ~Calibration() override = default;

    void setToolbox(QGCToolbox* toolbox) override; // Объявление метода

public slots:
    void launchCalibrationApp(); // Слот для запуска приложения
};