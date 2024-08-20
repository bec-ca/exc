#include "parser.hpp"

#include <utility>

#include "token_kind.generated.hpp"

#include "bee/file_reader.hpp"
#include "bee/string_util.hpp"
#include "tokenizer/token_reader.hpp"
#include "tokenizer/tokenizer.hpp"
#include "tokenizer/typed_token.hpp"

namespace exc {
namespace {

using Token = tokenizer::TypedToken<TokenKind>;

auto create_tokenizer()
{
  const std::vector<std::pair<std::string, TokenKind>> operators = {
    {"{", TokenKind::OpenBraces},
    {"}", TokenKind::CloseBraces},
    {";", TokenKind::Semicolon},
    {".", TokenKind::Period},
  };
  const std::map<std::string, TokenKind> keywords{
    {"ns", TokenKind::Namespace},
    {"enum", TokenKind::Enum},
  };
  return tokenizer::TypedTokenizer<TokenKind>(operators, keywords);
}

bee::OrError<Code> compile_impl(
  const bee::FilePath& src_path, const std::string_view& content)
{
  auto tok = create_tokenizer();
  bail(tokens, tok.tokenize(content, src_path));
  tokenizer::TokenReader reader(tokens, true);
  std::optional<Namespace> ns_opt;
  std::vector<EnumDecl> enums;
  while (!reader.eof()) {
    const auto& tok = reader.read();
    switch (tok.kind) {
    case TokenKind::Namespace: {
      if (ns_opt.has_value()) { return EF("Namespace declared twice"); }
      std::vector<std::string> ns_parts;
      while (true) {
        const auto& tok2 = reader.read();
        if (tok2.kind != TokenKind::Identifier) {
          return EF("Expected Identifier after 'ns'");
        }
        ns_parts.push_back(tok2.content);
        const auto& tok3 = reader.peek();
        if (tok3.kind != TokenKind::Period) { break; }
        reader.skip();
      }
      ns_opt = Namespace{.parts = std::move(ns_parts)};
    } break;
    case TokenKind::Enum: {
      const auto& name = reader.read();
      if (name.kind != TokenKind::Identifier) {
        return EF("Expected identifier after enum, got $", name);
      }
      const auto& open_brac = reader.read();
      if (open_brac.kind != TokenKind::OpenBraces) {
        return EF("Expected open braces after enum name, got $", name);
      }
      std::vector<std::string> legs;
      while (true) {
        const auto& leg = reader.read();
        if (leg.kind == TokenKind::CloseBraces) {
          break;
        } else if (leg.kind == TokenKind::Identifier) {
          legs.push_back(leg.content);
        } else {
          return EF("Unexpected token inside enum declaration: $", leg);
        }
      }
      enums.emplace_back(std::move(name.content), std::move(legs));
    } break;
    default:
      return EF("Unexpected token: $", tok);
    }
  }
  if (!ns_opt.has_value()) { return EF("Namespace not declared"); }
  return Code{.src = src_path, .ns = *ns_opt, .enums = enums};
}

} // namespace

bee::OrError<Code> Parser::parse(
  const bee::FilePath& src_path, const std::optional<std::string_view>& content)
{
  if (content.has_value()) {
    return compile_impl(src_path, *content);
  } else {
    bail(content, bee::FileReader::read_file(src_path));
    return compile_impl(src_path, content);
  }
}

} // namespace exc
