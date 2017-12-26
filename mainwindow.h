#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QWidget>
#include <QWheelEvent>
#include <QScrollBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QDateTime>
#include <QTimer>
#include <QPushButton>
#include <QVector>
#include <QScrollArea>
#include <QFont>
#include "videowindowdisplay.h"




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createMenu();
    void createTool();
    void createScrollArea();

public slots:
    void updateTime();
    void moveAddSlot();
    void closeVideoSlot(VideoWindowDisplay * video);
    void backVideoSlot(VideoWindowDisplay *video);

private:
    QScrollBar *vertivalScrollBar;
    QScrollBar *horirontalScrollBar;
    QWidget newPaper;
    QMenu *file;
    QMenu *help;
    QAction *create;
    QAction *quit;
    QAction *about;
    QAction *open;
    QAction *exit;

    QMenuBar *menubar;
    QToolBar *toolBar;

    QWidget *widget;
    QTimer *time;
    QLabel *label;

    QScrollArea *scrollArea;
    QWidget *widgetOnScroll;

    QPushButton *addBtn;
    QVector<VideoWindowDisplay *> vect;
};

#endif // MAINWINDOW_H
