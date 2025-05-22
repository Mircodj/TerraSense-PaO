#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    numSensori = 0;
    cardArray = new QVector<MSensorCard*>;



    // ------------------ Main Layout ------------------
    mainLayoutContainer = new QWidget();
    this->setCentralWidget(mainLayoutContainer);
    mainLayout = new QGridLayout(mainLayoutContainer);



    // ------------------ Layout SX ------------------
    fullSx = new QFrame();
    fullSx->setFixedWidth(270);
    mainLayout->addWidget(fullSx, 0, 0, 3, 1);
    leftSpace = new QGridLayout(fullSx);
    searchBar = new MSearchBar();
    searchBarP = searchBar->getSearchBar();
    leftSpace->addWidget(searchBar, 0, 0);
    connect(searchBarP, &QLineEdit::textChanged, this, [this]()->void{
        MWSearchHandler();
    });
    scrollArea = new QScrollArea();
    scrollArea->setFrameShape(QFrame::NoFrame);
    cardContainer = new QFrame();
    cardContainer->setStyleSheet("background-color: #EDEEEF");
    cardContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    cardContainer->setFixedSize(230, numSensori*70);
    scrollArea->setWidget(cardContainer);
    cardContainerLay = new QVBoxLayout(cardContainer);
    cardContainerLay->setSpacing(10);
    cardContainerLay->setContentsMargins(0, 0, 0, 0);
    cardContainerLay->setAlignment(Qt::AlignTop);
    cardContainer->setLayout(cardContainerLay);
    leftSpace->addWidget(scrollArea, 1, 0);



    // ------------------ Layout in alto a DX ------------------
    altoDx = new QFrame();
    //altoDx->setFixedSize(590, 56);
    altoDx->setFixedHeight(56);
    infoLayout = new QHBoxLayout(altoDx);
    //itemsSelected = new MInfoLabel("Item Selected: 0");
    programName = new MInfoLabel("TerraSense v0.1 ALPHA");
    //infoLayout->addWidget(itemsSelected);
    infoLayout->addStretch();
    infoLayout->addWidget(programName);
    mainLayout->addWidget(altoDx, 0, 1);



    // ------------------ Layout in centro a DX ------------------
    centroDx = new QFrame();
    centroDx->setMinimumSize(590, 400);
    centroDx->setObjectName("Pannello");
    mainLayout->addWidget(centroDx, 1, 1);



    // ------------------ Layout in basso a DX ------------------
    bassoDx = new QFrame();
    bassoDx->setFixedHeight(84);
    bassoDx->setFixedWidth(590);
    menuLayout = new QGridLayout(bassoDx);
    menuLayout->setHorizontalSpacing(10);
    configImage = new MImage(":/img/resources/ConfigImg.png");
    menuLayout->addWidget(configImage, 0, 0, 1, 2);
    sensorImage = new MImage(":/img/resources/SensorsImg.png");
    menuLayout->addWidget(sensorImage, 0, 2, 1, 3);
    saveButton = new MButton("Save");
    saveButton->setShortcut(Qt::CTRL | Qt::Key_S);
    loadButton = new MButton("Load");
    loadButton->setShortcut(Qt::CTRL | Qt::Key_L);
    addButton = new MButton("Add");
    addButton->setShortcut(Qt::CTRL | Qt::Key_A);
    removeButton = new MButton("Remove");
    removeButton->setShortcut(Qt::CTRL | Qt::Key_R);
    editButton = new MButton("Edit");
    editButton->setShortcut(Qt::CTRL | Qt::Key_E);
    menuLayout->addWidget(saveButton, 1, 0);
    menuLayout->addWidget(loadButton, 1, 1);
    menuLayout->addWidget(addButton, 1, 2);
    menuLayout->addWidget(removeButton, 1, 3);
    menuLayout->addWidget(editButton, 1, 4);
    mainLayout->addWidget(bassoDx, 2, 1, Qt::AlignHCenter);
    connect(saveButton, &QPushButton::clicked, this, [this]()->void{
        emit MWButtonClicked("Save");
    });
    connect(loadButton, &QPushButton::clicked, this, [this]()->void{
        emit MWButtonClicked("Load");
    });
    connect(addButton, &QPushButton::clicked, this, [this]()->void{
        emit MWButtonClicked("Add");
    });
    connect(removeButton, &QPushButton::clicked, this, [this]()->void{
        emit MWButtonClicked("Remove");
    });
    connect(editButton, &QPushButton::clicked, this, [this]()->void{
        emit MWButtonClicked("Edit");
    });
    this->setFocus();
}



