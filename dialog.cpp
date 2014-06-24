#include "dialog.h"
#include "ui_dialog.h"
#include <QtGui>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    game = false;

    mThread = new MyThread(this);
    connect(mThread, SIGNAL(ImageChanged(int, QImage)), this,SLOT(onImageChanged(int, QImage)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onImageChanged(int Number, QImage img)
{
    if(!game)
    {
        if(Number == 1) ui->label->setText("Kamień");
        else if (Number == 2) ui->label->setText("Papier");
        else if (Number == 3) ui->label->setText("Nożyczki");
        else ui->label->setText("Nie wykryto");
        updateGraphicsView(img);
    } else {
        game_window.updatePlayer(img);
        game_window.updateList(Number);
    }
}

void Dialog::on_pushButton_clicked()
{
    //Started
    mThread->Stop = false;
    mThread->start();
}

void Dialog::on_pushButton_2_clicked()
{
    //Stoped
    mThread->Stop = true;
}

void Dialog::on_pushButton_3_clicked()
{
    on_pushButton_clicked();
    game = true;
    mThread->game_window = true;
    game_window.show();
}


void Dialog::updateGraphicsView(QImage img)
{
    //QImage img2 = this->getQImageFromIplImage(img1);
    //QImage img2("/home/ania/projekty/RockPaperScissor/image.png");

    QGraphicsScene* scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::black);
    scene->addPixmap(QPixmap::fromImage(img));

    ui->graphicsView->show();
}

