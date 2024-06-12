#include "CommonTypes.hpp"
#include <cppdic/ServiceProviderBuilder.hpp>
#include <print>

int main()
{
    { // Provider can be constructed and resolves fairly complex dependencies
        auto&& provider = dic::ServiceProviderBuilder()
                              .addService<Aa>() // depends on nothing
                              .addService<Bb>() // depends on Aa
                              .addService<Cc>() // depends on Bb
                              .addService<Dd>() // depends on Aa and Cc
                              .addService<Ee>() // depends on Dd and Bb
                              .build();
        std::println("{}", provider.get<Ee>()->tuv()); // expecting 128
    }

    auto mock = std::make_shared<Mock>();

    { // Service can be mocked

        auto&& provider = dic::ServiceProviderBuilder()
                              .addService<I>(mock)
                              .addService<DependsOnI>()
                              .build();

        std::println("{}", provider.get<I>()->foo()); // expecting -1
    }

    { // Service can be replaced
        auto&& provider = dic::ServiceProviderBuilder()
                              .addService<I, Ia>()
                              .addService<DependsOnI>()
                              .addService<I>(mock)
                              .build();

        std::println("{}", provider.get<I>()->foo()); // expecting -1
    }

    return 0;
}
