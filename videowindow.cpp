#include "videowindow.h"

VideoWindow::VideoWindow(QObject *parent) : QObject(parent)
{



}

void VideoWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    image = new QImage(400, 30,QImage::Format_ARGB32);
    QPainter painter(image);

    QLinearGradient line(0, 0, 400, 300);
    line.setColorAt(0, Qt::white);
    line.setColorAt(1, Qt::green);
    painter.setBrush(line);
    painter.drawRect(0, 0, 400, 300);
    painter.drawImage((400-128)/2, (300-128)/2, QImage(":/bg.png"));



}
