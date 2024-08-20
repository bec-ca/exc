#include "code.hpp"

#include "bee/format.hpp"
#include "bee/string_util.hpp"

namespace exc {

////////////////////////////////////////////////////////////////////////////////
// Namespace
//

std::string Namespace::to_string() const { return bee::join(parts, "."); }
std::string Namespace::to_cpp_ns() const { return bee::join(parts, "::"); }

////////////////////////////////////////////////////////////////////////////////
// Code
//

std::string Code::to_string() const
{
  std::string out = F("file $\nns $\n", src, ns);
  for (const auto& [name, legs] : enums) {
    out += F("enum $:\n", name);
    for (const auto& leg : legs) { out += F("  $\n", leg); }
  }
  return out;
}

} // namespace exc
