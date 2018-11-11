#include "vd/decipher.h"

#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string vd::ReadText(const std::string& filename) {
  std::ifstream t(filename);
  if (t.fail()) throw std::runtime_error("Failed to read " + filename);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

std::vector<std::string> vd::ReadLines(const std::string& filename) {
  std::ifstream file(filename);
  if (file.fail()) throw std::runtime_error("Failed to read " + filename);
  std::string str;
  std::vector<std::string> lines;
  while (std::getline(file, str)) {
    lines.push_back(str);
  }
  return lines;
}

std::string vd::FindKey(const std::string& text, int keylength) {
  std::string key(keylength, 'x');
  for (int index = 0; index < keylength; ++index) {
    key[index] = FindKeyChar(text, index, keylength);
  }
  return key;
}

char vd::FindKeyChar(const std::string& text, int offset, int keylength) {
  std::array<int, 26> counters;
  counters.fill(0);
  for (std::size_t index = offset; index < text.size(); index += keylength) {
    char c = text[index];
    if (std::isalpha(c)) {
      ++counters[std::tolower(c) - 'a'];
    }
  }
  auto max_iter = std::max_element(counters.begin(), counters.end());
  char probably_e = 'a' + std::distance(counters.begin(), max_iter);
  return probably_e - 'e' + 'A';
}
