#include "../include/Transaction.h"
using namespace std;

Transaction::Transaction(const string &transId, const string &fromId, const string &toId, double amt)
    : transactionId(transId), fromAccountId(fromId), toAccountId(toId), amount(amt)
{
    timestamp = time(nullptr);
}
