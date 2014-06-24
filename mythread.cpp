#include "mythread.h"
#include <QtCore>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <iostream>
#include <stdio.h>
#include <QtGui>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

QMutex MyThread::mutex;

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
    game_window = false;

    //HAND GESTURE
    scale = 1.1;

    storage = 0;
    capture = 0;

    storage = cvCreateMemStorage(0);
    capture = cvCreateCameraCapture(0);

    frame = 0;

    cascade_palm = 0;
    cascade_fist = 0;
    cascade_scissor = 0;

    cascade_palm_name = "/home/ania/projekty/RockPaperScissor/XML/hand.xml"; //PALM - Paper
    cascade_fist_name = "/home/ania/projekty/RockPaperScissor/XML/fist.xml"; //FIST - Rock
    cascade_scissor_name = "/home/ania/projekty/RockPaperScissor/XML/palm.xml"; //SCISSOR

    loadFiles();
}

void MyThread::run()
{
    for(int i=0; i < 10000; i++)
    {
        if(this->Stop) break;

        frame = cvQueryFrame( capture);
        QImage img = getQImageFromIplImage(detectAndDraw(frame));
        //QImage img("/home/ania/projekty/RockPaperScissor/image.png");
        emit ImageChanged(result, img);

        this->msleep(10);
    }
}

QImage MyThread::getQImageFromIplImage(IplImage *frame)
{
    QImage qImg;
    IplImage *iplImg = cvCreateImage(cvSize(frame->width, frame->height),IPL_DEPTH_8U, 3);
    cvCvtColor(frame, iplImg, CV_BGR2RGB);
    qImg = QImage((uchar *)iplImg->imageData, iplImg->width, iplImg->height, QImage::Format_RGB888);

    return qImg;
}

IplImage* MyThread::detectAndDraw(IplImage *img)
{
    float scale_img;
    if(game_window) scale_img = 0.23;
    else scale_img = 0.7;
    CvPoint pt1, pt2;
    int i;
    int max_palm = 0, max_fist = 0, max_scissor = 0;

    cvResizeWindow("result", 800, 600);
    cvMoveWindow("result", 0,0);

    cvClearMemStorage( storage );
    /*** PALM ***/
    if(cascade_palm){
        CvSeq* faces = cvHaarDetectObjects(
                img,
                cascade_palm,
                storage,
                scale, 2, CV_HAAR_DO_CANNY_PRUNING,
                cvSize(24, 24) );
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;
            if (abs(pt1.x - pt2.x) * abs(pt1.y - pt2.y) > max_palm)
                max_palm = abs(pt1.x - pt2.x) * abs(pt1.y - pt2.y);
            cvRectangle( img, pt1, pt2, CV_RGB(200, 0, 0), 1, 8, 0 );
        }
    }

    /*** FIST ***/
    if(cascade_fist){
        CvSeq* faces = cvHaarDetectObjects(
                img,
                cascade_fist,
                storage,
                scale, 2, CV_HAAR_DO_CANNY_PRUNING,
                cvSize(24, 24) );
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;
            if (abs(pt1.x - pt2.x) * abs(pt1.y - pt2.y) > max_fist)
                max_fist = abs(pt1.x - pt2.x) * abs(pt1.y - pt2.y);
            //fprintf(stderr,"%d\n", max_fist);
            cvRectangle( img, pt1, pt2, CV_RGB(64, 64, 255), 1, 8, 0 );
        }
    }

    /*** SCISSORS ***/
    if(cascade_scissor){
        CvSeq* faces = cvHaarDetectObjects(
                img,
                cascade_scissor,
                storage,
                scale, 2, CV_HAAR_DO_CANNY_PRUNING,
                cvSize(24, 24) );
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;
            if (abs(pt1.x - pt2.x) * abs(pt1.y - pt2.y) > max_scissor)
                max_scissor = abs(pt1.x - pt2.x) * abs(pt1.y - pt2.y);
            //fprintf(stderr,"%d\n", max_scissor);
            cvRectangle( img, pt1, pt2, CV_RGB(255, 255, 128), 1, 8, 0 );
        }
    }

    if (max_scissor > 10000)  result = 2;
    else if (max_palm > 40000 && max_fist < 10000) result = 3;
    else if (max_fist >= 10000) result = 1;
    else result = 0;

    return img_resize(img, scale_img);

    /*if (max_scissor > 10000)  fprintf(stderr,"papier\n");
    else if (max_palm > 50000 && max_fist < 10000) fprintf(stderr,"nozyczki\n");
    else if (max_fist >= 10000) fprintf(stderr,"kamien\n");*/
}

IplImage* MyThread::img_resize(IplImage* src_img, float scale)
{
    IplImage* des_img;
    int new_height = src_img->height * scale;
    int new_width = src_img->width * scale;
    des_img=cvCreateImage(cvSize(new_width,new_height),src_img->depth,src_img->nChannels);
    cvResize(src_img,des_img,CV_INTER_LINEAR);
    return des_img;
}

bool MyThread::loadFiles()
{
    this->cascade_palm = (CvHaarClassifierCascade*)cvLoad( cascade_palm_name, 0, 0, 0 );
    if( !this->cascade_palm )
        return false;

    /*** FIST ***/
    this->cascade_fist = (CvHaarClassifierCascade*)cvLoad( cascade_fist_name, 0, 0, 0 );
    if( !this->cascade_fist )
        return false;

    /*** SCISSOR ***/
    this->cascade_scissor = (CvHaarClassifierCascade*)cvLoad( cascade_scissor_name, 0, 0, 0 );
    if( !this->cascade_fist )
        return false;

    return true;
}

