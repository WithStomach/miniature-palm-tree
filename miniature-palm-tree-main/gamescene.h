/*
* 主要游戏界面：
* 1）暂停键：点击左上角按键或按下空格键均可暂停游戏并调出菜单栏
* 2）商店界面：具体功能见store.h
* 3）地图：大小5 * 9， 包含阴影机制的实现
* 4）随时间生成僵尸
* 5）其余美化贴图
*/

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>

static QString const mapPath = ":/pic/background.jpg";

class GameScene : public QWidget
{
    Q_OBJECT
public:
    GameScene(QWidget *parent = 0);
    void game_start();
public slots:
    void zombie_construct(int last_row);
    void missile_construct(QString missilename,int row,int column);
public:
    QGraphicsScene* mainGame;
    QGraphicsView* gameMap;
};

#endif // GAMESCENE_H
