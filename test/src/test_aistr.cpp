// 2017-11-15
// aicpp

#include <gtest/gtest.h>
#include <ailib/aistr.h>

class Test_aistr : public ::testing::Test
{
public:
    Test_aistr(void) { }
    virtual ~Test_aistr(void) { }
    void SetUp() override { }
    void TearDown() override { }
};

TEST_F(Test_aistr, lengthConst) {
    ASSERT_EQ(ai::lengthConst(""), 0);
    ASSERT_EQ(ai::lengthConst("13245"), 5);
    ASSERT_EQ(ai::lengthConst("13245 dsfgs"), 11);
    constexpr auto val4 = ai::lengthConst("13245 dsfgs");
    static_assert(val4 == 11, "");
}

TEST_F(Test_aistr, checkPointerNotNull) {
    EXPECT_THROW(ai::checkPointerNotNull(nullptr), std::invalid_argument);
    char buf[10];
    char* ptr = nullptr;
    EXPECT_THROW(ai::checkPointerNotNull(ptr), std::invalid_argument);
    ptr = &buf[0];
    EXPECT_NO_THROW(ai::checkPointerNotNull(ptr));
}

TEST_F(Test_aistr, length) {
    EXPECT_THROW(ai::length(nullptr, 10), std::invalid_argument);
    ASSERT_EQ(ai::length("", 10), 0);
    ASSERT_EQ(ai::length("1234", 10), 4);
    ASSERT_EQ(ai::length("123456789", 9), 9);
    ASSERT_EQ(ai::length("1234567890", 10), 10);
    ASSERT_EQ(ai::length("12345678901", 10), 10);
}

TEST_F(Test_aistr, length_static) {
    char buf[10] = {0};
    ASSERT_EQ(ai::length(buf), 0);

#ifdef _MSC_VER
    strcpy_s(buf, "1234");
    ASSERT_EQ(ai::length(buf), 4);
    strcpy_s(buf, "123456789");
    ASSERT_EQ(ai::length(buf), 9);
#else
    strcpy(buf, "1234");
    ASSERT_EQ(ai::length(buf), 4);
    strcpy(buf, "123456789");
    ASSERT_EQ(ai::length(buf), 9);
#endif

    // make buffer without last null-terminated char
    buf[9] = '0';
    EXPECT_THROW(ai::length(buf), std::out_of_range);

    buf[9] = '\0';
    ASSERT_EQ(ai::length(buf), 9);
}

TEST_F(Test_aistr, assign) {
    char buf[10] = {0};

    EXPECT_THROW(ai::assign(buf, nullptr), std::invalid_argument);

    ai::assign(buf, "1234");
    ASSERT_EQ(std::string(buf), "1234");
    ai::assign(buf, "");
    ASSERT_EQ(std::string(buf), "");

    ai::assign(buf, "123456789");
    ASSERT_EQ(std::string(buf), "123456789");

    ai::assign(buf, "12345678901");
    ASSERT_EQ(std::string(buf), "123456789");
}

TEST_F(Test_aistr, compare) {
    char buf[10] = {0};

    EXPECT_THROW(ai::compare(buf, nullptr), std::invalid_argument);

    ai::assign(buf, "1234");
    ASSERT_EQ(ai::compare(buf, "1234"), 0);
    ASSERT_NE(ai::compare(buf, "1234 "), 0);
    ASSERT_NE(ai::compare(buf, " 1234"), 0);
    ASSERT_EQ(ai::compare(buf, "1234\0"), 0);

    ai::assign(buf, "");
    ASSERT_EQ(ai::compare(buf, ""), 0);

    ai::assign(buf, "123456789");
    ASSERT_EQ(ai::compare(buf, "123456789"), 0);

    ai::assign(buf, "12345678901");
    ASSERT_EQ(ai::compare(buf, "123456789"), 0);
}

TEST_F(Test_aistr, append) {
    char buf[10] = {0};

    EXPECT_THROW(ai::append(buf, nullptr), std::invalid_argument);

    ai::append(buf, "1234");
    ASSERT_EQ(ai::compare(buf, "1234"), 0);

    ai::append(buf, "");
    ASSERT_EQ(ai::compare(buf, "1234"), 0);

    ai::append(buf, "5678");
    ASSERT_EQ(ai::compare(buf, "12345678"), 0);

    ai::append(buf, "9");
    ASSERT_EQ(ai::compare(buf, "123456789"), 0);

    ai::append(buf, "01");
    ASSERT_EQ(ai::compare(buf, "123456789"), 0);
}

