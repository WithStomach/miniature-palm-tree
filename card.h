#ifndef CARD_H
#define CARD_H

#include <QGraphicsItem>

class Card : public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    Card(QString _name);
    ~Card();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;

    QString name;
    int cost;
};

#endif // CARD_H
