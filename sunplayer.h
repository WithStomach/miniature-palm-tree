#ifndef SUNPLAYER_H
#define SUNPLAYER_H

#include <QObject>
#include <QGraphicsItem>

class SunPlayer : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit SunPlayer();
    ~SunPlayer();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;

    int sun;//阳光值
    int sun_timer;//阳光自动回复计时器

signals:

public slots:
};

class ShadowPlayer : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ShadowPlayer();
    ~ShadowPlayer();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void advance(int step) Q_DECL_OVERRIDE;

    int shadow_timer;//阴影刷新倒计时计时器

signals:

public slots:
};

#endif // SUNPLAYER_H
