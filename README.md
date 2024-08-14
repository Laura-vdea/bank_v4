# VEDA 은행 시스템 프로젝트  
  
###### 주의 : build안에 'accountData.txt'를 미리 `touch` 명령어를 사용하여 만들어야 합니다.  

- 은행 시스템 프로젝트  
이 프로젝트는 사용자가 계정을 생성하고, 돈을 입출금하며, 계좌 잔액을 확인할 수 있는 간단한 은행 시스템입니다. 이 시스템은 C++과 Qt를 사용하여 GUI를 구현했습니다.  
  
## **프로젝트 구조**  
    - main.cpp: 애플리케이션의 시작 지점입니다.  
    - widget.h와 widget.cpp: 로그인, 회원가입, 계좌 관리와 같은 사용자 상호작용을 처리하는 애플리케이션의 메인 창입니다.  
    - signupwidget.h와 signupwidget.cpp: 신규 사용자의 회원가입 프로세스를 처리합니다.  
    - bankingsystem.h와 bankingsystem.cpp: 계좌 생성, 입출금, 잔액 조회 등 은행 시스템의 핵심 로직을 포함합니다.  
    - account.h와 account.cpp: 사용자의 은행 계좌를 나타내는 Account 클래스를 정의합니다.  
  
# [ 클래스 설명 ]  
#### [ Widget 클래스 ]  
- 파일: widget.h, widget.cpp   
Widget 클래스는 애플리케이션의 메인 창을 관리합니다. 로그인, 회원가입, 입출금과 같은 은행 업무를 수행하는 사용자의 상호작용을 처리합니다.  
  
- 주요 함수  
    - on_loginButton_clicked()            : 로그인 기능을 처리합니다.  
    - on_SignUpButton_clicked()           : 회원가입 다이얼로그를 엽니다.  
    - on_LogoutButton_clicked()           : 사용자 로그아웃을 처리합니다.  
    - on_pushButton_makeAcc_clicked()     : 계좌 생성 화면으로 이동합니다.  
    - on_pushButton_deposit_clicked()     : 입금 화면으로 이동합니다.  
    - on_pushButton_withdraw_clicked()    : 출금 화면으로 이동합니다.  
    - on_button_mconfirm_clicked()        : 새 계좌 생성 확인을 처리합니다.  
    - on_button_dconfirm_clicked()        : 입금 거래를 확인합니다.  
    - on_button_wconfirm_clicked()        : 출금 거래를 확인합니다.  
    - on_pushButton_allAcc_clicked()      : 시스템의 모든 계좌를 보여줍니다.  
    - on_button_show_clicked()            : 특정 계좌의 세부 정보를 보여줍니다.  
    - on_pushButton_exit_clicked()        : 애플리케이션을 종료합니다.  
    - on_ImportButton_clicked()           : 계좌 데이터를 가져오는 기능을 처리합니다.  
  
#### [ SignUpWidget 클래스 ]  
- 파일: signupwidget.h, signupwidget.cpp  
SignUpWidget 클래스는 신규 사용자 회원가입 인터페이스를 관리합니다. 입력을 검증하고, 기존 사용자를 확인하며, 새 사용자를 시스템에 저장합니다.  
  
- 주요 함수  
    - onSignUpClicked()                           : 회원가입 버튼이 클릭되었을 때 회원가입 프로세스를 처리합니다.  
    - saveMember(const QString &username)         : 새 회원을 시스템에 저장합니다.  
    - isMemberExists(const QString &username)     : 사용자가 이미 존재하는지 확인합니다.  
  
#### [ BankingSystem 클래스 ]  
- 파일: bankingsystem.h, bankingsystem.cpp  
BankingSystem 클래스는 애플리케이션의 핵심으로, 모든 은행 업무를 관리합니다. 계좌 생성, 입출금, 잔액 조회 등을 처리합니다.  
  
- 주요 함수  
    - createAccount(const QString &name, const QString &accountNumber, int initialBalance)    : 새 계좌를 생성합니다.  
    - deposit(const QString& accountNumber, int amount)                                       : 지정된 금액을 계좌에 입금합니다.  
    - withdraw(const QString& accountNumber, int amount)                                      : 지정된 금액을 계좌에서 출금합니다.  
    - showBalance(const QString& accountNumber)                                               : 특정 계좌의 잔액을 표시합니다.  
    - showAllAccounts()                                                                       : 시스템 내 모든 계좌를 표시합니다.  
    - getBalanceForAccount(const QString& accountNumber) const                                : 특정 계좌의 잔액을 반환합니다.  
    - getAccount(const QString &accountNumber) const                                          : 지정된 계좌 번호와 연관된 계좌 객체를 반환합니다.  
    - saveData()                                                                              : 계좌 데이터를 파일에 저장합니다.  
    - loadData()                                                                              : 파일에서 계좌 데이터를 불러옵니다.  
    - updateAccountBalance(const QString &accountNumber, int amount, bool isDeposit)            : 특정 계좌의 잔액을 업데이트합니다.  
    - logErrTransaction(const QString &accountNumber, int amount, bool isDeposit, bool success) : 실패한 거래를 기록합니다.  
    - logTransaction(const QString &accountNumber, int amount, bool isDeposit, bool success)    : 성공한 거래를 기록합니다.  
  
