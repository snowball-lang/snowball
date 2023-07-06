
// Copyright (c) 2017 Tristan Brindle (tcbrindle at gmail dot com)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TCB_PRETTY_PRINT_HPP_INCLUDED
#define TCB_PRETTY_PRINT_HPP_INCLUDED

#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>

#if __cplusplus >= 201700
#include <string_view>
#include <variant>
#define TCB_PRETTY_PRINT_HAVE_CPP17
#endif

namespace tcb {
inline namespace pretty_print {

namespace detail {

template <typename...>
using void_t = void;

template <typename T>
using iterator_t = decltype(std::begin(std::declval<T&>()));

template <typename T>
using iterator_category_t = typename std::iterator_traits<T>::iterator_category;

template <typename T>
using array_element_t = std::remove_pointer_t<std::decay_t<T>>;

template <typename T>
struct is_quotable : std::false_type {
};

template <typename C, typename T, typename A>
struct is_quotable<std::basic_string<C, T, A>> : std::true_type {
};

#ifdef TCB_PRETTY_PRINT_HAVE_CPP17
template <typename C, typename T>
struct is_quotable<std::basic_string_view<C, T>> : std::true_type {
};
#endif

template <>
struct is_quotable<char*> : std::true_type {
};
template <>
struct is_quotable<char16_t*> : std::true_type {
};
template <>
struct is_quotable<char32_t*> : std::true_type {
};
template <>
struct is_quotable<wchar_t*> : std::true_type {
};

template <typename T>
constexpr bool is_quotable_v = is_quotable<T>::value;

template <typename T, typename = void>
struct quoter {
    const T& operator()(const T& t) const { return t; }
};

#ifndef TCB_PRETTY_PRINT_NO_STRING_QUOTING
template <typename T>
struct quoter<T, std::enable_if_t<is_quotable_v<std::decay_t<T>>>> {
    decltype(auto) operator()(const T& t) const { return std::quoted(t); }
};
#endif

template <typename T>
decltype(auto) quoted(const T& t)
{
    return quoter<T>{}(t);
}

template <typename T, typename = void>
struct is_range_like : std::false_type {
};

// A type is "Range-like" if std::begin(R) returns a type whose
// iterator_traits::iterator_category is derived from std::input_iterator_tag
// This definition would probably make Eric and Casey scream ;)
template <typename T>
struct is_range_like<
    T, std::enable_if_t<std::is_base_of<
           std::input_iterator_tag, iterator_category_t<iterator_t<T>>>::value>>
    : std::true_type {
};

template <typename T>
constexpr bool is_range_like_v = is_range_like<T>::value;

template <typename, typename = void>
struct is_map_like : std::false_type {
};

// A map-like type is a range-like whose iterator type has
// 'first' and 'second' members. This is true for std::map and
// std::unordered_map, and for std::vector<std::pair>> (commonly used as a flat
// map).
template <typename Map>
struct is_map_like<Map,
                   void_t<std::enable_if_t<is_range_like_v<Map>>,
                          decltype(std::declval<iterator_t<Map>>()->first),
                          decltype(std::declval<iterator_t<Map>>()->second)>>
    : std::true_type {
};

template <typename T>
constexpr bool is_map_like_v = is_map_like<T>::value;

template <typename, typename = void>
struct is_tuple_like : std::false_type {
};

// A tuple-like type is one for which is specialisation of std::tuple_size
// exists, the 'value' member of which is of type std::size_t.
// FIXME: this definition sucks -- we really ought to check that tuple_element
// exists too for each I in [0, N)
template <typename T>
struct is_tuple_like<
    T,
    std::enable_if_t<std::is_same<
        std::decay_t<decltype(std::tuple_size<T>::value)>, std::size_t>::value>>
    : std::true_type {
};

template <typename T>
constexpr bool is_tuple_like_v = is_tuple_like<T>::value;

template <typename, typename = void>
struct is_optional_like : std::false_type {
};

// A type is optional-like for our purposes if it has a dereference operator,
// and is explicitly convertible to bool. This is true for std::optional,
// boost::optional and all pointer types, although we disable overloads for the
// latter by default.
template <typename T>
struct is_optional_like<T,
                        void_t<decltype(*std::declval<T>()),
                               decltype(static_cast<bool>(std::declval<T>()))>>
    : std::true_type {
};

template <typename T>
constexpr bool is_optional_like_v = is_optional_like<T>::value;

template <typename, typename, typename = void>
struct is_streamable : std::false_type {
};

template <typename StreamT, typename T>
struct is_streamable<
    StreamT, T,
    std::enable_if_t<std::is_convertible<decltype(std::declval<StreamT&>()
                                                  << std::declval<T>()),
                                         std::ios_base&>::value>>
    : std::true_type {
};

template <typename StreamT, typename T>
constexpr bool is_streamable_v = is_streamable<StreamT, T>::value;

// I'm sure clever non-recursive things could be done here with
// std::index_sequence and/or fold expressions, but this has
// the advantage that I actually understand what's going on :)
template <typename Tuple, std::size_t I, std::size_t N>
struct tuple_printer {
    template <typename OStream>
    OStream& operator()(OStream& os, const Tuple& t) const
    {
        using std::get;
        os << ", " << quoted(get<I>(t));
        return tuple_printer<Tuple, I + 1, N>{}(os, t);
    }
};

template <typename Tuple, std::size_t N>
struct tuple_printer<Tuple, 0, N> {
    template <typename OStream>
    OStream& operator()(OStream& os, const Tuple& t) const
    {
        using std::get;
        os << '(' << quoted(get<0>(t));
        return tuple_printer<Tuple, 1, N>{}(os, t);
    }
};

template <typename Tuple, std::size_t N>
struct tuple_printer<Tuple, N, N> {
    template <typename OStream>
    OStream& operator()(OStream& os, const Tuple& t) const
    {
        os << ')';
        return os;
    }
};

// Handle zero-sized tuples
template <typename Tuple>
struct tuple_printer<Tuple, 0, 0> {
    template <typename OStream>
    OStream& operator()(OStream& os, const Tuple& t) const
    {
        os << "()";
        return os;
    }
};

template <typename Tuple>
tuple_printer<Tuple, 0, std::tuple_size<Tuple>::value>
make_tuple_printer(const Tuple& t)
{
    return {};
}

// This is the test used to decide whether to enable the range stream function.
// it looks a bit complicated, but it's not that bad really. Basically,
// for this function to be enabled, we require
//
// * Range is range-like (that is, std::begin(c) returns an iterator),
//   -- BUT it's not map-like, which we handle separately,
// * AND it does not already have an output stream function (don't stomp on
//   std::string or custom containers' operator<<()s)
//   -- except for the case where Range is a raw C array whose element type is
//      different from the stream's character type
//
// To explain the last case, cout << int[5] will work with just the standard
// ostream headers, but pointer decay will occur and something like 0xDEADBEEF
// will be printed, which is not very useful. So we enable this overload for raw
// arrays, which becomes a better match (array->pointer conversion is not
// required). However, we still want char arrays to be printed as strings, so we
// disable this (again) if Range is a raw array of the same type as the
// OStream's character type.
//
// Phew!
template <typename OStream, typename Range>
constexpr bool should_print_range_v =
    is_range_like_v<Range> && !is_map_like_v<Range> &&
    (!is_streamable_v<OStream, Range> ||
     (std::is_array<Range>::value &&
      !std::is_same<array_element_t<Range>,
                    typename OStream::char_type>::value));

// For maps it's simple -- we print it if it is map-like
template <typename OStream, typename Map>
constexpr bool should_print_map_v = is_map_like_v<Map>;

// std::arrays are both tuple-like and range-like, but we prefer to regard them
// as ranges
template <typename Tuple>
constexpr bool should_print_tuple_v =
    is_tuple_like_v<Tuple> && !is_range_like_v<Tuple>;

// Raw C arrays are both optional-like (per our definition)
// and range-like. We prefer to treat them as ranges.
template <typename OStream, typename Optional>
constexpr bool should_print_optional_v =
    is_optional_like_v<Optional> && !is_range_like_v<Optional>
#ifndef TCB_PRETTY_PRINT_POINTERS_ARE_OPTIONALS
    && !std::is_pointer<Optional>::value
#endif
    && !std::is_same<array_element_t<Optional>,
                     typename OStream::char_type>::value;

} // namespace detail

// To ensure that all our print functions can call each other, we need to
// declare them all first, and then define them later.

template <
    typename OStream, typename Range,
    std::enable_if_t<detail::should_print_range_v<OStream, Range>, int> = 0>
OStream& operator<<(OStream& os, const Range& rng);

template <typename OStream, typename Map,
          std::enable_if_t<detail::should_print_map_v<OStream, Map>, int> = 0>
OStream& operator<<(OStream& os, const Map& map);

template <typename OStream, typename Tuple,
          std::enable_if_t<detail::should_print_tuple_v<Tuple>, int> = 0>
OStream& operator<<(OStream& os, const Tuple& tuple);

template <typename OStream, typename Optional,
          std::enable_if_t<detail::should_print_optional_v<OStream, Optional>,
                           int> = 0>
OStream& operator<<(OStream& os, const Optional& opt);

#ifdef TCB_PRETTY_PRINT_HAVE_CPP17
template <typename OStream, typename... Ts>
OStream& operator<<(OStream& os, const std::variant<Ts...>& var);
#endif

// http://en.cppreference.com/w/cpp/experimental/ostream_joiner
template <typename DelimT, typename CharT, typename Traits>
struct ostream_joiner {
    using char_type = CharT;
    using traits_type = Traits;
    using ostream_type = std::basic_ostream<CharT, Traits>;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using iterator_category = std::output_iterator_tag;

    ostream_joiner(ostream_type& stream, const DelimT& delim)
        : os_(std::addressof(stream)), delim_(delim)
    {
    }

    ostream_joiner(ostream_type& stream, DelimT&& delim)
        : os_(std::addressof(stream)), delim_(std::move(delim))
    {
    }

    template <typename T>
    ostream_joiner& operator=(const T& value)
    {
        if (!first_) {
            *os_ << delim_;
        }
        first_ = false;
        *os_ << value;
        return *this;
    }

    ostream_joiner& operator*() noexcept { return *this; }

    ostream_joiner& operator++() noexcept { return *this; }

    ostream_joiner& operator++(int) noexcept { return *this; }

private:
    ostream_type* os_;
    DelimT delim_;
    bool first_ = true;
};

template <typename CharT, typename Traits, typename DelimT>
ostream_joiner<std::decay_t<DelimT>, CharT, Traits>
make_ostream_joiner(std::basic_ostream<CharT, Traits>& os, DelimT&& delimiter)
{
    return ostream_joiner<std::decay_t<DelimT>, CharT, Traits>(
        os, std::forward<DelimT>(delimiter));
}

template <typename OStream, typename Range,
          std::enable_if_t<detail::should_print_range_v<OStream, Range>, int>>
OStream& operator<<(OStream& os, const Range& rng)
{
    os << '[';
    auto joiner = make_ostream_joiner(os, ", ");
    for (const auto& e : rng) {
        joiner = detail::quoted(e);
    }
    os << ']';
    return os;
}

template <typename OStream, typename Map,
          std::enable_if_t<detail::should_print_map_v<OStream, Map>, int>>
OStream& operator<<(OStream& os, const Map& map)
{
    os << '{';

    auto next = std::begin(map);
    const auto last = std::end(map);

    if (next != last) {
        os << detail::quoted(next->first) << ": "
           << detail::quoted(next->second);
        ++next;
    }

    while (next != last) {
        os << ", " << detail::quoted(next->first) << ": "
           << detail::quoted(next->second);
        ++next;
    }

    os << '}';
    return os;
}

template <typename OStream, typename Tuple,
          std::enable_if_t<detail::should_print_tuple_v<Tuple>, int>>
OStream& operator<<(OStream& os, const Tuple& tuple)
{
    const auto printer = detail::make_tuple_printer(tuple);
    return printer(os, tuple);
}

template <typename OStream, typename Opt,
          std::enable_if_t<detail::should_print_optional_v<OStream, Opt>, int>>
OStream& operator<<(OStream& os, const Opt& opt)
{
    if (opt) {
        os << *opt;
    } else {
        os << "--";
    }
    return os;
}

#ifdef TCB_PRETTY_PRINT_HAVE_CPP17
template <typename OStream, typename... Ts>
OStream& operator<<(OStream& os, const std::variant<Ts...>& var)
{
    const auto print_visitor = [&os](const auto& val) -> OStream& {
        os << detail::quoted(val);
        return os;
    };
    return std::visit(print_visitor, var);
}

#endif

template <typename Container>
std::string to_string(const Container& cont)
{
    std::ostringstream ss;
    ss << cont;
    return ss.str();
}

} // namespace pretty_print
} // namespace tcb

#endif