#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <map>
#include <memory>

using namespace std;

class Account {
protected:
    QString accountNumber; // 계좌 번호
    QString name; // 고객 이름
    int balance; // 잔액
    map<QString, unique_ptr<Account>> accountMap;  // 계좌 정보를 담는 맵
    //vector<pair<string, double>> transactions; // 기록 저장용 예시
public:
    Account(const QString& accNum, const QString& nm, int bal);
    virtual ~Account() {}

    QString getName() const; // 고객 이름을 반환하는 함수
    QString getAccountNumber() const; // 계좌 번호를 반환하는 함수
    int getBalance() const; // 잔액을 반환하는 함수

    void addAccount(const QString& accountNumber, unique_ptr<Account> account);
    Account* getAccount(const QString& accountNumber) const;
    void showAllAccounts() const;               // 유저의 모든 계좌 정보를 출력
    void saveAccounts(QTextStream& outFile) const; // 유저 계좌 정보를 파일에 저장
    void loadAccounts(QTextStream& inFile);        // 파일에서 유저 계좌 정보를 불러오기

    virtual bool deposit(double money); // 입금 함수
    virtual bool withdraw(double money); // 출금 함수
    virtual void showAccInfo() const; // 계좌 정보를 출력하는 함수
    virtual void save(QTextStream& outFile) const; // 계좌 정보를 파일에 저장하는 함수
    virtual void load(QTextStream& inFile); // 파일에서 계좌 정보를 읽어오는 함수
    //void printTransactions() const;
};

#endif // ACCOUNT_H
