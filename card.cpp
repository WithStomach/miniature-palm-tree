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

Card::Card(QString _name=""):QObject(), name(_name){
    is_clicked=false;
    number=0;
}

Card::~Card(){}

QRectF Card::boundingRect() const{
    return QRectF(0, 0, 200, 120);
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    setZValue(30);
    QImage img(":/pic/" + name + "Card.png");
    img = img.scaled(200, 120);
    painter->drawImage(0, 0, img);
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "@@@";
    emit Card::card_clicked(number);
}

void MainGame::card_clicked(int n){
    waiting=n;
}
