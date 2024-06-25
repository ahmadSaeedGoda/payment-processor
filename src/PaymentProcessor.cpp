#include "../include/PaymentProcessor.h"
#include "../include/Transaction.h"

#include <sstream>

using namespace std;

const string PaymentProcessor::ACCOUNT_PREFIX = "ACC_";
const double PaymentProcessor::MIN_AMOUNT = 1.0;

PaymentProcessor::PaymentProcessor(FileLogger &logger) : logger(logger) {}

void PaymentProcessor::createAccount(const string &ownerName, double initialBalance)
{
    lock_guard<mutex> lock(accountsMutex);

    string accountId = generateAccountId();

    auto acc = make_unique<Account>(accountId, ownerName, initialBalance);

    accounts.emplace_back(move(acc));

    // Log account creation
    logger.log("Created account for " + ownerName + " with ID: " + accountId);
}

bool PaymentProcessor::processTransaction(const string &fromAccountId, const string &toAccountId, double amount)
{
    lock_guard<mutex> lock(accountsMutex);
    lock_guard<mutex> txLock(txsMutex);

    try
    {
        Account &fromAccount = findAccountById(fromAccountId);
        Account &toAccount = findAccountById(toAccountId);

        auto tx = make_unique<Transaction>(&fromAccount, &toAccount, amount);
        tx->execute();

        txs.emplace_back(move(tx));
    }
    catch (const exception &e)
    {
        logger.log(e.what());
        return false;
    }

    // Log transaction details
    stringstream ss;
    ss << "Processed transaction from " << fromAccountId << " to " << toAccountId << " amount: " << amount;
    logger.log(ss.str());

    return true;
}

double PaymentProcessor::getAccountBalance(const string &accountId)
{
    lock_guard<mutex> lock(accountsMutex);

    try
    {
        Account &account = findAccountById(accountId);
        return account.getBalance();
    }
    catch (const exception &e)
    {
        logger.log("Account not found: " + accountId);

        return -0.0;
    }
}

string PaymentProcessor::generateAccountId()
{
    return ACCOUNT_PREFIX + to_string(accounts.size() + 1);
}

Account &PaymentProcessor::findAccountById(const string &accountId)
{
    for (auto &account : accounts)
    {
        if (account->getId() == accountId)
        {
            return *account;
        }
    }

    throw runtime_error("Account not found");
}

vector<unique_ptr<Account>> PaymentProcessor::getAccounts()
{
    lock_guard<mutex> lock(accountsMutex);

    vector<unique_ptr<Account>> copyAccounts;
    copyAccounts.reserve(accounts.size());

    for (const auto &account : accounts)
    {
        copyAccounts.push_back(make_unique<Account>(*account));
    }

    return copyAccounts;
}

vector<unique_ptr<Transaction>> PaymentProcessor::getTxs()
{
    lock_guard<mutex> lock(txsMutex);

    vector<unique_ptr<Transaction>> copyTxs;
    copyTxs.reserve(txs.size());

    for (const auto &tx : txs)
    {
        copyTxs.push_back(make_unique<Transaction>(*tx));
    }

    return copyTxs;
}
