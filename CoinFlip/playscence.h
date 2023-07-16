#ifndef PLAYSCENCE_H
#define PLAYSCENCE_H

#include <QMainWindow>
#include"mycoin.h"

namespace Ui {
class PlayScence;
}

class PlayScence : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayScence(int levelNumber,QWidget *parent = nullptr);
    //PlayScence(int levelNumber);
    ~PlayScence();
     void paintEvent(QPaintEvent*);
public:
    int levelNumber; //关卡编号
    int coinArray[4][4]; //存放金币信息的二维数组
    int isWin = 0; //判断是否胜利
    MyCoin* coin[4][4]; //存放金币的二维数组

signals:
    void Return_SelectedScence();

private:
    Ui::PlayScence *ui;
};

#endif // PLAYSCENCE_H
