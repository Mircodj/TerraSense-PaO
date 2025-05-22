#include "model/sensorlogic.h"

SensorLogic::SensorLogic(){
    sensorArray = new QVector<AbstractSensor*>;
}

QVector<AbstractSensor*> SensorLogic::getSensorArray(){
    return *sensorArray;
}

void SensorLogic::addTemperatureSensor(QString nome, QString id, double minVal, double maxVal, QString mountType, QString powerType){
    AbstractSensor *a = new TemperatureSensor(nome, id, minVal, maxVal, mountType, powerType);
    sensorArray->append(a);
}

void SensorLogic::addWaterLevelSensor(QString nome, QString id, double minVal, double maxVal, QString protectionLevel, QString measureMethod){
    AbstractSensor *a = new WaterLevelSensor(nome, id, minVal, maxVal, protectionLevel, measureMethod);
    sensorArray->append(a);
}

void SensorLogic::addSoilMoistureSensor(QString nome, QString id, double minVal, double maxVal, QString sensorMaterial, QString depth){
    AbstractSensor *a = new SoilMoistureSensor(nome, id, minVal, maxVal, sensorMaterial, depth);
    sensorArray->append(a);
}

AbstractSensor* SensorLogic::getLastSensor(){
    return sensorArray->last();
}

void SensorLogic::removeSensor(AbstractSensor* remove){
    sensorArray->remove(sensorArray->indexOf(remove));
}

void SensorLogic::saveToJSON(){
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Configuration", "", "JSON files (*.json)");
    if (!fileName.endsWith(".json", Qt::CaseInsensitive)) {
        fileName += ".json";
    }
    QJsonArray jsonArray;
    for (int i = 0; i<sensorArray->size(); i++) {
        jsonArray.append(sensorArray->at(i)->toJson());
    }
    QJsonDocument jsonDoc(jsonArray);
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox a;
        a.setText("Error: Can't save");
        a.exec();
        return;
    }
    file.write(jsonDoc.toJson());
    file.close();
}

bool SensorLogic::loadFromJSON(){
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Load Configuration", "", "JSON files (*.json)");
    QFile file(fileName);
    if (fileName.isEmpty()) {
        QMessageBox a;
        a.setText("Error: No file selected");
        a.exec();
        return false;
    }
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox a;
        a.setText("Error: Can't open file");
        a.exec();
        return false;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
    if (!jsonDoc.isArray()) {
        QMessageBox a;
        a.setText("Error: JSON configuration not valid");
        a.exec();
        return false;
    }
    QJsonArray jsonArray = jsonDoc.array();
    sensorArray->clear();
    for (const QJsonValue& value : jsonArray) {
        if (value.isObject()) {
            QJsonObject jsonObject = value.toObject();
            if(jsonObject["sensorType"] == "Temperature"){
                sensorArray->append(new TemperatureSensor(jsonObject["name"].toString(), jsonObject["group"].toString(), jsonObject["minValue"].toInt(), jsonObject["maxValue"].toInt(), jsonObject["mountType"].toString(), jsonObject["powerType"].toString()));
            } else if(jsonObject["sensorType"] == "SoilMoisture"){
                sensorArray->append(new SoilMoistureSensor(jsonObject["name"].toString(), jsonObject["group"].toString(), jsonObject["minValue"].toInt(), jsonObject["maxValue"].toInt(), jsonObject["sensorMaterial"].toString(), jsonObject["depth"].toString()));
            } else if(jsonObject["sensorType"] == "WaterLevel"){
                sensorArray->append(new WaterLevelSensor(jsonObject["name"].toString(), jsonObject["group"].toString(), jsonObject["minValue"].toInt(), jsonObject["maxValue"].toInt(), jsonObject["protectionLevel"].toString(), jsonObject["measureMethod"].toString()));
            }
        }
    }
    return true;
}

void SensorLogic::visitEditDataSL(TemperatureSensor* sensor, QVector<QString> params[]){
    for(int i = 0; i<sensorArray->size(); i++){
        sensor->setName((*params)[1]);
        sensor->setGroup((*params)[2]);
        sensor->setMaxValue((*params)[4].toDouble());
        sensor->setMinValue((*params)[3].toDouble());
        sensor->setMountType((*params)[5]);
        sensor->setPowerType((*params)[6]);
        break;
    }
}

void SensorLogic::visitEditDataSL(SoilMoistureSensor* sensor, QVector<QString> params[]){
    for(int i = 0; i<sensorArray->size(); i++){
        sensor->setName((*params)[1]);
        sensor->setGroup((*params)[2]);
        sensor->setMaxValue((*params)[4].toDouble());
        sensor->setMinValue((*params)[3].toDouble());
        sensor->setSensorMaterial((*params)[5]);
        sensor->setDepth((*params)[6]);
        break;
    }
}

void SensorLogic::visitEditDataSL(WaterLevelSensor* sensor, QVector<QString> params[]){
    for(int i = 0; i<sensorArray->size(); i++){
        sensor->setName((*params)[1]);
        sensor->setGroup((*params)[2]);
        sensor->setMaxValue((*params)[4].toDouble());
        sensor->setMinValue((*params)[3].toDouble());
        sensor->setProtectionLevel((*params)[5]);
        sensor->setMeasureMethod((*params)[6]);
        break;
    }
}

void SensorLogic::editSensor(AbstractSensor* sensor, QVector<QString> params[]){
    sensor->acceptEditData(this, params);
}

QLineSeries* SensorLogic::generateData(AbstractSensor* sensor, QString values, QString distributionType){
    QLineSeries* output = new QLineSeries();
    int num = values.mid(0, 2).toInt();
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    if(distributionType == "Random"){
        std::uniform_int_distribution<int> distr(sensor->getMinValue(), sensor->getMaxValue());
        for(int i = 0; i<=num; i++){
            output->append(i, distr(generator));
        }
    } else if(distributionType == "Gaussian"){
        double centro = (sensor->getMaxValue()+sensor->getMinValue())/2;
        double dev = (sensor->getMaxValue()-sensor->getMinValue())*0.05;
        std::normal_distribution<> d(centro, dev);
        std::uniform_int_distribution<int> distr(sensor->getMinValue(), sensor->getMaxValue());
        for(int i = 0; i<=num; i++){
            double temp = d(generator);
            temp = std::max(sensor->getMinValue(), std::min(temp, sensor->getMaxValue()));
            output->append(i, temp);
        }
    } else if(distributionType == "Logarithmic"){
        double min = sensor->getMinValue();
        double max = sensor->getMaxValue();
        std::uniform_real_distribution<> uniform_dist(0.0, 1.0);
        for(int i = 0; i<=num; i++){
            double temp = uniform_dist(generator);
            double logval = std::log(1.0 + temp * (std::exp(max) - std::exp(min)));
            double value = min + (logval - std::log(1.0 + std::exp(min))) / (std::log(1.0 + std::exp(max)) - std::log(1.0 + std::exp(min))) * (max - min);
            value = std::max(min, std::min(value, max));
            output->append(i, value);
        }
    }
    return output;
}
