// 2018-06-01
// aicpp

#include <ailib/aichrono.h>
#include <cassert>
#include <iomanip>
#include <sstream>
#include <locale>
#include <algorithm>
#include <tuple>

namespace ai
{

#pragma region common clock functions

    bool isEmpty(const TimePoint& time_point)
    {
        return isEmpty(time_point.time_since_epoch());
    }

    bool isEmpty(const SteadyTimePoint& time_point)
    {
        return isEmpty(time_point.time_since_epoch());
    }
    
#pragma endregion

#pragma region time_t functions

    time_t toCTime(const TimePoint& time_point)
    {
#ifdef _USE_32BIT_TIME_T
        return static_cast<__time32_t>(Clock::to_time_t(time_point));
#else
        return Clock::to_time_t(time_point);
#endif
    }

    TimePoint fromCTime(const time_t& time)
    {
        return Clock::from_time_t(time);
    }

    std::tm tmGMT(const time_t& time)
    {
        std::tm result = { 0 };
#ifdef defined(_MSC_VER)
        const auto err = gmtime_s(&result, &time);
        if (err) { throw std::runtime_error("Invalid argument of gmtime_s. Error: " + std::to_string(err)); }
#elif defined(linux)
        if (!gmtime_r(&time, &result)) { throw std::runtime_error("Invalid argument of gmtime_r. Error: " + std::to_string(errno)); }
#endif
        return result;
    }

    std::tm tmLocal(const time_t& time) 
    {
        std::tm result = { 0 };
#if defined(_MSC_VER)
        const auto err = localtime_s(&result, &time);
        if (err) { throw std::runtime_error("Invalid argument of localtime_s. Error: " + std::to_string(err)); }
#elif defined(linux)
        if (!localtime_r(&time, &result)) { throw std::runtime_error("Invalid argument of localtime_r. Error: " + std::to_string(errno)); }
#endif
        return result;
    }

    time_t gmtFromTm(const std::tm& tm) 
    {
        std::tm tm_put = tm;
        time_t result = -1;
#if defined(_MSC_VER)
        result = _mkgmtime(&tm_put);
        if (result == -1) { throw std::runtime_error("Invalid argument of _mkgmtime"); }
#elif defined(linux)
        result = timegm(&tmPut);
        if (result == -1) { throw std::runtime_error("Invalid argument of timegm. Error: " + std::to_string(errno)); }
#endif
        return result;
    }

    time_t toLocalTime(const time_t& time)
    {
        struct tm loc = ai::tmLocal(time);
        return mktime(&loc);
    }

    time_t toGMTTime(const time_t& time)
    {
        struct tm gm = ai::tmGMT(time);
        return mktime(&gm);
    }

    int offsetLocalTimezoneInSeconds()
    {
        const time_t now = time(nullptr);
        return static_cast<int>(difftime(toLocalTime(now), toGMTTime(now)));
    }

#pragma endregion


#pragma region String formatting

    // formatting
    // format specification: http://en.cppreference.com/w/cpp/io/manip/get_time
    TimePoint timePointFromString(const std::string& str_time, const std::string& format)
    {
#ifdef _MSC_VER
        // MSVC doesn't implement format params without separators
        // see: https://connect.microsoft.com/VisualStudio/Feedback/Details/2290315
        static std::string invalid_parts[] = { "%Y%m", "%m%d", "%d%H", "%d%T", "%H%M", "%M%S" };
        for (const auto& part : invalid_parts)
        {
            if (format.find(part) != std::string::npos)
            {
                throw std::runtime_error("Convert string to time failed. Invalid format part (for MSVC): " + part + ".");
            }
        }
#endif
        std::tm tm = {};
        std::istringstream ss(str_time);
        ss >> std::get_time(&tm, format.c_str());
        if (ss.fail()) {
            throw std::runtime_error("Convert string to time failed.");
        }
        return fromCTime(gmtFromTm(tm));
    }

    std::string stringFromTimePoint(const TimePoint& time_point, const std::string& format)
    {
        struct tm gm = tmGMT(toCTime(time_point));

        std::ostringstream ss;
        ss << std::put_time(&gm, format.c_str());
        if (ss.fail()) {
            throw std::runtime_error("Convert time point to string failed.");
        }
        return ss.str();
    }

