#include "bankingsystem.h"
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

using namespace std;

// 전역 변수로 BankingSystem 객체 생성
BankingSystem bankingSystem;

// 계좌 생성 함수
bool BankingSystem::createAccount(const QString &name, const QString &accountNumber, int initialBalance) {
    // 필드 값들이 유효하지 않을 경우 경고 메시지를 표시하고 함수 종료
    if (name.isEmpty() || accountNumber.isEmpty() || accountNumber == "0" || initialBalance <= 0) {
        QMessageBox::warning(nullptr, "Input Error", "모든 필드를 올바르게 입력하세요.");
        return false;
    }

    // 계좌번호가 이미 존재할 경우 경고 메시지를 표시하고 함수 종료
    if (hasAccount(accountNumber)) {
        QMessageBox::warning(nullptr, "Account Error", "이미 존재하는 계좌번호입니다.");
        return false;
    }

    // 새로운 계좌를 생성하여 accountMap에 추가하고 데이터를 저장
    accountMap[accountNumber] = std::make_shared<Account>(accountNumber, name, initialBalance);
    saveData();

    // 계좌 생성 성공 메시지를 표시
    QString message = QString("계좌가 성공적으로 생성되었습니다.\n\n계좌번호: %1\n이름: %2\n초기 잔액: %3")
                          .arg(accountNumber)
                          .arg(name)
                          .arg(initialBalance);
    QMessageBox::information(nullptr, "Account Created", message);
    return true;
}

// 입금 함수
bool BankingSystem::deposit(const QString& accountNumber, int depositAmount) {
    // 입력된 값들이 유효하지 않을 경우 경고 메시지를 표시하고 함수 종료
    if (accountNumber.isEmpty() || depositAmount <= 0) {
        QMessageBox::warning(nullptr, "Input Error", "모든 필드를 올바르게 입력하세요.");
        return false;
    }

    // 계좌 잔액을 업데이트하고 성공 메시지를 표시
    if (updateAccountBalance(accountNumber, depositAmount, true)) {
        int currentBalance = getBalanceForAccount(accountNumber);
        QString message = QString("입금이 성공적으로 완료되었습니다.\n\n계좌번호: %1\n입금 금액: %2\n입금 후 잔액: %3")
                              .arg(accountNumber)
                              .arg(depositAmount)
                              .arg(currentBalance);

        QMessageBox::information(nullptr, "Deposit Successful", message);
        return true;
    } else {
        // 입금 실패 시 경고 메시지 표시
        QMessageBox::warning(nullptr, "Deposit Failed", "입금이 실패하였습니다. 계좌 번호를 확인하세요.");
        return false;
    }
}

// 출금 함수
bool BankingSystem::withdraw(const QString& accountNumber, int withdrawAmount) {
    // 입력된 값들이 유효하지 않을 경우 경고 메시지를 표시하고 함수 종료
    if (accountNumber.isEmpty() || withdrawAmount <= 0) {
        QMessageBox::warning(nullptr, "Input Error", "모든 필드를 올바르게 입력하세요.");
        return false;
    }

    // 계좌 잔액을 업데이트하고 성공 메시지를 표시
    if (updateAccountBalance(accountNumber, withdrawAmount, false)) {
        int currentBalance = getBalanceForAccount(accountNumber);
        QString message = QString("출금이 성공적으로 완료되었습니다.\n\n계좌번호: %1\n출금 금액: %2\n출금 후 잔액: %3")
                              .arg(accountNumber)
                              .arg(withdrawAmount)
                              .arg(currentBalance);

        QMessageBox::information(nullptr, "Withdraw Successful", message);
        return true;
    } else {
        // 출금 실패 시 경고 메시지 표시
        QMessageBox::warning(nullptr, "Withdraw Failed", "출금이 실패하였습니다. 잔액을 확인하세요.");
        return false;
    }
}

// 계좌 잔액 확인 함수
void BankingSystem::showBalance(const QString& accountNumber) {
    QFile file("accountData.txt");

    // 파일을 열 수 없을 경우 경고 메시지 표시
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "File Error", "파일을 열 수 없습니다.");
        return;
    }

    QTextStream in(&file);
    int balance = -1;

    // 파일에서 계좌번호를 찾아 잔액을 가져옴
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList accountDetails = line.split(" ");

        if (accountDetails.size() == 3 && accountDetails[0] == accountNumber) {
            balance = accountDetails[2].toInt();
            break;
        }
    }

    file.close();

    // 잔액이 유효하면 잔액 정보를 표시, 그렇지 않으면 경고 메시지 표시
    if (balance != -1) {
        QString message = QString("계좌번호: %1\n잔액: %2").arg(accountNumber).arg(balance);
        QMessageBox::information(nullptr, "Account Balance", message);
    } else {
        QMessageBox::warning(nullptr, "Account Not Found", "계좌를 찾을 수 없습니다.");
    }
}

