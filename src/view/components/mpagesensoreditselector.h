#ifndef MPAGESENSOREDITSELECTOR_H
#define MPAGESENSOREDITSELECTOR_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <view/components/msensortitlelabel.h>
#include <view/components/minfolabelitalic.h>
#include <QLineEdit>
#include <QComboBox>

class MPageSensorEditSelector : public QWidget {
    Q_OBJECT

    public:
        MPageSensorEditSelector(QString key);
        QString getValue();
        void addItem(QString item);
        void setItem(QString item);

    private:
        QComboBox *sensorType;

};

#endif // MPAGESENSOREDITSELECTOR_H
