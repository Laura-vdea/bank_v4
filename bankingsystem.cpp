#include "bankingsystem.h"
#include <iostream>

void BankingSystem::createAccount(const string& name, const string& accountNumber, double initialBalance) {
    if (accounts.find(name) != accounts.end()) {
        cout << "Account with this name already exists!" << endl;
        return;
    }
    accounts[name] = make_shared<Account>(accountNumber, initialBalance);
    cout << "Account created for " << name << " with account number " << accountNumber << "." << endl;
}

void BankingSystem::deposit(const string& name, double amount) {
    auto account = getAccount(name);
    if (account) {
        account->deposit(amount);
        cout << "Deposited " << amount << " to " << name << "'s account." << endl;
    }
}

void BankingSystem::withdraw(const string& name, double amount) {
    auto account = getAccount(name);
    if (account) {
        if (account->withdraw(amount)) {
            cout << "Withdrew " << amount << " from " << name << "'s account." << endl;
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }
}

void BankingSystem::showBalance(const string& name) const {
    auto account = getAccount(name);
    if (account) {
        cout << name << "'s account balance: " << account->getBalance() << endl;
    }
}

shared_ptr<Account> BankingSystem::getAccount(const string& name) const {
    auto it = accounts.find(name);
    if (it != accounts.end()) {
        return it->second;
    } else {
        cout << "Account not found for " << name << "!" << endl;
        return nullptr;
    }
}

