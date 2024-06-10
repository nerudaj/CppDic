#include "CommonTypes.hpp"
#include <cppdic/utils/TypesAfter.hpp>

static void TypesAfterTests()
{
    static_assert(std::is_same_v<
                  dic::utils::TypesAfter<0, A, B, C>::Types,
                  std::tuple<B, C>>);
    static_assert(std::is_same_v<
                  dic::utils::TypesAfter<1, A, B, C>::Types,
                  std::tuple<C>>);
    static_assert(
        std::
            is_same_v<dic::utils::TypesAfter<2, A, B, C>::Types, std::tuple<>>);
}