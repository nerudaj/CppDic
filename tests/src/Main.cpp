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

    constexpr auto index =
        dic::utils::getIndex<Cc, dic::Service<Aa>, dic::Service<Bb>>(0);
    // using TypesBeforeThisOne = ;
    using Permutations =
        dic::utils::Permutations<dic::utils::TypesBeforeTupleAdapter<
            index,
            typename dic::Services<dic::Service<Aa>, dic::Service<Bb>>>::
                                     Types>::Types;
    static_assert(std::is_same_v<
                  Permutations,
                  std::tuple<
                      std::tuple<std::shared_ptr<Aa>, std::shared_ptr<Bb>>,
                      std::tuple<std::shared_ptr<Bb>, std::shared_ptr<Aa>>>>);
    constexpr bool value =
        dic::utils::CanConstructTypeFromAListOfTuples<Cc, Permutations>::value;
    constexpr bool value2 =
        dic::utils::CanConstructTypeFromAtLeastOneTuplePrefixSubset<
            Cc,
            std::tuple<std::shared_ptr<Bb>, std::shared_ptr<Aa>>>::value;

    {
        auto&& provider = dic::ServiceProviderBuilder()
                              .addService<Aa>()
                              .addService<Bb>()
                              .addService<Cc>()
                              .addService<Dd>()
                              .addService<Ee>()
                              .build();
        std::println("{}", provider.get<Ee>()->tuv());
    }

    return 0;
}