void MainWindow::updateButtonLayout(int numSensorSelected){
    if(numSensorSelected == 0){
        removeButton->setDisabled(true);
        editButton->setDisabled(true);
        initialScreen();
    } else if(numSensorSelected >= 2){
        editButton->setDisabled(true);
        moreThan2SensorScreen();
    } else {
        loadButton->setDisabled(false);
        addButton->setDisabled(false);
        removeButton->setDisabled(false);
        editButton->setDisabled(false);
    }
    this->update();
}



void MainWindow::enableSave(){
    saveButton->setDisabled(false);
}

void MainWindow::disableSave(){
    saveButton->setDisabled(true);
}



MainWindow::~MainWindow() {}



void MainWindow::initialScreen(){
    delete(centroDx);
    centroDx = new QFrame();
    centroDx->setMinimumSize(590, 400);
    centroDx->setObjectName("Pannello");
    mainLayout->addWidget(centroDx, 1, 1);
    QBoxLayout *middle = new QVBoxLayout(centroDx);
    MTitleLabel *text = new MTitleLabel("Load a Configuration /\nSelect or Add a Sensor to start...");
    text->setAlignment(Qt::AlignCenter);
    middle->addWidget(text);
}



void MainWindow::moreThan2SensorScreen(){
    delete(centroDx);
    centroDx = new QFrame();
    centroDx->setMinimumSize(590, 400);
    centroDx->setObjectName("Pannello");
    mainLayout->addWidget(centroDx, 1, 1);
    QBoxLayout *middle = new QVBoxLayout(centroDx);
    MTitleLabel *text = new MTitleLabel("More than a Sensor selected");
    text->setAlignment(Qt::AlignCenter);
    middle->addWidget(text);
}



void MainWindow::showSensorScreen(AbstractSensor* sensor){
    sensor->acceptShow(this);
}



void MainWindow::visitGetDataMW(TemperatureSensor *sens){
    delete(centroDx);
    centroDx = new QFrame();
    centroDx->setObjectName("Pannello");
    centroDx->setMinimumSize(590, 400);
    mainLayout->addWidget(centroDx, 1, 1);
    QGridLayout *middle = new QGridLayout(centroDx);
    QWidget *topContainer = new QWidget();
    QHBoxLayout *topLayout = new QHBoxLayout(topContainer);
    topContainer->setFixedHeight(40);
    MTitleLabel *title = new MTitleLabel(sens->getName());
    title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    topLayout->addWidget(title);
    middle->addWidget(topContainer, 0, 0);
    QFrame *mainElement = new QFrame();
    QGridLayout *internalLayout = new QGridLayout(mainElement);
    internalLayout->setContentsMargins(0, 0, 0, 0);
    internalLayout->addWidget(new MPageSensorCard("Type", "Temperature Sensor"), 0, 0);
    internalLayout->addWidget(new MPageSensorCard("Group", sens->getGroup()), 0, 1);
    internalLayout->addWidget(new MPageSensorCard("Minimum Value", QString::number(sens->getMinValue())), 1, 0);
    internalLayout->addWidget(new MPageSensorCard("Maximum Value", QString::number(sens->getMaxValue())), 1, 1);
    internalLayout->addWidget(new MPageSensorCard("Mount Type", sens->getMountType()), 2, 0);
    internalLayout->addWidget(new MPageSensorCard("Power Type", sens->getPowerType()), 2, 1);
    internalLayout->setAlignment(Qt::AlignTop);
    middle->addWidget(mainElement, 1, 0);
    QWidget *bottomContainer = new QWidget();
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomContainer);
    bottomContainer->setFixedHeight(60);
    bottomLayout->addStretch(0);
    middle->addWidget(bottomContainer, 2, 0);
    addGraphControls(bottomLayout, sens);

}


void MainWindow::visitGetDataMW(WaterLevelSensor *sens){
    delete(centroDx);
    centroDx = new QFrame();
    centroDx->setObjectName("Pannello");
    centroDx->setMinimumSize(590, 400);
    mainLayout->addWidget(centroDx, 1, 1);
    QGridLayout *middle = new QGridLayout(centroDx);
    QWidget *topContainer = new QWidget();
    QHBoxLayout *topLayout = new QHBoxLayout(topContainer);
    topContainer->setFixedHeight(40);
    MTitleLabel *title = new MTitleLabel(sens->getName());
    title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    topLayout->addWidget(title);
    middle->addWidget(topContainer, 0, 0);
    QFrame *mainElement = new QFrame();
    QGridLayout *internalLayout = new QGridLayout(mainElement);
    internalLayout->setContentsMargins(0, 0, 0, 0);
    internalLayout->addWidget(new MPageSensorCard("Type", "Water Level Sensor"), 0, 0);
    internalLayout->addWidget(new MPageSensorCard("Group", sens->getGroup()), 0, 1);
    internalLayout->addWidget(new MPageSensorCard("Minimum Value", QString::number(sens->getMinValue())), 1, 0);
    internalLayout->addWidget(new MPageSensorCard("Maximum Value", QString::number(sens->getMaxValue())), 1, 1);
    internalLayout->addWidget(new MPageSensorCard("Protection Level", sens->getProtectionLevel()), 2, 0);
    internalLayout->addWidget(new MPageSensorCard("Measure Type", sens->getMeasureMethod()), 2, 1);
    internalLayout->setAlignment(Qt::AlignTop);
    middle->addWidget(mainElement, 1, 0);
    QWidget *bottomContainer = new QWidget();
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomContainer);
    bottomContainer->setFixedHeight(60);
    bottomLayout->addStretch(0);
    middle->addWidget(bottomContainer, 2, 0);
    addGraphControls(bottomLayout, sens);
}



