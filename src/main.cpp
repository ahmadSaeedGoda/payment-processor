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

    auto lambda = [&processor](int acc1, int acc2, double amount) -> bool
    {
        string acc1Id = ACC_PREFIX + to_string(acc1);
        string acc2Id = ACC_PREFIX + to_string(acc2);
        return processor.processTransaction(acc1Id, acc2Id, amount);
    };

    vector<thread> threads;

    threads.emplace_back((lambda), 1, 2, 200); // 1=800, 2=700

    threads.emplace_back((lambda), 2, 3, 150); // 2=550, 3=850

    threads.emplace_back((lambda), 1, 3, 300); // 1=500, 3=1150

    threads.emplace_back((lambda), 1, 4, 99999.9999); // Must Fail, because there is no account 4 created

    for (auto &thread : threads)
    {
        thread.join();
    }

    util::printCustomersBalancesAfterTxsProcessing(customerList, processor);

    return 0;
}
