#include "missile.h"
#include "gamescene.h"
#include <QPainter>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include <QList>

QMap<QString, int> Missile::DamageInfo={
    std::map<QString,int>::value_type("Pea",20),
    std::map<QString,int>::value_type("PiercingPea",10),
    std::map<QString,int>::value_type("ShadowPea",30),
    std::map<QString,int>::value_type("PiercingShadowPea",30),
};

Missile::Missile(QString _name):QObject(),name(_name){
    damage=DamageInfo[_name];
    speed=50;
};

Missile::~Missile(){}

QRectF Missile::boundingRect() const
{
    return QRectF(0, 0, 30, 80);
}

void Missile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    setZValue(20);
    QImage missile(":/pic/" + name + ".png");
    missile = missile.scaled(30, 30);
    painter->drawImage(0, 0, missile);
}

void GameScene::missile_construct(QString missilename,int row,int column){
    Missile *missile=new Missile(missilename);
    mainGame->addItem(missile);
    int delay=0;
    if (missilename=="PiercingPea")
        delay=10;
    missile->setPos(80*column-170-delay,190-row*100);
}

void Missile::advance(int step=1){
    if(!step)
        return;
    if (this->x()>=600)
    {
        delete this;
        return ;
    }
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
    if(!e)
        hit((Zombie*)(*it));
    if (e||(this->name.contains("Piercing")))
        setPos(mapToParent(speed, 0));
}

void Missile::hit(Zombie *target){
    target->HP -= damage;
    if (target->HP<=0 && target->mode != "dead")
        target->dead();
    if (!(this->name.contains("Piercing")))
        delete this;
    return ;
}
