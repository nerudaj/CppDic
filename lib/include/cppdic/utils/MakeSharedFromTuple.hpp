#pragma once

#include <concepts>
#include <tuple>

namespace dic
{
    namespace utils
    {
        template<class Target, class... Ts>
        auto makeSharedFromTuple(const std::tuple<Ts...>& tuple)
        {
            static_assert(
                std::constructible_from<Target, Ts...>,
                "Cannot construct type from given tuple");
            return std::apply(
                [](const Ts&... args)
                { return std::make_shared<Target>(args...); },
                tuple);
        }
    } // namespace utils
} // namespace dic