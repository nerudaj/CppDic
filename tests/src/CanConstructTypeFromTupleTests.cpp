#include "CommonTypes.hpp"
#include <cppdic/utils/CanConstructTypeFromTuple.hpp>

static void CanConstructTypeFromTupleTests()
{
    static_assert(
        dic::utils::CanConstructTypeFromTuple<D, std::tuple<A, B, C>>::value);
    static_assert(
        !dic::utils::CanConstructTypeFromTuple<D, std::tuple<A, B>>::value);
    static_assert(
        !dic::utils::CanConstructTypeFromTuple<E, std::tuple<A, B, C>>::value);
}