void MainWindow::visitGetDataMW(SoilMoistureSensor *sens){
    delete(centroDx);
    centroDx = new QFrame();
    centroDx->setObjectName("Pannello");
    centroDx->setMinimumSize(590, 400);
    mainLayout->addWidget(centroDx, 1, 1);
    QGridLayout *middle = new QGridLayout(centroDx);
    QWidget *topContainer = new QWidget();
    QHBoxLayout *topLayout = new QHBoxLayout(topContainer);
    topContainer->setFixedHeight(40);
    MTitleLabel *title = new MTitleLabel(sens->getName());
    title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    topLayout->addWidget(title);
    middle->addWidget(topContainer, 0, 0);
    QFrame *mainElement = new QFrame();
    QGridLayout *internalLayout = new QGridLayout(mainElement);
    internalLayout->setContentsMargins(0, 0, 0, 0);
    internalLayout->addWidget(new MPageSensorCard("Type", "Soil Moisture Sensor"), 0, 0);
    internalLayout->addWidget(new MPageSensorCard("Group", sens->getGroup()), 0, 1);
    internalLayout->addWidget(new MPageSensorCard("Minimum Value", QString::number(sens->getMinValue())), 1, 0);
    internalLayout->addWidget(new MPageSensorCard("Maximum Value", QString::number(sens->getMaxValue())), 1, 1);
    internalLayout->addWidget(new MPageSensorCard("Protection Level", sens->getSensorMaterial()), 2, 0);
    internalLayout->addWidget(new MPageSensorCard("Measure Type", sens->getDepth()), 2, 1);
    internalLayout->setAlignment(Qt::AlignTop);
    middle->addWidget(mainElement, 1, 0);
    QWidget *bottomContainer = new QWidget();
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomContainer);
    bottomContainer->setFixedHeight(60);
    bottomLayout->addStretch(0);
    middle->addWidget(bottomContainer, 2, 0);
    addGraphControls(bottomLayout, sens);
}


void MainWindow::addGraphControls(QHBoxLayout *bottomLayout, AbstractSensor* sens){
    QComboBox *graphType = new QComboBox();
    graphType->setFixedSize(150, 32);
    graphType->addItem("10 Values");
    graphType->addItem("20 Values");
    graphType->addItem("30 Values");
    bottomLayout->addWidget(graphType, Qt::AlignLeft);
    QComboBox *temp = new QComboBox();
    temp->setFixedSize(150, 32);
    temp->addItem("Gaussian");
    temp->addItem("Random");
    temp->addItem("Logarithmic");
    bottomLayout->addWidget(temp, Qt::AlignLeft);
    MButtonAccent *graphButton = new MButtonAccent("Generate Graph");
    bottomLayout->addWidget(graphButton, Qt::AlignLeft);
    connect(graphButton, &QPushButton::clicked, this, [this, graphType, temp, sens]() {
        emit MWcreateGraph(graphType->currentText(), temp->currentText(), sens);
    });
}


