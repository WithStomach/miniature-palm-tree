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
    void clicked();
    void mousePressEvent(QGraphicsSceneMouseEvent*);

    QString name;
    static QMap<QString, int> CostInfo;
    int cost,number;
    bool is_clicked;

signals:
    void card_clicked(int n);
};

#endif // CARD_H
