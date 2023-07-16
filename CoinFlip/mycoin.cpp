#include "mycoin.h"

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString filePath) //构造函数
{

    QPixmap pix;
    bool ret = pix.load(filePath);

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

   this->timer1 = new QTimer(this); //正面翻反面
   this->timer2 = new QTimer(this); //反面翻正面

    //正面翻反面
    connect(this->timer1,&QTimer::timeout,this,[=](){
     QString str = QString(":/res/Coin000%1.png").arg(this->min++);

     QPixmap pix2;
     bool ret = pix2.load(str);

     //判断加载是否成功
     if(!ret)
     {
         return;
     }

      //设置固定大小
     this->setFixedSize(pix2.width(),pix2.height());

     //设置按钮样式为无边框
     this->setStyleSheet("QPushButton{border:0px;}");

     //加载图标
     this->setIcon(pix2);

     //设置图标大小
     this->setIconSize(QSize(this->width(),this->height()));

     //判断越界
    if(this->min > this->max)
    {
        this->timer1->stop();
        this->isAnimation = false;
        this->min = 1; //更新数据
    }


    });

    //反面翻正面
    connect(this->timer2,&QTimer::timeout,this,[=](){
     QString str = QString(":/res/Coin000%1.png").arg(this->max--);

     QPixmap pix2;
     bool ret = pix2.load(str);

     //判断加载是否成功
     if(!ret)
     {
         return;
     }

      //设置固定大小
     this->setFixedSize(pix2.width(),pix2.height());

     //设置按钮样式为无边框
     this->setStyleSheet("QPushButton{border:0px;}");

     //加载图标
     this->setIcon(pix2);

     //设置图标大小
     this->setIconSize(QSize(this->width(),this->height()));

     //判断越界
    if(this->max < this->min)
    {
        this->timer2->stop();
        this->isAnimation = false;
        this->max= 8; //更新数据
    }


    });


}


void MyCoin::ChangeCoin()//翻转金币
{
    //正面翻反面
    if(this->flag)
    {
        this->timer1->start(30);
        this->isAnimation = true;


        this->flag = 0;
    }else {
    //反面翻正面
    this->timer2->start(30);
        this->isAnimation = true;

        this->flag = 1;
}






}

void MyCoin::mousePressEvent(QMouseEvent* e) //判断动画执行来决定是否点击有用
{
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else {
        QPushButton::mousePressEvent(e); //交给父亲
    }

}
