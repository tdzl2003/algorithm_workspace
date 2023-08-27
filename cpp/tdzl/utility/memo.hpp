#pragma once

// Source: https://stackoverflow.com/questions/17805969/writing-universal-memoization-function-in-c11
// Source: https://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set/7115547#7115547

#include <tuple>

namespace std {
    namespace
    {

        // Code from boost
        // Reciprocal of the golden ratio helps spread entropy
        //     and handles duplicates.
        // See Mike Seymour in magic-numbers-in-boosthash-combine:
        //     http://stackoverflow.com/questions/4948780

        template <class T>
        inline void hash_combine(std::size_t& seed, T const& v)
        {
            seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        // Recursive template code derived from Matthieu M.
        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
        struct HashValueImpl
        {
            static void apply(size_t& seed, Tuple const& tuple)
            {
                HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
                hash_combine(seed, std::get<Index>(tuple));
            }
        };

        template <class Tuple>
        struct HashValueImpl<Tuple, 0>
        {
            static void apply(size_t& seed, Tuple const& tuple)
            {
                hash_combine(seed, std::get<0>(tuple));
            }
        };
    }

    template <typename ... TT>
    struct hash<std::tuple<TT...>>
    {
        size_t
            operator()(std::tuple<TT...> const& tt) const
        {
            size_t seed = 0;
            HashValueImpl<std::tuple<TT...> >::apply(seed, tt);
            return seed;
        }

    };
}

struct wrap {};

template<class Sig, class F, template<class...>class Hash = std::hash>
struct memoizer;
template<class R, class...Args, class F, template<class...>class Hash>
struct memoizer<R(Args...), F, Hash> {
    using base_type = F;
private:
    F base;
    mutable std::unordered_map< std::tuple<std::decay_t<Args>...>, R > cache;
public:

    template<class... Ts>
    R operator()(Ts&&... ts) const
    {
        auto args = std::make_tuple(ts...);
        auto it = cache.find(args);
        if (it != cache.end())
            return it->second;

        auto&& retval = base(*this, std::forward<Ts>(ts)...);

        cache.emplace(std::move(args), retval);

        return decltype(retval)(retval);
    }
    template<class... Ts>
    R operator()(Ts&&... ts)
    {
        auto args = std::tie(ts...);
        auto it = cache.find(args);
        if (it != cache.end())
            return it->second;

        auto&& retval = base(*this, std::forward<Ts>(ts)...);

        cache.emplace(std::move(args), retval);

        return decltype(retval)(retval);
    }

    memoizer(memoizer const&) = default;
    memoizer(memoizer&&) = default;
    memoizer& operator=(memoizer const&) = default;
    memoizer& operator=(memoizer&&) = default;
    memoizer() = delete;
    template<typename L>
    memoizer(wrap, L&& f) :
        base(std::forward<L>(f))
    {}
};

template<typename Sig, typename F>
memoizer<Sig, std::decay_t<F>> memorize(F&& f) { return { wrap{}, std::forward<F>(f) }; }
