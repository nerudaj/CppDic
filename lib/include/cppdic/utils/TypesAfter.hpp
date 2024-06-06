#pragma once

#include <tuple>

namespace dic
{
    namespace utils
    {
        template<size_t, class...>
        struct TypesAfter;

        template<size_t Index, class Head, class... Tail>
        struct TypesAfter<Index, Head, Tail...> : TypesAfter<Index - 1, Tail...>
        {
        };

        template<class Head, class... Tail>
        struct TypesAfter<0, Head, Tail...>
        {
            using Types = std::tuple<Tail...>;
        };
    } // namespace utils
} // namespace dic