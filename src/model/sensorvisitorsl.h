#ifndef SENSORVISITORSL_H
#define SENSORVISITORSL_H

#include <QObject>

class SoilMoistureSensor;
class TemperatureSensor;
class WaterLevelSensor;

class SensorVisitorSL {
    public:
        virtual void visitEditDataSL(SoilMoistureSensor*, QVector<QString> params[]) =0;
        virtual void visitEditDataSL(TemperatureSensor*, QVector<QString> params[]) =0;
        virtual void visitEditDataSL(WaterLevelSensor*, QVector<QString> params[]) =0;
};

#endif // SENSORVISITORSL_H
