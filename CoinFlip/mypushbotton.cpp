#include "mypushbotton.h"
#include <QPropertyAnimation>

MyPushbotton::MyPushbotton(QString normalImg,QString selectedImg)//构造函数
{
    this->normalImgPath = normalImg;
    this->selectedImgPath = selectedImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);

    //判断加载是否成功
    if(!ret)
    {
        return;
    }

     //设置固定大小
  this->setFixedSize(pix.width(),pix.height());

    //设置按钮样式为无边框
    this->setStyleSheet("QPushButton{border:0px;}");

    //加载图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(this->width(),this->height()));


}

void MyPushbotton::Zoom1() //下降动画
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设置动画时间
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y() + 10,this->width(),this->height()));

    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();

}

void MyPushbotton::Zoom2()//上升动画
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设置动画时间
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y() + 10,this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();



}

void MyPushbotton::mousePressEvent(QMouseEvent* e)
{
    //判断是否需要切换
    if(this->selectedImgPath != " ")
    {
        QPixmap pix;
        bool ret = pix.load(this->selectedImgPath);

        //判断加载是否成功
        if(!ret)
        {
            return;
        }

         //设置固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置按钮样式为无边框
        this->setStyleSheet("QPushButton{border:0px;}");

        //加载图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(this->width(),this->height()));
    }

    //其他情况抛给父类
    return QPushButton::mousePressEvent(e);

}
void MyPushbotton::mouseReleaseEvent(QMouseEvent* e)
{
    //判断是否需要切换
    if(this->normalImgPath!= " ")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);

        //判断加载是否成功
        if(!ret)
        {
            return;
        }

         //设置固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置按钮样式为无边框
        this->setStyleSheet("QPushButton{border:0px;}");

        //加载图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(this->width(),this->height()));
    }

    //其他情况抛给父类
    return QPushButton::mouseReleaseEvent(e);


}