    namespace
    {
        using StrRange = std::pair<std::string::size_type, std::string::size_type>;
        static const StrRange invalid_range = std::make_pair( std::string::npos, std::string::npos );

        bool isInvalidRange(const StrRange& range)
        {
            return range.first == invalid_range.first ||
                (range.second != std::string::npos && range.first > range.second);
        }

        StrRange findNumber(const std::string& input_string)
        {
            constexpr auto num_chars = "0123456789";
            const auto it_beg_num = input_string.find_first_of(num_chars);
            const auto it_end_num = input_string.find_first_not_of(num_chars, it_beg_num);
            if (it_beg_num != std::string::npos)
            {
                const auto it_end = (it_end_num != std::string::npos) ? it_end_num : input_string.length();
                return StrRange{ it_beg_num, it_end };
            }
            return invalid_range;
        }

        bool isSpaceString(const std::string& input_string)
        {
            return std::all_of(input_string.begin(), input_string.end(), ::isspace);
        }

        size_t numberWithSuffix(const std::string& input_string, const std::string &suffix)
        {
            constexpr auto max_length = 50U;
            constexpr auto result_default = 0U;

            if (suffix.empty()) { return result_default; }
            if (input_string.length() <= suffix.length()) { return result_default; }
            if (input_string.length() > max_length) { return result_default; }

            const auto it_suffix = input_string.rfind(suffix);
            if (it_suffix != std::string::npos) {
                // has suffix
                const auto num_range = findNumber(input_string);
                if (!isInvalidRange(num_range) && num_range.second == it_suffix)
                {
                    // check rest range
                    if (isSpaceString(input_string.substr(0, num_range.first)) &&
                        isSpaceString(input_string.substr(it_suffix + suffix.length())) )
                    {
                        return std::stoi(input_string.substr(num_range.first, num_range.second - num_range.first));
                    }
                }
            }
            return result_default;
        }

        void outputPaddingNumber(std::ostream& os, const uint64_t& value, const size_t padding = 2)
        {
            os << std::setw(padding) << std::setfill('0') << value;
        }
    }

    Duration durationFromString(const std::string& str_duration)
    {
        static std::pair<std::string, Duration> ratios[] = {
            std::make_pair("ms", millisecond),
            std::make_pair("s", second),
            std::make_pair("m", minute),
            std::make_pair("h", hour),
            std::make_pair("d", day),
        };
        for (const auto& ratio : ratios)
        {
            const auto value = numberWithSuffix(str_duration, ratio.first);
            if (value)
            {
                return ratio.second * value;
            }
        }

        // without suffix - mean it's seconds
        const auto num_range = findNumber(str_duration);
        if (!isInvalidRange(num_range))
        {
            // check rest range
            if (isSpaceString(str_duration.substr(0, num_range.first)) &&
                isSpaceString(str_duration.substr(num_range.second)))
            {

                return second * stoi(str_duration.substr(num_range.first, num_range.second - num_range.first));
            }
        }

        return{};
    }

    std::string stringFromDuration(const Duration& duration)
    {
        std::stringstream os;
        std::string prefix;
        auto rest_duration = duration;
        if (duration < Duration{}) { // if negative print lead sign
            prefix = "-";
            rest_duration = -rest_duration;
        }


        // HH
        {
            constexpr auto denom = hour;
            const auto show_duration = rest_duration / denom;
            rest_duration %= denom;
            if (show_duration) {
                outputPaddingNumber(os, show_duration);
                os << ":";
            }
        }

        // MM
        {
            constexpr auto denom = minute;
            const auto show_duration = rest_duration / denom;
            rest_duration %= denom;
            if (!os.str().empty() || show_duration) {
                outputPaddingNumber(os, show_duration);
                os << ":";
            }
        }

        // SS
        {
            constexpr auto denom = second;
            const auto show_duration = rest_duration / denom;
            rest_duration %= denom;
            outputPaddingNumber(os, show_duration);
            os << ".";
        }

        // milliseconds
        {
            constexpr auto denom = millisecond;
            const auto show_duration = rest_duration / denom;
            outputPaddingNumber(os, show_duration, 3);
        }

        return prefix + os.str();
    }

#pragma endregion

}
