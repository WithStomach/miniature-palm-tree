/*
 * 主菜单界面
 * 基本构架：
 * 1）开始游戏按钮
 * 2）退出游戏按钮
 * 3）保存游戏与读取存档
 * 4）成就（？）
 * 注：各按钮均使用OptionButton类
 * 每个按键对应槽函数在该类中实现
 * 按钮详情参见optionbutton.h
 */
#ifndef MAINMENU_H
#define MAINMENU_H
#include <QWidget>
#include "gamescene.h"

static const QString iconPath = ""; //窗口图标路径
static const QString bkgPath = ":/pic/beginMenu.png"; //背景图片路径
static const int mainWidth = 1020, mainHeight = 600; //主窗口尺寸

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();
    void paintEvent(QPaintEvent* );
    void game_start();//游戏开始
private:
    Ui::MainMenu *ui;
    GameScene* gameWidget;

};

#endif // MAINMENU_H
