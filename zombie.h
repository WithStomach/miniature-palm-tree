#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsItem>
#include <QPainterPath>
#include "plant.h"

class Zombie :public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    static int zombieNum;//记录自游戏开始起生成的僵尸总数
    static int rowNum[5];//记录每一行的僵尸数量
    // 记录僵尸各项数据的map，通过僵尸名字获取信息
    static QMap<QString, int> HPInfo, ATKInfo, SpeedInfo, Hei, StepNum;

    Zombie(QString _name, int _r);
    ~Zombie();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;
    void dead();
    void attack(Plant* p);
    QPainterPath shape()const;
    void poison(int time,int level); // 僵尸减速接口

    QString name;
    QString mode;//僵尸当前行为模式
    int HP;
    int ATK;
    int speed;
    int row; // 僵尸所在行
    int stage; // 僵尸的形态
    int step; // 记录当前动作对应的贴图标号
    int mStep; // 行走动作包含的帧数
    int poison_time,poison_level; // 僵尸被减速的剩余时间和等级
signals:
    // 僵尸死亡时发出信号
    void death(int i);
};

#endif // ZOMBIE_H
