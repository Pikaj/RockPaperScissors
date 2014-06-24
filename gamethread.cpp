#include "gamethread.h"
#include <QtCore>

GameThread::GameThread(QObject *parent) :
    QThread(parent)
{
}

void GameThread::run()
{
    for(int i=0; i < 1000; i++)
    {
        if(this->Stop) break;

        emit FieldChanged(i % 4);

        sleep(1);
    }
}
