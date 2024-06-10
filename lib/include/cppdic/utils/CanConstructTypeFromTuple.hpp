#pragma once

#include <tuple>
#include <type_traits>

namespace dic
{
    namespace utils
    {
        template<class, class>
        struct CanConstructTypeFromTuple;

        template<class T, class... Us>
        struct CanConstructTypeFromTuple<T, std::tuple<Us...>>
            : std::bool_constant<std::constructible_from<T, Us...>>
        {
        };
    } // namespace utils
} // namespace dic
