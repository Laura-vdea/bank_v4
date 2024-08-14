#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

// SignUpWidget 클래스는 사용자 회원가입을 위한 다이얼로그 창을 관리하는 클래스이며, 사용자가 입력한 사용자 이름을 검증하고, 이미 존재하는 회원인지 확인하며, 새로운 회원을 등록하는 기능을 제공한다.
class SignUpWidget : public QDialog {
    Q_OBJECT

public:
    // 생성자: SignUpWidget 클래스를 초기화하며, 부모 위젯을 설정할 수 있다.
    explicit SignUpWidget(QWidget *parent = nullptr);

    // 소멸자: SignUpWidget 객체가 파괴될 때 호출되며, 동적으로 할당된 리소스를 해제
    ~SignUpWidget();

private slots:
    // onSignUpClicked 함수는 'Sign Up' 버튼이 클릭되었을 때 호출되는 슬롯 함수
    // 이 함수는 입력된 사용자 이름을 검증하고, 회원으로 등록하는 로직을 처리
    void onSignUpClicked();

private:
    // lineEditUsername: 사용자 이름을 입력받는 QLineEdit 위젯
    QLineEdit *lineEditUsername;

    // signUpButton: 'Sign Up' 버튼을 나타내는 QPushButton 위젯
    QPushButton *signUpButton;

    // saveMember 함수는 입력된 사용자 이름을 파일에 저장하여 새로운 회원을 등록
    void saveMember(const QString &username);

    // isMemberExists 함수는 입력된 사용자 이름이 이미 회원 목록에 존재하는지 확인하는 함수
    // 회원이 존재하면 true를 반환하고, 존재하지 않으면 false를 반환
    bool isMemberExists(const QString &username);
};

#endif // SIGNUPWIDGET_H
