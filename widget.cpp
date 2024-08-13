#include "widget.h"
#include "./ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget), bankingSystem(new BankingSystem)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->button_dcancel, &QPushButton::clicked, this, &Widget::cancel);
    connect(ui->button_wcancel, &QPushButton::clicked, this, &Widget::cancel);
    connect(ui->button_mcancel, &QPushButton::clicked, this, &Widget::cancel);
    connect(ui->button_scancel, &QPushButton::clicked, this, &Widget::cancel);
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_loginButton_clicked()
{
    QString name = ui->lineEdit_namelogin->text();
    if (name == "test") {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void Widget::on_pushButton_makeAcc_clicked() {
    ui->stackedWidget->setCurrentIndex(5);
}

void Widget::on_pushButton_deposit_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::on_pushButton_withdraw_clicked() {
    ui->stackedWidget->setCurrentIndex(3);
}

void Widget::on_pushButton_allAcc_clicked() {
    bankingSystem->showAllAccounts();
}
void Widget::on_pushButton_spAcc_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Widget::on_button_mconfirm_clicked()
{
    QString name = ui->lineEdit_mn->text();
    QString accountNumber = ui->lineEdit_ma->text();
    double initialBalance = ui->spinBox_mb->text().toInt();

    bankingSystem->createAccount(name.toStdString(), accountNumber.toStdString(), initialBalance);
}

void Widget::on_button_dconfirm_clicked()
{
    QString accountNumber = ui->accountDepositEdit->text();  // 계좌 번호 입력란
    int amount = ui->depositAmmount->text().toInt();  // 입금 금액 입력란

    bankingSystem->deposit(accountNumber, amount);
}

void Widget::on_button_wconfirm_clicked()
{
    QString accountNumber = ui->accountWithdrawEdit->text();  // 계좌 번호 입력란
    int amount = ui->withdrawAmmount->text().toInt();  // 출금 금액 입력란

    bankingSystem->withdraw(accountNumber, amount);
}

void Widget::on_button_show_clicked()
{
    QString accountNumber = ui->lineEdit_ma->text();  // 계좌번호 필드를 가져옴
    bankingSystem->showBalance(accountNumber);
}

void Widget::cancel() {
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_exit_clicked()
{
    this->close();
}


