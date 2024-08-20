
#include "example.generated.hpp"

namespace exc {}

const char* exc::Enum<exc::Example>::to_string(exc::Example e)
{
  switch (e) {
  case Example::Apple:
    return "Apple";
  case Example::Orange:
    return "Orange";
  case Example::Pineapple:
    return "Pineapple";
  case Example::Banana:
    return "Banana";
  case Example::Extra:
    return "Extra";
  case Example::OneMore:
    return "OneMore";
  case Example::Other:
    return "Other";
  case Example::LastOne:
    return "LastOne";
  }
}
