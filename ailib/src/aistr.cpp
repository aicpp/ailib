// 2017-11-14
// aicpp

#include <ailib/aistr.h>

namespace ai
{
    void checkPointerNotNull(const char* str)
    {
        if (!str) { throw std::invalid_argument("pointer to null-terminated string is null"); }
    }

    std::size_t length(const char* str, const size_t max_length)
    {
        checkPointerNotNull(str);
#ifdef _MSC_VER
        return strnlen_s(str, max_length);
#else
        return strnlen(str, max_length);
#endif
    }
}
