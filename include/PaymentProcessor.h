#ifndef PAYMENTPROCESSOR_H
#define PAYMENTPROCESSOR_H
#include <vector>
#include <memory>
#include <stdexcept>
#include <mutex>

#include "Account.h"
#include "Transaction.h"
#include "FileLogger.h"

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
    vector<unique_ptr<Account>> getAccounts();
    vector<unique_ptr<Transaction>> getTxs();
    Account &findAccountById(const string &accountId);

private:
    vector<unique_ptr<Account>> accounts;
    vector<unique_ptr<Transaction>> txs;
    mutex txsMutex;
    mutex accountsMutex;
    FileLogger &logger;

    string generateAccountId();
};

#endif // PAYMENTPROCESSOR_H
