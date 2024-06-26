#include "../include/Utility.h"
#include "../include/PaymentProcessor.h"
#include "../include/ThreadPool.h"
#include <sstream>
#include <thread>

using namespace std;
using namespace util;

const string LOG_FILE_NAME = "transaction_log.log";
const string ACC_PREFIX = PaymentProcessor::ACCOUNT_PREFIX;
const int WORKERS_COUNT = 5;

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

    ThreadPool pool(WORKERS_COUNT);

    vector<future<bool>> futures;
    vector<unique_ptr<Account>> createdAccounts = processor.getAccounts();

    // Pair each account with every other account,
    // think of it like a feast/game such as in Christmas e.g where everybody treats the other
    for (size_t i = 0; i < createdAccounts.size(); ++i)
    {
        for (size_t j = i + 1; j < createdAccounts.size(); ++j)
        {
            auto accId1 = createdAccounts[i]->getId();
            auto accId2 = createdAccounts[j]->getId();

            double amount1 = getRandomAmount(0, 1000);
            double amount2 = getRandomAmount(0, 1000);

            // Enqueue transactions using the thread pool
            futures.emplace_back(pool.enqueue(lambda, accId1, accId2, amount1));
            futures.emplace_back(pool.enqueue(lambda, accId2, accId1, amount2));
        }
    }

    // Wait for transactions to complete
    for (auto &future : futures)
    {
        future.get();
    }

    printCustomersBalancesAfterTxsProcessing(processor);

    printProcessedTxs(processor);

    return 0;
}
