#include "CommonTypes.hpp"
#include <cppdic/utils/CanConstructTypeFromAtLeastOneTuplePrefixSubset.hpp>

static void CanConstructTypeFromAtLeastOneTuplePrefixSubsetTests()
{
    static_assert(dic::utils::CanConstructTypeFromAtLeastOneTuplePrefixSubset<
                  D,
                  std::tuple<A, B, C>>::value);
    static_assert(dic::utils::CanConstructTypeFromAtLeastOneTuplePrefixSubset<
                  E,
                  std::tuple<A, B, C, D>>::value);
    static_assert(!dic::utils::CanConstructTypeFromAtLeastOneTuplePrefixSubset<
                  E,
                  std::tuple<B, A, C, D>>::value); // swapped A-B
}