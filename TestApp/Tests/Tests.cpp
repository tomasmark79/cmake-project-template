#include <gtest/gtest.h>

#include "HelloWorld.hpp"

class HelloWorldTest : public ::testing::Test
{
protected:
    HelloWorld hw;
    virtual void SetUp() {};
    virtual void TearDown() {};
};

TEST_F(HelloWorldTest, HelloWorld)
{
    testing::internal::CaptureStdout();
    hw.sayHello();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Hello World!\n");
}
