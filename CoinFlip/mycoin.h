#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString filePath); //构造函数

public:
    int posX;//金币x坐标
    int posY;//金币y坐标
    bool flag;//正反状态
    bool isAnimation = false; //判断是否处于动画中
    bool isWin = false; //判断是否胜利

public:
    //翻转效果的实现
    QTimer* timer1; //正面翻反面
    QTimer* timer2; //反面翻正面
    int min = 1; //图片数
    int max = 8; //图片数
    void ChangeCoin();//翻转金币

public:
    void mousePressEvent(QMouseEvent* e);
signals:

public slots:
};

#endif // MYCOIN_H
