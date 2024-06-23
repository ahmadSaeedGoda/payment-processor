#include <gtest/gtest.h>
#include "../include/PaymentProcessor.h"
#include "../include/Account.h"

const string TEST_LOG_FILE_NAME = "test_transaction_log.log";
const string PREFIX = PaymentProcessor::ACCOUNT_PREFIX;

TEST(PaymentProcessorTest, CreateAccount)
{
    FileLogger logger(TEST_LOG_FILE_NAME);
    PaymentProcessor processor(logger);
    processor.createAccount("1", 1000.0);
    EXPECT_EQ(processor.getAccountBalance(PREFIX + "1"), 1000.0);
}

TEST(PaymentProcessorTest, ProcessTransaction)
{
    FileLogger logger(TEST_LOG_FILE_NAME);
    PaymentProcessor processor(logger);
    processor.createAccount("User1", 1000.0);
    processor.createAccount("User2", 1000.0);

    bool success = processor.processTransaction(PREFIX + "1", PREFIX + "2", 500.0);
    EXPECT_TRUE(success);
    // Verify updated balances after transaction
    EXPECT_EQ(processor.getAccountBalance(PREFIX + "1"), 500.0);
    EXPECT_EQ(processor.getAccountBalance(PREFIX + "2"), 1500.0);
}

TEST(PaymentProcessorTest, ProcessInvalidTransaction)
{
    FileLogger logger(TEST_LOG_FILE_NAME);
    PaymentProcessor processor(logger);
    processor.createAccount("1", 1000.0);
    processor.createAccount("2", 1000.0);

    // Process transaction with insufficient funds
    bool success = processor.processTransaction(PREFIX + "1", PREFIX + "2", 5000.0);
    EXPECT_TRUE(success == false);

    // Balances should remain unchanged due to insufficient funds
    EXPECT_EQ(processor.getAccountBalance(PREFIX + "1"), 1000.0);
    EXPECT_EQ(processor.getAccountBalance(PREFIX + "2"), 1000.0);
}

TEST(PaymentProcessorTest, RetrieveBalanceForNonExistAccount)
{
    FileLogger logger(TEST_LOG_FILE_NAME);
    PaymentProcessor processor(logger);
    processor.createAccount("1", 1000.0);
    processor.createAccount("2", 1000.0);

    EXPECT_EQ(processor.getAccountBalance(PREFIX + "4"), -0.00);
    EXPECT_EQ(processor.getAccountBalance(PREFIX + "5"), -0.0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
