#include "../include/Account.h"

using namespace std;

Account::Account(const string &id, const string &name, double initialBalance)
    : id(id), name(name), balance(initialBalance) {}

double Account::getBalance() const
{
    return balance;
}

string Account::getId()
{
    return id;
}

void Account::withdraw(double amount)
{
    if (amount <= balance)
    {
        balance -= amount;
    }
    // You might want to handle the case where amount > balance, e.g., throw an exception or log an error
}

void Account::deposit(double amount)
{
    balance += amount;
}
