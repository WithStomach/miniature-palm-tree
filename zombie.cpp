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

QString zombieName[] = {"noraml", "block", "paper"};
int Zombie::zombieNum = 0;
int Zombie::rowNum[5] = {0, 0, 0, 0, 0};
QMap<QString, int> Zombie::HPInfo = {
    std::map<QString, int>::value_type("normal", 100),
    std::map<QString, int>::value_type("block", 100),
    std::map<QString, int>::value_type("paper", 100),
};
QMap<QString, int> Zombie::ATKInfo = {
    std::map<QString, int>::value_type("normal", 100),
    std::map<QString, int>::value_type("block", 100),
    std::map<QString, int>::value_type("paper", 100)
};
QMap<QString, int> Zombie::SpeedInfo = {
    std::map<QString, int>::value_type("normal", 2),
    std::map<QString, int>::value_type("block", 2),
    std::map<QString, int>::value_type("paper", 2)
};
QMap<QString, int> Zombie::Hei = {
    std::map<QString, int>::value_type("normal", 120),
    std::map<QString, int>::value_type("block", 144),
    std::map<QString, int>::value_type("paper", 137)
};
QMap<QString, int> Zombie::Wid = {
    std::map<QString, int>::value_type("normal", 2),
    std::map<QString, int>::value_type("block", 2),
    std::map<QString, int>::value_type("paper", 2)
};
QMap<QString, int> Zombie::Stage = {
    std::map<QString, int>::value_type("normal", 0),
    std::map<QString, int>::value_type("block", 1),
    std::map<QString, int>::value_type("paper", 1)
};
QMap<QString, int> Zombie::StepNum = {
    std::map<QString, int>::value_type("normal", 21),
    std::map<QString, int>::value_type("block", 21),
    std::map<QString, int>::value_type("paper", 19)
};

Zombie::Zombie(QString _name, int _r):QObject(), name(_name), row(_r){
    Zombie::zombieNum++;
    HP = Zombie::HPInfo[name];
    ATK = Zombie::ATKInfo[name];
    speed = Zombie::SpeedInfo[name];
    rowNum[row]++;
    stage = 0;
    step = 0;
    mStep = StepNum[name];
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
    int wid = 100;
    if(mode == "dead")
        wid = 140;
    return QRectF(0, 0, wid, Hei[name]);
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QImage ii(":/Zombie/zombiePic/" + name + "Zombie_" + mode +
              "(" + QString::number(step + 1 + stage) + ").png");
    painter->drawImage(0, Hei[name] - ii.height(), ii);
}

void Zombie::advance(int s = 1){
    if(!s)
        return;
    bool e = true;
    if(mode == "dead"){
        update();
        step++;
        if(step == 10){
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
            step = 0;
            mode = "move";
        }
        step++;
        step %= mStep;
        setPos(mapToParent(-speed, 0));
    }
    else{
        if(mode == "move"){
            step = 0;
            mode = "attack";
        }
        step++;
        step %= 11;
        this->update();
        if(step % 5 == 0 && step != 0)
            attack((Plant*)(*it));
    }
}

void Zombie::dead()
{
    if(stage == 0){
        if(name == "block"){
            name = "normal";
            HP = HPInfo[name];
            step = 0;
            mStep = StepNum[name];
            setPos(this->x(), 270 - Hei[name] - row * 100);
            return;
        }
        else if(name == "paper"){
            stage = 19;
            HP = HPInfo[name];
            step = 0;
            speed = 3;
            ATK *= 2;
            mStep = 14;
            return;
        }
    }
    mode = "dead";
    stage = 0;
    step = 0;
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
        Zombie* newZombie = new Zombie(QString("paper"), _r);
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
           newZombie->setPos(500, 270 - Zombie::Hei[newZombie->name] - _r * 100);
           if(i == cnt - 1)
               connect(newZombie, &Zombie::death, this, &zombie_construct);
        }
    }
}
