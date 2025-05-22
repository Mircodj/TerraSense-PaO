#ifndef MIMAGE_H
#define MIMAGE_H

#include <QLabel>
#include <QPixmap>

class MImage : public QLabel {
    public:
        MImage(QString location);
};

#endif // MIMAGE_H