// 모든 계좌 정보 표시 함수
void BankingSystem::showAllAccounts() {
    QFile file("accountData.txt");

    // 파일을 열 수 없을 경우 경고 메시지 표시
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "File Error", "파일을 열 수 없습니다.");
        return;
    }

    QTextStream in(&file);
    QString content = "전체 계좌 정보:\n\n";
    bool validAccountFound = false;

    // 모든 계좌 정보를 읽어와서 표시
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList accountDetails = line.split(" ");

        if (accountDetails.size() == 3) {
            QString accountNumber = accountDetails[0];
            QString name = accountDetails[1];
            int balance = accountDetails[2].toInt();

            if (accountNumber != "0" && !name.isEmpty() && balance >= 0) {
                content += QString("계좌번호: %1\n이름: %2\n잔액: %3\n\n")
                               .arg(accountNumber)
                               .arg(name)
                               .arg(balance);
                validAccountFound = true;
            }
        }
    }

    file.close();

    // 유효한 계좌가 있는 경우 계좌 정보를 표시, 그렇지 않으면 경고 메시지 표시
    if (validAccountFound) {
        QMessageBox::information(nullptr, "All Accounts", content);
    } else {
        QMessageBox::information(nullptr, "All Accounts", "유효한 계좌가 없습니다.");
    }
}

// 계좌 정보를 반환하는 함수 (nullptr를 반환할 수 있음)
shared_ptr<Account> BankingSystem::getAccount(const QString &accountNumber) const {
    auto it = accountMap.find(accountNumber);
    return (it != accountMap.end()) ? it->second : nullptr;
}

// 계좌 존재 여부 확인 함수
bool BankingSystem::hasAccount(const QString &accountNumber) const {
    return accountMap.find(accountNumber) != accountMap.end();
}

// 계좌 데이터를 파일에 저장하는 함수
void BankingSystem::saveData() {
    QFile outFile("accountData.txt");
    // 파일을 열 수 없을 경우 경고 메시지 표시
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "File Error", "파일을 열 수 없습니다.");
        return;
    }

    QTextStream out(&outFile);
    // 모든 계좌 정보를 파일에 기록
    for (const auto &pair : accountMap) {
        QString accountNumber = pair.second->getAccountNumber();
        QString name = pair.second->getName();
        int balance = pair.second->getBalance();

        if (accountNumber != "0" && !name.isEmpty() && balance >= 0) {
            out << accountNumber << " "
                << name << " "
                << balance << "\n";
        }
    }

    outFile.close();
}

// 계좌 데이터를 파일에서 불러오는 함수
void BankingSystem::loadData() {
    QFile inFile("accountData.txt");
    // 파일을 열 수 없을 경우 경고 메시지 표시
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "File Error", "파일을 열 수 없습니다.");
        return;
    }

    QTextStream in(&inFile);
    accountMap.clear(); // 기존 계좌 정보를 초기화
    QString accountNumber, name;
    int balance;

    // 파일에서 계좌 정보를 읽어와 accountMap에 추가
    while (!in.atEnd()) {
        in >> accountNumber >> name >> balance;
        if (accountNumber != "0" && !name.isEmpty() && balance >= 0) {
            accountMap[accountNumber] = std::make_shared<Account>(accountNumber, name, balance);
        }
    }

    inFile.close();
}

// 계좌 잔액을 업데이트하는 함수
bool BankingSystem::updateAccountBalance(const QString &accountNumber, int amount, bool isDeposit) {
    auto account = getAccount(accountNumber);
    if (!account) {
        // 계좌가 없을 경우 경고 메시지 표시하고 실패 로그 기록
        QMessageBox::warning(nullptr, "Account Error", "계좌를 찾을 수 없습니다.");
        logErrTransaction(accountNumber, amount, isDeposit, false); // 실패 로그 기록
        return false;
    }

    // 입금 또는 출금 작업을 수행하고 로그 기록
    if (isDeposit) {
        account->deposit(amount);
        logTransaction(accountNumber, amount, isDeposit, true); // 성공 로그 기록
    } else {
        if (!account->withdraw(amount)) {
            // 출금 실패 시 경고 메시지 표시하고 실패 로그 기록
            QMessageBox::warning(nullptr, "Withdrawal Error", "잔액이 부족합니다.");
            logErrTransaction(accountNumber, amount, isDeposit, false); // 실패 로그 기록
            return false;
        }
    }

    saveData(); // 계좌 정보 저장
    return true;
}

// 입출금 에러 로그 기록 함수
void BankingSystem::logErrTransaction(const QString &accountNumber, int amount, bool isDeposit, bool success) {
    QFile file("bank_error_history.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    QString transactionType = isDeposit ? "Deposit" : "WithDrawal";
    QString status = success ? "Success" : "Failed";
    QString timestamp = QDateTime::currentDateTime().toString("yyy-MM-dd hh:mm:ss");

    // 에러 로그를 파일에 기록
    out << timestamp << " | " << transactionType << " | Account: " << accountNumber << " | Amount: " << amount << " | " << status << "\n";
    file.close();
}

// 입출금 로그 기록 함수
void BankingSystem::logTransaction(const QString &accountNumber, int amount, bool isDeposit, bool success) {
    QFile file("bank_history.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    QString transactionType = isDeposit ? "Deposit" : "WithDrawal";
    QString status = success ? "Success" : "Failed";
    QString timestamp = QDateTime::currentDateTime().toString("yyy-MM-dd hh:mm:ss");

    // 거래 로그를 파일에 기록
    out << timestamp << " | " << transactionType << " | Account: " << accountNumber << " | Amount: " << amount << " | " << status << "\n";
    file.close();
}

// 계좌 잔액을 반환하는 함수
int BankingSystem::getBalanceForAccount(const QString &accountNumber) const {
    auto account = getAccount(accountNumber);
    return account ? account->getBalance() : -1;
}
