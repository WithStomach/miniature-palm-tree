#include "optionbutton.h"
#include <QString>
#include <QPainter>

OptionButton::OptionButton(int width, int height, QString optionName)
{
    this->option = optionName;
    QPixmap img(":/" + option + ".jpg");
    this->setFixedSize(width, height);
    img = img.scaled(this->width() * 0.5, this->height() * 0.5);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(img);
    this->setIconSize(QSize(this->width(), this->height()));
}
