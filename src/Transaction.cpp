#include "../include/Transaction.h"
#include "../include/PaymentProcessor.h"

#include <sstream>

using namespace std;

Transaction::Transaction(Account *fromAccount, Account *toAccount, double amount)
    : fromAccount(fromAccount), toAccount(toAccount), amount(amount)
{
}

void Transaction::execute()
{
    stringstream ss;

    if (amount < PaymentProcessor::MIN_AMOUNT)
    {
        ss << "Transaction failed >>>> Minimum amount for a valid transaction is: " << PaymentProcessor::MIN_AMOUNT;
        throw invalid_argument(ss.str());
        ss.clear();
    }

    if (fromAccount->getBalance() < amount)
    {
        ss << "Transaction failed: Insufficient funds in account " << fromAccount->getId();
        throw invalid_argument(ss.str());
        ss.clear();
    }

    // Perform transaction
    fromAccount->withdraw(amount);
    toAccount->deposit(amount);

    timestamp = time(nullptr);

    return;
}

string Transaction::getId()
{
    return transactionId;
}

Account *Transaction::getSender()
{
    return fromAccount;
}

Account *Transaction::getReceiver()
{
    return toAccount;
}

double Transaction::getAmount()
{
    return amount;
}

time_t Transaction::getTimestamp()
{
    return timestamp;
}
