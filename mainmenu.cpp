#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QString>
#include <QObject>
#include <QPainter>
#include "optionbutton.h"

static const QString iconPath = ""; //窗口图标路径
static const QString bkgPath = ":/cheese.jpg"; //背景图片路径
static const int mainWidth = 1600, mainHeight = 960; //主窗口尺寸

// 所有按键位置、大小均有待修改
MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    //窗口基础属性设置
    ui->setupUi(this);
    setFixedSize(mainWidth, mainHeight);
    setWindowTitle("燕雀之魂");
    //QPixmap icon(iconPath);
    //setWindowIcon(icon);

    // 开始游戏按键
    OptionButton* startButton = new OptionButton(300, 100, "whiteCatBird");
    startButton->setParent(this);
    startButton->move(750, 800);
    this->gameWidget = new GameScene();
    connect(startButton, &QPushButton::clicked, this, &game_start);

    //退出游戏按键
    OptionButton* exitButton = new OptionButton(300, 50, "exit");
    exitButton->setParent(this);
    exitButton->move(750, 800);

    //进入存档界面按键
    OptionButton* saveloadButton = new OptionButton(300, 50, "saveload");
    saveloadButton->setParent(this);
    saveloadButton->move(70, 90);

    //成就（？）


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

void MainMenu::game_start()
{
    this->hide();
    this->gameWidget->show();
}

