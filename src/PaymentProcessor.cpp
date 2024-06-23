#include "../include/PaymentProcessor.h"
#include <sstream>

using namespace std;

const string PaymentProcessor::ACCOUNT_PREFIX = "ACC_";

PaymentProcessor::PaymentProcessor(FileLogger &logger) : logger(logger) {}

void PaymentProcessor::createAccount(const string &ownerName, double initialBalance)
{
    lock_guard<mutex> lock(accountsMutex);

    string accountId = generateAccountId();

    Account *acc = new Account(accountId, ownerName, initialBalance);

    accounts.push_back(acc);

    // Log account creation
    stringstream ss;
    ss << "Created account for " << ownerName << " with ID: " << accountId;
    logger.log(ss.str());
}

bool PaymentProcessor::processTransaction(const string &fromAccountId, const string &toAccountId, double amount)
{
    lock_guard<mutex> lock(accountsMutex);

    Account *fromAccount = findAccountById(fromAccountId);
    Account *toAccount = findAccountById(toAccountId);

    if (fromAccount == nullptr || toAccount == nullptr)
    {
        logger.log("Transaction failed: Invalid account ID");
        return false;
    }

    if (fromAccount->getBalance() < amount)
    {
        stringstream ss;
        ss << "Transaction failed: Insufficient funds in account " << fromAccountId;
        logger.log(ss.str());
        return false;
    }

    // Perform transaction
    fromAccount->withdraw(amount);
    toAccount->deposit(amount);

    // Log transaction details
    stringstream ss;
    ss << "Processed transaction from " << fromAccountId << " to " << toAccountId << " amount: " << amount;
    logger.log(ss.str());

    return true;
}

double PaymentProcessor::getAccountBalance(const string &accountId)
{
    lock_guard<mutex> lock(accountsMutex);

    Account *account = findAccountById(accountId);

    if (account == nullptr)
    {
        stringstream ss;
        ss << "Account not found: " << accountId;
        logger.log(ss.str());

        return -0.0;
    }
    return account->getBalance();
}

string PaymentProcessor::generateAccountId()
{
    return ACCOUNT_PREFIX + to_string(accounts.size() + 1);
}

Account *PaymentProcessor::findAccountById(const string &accountId)
{
    for (auto account : accounts)
    {
        if (account->getId() == ACCOUNT_PREFIX + accountId)
        {
            return account;
        }
    }
    return nullptr;
}
