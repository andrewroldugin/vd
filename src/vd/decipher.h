#ifndef VD_DECIPHER_H
#define VD_DECIPHER_H

const int ALPHABET_SIZE = 26;
const char ALPHABET_START = 'A';
const int MAX_KEY_LENGTH = 12;
const double IC_ENGLISH = 1.73;

#include <array>
#include <string>
#include <vector>

namespace vd {
  std::string ReadText(const std::string& filename);
  std::string FindKey(const std::string& text, int keylength);
  char FindKeyChar(const std::string& text, int offset, int keylength);
  int FindKeyLength(const std::string& text);
  double CalcIC(const std::string& text, int offset, int keylength);
  template<typename T>
  int CountLetters(const std::string& text, int offset, int keylength,
                   std::array<T, ALPHABET_SIZE>& a);
  std::string PrepareText(const std::string& text);
  std::string DecipherText(const std::string& text, const std::string& key);
}

#endif  // VD_DECIPHER_H
