#ifndef MYPUSHBOTTON_H
#define MYPUSHBOTTON_H

#include <QPushButton>
#include <QString>


class MyPushbotton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushbotton(QWidget *parent = nullptr);
    MyPushbotton(QString normalImg,QString selectedImg = " ");//构造函数
    void Zoom1(); //下降动画
    void Zoom2(); //上升动画
public:
    QString normalImgPath; //默认图片路径
    QString selectedImgPath;//选中图片路径
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);


signals:


public slots:
};

#endif // MYPUSHBOTTON_H
