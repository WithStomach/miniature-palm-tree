#include "missile.h"
#include <QPainter>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include <QList>

QMap<QString, int> Missile::DamageInfo={
    std::map<QString,int>::value_type("Pea",20)
};

Missile::Missile(QString _name):QObject(),name(_name){
    damage=0;
    speed=50;
};

Missile::~Missile(){}

QRectF Missile::boundingRect() const
{
    return QRectF(0, 0, 30, 80);
}

void Missile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QImage ii(":/pic/" + name + ".png");
    ii = ii.scaled(30, 30);
    painter->drawImage(0, 0, ii);
}

void Missile::advance(int step=1){
    if(!step)
        return;
    bool e = true;
    const char* n = typeid(Zombie).name();
    QList<QGraphicsItem*> dd = this->scene()->collidingItems(this, Qt::IntersectsItemBoundingRect);
    QList<QGraphicsItem*>::iterator it = dd.begin();
    // 如果子弹与僵尸单位发生碰撞，停止移动并造成伤害
    for(; it != dd.end(); it++){
        QGraphicsItem* tt = *it;
        if(typeid(*tt).name() == n){
                e = false;
                break;
        }
    }
    if(e)
        setPos(mapToParent(speed, 0));
    else{
        hit((Zombie*)(*it));
    }
}

void Missile::hit(Zombie *target){
    target->HP -= damage;
    if (target->HP<=0 && target->mode != "dead")
        target->dead();
    delete this;
}