#### [ Account 클래스 ]
- 파일: account.h, account.cpp  
Account 클래스는 은행 계좌를 나타냅니다. 돈을 입금하고 출금하며, 계좌 정보를 확인하고, 계좌 데이터를 저장/로드하는 기능을 제공합니다.  
  
- 주요 함수  
    - getName() const                                                         : 계좌 소유자의 이름을 반환합니다.  
    - getAccountNumber() const                                                : 계좌 번호를 반환합니다.  
    - getBalance() const                                                      : 현재 계좌 잔액을 반환합니다.  
    - addAccount(const QString& accountNumber, unique_ptr<Account> account)   : 계좌 맵에 새 계좌를 추가합니다.  
    - getAccount(const QString& accountNumber) const                          : 계좌 번호를 기준으로 계좌를 검색합니다.  
    - showAllAccounts() const                                                 : 모든 계좌의 정보를 표시합니다.  
    - saveAccounts(QTextStream& outFile) const                                : 계좌 정보를 파일에 저장합니다.  
    - loadAccounts(QTextStream& inFile)                                       : 파일에서 계좌 정보를 불러옵니다.  
    - deposit(double money)                                                   : 지정된 금액을 계좌에 입금합니다.  
    - withdraw(double money)                                                  : 지정된 금액을 계좌에서 출금합니다.  
    - showAccInfo() const                                                     : 계좌 정보를 표시합니다.  
    - save(QTextStream& outFile) const                                        : 계좌 정보를 파일에 저장합니다.  
    - load(QTextStream& inFile)                                               : 파일에서 계좌 정보를 불러옵니다.  
    - getTransactions() const                                                 : 계좌의 거래 내역을 반환합니다.  
  
#### [ 빌드 및 실행 방법 ]  
> $ git clone https://github.com/your-repository/banking-system.git  
  
#### [ 프로젝트 디렉토리로 이동 ]  
> $ cd banking-system  
  
#### [ Qt Creator에서 프로젝트를 열기 ]  
> Qt Creator에서 `banking-system.pro` 또는 `CMakeLists.txt` 파일을 엽니다.  
  
#### [ 프로젝트를 빌드 ]  
> Qt Creator에서 빌드 버튼을 클릭합니다.  
  
#### [ 프로젝트를 실행 ]  
> Qt Creator에서 실행 버튼을 클릭합니다.  
  
#### [ 프로젝트 코드 상세 설명 ]  
> 주석 참조  
  
#### [ 프로젝트 단계별 과정 설명 ]  
1. 회원가입
- sign up button click &rarr; 생성할 이름 입력
2. 로그인 & 로그아웃
- 이름 입력 &rarr; login button click
- log out button click 
![image](https://github.com/user-attachments/assets/4a34293a-3c5a-4520-85e5-5aed2e98c47f)


3. import account data 
-  import account data button click &rarr; .txt로 저장된 정보 가져옴

4. 계좌 생성
- make a account button click
- 생성할 계좌 번호 입력
- 계좌 사용자 이름 입력
- 초기 금액 입력
- create button click &rarr; 계좌 생성 완료 메시지
- cancel button click &rarr; 계좌 생성 취소
![image](https://github.com/user-attachments/assets/7fdf905a-8b91-496f-a380-1e594bff40de)


5. 입금
- deposit button click
- 생성한 계좌 번호 입력
- 입금할 금액 입력
- deposit button click &rarr; 입금 완료 메시지(+입금 후 금액)
	 	                   &rarr; 알맞은 계좌 번호가 아닐 경우 경고(예외 처리)
- cancel button click  &rarr; 입금 취소
![image](https://github.com/user-attachments/assets/7747f14f-94e1-4e06-a1e3-cf5f6586dbcd)



6. 출금
- withdraw button click
- 생성한 계좌 번호 입력
- 출금할 금액 입력
- withdraw button click &rarr; 출금 완료 메시지(+출금 후 금액)
		                    &rarr; 알맞은 계좌 번호가 아닐 경우 경고(예외 처리)
		                    &rarr; 계좌에 출금할 수 없는 금액일 경우 경고 + 출금 불가능(예외 처리)
- cancel button click &rarr; 출금 취소
![image](https://github.com/user-attachments/assets/0e1942aa-ce3b-4400-837d-f2d75477431e)



7. 모든 계좌 확인 
- all accounts button click
- 로그인 한 이름으로 생성된 계좌 정보 출력
*계좌 정보에는 계좌 번호, 이름, 금액이 포함
![image](https://github.com/user-attachments/assets/66404d52-c49f-42cc-9eb8-ae60deed40a1)


8. 계좌 상세 거래 내역 확인
- transaction history button click
- 생성한 계좌 번호 입력
- show button click &rarr; 해당 계좌번호로 입금, 출금 내역 이루어진 순서대로 모두 출력
- cancle button click &rarr; 출력 없이 취소
![image](https://github.com/user-attachments/assets/1f100f7b-3014-4571-9fa5-f1f6004a69f4)

9. 종료
- exit button click

  
#### License  
This project is licensed under the MIT License. See the `LICENSE` file for more details.  



