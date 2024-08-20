
#pragma once

#include <array>
#include <cstdint>

#include "exc/enum.hpp"

namespace exc {

enum class Example {
  Apple,
  Orange,
  Pineapple,
  Banana,
  Extra,
  OneMore,
  Other,
  LastOne,

};

}

template <> struct exc::Enum<exc::Example> {
 public:
  using Example = exc::Example;

  static const char* to_string(Example t);

  static constexpr size_t count = 8;

  static constexpr std::array<Example, count> all = {
    Example::Apple,
    Example::Orange,
    Example::Pineapple,
    Example::Banana,
    Example::Extra,
    Example::OneMore,
    Example::Other,
    Example::LastOne,

  };
};

static_assert(exc::is_ex_enum<exc::Example>);
