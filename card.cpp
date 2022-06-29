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

}

Card::~Card(){}

QRectF Card::boundingRect() const{
    return QRectF(0, 0, 200, 150);
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QImage ii(":/pic/" + name + "Card.png");
    ii = ii.scaled(200, 150);
    painter->drawImage(0, 0, ii);
}
