#include "model/sensors/waterlevelsensor.h"

WaterLevelSensor::WaterLevelSensor(QString name, QString group = "T001", double minValue = -20, double maxValue = 85, QString protectionLevel = "NA", QString measureMethod = "NA") : AbstractSensor(name, group, minValue, maxValue){
    this->protectionLevel = protectionLevel;
    this->measureMethod = measureMethod;
};

QString WaterLevelSensor::getProtectionLevel(){ return this->protectionLevel; }

QString WaterLevelSensor::getMeasureMethod(){ return this->measureMethod; }

void WaterLevelSensor::setProtectionLevel(QString protectionLevel){ this->protectionLevel = protectionLevel; };

void WaterLevelSensor::setMeasureMethod(QString measureMethod){ this->measureMethod = measureMethod; };

WaterLevelSensor::~WaterLevelSensor(){}

void WaterLevelSensor::acceptShow(SensorVisitorMW* sv){
    sv->visitGetDataMW(this);
}

QJsonObject WaterLevelSensor::toJson(){
    QJsonObject json;
    json["sensorType"] = "WaterLevel";
    json["name"] = this->getName();
    json["group"] = this->getGroup();
    json["minValue"] = this->getMinValue();
    json["maxValue"] = this->getMaxValue();
    json["protectionLevel"] = this->getProtectionLevel();
    json["measureMethod"] = this->getMeasureMethod();
    return json;
}

void WaterLevelSensor::acceptEdit(SensorVisitorMW* sv){
    sv->visitEditDataMW(this);
}

void WaterLevelSensor::acceptEditData(SensorVisitorSL* sv, QVector<QString> params[]){
    sv->visitEditDataSL(this, params);
}

