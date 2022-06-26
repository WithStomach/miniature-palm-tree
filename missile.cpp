#include "missile.h"
#include <QPainter>
#include <QDebug>

Missile::Missile(QString _name):QObject(),name(_name){
    damage=0;
};

Missile::~Missile(){}

QRectF Missile::boundingRect() const
{
    return QRectF(0, 0, 30, 30);
}

void Missile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QImage ii(":/pic/" + name + ".png");
    ii = ii.scaled(30, 30);
    painter->drawImage(0, 0, ii);
}
