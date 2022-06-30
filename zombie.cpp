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
#include <QImage>
#include "gamescene.h"

//记录僵尸名字的数组
QString zombieName[] = {"noraml", "block", "paper", "football"};

int Zombie::zombieNum = 0;
int Zombie::rowNum[5] = {0, 0, 0, 0, 0};
//僵尸生命值
QMap<QString, int> Zombie::HPInfo = {
    std::map<QString, int>::value_type("normal", 300),
    std::map<QString, int>::value_type("block", 200),
    std::map<QString, int>::value_type("paper", 300),
    std::map<QString, int>::value_type("football", 450)
};
//攻击力
QMap<QString, int> Zombie::ATKInfo = {
    std::map<QString, int>::value_type("normal", 100),
    std::map<QString, int>::value_type("block", 100),
    std::map<QString, int>::value_type("paper", 100),
    std::map<QString, int>::value_type("football", 100)
};
//速度
QMap<QString, int> Zombie::SpeedInfo = {
    std::map<QString, int>::value_type("normal", 2),
    std::map<QString, int>::value_type("block", 2),
    std::map<QString, int>::value_type("paper", 2),
    std::map<QString, int>::value_type("football", 4)
};
//贴图高度
QMap<QString, int> Zombie::Hei = {
    std::map<QString, int>::value_type("normal", 120),
    std::map<QString, int>::value_type("block", 144),
    std::map<QString, int>::value_type("paper", 137),
    std::map<QString, int>::value_type("football", 160)
};
//行走动作帧数
QMap<QString, int> Zombie::StepNum = {
    std::map<QString, int>::value_type("normal", 21),
    std::map<QString, int>::value_type("block", 21),
    std::map<QString, int>::value_type("paper", 19),
    std::map<QString, int>::value_type("football", 11)
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
    setZValue(10);
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
    int wid = 150;
    return QRectF(0, 0, wid, Hei[name] + 5);
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QImage ii(":/Zombie/zombiePic/" + name + "Zombie_" + mode +
              "(" + QString::number(step + 1 + stage) + ").png");
    painter->drawImage(0, Hei[name] - ii.height(), ii);
    QRectF HP_all(ii.width() / 2 - 35, Hei[name], ii.width() / 2 + 35, 5);
    painter->drawRect(HP_all);
    QImage hp(":/pic/zombie_HP.png");
    hp = hp.scaled((double(HP)/HPInfo[name]) * 70, 5);
    painter->drawImage(ii.width() / 2 - 35, Hei[name], hp);
}

void Zombie::advance(int s = 1){
    if(!s)
        return;
    bool e = true;
    // 若处于死亡状态，正常播放死亡动作，无其他操作
    if(mode == "dead"){
        update();
        step++;
        //死亡动作完成后，发出信号，并删除对象
        if(step == 10){
            emit(death(row));
            delete this;
        }
        return;
    }
    //判定是否与植物发生碰撞
    const char* n = typeid(Plant).name();
    QList<QGraphicsItem*> dd = this->scene()->collidingItems(this,
                                                             Qt::IntersectsItemShape);
    QList<QGraphicsItem*>::iterator it = dd.begin();
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
    //若未与植物碰撞，继续正常移动
    if(e){
        if(mode == "attack"){
            step = 0;
            mode = "move";
        }
        step++;
        step %= mStep;
        setPos(mapToParent(-speed, 0));
    }
    // 如果僵尸与植物单位发生碰撞，停止移动开始攻击
    else{
        if(mode == "move"){
            step = 0;
            mode = "attack";
        }
        step++;
        step %= 11;
        this->update();
        //每5帧进行一次伤害判定
        if(step % 5 == 0 && step != 0)
            attack((Plant*)(*it));
    }
    //若处于减速状态，减速时间减少
    if(poison_time > 0){
        poison_time--;
        //脱离减速状态后速度恢复
        switch (poison_level)
        {
            case 2:
                HP-=2;
            break;
            case 3:
                HP-=3;
            break;
            case 4:
                HP-=0.02*HPInfo[name]+3;
            break;
            case 5:
                HP-=0.04*HPInfo[name]+3;
            break;
        }
        if (HP<=0)
            this->dead();
        //结算伤害
        if(poison_time == 0)
            speed *= 2;
    }
    if(this->x() < -320){
        emit zombie_victory();
        return;
    }
}

void Zombie::dead()
{
    //某些僵尸第一次死亡对应形态转变
    if(stage == 0){
        //路障僵尸变为普通僵尸
        if(name == "block"){
            name = "normal";
            HP = HPInfo[name];
            step = 0;
            mStep = StepNum[name];
            setPos(this->x(), 270 - Hei[name] - row * 100);
            return;
        }
        //读报僵尸的报纸脱落，速度与攻击力增加
        else if(name == "paper"){
            stage = 19;
            HP = HPInfo[name];
            step = 0;
            speed *= 2;
            ATK *= 2;
            mStep = 14;
            return;
        }
        else if(name == "football"){
            stage = 11;
            HP = 100;
            step = 0;
            mStep = 11;
            return;
        }
    }
    //进入死亡阶段
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
    path.addEllipse(QRectF(10, Hei[name] - 100, 85, Hei[name] - 40));
    return path;
}

void Zombie::poison(int time,int level)
{
    if(poison_time == 0)
        speed /= 2;
    poison_time = time;
    if (poison_level<level)
        poison_level=level;
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
        Zombie* newZombie = new Zombie(QString("normal"), _r);
        mainGame->addItem(newZombie);
        newZombie->setPos(500, 270 - Zombie::Hei[newZombie->name] - _r * 100);
        //newZombie->setPos(500, 200);
        connect(newZombie, &Zombie::death, this, &zombie_construct);
        connect(newZombie, &Zombie::zombie_victory, this, &lose);
    }
    //第二阶段会出现较强的僵尸，且数量更多
    else if(Zombie::zombieNum <= 20){
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
               connect(newZombie, &Zombie::death, this, &zombie_construct, Qt::QueuedConnection);
        }
    }
    //一大波僵尸
    else if (Zombie::zombieNum <= 50){
        int cnt = qrand() % 6 + 1;//每次出现1 ~ 6只僵尸
        int lr = -1;
        for(int i = 0; i < cnt; i++){
           int _r = qrand() % 5;
           if(_r == lr)
               _r = (_r + 1) % 5;
           lr = _r;
           int _k = qrand() % 4; // 可能出现橄榄球僵尸
           Zombie* newZombie = new Zombie(zombieName[_k], _r);
           mainGame->addItem(newZombie);
           newZombie->setPos(500, 270 - Zombie::Hei[newZombie->name] - _r * 100);
           if(i == cnt - 1)
               connect(newZombie, &Zombie::death, this, &zombie_construct, Qt::QueuedConnection);
        }
    }
    // 游戏胜利
    else{
        victory();
    }
}
