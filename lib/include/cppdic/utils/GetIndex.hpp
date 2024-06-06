#pragma once

#include <concepts>

namespace dic
{
    namespace utils
    {
        template<class T>
        static consteval std::size_t getIndex(std::size_t index)
        {
            return index;
        }

        template<class T, class FirstT, class... RemainingTs>
        static consteval std::size_t getIndex(std::size_t index)
        {
            using Base = FirstT::BaseType;
            if constexpr (std::is_same_v<T, Base>) return index;
            return getIndex<T, RemainingTs...>(index + 1);
        }
    } // namespace utils
} // namespace dic
