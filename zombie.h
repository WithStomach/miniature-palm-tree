#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsItem>

static bool e = true;
static QMap<QString, int> zombieHPInfo, zombieATKInfo, zombieSpeedInfo;

class zombie : public QGraphicsItem{
public:
    zombie(QString _name);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;

    QString name;
    int HP;
    int ATK;
    int speed;
    
};

#endif // ZOMBIE_H
