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
#include "plant.h"
#include <QDialog>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

QString GameScene::zombieName[4] = {"normal", "block", "paper", "football"};
QString MainGame::cardName[5] = {};

GameScene::GameScene(QWidget *parent) : QWidget(parent)
{
    is_going = true;
    for(int i = 0; i < 5; i++)
       Zombie::rowNum[i] = 0;

    this->setFixedSize(mainWidth, mainHeight);

    mainGame = new MainGame;
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

    //开始产生僵尸
    zombie_construct(-1);

    //DEBUG
    mainGame->plants[3][5]->AddPlant(new Card("ShadowPeaShooter"));
    //DEBUG

    //持续刷新界面
    update_t->start(100);
}

void GameScene::pause(){
   if(is_going){
       is_going = false;
       update_t->stop();
   }
   else{
       update_t->start(100);
       is_going = true;
   }
}

void GameScene::back_main_menu()
{
    this->gameMap->close();
    emit back();
    delete this;
}

void GameScene::lose()
{
    update_t->stop();
    QDialog* l = new QDialog(this);
    l->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    l->setStyleSheet("background-image:url(:/pic/lose.png);");
    l->setFixedSize(564, 468);
    l->setModal(true);
    l->move(600, 400);
    l->show();
}

void GameScene::victory()
{
    update_t->stop();
    QDialog* l = new QDialog(this);
    l->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    l->setStyleSheet("background-image:url(:/pic/victory.png);");
    l->setFixedSize(254, 127);
    l->setModal(true);
    l->move(600, 400);
    l->show();
}

MainGame::MainGame()
{
    this->setItemIndexMethod(QGraphicsScene::NoIndex);
    this->setSceneRect(-0.5 * mainWidth, -0.5 * mainHeight,
                           mainWidth, mainHeight);
    waiting = 0;

    //初始化卡牌列表，必有一张向日葵
    card[0] = new Card("PeaShooter");
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    this->addItem(card[0]);
    card[0]->number = 1;
    card[0]->setPos(-490, -180);
    connect(card[0], &Card::card_clicked, this, &MainGame::card_clicked);
    for(int i = 1; i < 3; i++){
        card[i] = new Card("PeaShooter");
        card[i]->number = i + 1;
        this->addItem(card[i]);
        card[i]->setPos(-490, -180 + 120 * i);
        connect(card[i], &Card::card_clicked, this, &MainGame::card_clicked);
    }

    //初始化植物
    for (int i=0;i<5;++i)
        for (int j=0;j<9;++j)
        {
            plants[i][j]=new Plant();
            plants[i][j]->row=i;
            plants[i][j]->column=j;
            addItem(plants[i][j]);
            plants[i][j]->setPos(80*j-250,190-i*100);
            connect(plants[i][j],SIGNAL(missilelaunch(QString,int,int,int)),this,SLOT(missile_construct(QString,int,int,int)));
            //DEBUG
            if (j<2)
                for (int k=1;k<=3;++k)
                {
                    plants[i][j]->AddPlant(new Card("PeaShooter"));
                    qDebug()<<plants[i][j]->name;
                }
            //DEBUG
        }
}

MainGame::~MainGame()
{

}

void MainGame::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "!!!";
    if(event->button() == Qt::LeftButton){
        int x = event->scenePos().x(), y = event->scenePos().y();
        qDebug() << x << " " << y;
        // 若点击刷新按钮, 且此时不处于等待状态，商店刷新
        if(!waiting && x >= -490 && y >= -290 && x <= -290 && y <= -210){
            qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
            qDebug() << "???";
            //每张卡牌随机变为其他种类的卡牌
            for(int i = 0; i < 3; i++){
                card[i] = new Card(cardName[qrand() % 5]);
                this->addItem(card[i]);
                card[i]->setPos(-490, -180 + 120 * i);
            }
        }
        //点击地图区域种下植物
        else if(waiting && x >= -170 && x <= 470 && y >= -310 && y <= 190){
            int c = (x + 250) / 80, r = (190 - y) / 100;
            qDebug() << r << " " << c;
            bool e = plants[r][c]->AddPlant(card[waiting - 1]);
            //种下植物后卡牌消失
            if(e){
                if(cd[waiting - 1]){
                    delete card[waiting - 1];
                    card[waiting - 1] = NULL;
                    cd[waiting - 1] = false;
                    waiting = 0;
                }
            }
        }
        else{
            //点击其余区域会导致等待期终止
            waiting = 0;
            QGraphicsScene::mousePressEvent(event);
        }
    }
}

