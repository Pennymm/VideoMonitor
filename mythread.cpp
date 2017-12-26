#include "mythread.h"
#include <QDebug>


MyThread::MyThread(QObject *parent) : QThread(parent)
{
    //    run();
    record = false;
    avi = NULL;
}

MyThread::~MyThread()
{

}

void MyThread::initNetwork(QString ip, int port)
{
    this->ip = ip;
    this->port = port;
    qDebug()<<this->ip << " : "<< this->port;
}

void MyThread::startRecord()
{
    QString str = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    str.append(".avi");
    //    QFile *fileOfRecord = new QFile(str);
    avi = AVI_open_output_file(str.toUtf8().data());
    AVI_set_video(avi, 640, 480, 9, "MJPG");
}

QString MyThread::getip()
{
    return this->ip;
}

int MyThread::getport()
{
    return this->port;
}

void MyThread::run()
{
    QByteArray dataStream;
    QByteArray frame;

    QTcpSocket socket;

    socket.connectToHost(ip, port);

    if(socket.waitForConnected()){
        //success
        qDebug()<<"connect success";

    }else{
        qDebug()<<"connect fail";
    }

    QByteArray req;
    req.append("?action=stream\n");
    socket.write(req);
    if(socket.waitForBytesWritten(3000)){
        qDebug()<<"write success";
    }else{
        qDebug()<<"write error";
    }
    //接收服务器回复的视频数据
    while(!dataStream.contains("\r\n\r\n")){
        if(socket.waitForReadyRead(3000)){
            dataStream.append(socket.readAll());
        }
    }
    //校验并删除报头信息

    dataStream.remove(0, dataStream.indexOf("\r\n\r\n")+4);
    while(true){
        while(!dataStream.contains("\r\n--")){
            if(socket.waitForReadyRead(3000)){
                dataStream.append(socket.readAll());
            }
        }
        //继续接收视频流，提取图片
        dataStream.remove(0, dataStream.indexOf("\n\n")+2);
        frame = dataStream.mid(0, dataStream.indexOf("\r\n--"));
        //将frame转换成image
        QImage *img = new QImage;
        img->loadFromData(frame, "JPEG");

        //        image = img;
        emit(sendImage(img));
        //        update();
        dataStream.remove(0, frame.size()+4);

        //将image画在窗体中
        //继续读取下一张图片

        if(record)
        {
            if((AVI_write_frame(avi, frame.data(), frame.size(), 0)) < 0)
            {
                qDebug()<<"write frame to avi fail!";
            }

        }
    }
}

void MyThread::screenShotSlot()
{

}
