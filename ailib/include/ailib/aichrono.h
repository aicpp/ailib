// 2018-06-01
// aicpp
#pragma once

#include <chrono>
#include <string>


/// @defgroup aichrono aichrono
/// Helpers to work with time and duration

namespace ai
{
    /// @addtogroup aichrono
    /// @{

    using namespace std::chrono_literals;

    // default duration ratio
    using Duration = std::chrono::nanoseconds;

    // common periods in default ratio
    static constexpr Duration millisecond = std::chrono::duration_cast<Duration>(1ms);
    static constexpr Duration second      = std::chrono::duration_cast<Duration>(1s);
    static constexpr Duration minute      = std::chrono::duration_cast<Duration>(1min);
    static constexpr Duration hour        = std::chrono::duration_cast<Duration>(1h);
    static constexpr Duration day         = std::chrono::duration_cast<Duration>(24h);
    static constexpr Duration week        = std::chrono::duration_cast<Duration>(24h * 7);

    // common duration types
    using Nanoseconds = std::chrono::nanoseconds;
    using Microseconds = std::chrono::microseconds;
    using Milliseconds = std::chrono::milliseconds;
    using Seconds = std::chrono::seconds;
    using Minutes = std::chrono::minutes;
    using Hours = std::chrono::hours;
    using Days = std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>::type>;

    // common clock types
    using Clock = std::chrono::system_clock;
    using TimePoint = Clock::time_point;
    using SteadyClock = std::chrono::steady_clock;
    using SteadyTimePoint = SteadyClock::time_point;

#pragma region common clock functions

    /// @brief Check if duration have zero value
    /// @param[in] duration duration to check
    /// @return true if duration.count() == 0
    template <typename Rep, typename Period>
    bool isEmpty(const std::chrono::duration<Rep, Period>& duration);

    /// @brief Check if time point have zero value
    /// @param[in] time_point time point to check
    /// @return true if time_since_epoch().count() == 0
    bool isEmpty(const TimePoint& time_point);

    /// @brief Check if time point have zero value
    /// @param[in] time_point time point to check
    /// @return true if time_since_epoch().count() == 0
    bool isEmpty(const SteadyTimePoint& time_point);

#pragma endregion

#pragma region convert durations

    /// @brief convert any duration type to Duration
    /// @param[in] duration duration to convert
    /// @return duration in ratio Duration
    template <typename Rep, typename Period>
    Duration toDuration(const std::chrono::duration<Rep, Period> &duration);

    /// @brief convert any duration type to Nanoseconds
    /// @param[in] duration duration to convert
    /// @return duration in ratio Nanoseconds
    template <typename Rep, typename Period>
    Nanoseconds toNanoseconds(const std::chrono::duration<Rep, Period> &duration);

    /// @brief convert any duration type to Microseconds
    /// @param[in] duration duration to convert
    /// @return duration in ratio Microseconds
    template <typename Rep, typename Period>
    Microseconds toMicroseconds(const std::chrono::duration<Rep, Period> &duration);

    /// @brief convert any duration type to Milliseconds
    /// @param[in] duration duration to convert
    /// @return duration in ratio Milliseconds
    template <typename Rep, typename Period>
    Milliseconds toMilliseconds(const std::chrono::duration<Rep, Period> &duration);

    /// @brief convert any duration type to Seconds
    /// @param[in] duration duration to convert
    /// @return duration in ratio Seconds
    template <typename Rep, typename Period>
    Seconds toSeconds(const std::chrono::duration<Rep, Period> &duration);

    /// @brief convert any duration type to Minutes
    /// @param[in] duration duration to convert
    /// @return duration in ratio Minutes
    template <typename Rep, typename Period>
    Minutes toMinutes(const std::chrono::duration<Rep, Period> &duration);

    /// @brief convert any duration type to Hours
    /// @param[in] duration duration to convert
    /// @return duration in ratio Hours
    template <typename Rep, typename Period>
    Hours toHours(const std::chrono::duration<Rep, Period> &duration);

    /// @brief convert any duration type to Days
    /// @param[in] duration duration to convert
    /// @return duration in ratio Days
    template <typename Rep, typename Period>
    Days toDays(const std::chrono::duration<Rep, Period> &duration);

#pragma endregion

#pragma region time_t functions

    /// @brief Convert chrono time point to C-style time_t type
    /// @param[in] time_point time point to convert from
    /// @return time_t representation of input time_point
    time_t toCTime(const TimePoint& time_point);

    /// @brief Convert C-style time_t to chrono time point
    /// @param[in] time C-style time to convert from
    /// @return time_point representation of input time_t
    TimePoint fromCTime(const time_t& time);

    /// @brief Convert C-style time_t to std::tm structure as UTC format<br>
    /// see: http://en.cppreference.com/w/c/chrono/gmtime <br>
    /// @param[in] time C-style time to convert from
    /// @return tm structure of input time
    /// @see tmLocal, gmtFromTm
    std::tm tmGMT(const time_t& time);

    /// @brief Convert C-style time_t to std::tm structure as local time format<br>
    /// see: http://en.cppreference.com/w/c/chrono/localtime <br>
    /// @param[in] time C-style time to convert from
    /// @return tm structure of input time
    /// @see tmGMT, gmtFromTm
    std::tm tmLocal(const time_t& time);