void MainWindow::addSensorScreen(){
    delete(centroDx);
    centroDx = new QFrame();
    centroDx->setObjectName("Pannello");
    centroDx->setMinimumSize(590, 400);
    mainLayout->addWidget(centroDx, 1, 1);
    QGridLayout *middle = new QGridLayout(centroDx);
    QFrame *topContainer = new QFrame();
    QHBoxLayout *topLayout = new QHBoxLayout(topContainer);
    topContainer->setFixedHeight(40);
    MTitleLabel *title = new MTitleLabel("Add a Sensor - Select a sensor type");
    title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    topLayout->addWidget(title);
    middle->addWidget(topContainer, 0, 0);
    QFrame *mainElement = new QFrame();
    QGridLayout *internalLayout = new QGridLayout(mainElement);
    internalLayout->setContentsMargins(0, 0, 0, 0);
    internalLayout->setSpacing(0);
    internalLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    MPageSensorEditSelector *type = new MPageSensorEditSelector("Sensor Type");
    type->addItem("Temperature Sensor");
    type->addItem("Water Level Sensor");
    type->addItem("Soil Moisture Sensor");
    internalLayout->addWidget(type, 0,0);
    middle->addWidget(mainElement, 1, 0);
    QWidget *bottomContainer = new QWidget();
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomContainer);
    bottomContainer->setFixedHeight(60);
    bottomLayout->addStretch(0);
    MButtonAccent *continueButton = new MButtonAccent("Continue");
    bottomLayout->addWidget(continueButton, Qt::AlignLeft);
    middle->addWidget(bottomContainer, 2, 0);
    connect(continueButton, &QPushButton::clicked, this, [this, type]() {
        sensorType = type->getValue();
        delete(centroDx);
        centroDx = new QFrame();
        centroDx->setObjectName("Pannello");
        centroDx->setMinimumSize(590, 400);
        mainLayout->addWidget(centroDx, 1, 1);
        QGridLayout *middle2 = new QGridLayout(centroDx);
        QFrame *topContainer2 = new QFrame();
        QHBoxLayout *topLayout2 = new QHBoxLayout(topContainer2);
        topContainer2->setFixedHeight(40);
        MTitleLabel *title = new MTitleLabel("Add a Sensor - Set parameters");
        title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        topLayout2->addWidget(title);
        middle2->addWidget(topContainer2, 0, 0);
        QWidget *bottomContainer2 = new QWidget();
        QHBoxLayout *bottomLayout2 = new QHBoxLayout(bottomContainer2);
        bottomContainer2->setFixedHeight(60);
        bottomLayout2->addStretch(0);
        MButtonAccent *saveButton2 = new MButtonAccent("Save");
        bottomLayout2->addWidget(saveButton2, Qt::AlignLeft);
        middle2->addWidget(bottomContainer2, 2, 0);
        if(sensorType=="Temperature Sensor"){
            QFrame *mainElement2 = new QFrame();
            QGridLayout *internalLayout2 = new QGridLayout(mainElement2);
            internalLayout2->setContentsMargins(0, 0, 0, 0);
            internalLayout2->setSpacing(0);
            MPageSensorEdit *name = new MPageSensorEdit("Name", "Name");
            internalLayout2->addWidget(name, 0, 0, Qt::AlignTop);
            MPageSensorEdit *group = new MPageSensorEdit("Group", "T001");
            internalLayout2->addWidget(group, 0, 1, Qt::AlignTop);
            MPageSensorEdit *minVal = new MPageSensorEdit("Minimum Value", "0");
            internalLayout2->addWidget(minVal, 1, 0, Qt::AlignTop);
            MPageSensorEdit *maxVal = new MPageSensorEdit("Maximum Value", "100");
            internalLayout2->addWidget(maxVal, 1, 1, Qt::AlignTop);
            MPageSensorEditSelector *mountType = new MPageSensorEditSelector("Mounting Type");
            mountType->addItem("Wall Mount");
            mountType->addItem("Roof Mount");
            mountType->addItem("Table Mount");
            internalLayout2->addWidget(mountType, 2, 0, Qt::AlignTop);
            MPageSensorEditSelector *powerType = new MPageSensorEditSelector("Power Type");
            powerType->addItem("Battery");
            powerType->addItem("Solar");
            powerType->addItem("AC/DC");
            internalLayout2->addWidget(powerType, 2, 1, Qt::AlignTop);
            internalLayout2->setAlignment(Qt::AlignTop);
            middle2->addWidget(mainElement2, 1, 0);
            auto temp = std::make_shared<QVector<QString>>(7);
            connect(saveButton2, &QPushButton::clicked, this, [this, temp, name, group, minVal, maxVal, mountType, powerType]() {
                (*temp)[0] = sensorType;
                (*temp)[1] = name->getValue();
                (*temp)[2] = group->getValue();
                (*temp)[3] = minVal->getValue();
                (*temp)[4] = maxVal->getValue();
                (*temp)[5] = mountType->getValue();
                (*temp)[6] = powerType->getValue();
                emit MWButtonClickedParams("AddSensorSave", temp.get());
            });
        } else if(sensorType=="Water Level Sensor"){
            QFrame *mainElement2 = new QFrame();
            QGridLayout *internalLayout2 = new QGridLayout(mainElement2);
            internalLayout2->setContentsMargins(0, 0, 0, 0);
            internalLayout2->setSpacing(0);
            MPageSensorEdit *name = new MPageSensorEdit("Name", "Name");
            internalLayout2->addWidget(name, 0, 0, Qt::AlignTop);
            MPageSensorEdit *group = new MPageSensorEdit("Group", "WL001");
            internalLayout2->addWidget(group, 0, 1, Qt::AlignTop);
            MPageSensorEdit *minVal = new MPageSensorEdit("Minimum Value", "0");
            internalLayout2->addWidget(minVal, 1, 0, Qt::AlignTop);
            MPageSensorEdit *maxVal = new MPageSensorEdit("Maximum Value", "100");
            internalLayout2->addWidget(maxVal, 1, 1, Qt::AlignTop);
            MPageSensorEditSelector *protectionLevel = new MPageSensorEditSelector("Protection Level");
            protectionLevel->addItem("IP68");
            protectionLevel->addItem("IPX5");
            protectionLevel->addItem("IP57");
            internalLayout2->addWidget(protectionLevel, 2, 0, Qt::AlignTop);
            MPageSensorEditSelector *measureMethod = new MPageSensorEditSelector("Measure Type");
            measureMethod->addItem("Ultrasonic");
            measureMethod->addItem("Physical");
            measureMethod->addItem("Floater");
            internalLayout2->addWidget(measureMethod, 2, 1, Qt::AlignTop);
            internalLayout2->setAlignment(Qt::AlignTop);
            middle2->addWidget(mainElement2, 1, 0);
            auto temp = std::make_shared<QVector<QString>>(7);
            connect(saveButton2, &QPushButton::clicked, this, [this, temp, name, group, minVal, maxVal, protectionLevel, measureMethod]() {
                (*temp)[0] = sensorType;
                (*temp)[1] = name->getValue();
                (*temp)[2] = group->getValue();
                (*temp)[3] = minVal->getValue();
                (*temp)[4] = maxVal->getValue();
                (*temp)[5] = protectionLevel->getValue();
                (*temp)[6] = measureMethod->getValue();
                emit MWButtonClickedParams("AddSensorSave", temp.get());
            });
        } else if(sensorType=="Soil Moisture Sensor"){
            QFrame *mainElement2 = new QFrame();
            QGridLayout *internalLayout2 = new QGridLayout(mainElement2);
            internalLayout2->setContentsMargins(0, 0, 0, 0);
            internalLayout2->setSpacing(0);
            MPageSensorEdit *name = new MPageSensorEdit("Name", "Name");
            internalLayout2->addWidget(name, 0, 0, Qt::AlignTop);
            MPageSensorEdit *group = new MPageSensorEdit("Group", "SM001");
            internalLayout2->addWidget(group, 0, 1, Qt::AlignTop);
            MPageSensorEdit *minVal = new MPageSensorEdit("Minimum Value", "0");
            internalLayout2->addWidget(minVal, 1, 0, Qt::AlignTop);
            MPageSensorEdit *maxVal = new MPageSensorEdit("Maximum Value", "100");
            internalLayout2->addWidget(maxVal, 1, 1, Qt::AlignTop);
            MPageSensorEditSelector *sensorMaterial = new MPageSensorEditSelector("Sensor Material");
            sensorMaterial->addItem("Steel");
            sensorMaterial->addItem("Copper");
            sensorMaterial->addItem("Brass");
            internalLayout2->addWidget(sensorMaterial, 2, 0, Qt::AlignTop);
            MPageSensorEditSelector *depth = new MPageSensorEditSelector("Depth");
            depth->addItem("10cm");
            depth->addItem("20cm");
            depth->addItem("45cm");
            internalLayout2->addWidget(depth, 2, 1, Qt::AlignTop);
            internalLayout2->setAlignment(Qt::AlignTop);
            middle2->addWidget(mainElement2, 1, 0);
            auto temp = std::make_shared<QVector<QString>>(7);
            connect(saveButton2, &QPushButton::clicked, this, [this, temp, name, group, minVal, maxVal, sensorMaterial, depth]() {
                (*temp)[0] = sensorType;
                (*temp)[1] = name->getValue();
                (*temp)[2] = group->getValue();
                (*temp)[3] = minVal->getValue();
                (*temp)[4] = maxVal->getValue();
                (*temp)[5] = sensorMaterial->getValue();
                (*temp)[6] = depth->getValue();
                emit MWButtonClickedParams("AddSensorSave", temp.get());
            });
        }
    });
}



