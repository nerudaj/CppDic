#include "CommonTypes.hpp"
#include <cppdic/utils/Permutations.hpp>
#include <tuple>

static void PermutationsTests()
{
    static_assert(std::is_same_v<
                  dic::utils::Permutations<std::tuple<A, B, C>>::Types,
                  std::tuple<
                      std::tuple<A, B, C>,
                      std::tuple<A, C, B>,
                      std::tuple<B, C, A>,
                      std::tuple<B, A, C>,
                      std::tuple<C, A, B>,
                      std::tuple<C, B, A>>>);

    // Unlike std::next_permutation this produces all permutations
    // disregarding of initial order
    static_assert(std::is_same_v<
                  dic::utils::Permutations<std::tuple<C, B, A>>::Types,
                  std::tuple<
                      std::tuple<C, B, A>,
                      std::tuple<C, A, B>,
                      std::tuple<B, A, C>,
                      std::tuple<B, C, A>,
                      std::tuple<A, C, B>,
                      std::tuple<A, B, C>>>);
}