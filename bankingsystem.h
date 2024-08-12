#ifndef BANKINGSYSTEM_H
#define BANKINGSYSTEM_H

#include "account.h"
#include <map>
#include <memory>
#include <string>
using namespace std;

class BankingSystem {
public:
    void createAccount(const string& name, const string& accountNumber, double initialBalance);
    void deposit(const string& name, double amount);
    void withdraw(const string& name, double amount);
    void showBalance(const string& name) const;

private:
    shared_ptr<Account> getAccount(const string& name) const;

    map<string, shared_ptr<Account>> accounts;
};

#endif // BANKINGSYSTEM_H

