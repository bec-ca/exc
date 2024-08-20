
#pragma once

#include <array>
#include <cstdint>

#include "exc/enum.hpp"

namespace exc {

enum class TokenKind {
  Empty,
  Comment,
  String,
  Number,
  Identifier,
  Eof,
  Namespace,
  Enum,
  OpenBraces,
  CloseBraces,
  Semicolon,
  Period,

};

}

template <> struct exc::Enum<exc::TokenKind> {
 public:
  using TokenKind = exc::TokenKind;

  static const char* to_string(TokenKind t);

  static constexpr size_t count = 12;

  static constexpr std::array<TokenKind, count> all = {
    TokenKind::Empty,
    TokenKind::Comment,
    TokenKind::String,
    TokenKind::Number,
    TokenKind::Identifier,
    TokenKind::Eof,
    TokenKind::Namespace,
    TokenKind::Enum,
    TokenKind::OpenBraces,
    TokenKind::CloseBraces,
    TokenKind::Semicolon,
    TokenKind::Period,

  };
};

static_assert(exc::is_ex_enum<exc::TokenKind>);
