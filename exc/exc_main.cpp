#include "compiler.hpp"
#include "parser.hpp"

#include "bee/file_writer.hpp"
#include "clang_format/clang_format.hpp"
#include "command/command_builder.hpp"
#include "command/file_path.hpp"
#include "command/group_builder.hpp"

namespace exc {
namespace {

bee::OrError<> compile_main(const bee::FilePath& src_path)
{
  bail(code, Parser::parse(src_path));
  auto compiled = Compiler::compile(code);

  bail_unit(bee::FileWriter::write_file(compiled.header_path, compiled.header));
  bail_unit(bee::FileWriter::write_file(compiled.src_path, compiled.src));

  bail_unit(clang_format::ClangFormat::format_file(compiled.header_path));
  bail_unit(clang_format::ClangFormat::format_file(compiled.src_path));

  return bee::ok();
}

command::Cmd compile_cmd()
{
  using namespace command::flags;
  auto builder = command::CommandBuilder("Compile EXtended C code");
  auto src_path = builder.required_anon(command::flags::FilePath, "SOURCE");
  return builder.run(
    [=]() -> bee::OrError<> { return compile_main(*src_path); });
}

int main(int argc, char* argv[])
{
  using namespace command::flags;
  return command::GroupBuilder("EXtended C compiler")
    .cmd("compile", compile_cmd())
    .build()
    .main(argc, argv);
}

} // namespace
} // namespace exc

int main(int argc, char* argv[]) { return exc::main(argc, argv); }
