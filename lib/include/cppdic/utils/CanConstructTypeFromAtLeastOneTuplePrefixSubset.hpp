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

            template<class Target, size_t PrefixLen, class Tuple>
            struct CanConstructTypeFromAtLeastOneTuplePrefixSubset
                : std::bool_constant<
                      CanConstructTypeFromTuple<
                          Target,
                          decltype(makeSubsetTuple(
                              Tuple {},
                              std::make_index_sequence<PrefixLen> {}))>::value
                      || CanConstructTypeFromAtLeastOneTuplePrefixSubset<
                          Target,
                          PrefixLen - 1,
                          Tuple>::value>
            {
            };

            template<class Target, class Tuple>
            struct CanConstructTypeFromAtLeastOneTuplePrefixSubset<
                Target,
                0,
                Tuple> : std::false_type
            {
            };
        } // namespace detail

        template<class Target, class Tuple>
        struct CanConstructTypeFromAtLeastOneTuplePrefixSubset
            : std::bool_constant<
                  detail::CanConstructTypeFromAtLeastOneTuplePrefixSubset<
                      Target,
                      std::tuple_size_v<Tuple>,
                      Tuple>::value>
        {
        };
    } // namespace utils
} // namespace dic
