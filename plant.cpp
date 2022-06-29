#include "plant.h"

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

const int Plant::level_limit[6]={1,3,9,16,25,25};
QMap<QString, int> Plant::HPInfo={
    std::map<QString,int>::value_type("PeaShooter",300),
    std::map<QString,int>::value_type("SunFlower",300)
};
QMap<QString, int> Plant::CooldownInfo={
    std::map<QString,int>::value_type("PeaShooter",9),
    std::map<QString,int>::value_type("SunFlower",75)
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
    name="Empty";
    HP=0;
    XP=0;
    level=0;
    cooldown=1000;
    stage=0;
}

QRectF Plant::boundingRect() const{
    return QRectF(0, 0, 70, 70);
}


void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    setZValue(0);
    QImage pic(":/pic/" + name + ".png");
    pic = pic.scaled(70, 70);
    painter->drawImage(0, 0, pic);
    if (name!="Empty")
    {
        QRectF HP_all(0,70,70,5);
        painter->drawRect(HP_all);
        QImage hp(":/pic/HP.png");
        hp = hp.scaled((double(HP)/HPInfo[name])*70, 5);
        painter->drawImage(0,70,hp);
        QRectF XP_all(0,75,70,5);
        painter->drawRect(XP_all);
        QImage xp(":/pic/XP.png");
        xp = xp.scaled((double(XP)/level_limit[level])*70, 5);
        painter->drawImage(0,75,xp);
    }
}

void Plant::advance(int step=1){
    if (!step)
        return ;
    ++stage;
    stage%=cooldown;
    if (stage==0)
        movement();
}

bool Plant::AddPlant(Card *card){
    if (name=="Empty"){
        name=card->name;
        XP=1;
        level=1;
        HP=Plant::HPInfo[card->name];
        cooldown=Plant::CooldownInfo[card->name];
        stage=0;
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
            {
                ++level;
                HP=HPInfo[name];
            }
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
        if (Zombie::rowNum[row])
        {
            missilelaunch("Pea",row,column);
            if (level>1)
            {
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                int rand=qrand()%(6-level);
                if (!rand)
                    missilelaunch("PiercingPea",row,column);
                if (level==5)
                {
                    int rand2=qrand()%2;
                    if (!rand2)
                        missilelaunch("PiercingPea",row,column);
                }
            }
            return ;
        }
    }
    return ;
}
