#ifndef SOILMOISTURESENSOR_H
#define SOILMOISTURESENSOR_H

#include <QObject>
#include "model/sensors/abstractsensor.h"

class SoilMoistureSensor : public AbstractSensor {

    public:
        SoilMoistureSensor(QString name, QString group, double minValue, double maxValue, QString sensorMaterial, QString depth);
        QString getSensorMaterial();
        QString getDepth();
        void setDepth(QString);
        void setSensorMaterial(QString);
        ~SoilMoistureSensor();
        void acceptShow(SensorVisitorMW* sv) override;
        void acceptEdit(SensorVisitorMW* sv) override;
        void acceptEditData(SensorVisitorSL* sv, QVector<QString> params[]) override;
        QJsonObject toJson() override;

    private:
        QString sensorMaterial;
        QString depth;
};

#endif // SOILMOISTURESENSOR_H
