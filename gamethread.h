#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QThread>

class GameThread : public QThread
{
    Q_OBJECT
public:
    explicit GameThread(QObject *parent = 0);
    void run();
    bool Stop;

signals:
    void FieldChanged(int);

public slots:

};

#endif // GAMETHREAD_H
