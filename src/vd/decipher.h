#ifndef VD_DECIPHER_H
#define VD_DECIPHER_H

const int ALPHABET_SIZE = 26;
const int MAX_KEY_LENGTH = 12;
const double IC_ENGLISH = 1.73;

#include <string>
#include <vector>

namespace vd {
  std::string ReadText(const std::string& filename);
  std::vector<std::string> ReadLines(const std::string& filename);
  std::string FindKey(const std::string& text, int keylength);
  char FindKeyChar(const std::string& text, int offset, int keylength);
  int FindKeyLength(const std::string& text);
  double CalcIC(const std::string& text, int offset, int keylength);
}

#endif  // VD_DECIPHER_H
