#include "vd/decipher.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <limits>
#include <numeric>
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
  std::string key;
  key.reserve(keylength);
  for (int index = 0; index < keylength; ++index) {
    key.push_back(FindKeyChar(text, index, keylength));
  }
  return key;
}

char vd::FindKeyChar(const std::string& text, int offset, int keylength) {
  std::array<int, ALPHABET_SIZE> counters;
  std::array<double, ALPHABET_SIZE> letter_freq = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
  };
  counters.fill(0);
  int count = 0;
  for (std::size_t index = offset; index < text.size(); index += keylength) {
    char c = text[index];
    if (std::isalpha(c)) {
      ++count;
      ++counters[std::tolower(c) - 'a'];
    }
  }
  int caeser_key = 0;
  double min_chi = std::numeric_limits<double>::max();
  for (int step = 0; step < ALPHABET_SIZE; ++step) {
    // calc chi squared
    // https://en.wikipedia.org/wiki/Chi-squared_test
    double chi = 0.;
    for (int index = 0; index < ALPHABET_SIZE; ++index) {
      int actual = counters[(step + index) % ALPHABET_SIZE];
      if (actual > 0) {
        double expected = (letter_freq[index] / 100.) * count;
        chi += pow(expected - actual, 2) / expected;
      }
    }
    if (chi < min_chi) {
      min_chi = chi;
      caeser_key = step;
    }
  }
  return 'A' + caeser_key;
}

// Calc index of coincidence
// For details see: https://en.wikipedia.org/wiki/Index_of_coincidence
double vd::CalcIC(const std::string& text, int offset, int keylength) {
  std::array<int, ALPHABET_SIZE> counters;
  counters.fill(0);
  int count = 0;
  for (std::size_t index = offset; index < text.size(); index += keylength) {
    char c = text[index];
    if (std::isalpha(c)) {
      ++count;
      ++counters[std::tolower(c) - 'a'];
    }
  }
  return std::accumulate(counters.begin(), counters.end(), 0.,
         [count](double sum, int x) {
           return sum + (x / double(count)) * ((x - 1) / double(count - 1));
         }) * ALPHABET_SIZE;
}

int vd::FindKeyLength(const std::string& text) {
  int out = 0;
  double min_freqoffset = 0.;
  for (int keylength = 1; keylength <= MAX_KEY_LENGTH; ++keylength) {
    double ic = 0.;
    for (int offset = 0; offset < keylength; ++offset) {
      ic += CalcIC(text, offset, keylength);
    }
    ic /= keylength;
    double freqoffset = std::abs(IC_ENGLISH - ic);
    if (!out || freqoffset < min_freqoffset) {
      min_freqoffset = freqoffset;
      out = keylength;
    }
  }
  return out;
}
