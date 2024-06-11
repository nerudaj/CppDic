#pragma once

#include "cppdic/utils/CanConstructTypeFromAtLeastOneTuplePrefixSubset.hpp"
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
            {
                using _Recurse = CanConstructTypeFromAListOfTuples<T, Tail...>;
                using _Detail = ::dic::utils::
                    CanConstructTypeFromAtLeastOneTuplePrefixSubset<T, Head>;
                constexpr static bool value = _Detail::value || _Recurse::value;
                using Tuple = std::conditional_t<
                    _Detail::value,
                    typename _Detail::Tuple,
                    typename _Recurse::Tuple>;
            };

            template<class T, class U>
            struct CanConstructTypeFromAListOfTuples<T, U>
            {
                using _Detail = ::dic::utils::
                    CanConstructTypeFromAtLeastOneTuplePrefixSubset<T, U>;
                constexpr static bool value = _Detail::value;
                using Tuple = std::conditional_t<
                    _Detail::value,
                    typename _Detail::Tuple,
                    std::tuple<>>;
            };
        } // namespace detail

        template<class, class>
        struct CanConstructTypeFromAListOfTuples;

        template<class T, class... Us>
        struct CanConstructTypeFromAListOfTuples<T, std::tuple<Us...>>
        {
            using _Detail = detail::CanConstructTypeFromAListOfTuples<T, Us...>;
            constexpr static bool value = _Detail::value;
            using Tuple = _Detail::Tuple;
        };
    } // namespace utils
} // namespace dic
