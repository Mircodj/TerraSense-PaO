#include "mpagesensorcard.h"

MPageSensorCard::MPageSensorCard(QString key, QString value) : QWidget(){
    this->setFixedHeight(60);

    QVBoxLayout *layout = new QVBoxLayout();
    this->setLayout(layout);

    MInfoLabelItalic *keyLabel = new MInfoLabelItalic(key);
    layout->addWidget(keyLabel);

    MSensorTitleLabel *valueLabel = new MSensorTitleLabel(value);
    layout->addWidget(valueLabel);
}
