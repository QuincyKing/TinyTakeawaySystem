#ifndef BUYERWINDOW_H
#define BUYERWINDOW_H

#include "prerequisite.h"
#include "userds.h"
#include "sellerdb.h"

namespace Ui {
class BuyerWindow;
}

class BuyerWindow : public QWidget
{
    Q_OBJECT

public:
    BuyerWindow(QSharedPointer<SellerDB> &, QSharedPointer<UserDS> &, QWidget *parent = 0);
    ~BuyerWindow();

signals:
    void showmw(int);
    void showow();
    void showlw();

private slots:
    void on_lwshop_itemClicked(QListWidgetItem *item);
    void on_pblogout_clicked();
    void on_pborder_clicked();
    void showBuyerw();

private:
    Ui::BuyerWindow *ui;
    QSharedPointer<UserDS> SessionUser;
    QSharedPointer<SellerDB> sdb;
    QMap<int, QString> shops;
};

#endif // BUYERWINDOW_H
