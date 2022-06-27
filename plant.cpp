#include "plant.h"

#ifndef MISSILE_H
#include "missile.h"
#endif

#ifndef GAMESCENE_H
#include "gamescene.h"
#endif


#include <QPainter>
#include <QDebug>
#include <QTimer>

const int Plant::level_limit[5]={1,3,9,18,36};
QMap<QString, int> Plant::HPInfo={
    std::map<QString,int>::value_type("PeaShooter",300),
    std::map<QString,int>::value_type("SunFlower",300)
};
QMap<QString, int> Plant::CooldownInfo={
    std::map<QString,int>::value_type("PeaShooter",1000),
    std::map<QString,int>::value_type("SunFlower",7500)
};

Card::Card(QString _name=""):QObject(), name(_name){
}

Card::~Card(){}

QRectF Card::boundingRect() const{
    return QRectF(0, 0, 70, 200);
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QImage ii(":/pic/" + name + "Card.png");
    ii = ii.scaled(70, 200);
    painter->drawImage(0, 0, ii);
}


Plant::Plant(){
    name="PeaShooter";
    HP=0;
    XP=0;
    level=0;
    cooldown=1000;
    timer=new QTimer();
}

QRectF Plant::boundingRect() const{
    return QRectF(0, 0, 80, 80);
}


void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QImage ii(":/pic/" + name + ".png");
    ii = ii.scaled(80, 80);
    painter->drawImage(0, 0, ii);
}

bool Plant::AddPlant(Card *card){
    if (name=="Empty"){
        name=card->name;
        XP=1;
        level=1;
        HP=Plant::HPInfo[card->name];
        cooldown=Plant::CooldownInfo[card->name];
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(movement()));
        timer->start(cooldown);
        return true;
    }
    else{
        if (name!=card->name)
            return false;
        else{
            if (level==5)
                return false;
            ++XP;
            if (XP>=(Plant::level_limit[level]))
                ++level;
            return true;
        }
    }
    return true;
}

void Plant::dead(){
    name="Empty";
    HP=0;
    XP=0;
    level=0;
    cooldown=1000;
}

void Plant::movement(){
    if (name=="PeaShooter"){
        Missile *missile=new Missile("Pea");
        //mainGame->addItem(missile);
        missile->setPos(100,0);
        return ;
    }
    return ;
}
