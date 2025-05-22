#ifndef WATERLEVELSENSOR_H
#define WATERLEVELSENSOR_H

#include <QObject>
#include "model/sensors/abstractsensor.h"

class WaterLevelSensor : public AbstractSensor {

    public:
        WaterLevelSensor(QString name, QString group, double minValue, double maxValue, QString protectionLevel, QString measureMethod);
        QString getProtectionLevel();
        QString getMeasureMethod();
        void setProtectionLevel(QString);
        void setMeasureMethod(QString);
        ~WaterLevelSensor();
        void acceptShow(SensorVisitorMW* sv) override;
        void acceptEdit(SensorVisitorMW* sv) override;
        void acceptEditData(SensorVisitorSL* sv, QVector<QString> params[]) override;
        QJsonObject toJson() override;

    private:
        QString protectionLevel;
        QString measureMethod;
};

#endif // WATERLEVELSENSOR_H
