#include "account.h"

// Account 클래스 생성자
// 계좌번호, 고객명, 잔액을 초기화하는 생성자
Account::Account(const QString& accNum, const QString& nm, int bal)
    : accountNumber(accNum), name(nm), balance(bal) {}

// 계좌번호를 반환하는 함수
QString Account::getAccountNumber() const {
    return accountNumber;  // 계좌번호를 QString 타입으로 반환
}

// 계좌를 계좌번호와 함께 accountMap에 추가하는 함수
void Account::addAccount(const QString& accountNumber, unique_ptr<Account> account) {
    accountMap[accountNumber] = std::move(account);  // unique_ptr로 관리되는 계좌 객체를 이동하여 저장
}

// 잔액을 반환하는 함수
int Account::getBalance() const {
    return balance;  // 현재 계좌 잔액을 반환
}

// 계좌번호를 이용해 accountMap에서 계좌를 찾는 함수
Account* Account::getAccount(const QString& accountNumber) const {
    auto it = accountMap.find(accountNumber);  // 계좌번호로 검색
    return (it != accountMap.end()) ? it->second.get() : nullptr;  // 계좌가 존재하면 반환, 없으면 nullptr 반환
}

// 모든 계좌 정보를 출력하는 함수
void Account::showAllAccounts() const {
    for (const auto& pair : accountMap) {  // 모든 계좌에 대해
        pair.second->showAccInfo();  // 계좌 정보를 출력
    }
}

// 입금 처리 함수
bool Account::deposit(double money) {
    if (money <= 0) return false;  // 입금 금액이 0 이하일 경우 실패
    balance += money;  // 잔액에 입금 금액을 더함
    transactions.push_back({"Deposit", money});  // 거래 내역에 입금 기록 추가
    return true;  // 입금 성공
}

// 출금 처리 함수
bool Account::withdraw(double money) {
    if (money > balance || money <= 0) return false;  // 출금 금액이 잔액보다 많거나 0 이하일 경우 실패
    balance -= money;  // 잔액에서 출금 금액을 차감
    transactions.push_back({"Withdraw", money});  // 거래 내역에 출금 기록 추가
    return true;  // 출금 성공
}

// 계좌명의를 반환하는 함수
QString Account::getName() const {
    return name;  // 계좌명의 반환
}

// 계좌 정보를 출력하는 함수
void Account::showAccInfo() const {
    // 메모장 파일(accountData.txt)에서 데이터를 불러오는 로직
    QFile file("accountData.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 파일을 열지 못했을 때 경고 메시지 표시
        QMessageBox::warning(nullptr, "File Error", "파일을 열 수 없습니다.");
        return;
    }

    QTextStream in(&file);
    QString msg = "개설되어있는 계좌 확인입니다 : \n\n";
    QString content;

    // 파일의 내용을 한 줄씩 읽어서 content에 저장
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList accountDetails = line.split(" ");

        if(accountDetails.size() == 3) {
            QString accountNumber = accountDetails[0];
            QString name = accountDetails[1];
            int balance = accountDetails[2].toInt();

            // 계좌 정보를 content에 추가
            content += QString("계좌번호 : %1\n이름 : %2\n잔액 : %3\n\n")
                           .arg(accountNumber)
                           .arg(name)
                           .arg(balance);
        }
    }

    file.close();
    // 계좌 정보를 메시지 박스로 표시
    QMessageBox::information(nullptr, "Account Show", msg + content);
}

// 계좌 정보를 파일에 저장하는 함수
void Account::save(QTextStream& outFile) const {
    // 모든 계좌 정보를 파일에 저장
    for (const auto& pair : accountMap) {
        pair.second->save(outFile);  // 각 계좌 정보를 저장
    }
}

// 파일에서 계좌 정보를 읽어오는 함수
void Account::load(QTextStream& inFile) {
    accountMap.clear();  // 기존 계좌 정보를 초기화
    while (!inFile.atEnd()) {  // 스트림의 끝을 확인하며 읽기
        QChar accountType;
        inFile >> accountType;

        if (accountType == 'N') {  // 'N'이 보통 예금 계좌임을 나타냄
            QString accountNumber, name;
            int balance;
            inFile >> accountNumber >> name >> balance;  // 계좌 정보 읽기
            accountMap[accountNumber] = std::make_unique<Account>(accountNumber, name, balance);  // 계좌 추가
        }
    }
}

// 거래 내역을 반환하는 함수
vector<pair<QString, double>> Account::getTransactions() const {
    return transactions;  // 거래 내역 리스트를 반환
}
