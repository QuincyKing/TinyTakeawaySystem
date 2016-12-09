#ifndef SELLERWINDOW_H
#define SELLERWINDOW_H

#include "prerequisite.h"
#include <map>
#include "userds.h"
#include "smenudb.h"
#include "bardelegate.h"

namespace Ui {
class SellerWindow;
}

class SellerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SellerWindow(QSharedPointer<SMenuDB> &, QSharedPointer<UserDS> &, QWidget *parent = 0);
    ~SellerWindow();
signals:
    void showsow();

private slots:
    void on_pbupgrade_clicked();
    void showSellerw();
    void on_pbback_clicked();

private:
    Ui::SellerWindow *ui;
    QSharedPointer<UserDS> SessionUser;
    QSharedPointer<SMenuDB> smdb;
    QStandardItemModel *model;
    int countrow;
};

#endif // SELLERWINDOW_H
