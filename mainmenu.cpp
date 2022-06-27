#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QString>
#include <QObject>
#include <QPainter>
#include "optionbutton.h"



// 所有按键位置、大小均有待修改
MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    //窗口基础属性设置
    ui->setupUi(this);
    setFixedSize(mainWidth, mainHeight);
    setWindowTitle("燕雀之魂");
    QPixmap icon(iconPath);
    setWindowIcon(icon);

    // 开始游戏按键
    int width = 400, height = 200;
    OptionButton* startButton = new OptionButton(width, height, "start");
    startButton->setParent(this);
    startButton->move(530, 50);
    connect(startButton, &QPushButton::clicked, this, &game_start);

    //退出游戏按键
    width = 300, height = 150;
    OptionButton* exitButton = new OptionButton(width, height, "exit");
    exitButton->setParent(this);
    exitButton->move(550, 300);
    connect(exitButton, &QPushButton::clicked, this, &exit);

    //进入存档界面按键
    width = 300, height = 150;
    OptionButton* saveloadButton = new OptionButton(width, height, "save");
    saveloadButton->setParent(this);
    saveloadButton->move(530, 200);
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

//开始游戏后，主界面关闭，进入游戏界面
void MainMenu::game_start()
{
    this->hide();
    this->gameWidget = new GameScene();
    gameWidget->game_start();
    
}

