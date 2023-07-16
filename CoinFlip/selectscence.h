#ifndef SELECTSCENCE_H
#define SELECTSCENCE_H

#include <QMainWindow>
#include "playscence.h"

namespace Ui {
class SelectScence;
}

class SelectScence : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectScence(QWidget *parent = nullptr);
    ~SelectScence();
    void paintEvent(QPaintEvent*);


signals:
        void Ruturn_MainScence(); //返回信号

private:
    Ui::SelectScence *ui;
};

#endif // SELECTSCENCE_H
