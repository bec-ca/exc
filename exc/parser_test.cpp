#include "parser.hpp"

#include "bee/testing.hpp"

namespace exc {
namespace {

TEST(basic)
{
  constexpr auto code = R"(
  ns foo.bar

  enum Something {
    foo
    bar
    other
  }

  )";
  auto out = Parser::parse(bee::FilePath("test.exc"), code);
  P(out);
}

} // namespace
} // namespace exc
