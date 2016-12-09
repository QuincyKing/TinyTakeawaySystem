#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QSharedPointer<RegUserDB>& rudb, QSharedPointer<UserDS>& SessionUser, QWidget *parent) :
    rudb(rudb), SessionUser(SessionUser), QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbLogin_clicked()
{
    QString username = ui->leUsername->text();
    QString password = ui->lePassword->text();
    UserDS user(username, password);

    qDebug() << user.getUsername();
    if(user.isValidUsernamePattern() && user.isValidPasswordPattern()) {
        if(rudb->authUser(user))
        {
            ui->leUsername->setText("");
            ui->lePassword->setText("");

            SessionUser->update(user);
            qDebug() << SessionUser->getUsername();
            hide();
            if(user.getUserFlag())
                emit showbw();
            else
                emit showsw();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("username or pwd is wrong");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Username should be 5~10 characters.\nPassword should be 6~10 characters.");
        msgBox.exec();
    }
}

void MainWindow::on_clbRegister_clicked()
{
    hide();
    emit showrw();
}
