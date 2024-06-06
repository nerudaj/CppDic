#pragma once

#include <concepts>
#include <type_traits>

namespace dic
{
    namespace utils
    {
        template<class, size_t, class...>
        struct CanConstructTypeFromAtLeastOnePrefixSubset;

        template<class T, size_t Idx, class Head, class... Tail>
        struct CanConstructTypeFromAtLeastOnePrefixSubset<T, Idx, Head, Tail...>
            : std::bool_constant<
                  std::constructible_from<T, Head, Tail...>
                  || CanConstructTypeFromAtLeastOnePrefixSubset<T, Idx - 1, Tail...>::
                      value>
        {
        };

        template<class T, class U>
        struct CanConstructTypeFromAtLeastOnePrefixSubset<T, 1, U>
            : std::bool_constant<std::constructible_from<T, U>>
        {
        };
    }
}
