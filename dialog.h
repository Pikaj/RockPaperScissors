#ifndef DIALOG_H
#define DIALOG_H

#include "mythread.h"
#include "game.h"
#include <QDialog>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <iostream>
#include <stdio.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    MyThread *mThread;
    Game game_window;
    bool game;
    void updateGraphicsView(QImage img);

private:
    Ui::Dialog *ui;

public slots:
    void onImageChanged(int Number, QImage img);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // DIALOG_H
