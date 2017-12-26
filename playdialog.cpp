#include "playdialog.h"
#include <QDebug>


playDialog::playDialog(QDialog *parent) : QDialog(parent)
{
    ipLabel = new QLabel("ip: ", this);
    portLabel = new QLabel("port: ", this);

    ipLine = new QLineEdit("127.  0.  0.  1", this);
    portLine = new QLineEdit("10001", this);

    btnBox = new QDialogButtonBox(QDialogButtonBox::Ok\
                                  |QDialogButtonBox::Cancel, Qt::Horizontal, this);

    grid = new QGridLayout;
    grid->addWidget(ipLabel, 0, 0, 1, 1);
    grid->addWidget(portLabel, 1, 0, 1, 1);
    grid->addWidget(ipLine, 0, 1, 1, 1);
    grid->addWidget(portLine, 1, 1, 1, 1);
    grid->addWidget(btnBox, 2, 0, 1, 2);//, Qt::AlignCenter|Qt::AlignLeft

    grid->setHorizontalSpacing(20);
    grid->setVerticalSpacing(20);
    grid->setContentsMargins(10, 10, 10, 10);
    this->setLayout(grid);

    isAccept = false;

    connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));//btnBoxAcceptSlot()
    connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));//btnBoxRejectSlot()

}

QString playDialog::getIP()
{
    return ipLine->text();
}

QString playDialog::getPort()
{
    return portLine->text();
}

void playDialog::btnBoxAcceptSlot()
{
    isAccept = true;
    this->close();
    //    QString strIP = ipLine->text();
    //    QString strPort = portLine->text();

    //    qDebug()<<"accept....";

}

void playDialog::btnBoxRejectSlot()
{
    isAccept = false;
    this->close();
    //    return false;

}
