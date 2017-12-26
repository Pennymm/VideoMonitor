#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("视频监控");
    createMenu();
    createTool();
    createScrollArea();
    this->statusBar()->show();

    time = new QTimer;

    connect(time, SIGNAL(timeout()), this, SLOT(updateTime()));
    time->start(1000);

    connect(addBtn, SIGNAL(clicked()), this, SLOT(moveAddSlot()));

}

MainWindow::~MainWindow()
{

}
//菜单栏
void MainWindow::createMenu()
{
    menubar = menuBar();
    file = menubar->addMenu("文件");
    help = menubar->addMenu("帮助");
    create = file->addAction(QIcon(":/New.png"), "新建视频");
    quit = file->addAction(QIcon(":/Exit.png"), "退出视频");
    about = help->addAction(QIcon(":/About.png"), "关于");

    create->setShortcut(QKeySequence("Ctrl+C"));
    quit->setShortcut(QKeySequence("Ctrl+Q"));
    about->setShortcut(QKeySequence("Ctrl+A"));

    create->setStatusTip("create");
    quit->setStatusTip("quit");
    about->setStatusTip("about");
}
//工具栏
void MainWindow::createTool()
{
    toolBar = addToolBar(QString("toolBar"));
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //
    open = toolBar->addAction(QIcon(":/New.png"), "新建");
    exit = toolBar->addAction(QIcon(":/Exit.png"), "退出");

    open->setToolTip("new");
    open->setToolTip("exit");

    open->setShortcut(QKeySequence("Ctrl+O"));
    exit->setShortcut(QKeySequence("Ctrl+E"));

    open->setStatusTip("新建");
    exit->setStatusTip("退出");

    widget = new QWidget;
    label = new QLabel("");

    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //toolBar is a pointer to an existing toolbar
    toolBar->addWidget(widget);
    toolBar->addWidget(label);
}
//滚动条
void MainWindow::createScrollArea()
{

    widgetOnScroll = new QWidget;
    widgetOnScroll->resize(2000,2000);
    scrollArea = new QScrollArea;
    scrollArea->setWidget(widgetOnScroll);
    this->setCentralWidget(scrollArea);

    addBtn = new QPushButton("+", widgetOnScroll);
    addBtn->setFont(QFont("黑体", 500, 100));
    addBtn->setGeometry(0, 0, 400, 300);
    addBtn->show();

}
//显示时间
void MainWindow::updateTime()
{
    QString str = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    label->setText(str);
    time->start(1000);
}
//点击加号“+”按钮
void MainWindow::moveAddSlot()
{
    VideoWindowDisplay *video = new VideoWindowDisplay(widgetOnScroll);

    //    video->setGeometry((QRect(addBtn->geometry())));
    vect.append(video);
    vect.last()->setGeometry((QRect(addBtn->geometry())));
    vect.last()->show();
    video->indexOfVideo = vect.count()-1;
    connect(video, SIGNAL(exitBtnSignal(VideoWindowDisplay*)), \
            this, SLOT(closeVideoSlot(VideoWindowDisplay*)));
    connect(video, SIGNAL(videoBackSignal(VideoWindowDisplay*)), \
            this, SLOT(backVideoSlot(VideoWindowDisplay*)));

    qDebug()<<"number of window while add : "<<vect.count();

    int row = vect.count()%3;
    int col = vect.count()/3;
    //    addBtn->move();
    addBtn->setGeometry(row*400, col*300, 400, 300);
    addBtn->show();
}
//关闭视频窗口
void MainWindow::closeVideoSlot(VideoWindowDisplay *video)
{
    //获取下标
    int index = vect.indexOf(video);
    //移动按钮 到最火一个video的位置
//    addBtn->setGeometry(vect.last()->geometry());

    //for依次移动
    for(int i = vect.count()-1; i > index; --i)
    {
//        --vect.at(i)->indexOfVideo;
//        vect.at(i)->setGeometry(vect.at(i-1)->geometry());
         vect.at(i)->setGeometry(((i-1)%3)*400, ((i-1)/3)*300, 400, 300);
        vect.at(i)->show();
    }
    addBtn->setGeometry(((vect.count()-1)%3)*400, ((vect.count()-1)/3)*300, 400, 300);
    vect.at(index)->close();
    vect.removeOne(video);

    //释放index

//    //vect.remove(index, 1);
//    vect.at(index)->close();

//    delete vect.at(index);
//    for(int i = index; i < vect.count(); ++i)
//    {
//        qDebug()<<"i+1: " <<i+1;
//        --vect.at(i)->indexOfVideo;
//        vect.at(i)->setGeometry(((i)%3)*400, ((i)/3)*300, 400, 300);
//        //vect.at(i)->setGeometry(vect.at(i-1)->geometry());
//        vect.at(i)->show();
//    }

//    //    vect.at(index)->deleteLater();
//    qDebug()<<"number of window: "<<vect.count();

//    addBtn->setGeometry((vect.count()%3)*400, (vect.count()/3)*300, 400, 300);
//    addBtn->show();


}

void MainWindow::backVideoSlot(VideoWindowDisplay *video)
{
//    auto posit = vect.
    vect.insert(video->indexOfVideo-1, 1, video);
    for(int i = video->indexOfVideo; i < vect.count(); ++i)
    {
        vect.at(i)->setGeometry(((i)%3)*400, ((i)/3)*300, 400, 300);
        vect.at(i)->show();
    }
    addBtn->setGeometry((vect.count()%3)*400, (vect.count()/3)*300, 400, 300);
    addBtn->show();
}