void MainWindow::addSensorToList(AbstractSensor* a){
    numSensori+=1;
    cardContainer->setFixedSize(230, numSensori*70);
    MSensorCard *temp = new MSensorCard(a);
    cardContainerLay->addWidget(temp);
    connect(temp->getCheckPointer(), &QCheckBox::stateChanged, this, [this, a, temp]()->void{
        emit MWSensorChecked(a, temp->getCheckStatus());
    });
    cardArray->append(temp);
    MWSearchHandler();
}



void MainWindow::MWSearchHandler(){
    int numVisible = 0;
    if(searchBarP->text() == ""){
        for(int i=0; i<cardArray->size(); i++) {
            numVisible++;
            cardArray->at(i)->setVisible(true);
        }
    }
    if(searchBarP->text() != ""){
        for(int i=0; i<cardArray->size(); i++) {
            QRegularExpression re(searchBarP->text());
            QRegularExpressionMatch match1 = re.match(cardArray->at(i)->getInfo());
            QRegularExpressionMatch match2 = re.match(cardArray->at(i)->getTitle());
            if (match1.hasMatch() || match2.hasMatch()) {
                cardArray->at(i)->setVisible(true);
                numVisible++;
            } else {
                cardArray->at(i)->setVisible(false);
            }
        }
    }
    cardContainer->setFixedSize(230, numVisible*70);
}



