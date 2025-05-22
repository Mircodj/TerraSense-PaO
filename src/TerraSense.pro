QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cpp \
    main.cpp \
    model/sensors/abstractsensor.cpp \
    model/sensorlogic.cpp \
    model/sensors/soilmoisturesensor.cpp \
    model/sensors/temperaturesensor.cpp \
    model/sensors/waterlevelsensor.cpp \
    view/components/mbuttonaccent.cpp \
    view/components/mbuttononw.cpp \
    view/components/mimage.cpp \
    view/components/minfolabel.cpp \
    view/components/minfolabelitalic.cpp \
    view/components/mpagesensorcard.cpp \
    view/components/mpagesensoredit.cpp \
    view/components/mpagesensoreditselector.cpp \
    view/components/msearchbar.cpp \
    view/components/msensorcard.cpp \
    view/components/msensortitlelabel.cpp \
    view/components/mtitlelabel.cpp \
    view/components/mbutton.cpp \
    view/mainwindow.cpp

HEADERS += \
    view/mainwindow.h \
    controller/controller.h \
    model/sensors/abstractsensor.h \
    model/sensorlogic.h \
    model/sensors/soilmoisturesensor.h \
    model/sensors/waterlevelsensor.h \
    model/sensors/temperaturesensor.h \
    model/sensorvisitormv.h \
    model/sensorvisitorsl.h \
    view/components/mbuttonaccent.h \
    view/components/mbuttononw.h \
    view/components/mimage.h \
    view/components/minfolabel.h \
    view/components/minfolabelitalic.h \
    view/components/mpagesensorcard.h \
    view/components/mpagesensoredit.h \
    view/components/mpagesensoreditselector.h \
    view/components/msearchbar.h \
    view/components/msensorcard.h \
    view/components/msensortitlelabel.h \
    view/components/mtitlelabel.h \
    view/components/mbutton.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
