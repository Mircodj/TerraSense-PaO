#include "model/sensors/soilmoisturesensor.h"

SoilMoistureSensor::SoilMoistureSensor(QString name, QString group = "T001", double minValue = -20, double maxValue = 85, QString sensorMaterial = "NA", QString depth = "10cm") : AbstractSensor(name, group, minValue, maxValue){
    this->sensorMaterial = sensorMaterial;
    this->depth = depth;
};

QString SoilMoistureSensor::getDepth(){ return this->depth; }

QString SoilMoistureSensor::getSensorMaterial(){ return this->sensorMaterial; }

void SoilMoistureSensor::setDepth(QString depth){ this->depth = depth; };

void SoilMoistureSensor::setSensorMaterial(QString sensorMaterial){ this->sensorMaterial = sensorMaterial; };

SoilMoistureSensor::~SoilMoistureSensor(){}

void SoilMoistureSensor::acceptShow(SensorVisitorMW* sv){
    sv->visitGetDataMW(this);
}

QJsonObject SoilMoistureSensor::toJson(){
    QJsonObject json;
    json["sensorType"] = "SoilMoisture";
    json["name"] = this->getName();
    json["group"] = this->getGroup();
    json["minValue"] = this->getMinValue();
    json["maxValue"] = this->getMaxValue();
    json["sensorMaterial"] = this->getSensorMaterial();
    json["depth"] = this->getDepth();
    return json;
}

void SoilMoistureSensor::acceptEdit(SensorVisitorMW* sv){
    sv->visitEditDataMW(this);
}

void SoilMoistureSensor::acceptEditData(SensorVisitorSL* sv, QVector<QString> params[]){
    sv->visitEditDataSL(this, params);
}

