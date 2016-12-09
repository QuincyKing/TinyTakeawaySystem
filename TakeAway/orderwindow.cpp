#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "orderds.h"

OrderWindow::OrderWindow(QSharedPointer<OrderDB> &odb, QSharedPointer<UserDS> &SessionUser, QWidget *parent) :
    QWidget(parent), odb(odb), SessionUser(SessionUser),
    ui(new Ui::OrderWindow)
{
    ui->setupUi(this);
}

void OrderWindow::on_pbAccept_clicked()
{
    odb->updateOrderState(data.oid);
    hide();
    emit showbw();
}

OrderWindow::~OrderWindow()
{
    delete ui;
}

void OrderWindow::on_pbBack_clicked()
{
    hide();
    emit showbw();
}

void OrderWindow::showOrderw()
{
    ui->lwOrder->setResizeMode(QListView::Adjust);
    ui->lwOrder->setAutoScroll(true);
    ui->lwOrder->setFrameShape(QListWidget::NoFrame);
    ui->lwOrder->setAutoScroll(true);
    ui->lwOrder->clear();

    data = odb->searchRecentOrder(SessionUser);
    QString time;
    if(!data.order.empty())
    {
       time = odb->getTime(data.oid);
    }

    QRegularExpression re;
    re.setPattern("[T]{1,}");
    time.replace(re, "\t");

    QMap<QString, int>::iterator cursor = data.order.begin();
    for(; cursor != data.order.end(); cursor++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->lwOrder);
        item->setText(cursor.key() + "\t\t\t*  " + QString::number(cursor.value()) );
        item->setSizeHint(QSize(item->sizeHint().height(), 50));
        ui->lwOrder->addItem(item);
    }
    QListWidgetItem *timeitem = new QListWidgetItem(ui->lwOrder);
    timeitem->setText("Estimated arrival time\t\t\t" + time);
    timeitem->setSizeHint(QSize(timeitem->sizeHint().height(), 50));
    ui->lwOrder->addItem(timeitem);

    show();
    if(data.order.empty())
    {
        QMessageBox msgBox;
        msgBox.setText("None Order!");
        msgBox.exec();
    }
}
