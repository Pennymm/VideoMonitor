#include "videowindowdisplay.h"
#include <QDebug>

VideoWindowDisplay::VideoWindowDisplay(QWidget *parent) : QWidget(parent)
{
    drawBackgroundImage();
    //    w = new QWidget(this->parent());
    //    QWidget *w = new QWidget(this->parentWidget());

    playBtn = new QPushButton(QIcon(":/Start.png"), "", this);
    playBtn->setGeometry(120, 230, 48, 48);
    playBtn->setIconSize(QSize(48, 48));
    playBtn->setStyleSheet("border : 0");
    //    playBtn->setFixedSize(48, 48);

    pauseBtn = new QPushButton(QIcon(":/Pause.png"), "", this);
    pauseBtn->setGeometry(120, 230, 48, 48);
    pauseBtn->setIconSize(QSize(48, 48));
    pauseBtn->setStyleSheet("border : 0");

    stack = new QStackedLayout;
    stack->addWidget(playBtn);
    stack->addWidget(pauseBtn);

    screenShotBtn = new QPushButton(QIcon(":/Photo.png"), "", this);
    screenShotBtn->setGeometry(170, 230, 48, 48);
    screenShotBtn->setIconSize(QSize(48, 48));
    screenShotBtn->setStyleSheet("border : 0");
    screenShotBtn->setEnabled(false);

    screenCapBtn = new QPushButton(QIcon(":/Video.png"), "", this);
    screenCapBtn->setGeometry(220, 230, 48, 48);
    screenCapBtn->setIconSize(QSize(48, 48));
    screenCapBtn->setStyleSheet("border : 0");
    screenCapBtn->setEnabled(false);

    stopRecordBtn = new QPushButton(QIcon(":/StopRecord.png"), "", this);
    stopRecordBtn->setGeometry(220, 230, 48, 48);
    stopRecordBtn->setIconSize(QSize(48, 48));
    stopRecordBtn->setStyleSheet("border : 0");

    recordLayout = new QStackedLayout;
    recordLayout->addWidget(screenCapBtn);
    recordLayout->addWidget(stopRecordBtn);


    enlargeBtn = new QPushButton(QIcon(":/FullScreen.png"), "", this);
    enlargeBtn->setGeometry(270, 230, 48, 48);
    enlargeBtn->setIconSize(QSize(48, 48));
    enlargeBtn->setStyleSheet("border : 0");
    enlargeBtn->setEnabled(false);

    exitBtn = new QPushButton(QIcon(":/Exit.png"), "", this);
    exitBtn->setGeometry(320, 230, 48, 48);
    exitBtn->setIconSize(QSize(48, 48));
    exitBtn->setStyleSheet("border : 0");

    //    address = new QLabel("IP : Port", this);
    //    videoInfo = new QLabel("Video Info", this);
    //    address->setGeometry(10, 230, 100, 20);
    //    videoInfo->setGeometry(10, 260, 80, 20);


    //在Qt5之后已经可以支持兰巴达表达式（Lambda expression in C++）
    connect(playBtn,&QPushButton::clicked,[this](){
        this->stack->setCurrentIndex(1);
        playBtnClickedSlot();

    });

    connect(pauseBtn,&QPushButton::clicked,[this](){
        this->stack->setCurrentIndex(0);
        th->terminate();
        //        th->wait();
        //        th->disconnect(ip, port);



    });
    connect(screenCapBtn,&QPushButton::clicked,[this](){
        this->recordLayout->setCurrentIndex(1);
    });
    connect(stopRecordBtn,&QPushButton::clicked,[this](){
        this->recordLayout->setCurrentIndex(0);
    });


    //     connect(enlargeBtn, &QPushButton::clicked, [this](int ok){
    /* connect(enlargeBtn, &QPushButton::clicked, [this](int ok){
                w = new QWidget(this->parent());
        if(!ok)
        {
            this->setParent(NULL);
            this->showFullScreen();
            //this->setGeometry((QApplication::desktop()->width()-this->width())/2, \
                            (QApplication::desktop()->height()-this->width())/2, \
                            this->width(), this->height());
            //this->show();

            //this->resize(1000,500);
        }else{
            //this->setParent(w);
        }
    });*/


    connect(enlargeBtn, SIGNAL(clicked()), this, SLOT(largeBtnClickedSlot()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(exitBtnClickedSlot()));
    connect(screenShotBtn, SIGNAL(clicked()), this, SLOT(shotBtnClickedSlot()));
    connect(screenCapBtn, SIGNAL(clicked()), this, SLOT(capBtnClickedSlot()));
    connect(stopRecordBtn, SIGNAL(clicked()), this, SLOT(stopBtnClickedSlot()));

}

void VideoWindowDisplay::drawBackgroundImage()
{
    image = new QImage(400, 300,QImage::Format_ARGB32);
    QPainter painter(image);

    painter.setPen(Qt::green);
    painter.setFont(QFont("黑体", 20, 5));
    painter.drawText(this->height()-50, this->width()+20,  ip);
    painter.drawText(this->height()-50, this->width()+20, port);

    //    address = new QLabel("IP : Port", this);
    //    videoInfo = new QLabel("Video Info", this);
    //    address->setGeometry(10, 230, 100, 20);
    //    videoInfo->setGeometry(10, 260, 80, 20);

    QLinearGradient line(0, 0, 400, 300);
    line.setColorAt(0, Qt::white);
    line.setColorAt(1, Qt::green);
    painter.setBrush(line);
    painter.drawRect(0, 0, 400, 300);
    painter.drawImage((400-128)/2, (300-128)/2, QImage(":/bg.png"));
}



void VideoWindowDisplay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    //    QRect target(0, 0, 400, 300);
    QRect target(0, 0, this->width(), this->height());
    painter.drawImage(target, *image);

}

