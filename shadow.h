#ifndef SHADOW_H
#define SHADOW_H

#include <QObject>
#include <QGraphicsItem>

class Shadow : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Shadow();
    ~Shadow();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;
    int update_time;
    int row,cloumn;
    void init();
    void re_born();
signals:
    void shadow_cover(int, int);
public slots:

};

#endif // SHADOW_H
