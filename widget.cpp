#include "widget.h"
#include "./ui_widget.h"

#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget), bankingSystem(new BankingSystem)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_loginButton_clicked()   //로그인 버튼 클릭시
{
    QString name = ui->lineEdit_namelogin->text();
    if(name == "test"){
         ui->stackedWidget->setCurrentIndex(1);
    }
    //ui->stackedWidget->setCurrentIndex(1);
}
void Widget::on_pushButton_makeAcc_clicked()  //make a account 버튼 클릭 시
{
    ui->stackedWidget->setCurrentIndex(5);

}
void Widget::on_pushButton_deposit_clicked()  // deposit 버튼 클릭시
{
    ui->stackedWidget->setCurrentIndex(2);
}
void Widget::on_pushButton_withdraw_clicked()  // withdraw 버튼 클릭시
{
    ui->stackedWidget->setCurrentIndex(3);
}
void Widget::on_pushButton_allAcc_clicked()  // all accounts 버튼 클릭시
{
    ui->stackedWidget->setCurrentIndex(4);
}


void Widget::on_button_mconfirm_clicked()   // make a account confirm
{
    QString name = ui->lineEdit_mn->text();
    QString accountNumber = ui->lineEdit_ma->text();
    double initialBalance = ui->spinBox_mb->value();

    bankingSystem->createAccount(name.toStdString(), accountNumber.toStdString(), initialBalance);
    QMessageBox::information(this, "Account Created", "Account created successfully.");
}


void Widget::on_button_dconfirm_clicked()   // deposit confirm
{
    QString name = ui->lineEdit_namelogin->text();
    double amount = ui->spinBox_deposit->value();

    bankingSystem->deposit(name.toStdString(), amount);
    QMessageBox::information(this, "Deposit Successful", "Amount deposited successfully.");
}


void Widget::on_button_wconfirm_clicked()  // withdraw confirm
{
    QString name = ui->lineEdit_namelogin->text();
    double amount = ui->spinBox_withdraw->value();

    bankingSystem->deposit(name.toStdString(), amount);
    QMessageBox::information(this, "Deposit Successful", "Amount deposited successfully.");
}

void Widget::on_button_show_clicked()
{
    QString name = ui->lineEdit_namelogin->text();

    bankingSystem->showBalance(name.toStdString());
}

