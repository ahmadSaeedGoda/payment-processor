#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Account.h"
#include <vector>

using namespace std;

class Transaction
{
public:
    Transaction(Account *fromAccount, Account *toAccount, double amount);

    void execute();
    string getId();
    Account *getSender();
    Account *getReceiver();
    double getAmount();
    time_t getTimestamp();

private:
    string transactionId;
    Account *fromAccount;
    Account *toAccount;
    double amount;
    time_t timestamp;
};

#endif // TRANSACTION_H
