#include "CommonTypes.hpp"
#include <cppdic/utils/TypesBefore.hpp>

static void TypesBeforeTests()
{
    static_assert(std::is_same_v<
                  dic::utils::TypesBefore<0, A, B, C>::Types,
                  std::tuple<>>);
    static_assert(std::is_same_v<
                  dic::utils::TypesBefore<1, A, B, C>::Types,
                  std::tuple<A>>);
    static_assert(std::is_same_v<
                  dic::utils::TypesBefore<2, A, B, C>::Types,
                  std::tuple<A, B>>);
    static_assert(std::is_same_v<
                  dic::utils::TypesBefore<3, A, B, C>::Types,
                  std::tuple<A, B, C>>);
}
