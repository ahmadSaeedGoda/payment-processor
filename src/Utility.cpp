#include "../include/Utility.h"
#include "../include/ConsoleLogger.h"
#include "../include/PaymentProcessor.h"

#include <sstream>

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

    void printCustomersBalancesAfterTxsProcessing(vector<Customer> &customerList, PaymentProcessor &processor)
    {
        Logger *consoleLogger = new ConsoleLogger();

        consoleLogger->log("Final Balances:");

        for (size_t i = 0; i < customerList.size(); i++)
        {
            const string ab = to_string(processor.getAccountBalance(to_string(i + 1)));
            stringstream ss;
            ss << customerList[i].name << ": " << ab;

            const string message = ss.str();

            consoleLogger->log(message);
        }

        delete consoleLogger;
    }
}
