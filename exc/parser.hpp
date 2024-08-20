#pragma once

#include <optional>

#include "code.hpp"

#include "bee/file_path.hpp"
#include "bee/or_error.hpp"

namespace exc {

struct Parser {
 public:
  static bee::OrError<Code> parse(
    const bee::FilePath& src_path,
    const std::optional<std::string_view>& content = std::nullopt);
};

} // namespace exc
