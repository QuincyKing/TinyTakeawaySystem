#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "sellerdb.h"
#include "BarDelegate.h"

MenuWindow::MenuWindow(QSharedPointer<MenuDB> &menudb, QSharedPointer<UserDS> &SessionUser, QWidget *parent) :
    QWidget(parent),SessionUser(SessionUser), menudb(menudb),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_pbSubmit_clicked()
{
    int totalprice = 0;
    int newmoney;
    for(int row= 0; row  < countrow; row++)
    {
        QModelIndex index1 = model->index(row,0,QModelIndex());
        QString string = model->data(index1).toString();
        int price = string.split(":").at(1).toInt();

        QModelIndex index2 = model->index(row,1,QModelIndex());
        int count = model->data(index2).toInt();

        int id = (menu.find(string)).value();

        if(count > 0)
        {
            order.insert(id, count);
            totalprice += price * count;
        }
    }

    newmoney = (SessionUser->getMoney() - totalprice);
    if( newmoney >= 0)
    {
        SessionUser->setMoney(newmoney);
        menudb->submitOrder(order, SessionUser, shop, totalprice);
        hide();
        emit showow();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Insufficient balance!");
        msgBox.exec();
    }
}

void MenuWindow::on_pbBack_clicked()
{
    hide();
    emit showbw();
}

void MenuWindow::showMenuw(int shop)
{
    ui->tvMenu->setShowGrid(false);
    ui->tvMenu->horizontalHeader()->setVisible(false);
    ui->tvMenu->verticalHeader()->setVisible(false);
    ui->tvMenu->setFrameShape(QFrame::NoFrame);
    ui->tvMenu->setAutoScroll(true);

    this->shop = shop;
    QSharedPointer<SellerDB> sellerdb = QSharedPointer<SellerDB>(new SellerDB);
    QString shopname = sellerdb->searchShopName(shop);
    ui->lShopname->setText(shopname);
    menudb->setShop(shop);
    menu = menudb->searchShopMenu();

    countrow = menu.size();
    model=new QStandardItemModel(countrow,2,this);
    ui->tvMenu->setModel(model);
    ui->tvMenu->setColumnWidth(0,343);
    ui->tvMenu->setColumnWidth(1,50);

    for(int i = 0; i < countrow; i++)
    {
        ui->tvMenu->setRowHeight(i,50);
    }

    BarDelegate *delegate=new BarDelegate(this);
    ui->tvMenu->setItemDelegateForColumn( 1, delegate );

   QMap<QString, int>::iterator cursor = menu.begin();
    for( int r=0 ; r<countrow; ++r, cursor++)
    {
      QStandardItem *item = new QStandardItem( cursor.key()  );
      item->setEditable( false );
      model->setItem( r, 0, item );
      model->setItem( r, 1, new QStandardItem( QString::number(0)) );
    }

    this->show();
}