    /// @brief Convert std::tm structure as UTC format to C-style time_t <br>
    /// see: https://msdn.microsoft.com/en-us/library/2093ets1.aspx <br>
    /// @param[in] tm std::tm structure to convert from
    /// @return C-style time
    /// @see tmGMT
    time_t gmtFromTm(const std::tm& tm);

    /// @brief Convert C-style UTC-time to local time format<br>
    /// @param[in] time C-style UTC-time to convert from
    /// @return C-style local time of input UTC-time
    /// @see tmLocal
    time_t toLocalTime(const time_t& time);

    /// @brief Convert C-style local time to UTC-time format<br>
    /// @param[in] time C-style local time to convert from
    /// @return C-style UTC-time of input local time
    /// @see tmGMT
    time_t toGMTTime(const time_t& time);

    /// @brief Retreive local timezone offset in seconds<br>
    /// see: http://en.cppreference.com/w/cpp/chrono/c/difftime <br>
    /// @return offset in seconds
    int offsetLocalTimezoneInSeconds();

#pragma endregion

#pragma region String formatting

    static constexpr auto default_format_time_point = "%Y-%m-%d %T"; // default format to conversion between time point and string

    /// @brief Convert string representation of input str_time to time point<br>
    /// to convertation using format with default locale <br>
    /// @param[in] str_time string representation of time to convert from
    /// @param[in] format specified the conversion format <br>
    /// using default locale <br>
    /// see: http://en.cppreference.com/w/cpp/io/manip/get_time <br>
    /// @return time point representation of input str_time
    /// @see stringFromTimePoint
    TimePoint timePointFromString(const std::string& str_time, const std::string& format);

    /// @brief Convert input time point to it's string representation by using conversion format
    /// @param[in] time_point time point to convert from
    /// @param[in] format specified the conversion format <br>
    /// using default locale for LC_TIME <br>
    /// see: http://en.cppreference.com/w/cpp/io/manip/put_time <br>
    /// see: http://en.cppreference.com/w/c/locale/LC_categories <br>
    /// @return string representation of input time point
    /// @see timePointFromString
    std::string stringFromTimePoint(const TimePoint& time_point, const std::string& format = default_format_time_point);

    /// @brief Convert string representation of input str_duration to duration<br>
    /// str_duration in format like: \<number\>\<suffix\> <br>
    /// Examples: <br>
    /// "2d" - 2 days <br>
    /// "54h" - 54 hours <br>
    /// "43m" - 43 minutes <br>
    /// "123", "123s" - 123 seconds <br>
    /// "1423ms" - 1423 milliseconds <br>
    /// doesn't allow multiple or negative parts <br>
    /// @param[in] str_duration string representation of duration to convert from
    /// @return duration representation of input str_duration or empty when error
    /// @see stringFromDuration
    Duration durationFromString(const std::string& str_duration);

    /// @brief Convert input duration to it's string representation<br>
    /// in format like: 184:23:34.453, 04:23:34.000, 12:03.453, 03.453
    /// @param[in] duration duration to convert from
    /// @return string representation of input duration
    /// @see durationFromString
    std::string stringFromDuration(const Duration& duration);

#pragma endregion

    // template implementation
#pragma region common clock functions implementation

    template <typename Rep, typename Period>
    bool isEmpty(const std::chrono::duration<Rep, Period>& duration)
    {
        return !duration.count();
    }

#pragma endregion

#pragma region convert durations implementation
    template <typename Rep, typename Period>
    Duration toDuration(const std::chrono::duration<Rep, Period> &duration)
    {
        return std::chrono::duration_cast<Duration>(duration);
    }

    template <typename Rep, typename Period>
    Nanoseconds toNanoseconds(const std::chrono::duration<Rep, Period> &duration)
    {
        return std::chrono::duration_cast<Nanoseconds>(duration);
    }

    template <typename Rep, typename Period>
    Microseconds toMicroseconds(const std::chrono::duration<Rep, Period> &duration)
    {
        return std::chrono::duration_cast<Microseconds>(duration);
    }

    template <typename Rep, typename Period>
    Milliseconds toMilliseconds(const std::chrono::duration<Rep, Period> &duration)
    {
        return std::chrono::duration_cast<Milliseconds>(duration);
    }

    template <typename Rep, typename Period>
    Seconds toSeconds(const std::chrono::duration<Rep, Period> &duration)
    {
        return std::chrono::duration_cast<Seconds>(duration);
    }

    template <typename Rep, typename Period>
    Minutes toMinutes(const std::chrono::duration<Rep, Period> &duration)
    {
        return std::chrono::duration_cast<Minutes>(duration);
    }

    template <typename Rep, typename Period>
    Hours toHours(const std::chrono::duration<Rep, Period> &duration)
    {
        return std::chrono::duration_cast<Hours>(duration);
    }

    template <typename Rep, typename Period>
    Days toDays(const std::chrono::duration<Rep, Period> &duration)
    {
        return std::chrono::duration_cast<Days>(duration);
    }

#pragma endregion

    /// @}
}
