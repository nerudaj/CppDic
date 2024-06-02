#pragma once

#include <memory>
#include <tuple>

namespace dic
{

    template<class Base, class Impl = Base>
    struct Service
    {
        using BaseType = Base;
        using ImplType = Impl;
    };

    template<class... Ts>
    using Services = std::tuple<std::shared_ptr<typename Ts::BaseType>...>;

} // namespace dic