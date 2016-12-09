#include "buyerwindow.h"
#include "ui_buyerwindow.h"

BuyerWindow::BuyerWindow(QSharedPointer<SellerDB> &sdb, QSharedPointer<UserDS> &SessionUser, QWidget *parent) :
    QWidget(parent), SessionUser(SessionUser), sdb(sdb),
    ui(new Ui::BuyerWindow)
{
    ui->setupUi(this);
}

void BuyerWindow::on_lwshop_itemClicked(QListWidgetItem *item)
{
    int Id = item->data(Qt::UserRole).toInt();

    hide();
    emit showmw(Id);
}

void BuyerWindow::on_pblogout_clicked()
{
    SessionUser->clear();

    hide();
    emit showlw();
}

void BuyerWindow::on_pborder_clicked()
{
    hide();
    emit showow();
}

void BuyerWindow::showBuyerw()
{
    ui->lwshop->setResizeMode(QListView::Adjust);
    ui->lwshop->setAutoScroll(true);
    ui->lwshop->setFrameShape(QListWidget::NoFrame);
    ui->lname->setText( SessionUser->getUsername() );
    ui->lwshop->clear();

    shops = sdb->searchAllShop();
    if(shops.empty())
    {
        return;
    }

    QMap<int, QString>::iterator cursor = shops.begin();
    for(; cursor != shops.end(); cursor++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->lwshop);
        item->setData(Qt::UserRole, cursor.key());
        item->setText(cursor.value());
        item->setSizeHint(QSize(item->sizeHint().height(), 50));
        ui->lwshop->addItem(item);
    }
    show();
}

BuyerWindow::~BuyerWindow()
{
    delete ui;
}
