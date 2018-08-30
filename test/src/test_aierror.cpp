// 2017-11-15
// aicpp
#include <gtest/gtest.h>
#include <ailib/aierror.h>

class Test_aierror : public ::testing::Test
{
public:
    Test_aierror(void) { }
    virtual ~Test_aierror(void) { }
    void SetUp() override { }
    void TearDown() override { }
};

TEST_F(Test_aierror, formatError) {
    ASSERT_EQ(ai::formatError(0, ""), "Error: 0 - ");
    ASSERT_EQ(ai::formatError(1, "1 asdffd fdsa adf"), "Error: 1 - 1 asdffd fdsa adf");
    ASSERT_EQ(ai::formatError(-1, "msg"), "Error: -1 - msg");
    ASSERT_EQ(ai::formatError(-11345325, "msg"), "Error: -11345325 - msg");
    ASSERT_EQ(ai::formatError(5424432, "msg"), "Error: 5424432 - msg");
}

TEST_F(Test_aierror, stringFromErrno) {
#ifdef _MSC_VER
    for (auto i=0;i<20;i++)
    {
        _set_errno(i);
        auto str_default = ai::stringFromErrno();
        auto str_explicit = ai::stringFromErrno(i);
        ASSERT_FALSE(str_default.empty());
        ASSERT_EQ(str_default, str_explicit);
    }
#endif
}

TEST_F(Test_aierror, formatErrno) {
#ifdef _MSC_VER
    for (auto i=0;i<20;i++)
    {
        _set_errno(i);
        auto str_default = ai::stringFromErrno();
        auto str_explicit = ai::stringFromErrno(i);
        auto fmt_default = ai::formatErrno();
        auto fmt_explicit = ai::formatErrno(i);
        ASSERT_TRUE(fmt_default.find(str_default) > 0);
        ASSERT_TRUE(fmt_explicit.find(str_explicit) > 0);
    }
#endif
}

#ifdef _WIN32

TEST_F(Test_aierror, stringFromLastError) {
    for (auto i = 0; i<30; i++)
    {
        ::SetLastError(i);
        auto str_default = ai::stringFromLastError();
        auto str_explicit = ai::stringFromLastError(i);
        ASSERT_FALSE(str_default.empty()) << "[" << i << "] -> <empty> -> " << str_default;
        ASSERT_EQ(str_default, str_explicit);
    }
}

TEST_F(Test_aierror, formatLastError) {
    for (auto i = 0; i<30; i++)
    {
        _set_errno(i);
        auto str_default = ai::stringFromLastError();
        auto str_explicit = ai::stringFromLastError(i);
        auto fmt_default = ai::formatLastError();
        auto fmt_explicit = ai::formatLastError(i);
        ASSERT_TRUE(fmt_default.find(str_default) > 0);
        ASSERT_TRUE(fmt_explicit.find(str_explicit) > 0);
    }
}

#endif
