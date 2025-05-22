#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <QObject>
#include "model/sensorvisitormv.h"
#include "model/sensorvisitorsl.h"
#include <QJsonObject>

class AbstractSensor {

    public:
        AbstractSensor(QString name, QString group, double minValue, double maxValue);
        QString getName();
        QString getGroup();
        double getMinValue();
        double getMaxValue();
        void setName(QString);
        void setGroup(QString);
        void setMinValue(double);
        void setMaxValue(double);
        virtual ~AbstractSensor() = 0;
        virtual void acceptShow(SensorVisitorMW* sv) = 0;
        virtual void acceptEdit(SensorVisitorMW* sv) = 0;
        virtual void acceptEditData(SensorVisitorSL* sv, QVector<QString> params[]) = 0;
        virtual QJsonObject toJson() = 0;

    private:
        QString name;
        QString group;
        double minValue;
        double maxValue;
};

#endif // ABSTRACTSENSOR_H
