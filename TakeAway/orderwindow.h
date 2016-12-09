#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include "prerequisite.h"
#include "orderdb.h"
#include "orderds.h"

namespace Ui {
class OrderWindow;
}

class OrderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWindow(QSharedPointer<OrderDB> &odb, QSharedPointer<UserDS> &SessionUser, QWidget *parent = 0);
    ~OrderWindow();
signals:
    void showbw();
private slots:
    void on_pbBack_clicked();
    void on_pbAccept_clicked();
    void showOrderw();
private:
    Ui::OrderWindow *ui;
    QSharedPointer<UserDS> SessionUser;
    QSharedPointer<OrderDB> odb;
    OrderDS data;
};

#endif // ORDERWINDOW_H
