#include "sellerorderwindow.h"
#include "ui_sellerorderwindow.h"

SellerOrderWindow::SellerOrderWindow(QSharedPointer<SOrderDB> &sodb, QSharedPointer<UserDS> &SessionUser, QWidget *parent) :
    QWidget(parent),SessionUser(SessionUser), sodb(sodb),
    ui(new Ui::SellerOrderWindow)
{
    ui->setupUi(this);
}

SellerOrderWindow::~SellerOrderWindow()
{
    delete ui;
}

void SellerOrderWindow::on_pbmenu_clicked()
{
    hide();
    emit showsmw();
}

void SellerOrderWindow::on_pblogout_clicked()
{
    SessionUser->clear();

    hide();
    emit showlw();
}

void SellerOrderWindow::showSellerOrderw()
{
    ui->lname->setText(SessionUser->getUsername());
    ui->lworder->setAutoScroll(true);
    ui->lworder->setFrameShape(QFrame::NoFrame);
    ui->lworder->clear();

    std::map<std::vector<std::string>, std::string> order = sodb->getOrder(SessionUser->getUid());
    std::map<std::vector<std::string>, std::string>::iterator cursor = order.begin();
    for(; cursor != order.end(); cursor++)
    {
        std::vector<std::string> vec = cursor->first;
        QListWidgetItem *item = new QListWidgetItem(ui->lworder);
        item->setText(QString::fromStdString(cursor->second));
        item->setSizeHint(QSize(item->sizeHint().height(), 30));
        ui->lworder->addItem(item);
        std::vector<std::string>::iterator curvec = vec.begin();
        for(;curvec != vec.end(); curvec++)
        {
            QListWidgetItem *item = new QListWidgetItem(ui->lworder);
            item->setText(QString::fromStdString(*curvec));
            item->setSizeHint(QSize(item->sizeHint().height(), 30));
            ui->lworder->addItem(item);
        }
    }
    show();
}
