#include <gtest/gtest.h>
#include <ailib/aichrono.h>
#include <fmt/format.h>

using namespace ai;

//---------------------------------------------------------------------------
class Test_aichrono : public ::testing::Test
{
public:
    Test_aichrono(void)
    {
    };

    virtual ~Test_aichrono(void)
    {
    };

    static void SetUpTestCase()
    {
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

protected:
};


TEST_F(Test_aichrono, isEmpty_Duration)
{
    ASSERT_TRUE (isEmpty(Duration(0)));
    ASSERT_FALSE(isEmpty(Duration(-1)));
    ASSERT_FALSE(isEmpty(Duration(1)));

    ASSERT_TRUE (isEmpty(Nanoseconds(0)));
    ASSERT_FALSE(isEmpty(Nanoseconds(-1)));
    ASSERT_FALSE(isEmpty(Nanoseconds(1)));

    ASSERT_TRUE (isEmpty(Microseconds(0)));
    ASSERT_FALSE(isEmpty(Microseconds(-1)));
    ASSERT_FALSE(isEmpty(Microseconds(1)));

    ASSERT_TRUE (isEmpty(Milliseconds(0)));
    ASSERT_FALSE(isEmpty(Milliseconds(-1)));
    ASSERT_FALSE(isEmpty(Milliseconds(1)));

    ASSERT_TRUE (isEmpty(Seconds(0)));
    ASSERT_FALSE(isEmpty(Seconds(-1)));
    ASSERT_FALSE(isEmpty(Seconds(1)));

    ASSERT_TRUE (isEmpty(Minutes(0)));
    ASSERT_FALSE(isEmpty(Minutes(-1)));
    ASSERT_FALSE(isEmpty(Minutes(1)));

    ASSERT_TRUE (isEmpty(Hours(0)));
    ASSERT_FALSE(isEmpty(Hours(-1)));
    ASSERT_FALSE(isEmpty(Hours(1)));

    ASSERT_TRUE (isEmpty(Days(0)));
    ASSERT_FALSE(isEmpty(Days(-1)));
    ASSERT_FALSE(isEmpty(Days(1)));
}

TEST_F(Test_aichrono, isEmpty_TimePoint)
{
    ASSERT_TRUE (isEmpty(TimePoint()));
    ASSERT_TRUE (isEmpty(TimePoint::clock::from_time_t(0)));
    ASSERT_FALSE(isEmpty(TimePoint::clock::from_time_t(-1)));
    ASSERT_FALSE(isEmpty(TimePoint::clock::from_time_t(1)));
    ASSERT_FALSE(isEmpty(TimePoint::clock::now()));
}

TEST_F(Test_aichrono, isEmpty_SteadyTimePoint)
{
    ASSERT_TRUE (isEmpty(SteadyTimePoint()));
    ASSERT_FALSE(isEmpty(SteadyTimePoint::clock::now()));
}

TEST_F(Test_aichrono, toDuration)
{
    ASSERT_EQ(toDuration(Nanoseconds(123)).count() , 123);
    ASSERT_EQ(toDuration(Microseconds(123)).count(), 123 * 1000);
    ASSERT_EQ(toDuration(Milliseconds(123)).count(), 123 * 1000000);
    ASSERT_EQ(toDuration(Seconds(123)).count()     , 123 * 1000000000LL);
    ASSERT_EQ(toDuration(Minutes(123)).count()     , 123 * 1000000000LL * 60);
    ASSERT_EQ(toDuration(Hours(123)).count()       , 123 * 1000000000LL * 60 * 60);
    ASSERT_EQ(toDuration(Days(123)).count()        , 123 * 1000000000LL * 60 * 60 * 24);
}

TEST_F(Test_aichrono, toNanoseconds)
{
    ASSERT_EQ(toNanoseconds(Nanoseconds(123)).count() , 123);
    ASSERT_EQ(toNanoseconds(Microseconds(123)).count(), 123 * 1000);
    ASSERT_EQ(toNanoseconds(Milliseconds(123)).count(), 123 * 1000000);
    ASSERT_EQ(toNanoseconds(Seconds(123)).count()     , 123 * 1000000000LL);
    ASSERT_EQ(toNanoseconds(Minutes(123)).count()     , 123 * 1000000000LL * 60);
    ASSERT_EQ(toNanoseconds(Hours(123)).count()       , 123 * 1000000000LL * 60 * 60);
    ASSERT_EQ(toNanoseconds(Days(123)).count()        , 123 * 1000000000LL * 60 * 60 * 24);
}

TEST_F(Test_aichrono, toMicroseconds)
{
    ASSERT_EQ(toMicroseconds(Nanoseconds(123)).count()  , 0);
    ASSERT_EQ(toMicroseconds(Nanoseconds(12345)).count(), 12);
    ASSERT_EQ(toMicroseconds(Microseconds(123)).count() , 123);
    ASSERT_EQ(toMicroseconds(Milliseconds(123)).count() , 123 * 1000);
    ASSERT_EQ(toMicroseconds(Seconds(123)).count()      , 123 * 1000000LL);
    ASSERT_EQ(toMicroseconds(Minutes(123)).count()      , 123 * 1000000LL * 60);
    ASSERT_EQ(toMicroseconds(Hours(123)).count()        , 123 * 1000000LL * 60 * 60);
    ASSERT_EQ(toMicroseconds(Days(123)).count()         , 123 * 1000000LL * 60 * 60 * 24);
}

TEST_F(Test_aichrono, toMilliseconds)
{
    ASSERT_EQ(toMilliseconds(Nanoseconds(12345)).count(), 0);
    ASSERT_EQ(toMilliseconds(Microseconds(123)).count() , 0);
    ASSERT_EQ(toMilliseconds(Microseconds(723)).count() , 0);
    ASSERT_EQ(toMilliseconds(Microseconds(1723)).count(), 1);
    ASSERT_EQ(toMilliseconds(Milliseconds(123)).count() , 123);
    ASSERT_EQ(toMilliseconds(Seconds(123)).count()      , 123 * 1000LL);
    ASSERT_EQ(toMilliseconds(Minutes(123)).count()      , 123 * 1000LL * 60);
    ASSERT_EQ(toMilliseconds(Hours(123)).count()        , 123 * 1000LL * 60 * 60);
    ASSERT_EQ(toMilliseconds(Days(123)).count()         , 123 * 1000LL * 60 * 60 * 24);
}

TEST_F(Test_aichrono, toSeconds)
{
    ASSERT_EQ(toSeconds(Nanoseconds(12345)).count(), 0);
    ASSERT_EQ(toSeconds(Microseconds(123)).count() , 0);
    ASSERT_EQ(toSeconds(Milliseconds(123)).count() , 0);
    ASSERT_EQ(toSeconds(Milliseconds(723)).count() , 0);
    ASSERT_EQ(toSeconds(Milliseconds(1723)).count(), 1);
    ASSERT_EQ(toSeconds(Seconds(123)).count()      , 123 * 1LL);
    ASSERT_EQ(toSeconds(Minutes(123)).count()      , 123 * 1LL * 60);
    ASSERT_EQ(toSeconds(Hours(123)).count()        , 123 * 1LL * 60 * 60);
    ASSERT_EQ(toSeconds(Days(123)).count()         , 123 * 1LL * 60 * 60 * 24);
}

TEST_F(Test_aichrono, toMinutes)
{
    ASSERT_EQ(toMinutes(Nanoseconds(12345)).count(), 0);
    ASSERT_EQ(toMinutes(Microseconds(123)).count() , 0);
    ASSERT_EQ(toMinutes(Milliseconds(123)).count() , 0);
    ASSERT_EQ(toMinutes(Seconds(59)).count()       , 0);
    ASSERT_EQ(toMinutes(Seconds(60)).count()       , 1);
    ASSERT_EQ(toMinutes(Seconds(119)).count()      , 1);
    ASSERT_EQ(toMinutes(Minutes(123)).count()      , 123 * 1LL);
    ASSERT_EQ(toMinutes(Hours(123)).count()        , 123 * 1LL * 60);
    ASSERT_EQ(toMinutes(Days(123)).count()         , 123 * 1LL * 60 * 24);
}

TEST_F(Test_aichrono, toHours)
{
    ASSERT_EQ(toHours(Nanoseconds(12345)).count(), 0);
    ASSERT_EQ(toHours(Microseconds(123)).count() , 0);
    ASSERT_EQ(toHours(Milliseconds(123)).count() , 0);
    ASSERT_EQ(toHours(Seconds(123)).count()      , 0);
    ASSERT_EQ(toHours(Minutes(59)).count()       , 0);
    ASSERT_EQ(toHours(Minutes(60)).count()       , 1);
    ASSERT_EQ(toHours(Minutes(119)).count()      , 1);
    ASSERT_EQ(toHours(Hours(123)).count()        , 123 * 1LL);
    ASSERT_EQ(toHours(Days(123)).count()         , 123 * 1LL * 24);
}

TEST_F(Test_aichrono, toDays)
{
    ASSERT_EQ(toDays(Nanoseconds(12345)).count(), 0);
    ASSERT_EQ(toDays(Microseconds(123)).count() , 0);
    ASSERT_EQ(toDays(Milliseconds(123)).count() , 0);
    ASSERT_EQ(toDays(Seconds(60 * 60 * 24 - 1)).count()      , 0);
    ASSERT_EQ(toDays(Seconds(60 * 60 * 24)).count()      , 1);
    ASSERT_EQ(toDays(Minutes(123)).count()      , 0);
    ASSERT_EQ(toDays(Hours(23)).count()         , 0);
    ASSERT_EQ(toDays(Hours(24)).count()         , 1);
    ASSERT_EQ(toDays(Hours(40)).count()         , 1);
    ASSERT_EQ(toDays(Days(123)).count()         , 123);
}

TEST_F(Test_aichrono, toCTime)
{
    Clock::time_point empty;
    ASSERT_EQ(toCTime(empty), toSeconds(empty.time_since_epoch()).count());

    Clock::time_point now = Clock::now();
    ASSERT_EQ(toCTime(now), toSeconds(now.time_since_epoch()).count());
}

TEST_F(Test_aichrono, fromCTime)
{
    time_t empty = 0;
    ASSERT_EQ(fromCTime(empty), Clock::time_point());

    time_t now = time(nullptr);
    ASSERT_EQ(fromCTime(now), Clock::from_time_t(now));
}

TEST_F(Test_aichrono, tmGMT)
{
    std::time_t now = std::time(nullptr);
    ASSERT_NO_THROW(ai::tmGMT(now));

    const std::time_t invalid_max = std::numeric_limits<std::time_t>::max();
#ifndef _USE_32BIT_TIME_T
    ASSERT_THROW(ai::tmGMT(invalid_max), std::runtime_error);
#endif

    const std::time_t invalid_min = std::numeric_limits<std::time_t>::min();
    ASSERT_THROW(ai::tmGMT(invalid_min), std::runtime_error);

    const std::time_t invalid_min2 = -(time_t)(ai::toSeconds(ai::day * 1).count()); // above one day to exceed timezone limit
    ASSERT_THROW(ai::tmGMT(invalid_min2), std::runtime_error);

    std::time_t* invalid_ptr = nullptr;
    ASSERT_DEATH(ai::tmGMT(*invalid_ptr), "");
}

TEST_F(Test_aichrono, tmLocal)
{
     std::time_t now = std::time(nullptr);
     ASSERT_NO_THROW(ai::tmLocal(now));
     
     const std::time_t invalid_max = std::numeric_limits<std::time_t>::max();
     ASSERT_THROW(ai::tmLocal(invalid_max), std::runtime_error);
    
     const std::time_t invalid_min = std::numeric_limits<std::time_t>::min();
     ASSERT_THROW(ai::tmLocal(invalid_min), std::runtime_error);
    
     const std::time_t invalid_min2 = -(time_t)(ai::toSeconds(ai::day * 1).count()); // above one day to exceed timezone limit
     ASSERT_THROW(ai::tmLocal(invalid_min2), std::runtime_error);
    
     std::time_t* invalid_ptr = nullptr;
     ASSERT_DEATH(ai::tmLocal(*invalid_ptr), "");
}

TEST_F(Test_aichrono, gmtFromTm)
{
    std::time_t now = std::time(nullptr);
    const auto tm_gmt = ai::tmGMT(now);
    const auto res_now = ai::gmtFromTm(tm_gmt);
    ASSERT_EQ(now, res_now);

    constexpr std::time_t invalid_time = -1;
    ASSERT_THROW(ai::gmtFromTm(ai::tmGMT(-1)), std::runtime_error);

    std::tm tm_invalid;
    std::memset(&tm_invalid, -1, sizeof(tm_invalid));
    ASSERT_THROW(ai::gmtFromTm(tm_invalid), std::runtime_error) << "tm_invalid";
}

TEST_F(Test_aichrono, toLocalTime)
{
    std::time_t now = std::time(nullptr);
    ASSERT_GT(now, ai::toSeconds(ai::day).count());
    const auto now_local = ai::toLocalTime(now);
    const auto tm_local = ai::tmGMT(now_local);
    const auto res_local_now = ai::gmtFromTm(tm_local);
    ASSERT_EQ(now_local, res_local_now);

    // const auto zero_local = ai::toLocalTime(0);
    // const auto tm_zero = ai::tmGMT(zero_local);
    // const auto res_zero = ai::gmtFromTm(tm_zero);
    // ASSERT_EQ(zero_local, res_zero);
}

TEST_F(Test_aichrono, toGMTTime)
{
    std::time_t now = std::time(nullptr);
    ASSERT_GT(now, ai::toSeconds(ai::day).count());
    const auto now_gmt = ai::toGMTTime(now);
    const auto tm_gmt = ai::tmGMT(now_gmt);
    const auto res_gmt = ai::gmtFromTm(tm_gmt);
    ASSERT_EQ(now_gmt, res_gmt);
}

TEST_F(Test_aichrono, offsetLocalTimezoneInSeconds)
{
    const auto diff = difftime(123, 123);
    ASSERT_EQ(diff, 0.0);

    const auto offset_seconds = ai::offsetLocalTimezoneInSeconds();
    std::time_t now = std::time(nullptr);
    const auto now_local = ai::toLocalTime(now);
    const auto now_gmt = ai::toGMTTime(now);
    const auto diff_times = now_local - now_gmt;
    ASSERT_EQ(diff_times, offset_seconds);
}

TEST_F(Test_aichrono, timePointFromString_DefaultSuccess)
{
    std::string src_time = "2000-01-01 23:43:59";
    std::string format = ai::default_format_time_point;
    const auto tp = ai::timePointFromString(src_time, format);

    // get etalon
    std::tm tm = {};
    std::istringstream ss(src_time);
    ss >> std::get_time(&tm, format.c_str());
    const auto tp_etalon = ai::fromCTime(ai::gmtFromTm(tm));

    ASSERT_EQ(tp, tp_etalon);
}

TEST_F(Test_aichrono, timePointFromString_Success1)
{
    std::string src_time = "2000-01-01";
    std::string format = "%Y-%m-%d"; // locale independent format
    const auto tp = ai::timePointFromString(src_time, format);

    // get etalon
    std::tm tm = {};
    std::istringstream ss(src_time);
    ss >> std::get_time(&tm, format.c_str());
    const auto tp_etalon = ai::fromCTime(ai::gmtFromTm(tm));

    ASSERT_EQ(tp, tp_etalon);
}

TEST_F(Test_aichrono, timePointFromString_Success2)
{
    std::string src_time = "2018-12-31";
    std::string format = "%Y-%m-%d";
    const auto tp = ai::timePointFromString(src_time, format);

    // get etalon
    std::tm tm = {};
    std::istringstream ss(src_time);
    ss >> std::get_time(&tm, format.c_str());
    const auto tp_etalon = ai::fromCTime(ai::gmtFromTm(tm));

    ASSERT_EQ(tp, tp_etalon);
}

TEST_F(Test_aichrono, timePointFromString_Success3)
{
    std::string src_time = "2018 12 31";
    std::string format = "%Y %m %d"; // locale independent format
    const auto tp = ai::timePointFromString(src_time, format);

    // get etalon
    std::tm tm = {};
    std::istringstream ss(src_time);
    ss >> std::get_time(&tm, format.c_str());
    const auto tp_etalon = ai::fromCTime(ai::gmtFromTm(tm));

    ASSERT_EQ(tp, tp_etalon);
}

TEST_F(Test_aichrono, timePointFromString_EmptyInputTime)
{
    std::string src_time = "";
    std::string format = "%Y-%m-%d";
    ASSERT_THROW(ai::timePointFromString(src_time, format), std::runtime_error);
}

TEST_F(Test_aichrono, timePointFromString_EmptyInputFormat)
{
    std::string src_time = "2000-01-01 23:43:59";
    std::string format = "";
    ASSERT_THROW(ai::timePointFromString(src_time, format), std::runtime_error);
}

TEST_F(Test_aichrono, timePointFromString_InvalidInputTime)
{
    std::string src_time = "dsa000 fd2s1 f0a1";
    std::string format = "%Y-%m-%d";
    ASSERT_THROW(ai::timePointFromString(src_time, format), std::runtime_error);
}

TEST_F(Test_aichrono, timePointFromString_InvalidInputFormat)
{
    std::string src_time = "2000-01-01 23:43:59";
    std::string format = "2000-01-01 23:43:59";
    ASSERT_THROW(ai::timePointFromString(src_time, format), std::runtime_error);
}

TEST_F(Test_aichrono, stringFromTimePoint_DefaultSuccess)
{
    const auto now = ai::Clock::now();
    std::string format = ai::default_format_time_point;
    const auto str_time = ai::stringFromTimePoint(now);

    // get etalon
    const auto tm = tmGMT(toCTime(now));
    std::ostringstream ss;
    ss << std::put_time(&tm, format.c_str());
    const auto etalon = ss.str();

    ASSERT_EQ(str_time, etalon);
}

TEST_F(Test_aichrono, stringFromTimePoint_Success1)
{
    const auto now = ai::Clock::now();
    std::string format = "%Y-%m-%d";
    const auto str_time = ai::stringFromTimePoint(now, format);

    // get etalon
    const auto tm = tmGMT(toCTime(now));
    std::ostringstream ss;
    ss << std::put_time(&tm, format.c_str());
    const auto etalon = ss.str();

    ASSERT_EQ(str_time, etalon);
}

TEST_F(Test_aichrono, stringFromTimePoint_Success2)
{
    const auto now = ai::Clock::now();
    std::string format = "%Y %m %d";
    const auto str_time = ai::stringFromTimePoint(now, format);

    // get etalon
    const auto tm = tmGMT(toCTime(now));
    std::ostringstream ss;
    ss << std::put_time(&tm, format.c_str());
    const auto etalon = ss.str();

    ASSERT_EQ(str_time, etalon);
}

TEST_F(Test_aichrono, stringFromTimePoint_EmptyInputFormat)
{
    const auto now = ai::Clock::now();
    std::string format = "";
    ASSERT_EQ(ai::stringFromTimePoint(now, format), "");
}

TEST_F(Test_aichrono, stringFromTimePoint_EmptyInputTime)
{
    const ai::TimePoint tp = {};
    std::string format = "%Y-%m-%d";
    ASSERT_EQ(ai::stringFromTimePoint(tp, format), "1970-01-01");
}

TEST_F(Test_aichrono, stringFromTimePoint_InvalidInputFormat1)
{
    const auto now = ai::Clock::now();
    std::string format = "dsa000 fd2s1 f0a1";
    ASSERT_EQ(ai::stringFromTimePoint(now, format), format);
}

TEST_F(Test_aichrono, stringFromTimePoint_InvalidInputFormat2)
{
    const auto now = ai::Clock::now();
    std::string format = "%q"; // invalid sp
    ASSERT_DEATH(ai::stringFromTimePoint(now, format), "");
}

TEST_F(Test_aichrono, durationFromString_Empty)
{
    std::string str_duration = "";
    const auto dur = ai::durationFromString(str_duration);
    ASSERT_EQ(dur, ai::Duration{});
}

TEST_F(Test_aichrono, durationFromString_Invalid)
{
    ASSERT_EQ(ai::durationFromString("asdf"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString(" "), ai::Duration{});
    ASSERT_EQ(ai::durationFromString(" fs"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString(" hj45gd"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString("45gd"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString("tr45d"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString("tr45s"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString("45se"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString("45s e"), ai::Duration{});
}

TEST_F(Test_aichrono, durationFromString_InvalidMultipleRatios)
{
    // doesn't allow multiple ratios
    ASSERT_EQ(ai::durationFromString("45s45s"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString("45m45s"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString("45m 45s"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString("45m 45"), ai::Duration{});
}

TEST_F(Test_aichrono, durationFromString_InvalidNegative)
{
    // doesn't allow multiple ratios
    ASSERT_EQ(ai::durationFromString("-45s"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString(" -45s"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString("-45"), ai::Duration{});
    ASSERT_EQ(ai::durationFromString("-45m"), ai::Duration{});
}

TEST_F(Test_aichrono, durationFromString_Valid)
{
    static std::pair<std::string, Duration> ratios[] = {
        std::make_pair("ms", millisecond),
        std::make_pair("s", second),
        std::make_pair("m", minute),
        std::make_pair("h", hour),
        std::make_pair("d", day),
    };
    static size_t numbers[] = {
        1,
        2,
        9,
        10,
        99,
        101,
        999,
        54201,
    };

    for (const auto& ratio : ratios)
    {
        for (const auto& num : numbers)
        {
            const auto str_base = std::to_string(num) + ratio.first;
            const auto dur_match = ratio.second * num;
            ASSERT_EQ(ai::durationFromString(str_base), dur_match) << "ratio:" << ratio.first << " num:" << num;
            ASSERT_EQ(ai::durationFromString(str_base + "  "), dur_match) << "ratio:" << ratio.first << " num:" << num;
            ASSERT_EQ(ai::durationFromString("  " + str_base), dur_match) << "ratio:" << ratio.first << " num:" << num;
            ASSERT_EQ(ai::durationFromString("  " + str_base + "  "), dur_match) << "ratio:" << ratio.first << " num:" << num;
            if (ratio.second == second)
            {
                ASSERT_EQ(ai::durationFromString(std::to_string(num)), dur_match) << "ratio:" << ratio.first << " num:" << num;
            }
        }
    }
}

TEST_F(Test_aichrono, stringFromDuration_Days)
{
    static size_t parts[] = {
        1,
        2,
        9,
        10,
        99,
        101,
        999,
        54201,
    };

    for (const auto& num : parts)
    {
        const auto str_match = std::to_string(num * 24) + ":00:00.000";
        const auto dur = day * num;
        ASSERT_EQ(stringFromDuration(dur), str_match) << "num:" << num;
        ASSERT_EQ(stringFromDuration(-dur), "-" + str_match) << "num:" << num;
    }
}

TEST_F(Test_aichrono, stringFromDuration_Hours)
{
    static size_t parts[] = {
        1,
        2,
        9,
        10,
        99,
        101,
        999,
        54201,
    };

    for (const auto& num : parts)
    {
        const auto str_match = fmt::format("{:02}", num) + ":00:00.000";
        const auto dur = hour * num;
        ASSERT_EQ(stringFromDuration(dur), str_match) << "num:" << num;
        ASSERT_EQ(stringFromDuration(-dur), "-" + str_match) << "num:" << num;
    }
}

TEST_F(Test_aichrono, stringFromDuration_Minutes)
{
    static size_t parts[] = {
        1,
        2,
        9,
        10,
        59,
    };

    for (const auto& num : parts)
    {
        const auto str_match = fmt::format("{:02}", num) + ":00.000";
        const auto dur = minute * num;
        ASSERT_EQ(stringFromDuration(dur), str_match) << "num:" << num;
        ASSERT_EQ(stringFromDuration(-dur), "-" + str_match) << "num:" << num;
    }
}

TEST_F(Test_aichrono, stringFromDuration_Seconds)
{
    static size_t parts[] = {
        1,
        2,
        9,
        10,
        59,
    };

    for (const auto& num : parts)
    {
        const auto str_match = fmt::format("{:02}", num) + ".000";
        const auto dur = second * num;
        ASSERT_EQ(stringFromDuration(dur), str_match) << "num:" << num;
        ASSERT_EQ(stringFromDuration(-dur), "-" + str_match) << "num:" << num;
    }
}

TEST_F(Test_aichrono, stringFromDuration_Milliseconds)
{
    static size_t parts[] = {
        1,
        2,
        9,
        10,
        59,
        101,
        999,
    };

    for (const auto& num : parts)
    {
        const auto str_match = "00." + fmt::format("{:03}", num);
        const auto dur = millisecond * num;
        ASSERT_EQ(stringFromDuration(dur), str_match) << "num:" << num;
        ASSERT_EQ(stringFromDuration(-dur), "-" + str_match) << "num:" << num;
    }
}

TEST_F(Test_aichrono, stringFromDuration_Complex)
{
    ASSERT_EQ(stringFromDuration(134h + 33min + 5s + 543ms), "134:33:05.543");
    ASSERT_EQ(stringFromDuration(0h + 33min + 5s + 543ms), "33:05.543");
    ASSERT_EQ(stringFromDuration(0h + 120min + 5s + 543ms), "02:00:05.543");
    ASSERT_EQ(stringFromDuration(0h + 120min + 5s + 0ms), "02:00:05.000");
}

TEST_F(Test_aichrono, stringFromDuration_Empty)
{
    ASSERT_EQ(stringFromDuration({}), "00.000");
}
