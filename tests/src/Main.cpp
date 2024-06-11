#include "CommonTypes.hpp"
#include <cppdic/ServiceProviderBuilder.hpp>
#include <print>

struct Mock : public I
{
    int foo() override
    {
        return -1;
    }
};

int main()
{
    {
        // Can be constructed
        auto provider =
            dic::ServiceProviderBuilder()
                .addService<A>()
                .addService<B>()
                .addService<Eshared>() // requires A and B as dependencies
                .build();
        provider.get<Eshared>()->hello();
    }

    {
        auto mock = std::make_shared<Mock>();
        auto&& provider = dic::ServiceProviderBuilder()
                              .addService<I, Ia>()
                              .addService<I>(mock)
                              .build();

        std::println("{}", provider.get<I>()->foo());
    }

    return 0;
}
