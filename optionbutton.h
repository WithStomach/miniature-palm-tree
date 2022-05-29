/*
* 功能性按钮类
* 1）各按键直接以其实现功能命名（option）
* 2）每个按键动画已实现
* 3）按键贴图请已option命名，且确保格式为jpg
* 注：本文件中不定义按键对应槽函数。
*/
#ifndef OPTIONBUTTON_H
#define OPTIONBUTTON_H

#include <QPushButton>

class OptionButton : public QPushButton
{
    Q_OBJECT

public:
    OptionButton(int width, int height, QString optionName);
    void click_animation1();
    void click_animation2();
    void click_operation();

    QString option;

};

#endif // OPTIONBUTTON_H
