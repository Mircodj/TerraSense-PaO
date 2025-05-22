#include "mbutton.h"

MButton::MButton(QString text) : QPushButton(text){
    this->setObjectName("MButton");
    this->setFixedSize(QSize(110, 32));
}
