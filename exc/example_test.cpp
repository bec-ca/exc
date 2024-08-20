#include "example.generated.hpp"

#include "bee/testing.hpp"

namespace exc {
namespace {

TEST(to_string)
{
  for (const auto& e : exc::Enum<Example>::all) { P(e); }
}

} // namespace
} // namespace exc
