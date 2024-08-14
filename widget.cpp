#include "widget.h"
#include "./ui_widget.h"
#include "signupwidget.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

// Widget 클래스의 생성자
Widget::Widget(QWidget *parent)
    : QWidget(parent), // 부모 위젯을 설정하며 QWidget을 상속
      ui(new Ui::Widget), // UI 객체 초기화
      bankingSystem(new BankingSystem) // BankingSystem 객체 초기화
{
    ui->setupUi(this); // UI 구성 설정

    ui->stackedWidget->setCurrentIndex(0); // 초기 화면을 첫 번째 페이지로 설정
    ui->ImportButton->hide(); // 계좌 데이터 불러오기 버튼 숨기기
    ui->loginButton->show();  // 로그인 버튼 보이기
    ui->SignUpButton->show(); // 회원가입 버튼 보이기
    ui->LogoutButton->hide(); // 로그아웃 버튼 숨기기

    // 다양한 취소 버튼과 cancel() 슬롯 함수 연결
    connect(ui->button_dcancel, &QPushButton::clicked, this, &Widget::cancel);  // 입금 취소
    connect(ui->button_wcancel, &QPushButton::clicked, this, &Widget::cancel);  // 출금 취소
    connect(ui->button_mcancel, &QPushButton::clicked, this, &Widget::cancel);  // 계좌 생성 취소
    connect(ui->button_scancel, &QPushButton::clicked, this, &Widget::cancel);  // 특정 계좌 조회 취소
}

// Widget 클래스의 소멸자
Widget::~Widget() {
    delete ui; // ui 객체 메모리 해제
}

// 로그인 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_loginButton_clicked() {
    QString username = ui->lineEdit_namelogin->text().trimmed(); // 사용자 입력을 받아 공백을 제거한 후 username 변수에 저장

    // UI 요소 초기화
    ui->LogoutButton->hide();  // 로그아웃 버튼 숨기기
    ui->ImportButton->hide();  // 계좌 데이터 불러오기 버튼 숨기기
    ui->loginButton->show();   // 로그인 버튼 보이기
    ui->SignUpButton->hide();  // 회원가입 버튼 숨기기

    // 사용자 이름이 비어있는 경우 경고 메시지를 표시하고 함수 종료
    if (username.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter a username.");
        return;
    }

    // member.txt 파일을 열어 로그인 검증
    QFile file("member.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        bool userExists = false;

        // 파일 내에서 username과 일치하는 사용자가 있는지 확인
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line == username) {
                userExists = true;
                break;
            }
        }

        file.close(); // 파일 닫기

        if (userExists) {
            // 사용자가 존재하면 환영 메시지를 표시하고, 메인 화면으로 전환
            QMessageBox::information(this, "Welcome", QString("%1님 환영합니다.").arg(username));

            ui->stackedWidget->setCurrentIndex(1);  // 메인 화면으로 전환
            ui->LogoutButton->show();   // 로그아웃 버튼 보이기
            ui->ImportButton->show();   // 계좌 데이터 불러오기 버튼 보이기
            ui->loginButton->hide();    // 로그인 버튼 숨기기
            ui->lineEdit_namelogin->hide();  // 로그인 입력 필드 숨기기
            ui->SignUpButton->hide();   // 회원가입 버튼 숨기기

            QString msg = " 님 환영합니다.";
            QString welcomeMsg = username + msg;
            ui->label_username->setText(welcomeMsg);  // Label에 사용자 이름 설정
            ui->label_username->show();  // 사용자 이름 Label 보이기

        } else {
            // 사용자가 존재하지 않으면 경고 메시지 표시
            QMessageBox::warning(this, "Login Failed", "Username not found. Please sign up first.");
            ui->SignUpButton->show();
        }
    } else {
        // 파일을 열 수 없는 경우 경고 메시지 표시
        QMessageBox::warning(this, "File Error", "Unable to open member file.");
    }
}

