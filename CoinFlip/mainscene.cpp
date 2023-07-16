#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbotton.h"
#include "selectscence.h"
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //选择关卡场景
    SelectScence* selectscence = new SelectScence;

    //关闭按钮
    connect(ui->actionclose,&QAction::triggered,this,[=](){

        this->close();
    });

    //加载开始按钮音效
    QSound* startSound = new QSound(":/res/TapButtonSound.wav",this);
//    startSound->setLoops(-1);
//    startSound->play();

    //开始按钮
    MyPushbotton * startBotton = new MyPushbotton(":/res/MenuSceneStartButton.png");
    startBotton->setParent(this);

    //设置按钮位置居中
    startBotton->move(this->width() * 0.5 - startBotton->width() * 0.5,
                      this->height() * 0.7);

    //监听返回信号
    connect(selectscence,&SelectScence::Ruturn_MainScence,this,[=](){
        this->setGeometry(selectscence->geometry());
        selectscence->hide();
        this->show();
    });

    //点击按钮动画
    connect(startBotton,&QPushButton::clicked,this,[=](){
        //按钮音效
        startSound->play();

        startBotton->Zoom1();
        startBotton->Zoom2();

        //延时切换
        QTimer::singleShot(500,this,[=](){
            //设置切换场景的geometry
            selectscence->setGeometry(this->geometry());
            this->hide();
            selectscence->show();
        });
    });

}

//背景图片
void MainScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //title
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);
    painter.drawPixmap(10,30,pix);
}

MainScene::~MainScene()
{
    delete ui;
}
