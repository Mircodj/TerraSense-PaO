#ifndef MPAGESENSOREDIT_H
#define MPAGESENSOREDIT_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <view/components/msensortitlelabel.h>
#include <view/components/minfolabelitalic.h>
#include <QLineEdit>

class MPageSensorEdit : public QWidget {
    Q_OBJECT

    public:
        MPageSensorEdit(QString key, QString value);
        QString getValue();

    private:
        QLineEdit *editLabel;

};

#endif // MPAGESENSOREDIT_H
