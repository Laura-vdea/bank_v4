#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account {
public:
    Account(string accountNumber, double balance);

    string getAccountNumber() const;
    double getBalance() const;

    void deposit(double amount);
    bool withdraw(double amount);

private:
    string accountNumber;
    double balance;
};

#endif // ACCOUNT_H
