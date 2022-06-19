#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsItem>

static const int zombieWidth = 50, zombieHeight = 150;

class Zombie :public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    Zombie(QString _name);
    ~Zombie();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;
    void dead();

    QString name;
    static int zombieNum;
    static QMap<QString, int> HPInfo, ATKInfo, SpeedInfo;
    int HP;
    int ATK;
    int speed;


signals:
    void death();
};

#endif // ZOMBIE_H
