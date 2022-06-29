#ifndef MISSILE_H
#define MISSILE_H

#include <QGraphicsItem>

#ifndef ZOMBIE_H
#include "zombie.h"
#endif


class Missile : public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    Missile(QString _name,int lvl);
    ~Missile();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;

    QString name;
    static QMap<QString, int> DamageInfo;
    int damage;
    int speed;
    int level;

    void hit(Zombie* target);
};

#endif // MISSILE_H
