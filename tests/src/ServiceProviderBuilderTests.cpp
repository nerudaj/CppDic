#include "CommonTypes.hpp"
#include <cppdic/ServiceProviderBuilder.hpp>

static void ServiceProviderBuilderTests_IsConstructible()
{
    constexpr auto builder = dic::ServiceProviderBuilder();
}

static void ServiceProviderBuilderTests_CanAddNewConcreteDependency()
{
    auto builder =
        dic::ServiceProviderBuilder().addService<A>().addService<B>();
}

static void ServiceProviderBuilderTests_CanAddNewInterfaceDependency()
{
    auto builder = dic::ServiceProviderBuilder().addService<I, Ia>();
}

static void ServiceProviderBuilderTests_CanOverwriteExistingConcreteDependency()
{
    auto builder =
        dic::ServiceProviderBuilder().addService<I, Ia>().addService<I, Ib>();
}