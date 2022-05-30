#include "zombie.h"
#include <QPainter>
#include <QDebug>

zombie::zombie(QString _name):name(_name){

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
    setPos(mapToParent(-2, 0));
}
