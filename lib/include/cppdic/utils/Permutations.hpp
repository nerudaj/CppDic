#pragma once

#include <type_traits>

// https://codereview.stackexchange.com/questions/80373/generating-all-permutations-of-a-template-pack

namespace dic
{
    namespace utils
    {
        namespace detail
        {

            template<typename P1, typename P2>
            struct merge
            {
            };

            template<
                template<typename...>
                class P,
                typename... Ts,
                typename... Us>
            struct merge<P<Ts...>, P<Us...>>
            {
                using type = P<Ts..., Us...>;
            };

            template<typename T, typename P>
            struct prepend
            {
            };

            template<
                typename T,
                template<typename...>
                class P,
                typename... Packs>
            struct prepend<T, P<Packs...>>
            {
                using type = P<typename merge<P<T>, Packs>::type...>;
            };

            // N is the number of rotations to go
            template<std::size_t N, typename Pack, typename = void>
            struct permutations_impl
            {
            };

            template<template<typename...> class P, typename... Ts>
            struct permutations_impl<0, P<Ts...>>
            {
                // All rotations done, break the recursion
                using type = P<>;
            };

            template<std::size_t N, template<typename...> class P, typename T>
            struct permutations_impl<N, P<T>>
            {
                using type = P<P<T>>;
            };

            template<
                std::size_t N,
                template<typename...>
                class P,
                typename F,
                typename... Rest>
            struct permutations_impl<
                N,
                P<F, Rest...>,
                std::enable_if_t<(sizeof...(Rest) && N != 0)>>
            {
                using PermuteRest =
                    typename permutations_impl<sizeof...(Rest), P<Rest...>>::
                        type;
                using NextRotation =
                    typename permutations_impl<N - 1, P<Rest..., F>>::type;

                using type = typename merge<
                    typename prepend<F, PermuteRest>::type,
                    NextRotation>::type;
            };

        } // namespace detail

        template<typename Pack>
        struct Permutations
        {
        };

        template<template<typename...> class P, typename... Ts>
        struct Permutations<P<Ts...>>
        {
            using Types = typename detail::
                permutations_impl<sizeof...(Ts), P<Ts...>>::type;
        };
    } // namespace utils
} // namespace dic
