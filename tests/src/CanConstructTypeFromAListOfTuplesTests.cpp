#include "CommonTypes.hpp"
#include <cppdic/utils/CanConstructTypeFromAListOfTuples.hpp>
#include <cppdic/utils/Permutations.hpp>

static void CanConstructTypeFromAListOfTuplesTests()
{
    static_assert(
        std::is_same_v<
            dic::utils::detail::
                CanConstructTypeFromAListOfTuples<E, std::tuple<A, B>>::Tuple,
            std::tuple<A, B>>);

    static_assert(std::is_same_v<
                  dic::utils::detail::CanConstructTypeFromAListOfTuples<
                      E,
                      std::tuple<A, B>,
                      std::tuple<B, A>>::Tuple,
                  std::tuple<A, B>>);

    static_assert(
        std::is_same_v<
            dic::utils::CanConstructTypeFromAListOfTuples<
                E,
                dic::utils::Permutations<std::tuple<A, B, C>>::Types>::Tuple,
            std::tuple<A, B>>);
}