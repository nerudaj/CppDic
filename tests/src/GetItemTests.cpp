#include "CommonTypes.hpp"
#include <cppdic/utils/GetIndex.hpp>

static void GetItemTests()
{
    using dic::Service;

    static_assert(
        dic::utils::getIndex<A, Service<A>, Service<B>, Service<C>>(0) == 0);
    static_assert(
        dic::utils::getIndex<B, Service<A>, Service<B>, Service<C>>(0) == 1);
    static_assert(
        dic::utils::getIndex<C, Service<A>, Service<B>, Service<C>>(0) == 2);
    static_assert(
        dic::utils::getIndex<D, Service<A>, Service<B>, Service<C>>(0) == 3);
}