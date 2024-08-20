
#include "token_kind.generated.hpp"

namespace exc {}

const char* exc::Enum<exc::TokenKind>::to_string(exc::TokenKind e)
{
  switch (e) {
  case TokenKind::Empty:
    return "Empty";
  case TokenKind::Comment:
    return "Comment";
  case TokenKind::String:
    return "String";
  case TokenKind::Number:
    return "Number";
  case TokenKind::Identifier:
    return "Identifier";
  case TokenKind::Eof:
    return "Eof";
  case TokenKind::Namespace:
    return "Namespace";
  case TokenKind::Enum:
    return "Enum";
  case TokenKind::OpenBraces:
    return "OpenBraces";
  case TokenKind::CloseBraces:
    return "CloseBraces";
  case TokenKind::Semicolon:
    return "Semicolon";
  case TokenKind::Period:
    return "Period";
  }
}
