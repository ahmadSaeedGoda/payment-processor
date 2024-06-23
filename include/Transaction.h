#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
using namespace std;

class Transaction
{
public:
    string transactionId;
    string fromAccountId;
    string toAccountId;
    double amount;
    time_t timestamp;

    Transaction(const string &transId, const string &fromId, const string &toId, double amt);
};

#endif // TRANSACTION_H
