#include "abstractsensor.h"

AbstractSensor::AbstractSensor(QString name, QString group, double minValue, double maxValue){
    this->name = name;
    this->group = group;
    this->minValue = minValue;
    this->maxValue = maxValue;
}

QString AbstractSensor::getGroup(){ return this->group; }

QString AbstractSensor::getName(){ return this->name; }

double AbstractSensor::getMinValue(){ return this->minValue; }

double AbstractSensor::getMaxValue(){ return this->maxValue; }

void AbstractSensor::setName(QString newName){ this->name = newName; };

void AbstractSensor::setGroup(QString group){ this->group = group; };

void AbstractSensor::setMinValue(double newValue){ this->minValue = newValue; };

void AbstractSensor::setMaxValue(double newValue){ this->maxValue = newValue; };

AbstractSensor::~AbstractSensor(){};
