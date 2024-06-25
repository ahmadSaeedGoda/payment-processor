#include <gtest/gtest.h>
#include "../include/PaymentProcessor.h"
#include "../include/Account.h"

const string TEST_LOG_FILE_NAME = "test_transaction_log.log";
const string PREFIX = PaymentProcessor::ACCOUNT_PREFIX;

TEST(PaymentProcessorTest, CreateAccount)
{
    FileLogger logger(TEST_LOG_FILE_NAME);
    PaymentProcessor processor(logger);
    processor.createAccount("Mickey", 5555.12);

    auto accName = processor.getAccounts()[0]->getName();
    auto accBal = processor.getAccounts()[0]->getBalance();

    EXPECT_EQ(accName, "Mickey");
    EXPECT_EQ(accBal, 5555.12);
}

TEST(PaymentProcessorTest, ProcessTransaction)
{
    const string customer1 = "Mickey";
    const string customer2 = "Minnie";

    FileLogger logger(TEST_LOG_FILE_NAME);
    PaymentProcessor processor(logger);

    processor.createAccount(customer1, 1000.0);
    processor.createAccount(customer2, 1000.0);

    auto customer1AccId = processor.getAccounts()[0].get()->getId();
    auto customer2AccId = processor.getAccounts()[1].get()->getId();

    bool success = processor.processTransaction(customer1AccId, customer2AccId, 700.0);
    EXPECT_TRUE(success);

    // Verify updated balances after transaction

    auto customer1AccName = processor.getAccounts()[0]->getName();
    auto customer1AccBal = processor.getAccounts()[0]->getBalance();

    auto customer2AccName = processor.getAccounts()[1]->getName();
    auto customer2AccBal = processor.getAccounts()[1]->getBalance();

    EXPECT_EQ(customer1AccName, customer1);
    EXPECT_EQ(customer1AccBal, 300);

    EXPECT_EQ(customer2AccName, customer2);
    EXPECT_EQ(customer2AccBal, 1700);
}

TEST(PaymentProcessorTest, ProcessInvalidTransaction)
{

    const string customer1 = "Bugs";
    const string customer2 = "Bunny";

    FileLogger logger(TEST_LOG_FILE_NAME);
    PaymentProcessor processor(logger);
    processor.createAccount(customer1, 7000.0);
    processor.createAccount(customer2, 2000.0);

    // Process transaction with insufficient funds

    auto customer1AccId = processor.getAccounts()[0].get()->getId();
    auto customer2AccId = processor.getAccounts()[1].get()->getId();

    bool success = processor.processTransaction(customer1AccId, customer2AccId, 90000);
    EXPECT_TRUE(success == false);

    // Balances should remain unchanged due to insufficient funds
    EXPECT_EQ(processor.getAccountBalance(customer1AccId), 7000.0);
    EXPECT_EQ(processor.getAccountBalance(customer2AccId), 2000.0);
}

TEST(PaymentProcessorTest, RetrieveBalanceForNonExistAccount)
{
    const string customer1 = "Bugs";
    const string customer2 = "Bunny";

    FileLogger logger(TEST_LOG_FILE_NAME);
    PaymentProcessor processor(logger);

    processor.createAccount(customer1, 1000.0);
    processor.createAccount(customer2, 1000.0);

    EXPECT_EQ(processor.getAccountBalance("Minnie"), -0.00);
    EXPECT_EQ(processor.getAccountBalance("Mickey"), -0.0);

    auto customer2AccId = processor.getAccounts()[1].get()->getId();
    auto customer2AccBal = processor.getAccounts()[1].get()->getBalance();
    auto txRes = processor.processTransaction(customer2AccId, "Mickey", 500);

    EXPECT_EQ(txRes, false);
    EXPECT_EQ(processor.getAccountBalance(customer2AccId), customer2AccBal);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
