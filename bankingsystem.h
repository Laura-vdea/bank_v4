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
#include <QDateTime>

using namespace std;

// BankingSystem 클래스는 은행 시스템을 관리하는 클래스이며, 계좌 생성, 입금, 출금, 잔액 조회, 전체 계좌 조회 등의 기능을 제공한다.
class BankingSystem {
    vector<Account *> acc;   // 계좌 정보를 저장하는 벡터 (현재 사용되지 않음)
    QString currentUser;     // 현재 로그인된 사용자 이름
    QString accountNumber;   // 현재 처리 중인 계좌번호
    int money;               // 현재 처리 중인 금액

public:
    // 기본 생성자: BankingSystem 객체를 생성하며, 초기 데이터 로드를 수행
    BankingSystem() { loadData(); }

    // 새로운 계좌를 생성하는 함수
    // 사용자 이름, 계좌번호, 초기 잔액을 입력 받아 계좌를 생성
    bool createAccount(const QString &name, const QString &accountNumber, int initialBalance);

    // 입금 함수: 지정된 계좌번호에 금액을 입금
    bool deposit(const QString& accountNumber, int amount);

    // 출금 함수: 지정된 계좌번호에서 금액을 출금
    bool withdraw(const QString& accountNumber, int amount);

    // 잔액 조회 함수: 지정된 계좌번호의 잔액을 조회하여 표시
    void showBalance(const QString& accountNumber);

    // 전체 계좌 조회 함수: 시스템에 등록된 모든 계좌의 정보를 표시
    void showAllAccounts();

    // 특정 계좌의 잔액을 반환하는 함수
    int getBalanceForAccount(const QString& accountNumber) const;

    // 특정 계좌 객체를 반환하는 함수
    shared_ptr<Account> getAccount(const QString &accountNumber) const;

private:
    // accountMap: 계좌 정보를 저장하는 맵으로, 키는 계좌번호, 값은 계좌 객체
    map<QString, shared_ptr<Account>> accountMap;

    // 계좌가 존재하는지 확인하는 함수
    bool hasAccount(const QString &accountNumber) const;

    // 계좌 정보를 파일에 저장하는 함수
    void saveData();

    // 계좌 정보를 파일에서 불러오는 함수
    void loadData();

    // 계좌 잔액을 업데이트하는 함수 (입금 또는 출금)
    bool updateAccountBalance(const QString &accountNumber, int amount, bool isDeposit);

    // 입출금 실패 시 로그를 기록하는 함수
    void logErrTransaction(const QString &accountNumber, int amount, bool isDeposit, bool success);

    // 입출금 성공 시 로그를 기록하는 함수
    void logTransaction(const QString &accountNumber, int amount, bool isDeposit, bool success);
};

// 전역으로 사용할 BankingSystem 객체 선언
extern BankingSystem bankingSystem;

#endif // BANKINGSYSTEM_H
