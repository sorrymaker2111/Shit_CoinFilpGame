#include "playscence.h"
#include "ui_playscence.h"
#include <QDebug>
#include <QPainter>
#include"mypushbotton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>

PlayScence::PlayScence(int levelNumber,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayScence)
{
    ui->setupUi(this);

        QString str = QString("您选择的是第 %1 关").arg(levelNumber);
        qDebug() << str;

        this->levelNumber = levelNumber;

        //关闭按钮
        connect(ui->actionclose,&QAction::triggered,this,[=](){

            this->close();
        });

        //胜利标志
        QLabel* winLabel = new QLabel(this);
        QPixmap pix;
        pix.load(":/res/LevelCompletedDialogBg.png");
        winLabel->setPixmap(pix);
        winLabel->setGeometry(0,0,pix.width(),pix.height());
        winLabel->move((this->width() - pix.width()) * 0.5,-pix.height());


        //返回按钮
        MyPushbotton* returnBtn = new MyPushbotton(":/res/BackButton.png",
                                                   ":/res/BackButtonSelected.png");

        //翻转音效
        QSound* filptSound = new QSound(":/res/ConFlipSound.wav",this);
        //胜利音效
        QSound* winSound = new QSound(":/res/LevelWinSound.wav",this);
        //返回音效
        QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);

        //设置返回按钮
        returnBtn->setParent(this);
        returnBtn->move(this->width() - returnBtn->width(),this->height() - returnBtn->height());

        //返回功能
        connect(returnBtn,&QPushButton::clicked,this,[=](){
            backSound->play();

            //延时触发信号
            QTimer::singleShot(200,this,[=](){
                emit this->Return_SelectedScence();
            });

        });

        //设置左下角关卡数显示

        //设置字体字号
        QFont font;
        font.setFamily("Aa奇思胖丫儿");
        font.setPointSize(20);

        QLabel* label = new QLabel(this);
        label->setGeometry(20,this->height() - 50,150,50);
        QString str2 = QString("LEVEL:%1").arg(this->levelNumber);
        label->setText(str2);
        label->setFont(font);


        //加载默认金币数据
        for(int i = 0;i < 4;i++)
        {
            for(int j = 0;j < 4;j++)
            {
                dataConfig dataconfig;
                this->coinArray[i][j] = dataconfig.mData[this->levelNumber][i][j];

            }
        }

        //设置金币背景
        for(int i = 0;i < 4;i++)
        {
            for(int j = 0;j < 4;j++)
            {
                QPixmap pix;
                pix.load(":/res/BoardNode.png");
                QLabel* label = new QLabel(this);
                label->setGeometry(0,0,pix.width(),pix.height());
                label->setPixmap(pix);
                label->move(57 + i * 50,200 + j * 50);

                //创建默认金币
                QString str3; //默认路径

                if(this->coinArray[i][j] == 1) //金币
                {
                     str3 = ":/res/Coin0001.png";
                }else {
                     str3 = ":/res/Coin0008.png";
                }

                MyCoin* coin = new MyCoin(str3);
                this->coin[i][j] = coin;
                coin->setParent(this);
                coin->move(59 + i * 50,204 + j * 50);

                //设置金币属性
                coin->posX = i;
                coin->posY = j;
                coin->flag = this->coinArray[i][j];


            }
        }

            //翻转金币实现
            for(int i = 0;i < 4;i++)
            {
                for(int j = 0;j < 4;j++)
                {
                    //连接翻转金币的槽函数
                    connect(coin[i][j],&QPushButton::clicked,this,[=](){
                        //翻转音效
                        filptSound->play();

                        //点击按钮后先禁用按钮点击功能

                        for(int i = 0;i < 4;i++)
                        {
                            for(int j = 0;j < 4;j++)
                            {
                                this->coin[i][j]->isWin = true;
                            }
                        }


                        coin[i][j]->ChangeCoin();
                        //更新数据
                        this->coinArray[i][j] = this->coinArray[i][j] == 0 ? 1 : 0;

                        //翻转周围金币,实现延时效果

                        QTimer::singleShot(300,this,[=](){
                            //翻转上侧金币
                            if(coin[i][j]->posY - 1 >= 0)
                            {
                                this->coin[coin[i][j]->posX][coin[i][j]->posY - 1]->ChangeCoin();

                                //更新数据
                                this->coinArray[coin[i][j]->posX][coin[i][j]->posY - 1] = this->coinArray[coin[i][j]->posX][coin[i][j]->posY - 1] == 0 ? 1 : 0;
                            }

                            //翻转下侧金币
                            if(coin[i][j]->posY + 1 <= 3)
                            {
                                this->coin[coin[i][j]->posX][coin[i][j]->posY + 1]->ChangeCoin();

                                //更新数据
                                this->coinArray[coin[i][j]->posX][coin[i][j]->posY + 1] = this->coinArray[coin[i][j]->posX][coin[i][j]->posY + 1] == 0 ? 1 : 0;
                            }

                            //翻转左侧金币
                            if(coin[i][j]->posX - 1 >= 0)
                            {
                                this->coin[coin[i][j]->posX - 1][coin[i][j]->posY]->ChangeCoin();

                                //更新数据
                                this->coinArray[coin[i][j]->posX - 1][coin[i][j]->posY] = this->coinArray[coin[i][j]->posX - 1][coin[i][j]->posY] == 0 ? 1 : 0;
                            }

                            //翻转右侧金币
                            if(coin[i][j]->posX + 1 <= 3)
                            {
                                this->coin[coin[i][j]->posX + 1][coin[i][j]->posY]->ChangeCoin();

                                //更新数据
                                this->coinArray[coin[i][j]->posX + 1][coin[i][j]->posY] = this->coinArray[coin[i][j]->posX + 1][coin[i][j]->posY] == 0 ? 1 : 0;
                            }



                            //金币翻转完后再启用
                            for(int i = 0;i < 4;i++)
                            {
                                for(int j = 0;j < 4;j++)
                                {
                                    this->coin[i][j]->isWin = false;
                                }
                            }

                            //判断胜利
                            for(int i = 0;i < 4;i++)
                            {
                                for(int j = 0;j < 4;j++)
                                {
                                    this->isWin += this->coin[i][j]->flag;
                                }
                            }



                            if(this->isWin == 16)
                            {
                                //胜利音效
                                winSound->play();

                               qDebug() << "游戏胜利!";

                               //更新coin的isWin
                               for(int i = 0;i < 4;i++)
                               {
                                   for(int j = 0;j < 4;j++)
                                   {
                                       this->coin[i][j]->isWin = true;
                                   }
                               }



                               //胜利图标动画
                               QPropertyAnimation* animation = new QPropertyAnimation(winLabel,"geometry");

                               //持续时间
                               animation->setDuration(1000);

                               //开始关键帧
                               animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                               //结束关键帧
                               animation->setEndValue(QRect(winLabel->x(),winLabel->y() + 114,winLabel->width(),winLabel->height()));

                               //拉曲线
                               animation->setEasingCurve(QEasingCurve::OutBounce);

                               animation->start();

                            }else
                            {
                                //未完成，重置数据
                                this->isWin = 0;
                            }

                        });




                    });
                }
            }


}

//PlayScence::PlayScence(int levelNumber)
//{
//    ui->setupUi(this);

//    QString str = QString("您选择的是第 %1 关").arg(levelNumber);
//    qDebug() << str;

//    this->levelNumber = levelNumber;

//    //关闭按钮
//    connect(ui->actionclose,&QAction::triggered,this,[=](){

//        this->close();
//    });

//    //返回按钮
//    MyPushbotton* returnBtn = new MyPushbotton(":/res/BackButton.png",
//                                               ":/res/BackButtonSelected.png");

//    //设置返回按钮
//    returnBtn->setParent(this);
//    returnBtn->move(this->width() - returnBtn->width(),this->height() - returnBtn->height());

//    //返回功能
//    connect(returnBtn,&QPushButton::clicked,this,[=](){

//        //延时触发信号
//        QTimer::singleShot(500,this,[=](){
//            emit this->Return_SelectedScence();
//        });

//    });

//}

void PlayScence::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //title
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5,30,pix);
}


PlayScence::~PlayScence()
{
    delete ui;
}
