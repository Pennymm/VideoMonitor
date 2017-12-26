#ifndef PLAYDIALOG_H
#define PLAYDIALOG_H

//#include <QWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>

class playDialog : public QDialog
{
    Q_OBJECT
public:
    explicit playDialog(QDialog *parent = nullptr);
    QString getIP();
    QString getPort();

    bool isAccept;



signals:

public slots:
    void btnBoxAcceptSlot();
    void btnBoxRejectSlot();

private:
    QDialogButtonBox *btnBox;
    QLabel *ipLabel;
    QLabel *portLabel;
    QLineEdit *ipLine;
    QLineEdit *portLine;


    QGridLayout *grid;
};

#endif // PLAYDIALOG_H
