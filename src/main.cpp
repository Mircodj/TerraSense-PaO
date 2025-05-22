#include "view/mainwindow.h"

#include <QApplication>
#include <QFontDatabase>
#include <controller/controller.h>

int main(int argc, char *argv[]){
    qputenv("QT_ASSUME_STDERR_HAS_CONSOLE", "1");
    qputenv("XDG_SESSION_TYPE", "xdg");
    QApplication a(argc, argv);

    //Applico QSS Stylesheet
    QFile file(":/qss/resources/main.qss");
    bool bOpened = file.open(QFile::ReadOnly);
    assert (bOpened == true);
    QString QSSMain = QLatin1String(file.readAll());
    a.setStyleSheet(QSSMain);

    //Carico Font
    QFontDatabase::addApplicationFont(":/fonts/resources/Gilroy-Medium.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/Gilroy-MediumItalic.ttf");

    Controller controller;

    return a.exec();
}
