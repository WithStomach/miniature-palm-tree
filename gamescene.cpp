#include "gamescene.h"
#include "mainmenu.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include "zombie.h"
#include <math.h>

GameScene::GameScene(QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(mainWidth, mainHeight);

    mainGame = new QGraphicsScene;
    mainGame->setItemIndexMethod(QGraphicsScene::NoIndex);
    mainGame->setSceneRect(-0.5 * mainWidth, -0.5 * mainHeight,
                           mainWidth, mainHeight);

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
    //gameMap->setParent(this);
    // 商店

}

void GameScene::game_start()
{
    gameMap->show();
    //阳光生成
    
    //
    QTimer* zombieBirthTimer = new QTimer;
    QObject::connect(zombieBirthTimer, &QTimer::timeout,
                     this, &zombie_construct);
    zombieBirthTimer->start(10000);
    QTimer* t1 = new QTimer();
    QObject::connect(t1, SIGNAL(timeout()), mainGame, SLOT(advance()));
    t1->start(100);
}

void GameScene::zombie_construct()
{
    zombie* newZombie = new zombie(QString("normal"));
    mainGame->addItem(newZombie);
    newZombie->setPos(700, (qrand() % 5) * 50);
}
