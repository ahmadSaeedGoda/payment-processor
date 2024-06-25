#ifndef UTILITY_H
#define UTILITY_H

#include "ConsoleLogger.h"
#include "PaymentProcessor.h"

using namespace std;

namespace util
{
    const vector<string> CUSTOMERS = {"Alice", "Bob", "Charlie"};
    const vector<double> INITIAL_BALANCES = {1000.0, 500.0, 700.0};

    struct Customer
    {
        string name;
        double balance;
    };

    vector<Customer> createCustomersWithInitialBalances();
    void printCustomersBalancesAfterTxsProcessing(PaymentProcessor &processor);
    void printProcessedTxs(PaymentProcessor &processor);
}

#endif // UTILITY_H
