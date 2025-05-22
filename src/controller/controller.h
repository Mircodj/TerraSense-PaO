#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <view/mainwindow.h>
#include <model/sensorlogic.h>
#include <QDebug>
#include <QString>
#include <QMessageBox>

class Controller : public QObject {
    Q_OBJECT

    public:
        Controller();

    private:
        MainWindow *mainWindow;
        SensorLogic *sensorLogic;
        int numSensori;
        QVector<AbstractSensor*> *sensorChecked;

    public slots:
        void handlerMWButtonClicked(QString msg);
        void handlerMWButtonClickedParams(QString msg, QVector<QString> params[]);
        void handlerMWSensorChecked(AbstractSensor* sens, bool status);
        void handlerMWButtonEdit(QVector<QString> params[], AbstractSensor* dest);
        void handlerMWcreateGraph(QString, QString, AbstractSensor*);

};

#endif // CONTROLLER_H
