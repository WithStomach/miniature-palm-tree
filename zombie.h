#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsItem>

static const int zombieWidth = 50, zombieHeight = 150;

class Zombie : public QGraphicsItem{
public:
    Zombie(QString _name);
    ~Zombie();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;

    QString name;
    static int zombieNum;
    static QMap<QString, int> HPInfo, ATKInfo, SpeedInfo;
    int HP;
    int ATK;
    int speed;
    
};

#endif // ZOMBIE_H
