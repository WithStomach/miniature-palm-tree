#include "shadow.h"
#include <QRectF>
#include <QPixmap>
#include <QPainter>
#include <QTime>

Shadow::Shadow() : QObject()
{
    setZValue(1);
    setAcceptTouchEvents(true);
    update_time = 0;
    row = -1;
    cloumn = -1;
}

Shadow::~Shadow()
{

}

QRectF Shadow::boundingRect() const
{
    return QRectF(0, 0, 70, 70);
}

void Shadow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPixmap ii(":/pic/shadow.png");
    painter->drawPixmap(0, 0, ii.width(), ii.height(), ii);
}

void Shadow::advance(int step = 1)
{
    if(!step)
        return;
    update_time++;
    if(update_time == 400){
        update_time = 0;
        //qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        row = qrand() % 5;
        cloumn = qrand() % 3;
        setPos(80 * cloumn - 250,190 - row * 100);
        emit shadow_cover(row, cloumn);
        return;
    }
    emit shadow_cover(row, cloumn);
}

void Shadow::init()
{
    update_time = 0;
    //qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    row = qrand() % 5;
    cloumn = qrand() % 3;
    setPos(80 * cloumn - 250, 190 - row * 100);
    emit shadow_cover(row, cloumn);
}
