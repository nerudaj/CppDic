#pragma once

#include "cppdic/utils/CanConstructTypeFromAtLeastOnePrefixSubset.hpp"
#include "cppdic/utils/GetIndex.hpp"
#include "cppdic/utils/Permutations.hpp"
#include "cppdic/utils/TypesAfter.hpp"
#include "cppdic/utils/TypesBefore.hpp"

namespace dic
{
    namespace utils
    {

        template<class, class>
        struct CanConstructFromTuple;

        template<class T, class... Us>
        struct CanConstructFromTuple<T, std::tuple<Us...>>
            //: std::bool_constant<std::constructible_from<T, Us...>>
            : std::bool_constant<CanConstructTypeFromAtLeastOnePrefixSubset<
                  T,
                  sizeof...(Us),
                  Us...>::value>
        {
        };

        // Rule no1 of recursion
        template<class, class...>
        struct CanConstructFromAListOfTuples;

        template<class T, class Head, class... Tail>
        struct CanConstructFromAListOfTuples<T, Head, Tail...>
            : std::bool_constant<
                  CanConstructFromTuple<T, Head>::value
                  || CanConstructFromAListOfTuples<T, Tail...>::value>
        {
        };

        template<class T, class U>
        struct CanConstructFromAListOfTuples<T, U>
            : std::bool_constant<CanConstructFromTuple<T, U>::value>
        {
        };

        template<class, class>
        struct TopLevelUnpack;

        template<class T, class... Us>
        struct TopLevelUnpack<T, std::tuple<Us...>>
            : std::bool_constant<CanConstructFromAListOfTuples<T, Us...>::value>
        {
        };
    } // namespace utils
} // namespace dic