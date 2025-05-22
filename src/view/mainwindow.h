#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QScrollArea>
#include <QDebug>
#include <QtCharts>
#include <model/sensors/abstractsensor.h>
#include <model/sensors/temperaturesensor.h>
#include <model/sensors/waterlevelsensor.h>
#include <model/sensors/soilmoisturesensor.h>
#include <view/components/mtitlelabel.h>
#include <view/components/msearchbar.h>
#include <view/components/msensorcard.h>
#include <view/components/minfolabel.h>
#include <view/components/minfolabelitalic.h>
#include <view/components/mbutton.h>
#include <view/components/mbuttonaccent.h>
#include <view/components/mimage.h>
#include <view/components/mtitlelabel.h>
#include <QComboBox>
#include <QMessageBox>
#include <view/components/mpagesensorcard.h>
#include <view/components/mpagesensoredit.h>
#include <view/components/mpagesensoreditselector.h>
#include <view/components/mbuttononw.h>

class MainWindow : public QMainWindow, SensorVisitorMW {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void updateButtonLayout(int numSensorSelected = 0);
        void initialScreen();
        void moreThan2SensorScreen();
        void showSensorScreen(AbstractSensor*);
        void addSensorScreen();;
        void addSensorToList(AbstractSensor* a);
        void clearSensorList();
        void removeSensorList(AbstractSensor* a);
        void visitGetDataMW(TemperatureSensor*) override;
        void visitGetDataMW(SoilMoistureSensor*) override;
        void visitGetDataMW(WaterLevelSensor*) override;
        void showGraphView(QLineSeries*, AbstractSensor*);
        void addGraphControls(QHBoxLayout*, AbstractSensor*);
        void editSensorScreen(AbstractSensor*);
        void visitEditDataMW(TemperatureSensor*) override;
        void visitEditDataMW(SoilMoistureSensor*) override;
        void visitEditDataMW(WaterLevelSensor*) override;
        void updateSensorCard(AbstractSensor* sensor);
        void disableSave();
        void enableSave();

    private:
        //Main Layout
        int numSensori = 0;
        QWidget *mainLayoutContainer;
        QGridLayout *mainLayout;
        
        //Layout SX
        QFrame *fullSx;
        QGridLayout *leftSpace;
        QLineEdit *searchBarP;
        QString sensorType;

        //Alto a DX
        QFrame *altoDx;
        QHBoxLayout *infoLayout;
        MInfoLabel *itemsSelected;
        MInfoLabel *programName;  
        MSearchBar *searchBar;
        QScrollArea *scrollArea;
        QFrame *cardContainer;
        QVBoxLayout *cardContainerLay;
        QVector<MSensorCard*> *cardArray;


        //Centro a DX
        QFrame *centroDx;

        //Basso a DX
        QFrame *bassoDx;
        QGridLayout *menuLayout; 
        MImage *configImage;
        MImage *sensorImage;
        MButton *saveButton;
        MButton *loadButton;
        MButton *addButton;
        MButton *removeButton;
        MButton *editButton;

        //Funzioni Utils
        void MWSearchHandler();

    signals:
        void MWButtonClicked(QString msg);
        void MWButtonClickedParams(QString msg, QVector<QString> params[]);
        void MWSensorChecked(AbstractSensor* sens, bool checkStatus);
        void MWSearchText(QString searchTerm);
        void MWButtonEdit(QVector<QString> params[], AbstractSensor* sensor);
        void MWcreateGraph(QString, QString, AbstractSensor*);
};

#endif // MAINWINDOW_H
