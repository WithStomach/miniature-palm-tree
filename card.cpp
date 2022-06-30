#include "card.h"

#ifndef PLANT_H
#include "plant.h"
#endif


#ifndef MISSILE_H
#include "missile.h"
#endif

#ifndef ZOMBIE_H
#include "zombie.h"
#endif

#ifndef GAMESCENE_H
#include "gamescene.h"
#endif


#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QtGlobal>

QMap<QString, int> Card::CostInfo = {
    std::map<QString, int>::value_type("PeaShooter", 100),
    std::map<QString, int>::value_type("ShadowPeaShooter", 175),
    std::map<QString, int>::value_type("SunFlower", 50),
    std::map<QString, int>::value_type("Wallnut",75)
};

Card::Card(QString _name=""):QObject(), name(_name){
    is_clicked=false;
    number=0;
    cost = CostInfo[name];
}

Card::~Card(){}

QRectF Card::boundingRect() const{
    return QRectF(0, 0, 200, 120);
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    setZValue(30);
    QImage img(":/pic/" + name + "Card.png");
    img = img.scaled(200, 120);
    painter->drawImage(0, 6, img);
    if (is_clicked)
    {
        QImage img(":/pic/cover.png");
        img = img.scaled(200, 120);
        painter->drawImage(0, 0, img);
    }
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    is_clicked=true;
   update();
   emit Card::card_clicked(number);

}

void MainGame::card_clicked(int n){
    waiting=n;
}
