#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <QObject>
#include "model/sensors/abstractsensor.h"

class TemperatureSensor : public AbstractSensor {

    public:
        TemperatureSensor(QString name, QString group, double minValue, double maxValue, QString mountType, QString powerType);
        QString getMountType();
        QString getPowerType();
        void setPowerType(QString);
        void setMountType(QString);
        ~TemperatureSensor();
        void acceptShow(SensorVisitorMW* sv) override;
        void acceptEdit(SensorVisitorMW* sv) override;
        void acceptEditData(SensorVisitorSL* sv, QVector<QString> params[]) override;
        QJsonObject toJson() override;

    private:
        QString mountType;
        QString powerType;
};

#endif // TEMPERATURESENSOR_H
