#pragma once

#include "cppdic/utils/CanConstructTypeFromTuple.hpp"
#include "cppdic/utils/TypesBefore.hpp"
#include <concepts>
#include <type_traits>

namespace dic
{
    namespace utils
    {
        namespace detail
        {
            template<class Target, size_t, class>
            struct CanConstructTypeFromAtLeastOneTuplePrefixSubset;

            template<class Target, size_t PrefixLen, class _Tuple>
            struct CanConstructTypeFromAtLeastOneTuplePrefixSubset
            {
                using _Subset =
                    TypesBeforeTupleAdapter<PrefixLen, _Tuple>::Types;
                using _Detail =
                    CanConstructTypeFromTuple<Target, typename _Subset>;
                using _Recurse =
                    CanConstructTypeFromAtLeastOneTuplePrefixSubset<
                        Target,
                        PrefixLen - 1,
                        _Tuple>;
                constexpr static bool value = _Detail::value || _Recurse::value;
                using Tuple = std::conditional_t<
                    _Detail::value,
                    typename _Subset,
                    typename _Recurse::Tuple>;
            };

            template<class Target, class _Tuple>
            struct CanConstructTypeFromAtLeastOneTuplePrefixSubset<
                Target,
                0,
                _Tuple>
            {
                constexpr static bool value = false;
                using Tuple = std::tuple<>;
            };
        } // namespace detail

        template<class Target, class _Tuple>
        struct CanConstructTypeFromAtLeastOneTuplePrefixSubset
        {
            using _Detail =
                detail::CanConstructTypeFromAtLeastOneTuplePrefixSubset<
                    Target,
                    std::tuple_size_v<_Tuple>,
                    _Tuple>;
            constexpr static bool value = _Detail::value;
            using Tuple = _Detail::Tuple;
        };
    } // namespace utils
} // namespace dic
