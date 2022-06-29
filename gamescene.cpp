#include "gamescene.h"
#include "mainmenu.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include "zombie.h"
#include <math.h>
#include <typeinfo>
#include "optionbutton.h"
#include <QDebug>
#include <QTime>
#include "missile.h"
#include <QDialog>


QString GameScene::zombieName[4] = {"normal", "block", "paper", "football"};

GameScene::GameScene(QWidget *parent) : QWidget(parent)
{
    is_going = true;
    for(int i = 0; i < 5; i++)
       Zombie::rowNum[i] = 0;

    this->setFixedSize(mainWidth, mainHeight);

    mainGame = new QGraphicsScene;
    mainGame->setItemIndexMethod(QGraphicsScene::NoIndex);
    mainGame->setSceneRect(-0.5 * mainWidth, -0.5 * mainHeight,
                           mainWidth, mainHeight);
    update_t = new QTimer();
    connect(update_t, SIGNAL(timeout()), mainGame, SLOT(advance()));

    //设置背景（地图）
    QGraphicsPixmapItem* bkg = new QGraphicsPixmapItem;
    QPixmap img(mapPath);
    bkg->setPixmap(img);
    mainGame->addItem(bkg);
    bkg->setPos(-0.5 * mainWidth, -0.5 * mainHeight);

    gameMap = new QGraphicsView;
    gameMap->setScene(mainGame);
    gameMap->setRenderHint(QPainter::Antialiasing);
    gameMap->setCacheMode(QGraphicsView::CacheBackground);
    gameMap->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    gameMap->setSceneRect(-0.5 * mainWidth, -0.5 * mainHeight,
                          mainWidth, mainHeight);
    gameMap->setFixedSize(mainWidth + 5, mainHeight + 5);
    OptionButton* pauseButton = new OptionButton(100, 40, "pause");
    OptionButton* back_menu = new OptionButton(100, 40, "back_menu");
    pauseButton->setParent(gameMap);
    back_menu->setParent(gameMap);
    pauseButton->move(900, 0);
    back_menu->move(700, 0);
    connect(pauseButton, &QPushButton::clicked, this, &pause);
    connect(back_menu, &QPushButton::clicked, this, &back_main_menu);
    // 商店
}

void GameScene::game_start()
{
    gameMap->show();

    //测试用代码
    Plant* newZombie = new Plant();
    mainGame->addItem(newZombie);
    newZombie->setPos(200, 200);


    //开始产生僵尸
    zombie_construct(-1);

    //植物初始化
    Plant *plants[5][9];
    for (int i=0;i<5;++i)
        for (int j=0;j<9;++j)
        {
            plants[i][j]=new Plant();
            plants[i][j]->row=i;plants[i][j]->column=j;
            mainGame->addItem(plants[i][j]);
            plants[i][j]->setPos(80*j-250,190-i*100);
            connect(plants[i][j],SIGNAL(missilelaunch(QString,int,int)),this,SLOT(missile_construct(QString,int,int)));
            //DEBUG
            if (j<2)
                for (int k=1;k<=3;++k)
                    plants[i][j]->AddPlant(new Card("PeaShooter"));
            //DEBUG
        }


    //持续刷新界面
    update_t->start(200);
}

void GameScene::pause(){
   if(is_going){
       is_going = false;
       update_t->stop();
   }
   else{
       update_t->start(200);
       is_going = true;
   }
}

void GameScene::back_main_menu()
{
    this->gameMap->close();
    emit back();
    delete this;
}