// 로그아웃 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_LogoutButton_clicked() {
    // 로그아웃 확인 다이얼로그를 띄움
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Logout", "정말로 로그아웃 하시겠습니까?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 사용자가 Yes를 선택한 경우 로그아웃 수행
        QMessageBox::information(this, "Logout", "로그아웃 되었습니다.");
        ui->stackedWidget->setCurrentIndex(0);  // 로그인 화면으로 돌아감

        ui->lineEdit_namelogin->clear();    // 로그인 필드 초기화
        ui->lineEdit_namelogin->show();     // 로그인 입력 필드 다시 보이기

        ui->label_username->hide();         // 사용자 이름 Label 숨기기
        ui->LogoutButton->hide();           // 로그아웃 버튼 숨기기
        ui->SignUpButton->show();           // 회원가입 버튼 다시 보이기
        ui->ImportButton->hide();           // 계좌 데이터 불러오기 버튼 숨기기
        ui->loginButton->show();            // 로그인 버튼 보이기
    }
}

// 회원가입 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_SignUpButton_clicked() {
    SignUpWidget *signUpWidget = new SignUpWidget(this); // SignUpWidget 객체 생성
    signUpWidget->setModal(true); // 모달 다이얼로그로 설정
    signUpWidget->show(); // 다이얼로그 표시
}

// 계좌 데이터 불러오기 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_ImportButton_clicked() {
    // 계좌 데이터 파일을 열어 계좌 정보를 불러옴
    QFile file("accountData.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File Error", "Cannot open the account data file.");
        return;
    }

    QTextStream in(&file);
    QString content;
    bool invalidDataFound = false;

    // 파일에서 데이터를 한 줄씩 읽어 계좌 정보를 파싱
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList accountDetails = line.split(" ");

        // 계좌 정보가 유효한지 확인
        if (accountDetails.size() == 3) {
            QString accountNumber = accountDetails[0];
            QString name = accountDetails[1];
            int balance = accountDetails[2].toInt();

            if (accountNumber != "0" && !name.isEmpty() && balance >= 0) {
                // 유효한 계좌 정보를 content에 추가
                content += QString("계좌번호: %1\n이름: %2\n잔액: %3\n\n")
                               .arg(accountNumber)
                               .arg(name)
                               .arg(balance);
            } else {
                invalidDataFound = true;
            }
        } else {
            invalidDataFound = true;
        }
    }

    file.close(); // 파일 닫기

    // 잘못된 데이터가 발견되었을 때 경고 메시지 표시
    if (invalidDataFound) {
        QMessageBox::warning(this, "Data Error", "잘못된 데이터가 발견되었습니다. 계좌번호가 '0'이거나 필드가 누락된 경우입니다.");
    }

    // 불러온 계좌 정보를 표시
    if (!content.isEmpty()) {
        QMessageBox::information(this, "Imported Data", content);
    } else {
        QMessageBox::information(this, "Imported Data", "유효한 데이터가 없습니다.");
    }
}

// 계좌 생성 메뉴 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_pushButton_makeAcc_clicked() {
    ui->stackedWidget->setCurrentIndex(5); // 계좌 생성 화면으로 전환
}

// 입금 메뉴 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_pushButton_deposit_clicked() {
    ui->stackedWidget->setCurrentIndex(2); // 입금 화면으로 전환
}

// 출금 메뉴 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_pushButton_withdraw_clicked() {
    ui->stackedWidget->setCurrentIndex(3); // 출금 화면으로 전환
}

// 모든 계좌 보기 메뉴 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_pushButton_allAcc_clicked() {
    bankingSystem->showAllAccounts(); // 모든 계좌 정보를 표시
}

// 특정 계좌 보기 메뉴 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_pushButton_spAcc_clicked() {
    ui->stackedWidget->setCurrentIndex(4); // 특정 계좌 보기 화면으로 전환
}

