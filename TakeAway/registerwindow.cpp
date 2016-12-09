#include "registerwindow.h"
#include "ui_registerwindow.h"

RegisterWindow::RegisterWindow(QSharedPointer<RegUserDB>& rudb, QSharedPointer<UserDS>& SessionUser, QWidget *parent) :
    rudb(rudb), SessionUser(SessionUser), QWidget(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    ui->buyer->setChecked(true);
    ui->lePass->setEchoMode(QLineEdit::Password);
    ui->leRepass->setEchoMode(QLineEdit::Password);
    ui->lSellername->setVisible(false);
    ui->leSellername->setVisible(false);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_pbRegister_clicked()
{
    bool isValid = true;
    UserDS user;
    QString sellername;
    QString username = ui->leName->text();
    QString password = ui->lePass->text();
    QString repassword = ui->leRepass->text();
    QString tele = ui->leTele->text();
    bool userFlag = ui->buyer->isChecked();
    if(!userFlag)
    {
        sellername = ui->leSellername->text();
    }

    if((!user.isValidUsernamePattern(username)) || (!user.isValidPasswordPattern(password)) || (!user.isValidTelePattern(tele)))
    {
        isValid = false;
    }

    if(repassword != password)
    {
        isValid = false;
    }

    if(isValid)
    {
        if(userFlag)
            user.update(username, password, userFlag, tele, 0);
        else
            user.update(username, password, userFlag, tele, 0, sellername);
        if(rudb->addUser(user))
        {
            ui->leName->setText("");
            ui->lePass->setText("");
            ui->leRepass->setText("");
            ui->leTele->setText("");
            ui->buyer->setChecked(true);
            ui->leSellername->setText("");

            SessionUser->update(user);
            hide();
            emit showbw();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("[Error] " + user.userDataTypeStr(user.getUserType()));
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("wrong format\n");
        msgBox.exec();
    }
}

void RegisterWindow::on_clbLogin_clicked()
{
    hide();
    emit showlw();
}

void RegisterWindow::on_checkBox_toggled(bool checked)
{
    if(checked)
    {
        ui->lePass->setEchoMode(QLineEdit::Normal);
        ui->leRepass->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->lePass->setEchoMode(QLineEdit::Password);
        ui->leRepass->setEchoMode(QLineEdit::Password);
    }
}

void RegisterWindow::on_buyer_clicked()
{
    ui->lSellername->setVisible(false);
    ui->leSellername->setVisible(false);
}

void RegisterWindow::on_seller_clicked()
{
    ui->lSellername->setVisible(true);
    ui->leSellername->setVisible(true);
}
