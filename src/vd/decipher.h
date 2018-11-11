#ifndef VD_DECIPHER_H
#define VD_DECIPHER_H

const int ALPHABET_SIZE = 26;

#include <string>
#include <vector>

namespace vd {
  std::string ReadText(const std::string& filename);
  std::vector<std::string> ReadLines(const std::string& filename);
  std::string FindKey(const std::string& text, int keylength);
  char FindKeyChar(const std::string& text, int offset, int keylength);
}

#endif  // VD_DECIPHER_H
