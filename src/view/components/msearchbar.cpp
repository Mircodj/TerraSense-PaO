#include "msearchbar.h"

MSearchBar::MSearchBar() {
    QFrame *frame = new QFrame(this);
    frame->setFixedSize(250, 36);
    this->setFixedSize(270, 46);
    frame->setStyleSheet("background-color: white; border-radius: 6px;");

    QPixmap *searchImage = new QPixmap(":/img/resources/searchIcon.svg");
    QLabel *searchSpace = new QLabel("");
    searchSpace->setPixmap(*searchImage);

    lineedit = new QLineEdit();
    lineedit->setPlaceholderText("Search...");

    QGridLayout *layout = new QGridLayout(frame);
    layout->addWidget(searchSpace, 0, 0);
    layout->addWidget(lineedit, 0, 1);
}

QLineEdit* MSearchBar::getSearchBar(){
    return lineedit;
}

QString MSearchBar::getSearchText(){
    return lineedit->text();
}
