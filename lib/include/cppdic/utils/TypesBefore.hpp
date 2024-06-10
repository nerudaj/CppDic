#pragma once

#include <tuple>
#include <utility>

namespace dic
{
    namespace utils
    {
        template<class T, size_t... I>
        auto makeSubsetTuple(const T& t, std::index_sequence<I...>)
        {
            return std::make_tuple(std::get<I>(t)...);
        }

        template<size_t Index, class... Ts>
        struct TypesBefore
        {
            using Types = decltype(makeSubsetTuple(
                std::tuple<Ts...> {}, std::make_index_sequence<Index> {}));
        };
    } // namespace utils
} // namespace dic
