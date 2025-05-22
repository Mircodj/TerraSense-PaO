#include "model/sensors/temperaturesensor.h"

TemperatureSensor::TemperatureSensor(QString name, QString group = "T001", double minValue = -20, double maxValue = 85, QString mountType = "NA", QString powerType = "NA") : AbstractSensor(name, group, minValue, maxValue){
    this->powerType = powerType;
    this->mountType = mountType;
};

QString TemperatureSensor::getMountType(){ return this->mountType; }

QString TemperatureSensor::getPowerType(){ return this->powerType; }

void TemperatureSensor::setMountType(QString mountType){ this->mountType = mountType; };

void TemperatureSensor::setPowerType(QString powerType){ this->powerType = powerType; };

TemperatureSensor::~TemperatureSensor(){}

void TemperatureSensor::acceptShow(SensorVisitorMW* sv){
    sv->visitGetDataMW(this);
}

QJsonObject TemperatureSensor::toJson(){
    QJsonObject json;
    json["sensorType"] = "Temperature";
    json["name"] = this->getName();
    json["group"] = this->getGroup();
    json["minValue"] = this->getMinValue();
    json["maxValue"] = this->getMaxValue();
    json["mountType"] = this->getMountType();
    json["powerType"] = this->getPowerType();
    return json;
}

void TemperatureSensor::acceptEdit(SensorVisitorMW* sv){
    sv->visitEditDataMW(this);
}

void TemperatureSensor::acceptEditData(SensorVisitorSL* sv, QVector<QString> params[]){
    sv->visitEditDataSL(this, params);
}
