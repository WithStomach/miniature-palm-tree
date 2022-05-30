#include "optionbutton.h"
#include <QString>
#include <QPainter>
#include <QPropertyAnimation>
#include <QObject>

OptionButton::OptionButton(int width, int height, QString optionName)
{
    this->option = optionName;
    QPixmap img(":/pic/" + option + ".jpg");
    this->setFixedSize(width, height);
    img = img.scaled(this->width() * 0.5, this->height() * 0.5);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(img);
    this->setIconSize(QSize(this->width(), this->height()));
    connect(this, &QPushButton::pressed, this, &OptionButton::click_operation);
}

void OptionButton::click_animation1()
{

    QPropertyAnimation * animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(), this->y(),
                                   this->width(), this->height()));
    animation1->setEndValue(QRect(this->x(), this->y() + 10,
                                 this->width(), this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}

void OptionButton::click_animation2()
{

    QPropertyAnimation * animation2 = new QPropertyAnimation(this, "geometry");
    animation2->setDuration(200);
    animation2->setStartValue(QRect(this->x(), this->y() + 10,
                                   this->width(), this->height()));
    animation2->setEndValue(QRect(this->x(), this->y(),
                                 this->width(), this->height()));
    animation2->setEasingCurve(QEasingCurve::OutBounce);
    animation2->start();
}

void OptionButton::click_operation()
{
    this->click_animation1();
    this->click_animation2();
}
