#ifndef MPAGESENSORCARD_H
#define MPAGESENSORCARD_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <view/components/msensortitlelabel.h>
#include <view/components/minfolabelitalic.h>

class MPageSensorCard : public QWidget {
    Q_OBJECT

    public:
        MPageSensorCard(QString key, QString value);
};

#endif // MPAGESENSORCARD_H
