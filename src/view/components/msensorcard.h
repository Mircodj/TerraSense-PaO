#ifndef MSENSORCARD_H
#define MSENSORCARD_H

#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <view/components/minfolabelitalic.h>
#include <view/components/msensortitlelabel.h>
#include <model/sensors/abstractsensor.h>
#include <QCheckBox>

class MSensorCard : public QWidget {
    public:
        MSensorCard(QWidget *parent = nullptr);
        MSensorCard(AbstractSensor* a);
        QCheckBox* getCheckPointer();
        bool getCheckStatus();
        QString getTitle();
        QString getInfo();
        AbstractSensor* getSensorPointer();
        void updateCard();

    private:
        QCheckBox *checkbox;
        MSensorTitleLabel *titleLabel;
        MInfoLabelItalic *infoLabel;
        AbstractSensor *sensor;
};

#endif // MSENSORCARD_H
