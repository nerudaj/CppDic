#pragma once

#include "cppdic/utils/CanConstructTypeFromTuple.hpp"
#include <tuple>
#include <type_traits>

namespace dic
{
    namespace utils
    {
        namespace detail
        {
            template<class, class...>
            struct CanConstructTypeFromAListOfTuples;

            template<class T, class Head, class... Tail>
            struct CanConstructTypeFromAListOfTuples<T, Head, Tail...>
                : std::bool_constant<
                      CanConstructTypeFromTuple<T, Head>::value
                      || CanConstructTypeFromAListOfTuples<T, Tail...>::value>
            {
            };

            template<class T, class U>
            struct CanConstructTypeFromAListOfTuples<T, U>
                : std::bool_constant<CanConstructTypeFromTuple<T, U>::value>
            {
            };
        } // namespace detail

        template<class, class>
        struct CanConstructTypeFromAListOfTuples;

        template<class T, class... Us>
        struct CanConstructTypeFromAListOfTuples<T, std::tuple<Us...>>
            : std::bool_constant<
                  detail::CanConstructTypeFromAListOfTuples<T, Us...>::value>
        {
        };
    } // namespace utils
} // namespace dic
