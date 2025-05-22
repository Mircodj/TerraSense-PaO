#include "mbuttononw.h"

MButtonOnW::MButtonOnW(QString text) : QPushButton(text){
    this->setObjectName("MButtonOnW");
    this->setFixedSize(QSize(110, 32));
}
