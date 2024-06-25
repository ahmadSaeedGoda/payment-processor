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

string Account::getName()
{
    return name;
}

void Account::withdraw(double amount)
{
    if (amount <= balance)
    {
        balance -= amount;
    }
}

void Account::deposit(double amount)
{
    balance += amount;
}