void VideoWindowDisplay::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        this->setParent(w);
        this->setGeometry(rectOfVideo);
        this->showNormal();

        //        emit(videoBackSignal(this));



    }



}

/*void VideoWindowDisplay::startMonitor()
{
    QByteArray dataStream;
    QByteArray frame;

    QTcpSocket socket;

    socket.connectToHost(this->ip, this->port.toInt());

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
        QImage *img;
        img->loadFromData(frame, "JPEG");
        image = img;
        update();
        dataStream.remove(0, frame.size());

        //将image画在窗体中
        //继续读取下一张图片
    }
}*/

void VideoWindowDisplay::playBtnClickedSlot()
{
    playDialog *playdlg = new playDialog;
    //    playDialog playdlg;
    playdlg->exec();
    //    qDebug()<<playdlg->result();
    if(playdlg->result() == QDialog::Accepted)//playdlg-> == QDialog::Accepted...playdlg->btnBox->Ok
        //playdlg->isAccept
    {

        qDebug()<<"accept!";
        ip = playdlg->getIP();
        port =playdlg->getPort();
//        address->setText(ip);
//        videoInfo->setText(port);
        qDebug()<<playdlg->getIP();
        qDebug()<<playdlg->getPort()<<"   main";

        //        MyThread *th = new MyThread;
        th = new MyThread;

        th->initNetwork(ip, port.toInt());
        //        qDebug()<<th->getip()<<" : "<<th->getport()<<" by call function";
        th->start();

        enlargeBtn->setEnabled(true);
        screenShotBtn->setEnabled(true);
        screenCapBtn->setEnabled(true);

        connect(th, SIGNAL(sendImage(QImage*)), this, \
                SLOT(receiveImageSlot(QImage *)));
    }else{

        qDebug()<<"reject!";
        stack->setCurrentIndex(0);
    }
}

void VideoWindowDisplay::exitBtnClickedSlot()
{

    emit exitBtnSignal(this);
}

void VideoWindowDisplay::receiveImageSlot(QImage *img)
{
    image = img;
    update();
}

void VideoWindowDisplay::shotBtnClickedSlot()
{
    //    emit();
    QString str = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    str.append(".jpeg");

    QFile * fileOfScreen = new QFile(str);

    image->save(fileOfScreen, "JPEG", -1);

    fileOfScreen->close();
}

void VideoWindowDisplay::capBtnClickedSlot()
{

    th->record = true;

    th->startRecord();


}

void VideoWindowDisplay::stopBtnClickedSlot()
{
    th->record = false;
    if(th->avi)
    {
        AVI_close(th->avi);
        th->avi = NULL;
    }

}

void VideoWindowDisplay::enlargeBtnClickedSlot()
{
    ScreenShot * full = new ScreenShot;


    disconnect(th, SIGNAL(sendImage(QImage*)), this, \
               SLOT(receiveImageSlot(QImage *)));

    connect(th, SIGNAL(sendImage(QImage*)), full, \
            SLOT(receiveImageSlot(QImage *)));
    full->exec();


    connect(th, SIGNAL(sendImage(QImage*)), this, \
            SLOT(receiveImageSlot(QImage *)));



    //                th = new MyThread;

    //                th->initNetwork(ip, port.toInt());
    //                //        qDebug()<<th->getip()<<" : "<<th->getport()<<" by call function";
    //                th->start();


}

void VideoWindowDisplay::largeBtnClickedSlot()
{
    w = this->parentWidget();
    rectOfVideo = this->geometry();


    this->setParent(NULL);
    this->showFullScreen();
    QLabel *notice= new QLabel(this);
    notice->setText("press key of 'ESC' to exit fullscreen");
    notice->setGeometry(20, 20, 50, 20);

    //    QPainter painter;
    //    painter.brush()


}

