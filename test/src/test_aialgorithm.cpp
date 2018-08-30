// 2017-11-23
// aicpp

#include <gtest/gtest.h>
#include <ailib/aialgorithm.h>

class Test_aialgorithm : public ::testing::Test
{
public:
    Test_aialgorithm(void)
    {
    }

    virtual ~Test_aialgorithm(void)
    {
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(Test_aialgorithm, countOf)
{
    char buf1[1];
    ASSERT_EQ(ai::countOf(buf1), 1);
    int buf2[1];
    ASSERT_EQ(ai::countOf(buf2), 1);
    char buf3[1234];
    ASSERT_EQ(ai::countOf(buf3), 1234);
    int buf4[1234];
    ASSERT_EQ(ai::countOf(buf4), 1234);
    constexpr auto val4 = ai::countOf(buf4);
    static_assert(val4 == 1234, "");

    struct A
    {
        int    a;
        double f;
    };
    A buf5[123];
    ASSERT_EQ(ai::countOf(buf5), 123);
}

TEST_F(Test_aialgorithm, fill)
{
    // one
    char buf1[1];
    std::memset(&buf1, 0, sizeof buf1);
    ai::fill(buf1, 'U');
    ASSERT_EQ(buf1[0], 'U');

    // many
    {
        int        buf[132];
        const auto size2 = ai::countOf(buf);
        std::memset(&buf, 0, size2 * sizeof(int));
        ai::fill(buf, 543);
        for (size_t i = 0; i < size2; i++)
        {
            ASSERT_EQ(buf[i], 543);
        }
    }
}

TEST_F(Test_aialgorithm, fillZero)
{
    // one
    {
        char buf1[1];
        std::memset(&buf1, 65, sizeof buf1);
        ai::fillZero(buf1);
        ASSERT_EQ(buf1[0], '\0');
    }

    // many
    {
        int        buf[132];
        const auto size2 = ai::countOf(buf);
        std::memset(&buf, 65, size2 * sizeof(int));
        ai::fillZero(buf);
        for (size_t i = 0; i < size2; i++)
        {
            ASSERT_EQ(buf[i], 0);
        }
    }
}

TEST_F(Test_aialgorithm, extractKeys)
{
    // prepare
    std::map<size_t, size_t> map1;
    std::map<std::string, size_t> map2;
    std::map<size_t, std::string> map3;
    std::map<std::string, std::string> map4;
    static constexpr auto count = 5;

    std::stringstream etalon_str;
    for (size_t i=0;i<count;i++)
    {
        map1.insert(std::make_pair(i,  i * 100U));
        map2.insert(std::make_pair(std::to_string(i), i * 200U));
        map3.insert(std::make_pair(i, std::to_string(i * 300U)));
        map4.insert(std::make_pair(std::to_string(i), std::to_string(i * 400U)));
        etalon_str << i << " ";
    }

    const auto keys1 = ai::extractKeys(map1);
    const auto keys2 = ai::extractKeys(map2);
    const auto keys3 = ai::extractKeys(map3);
    const auto keys4 = ai::extractKeys(map4);
    std::stringstream actual_str[4];
    for (size_t i = 0; i<count; i++)
    {
        actual_str[0] << keys1[i] << " ";
        actual_str[1] << keys2[i] << " ";
        actual_str[2] << keys3[i] << " ";
        actual_str[3] << keys4[i] << " ";
    }

    ASSERT_EQ(actual_str[0].str(), etalon_str.str());
    ASSERT_EQ(actual_str[1].str(), etalon_str.str());
    ASSERT_EQ(actual_str[2].str(), etalon_str.str());
    ASSERT_EQ(actual_str[3].str(), etalon_str.str());
}
