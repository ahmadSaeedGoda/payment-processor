#ifndef PAYMENTPROCESSOR_H
#define PAYMENTPROCESSOR_H

#include "Account.h"
#include "Transaction.h"
#include "FileLogger.h"

#include <mutex>
#include <vector>

using namespace std;

class PaymentProcessor
{
public:
    PaymentProcessor(FileLogger &logger);

    static const string ACCOUNT_PREFIX;
    static const double MIN_AMOUNT;
    void createAccount(const string &ownerName, double initialBalance);
    bool processTransaction(const string &fromAccountId, const string &toAccountId, double amount);
    double getAccountBalance(const string &accountId);

private:
    vector<Account *> accounts;
    mutex accountsMutex;
    FileLogger &logger;

    string generateAccountId();
    Account *findAccountById(const std::string &accountId);
};

#endif // PAYMENTPROCESSOR_H
