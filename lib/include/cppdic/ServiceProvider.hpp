#pragma once

#include <cppdic/Service.hpp>
#include <cppdic/Utils.hpp>

namespace dic
{

    template<class... Ts>
    class [[nodiscard]] ServiceProvider final
    {
    public:
        explicit ServiceProvider(Services<Ts...> _impls) : impls(_impls)
        {
            initialize<0, Ts...>();
        }

    public:
        template<class T>
        std::shared_ptr<T> get()
        {
            constexpr auto index = utils::getIndex<T, Ts...>(0);
            return std::get<index>(impls);
        }

    private:
        template<size_t Index, class Head, class... Tail>
        void initialize()
        {
            auto& impl = std::get<Index>(impls);
            if (impl == nullptr)
            {
                impl = std::make_shared<Head::ImplType>();
            }

            if constexpr (Index < sizeof...(Ts) - 1)
                initialize<Index + 1, Tail...>();
        }

    private:
        Services<Ts...> impls;
    };
} // namespace dic