// 계좌 생성 확인 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_button_mconfirm_clicked() {
    QString name = ui->lineEdit_mn->text(); // 이름 입력란에서 값 가져오기
    QString accountNumber = ui->lineEdit_ma->text(); // 계좌번호 입력란에서 값 가져오기
    double initialBalance = ui->spinBox_mb->text().toInt(); // 초기 잔액 입력란에서 값 가져오기

    bankingSystem->createAccount(name, accountNumber, initialBalance); // 계좌 생성

    // 처리 후 입력 폼 클리어
    ui->lineEdit_mn->clear();
    ui->lineEdit_ma->clear();
    ui->spinBox_mb->clear();
}

// 입금 확인 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_button_dconfirm_clicked() {
    QString accountNumber = ui->accountDepositEdit->text();  // 계좌 번호 입력란에서 값 가져오기
    int amount = ui->depositAmmount->text().toInt();  // 입금 금액 입력란에서 값 가져오기

    bankingSystem->deposit(accountNumber, amount); // 입금 처리

    // 처리 후 입력 폼 클리어
    ui->accountDepositEdit->clear();
    ui->depositAmmount->clear();
}

// 출금 확인 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_button_wconfirm_clicked() {
    QString accountNumber = ui->accountWithdrawEdit->text();  // 계좌 번호 입력란에서 값 가져오기
    int amount = ui->withdrawAmmount->text().toInt();  // 출금 금액 입력란에서 값 가져오기

    bankingSystem->withdraw(accountNumber, amount); // 출금 처리

    // 처리 후 입력 폼 클리어
    ui->accountWithdrawEdit->clear();
    ui->withdrawAmmount->clear();
}


// 세부 내역 보기 버튼 클릭 시 호출되는 슬롯 함수
/**
 * 
    메모장에서 데이터를 가져오는 것이 아닌, 현재 프로그램 내에서 관리되고 있는 계좌 정보와 거래 내역을 반영하여 보여준다.
    구체적으로, bankingSystem 객체는 메모리에 저장된 계좌와 거래 내역을 관리하며 사용자가 on_button_show_clicked()
    함수를 호출하면, 해당 계좌의 거래 내역을 메모리에서 가져와 화면에 표시해준다.

    이 때 거래 내역은 account->getTransactions()를 통해 메모리 상에서 직접 불러오고, 메모장 파일과는 관련이 없기 때문에 프로그램 시작시에는 호출이 되지 않음.
    따라서, 이 로직은 프로그램이 실행되는 동안 사용자가 계좌에 대해 수행한 입출금 거래 등 현재 상태를 반영하여 보여주는 것이다.

    즉, 이전에 저장된 파일이나 외부 데이터 소스에 의존하지 않고, [프로그램 내에서의 상태를 실시간으로 반영해 보여주는 기능]
 */
void Widget::on_button_show_clicked() {
    QString accountNumber = ui->lineEdit_spec->text(); // 계좌번호 입력란에서 값 가져오기
    auto account = bankingSystem->getAccount(accountNumber); // 계좌 정보 가져오기

    if (account) {
        QString transactionHistory;
        auto transactions = account->getTransactions(); // 거래 내역 가져오기

        // 거래 내역을 한 줄씩 처리하여 표시
        for (const auto &transaction : transactions) {
            transactionHistory += transaction.first + ": " + QString::number(transaction.second) + "\n";
        }
        ui->textEdit_show->setPlainText(transactionHistory); // 거래 내역을 텍스트 필드에 표시

    } else {
        // 계좌를 찾을 수 없는 경우 경고 메시지 표시
        QMessageBox::warning(nullptr, "Account Not Found", "계좌를 찾을 수 없습니다.");
    }
}

// 취소 버튼 클릭 시 호출되는 슬롯 함수, 메인 메뉴로 돌아감
void Widget::cancel() {
    ui->stackedWidget->setCurrentIndex(1); // 메인 화면으로 전환
}

// 종료 버튼 클릭 시 호출되는 슬롯 함수
void Widget::on_pushButton_exit_clicked() {
    this->close(); // 애플리케이션 종료
}
