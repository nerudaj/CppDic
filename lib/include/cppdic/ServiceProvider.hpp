#pragma once

#include <cppdic/Service.hpp>
#include <cppdic/Utils.hpp>

namespace dic
{

    template<class... Ts>
    class [[nodiscard]] ServiceProvider final
    {
    public:
        explicit ServiceProvider(Services<Ts...> _impls) : impls(_impls) {}

    public:
        template<class T>
        std::shared_ptr<T> get()
        {
            constexpr auto index = utils::getIndex<T, Ts...>(0);
            return std::get<index>(impls);
        }

    private:
        Services<Ts...> impls;
    };
} // namespace dic