#include "controller.h"

Controller::Controller(){
    mainWindow = new MainWindow();
    mainWindow->resize(900, 600);
    mainWindow->setMinimumSize(900, 600);
    mainWindow->setWindowTitle("TerraSense v0.1");
    mainWindow->show();
    connect(mainWindow, &MainWindow::MWButtonClicked, this, &Controller::handlerMWButtonClicked);
    connect(mainWindow, &MainWindow::MWButtonClickedParams, this, &Controller::handlerMWButtonClickedParams);
    connect(mainWindow, &MainWindow::MWSensorChecked, this, &Controller::handlerMWSensorChecked);
    connect(mainWindow, &MainWindow::MWButtonEdit, this, &Controller::handlerMWButtonEdit);
    connect(mainWindow, &MainWindow::MWcreateGraph, this, &Controller::handlerMWcreateGraph);
    mainWindow->updateButtonLayout(0);
    sensorLogic = new SensorLogic();
    sensorChecked = new QVector<AbstractSensor*>;
    mainWindow->disableSave();
}



void Controller::handlerMWButtonClicked(QString msg){
    if(msg == "Load"){
        bool result = sensorLogic->loadFromJSON();
        if(result == true){
            mainWindow->clearSensorList();
            for(int i = 0; i<sensorLogic->getSensorArray().size(); i++){
                mainWindow->addSensorToList(sensorLogic->getSensorArray().at(i));
            }
        }
        mainWindow->enableSave();
    }
    if(msg == "Add"){
        mainWindow->addSensorScreen();
    }
    if(msg == "Save")
        sensorLogic->saveToJSON();
    if(msg == "Edit")
        mainWindow->editSensorScreen(sensorChecked->at(0));
    if(msg == "Remove"){
        int size = sensorChecked->size();
        for(int i = 0; i<size; i++){
            sensorLogic->removeSensor(sensorChecked->at(i));
            mainWindow->removeSensorList(sensorChecked->at(i));
        }
        delete(sensorChecked);
        sensorChecked = new QVector<AbstractSensor*>;
        mainWindow->initialScreen();
        mainWindow->updateButtonLayout(0);
        if(sensorLogic->getSensorArray().size()==0){
            mainWindow->disableSave();
        } else {
            mainWindow->enableSave();
        }
    }
}



void Controller::handlerMWButtonClickedParams(QString msg, QVector<QString> params[]){
    if(msg == "AddSensorSave"){
        if((*params)[0] == "Temperature Sensor"){
            sensorLogic->addTemperatureSensor((*params)[1], (*params)[2], (*params)[3].toDouble(), (*params)[4].toDouble(), (*params)[5], (*params)[6]);
            mainWindow->addSensorToList(sensorLogic->getLastSensor());
        } else if((*params)[0] == "Water Level Sensor"){
            sensorLogic->addWaterLevelSensor((*params)[1], (*params)[2], (*params)[3].toDouble(), (*params)[4].toDouble(), (*params)[5], (*params)[6]);
            mainWindow->addSensorToList(sensorLogic->getLastSensor());
        } else if((*params)[0] == "Soil Moisture Sensor"){
            sensorLogic->addSoilMoistureSensor((*params)[1], (*params)[2], (*params)[3].toDouble(), (*params)[4].toDouble(), (*params)[5], (*params)[6]);
            mainWindow->addSensorToList(sensorLogic->getLastSensor());
        }
    }
    mainWindow->enableSave();
}



void Controller::handlerMWSensorChecked(AbstractSensor* a, bool status){
    if(status == true){
        sensorChecked->append(a);
    } else if(status == false){
        sensorChecked->removeOne(a);
    }
    if(sensorChecked->size() == 0){
        mainWindow->initialScreen();
    } else if(sensorChecked->size()  == 1){
        mainWindow->showSensorScreen(sensorChecked->at(0));
    } else if(sensorChecked->size() > 1){
        mainWindow->moreThan2SensorScreen();
    }
    mainWindow->updateButtonLayout(sensorChecked->size());
}



void Controller::handlerMWButtonEdit(QVector<QString> params[], AbstractSensor* dest){
    sensorLogic->editSensor(dest, params);
    mainWindow->updateSensorCard(dest);
    mainWindow->showSensorScreen(sensorChecked->at(0));
}



void Controller::handlerMWcreateGraph(QString values, QString distributionType, AbstractSensor* sensor){
    mainWindow->showGraphView(sensorLogic->generateData(sensor, values, distributionType), sensor);
}

