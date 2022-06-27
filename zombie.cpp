#include "zombie.h"
#include <QPainter>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include <QList>
#include "plant.h"
#include <synchapi.h>

int Zombie::zombieNum = 0;
int Zombie::rowNum[5] = {0, 0, 0, 0, 0};
QMap<QString, int> Zombie::HPInfo = {
    std::map<QString, int>::value_type("normal", 100)
};
QMap<QString, int> Zombie::ATKInfo = {
    std::map<QString, int>::value_type("normal", 10)
};
QMap<QString, int> Zombie::SpeedInfo = {
    std::map<QString, int>::value_type("normal", 2),
    std::map<QString, int>::value_type("shit", 2),
    std::map<QString, int>::value_type("flower", 2)
};


Zombie::Zombie(QString _name, int _r):QObject(), name(_name), row(_r){
    Zombie::zombieNum++;
    HP = Zombie::HPInfo[name];
    ATK = Zombie::ATKInfo[name];
    speed = Zombie::SpeedInfo[name];
    rowNum[row]++;
    stage = 0;
    mode = "move";
    //测试用代码
    QTimer* t1 = new QTimer(this);
    connect(t1, &QTimer::timeout, this, &dead);
    t1->setSingleShot(true);
    t1->start(20000);
}

Zombie::~Zombie()
{
    rowNum[row]--;
}


QRectF Zombie::boundingRect() const
{
    int wid = 85;
    if(mode == "dead")
        wid = 140;
    return QRectF(0, 0, wid, 120);
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

    QImage ii(":/Zombie/zombiePic/" + name + "Zombie_" + mode +
              "(" + QString::number(stage + 1) + ").png");
    painter->drawImage(0, 120 - ii.height(), ii);
}

void Zombie::advance(int step = 1){
    if(!step)
        return;
    bool e = true;
    if(mode == "dead"){
        update();
        stage++;
        if(stage == 10){
            emit(death(row));
            delete this;
        }
        return;
    }
    const char* n = typeid(Plant).name();
    QList<QGraphicsItem*> dd = this->scene()->collidingItems(this, Qt::IntersectsItemBoundingRect);
    QList<QGraphicsItem*>::iterator it = dd.begin();
    // 如果僵尸与植物单位发生碰撞，停止移动开始攻击
    for(; it != dd.end(); it++){
        QGraphicsItem* tt = *it;
        if(typeid(*tt).name() == n){
            Plant* ip = (Plant*)(*it);
            if(ip->name != "Empty"){
                e = false;
                break;
            }
        }
    }
    if(e){
        if(mode == "attack"){
            stage = 0;
            mode = "move";
        }
        stage++;
        stage %= 22;
        setPos(mapToParent(-speed, 0));
    }
    else{
        if(mode == "move"){
            stage = 0;
            mode = "attack";
        }
        stage++;
        stage %= 21;
        this->update();
        if(stage == 20)
            attack((Plant*)(*it));
    }
}

void Zombie::dead()
{
    mode = "dead";
    stage = 0;
}

void Zombie::attack(Plant *p)
{
    p->HP -= ATK;
    //if(p->HP <= 0)
       // p->dead();
}
