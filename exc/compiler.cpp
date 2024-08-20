#include "compiler.hpp"

#include "bee/print.hpp"
#include "bee/string_util.hpp"

namespace exc {
namespace {

constexpr auto specializations_template = R"(
template <> struct exc::Enum<{{NS}}::{{NAME}}> {
 public:
  using {{NAME}} = {{NS}}::{{NAME}};

  static const char* to_string({{NAME}} t);

  static constexpr size_t count = {{COUNT}};

  static constexpr std::array<{{NAME}}, count> all = {
    {{QUALIFIED_LEGS}}
  };
};

static_assert(exc::is_ex_enum<{{NS}}::{{NAME}}>);
)";

constexpr auto header_template = R"(
#pragma once

#include <array>
#include <cstdint>

#include "exc/enum.hpp"

namespace {{NS}} {

{{DECLS}}

}

{{SPECIALIZATIONS}}

)";

constexpr auto src_template = R"(
#include "{{HEADER_PATH}}"

namespace {{NS}} { }

{{IMPLS}}

)";

constexpr auto decl_template = R"(

enum class {{NAME}} {
  {{LEGS}}
};

)";

constexpr auto impl_template = R"(

const char* exc::Enum<{{NS}}::{{NAME}}>::to_string({{NS}}::{{NAME}} e) {
  switch(e) {
    {{STR_CASES}}
  }
}

)";

std::string format_code(
  const std::string_view& tmpl,
  const std::map<std::string, std::string>& replaces)
{
  std::string out(tmpl);
  for (const auto& [key, value] : replaces) {
    out = bee::find_and_replace(out, key, value);
  }

  return out;
}

} // namespace

Compiled Compiler::compile(const Code& code)
{
  std::string decls;
  std::string impls;
  std::string specializations;
  for (const auto& [name, legs] : code.enums) {
    std::string enum_legs;
    std::string qualifed_legs;
    std::string str_cases;
    for (const auto& leg : legs) {
      auto q = F("$::$", name, leg);
      enum_legs += F("$,\n", leg);
      str_cases += F("case $: return \"$\";\n", q, leg);
      qualifed_legs += F("$,\n", q);
    }
    std::map<std::string, std::string> replaces;
    replaces.emplace("{{NS}}", code.ns.to_cpp_ns());
    replaces.emplace("{{NAME}}", name);
    replaces.emplace("{{COUNT}}", F(legs.size()));
    replaces.emplace("{{LEGS}}", enum_legs);
    replaces.emplace("{{QUALIFIED_LEGS}}", qualifed_legs);
    replaces.emplace("{{STR_CASES}}", str_cases);
    decls += format_code(decl_template, replaces);
    impls += format_code(impl_template, replaces);
    specializations += format_code(specializations_template, replaces);
  }

  auto stem = code.src.stem();
  auto header_path = F("$.generated.hpp", stem);
  auto src_path = F("$.generated.cpp", stem);

  std::map<std::string, std::string> replaces;
  replaces.emplace("{{NS}}", code.ns.to_cpp_ns());
  replaces.emplace("{{HEADER_PATH}}", header_path);
  replaces.emplace("{{DECLS}}", decls);
  replaces.emplace("{{IMPLS}}", impls);
  replaces.emplace("{{SPECIALIZATIONS}}", specializations);

  return Compiled{
    .header_path = code.src.parent() / header_path,
    .header = format_code(header_template, replaces),
    .src_path = code.src.parent() / src_path,
    .src = format_code(src_template, replaces)};
}

} // namespace exc
