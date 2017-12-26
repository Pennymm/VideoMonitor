#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QLinearGradient>
#include <QBrush>
#include <QImage>

class VideoWindow : public QObject
{
    Q_OBJECT
public:
    explicit VideoWindow(QObject *parent = nullptr);


protected:
    virtual void paintEvent(QPaintEvent *event);



signals:

public slots:

private:
//    QPainter *painter;
    QImage *image;

};

#endif // VIDEOWINDOW_H
