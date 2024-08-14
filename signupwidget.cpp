#include "signupwidget.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

// SignUpWidget 클래스의 생성자
SignUpWidget::SignUpWidget(QWidget *parent)
    : QDialog(parent), // 부모 위젯을 설정하며, QDialog를 상속받아 다이얼로그 형태의 위젯을 생성
    lineEditUsername(new QLineEdit(this)), // 사용자 이름을 입력받는 QLineEdit 위젯 생성
    signUpButton(new QPushButton("Sign Up", this)) // "Sign Up" 텍스트가 표시된 QPushButton 위젯 생성
{
    // QVBoxLayout을 사용하여 위젯을 수직으로 배치할 레이아웃 생성
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 사용자 이름 입력 폼을 위한 QFormLayout 생성
    QFormLayout *formLayout = new QFormLayout;
    // "Username:" 레이블과 lineEditUsername을 한 행에 추가
    formLayout->addRow("Username:", lineEditUsername);
    // formLayout을 layout에 추가하여 QVBoxLayout의 첫 번째 요소로 배치
    layout->addLayout(formLayout);

    // Sign Up 버튼을 layout에 추가하여 QVBoxLayout의 마지막 요소로 배치
    layout->addWidget(signUpButton);

    // Sign Up 버튼이 클릭될 때 onSignUpClicked 슬롯이 호출되도록 연결
    connect(signUpButton, &QPushButton::clicked, this, &SignUpWidget::onSignUpClicked);
}

// SignUpWidget 클래스의 소멸자
SignUpWidget::~SignUpWidget() {
    // 생성자에서 동적으로 할당한 메모리는 Qt의 부모-자식 관계에 의해 자동으로 해제되므로 별도의 처리가 필요 없음
}

// 회원가입 버튼이 클릭되었을 때 호출되는 슬롯 함수
void SignUpWidget::onSignUpClicked() {
    // 사용자 입력으로부터 공백을 제거한 후, username 변수에 저장
    QString username = lineEditUsername->text().trimmed();

    // username이 비어 있는지 확인하여, 비어 있다면 경고 메시지를 표시하고 함수 종료
    if (username.isEmpty()) {
        QMessageBox::warning(this, "Sign Up Error", "Username cannot be empty.");
        return;
    }

    // username이 이미 존재하는지 확인하여, 존재한다면 경고 메시지를 표시하고 함수 종료
    if (isMemberExists(username)) {
        QMessageBox::warning(this, "Sign Up Error", "This username is already taken.");
        return;
    }

    // username이 비어있지 않고 존재하지 않으면, saveMember 함수를 호출하여 사용자 이름을 저장
    saveMember(username);
    // 성공적으로 회원가입이 완료되었다는 메시지를 표시
    QMessageBox::information(this, "Sign Up", "You have signed up successfully.");
    // 다이얼로그를 닫고 성공적으로 종료
    this->accept();
}

// 새로운 멤버를 파일에 저장하는 함수
void SignUpWidget::saveMember(const QString &username) {
    // "member.txt" 파일을 append 모드로 열기
    QFile file("member.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        // 파일에 텍스트를 쓰기 위한 QTextStream 생성
        QTextStream out(&file);
        // 파일에 username을 한 줄로 기록
        out << username << "\n";
        // 파일을 닫아 변경 사항을 저장
        file.close();
    }
}

// 입력된 사용자 이름이 이미 존재하는지 확인하는 함수
bool SignUpWidget::isMemberExists(const QString &username) {
    // "member.txt" 파일을 읽기 모드로 열기
    QFile file("member.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 파일로부터 텍스트를 읽기 위한 QTextStream 생성
        QTextStream in(&file);
        // 파일의 끝까지 한 줄씩 읽으며 username과 비교
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line == username) {
                // 동일한 username이 발견되면 true 반환
                return true;
            }
        }
        // 파일을 닫기
        file.close();
    }
    // 동일한 username이 없으면 false 반환
    return false;
}
