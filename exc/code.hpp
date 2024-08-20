#pragma once

#include <map>
#include <string>
#include <vector>

#include "bee/file_path.hpp"

namespace exc {

struct Namespace {
  std::vector<std::string> parts;

  std::string to_string() const;
  std::string to_cpp_ns() const;
};

struct EnumDecl {
  std::string name;
  std::vector<std::string> legs;
};

struct Code {
  bee::FilePath src;

  Namespace ns;
  std::vector<EnumDecl> enums;

  std::string to_string() const;
};

} // namespace exc
