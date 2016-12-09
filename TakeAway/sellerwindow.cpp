#include "sellerwindow.h"
#include "ui_sellerwindow.h"

SellerWindow::SellerWindow(QSharedPointer<SMenuDB> &smdb, QSharedPointer<UserDS> &SessionUser, QWidget *parent) :
    QWidget(parent),SessionUser(SessionUser), smdb(smdb),
    ui(new Ui::SellerWindow)
{
    ui->setupUi(this);
}

SellerWindow::~SellerWindow()
{
    delete ui;
}

void SellerWindow::on_pbupgrade_clicked()
{
    QMap<QString, int> menu;
    for(int row= 0; row  < countrow; row++)
    {
        QModelIndex index1 = model->index(row, 0, QModelIndex());
        QString name = model->data(index1).toString();

        QModelIndex index2 = model->index(row, 1, QModelIndex());
        int price = model->data(index2).toInt();

        QModelIndex index3 = model->index(row, 2, QModelIndex());
        int id = model->data(index3).toInt();

        QString str = name + ":" + QString::number(id);
        if(str != ":0" && price != 0)
         menu.insert(str, price);
    }

    smdb->upgradeMenu(menu, SessionUser->getUid());
    showSellerw();
}

void SellerWindow::on_pbback_clicked()
{
    hide();
    emit showsow();
}

void SellerWindow::showSellerw()
{
    ui->tvmenu->setShowGrid(false);
    ui->tvmenu->verticalHeader()->setVisible(false);
    ui->tvmenu->setFrameShape(QFrame::NoFrame);
    ui->tvmenu->setAutoScroll(true);
    ui->lname->setText(SessionUser->getUsername());

    QMap<QString, int> menu = smdb->getMenu(SessionUser->getUid());
    countrow = menu.size()+1;
    model=new QStandardItemModel(countrow, 2, this);
    ui->tvmenu->setModel(model);
    ui->tvmenu->setColumnWidth(0,343);
    ui->tvmenu->setColumnWidth(1,50);

    for(int i = 0; i < countrow; i++)
    {
        ui->tvmenu->setRowHeight(i,50);
    }

    BarDelegate *delegate=new BarDelegate(this);
    ui->tvmenu->setItemDelegateForColumn( 1, delegate );

   QMap<QString, int>::iterator cursor = menu.begin();
    for( int r=0 ; cursor != menu.end(); ++r, cursor++)
    {
      QString name = cursor.key().split(":").at(1);
      int id = cursor.key().split(":").at(0).toInt();
      QStandardItem *item = new QStandardItem( QString("%1").arg(name) );
      item->setEditable( true );
      model->setItem( r, 0, item );
      model->setItem( r, 1, new QStandardItem( QString::number(cursor.value())) );
      model->setItem(r, 2, new QStandardItem( QString::number( id ) ));
    }
    model->setItem( countrow-1, 1, new QStandardItem( QString::number(0)) );
    ui->tvmenu->setColumnHidden(2, true);
    this->show();
}
