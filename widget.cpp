#include "widget.h"
#include "./ui_widget.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget), bankingSystem(new BankingSystem)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->button_dcancel, &QPushButton::clicked, this, &Widget::cancel);  // deposit 취소
    connect(ui->button_wcancel, &QPushButton::clicked, this, &Widget::cancel);  // withdraw 취소
    connect(ui->button_mcancel, &QPushButton::clicked, this, &Widget::cancel);  // make a account 취소
    connect(ui->button_scancel, &QPushButton::clicked, this, &Widget::cancel);  // specific account 취소
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_loginButton_clicked()               //로그인
{
    QString name = ui->lineEdit_namelogin->text();
    if (name == "test") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else {
        QMessageBox::warning(this, "Login Failed", "Invalid username.");
    }
    /*QString name = ui->lineEdit_namelogin->text();
    QStringList validUsers;

    // users.txt 파일 열기
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open users file.");
        return;
    }

    // 파일을 한 줄씩 읽어서 validUsers에 추가
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            validUsers.append(line);
        }
    }
    file.close();

    // 입력된 이름이 validUsers에 있는지 확인
    if (validUsers.contains(name)) {
        ui->stackedWidget->setCurrentIndex(1);  // 로그인 성공
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username.");
    }*/
}

//6가지 menu버튼 클릭 시 화면 이동
void Widget::on_pushButton_makeAcc_clicked() {    // make a account 계좌 생성으로 이동
    ui->stackedWidget->setCurrentIndex(5);
}
void Widget::on_pushButton_deposit_clicked() {    // deposit 입금으로 이동
    ui->stackedWidget->setCurrentIndex(2);
}
void Widget::on_pushButton_withdraw_clicked() {   // withdraw 출금으로 이동
    ui->stackedWidget->setCurrentIndex(3);
}
void Widget::on_pushButton_allAcc_clicked() {     // all accounts 모든 계좌 출력으로 이동
    bankingSystem->showAllAccounts();
}
void Widget::on_pushButton_spAcc_clicked()        // transaction history 거래 내역으로 이동
{
    ui->stackedWidget->setCurrentIndex(4);
}

// 계좌 생성 확인 버튼 클릭
void Widget::on_button_mconfirm_clicked()
{
    QString name = ui->lineEdit_mn->text();
    QString accountNumber = ui->lineEdit_ma->text();
    double initialBalance = ui->spinBox_mb->text().toInt();

    bankingSystem->createAccount(name.toStdString(), accountNumber.toStdString(), initialBalance);
}
// 입금 확인 버튼 클릭
void Widget::on_button_dconfirm_clicked()
{
    QString accountNumber = ui->accountDepositEdit->text();  // 계좌 번호 입력란
    int amount = ui->depositAmmount->text().toInt();  // 입금 금액 입력란

    bankingSystem->deposit(accountNumber, amount);
}
// 출금 확인 버튼 클릭
void Widget::on_button_wconfirm_clicked()
{
    QString accountNumber = ui->accountWithdrawEdit->text();  // 계좌 번호 입력란
    int amount = ui->withdrawAmmount->text().toInt();  // 출금 금액 입력란

    bankingSystem->withdraw(accountNumber, amount);
}
// 세부 내역 보기 버튼 클릭
void Widget::on_button_show_clicked()
{
    //QString accountNumber = ui->lineEdit_ma->text();  // 계좌번호 필드를 가져옴
    //bankingSystem->showBalance(accountNumber);
    QString accountNumber = ui->lineEdit_spec->text();
    auto account = bankingSystem->getAccount(accountNumber);

    if (account) {
        QString transactionHistory;
        auto transactions = account->getTransactions();

        for (const auto &transaction : transactions) {
            transactionHistory += transaction.first + ": " + QString::number(transaction.second) + "\n";
        }
        ui->textEdit_show->setPlainText(transactionHistory);

        //QMessageBox::information(nullptr, "Transaction History", transactionHistory);
    } else {
        QMessageBox::warning(nullptr, "Account Not Found", "계좌를 찾을 수 없습니다.");
    }
}

// 취소 버튼 클릭 시 menu로 이동
void Widget::cancel() {
    ui->stackedWidget->setCurrentIndex(1);
}

//exit 버튼 클릭 시 종료
void Widget::on_pushButton_exit_clicked()
{
    this->close();
}
