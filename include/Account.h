#include <string>
#ifndef ACCOUNT_H
#define ACCOUNT_H

using namespace std;

class Account
{
public:
    Account(const string &id, const string &name, double initialBalance);
    void withdraw(double amount);
    void deposit(double amount);
    string getId();
    string getName();
    double getBalance() const;

private:
    string id;
    string name;
    double balance;
};

#endif // ACCOUNT_H
