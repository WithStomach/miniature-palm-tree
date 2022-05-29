#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QString>
#include <QObject>
#include <QPainter>
#include "optionbutton.h"

static const QString iconPath = "";
static const QString bkgPath = ":/cheese.jpg";

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    setFixedSize(1600, 960);
    setWindowTitle("燕雀之魂");
    //setWindowIcon(iconPath);
    OptionButton* startButton = new OptionButton(300, 100, "whiteCatBird");
    startButton->setParent(this);
    startButton->move(750, 800);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap img(bkgPath);
    painter.drawPixmap(0, 0, this->width(), this->height(), img);
}

