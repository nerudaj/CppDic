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

struct Aa
{
    int bar()
    {
        return 2;
    }
};

struct Bb
{
    Bb(std::shared_ptr<Aa> _aa) : aa(_aa) {}

    int baz()
    {
        return 2 * aa->bar(); // 4
    }

    std::shared_ptr<Aa> aa;
};

struct Cc
{
    Cc(std::shared_ptr<Bb> _bb) : bb(_bb) {}

    int foo()
    {
        return bb->baz() * 4; // 16
    }

    std::shared_ptr<Bb> bb;
};

struct Dd
{
    Dd(std::shared_ptr<Aa> _aa, std::shared_ptr<Cc> _cc) : aa(_aa), cc(_cc) {}

    int xyz()
    {
        return aa->bar() * cc->foo(); // 32
    }

    std::shared_ptr<Aa> aa;
    std::shared_ptr<Cc> cc;
};

struct Ee
{
    Ee(std::shared_ptr<Dd> _dd, std::shared_ptr<Bb> _bb) : dd(_dd), bb(_bb) {}

    int tuv()
    {
        return dd->xyz() * bb->baz(); // 128
    }

    std::shared_ptr<Dd> dd;
    std::shared_ptr<Bb> bb;
};

int main()
{
    { // Provider can be constructed and resolves fairly complex dependencies
        auto&& provider = dic::ServiceProviderBuilder()
                              .addService<Aa>()
                              .addService<Bb>()
                              .addService<Cc>()
                              .addService<Dd>()
                              .addService<Ee>()
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
