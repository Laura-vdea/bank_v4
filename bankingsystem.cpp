#include "bankingsystem.h"
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

using namespace std;

void BankingSystem::createAccount(const std::string &name, const std::string &accountNumber, double initialBalance) {
    QString qAccountNumber = QString::fromStdString(accountNumber);
    QString qName = QString::fromStdString(name);

    if (hasAccount(qAccountNumber)) {
        QMessageBox::warning(nullptr, "Account Error", "이미 존재하는 계좌번호입니다.");
        return;
    }

    accountMap[qAccountNumber] = std::make_shared<Account>(qAccountNumber, qName, initialBalance);
    saveData();

    QString message = QString("계좌가 성공적으로 생성되었습니다.\n\n계좌번호: %1\n이름: %2\n초기 잔액: %3")
                          .arg(qAccountNumber)
                          .arg(qName)
                          .arg(initialBalance);
    QMessageBox::information(nullptr, "Account Created", message);
}

bool BankingSystem::deposit(const QString& accountNumber, int depositAmount) {
    if (accountNumber.isEmpty() || depositAmount <= 0) {
        QMessageBox::warning(nullptr, "Input Error", "모든 필드를 올바르게 입력하세요.");
        return false;
    }

    if (updateAccountBalance(accountNumber, depositAmount, true)) {
        int currentBalance = getBalanceForAccount(accountNumber);
        QString message = QString("입금이 성공적으로 완료되었습니다.\n\n계좌번호: %1\n입금 금액: %2\n입금 후 잔액: %3")
                              .arg(accountNumber)
                              .arg(depositAmount)
                              .arg(currentBalance);

        QMessageBox::information(nullptr, "Deposit Successful", message);
        return true;
    } else {
        QMessageBox::warning(nullptr, "Deposit Failed", "입금이 실패하였습니다. 계좌 번호를 확인하세요.");
        return false;
    }
}

bool BankingSystem::withdraw(const QString& accountNumber, int withdrawAmount) {
    if (accountNumber.isEmpty() || withdrawAmount <= 0) {
        QMessageBox::warning(nullptr, "Input Error", "모든 필드를 올바르게 입력하세요.");
        return false;
    }

    if (updateAccountBalance(accountNumber, withdrawAmount, false)) {
        int currentBalance = getBalanceForAccount(accountNumber);
        QString message = QString("출금이 성공적으로 완료되었습니다.\n\n계좌번호: %1\n출금 금액: %2\n출금 후 잔액: %3")
                              .arg(accountNumber)
                              .arg(withdrawAmount)
                              .arg(currentBalance);

        QMessageBox::information(nullptr, "Withdraw Successful", message);
        return true;
    } else {
        QMessageBox::warning(nullptr, "Withdraw Failed", "출금이 실패하였습니다. 잔액을 확인하세요.");
        return false;
    }
}

void BankingSystem::showBalance(const QString& accountNumber) {
    QFile file("accountData.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "File Error", "파일을 열 수 없습니다.");
        return;
    }

    QTextStream in(&file);
    int balance = -1;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList accountDetails = line.split(" ");

        if (accountDetails.size() == 3 && accountDetails[0] == accountNumber) {
            balance = accountDetails[2].toInt();
            break;
        }
    }

    file.close();

    if (balance != -1) {
        QString message = QString("계좌번호: %1\n잔액: %2").arg(accountNumber).arg(balance);
        QMessageBox::information(nullptr, "Account Balance", message);
    } else {
        QMessageBox::warning(nullptr, "Account Not Found", "계좌를 찾을 수 없습니다.");
    }
}

void BankingSystem::showAllAccounts() {
    QFile file("accountData.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "File Error", "파일을 열 수 없습니다.");
        return;
    }

    QTextStream in(&file);
    QString content = "전체 계좌 정보:\n\n";

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList accountDetails = line.split(" ");

        if (accountDetails.size() == 3) {
            content += QString("계좌번호: %1\n이름: %2\n잔액: %3\n\n")
                           .arg(accountDetails[0])
                           .arg(accountDetails[1])
                           .arg(accountDetails[2]);
        }
    }

    file.close();
    QMessageBox::information(nullptr, "All Accounts", content);
}

shared_ptr<Account> BankingSystem::getAccount(const QString &accountNumber) const {
    auto it = accountMap.find(accountNumber);
    return (it != accountMap.end()) ? it->second : nullptr;
}

bool BankingSystem::hasAccount(const QString &accountNumber) const {
    return accountMap.find(accountNumber) != accountMap.end();
}

void BankingSystem::saveData() {
    QFile outFile("accountData.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "File Error", "파일을 열 수 없습니다.");
        return;
    }

    QTextStream out(&outFile);
    for (const auto &pair : accountMap) {
        out << pair.second->getAccountNumber() << " "
            << pair.second->getName() << " "
            << pair.second->getBalance() << "\n";
    }

    outFile.close();
}

void BankingSystem::loadData() {
    QFile inFile("accountData.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "File Error", "파일을 열 수 없습니다.");
        return;
    }

    QTextStream in(&inFile);
    accountMap.clear();
    QString accountNumber, name;
    int balance;

    while (!in.atEnd()) {
        in >> accountNumber >> name >> balance;
        accountMap[accountNumber] = std::make_shared<Account>(accountNumber, name, balance);
    }

    inFile.close();
}

bool BankingSystem::updateAccountBalance(const QString &accountNumber, int amount, bool isDeposit)
{
    auto account = getAccount(accountNumber);
    if (!account)
    {
        QMessageBox::warning(nullptr, "Account Error", "계좌를 찾을 수 없습니다.");
        return false;
    }

    if (isDeposit)
    {
        account->deposit(amount);
    }
    else
    {
        if (!account->withdraw(amount))
        {
            QMessageBox::warning(nullptr, "Withdrawal Error", "잔액이 부족합니다.");
            return false;
        }
    }

    saveData();
    return true;
}

int BankingSystem::getBalanceForAccount(const QString &accountNumber) const
{
    auto account = getAccount(accountNumber);
    return account ? account->getBalance() : -1;
}
