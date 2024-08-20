#include "compiler.hpp"

#include "bee/testing.hpp"
#include "clang_format/clang_format.hpp"

namespace exc {
namespace {

constexpr auto sep = "-----------------";

TEST(basic)
{
  auto out = Compiler::compile(Code{
    .src = bee::FilePath("test.exc"),
    .ns = {{"ns_foo"}},
    .enums =
      {
        {"foobar", {"abc", "dce", "efg"}},
        {"baz", {"qwe", "asd", "zxc"}},
      },
  });
  P(sep);
  P("header:");
  P(out.header_path);
  P(clang_format::ClangFormat::format_code(out.header, out.header_path)
      .value());
  P(sep);
  P("src:");
  P(out.src_path);
  P(clang_format::ClangFormat::format_code(out.src, out.src_path).value());
}

} // namespace
} // namespace exc
