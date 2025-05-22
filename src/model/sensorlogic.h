#ifndef SENSORLOGIC_H
#define SENSORLOGIC_H

#include <QObject>
#include <model/sensors/abstractsensor.h>
#include <model/sensors/temperaturesensor.h>
#include <model/sensors/waterlevelsensor.h>
#include <model/sensors/soilmoisturesensor.h>
#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <random>
#include <QLineSeries>
#include <QMessageBox>

class SensorLogic : public SensorVisitorSL {
    public:
        SensorLogic();
        void addTemperatureSensor(QString nome, QString group, double minVal, double maxVal, QString mountType, QString powerType);
        void addWaterLevelSensor(QString nome, QString group, double minVal, double maxVal, QString protectionLevel, QString measureMethod);
        void addSoilMoistureSensor(QString nome, QString group, double minVal, double maxVal, QString sensorMaterial, QString depth);
        AbstractSensor* getLastSensor();
        void removeSensor(AbstractSensor*);
        void saveToJSON();
        bool loadFromJSON();
        QVector<AbstractSensor*> getSensorArray();
        void editSensor(AbstractSensor* sens, QVector<QString> params[]);
        void visitEditDataSL(SoilMoistureSensor*, QVector<QString> params[]) override;
        void visitEditDataSL(TemperatureSensor*, QVector<QString> params[]) override;
        void visitEditDataSL(WaterLevelSensor*, QVector<QString> params[]) override;
        QLineSeries* generateData(AbstractSensor*, QString, QString);

    private:
        QVector<AbstractSensor*> *sensorArray;
};

#endif // SENSORLOGIC_H