void MainWindow::removeSensorList(AbstractSensor* a){
    numSensori-=1;
    cardContainer->setFixedSize(230, numSensori*70);
    for(int i = 0; i<cardArray->size(); i++){
        if(cardArray->at(i)->getSensorPointer() == a){
            cardArray->at(i)->setVisible(false);
            cardArray->remove(i);
            break;
        }
    }
    MWSearchHandler();
}

void MainWindow::clearSensorList(){
    numSensori=0;
    cardContainer->setFixedSize(230, numSensori*70);
    for(int i = 0; i<cardArray->size(); i++){
        delete(cardArray->at(i));
    }
    MWSearchHandler();
}



void MainWindow::showGraphView(QLineSeries* series, AbstractSensor* sensor){
    delete(centroDx);
    centroDx = new QFrame();
    centroDx->setObjectName("Pannello");
    centroDx->setMinimumSize(590, 400);
    mainLayout->addWidget(centroDx, 1, 1);
    QGridLayout *middle = new QGridLayout(centroDx);
    QFrame *topContainer = new QFrame();
    QHBoxLayout *topLayout = new QHBoxLayout(topContainer);
    topContainer->setFixedHeight(40);
    MTitleLabel *title = new MTitleLabel("Graph View");
    title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    topLayout->addWidget(title);
    middle->addWidget(topContainer, 0, 0);
    QFrame *mainElement = new QFrame();
    QGridLayout *internalLayout = new QGridLayout(mainElement);
    internalLayout->setContentsMargins(0, 0, 0, 0);
    internalLayout->setSpacing(0);
    internalLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    auto chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle(sensor->getName());
    auto yax = chart->axes(Qt::Vertical);
    yax.first()->setRange(sensor->getMinValue(), sensor->getMaxValue());
    chart->setBackgroundBrush(QBrush(QColor("white")));
    QChartView *a = new QChartView(chart, NULL);
    a->setBackgroundBrush(QBrush(QColor("white")));
    internalLayout->addWidget(a, 0,0);
    middle->addWidget(mainElement, 1, 0);
    QWidget *bottomContainer = new QWidget();
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomContainer);
    bottomContainer->setFixedHeight(60);
    bottomLayout->addStretch(0);
    MButtonAccent *saveGraph = new MButtonAccent("Save Graph");
    bottomLayout->addWidget(saveGraph, Qt::AlignLeft);
    middle->addWidget(bottomContainer, 2, 0);
    connect(saveGraph, &QPushButton::pressed, this, [chart, a]()->void{
        QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Chart", "", "PNG files (*.png)");
        if (!fileName.isEmpty()) {
            if (!fileName.endsWith(".png", Qt::CaseInsensitive)) {
                fileName += ".png";
            }
            QImage image(a->size(), QImage::Format_ARGB32);
            image.fill(Qt::white);
            QPainter painter(&image);
            chart->scene()->render(&painter);
            if (!image.save(fileName)) {
                QMessageBox a;
                a.setText("Failed to save the image.");
                a.exec();
            }
        }
    });
}



void MainWindow::editSensorScreen(AbstractSensor* sensor){
    sensor->acceptEdit(this);
}



