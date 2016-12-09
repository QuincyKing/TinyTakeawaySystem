#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "prerequisite.h"
#include "userds.h"
#include "bardelegate.h"
#include "menudb.h"

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWindow( QSharedPointer<MenuDB> &mendb, QSharedPointer<UserDS> &SessionUser, QWidget *parent = 0);
    ~MenuWindow();
signals:
    void showbw();
    void showow();
private slots:
    void on_pbSubmit_clicked();
    void showMenuw(int shop);
    void on_pbBack_clicked();
private:
    Ui::MenuWindow *ui;
    QSharedPointer<UserDS> SessionUser;
    QStandardItemModel *model;
    QMap<int, int> order;
    QSharedPointer<MenuDB> menudb;
    QMap<QString, int> menu;
    int shop;
    int countrow;
};

#endif // MENUWINDOW_H
