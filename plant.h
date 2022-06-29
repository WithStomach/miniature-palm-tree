#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsItem>

#include "card.h"

class Plant : public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    Plant();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent*);

    QString name;
    static QMap<QString, int> HPInfo;
    int HP;
    static const int level_limit[6];
    int XP,level;
    static QMap<QString, int> CooldownInfo;
    int cooldown;
    int stage;

    int row,column;

    bool AddPlant(Card *card);//用卡片种植
    void dead();//植物死亡


signals:
    void missilelaunch(QString missilename,int row,int column,int level=0);//向mainGame传递子弹信息
    void plant_clicked(int row,int column);
public slots:
    void movement();//植物行动
};

#endif // PLANT_H
