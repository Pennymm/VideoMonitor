#ifndef SCREENSHOT_H
#define SCREENSHOT_H

//#include <QWidget>
#include <QDialog>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>
#include "mythread.h"

class ScreenShot : public QDialog
{
    Q_OBJECT
public:
    explicit ScreenShot(QDialog *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void receiveImageSlot(QImage *img);

private:
//    MyThread *largeTh;
    QImage *image;
};

#endif // SCREENSHOT_H
