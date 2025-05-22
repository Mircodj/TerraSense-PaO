#include "mpagesensoredit.h"

MPageSensorEdit::MPageSensorEdit(QString key, QString value) : QWidget(){
    this->setFixedHeight(68);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    this->setLayout(layout);
    MInfoLabelItalic *keyLabel = new MInfoLabelItalic(key);
    layout->addWidget(keyLabel);
    editLabel = new QLineEdit();
    editLabel->setObjectName("EditSensor");
    editLabel->setFixedSize(250, 32);
    editLabel->setText(value);
    layout->addWidget(editLabel);
}

QString MPageSensorEdit::getValue(){
    return editLabel->text();
}
