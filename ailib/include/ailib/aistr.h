#pragma once

#include <algorithm>
#include <cstring> // strnlen_s
#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <cctype>
#include "aialgorithm.h"

/// @defgroup aistr aistr
/// Helpers to work with strings

namespace ai
{
    /// @addtogroup aistr
    /// @{

#pragma region Static: Compile time functions

    /// @brief Calculate length of static string at compile time
    /// @param[in] str static defined string
    /// @return the length of the null-terminated string str
    static constexpr std::size_t lengthConst(const char* str) {
        return (*str == 0) ? 0 : lengthConst(str + 1) + 1;
    }

#pragma endregion

#pragma region Static: Check helpers

    /// @brief Check input pointer is not null
    /// @param[in] str pointer to the null-terminated byte string to be examined
    /// @throw throws std::invalid_argument if str is null
    void checkPointerNotNull(const char* str);

#pragma endregion

#pragma region Static: capacity

    /// @brief Calculate length of null-terminated string str
    /// @param[in] str null-terminated string
    /// @param[in] max_length maximum number of characters to examine
    /// @return The length of the null-terminated string on success. max_length if the null character was not found.
    /// @throw throws std::invalid_argument if str is null
    std::size_t length(const char* str, const size_t max_length);

    /// @brief Calculate length of static char array str
    /// @param[in] str static char array
    /// @return The length of the static char array.
    /// @throw throws std::out_of_range if str length greather or equal N, i.e. if last char is not null.
    template<std::size_t N>
    std::size_t length(const char(&str)[N]);

#pragma endregion

#pragma region Static: assign

    /// @brief Replaces the contents of the static array lhs with a copy of rhs.
    /// @tparam N size of static char array
    /// @param[in] lhs static char array
    /// @param[in] rhs pointer to a character string to use as source to initialize the string with
    /// @throw throws std::invalid_argument if rhs is null
    template<std::size_t N>
    void assign(char(&lhs)[N], const char* rhs);

#pragma endregion

#pragma region Static: operations

    /// @brief Compare static array with rhs. The comparison is done lexicographically.
    /// @tparam N size of static char array
    /// @param[in] lhs static char array
    /// @param[in] rhs pointer to the null-terminated byte string to compare
    /// @return return same result as strncmp
    /// @throw throws std::invalid_argument if rhs is null
    template<std::size_t N>
    static int compare(const char(&lhs)[N], const char* rhs);

    /// @brief Appends additional characters to the the static array lhs with a copy of rhs.
    /// @tparam N size of static char array
    /// @param[in] lhs static char array
    /// @param[in] rhs pointer to a character string to use as source to initialize the string with
    /// @throw throws std::invalid_argument if rhs is null
    template<std::size_t N>
    void append(char(&lhs)[N], const char* rhs);

#pragma endregion

    /// @}

#pragma region Static: templates implementation

    template<std::size_t N>
    std::size_t length(const char(&str)[N])
    {
        const size_t max_length = countOf(str);
        auto result = ai::length(str, max_length);
        if (result == max_length)
        {
            throw std::out_of_range("char array doesn't have null-terminated character at position " + std::to_string(N));
        }
        return result;
    }

    template<std::size_t N>
    void assign(char(&lhs)[N], const char* rhs) {
        checkPointerNotNull(rhs);
        const size_t allow_to_copy = countOf(lhs) - 1;
        const size_t src_len = ai::length(rhs, allow_to_copy);
        const size_t bytes_to_copy = std::min(allow_to_copy, src_len) * sizeof(char);

        // use memmove to allow overflow buffers
        std::memmove(lhs, rhs, bytes_to_copy);

        lhs[bytes_to_copy] = '\0'; // ensure last byte is zero
    }

    template<std::size_t N>
    static int compare(const char(&lhs)[N], const char* rhs) {
        checkPointerNotNull(rhs);
        return std::strncmp(lhs, rhs, countOf(lhs));
    }

    template<std::size_t N>
    void append(char(&lhs)[N], const char* rhs) {
        checkPointerNotNull(rhs);
        const size_t allow_to_copy = countOf(lhs) - 1;
        const size_t src_len = ai::length(rhs, allow_to_copy);
        if (!src_len) { return; }

        const size_t origin_len = ai::length(lhs, allow_to_copy);
        const size_t copy_chars = std::min(allow_to_copy - origin_len, src_len);
        char* dest = lhs + origin_len;
        const size_t copy_bytes = copy_chars * sizeof(char);

        // use memmove to allow overflow buffers
        std::memmove(dest, rhs, copy_bytes);
        *(dest + copy_chars) = '\0'; // ensure last byte is zero
    }

#pragma endregion

}

