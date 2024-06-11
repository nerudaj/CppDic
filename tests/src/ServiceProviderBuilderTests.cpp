#include "CommonTypes.hpp"
#include <cppdic/ServiceProviderBuilder.hpp>

static void ServiceProviderBuilderTests_IsConstructible()
{
    constexpr auto builder = dic::ServiceProviderBuilder();
}

static void ServiceProviderBuilderTests_CanAddNewConcreteDependency()
{
    static_assert(
        std::is_same_v<
            decltype(dic::ServiceProviderBuilder()
                         .addService<A>()
                         .addService<B>()),
            dic::ServiceProviderBuilder<dic::Service<A>, dic::Service<B>>>);
}

static void ServiceProviderBuilderTests_CanAddNewInterfaceDependency()
{
    static_assert(std::is_same_v<
                  decltype(dic::ServiceProviderBuilder().addService<I, Ia>()),
                  dic::ServiceProviderBuilder<dic::Service<I, Ia>>>);
}

static void ServiceProviderBuilderTests_CanOverwriteExistingConcreteDependency()
{
    static_assert(std::is_same_v<
                  decltype(dic::ServiceProviderBuilder()
                               .addService<I, Ia>()
                               .addService<I, Ib>()),
                  dic::ServiceProviderBuilder<dic::Service<I, Ib>>>);
}

static void ServiceProviderBuilderTests_ChecksIfConcreteObjectCanBeConstructed()
{
    static_assert(std::is_same_v<
                  decltype(dic::ServiceProviderBuilder()
                               .addService<A>()
                               .addService<B>()
                               .addService<Eshared>()),
                  dic::ServiceProviderBuilder<
                      dic::Service<A>,
                      dic::Service<B>,
                      dic::Service<Eshared>>>);
}

static void ServiceProviderBuilderTests_ChecksIfInterfaceImplCanBeConstructed()
{
    static_assert(std::is_same_v<
                  decltype(dic::ServiceProviderBuilder()
                               .addService<A>()
                               .addService<I, IEshared>()),
                  dic::ServiceProviderBuilder<
                      dic::Service<A>,
                      dic::Service<I, IEshared>>>);
}

static void
ServiceProviderBuilderTests_CanReplaceInterfaceWithPreparedImplementation()
{
    auto&& bshared = std::make_shared<Ib>();
    static_assert(std::is_same_v<
                  decltype(dic::ServiceProviderBuilder()
                               .addService<I, Ia>()
                               .addService<I>(bshared)),
                  dic::ServiceProviderBuilder<dic::Service<I, I>>>);
}

/*
static void ServiceProviderBuilderTests_CanBuildProvider()
{
    auto provider = dic::ServiceProviderBuilder()
                        .addService<A>()
                        .addService<I, Ia>()
                        .build();
}*/