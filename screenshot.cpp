#include "screenshot.h"

ScreenShot::ScreenShot(QDialog *parent) : QDialog(parent)
{

    this->showFullScreen();
    image = new QImage;

//    connect(this->parent()->)


//    connect(this->parent()->
    // largeTh = new MyThread;

    //    largeTh->
    //    connect(largeTh, SIGNAL(sendImage(QImage*)), );

    //    largeTh->
}

void ScreenShot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect target(0, 0, this->width(), this->height());
    painter.drawImage(target, *image);

}

void ScreenShot::receiveImageSlot(QImage *img)
{
    image = img;
    update();
}


