#pragma once

#include <algorithm>
#include <vector>
#include <cstring> // std::memset

/// @defgroup aialgorithm aialgorithm
/// Helpers and extentions to implement algorithms

namespace ai
{
    /// @addtogroup aialgorithm
    /// @{

#pragma region Static: Compile time functions

    // ReSharper disable once CppParameterNeverUsed
    /// @brief Calculate count elements in static array at compile time
    /// @tparam T type of static array element
    /// @tparam N size of static array
    /// @param[in] str static array
    /// @return count of elements
#pragma warning(push)
#pragma warning(disable:4100) // disable 'str': unreferenced formal parameter. the name require for documentation.
    template<typename T, std::size_t N>
    static constexpr std::size_t countOf(T(&str)[N])
    {
        return N;
    }
#pragma warning(pop)

#pragma endregion

#pragma region Static: assign

    /// @brief Assigns the given value to all elements in destination buffer
    /// @tparam T type of static array element
    /// @tparam N size of static array
    /// @param[in] dest static array
    /// @param[in] value the object to be assigned
    /// @see [std::fill_n](http://en.cppreference.com/w/cpp/algorithm/fill_n)
    template<typename T, std::size_t N>
    void fill(T(&dest)[N], const T& value);

    /// @brief Fill destination buffer with zero bytes using std::memset <br>
    /// To avoid security issues consider SecureZeroMemory and others. <br>
    /// See [std::memset\#Notes](http://en.cppreference.com/w/cpp/string/byte/memset#Notes).
    /// @tparam T type of static array element. Must be trivially-copyable.
    /// @tparam N size of static char array
    /// @param[in] dest static char array
    /// @see ai::fill, [std::memset](http://en.cppreference.com/w/cpp/string/byte/memset)
    template<typename T, std::size_t N>
    void fillZero(T(&dest)[N]);

#pragma endregion

    /// @}

#pragma region Static: templates implementation

    template<typename T, std::size_t N>
    void fill(T(&dest)[N], const T& value)
    {
        std::fill_n(dest, countOf(dest), value);
    }

    template<typename T, std::size_t N>
    void fillZero(T(&dest)[N])
    {
        static_assert(std::is_trivially_copyable<T>::value, "The object must be trivially copyable to using in std::memset");
        std::memset(&dest, 0, sizeof(T) * ai::countOf(dest));
    }

    // specialization for char array
    template<std::size_t N>
    void fillZero(char(&dest)[N]) {
        ai::fill(dest, '\0');
    }

#pragma endregion

#pragma region Containers

    /// @brief Extract keys from associative container(std::map etc.) to std::vector
    /// See: https://en.cppreference.com/w/cpp/named_req/AssociativeContainer
    /// @param[in] map associative container
    template<typename Map>
    std::vector<typename Map::key_type> extractKeys(const Map& map)
    {
        static_assert(std::is_same<typename Map::mapped_type, typename Map::value_type::second_type>::value,
            "map must provide AssociativeContainer requirements. see: https://en.cppreference.com/w/cpp/named_req/AssociativeContainer");

        std::vector<typename Map::key_type> result;
        result.reserve(map.size());
        for(const auto& it : map)
        {
            result.push_back(it.first);
        }
        return result;
    }

#pragma endregion

}

