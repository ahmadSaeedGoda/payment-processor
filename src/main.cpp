#include "../include/Utility.h"
#include "../include/PaymentProcessor.h"
#include <sstream>
#include <thread>

using namespace std;
using namespace util;

const string LOG_FILE_NAME = "transaction_log.log";
const string ACC_PREFIX = PaymentProcessor::ACCOUNT_PREFIX;

int main()
{
    vector<Customer> customerList = createCustomersWithInitialBalances();

    FileLogger logger(LOG_FILE_NAME);
    PaymentProcessor processor(logger);

    for (const auto &customer : customerList)
    {
        processor.createAccount(customer.name, customer.balance);
    }

    auto lambda = [&processor](string acc1, string acc2, double amount) -> bool
    {
        return processor.processTransaction(acc1, acc2, amount);
    };

    vector<thread> threads;

    auto accId1 = processor.getAccounts()[0]->getId();
    auto accId2 = processor.getAccounts()[1]->getId();
    threads.emplace_back(lambda, accId1, accId2, 200); // 1=800, 2=700

    auto accId3 = processor.getAccounts()[2]->getId();
    threads.emplace_back(lambda, accId2, accId3, 150); // 2=550, 3=850

    threads.emplace_back(lambda, accId1, accId3, 300); // 1=500, 3=1150

    threads.emplace_back(lambda, accId1, accId1 + "4", 99999.9999); // Must Fail, because there is no account 4 created

    for (auto &thread : threads)
    {
        thread.join();
    }

    printCustomersBalancesAfterTxsProcessing(processor);

    printProcessedTxs(processor);

    return 0;
}
