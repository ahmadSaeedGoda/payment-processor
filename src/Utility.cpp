#include "../include/Utility.h"
#include "../include/ConsoleLogger.h"
#include "../include/PaymentProcessor.h"

using namespace std;

namespace util
{
    vector<Customer> createCustomersWithInitialBalances()
    {
        vector<Customer> customerList;
        customerList.reserve(CUSTOMERS.size());

        for (size_t i = 0; i < CUSTOMERS.size(); ++i)
        {
            customerList.emplace_back(Customer{CUSTOMERS[i], INITIAL_BALANCES[i]});
        }
        return customerList;
    }

    void printCustomersBalancesAfterTxsProcessing(PaymentProcessor &processor)
    {
        Logger *consoleLogger = new ConsoleLogger();

        consoleLogger->log("Final Balances:");

        vector<unique_ptr<Account>> ppAccounts = processor.getAccounts();

        for (const auto &acc : ppAccounts)
        {
            consoleLogger->log(acc->getName() + ": " + to_string(acc->getBalance()));
        }

        delete consoleLogger;
    }

    void printProcessedTxs(PaymentProcessor &processor)
    {
        Logger *consoleLogger = new ConsoleLogger();

        consoleLogger->log("Processed Transactions:");

        vector<unique_ptr<Transaction>> ppTxs = processor.getTxs();

        for (const auto &tx : ppTxs)
        {
            consoleLogger->log(
                "[" + to_string(tx->getTimestamp()) + "]" + ": From " + tx->getSender()->getName() + " to " + tx->getReceiver()->getName() + ", amount = " + to_string(tx->getAmount()));
        }

        delete consoleLogger;
    }
}
