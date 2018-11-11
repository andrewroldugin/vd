#ifndef VD_DECIPHER_H
#define VD_DECIPHER_H

#include <string>
#include <vector>

namespace vd {
  std::string ReadText(const std::string& filename);
  std::vector<std::string> ReadLines(const std::string& filename);
}

#endif  // VD_DECIPHER_H
