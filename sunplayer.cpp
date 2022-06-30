#include "sunplayer.h"
#include <QFont>
#include <QPainter>
#include <QString>
#include <QRectF>
#include <QPixmap>
#include <QDebug>

SunPlayer::SunPlayer() : QObject()
{
    sun = 150;
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

void SunPlayer::advance(int step = 1)
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

ShadowPlayer::ShadowPlayer()
{
    setZValue(30);
    shadow_timer = 400;
}

ShadowPlayer::~ShadowPlayer()
{

}

QRectF ShadowPlayer::boundingRect() const
{
    return QRectF(0, 0, 600, 80);
}

void ShadowPlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setFont(QFont("宋体", 15));
    painter->setPen(Qt::red);
    QString t = "距离阴影刷新：" + QString::number(int(shadow_timer * 0.1));
    painter->drawText(0, 0, 600, 80, Qt::AlignCenter, t);
}

void ShadowPlayer::advance(int step)
{
    if(!step)
        return;
    shadow_timer--;
    if(shadow_timer == 0){
        shadow_timer = 400;
        update();
        return;
    }
    update();
}
