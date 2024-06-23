#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <mutex>
using namespace std;

class Account
{
public:
    Account(const string &id, const string &name, double initialBalance);
    double getBalance() const;
    void withdraw(double amount);
    void deposit(double amount);
    string getId();

private:
    string id;
    string name;
    double balance;
};

#endif // ACCOUNT_H
