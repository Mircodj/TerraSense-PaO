#include "mpagesensoreditselector.h"

MPageSensorEditSelector::MPageSensorEditSelector(QString key) : QWidget(){
    this->setFixedHeight(68);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    this->setLayout(layout);
    MInfoLabelItalic *keyLabel = new MInfoLabelItalic(key);
    layout->addWidget(keyLabel);
    sensorType = new QComboBox();
    sensorType->setFixedSize(250, 32);
    layout->addWidget(sensorType);
}

QString MPageSensorEditSelector::getValue(){
    return sensorType->currentText();
}


void MPageSensorEditSelector::addItem(QString item){
    sensorType->addItem(item);
}

void MPageSensorEditSelector::setItem(QString item){
    int index = sensorType->findText(item);
    sensorType->setCurrentIndex(index);
}
