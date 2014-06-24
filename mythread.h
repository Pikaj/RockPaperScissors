#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QtCore>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <iostream>
#include <stdio.h>
#include <QtGui>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    bool game_window;
    void run();
    bool Stop;

signals:
    void ImageChanged(int Number, QImage img);

public slots:

private:
    static QMutex mutex;

    //HAND GESTURE
    double scale;
    int result;

    CvCapture *capture;
    IplImage *frame;
    CvMemStorage* storage;
    CvHaarClassifierCascade* cascade_palm;
    CvHaarClassifierCascade* cascade_fist;
    CvHaarClassifierCascade* cascade_scissor;

    const char* cascade_palm_name;
    const char* cascade_fist_name;
    const char* cascade_scissor_name;

    IplImage* detectAndDraw(IplImage *img);
    IplImage* img_resize(IplImage* src_img, float scale);
    QImage getQImageFromIplImage(IplImage *frame);
    bool loadFiles();

};

#endif // MYTHREAD_H
