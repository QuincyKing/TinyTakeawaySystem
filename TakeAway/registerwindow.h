#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include "prerequisite.h"
#include "reguserdb.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QSharedPointer<RegUserDB>&, QSharedPointer<UserDS>&, QWidget *parent = 0);
    ~RegisterWindow();

signals:
    void showlw();
    void showbw();

private slots:
    void on_pbRegister_clicked();
    void on_clbLogin_clicked();
    void on_checkBox_toggled(bool checked);
    void on_seller_clicked();
    void on_buyer_clicked();

private:
    Ui::RegisterWindow *ui;
    QSharedPointer<RegUserDB> rudb;
    QSharedPointer<UserDS> SessionUser;
    bool flag;
};

#endif // REGISTERWINDOW_H
