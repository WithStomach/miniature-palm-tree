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

QString zombieName[] = {"noraml", "shit", "flower"};

GameScene::GameScene(QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(mainWidth, mainHeight);
    OptionButton* exitButton = new OptionButton(300, 50, "exit");
    mainGame = new QGraphicsScene;
    mainGame->setItemIndexMethod(QGraphicsScene::NoIndex);
    mainGame->setSceneRect(-0.5 * mainWidth, -0.5 * mainHeight,
                           mainWidth, mainHeight);

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
    exitButton->setParent(gameMap);
    exitButton->move(0, 0);
    connect(exitButton, QPushButton::clicked, gameMap, &exit);
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
            plants[i][j]->setPos(80*j-260,190-i*100);
            //190 260, 90 160, -10 60, -110 -30, -210 -140
            connect(plants[i][j],SIGNAL(missilelaunch(QString,int,int)),this,SLOT(missile_construct(QString,int,int)));
            //DEBUG
            plants[i][j]->AddPlant(new Card("PeaShooter"));
            //DEBUG
        }


    //持续刷新界面
    QTimer* t1 = new QTimer();
    QObject::connect(t1, SIGNAL(timeout()), mainGame, SLOT(advance()));
    t1->start(200);
}

void GameScene::zombie_construct(int last_row)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    //生成僵尸数量少于4只时，每次只会出现一只普通僵尸
    if(Zombie::zombieNum <= 4){
        //随机决定下一只僵尸生成的行
        int _r = qrand() % 5;
        //若与上一只在相同行，则生成在下一行
        if(_r == last_row)
            _r = (_r + 1) % 5;
        Zombie* newZombie = new Zombie(QString("normal"), _r);
        mainGame->addItem(newZombie);
        newZombie->setPos(500, 150 - _r * 100);
        //newZombie->setPos(500, 200);
        connect(newZombie, &Zombie::death, this, &zombie_construct);
    }
    //第二阶段会出现较强的僵尸，且数量更多
    else if(Zombie::zombieNum <= 15){
        int cnt = qrand() % 3 + 1;//每次出现1 ~ 3只僵尸
        int lr = -1;
        for(int i = 0; i < cnt; i++){
           int _r = qrand() % 5;
           if(_r == lr)
               _r = (_r + 1) % 5;
           lr = _r;
           int _k = qrand() % 3;
           Zombie* newZombie = new Zombie(zombieName[_k], _r);
           mainGame->addItem(newZombie);
           newZombie->setPos(500, 162 - _r * 108);
           //162 282, 54, -54, -162, -270
           if(i == cnt - 1)
               connect(newZombie, &Zombie::death, this, &zombie_construct);
        }
    }

}

void GameScene::missile_construct(QString missilename,int row,int column){
    Missile *missile=new Missile(missilename);
    mainGame->addItem(missile);
    missile->setPos(90*column-170,190-row*100);
}
