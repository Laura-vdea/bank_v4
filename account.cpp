#include "account.h"

// Account 클래스 생성자의 파라미터 타입을 QString으로 수정
Account::Account(const QString& accNum, const QString& nm, int bal)
    : accountNumber(accNum), name(nm), balance(bal) {}

QString Account::getAccountNumber() const {
    return accountNumber;  // 리턴 타입을 QString으로 수정
}

void Account::addAccount(const QString& accountNumber, unique_ptr<Account> account) {
    accountMap[accountNumber] = std::move(account);
}

int Account::getBalance() const {
    return balance;
}

Account* Account::getAccount(const QString& accountNumber) const {
    auto it = accountMap.find(accountNumber);
    return (it != accountMap.end()) ? it->second.get() : nullptr;
}

void Account::showAllAccounts() const {
    for (const auto& pair : accountMap) {
        pair.second->showAccInfo();
    }
}

bool Account::deposit(double money) {
    if (money <= 0) return false; // 입금 금액이 0 이하이면 실패
    balance += money; // 잔액에 입금 금액 추가
    transactions.push_back({"Deposit", money});
    return true;
}


bool Account::withdraw(double money) {
    if (money > balance || money <= 0) return false; // 출금 금액이 잔액보다 많거나 0 이하이면 실패
    balance -= money; // 잔액에서 출금 금액 차감
    transactions.push_back({"Withdraw", money});
    return true;
}

QString Account::getName() const {
    return name;
}

void Account::showAccInfo() const { // 계좌 정보를 출력하는 함수
    //qDebug().nospace() << "계좌번호:" << accountNumber << ", 고객명:" << name << ", 잔액:" << balance;
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
    QMessageBox::information(nullptr, "Account Show", msg + content);
}

void Account::save(QTextStream& outFile) const { // 계좌 정보를 파일에 저장하는 함수
    // outFile << accountNumber << ' ' << name << ' ' << balance << '\n';
    for (const auto& pair : accountMap) {
        pair.second->save(outFile);
    }
}

void Account::load(QTextStream& inFile) { // 파일에서 계좌 정보를 읽어오는 함수
    // inFile >> accountNumber >> name >> balance;
    accountMap.clear();
    while (!inFile.atEnd()) {  // 스트림의 끝을 확인하는 방법 수정
        QChar accountType;
        inFile >> accountType;

        if (accountType == 'N') {  // 'N'이 보통 예금 계좌임을 나타냄
            QString accountNumber, name;
            int balance;
            inFile >> accountNumber >> name >> balance;
            accountMap[accountNumber] = std::make_unique<Account>(accountNumber, name, balance);
        }
    }
}
vector<pair<QString, double>> Account::getTransactions() const {
    return transactions;  // 거래 내역 반환
}
