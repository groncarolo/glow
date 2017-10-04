#ifndef GLOW_SUPPORT_SUPPORT_H
#define GLOW_SUPPORT_SUPPORT_H

#include "llvm/ADT/ArrayRef.h"

#include <chrono>
#include <iostream>
#include <sstream>

namespace std {
/// Convert the ptr \p ptr into an ascii representation in the format "0xFFF..."
std::string to_string(void *ptr);
/// Converts LLVM's StringRef to std::string.
std::string to_string(const llvm::StringRef sr);
} // namespace std

namespace glow {

/// \returns the escaped content of string \p str.
/// The char '\n' becomes '\'+'n' and quotes are handled correctly.
std::string escapeDottyString(const std::string &str);

/// Add quotes to the string \p in.
inline std::string quote(const std::string &in) { return '"' + in + '"'; }

/// A helper class that builds a textual descriptor of a group of parameters.
class DescriptionBuilder {
  std::stringstream repr_;

public:
  DescriptionBuilder(const std::string &name) { repr_ << name << '\n'; }

  DescriptionBuilder &addParam(const std::string &name, const char *value) {
    repr_ << name << " : " << value << '\n';
    return *this;
  }

  template <typename T_,
            typename = typename std::enable_if<std::is_scalar<T_>::value>::type>
  DescriptionBuilder &addParam(const std::string &name, T_ value) {
    repr_ << name << " : " << value << '\n';
    return *this;
  }

  template <typename T_, typename = typename std::enable_if<
                             !std::is_scalar<T_>::value>::type>
  DescriptionBuilder &addParam(const std::string &name, const T_ &value) {
    repr_ << name << " : " << std::to_string(value) << '\n';
    return *this;
  }

  operator std::string() const { return repr_.str(); }
};

} // namespace glow

#endif // GLOW_SUPPORT_SUPPORT_H
