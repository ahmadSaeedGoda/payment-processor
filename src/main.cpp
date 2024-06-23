#include "../include/Utility.h"
#include "../include/PaymentProcessor.h"
#include <sstream>
#include <thread>

using namespace std;

const string LOG_FILE_NAME = "transaction_log.log";
const string ACC_PREFIX = PaymentProcessor::ACCOUNT_PREFIX;

int main()
{
    vector<util::Customer> customerList = util::createCustomersWithInitialBalances();

    FileLogger logger(LOG_FILE_NAME);
    PaymentProcessor processor(logger);

    for (const auto &customer : customerList)
    {
        processor.createAccount(customer.name, customer.balance);
    }

    vector<thread> threads;
    threads.emplace_back(
        ([&processor]()
         { processor.processTransaction(
               ACC_PREFIX + to_string(1),
               ACC_PREFIX + to_string(2),
               200.0); })); // 1=800, 2=700

    threads.emplace_back(
        ([&processor]()
         { processor.processTransaction(
               ACC_PREFIX + to_string(2),
               ACC_PREFIX + to_string(3),
               150.0); })); // 2=550, 3=850

    threads.emplace_back(
        ([&processor]()
         { processor.processTransaction(
               ACC_PREFIX + to_string(1),
               ACC_PREFIX + to_string(3),
               300.0); })); // 1=500, 3=1150

    threads.emplace_back(
        ([&processor]()
         { processor.processTransaction(
               ACC_PREFIX + to_string(1),
               ACC_PREFIX + to_string(4),
               99999.9999); })); // Must Fail, because there is no account 4 created

    for (auto &thread : threads)
    {
        thread.join();
    }

    util::printCustomersBalancesAfterTxsProcessing(customerList, processor);

    return 0;
}
