#include "zombie.h"
#include <QPainter>
#include <QDebug>
#include <QMap>
#include <QString>


zombie::zombie(QString _name):name(_name){
    if(e){
        // 定义各种僵尸的基本数值
        zombieHPInfo[QString("normal")] = 100;
        zombieATKInfo[QString("normal")] = 10;
        zombieSpeedInfo[QString("normal")] = 2;
        e = false;
    }
    HP = zombieHPInfo[name];
    ATK = zombieATKInfo[name];
    speed = zombieSpeedInfo[name];
}

QRectF zombie::boundingRect() const
{
    return QRectF(0, 0, 70, 200);
}

QPainterPath zombie::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 80);
    return path;
}

void zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QImage ii(":/pic/" + name + "Zombie.jpg");
    ii = ii.scaled(70, 200);
    painter->drawImage(0, 0, ii);
}

void zombie::advance(int step = 1){
    if(!step)
        return;
    setPos(mapToParent(-speed, 0));
}
