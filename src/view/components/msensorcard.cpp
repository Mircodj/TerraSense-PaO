#include "msensorcard.h"


MSensorCard::MSensorCard(AbstractSensor* a){
    QFrame *frame = new QFrame(this);
    frame->setFixedSize(230, 60);
    this->setMinimumSize(230, 60);
    frame->setStyleSheet("background-color: white; border-radius: 6px;");

    sensor = a;

    titleLabel = new MSensorTitleLabel(sensor->getName());
    infoLabel = new MInfoLabelItalic(sensor->getGroup());

    checkbox = new QCheckBox(frame);

    QGridLayout *layout = new QGridLayout(frame);
    layout->addWidget(titleLabel, 0, 0);
    layout->addWidget(infoLabel, 1, 0);
    layout->addWidget(checkbox, 0, 1, Qt::AlignRight | Qt::AlignTop);
}

QCheckBox* MSensorCard::getCheckPointer(){
    return checkbox;
}

bool MSensorCard::getCheckStatus(){
    return checkbox->isChecked();
}

QString MSensorCard::getTitle(){
    return titleLabel->text();
}

QString MSensorCard::getInfo(){
    return infoLabel->text();
}

AbstractSensor* MSensorCard::getSensorPointer(){
    return sensor;
}

void MSensorCard::updateCard(){
    titleLabel->setText(sensor->getName());
    infoLabel->setText(sensor->getGroup());
}




