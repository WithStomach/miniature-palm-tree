#include "gamescene.h"
#include "mainmenu.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include "zombie.h"
#include <math.h>
#include "optionbutton.h"

GameScene::GameScene(QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(mainWidth, mainHeight);
    OptionButton* exitButton = new OptionButton(300, 50, "exit");
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
    exitButton->setParent(gameMap);
    exitButton->move(0, 0);
    connect(exitButton, QPushButton::clicked, gameMap, &exit);
    //gameMap->setParent(this);
    // 商店

}

void GameScene::game_start()
{
    gameMap->show();

    /*QTimer* zombieBirthTimer = new QTimer;
    QObject::connect(zombieBirthTimer, &QTimer::timeout,
                     this, &zombie_construct);
    zombieBirthTimer->start(5000);*/
    zombie_construct();

    QTimer* t1 = new QTimer();
    QObject::connect(t1, SIGNAL(timeout()), mainGame, SLOT(advance()));
    t1->start(100);
}

void GameScene::zombie_construct()
{
    if(Zombie::zombieNum <= 4){
        Zombie* newZombie = new Zombie(QString("normal"));
        mainGame->addItem(newZombie);
        newZombie->setPos(700, (qrand() % 5) * (mainHeight / 5) - mainHeight * 0.5);
        connect(newZombie, &Zombie::test_signal, this, &zombie_construct);
    }

}
