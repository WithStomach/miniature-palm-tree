#include "sunplayer.h"
#include <QFont>
#include <QPainter>
#include <QString>
#include <QRectF>
#include <QPixmap>
#include <QDebug>

SunPlayer::SunPlayer() : QObject()
{
    sun = 50;
    sun_timer = 0;
    setZValue(3);
}

SunPlayer::~SunPlayer()
{

}

QRectF SunPlayer::boundingRect() const
{
    return QRectF(0, 0, 100, 103);
}

void SunPlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPixmap ii(":/pic/Sun.png");
    painter->drawPixmap(0, 0, ii.width(), ii.height(), ii);
    QFont font1;
    font1.resolve(QFont::AllPropertiesResolved);
    painter->setFont(font1);
    painter->setPen(Qt::red);
    painter->drawText(0, 0, 100, 103, Qt::AlignCenter, QString::number(sun));

}

void SunPlayer::advance(int step)
{
    if(!step)
        return;
    sun_timer++;
    if(sun_timer == 200){
        sun_timer = 0;
        sun += 25;
        update();
    }
}
