#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsItem>
#include "plant.h"

class Zombie :public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    static int zombieNum;//记录自游戏开始起生成的僵尸总数
    static int rowNum[5];//记录每一行的僵尸数量
    // 记录僵尸各项数据的map，通过僵尸名字获取信息
    static QMap<QString, int> HPInfo, ATKInfo, SpeedInfo;


    Zombie(QString _name, int _r);
    ~Zombie();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;
    void dead();
    void attack(Plant* p);


    QString name;
    int HP;
    int ATK;
    int speed;
    int row;
    int stage;

signals:
    // 僵尸死亡时发出信号
    void death(int i);
};

#endif // ZOMBIE_H
