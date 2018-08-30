#include <ailib/aierror.h>
#include <cstring> // strerror_s
#include <string>


namespace ai
{
    std::string formatError(const int error_code, const std::string& error_descr)
    {
        return std::string("Error: " + std::to_string(error_code) + " - " + error_descr);
    }

    std::string stringFromErrno(const int error_code)
    {
        char buf_err[100] = {0};
        const auto buf_len = std::extent<decltype(buf_err)>::value;
#ifdef _MSC_VER
        if (!strerror_s(buf_err, buf_len, error_code))
        {
            return buf_err;
        }
#else
        if (!strerror_r(error_code, buf_err, buf_len))
        {
            return buf_err;
        }
#endif        
        return "!formatting errno failed!";
    }

    std::string formatErrno(const int error_code)
    {
        return ai::formatError(error_code, ai::stringFromErrno(error_code));
    }

#ifdef _WIN32
    std::string stringFromLastError(const int error_code)
    {
        LPSTR message_buffer = nullptr;
        const size_t size = ::FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            error_code,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPSTR>(&message_buffer),
            0,
            nullptr);

        std::string message(message_buffer, size);
        ::LocalFree(message_buffer);
        return message;
    }

    std::string formatLastError(const int error_code)
    {
        return ai::formatError(error_code, ai::stringFromLastError(error_code));
    }

#endif

}
