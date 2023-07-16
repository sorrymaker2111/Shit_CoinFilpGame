#include "selectscence.h"
#include "ui_selectscence.h"
#include <QPainter>
#include "mypushbotton.h"
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QSound>


SelectScence::SelectScence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectScence)
{
    ui->setupUi(this);

    //关闭按钮
    connect(ui->actionclose,&QAction::triggered,this,[=](){

        this->close();
    });

    //返回按钮
    MyPushbotton* returnBtn = new MyPushbotton(":/res/BackButton.png",
                                               ":/res/BackButtonSelected.png");

    //返回按钮音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);
    //选择按钮音效
    QSound* selectSound = new QSound(":/res/TapButtonSound.wav",this);

    //设置返回按钮
    returnBtn->setParent(this);
    returnBtn->move(this->width() - returnBtn->width(),this->height() - returnBtn->height());

    //返回功能
    connect(returnBtn,&QPushButton::clicked,this,[=](){
         //返回按钮音效
        backSound->play();

        //延时触发信号
        QTimer::singleShot(500,this,[=](){
            emit this->Ruturn_MainScence();
        });

    });

    //设置关卡按钮
    for(int i = 0;i < 20;i++)
    {
        //设置按钮
        MyPushbotton* Btn = new MyPushbotton(":/res/LevelIcon.png");
        Btn->setParent(this);
        Btn->move(25 + i % 4 * 70,130 + i / 4 * 70);

        //设置图标
        QLabel* label = new QLabel(this);
        label->setText(QString::number(i + 1));
        label->move(5+ i % 4 * 70,145 + i / 4 * 70);
        //居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //连接
        connect(Btn,&QPushButton::clicked,this,[=](){
            //选择关卡音效
            selectSound->play();

            //用字符集
            QString str =  QString("您选择的是第 %1 关").arg(i + 1);

            qDebug() << str;

            //进入游戏场景
            PlayScence* play = new PlayScence(i + 1);
            play->setGeometry(this->geometry());
            this->hide();
            play->show();

            //监听返回信号
            connect(play,&PlayScence::Return_SelectedScence,this,[=]()mutable{
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;

            });

        });

        //鼠标穿透
       label->setAttribute(Qt::WA_TransparentForMouseEvents);



    }
}

//背景图片
void SelectScence::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //title
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5,30,pix);
}

SelectScence::~SelectScence()
{
    delete ui;
}
