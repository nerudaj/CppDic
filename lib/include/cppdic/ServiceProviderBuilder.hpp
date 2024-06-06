#pragma once

#include <cppdic/Service.hpp>
#include <cppdic/ServiceProvider.hpp>
#include <cppdic/Utils.hpp>

namespace dic
{

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
        template<class Concrete>
        auto addService(std::shared_ptr<Concrete> impl = nullptr)
        {
            static_assert(
                !std::is_abstract_v<Concrete>,
                "When calling addService with just one template parameter, "
                "that "
                "parameter must not be an abstract class.");
            return addServiceImpl<true, Concrete, Concrete>(impl);
        }

        template<class Iface, class Impl>
        auto addService(std::shared_ptr<Iface> impl = nullptr)
        {
            static_assert(
                std::is_abstract_v<Iface>,
                "When calling addService with two template parameters, first "
                "parameter must be an abstract class.");
            static_assert(
                !std::is_abstract_v<Impl>,
                "When calling addService with two template parameters, the "
                "second "
                "parameter must be a concrete class.");
            static_assert(
                std::is_base_of_v<Iface, Impl>,
                "The first template parameter of addService must be a base "
                "class "
                "of the second parameter");
            return addServiceImpl<true, Iface, Impl>(impl);
        }

        auto build()
        {
            // This could construct all shared ptrs and hide impl types from
            // provider
            return ServiceProvider<Ts...>(impls);
        }

    private:
        template<bool PerformCreationChecks, class Iface, class Impl = Iface>
        auto addServiceImpl(std::shared_ptr<Iface> impl = nullptr)
        {
            constexpr auto index = utils::getIndex<Iface, Ts...>(0);

            if constexpr (PerformCreationChecks)
            {
                if constexpr (sizeof...(Ts) == 0)
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
                            || utils::TopLevelUnpack<
                                Impl,
                                utils::permutations_t<Services<Ts...>>>::value,
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

    private:
        Services<Ts...> impls;
    };
} // namespace dic