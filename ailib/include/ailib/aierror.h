#pragma once
#include <string>
#include <cerrno>

#ifdef _WIN32
#include <windows.h> // GetLastError
#endif


/// @defgroup aierror aierror
/// Helpers to work with standart system errors

namespace ai
{
/// @addtogroup aierror
/// @{

    /// @brief Format any error code and it's error description as "Error: <error_code> - <error_descr>"
    /// @param[in] error_code some error code
    /// @param[in] error_descr string representation of error_code
    /// @return format string representation of input arguments
    std::string formatError(const int error_code, const std::string& error_descr);

    /// @brief Get string description from current error number.<br>
    /// String representation depends from current locale. <br>
    /// See: http://en.cppreference.com/w/cpp/error/errno <br>
    /// See: https://msdn.microsoft.com/en-us/library/51sah927.aspx <br>
    /// @param[in] error_code error code, by default errno macros
    /// @return string representation of input error code
    /// @see formatErrno
    std::string stringFromErrno(const int error_code = errno);

    /// @brief Format errno using formatError
    /// @param[in] error_code error code, by default errno macros
    /// @return format string representation of errno
    /// @see stringFromErrno, formatError
    std::string formatErrno(const int error_code = errno);

#ifdef _WIN32
    /// @brief Get string description from Windows last error(function GetLastError)
    /// @param[in] error_code error code, by default GetLastError
    /// @return string representation of GetLastError
    /// @see formatLastError
    std::string stringFromLastError(const int error_code = ::GetLastError());

    /// @brief Format GetLastError using formatError
    /// @param[in] error_code error code, by default GetLastError
    /// @return format string representation of GetLastError
    /// @see stringFromLastError, formatError
    std::string formatLastError(const int error_code = ::GetLastError());
#endif

/// @}
}
