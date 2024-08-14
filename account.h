#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <map>
#include <memory>

using namespace std;

// Account 클래스는 은행 계좌를 관리하는 클래스
class Account {
protected:
    QString accountNumber; // 계좌 번호를 저장하는 변수
    QString name; // 고객 이름을 저장하는 변수
    int balance; // 계좌 잔액을 저장하는 변수
    map<QString, unique_ptr<Account>> accountMap; // 계좌 정보를 저장하는 맵 (계좌 번호를 키로 사용)
    vector<pair<QString, double>> transactions; // 거래 내역을 저장하는 벡터

public:
    // 생성자: 계좌 번호, 고객 이름, 초기 잔액을 받아 Account 객체를 초기화합니다.
    Account(const QString& accNum, const QString& nm, int bal);

    // 가상 소멸자: Account 객체가 파괴될 때 호출한다.
    // 기본적으로는 아무 작업도 하지 않으며, 파생 클래스에서 재정의될 수 있다.
    virtual ~Account() {}

    // 고객 이름을 반환하는 함수
    QString getName() const;

    // 계좌 번호를 반환하는 함수
    QString getAccountNumber() const;

    // 현재 잔액을 반환하는 함수
    int getBalance() const;

    // 새로운 계좌를 추가하는 함수
    // 계좌 번호와 해당 계좌 객체를 받아 accountMap에 추가
    void addAccount(const QString& accountNumber, unique_ptr<Account> account);

    // 계좌 번호로 계좌를 검색하여 반환하는 함수
    // 계좌가 존재하지 않으면 nullptr를 반환
    Account* getAccount(const QString& accountNumber) const;

    // 모든 계좌 정보를 출력하는 함수
    void showAllAccounts() const;

    // 유저 계좌 정보를 파일에 저장하는 함수
    void saveAccounts(QTextStream& outFile) const;

    // 파일에서 유저 계좌 정보를 불러오는 함수
    void loadAccounts(QTextStream& inFile);

    // 입금 함수: 지정된 금액을 잔액에 추가
    // 금액이 0 이하인 경우 false를 반환하며, 정상적으로 입금이 되면 true를 반환
    virtual bool deposit(double money);

    // 출금 함수: 지정된 금액을 잔액에서 차감
    // 출금 금액이 잔액보다 많거나 0 이하인 경우 false를 반환하며, 정상적으로 출금이 되면 true를 반환
    virtual bool withdraw(double money);

    // 계좌 정보를 출력하는 함수
    virtual void showAccInfo() const;

    // 계좌 정보를 파일에 저장하는 함수
    virtual void save(QTextStream& outFile) const;

    // 파일에서 계좌 정보를 읽어오는 함수
    virtual void load(QTextStream& inFile);

    // 거래 내역을 반환하는 함수
    vector<pair<QString, double>> getTransactions() const;
};

#endif // ACCOUNT_H
