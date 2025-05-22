#ifndef SENSORVISITOR_H
#define SENSORVISITOR_H

#include <QObject>

class SoilMoistureSensor;
class TemperatureSensor;
class WaterLevelSensor;

class SensorVisitorMW {
    public:
        virtual void visitGetDataMW(SoilMoistureSensor*) =0;
        virtual void visitGetDataMW(TemperatureSensor*) =0;
        virtual void visitGetDataMW(WaterLevelSensor*) =0;
        virtual void visitEditDataMW(SoilMoistureSensor*) =0;
        virtual void visitEditDataMW(TemperatureSensor*) =0;
        virtual void visitEditDataMW(WaterLevelSensor*) =0;
};

#endif // SENSORVISITOR_H
