#include "zombie.h"
#include <QPainter>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QTimer>

int Zombie::zombieNum = 0;
QMap<QString, int> Zombie::HPInfo = {
    std::map<QString, int>::value_type("normal", 100)
};
QMap<QString, int> Zombie::ATKInfo = {
    std::map<QString, int>::value_type("normal", 10)
};
QMap<QString, int> Zombie::SpeedInfo = {
    std::map<QString, int>::value_type("normal", 2)
};

Zombie::Zombie(QString _name):QObject(), name(_name){
    Zombie::zombieNum++;
    HP = Zombie::HPInfo[name];
    ATK = Zombie::ATKInfo[name];
    speed = Zombie::SpeedInfo[name];
    QTimer* t1 = new QTimer(this);
    connect(t1, &QTimer::timeout, this, &dead);
    t1->setSingleShot(true);
    t1->start(5000);
}

Zombie::~Zombie()
{
    zombieNum--;
}


QRectF Zombie::boundingRect() const
{
    return QRectF(0, 0, 70, 200);
}

QPainterPath Zombie::shape() const
{
    QPainterPath path;
    path.addRect(-20, -80, 20, 80);
    return path;
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QImage ii(":/pic/" + name + "Zombie.png");
    ii = ii.scaled(70, 200);
    painter->drawImage(0, 0, ii);
}

void Zombie::advance(int step = 1){
    if(!step)
        return;
    setPos(mapToParent(-speed, 0));

}

void Zombie::dead()
{
    emit test_signal();
    delete this;
}