void MainWindow::visitEditDataMW(TemperatureSensor* sensor){
    delete(centroDx);
    centroDx = new QFrame();
    centroDx->setObjectName("Pannello");
    centroDx->setMinimumSize(590, 400);
    mainLayout->addWidget(centroDx, 1, 1);
    QGridLayout *middle = new QGridLayout(centroDx);
    QFrame *topContainer = new QFrame();
    QHBoxLayout *topLayout = new QHBoxLayout(topContainer);
    topContainer->setFixedHeight(40);
    MTitleLabel *title = new MTitleLabel("Edit Temperature Sensor");
    title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    topLayout->addWidget(title);
    middle->addWidget(topContainer, 0, 0);
    QFrame *mainElement = new QFrame();
    QGridLayout *internalLayout = new QGridLayout(mainElement);
    internalLayout->setSpacing(0);
    internalLayout->setContentsMargins(0,0,0,0);
    MPageSensorEdit *name = new MPageSensorEdit("Name", sensor->getName());
    internalLayout->addWidget(name, 0, 0, Qt::AlignTop);
    MPageSensorEdit *group = new MPageSensorEdit("Group", sensor->getGroup());
    internalLayout->addWidget(group, 0, 1, Qt::AlignTop);
    MPageSensorEdit *minVal = new MPageSensorEdit("Minimum Value", QString::number(sensor->getMinValue()));
    internalLayout->addWidget(minVal, 1, 0, Qt::AlignTop);
    MPageSensorEdit *maxVal = new MPageSensorEdit("Maximum Value", QString::number(sensor->getMaxValue()));
    internalLayout->addWidget(maxVal, 1, 1, Qt::AlignTop);
    MPageSensorEditSelector *mountType = new MPageSensorEditSelector("Mounting Type");
    mountType->addItem("Wall Mount");
    mountType->addItem("Roof Mount");
    mountType->addItem("Table Mount");
    mountType->setItem(sensor->getMountType());
    internalLayout->addWidget(mountType, 2, 0, Qt::AlignTop);
    MPageSensorEditSelector *powerType = new MPageSensorEditSelector("Power Type");
    powerType->addItem("Battery");
    powerType->addItem("Solar");
    powerType->addItem("AC/DC");
    powerType->setItem(sensor->getPowerType());
    internalLayout->addWidget(powerType, 2, 1, Qt::AlignTop);
    internalLayout->setAlignment(Qt::AlignTop);
    middle->addWidget(mainElement, 1, 0);
    QWidget *bottomContainer = new QWidget();
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomContainer);
    bottomContainer->setFixedHeight(60);
    bottomLayout->addStretch(0);
    MButtonAccent *updateButton = new MButtonAccent("Update");
    bottomLayout->addWidget(updateButton, Qt::AlignLeft);
    middle->addWidget(bottomContainer, 2, 0);
    auto temp = std::make_shared<QVector<QString>>(7);
    connect(updateButton, &QPushButton::clicked, this, [this, temp, name, group, minVal, maxVal, mountType, powerType, sensor]() {
        (*temp)[0] = "Temperature Sensor";
        (*temp)[1] = name->getValue();
        (*temp)[2] = group->getValue();
        (*temp)[3] = minVal->getValue();
        (*temp)[4] = maxVal->getValue();
        (*temp)[5] = mountType->getValue();
        (*temp)[6] = powerType->getValue();
        emit MWButtonEdit(temp.get(), sensor);
    });
}



void MainWindow::visitEditDataMW(WaterLevelSensor* sensor){
    delete(centroDx);
    centroDx = new QFrame();
    centroDx->setObjectName("Pannello");
    centroDx->setMinimumSize(590, 400);
    mainLayout->addWidget(centroDx, 1, 1);
    QGridLayout *middle = new QGridLayout(centroDx);
    QFrame *topContainer = new QFrame();
    QHBoxLayout *topLayout = new QHBoxLayout(topContainer);
    topContainer->setFixedHeight(40);
    MTitleLabel *title = new MTitleLabel("Edit Water Level Sensor");
    title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    topLayout->addWidget(title);
    middle->addWidget(topContainer, 0, 0);
    QFrame *mainElement = new QFrame();
    QGridLayout *internalLayout = new QGridLayout(mainElement);
    internalLayout->setSpacing(0);
    internalLayout->setContentsMargins(0,0,0,0);
    MPageSensorEdit *name = new MPageSensorEdit("Name", sensor->getName());
    internalLayout->addWidget(name, 0, 0, Qt::AlignTop);
    MPageSensorEdit *group = new MPageSensorEdit("Group", sensor->getGroup());
    internalLayout->addWidget(group, 0, 1, Qt::AlignTop);
    MPageSensorEdit *minVal = new MPageSensorEdit("Minimum Value", QString::number(sensor->getMinValue()));
    internalLayout->addWidget(minVal, 1, 0, Qt::AlignTop);
    MPageSensorEdit *maxVal = new MPageSensorEdit("Maximum Value", QString::number(sensor->getMaxValue()));
    internalLayout->addWidget(maxVal, 1, 1, Qt::AlignTop);
    MPageSensorEditSelector *protectionLevel = new MPageSensorEditSelector("Protection Level");
    protectionLevel->addItem("IP68");
    protectionLevel->addItem("IPX5");
    protectionLevel->addItem("IP57");
    protectionLevel->setItem(sensor->getProtectionLevel());
    internalLayout->addWidget(protectionLevel, 2, 0, Qt::AlignTop);
    MPageSensorEditSelector *measureMethod = new MPageSensorEditSelector("Measure Type");
    measureMethod->addItem("Ultrasonic");
    measureMethod->addItem("Physical");
    measureMethod->addItem("Floater");
    measureMethod->setItem(sensor->getMeasureMethod());
    internalLayout->addWidget(measureMethod, 2, 1, Qt::AlignTop);
    internalLayout->setAlignment(Qt::AlignTop);
    middle->addWidget(mainElement, 1, 0);
    QWidget *bottomContainer = new QWidget();
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomContainer);
    bottomContainer->setFixedHeight(60);
    bottomLayout->addStretch(0);
    MButtonAccent *updateButton = new MButtonAccent("Update");
    bottomLayout->addWidget(updateButton, Qt::AlignLeft);
    middle->addWidget(bottomContainer, 2, 0);
    auto temp = std::make_shared<QVector<QString>>(7);
    connect(updateButton, &QPushButton::clicked, this, [this, temp, name, group, minVal, maxVal, protectionLevel, measureMethod, sensor]() {
        (*temp)[0] = "Water Level Sensor";
        (*temp)[1] = name->getValue();
        (*temp)[2] = group->getValue();
        (*temp)[3] = minVal->getValue();
        (*temp)[4] = maxVal->getValue();
        (*temp)[5] = protectionLevel->getValue();
        (*temp)[6] = measureMethod->getValue();
        emit MWButtonEdit(temp.get(), sensor);
    });
}



