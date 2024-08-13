#ifndef BANKINGSYSTEM_H
#define BANKINGSYSTEM_H

#include "account.h"
#include <map>
#include <memory>
#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

using namespace std;

class BankingSystem {
    vector<Account *> acc;
    QString currentUser; // 현재 사용자
    QString accountNumber;
    int money;

public:
    void createAccount(const std::string &name, const std::string &accountNumber, double initialBalance);
    bool deposit(const QString& accountNumber, int amount);     // 입금
    bool withdraw(const QString& accountNumber, int amount);    // 출금
    void showBalance(const QString& accountNumber);             // 잔액 조회
    void showAllAccounts();                                     // 전체 계좌 조회
    int getBalanceForAccount(const QString& accountNumber) const; // 잔액 조회
    shared_ptr<Account> getAccount(const QString &accountNumber) const;

private:
    map<QString, shared_ptr<Account>> accountMap;               // Use QString as the key
    bool hasAccount(const QString &accountNumber) const;
    void saveData();
    void loadData();
    bool updateAccountBalance(const QString &accountNumber, int amount, bool isDeposit);

    //shared_ptr<Account> getAccount(const QString &accountNumber) const;

};

extern BankingSystem bankingSystem;  // 전역으로 사용할 BankingSystem 객체 선언

#endif // BANKINGSYSTEM_H
