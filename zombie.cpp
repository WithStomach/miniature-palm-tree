#include "zombie.h"
#include <QPainter>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include <QList>
#include <QTime>
#include "plant.h"
#include <synchapi.h>
#include <QSound>
#include "gamescene.h"

QString zombieName[] = {"noraml", "block", "flower"};
int Zombie::zombieNum = 0;
int Zombie::rowNum[5] = {0, 0, 0, 0, 0};
QMap<QString, int> Zombie::HPInfo = {
    std::map<QString, int>::value_type("normal", 100),
    std::map<QString, int>::value_type("block", 200)
};
QMap<QString, int> Zombie::ATKInfo = {
    std::map<QString, int>::value_type("normal", 100),
    std::map<QString, int>::value_type("block", 100)
};
QMap<QString, int> Zombie::SpeedInfo = {
    std::map<QString, int>::value_type("normal", 2),
    std::map<QString, int>::value_type("block", 2),
    std::map<QString, int>::value_type("flower", 2)
};
QMap<QString, int> Zombie::Hei = {
    std::map<QString, int>::value_type("normal", 120),
    std::map<QString, int>::value_type("block", 144),
    std::map<QString, int>::value_type("flower", 2)
};
QMap<QString, int> Zombie::Wid = {
    std::map<QString, int>::value_type("normal", 2),
    std::map<QString, int>::value_type("block", 2),
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
    /*QTimer* t1 = new QTimer(this);
    connect(t1, &QTimer::timeout, this, &dead);
    t1->setSingleShot(true);
    t1->start(20000);*/
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
    return QRectF(0, 0, wid, Hei[name]);
}



void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

    QImage ii(":/Zombie/zombiePic/" + name + "Zombie_" + mode +
              "(" + QString::number(stage + 1) + ").png");
    painter->drawImage(0, Hei[name] - ii.height(), ii);
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
    QList<QGraphicsItem*> dd = this->scene()->collidingItems(this,
                                                             Qt::IntersectsItemShape);
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
        stage %= 21;
        setPos(mapToParent(-speed, 0));
    }
    else{
        if(mode == "move"){
            stage = 0;
            mode = "attack";
        }
        stage++;
        stage %= 11;
        this->update();
        if(stage % 10 == 0)
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
    if(p->HP <= 0)
         p->dead();
}

QPainterPath Zombie::shape() const
{
    QPainterPath path;
    path.addEllipse(QRectF(0, Hei[name] - 100, 85, Hei[name] - 40));
    return path;
}

void GameScene::zombie_construct(int last_row)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    //生成僵尸数量少于4只时，每次只会出现一只普通僵尸
    if(Zombie::zombieNum <= 4){
        //随机决定下一只僵尸生成的行
        int _r = qrand() % 5;
        //若与上一只在相同行，则生成在下一行
        if(_r == last_row)
            _r = (_r + 1) % 5;
        Zombie* newZombie = new Zombie(QString("block"), _r);
        mainGame->addItem(newZombie);
        newZombie->setPos(500, 270 - Zombie::Hei[newZombie->name] - _r * 100);
        //newZombie->setPos(500, 200);
        connect(newZombie, &Zombie::death, this, &zombie_construct);
    }
    //第二阶段会出现较强的僵尸，且数量更多
    else if(Zombie::zombieNum <= 15){
        int cnt = qrand() % 3 + 1;//每次出现1 ~ 3只僵尸
        int lr = -1;
        for(int i = 0; i < cnt; i++){
           int _r = qrand() % 5;
           if(_r == lr)
               _r = (_r + 1) % 5;
           lr = _r;
           int _k = qrand() % 3;
           Zombie* newZombie = new Zombie(zombieName[_k], _r);
           mainGame->addItem(newZombie);
           newZombie->setPos(500, 162 - _r * 108);
           //162 282, 54, -54, -162, -270
           if(i == cnt - 1)
               connect(newZombie, &Zombie::death, this, &zombie_construct);
        }
    }

}
