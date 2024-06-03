#include <cppdic/ServiceProviderBuilder.hpp>
#include <print>

class I
{
public:
    virtual void hello() = 0;
};

class A : public I
{
public:
    void hello() override
    {
        std::println("hello");
    }
};

class B : public I
{
public:
    void hello() override
    {
        std::println("world");
    }
};

class C
{
public:
    void hello()
    {
        std::println("C");
    }
};

class D
{
};

class Perm
{
public:
    Perm(A, C, B) {}
};

int main()
{
    constexpr auto index1 =
        dic::utils::getIndex<I, dic::Service<C, C>, dic::Service<I, A>>(0);
    static_assert(index1 == 1u);
    constexpr auto index2 =
        dic::utils::getIndex<B, dic::Service<C, C>, dic::Service<I, A>>(0);
    static_assert(index2 == 2u);

    using before = dic::utils::TypesBefore<1, A, B, C>::Types;
    static_assert(std::is_same_v<before, std::tuple<A>>);

    using after = dic::utils::TypesAfter<1, A, B, C>::Types;
    static_assert(std::is_same_v<after, std::tuple<C>>);

    auto&& b = std::make_shared<B>();
    auto&& provider = dic::ServiceProviderBuilder()
                          .addService<I, A>()
                          .addService<I, A>(b)
                          .addService<C>()
                          .build();
    provider.get<I>()->hello();

    static_assert(
        dic::utils::CanConstructFromTuple<Perm, std::tuple<A, C, B>>::value);
    static_assert(std::constructible_from<Perm, A, C, B>);
    static_assert(!std::constructible_from<Perm, A, B, C>);
    static_assert(
        !dic::utils::CanConstructFromTuple<Perm, std::tuple<A, B, C>>::value);
    static_assert(
        dic::utils::CanConstructFromAListOfTuples<Perm, std::tuple<A, C, B>>::
            value);
    static_assert(
        !dic::utils::CanConstructFromAListOfTuples<Perm, std::tuple<A, B, C>>::
            value);
    static_assert(dic::utils::TopLevelUnpack<
                  Perm,
                  dic::utils::permutations_t<std::tuple<A, B, C, D>>>::value);
    static_assert(!dic::utils::TopLevelUnpack<
                  Perm,
                  dic::utils::permutations_t<std::tuple<A, B>>>::value);
}
