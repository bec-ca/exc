#pragma once

#include "bee/to_string_t.hpp"

namespace exc {

template <class T> struct Enum;

template <class T>
concept is_ex_enum = requires(const T t) {
  { Enum<T>::to_string(t) } -> std::same_as<const char*>;
  { Enum<T>::count } -> std::convertible_to<size_t>;
  { Enum<T>::all } -> std::convertible_to<std::array<T, Enum<T>::count>>;
};

} // namespace exc

template <class T>
  requires exc::is_ex_enum<T>
struct bee::to_string_t<T> {
 public:
  static const char* convert(const T v) { return exc::Enum<T>::to_string(v); }
};
