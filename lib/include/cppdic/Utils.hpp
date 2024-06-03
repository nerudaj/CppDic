#pragma once

#include <concepts>
#include <tuple>

namespace dic
{
    namespace utils
    {
        // === getIndex ===
        template<class T>
        static consteval std::size_t getIndex(std::size_t index)
        {
            return index;
        }

        template<class T, class FirstT, class... RemainingTs>
        static consteval std::size_t getIndex(std::size_t index)
        {
            using Base = FirstT::BaseType;
            if constexpr (std::is_same_v<T, Base>) return index;
            return getIndex<T, RemainingTs...>(index + 1);
        }

        // === TypesBefore ===
        template<class T, size_t... I>
        auto makeSubsetTuple(const T& t, std::index_sequence<I...>)
        {
            return std::make_tuple(std::get<I>(t)...);
        }

        template<size_t Index, class... Ts>
        struct TypesBefore
        {
            using Types = decltype(makeSubsetTuple(
                std::tuple<Ts...> {}, std::make_index_sequence<Index> {}));
        };

        // === TypesAfter ===
        template<size_t, class...>
        struct TypesAfter;

        template<size_t Index, class Head, class... Tail>
        struct TypesAfter<Index, Head, Tail...> : TypesAfter<Index - 1, Tail...>
        {
        };

        template<class Head, class... Tail>
        struct TypesAfter<0, Head, Tail...>
        {
            using Types = std::tuple<Tail...>;
        };

        // === Permutations ===
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
        struct permutations
        {
        };

        template<template<typename...> class P, typename... Ts>
        struct permutations<P<Ts...>>
        {
            using type = typename detail::
                permutations_impl<sizeof...(Ts), P<Ts...>>::type;
        };

        template<typename Pack>
        using permutations_t = typename permutations<Pack>::type;

        template<class, size_t, class...>
        struct CanConstructFromAtLeastOneSubset;

        template<class T, size_t Idx, class Head, class... Tail>
        struct CanConstructFromAtLeastOneSubset<T, Idx, Head, Tail...>
            : std::bool_constant<
                  std::constructible_from<T, Head, Tail...>
                  || CanConstructFromAtLeastOneSubset<T, Idx - 1, Tail...>::
                      value>
        {
        };

        template<class T, class U>
        struct CanConstructFromAtLeastOneSubset<T, 1, U>
            : std::bool_constant<std::constructible_from<T, U>>
        {
        };

        template<class, class>
        struct CanConstructFromTuple;

        template<class T, class... Us>
        struct CanConstructFromTuple<T, std::tuple<Us...>>
            //: std::bool_constant<std::constructible_from<T, Us...>>
            : std::bool_constant<
                  CanConstructFromAtLeastOneSubset<T, sizeof...(Us), Us...>::
                      value>
        {
        };

        // Rule no1 of recursion
        template<class, class...>
        struct CanConstructFromAListOfTuples;

        template<class T, class Head, class... Tail>
        struct CanConstructFromAListOfTuples<T, Head, Tail...>
            : std::bool_constant<
                  CanConstructFromTuple<T, Head>::value
                  || CanConstructFromAListOfTuples<T, Tail...>::value>
        {
        };

        template<class T, class U>
        struct CanConstructFromAListOfTuples<T, U>
            : std::bool_constant<CanConstructFromTuple<T, U>::value>
        {
        };

        template<class, class>
        struct TopLevelUnpack;

        template<class T, class... Us>
        struct TopLevelUnpack<T, std::tuple<Us...>>
            : std::bool_constant<CanConstructFromAListOfTuples<T, Us...>::value>
        {
        };
    } // namespace utils
} // namespace dic