#pragma once

#include "cppdic/utils/Permutations.hpp"
#include "cppdic/utils/TypesAfter.hpp"
#include <tuple>
#include <utility>

namespace dic
{
    namespace utils
    {
        template<std::size_t, class...>
        struct TypesBefore;

        template<std::size_t N, class T, class... Ts>
        struct TypesBefore<N, T, Ts...>
        {
            using Types = detail::merge<
                std::tuple<T>,
                typename TypesBefore<N - 1, Ts...>::Types>::type;
        };

        // TODO: is this overload required?
        template<class Head, class... Tail>
        struct TypesBefore<0, Head, Tail...>
        {
            using Types = std::tuple<>;
        };

        template<>
        struct TypesBefore<0>
        {
            using Types = std::tuple<>;
        };

        template<size_t, class>
        struct TypesBeforeTupleAdapter;

        template<size_t Index, class... Ts>
        struct TypesBeforeTupleAdapter<Index, std::tuple<Ts...>>
        {
            using Types = TypesBefore<Index, Ts...>::Types;
        };
    } // namespace utils
} // namespace dic
