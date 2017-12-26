#ifndef VIDEOWINDOWDISPLAY_H
#define VIDEOWINDOWDISPLAY_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QLinearGradient>
#include <QBrush>
#include <QImage>
#include <QPushButton>
#include <QLabel>
#include <QBuffer>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QTcpSocket>
#include <QFile>
#include <QDateTime>
#include <QImageWriter>
#include <QKeyEvent>
//#include <qkey>
#include "playdialog.h"
#include "mythread.h"
#include "screenshot.h"
//#include <QApplication>
//#include <QDesktopWidget>






class VideoWindowDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWindowDisplay(QWidget *parent = nullptr);
    void drawBackgroundImage();
    int indexOfVideo;

protected:
    virtual void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    //    void startMonitor();

signals:
    void exitBtnSignal(VideoWindowDisplay *index);
    void videoBackSignal(VideoWindowDisplay *video);
    //    void screenShotSignal();

public slots:
    void playBtnClickedSlot();
    void exitBtnClickedSlot();
    void receiveImageSlot(QImage *img);
    void shotBtnClickedSlot();
    void capBtnClickedSlot();
    void stopBtnClickedSlot();
    void enlargeBtnClickedSlot();
    void largeBtnClickedSlot();


private:
    QImage *image;
    QPushButton *playBtn;
    QPushButton *pauseBtn;
    QPushButton *screenShotBtn;
    QPushButton *screenCapBtn;
    QPushButton *stopRecordBtn;
    QPushButton *enlargeBtn;
    QPushButton *exitBtn;

    QWidget *playW;
    QWidget *pauseW;

    QLabel *address;
    QLabel *videoInfo;

    QStackedLayout *stack;
    QStackedLayout *recordLayout;
    QVBoxLayout *vbox;

    QWidget *w;

    //    QDialogButtonBox *playDialog;
    playDialog  *playdlg;
    QString ip;
    QString port;
    MyThread *th;
    QFile *screenFile;
    QRect rectOfVideo;

};

#endif // VIDEOWINDOWDISPLAY_H
