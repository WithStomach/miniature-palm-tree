#ifndef MISSILE_H
#define MISSILE_H

#include <QGraphicsItem>

class Missile : public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    Missile(QString _name);
    ~Missile();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;

    QString name;
    int damage;
};

#endif // MISSILE_H
