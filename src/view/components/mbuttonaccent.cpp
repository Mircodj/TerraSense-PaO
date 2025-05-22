#include "mbuttonaccent.h"

MButtonAccent::MButtonAccent(QString text) : QPushButton(text){
    this->setObjectName("MButtonAccent");
    this->setFlat(true);
    this->setFixedSize(QSize(250, 32));
}
