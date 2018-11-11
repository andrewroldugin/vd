#include "vd/decipher.h"

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
