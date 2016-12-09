#ifndef SELLERORDERWINDOW_H
#define SELLERORDERWINDOW_H

#include "prerequisite.h"
#include "sorderdb.h"
#include "userds.h"

namespace Ui {
class SellerOrderWindow;
}

class SellerOrderWindow : public QWidget
{
    Q_OBJECT

public:
   explicit SellerOrderWindow(QSharedPointer<SOrderDB> &, QSharedPointer<UserDS> &, QWidget *parent = 0);
    ~SellerOrderWindow();
signals:
    void showlw();
    void showsmw();

private slots:
    void on_pbmenu_clicked();
    void on_pblogout_clicked();
    void showSellerOrderw();
private:
    Ui::SellerOrderWindow *ui;
    QSharedPointer<UserDS> SessionUser;
    QSharedPointer<SOrderDB> sodb;
};

#endif // SELLERORDERWINDOW_H