void MainWindow::visitEditDataMW(SoilMoistureSensor* sensor){
    delete(centroDx);
    centroDx = new QFrame();
    centroDx->setObjectName("Pannello");
    centroDx->setMinimumSize(590, 400);
    mainLayout->addWidget(centroDx, 1, 1);
    QGridLayout *middle = new QGridLayout(centroDx);
    QFrame *topContainer = new QFrame();
    QHBoxLayout *topLayout = new QHBoxLayout(topContainer);
    topContainer->setFixedHeight(40);
    MTitleLabel *title = new MTitleLabel("Edit Soil Moisture Sensor");
    title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    topLayout->addWidget(title);
    middle->addWidget(topContainer, 0, 0);
    QFrame *mainElement = new QFrame();
    QGridLayout *internalLayout = new QGridLayout(mainElement);
    internalLayout->setSpacing(0);
    internalLayout->setContentsMargins(0,0,0,0);
    MPageSensorEdit *name = new MPageSensorEdit("Name", sensor->getName());
    internalLayout->addWidget(name, 0, 0, Qt::AlignTop);
    MPageSensorEdit *group = new MPageSensorEdit("Group", sensor->getGroup());
    internalLayout->addWidget(group, 0, 1, Qt::AlignTop);
    MPageSensorEdit *minVal = new MPageSensorEdit("Minimum Value", QString::number(sensor->getMinValue()));
    internalLayout->addWidget(minVal, 1, 0, Qt::AlignTop);
    MPageSensorEdit *maxVal = new MPageSensorEdit("Maximum Value", QString::number(sensor->getMaxValue()));
    internalLayout->addWidget(maxVal, 1, 1, Qt::AlignTop);
    MPageSensorEditSelector *sensorMaterial = new MPageSensorEditSelector("Sensor Material");
    sensorMaterial->addItem("Steel");
    sensorMaterial->addItem("Copper");
    sensorMaterial->addItem("Brass");
    sensorMaterial->setItem(sensor->getSensorMaterial());
    internalLayout->addWidget(sensorMaterial, 2, 0, Qt::AlignTop);
    MPageSensorEditSelector *depth = new MPageSensorEditSelector("Depth");
    depth->addItem("10cm");
    depth->addItem("20cm");
    depth->addItem("45cm");
    depth->setItem(sensor->getDepth());
    internalLayout->addWidget(depth, 2, 1, Qt::AlignTop);
    internalLayout->setAlignment(Qt::AlignTop);
    middle->addWidget(mainElement, 1, 0);
    QWidget *bottomContainer = new QWidget();
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomContainer);
    bottomContainer->setFixedHeight(60);
    bottomLayout->addStretch(0);
    MButtonAccent *updateButton = new MButtonAccent("Update");
    bottomLayout->addWidget(updateButton, Qt::AlignLeft);
    middle->addWidget(bottomContainer, 2, 0);
    auto temp = std::make_shared<QVector<QString>>(7);
    connect(updateButton, &QPushButton::clicked, this, [this, temp, name, group, minVal, maxVal, sensorMaterial, depth, sensor]() {
        (*temp)[0] = "Soil Humidity Sensor";
        (*temp)[1] = name->getValue();
        (*temp)[2] = group->getValue();
        (*temp)[3] = minVal->getValue();
        (*temp)[4] = maxVal->getValue();
        (*temp)[5] = sensorMaterial->getValue();
        (*temp)[6] = depth->getValue();
        emit MWButtonEdit(temp.get(), sensor);
    });
}



void MainWindow::updateSensorCard(AbstractSensor* sensor){
    for(int i = 0; i<cardArray->size(); i++){
        if(cardArray->at(i)->getSensorPointer() == sensor){
            cardArray->at(i)->updateCard();
            break;
        }
    }
    MWSearchHandler();
}
