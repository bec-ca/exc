#pragma once

#include <string>

#include "code.hpp"

namespace exc {

struct Compiled {
  bee::FilePath header_path;
  std::string header;
  bee::FilePath src_path;
  std::string src;
};

struct Compiler {
 public:
  static Compiled compile(const Code& code);
};

} // namespace exc
