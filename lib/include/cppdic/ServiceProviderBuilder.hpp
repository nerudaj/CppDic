#pragma once

#include <cppdic/Service.hpp>
#include <cppdic/ServiceProvider.hpp>
#include <cppdic/Utils.hpp>

namespace dic
{
    template<class C>
    concept IsAbstract = std::is_abstract_v<C>;

    template<class C>
    concept IsConcrete = !std::is_abstract_v<C>;

    template<class... Ts>
    class ServiceProviderBuilder final
    {
    public:
        template<class T, class U, class V>
        struct ConcatTupleTypes3;

        template<class... Ts, class... Us, class... Vs>
        struct ConcatTupleTypes3<
            std::tuple<Ts...>,
            std::tuple<Us...>,
            std::tuple<Vs...>>
        {
            using CollectionWithConcatenatedTypes =
                ServiceProviderBuilder<Ts..., Us..., Vs...>;
        };

        [[nodiscard]] ServiceProviderBuilder() = default;

    private:
        ServiceProviderBuilder(Services<Ts...> impls) : impls(impls) {}

        friend class ServiceProviderBuilder;

    public:
        template<IsConcrete Concrete>
        auto addService()
        {
            return addServiceImpl<true, Concrete, Concrete>();
        }

        template<
            IsAbstract Iface,
            IsConcrete Impl,
            class = std::enable_if_t<std::is_base_of_v<Iface, Impl>>>
        auto addService()
        {
            return addServiceImpl<true, Iface, Impl>();
        }

        template<class T>
        auto addService(std::shared_ptr<T> impl)
        {
            return addServiceImpl<false, T, T>(impl);
        }

        auto build()
        {
            auto finalImpls = impls;
            initializeEmptyImpls<0, Ts...>(finalImpls);
            return ServiceProvider<Ts...>(finalImpls);
        }

    private:
        template<bool PerformCreationChecks, class Iface, class Impl = Iface>
        auto addServiceImpl(std::shared_ptr<Iface> impl = nullptr)
        {
            constexpr auto index = utils::getIndex<Iface, Ts...>(0);

            if constexpr (PerformCreationChecks)
            {
                using TypesBeforeThisOne = utils::
                    TypesBeforeTupleAdapter<index, Services<Ts...>>::Types;

                if constexpr (std::tuple_size_v<TypesBeforeThisOne> == 0)
                {
                    static_assert(
                        std::is_default_constructible_v<Impl>,
                        "Type has to be default-constructible, nothing else is "
                        "in the collection yet.");
                }
                else
                {
                    static_assert(
                        std::is_default_constructible_v<Impl>
                            || utils::CanConstructTypeFromAListOfTuples<
                                Impl,
                                utils::Permutations<
                                    TypesBeforeThisOne>::Types>::value,
                        "Could not construct service only from services "
                        "already "
                        "registered in the builder.");
                }
            }

            if constexpr (sizeof...(Ts) == index)
            {
                return ServiceProviderBuilder<Ts..., Service<Iface, Impl>>(
                    std::tuple_cat(
                        impls, std::tuple<std::shared_ptr<Iface>>(impl)));
            }
            else
            {
                // Overwrite previously stored implementation (if any)
                std::get<index>(impls) = impl;

                return ConcatTupleTypes3<
                    typename utils::TypesBefore<index, Ts...>::Types,
                    std::tuple<Service<Iface, Impl>>,
                    typename utils::TypesAfter<index, Ts...>::Types>::
                    CollectionWithConcatenatedTypes(impls);
            }
        }

        template<size_t Index, class Head, class... Tail>
        static void initializeEmptyImpls(auto& impls)
        {
            auto& impl = std::get<Index>(impls);
            constexpr static bool IsNull =
                !(std::is_same_v<Head::BaseType, Head::ImplType>
                  && std::is_abstract_v<Head::BaseType>);
            if constexpr (IsNull)
            {
                using Impl = Head::ImplType;

                if constexpr (std::is_default_constructible_v<Impl>)
                {
                    impl = std::make_shared<Impl>();
                }
                else
                {
                    using Deps = utils::CanConstructTypeFromAListOfTuples<
                        Impl,
                        typename utils::Permutations<std::remove_cvref_t<
                            decltype(impls)>>::Types>::Tuple;
                    auto deps = SubsetCallWrapper<Deps>::selectSubsetPub(impls);
                    static_assert(
                        std::is_same_v<decltype(deps), Deps>,
                        "Sanity check failed");
                    impl = utils::makeSharedFromTuple<Impl>(deps);
                }
            }

            if constexpr (sizeof...(Tail) > 0)
                initializeEmptyImpls<Index + 1, Tail...>(impls);
        }

        template<class>
        struct SubsetCallWrapper;

        template<class... Ts>
        struct SubsetCallWrapper<std::tuple<Ts...>>
        {
            template<class Head, class... Tail>
            static auto selectSubset(auto& impls, const auto& selectedSoFar)
            {
                if constexpr (sizeof...(Tail) == 0)
                    return std::tuple_cat(
                        selectedSoFar, std::tuple<Head>(std::get<Head>(impls)));
                else
                    return std::tuple_cat(
                        selectedSoFar,
                        selectSubset<Tail...>(impls, selectedSoFar));
            }

            template<class Head, class... Tail>
            static auto selectSubset(auto& impls)
            {
                auto first = std::tuple<Head>(std::get<Head>(impls));
                if constexpr (sizeof...(Tail) == 0)
                    return first;
                else
                    return selectSubset<Tail...>(impls, first);
            }

            static auto selectSubsetPub(auto& impls)
            {
                return selectSubset<Ts...>(impls);
            }
        };

    private:
        Services<Ts...> impls;
    };
} // namespace dic