#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QTcpSocket>
#include <QImage>
#include <QFile>
#include <QDateTime>

extern "C"
{
    #include "avilib.h"

}


class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    ~MyThread();
    void initNetwork(QString ip, int port);
    void startRecord();
//    void stopRecord();

            avi_t *avi;


    bool record;
//    void
    QString getip();
    int getport();

protected:
    void run();

signals:

    void sendImage(QImage *img);
    void sendSuccessMsg();

public slots:
    void screenShotSlot();

private:
    QString ip;
    int port;


};

#endif // MYTHREAD_H
