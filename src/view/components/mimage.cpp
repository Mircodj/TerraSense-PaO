#include "mimage.h"

MImage::MImage(QString location) {
    QPixmap *image = new QPixmap(location);
    this->setPixmap(*image);
}
