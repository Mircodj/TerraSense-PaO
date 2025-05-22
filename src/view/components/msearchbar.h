#ifndef MSEARCHBAR_H
#define MSEARCHBAR_H

#include <QWidget>
#include <QFrame>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>

class MSearchBar : public QWidget {
    public:
        MSearchBar();
        QLineEdit* getSearchBar();
        QString getSearchText();

    private:
        QLineEdit *lineedit;
};

#endif // MSEARCHBAR_H
