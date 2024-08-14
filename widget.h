#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <memory>
#include "bankingsystem.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    // 생성자: Widget 클래스를 초기화하며, 부모 위젯을 설정
    Widget(QWidget *parent = nullptr);

    // 소멸자: Widget 객체가 파괴될 때 호출되며, 동적으로 할당된 리소스를 해제
    ~Widget();

    // cancel 함수: 다양한 취소 버튼을 클릭했을 때 호출되는 함수로, 메인 메뉴로 돌아가는 역할
    void cancel();

private slots:
    // 로그인 버튼 클릭 시 호출되는 슬롯 함수
    void on_loginButton_clicked();

    // 회원가입 버튼 클릭 시 호출되는 슬롯 함수
    void on_SignUpButton_clicked();

    // 로그아웃 버튼 클릭 시 호출되는 슬롯 함수
    void on_LogoutButton_clicked();

    // 계좌 생성 버튼 클릭 시 호출되는 슬롯 함수
    void on_pushButton_makeAcc_clicked();

    // 입금 버튼 클릭 시 호출되는 슬롯 함수
    void on_pushButton_deposit_clicked();

    // 출금 버튼 클릭 시 호출되는 슬롯 함수
    void on_pushButton_withdraw_clicked();

    // 계좌 생성 확인 버튼 클릭 시 호출되는 슬롯 함수
    void on_button_mconfirm_clicked();

    // 입금 확인 버튼 클릭 시 호출되는 슬롯 함수
    void on_button_dconfirm_clicked();

    // 출금 확인 버튼 클릭 시 호출되는 슬롯 함수
    void on_button_wconfirm_clicked();

    // 모든 계좌 보기 버튼 클릭 시 호출되는 슬롯 함수
    void on_pushButton_allAcc_clicked();

    // 특정 계좌 보기 버튼 클릭 시 호출되는 슬롯 함수
    void on_button_show_clicked();

    // 종료 버튼 클릭 시 호출되는 슬롯 함수
    void on_pushButton_exit_clicked();

    // 특정 계좌 보기 메뉴 버튼 클릭 시 호출되는 슬롯 함수
    void on_pushButton_spAcc_clicked();

private:
    // Ui::Widget 포인터: UI 요소들을 관리하는 객체로, 이 클래스에서 생성된 UI 폼을 관리
    Ui::Widget *ui;

    // bankingSystem: BankingSystem 클래스의 인스턴스를 관리하는 shared_ptr로, 메모리 관리와 함께 은행 시스템의 기능을 제공
    std::shared_ptr<BankingSystem> bankingSystem;

private slots:
    // 계좌 데이터 불러오기 버튼 클릭 시 호출되는 슬롯 함수
    void on_ImportButton_clicked();
};

#endif // WIDGET_H
