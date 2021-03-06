#include "vd/decipher.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>

std::string vd::DecipherText(const std::string& text, const std::string& key) {
  std::string out;
  out.reserve(text.size());
  const int ASIZE = ALPHABET_SIZE;
  const int ASTART = ALPHABET_START;
  for (std::size_t i = 0; i < text.size(); ++i)
    out.push_back(ASTART + (text[i] - key[i % key.size()] + ASIZE) % ASIZE);
  return out;
}

std::string vd::PrepareText(const std::string& text) {
  std::string out;
  // imperative way of filtermap
  out.reserve(std::count_if(text.begin(), text.end(), isalpha));
  for (auto x:text) if (std::isalpha(x)) out.push_back(std::toupper(x));
  return out;
}

std::string vd::ReadText(const std::string& filename) {
  std::ifstream t(filename);
  if (t.fail()) throw std::runtime_error("Failed to read " + filename);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

std::string vd::FindKey(const std::string& text, int keylength) {
  std::string key;
  key.reserve(keylength);
  for (int index = 0; index < keylength; ++index) {
    key.push_back(FindKeyChar(text, index, keylength));
  }
  return key;
}

int vd::CountLetters(const std::string& text, int offset, int keylength,
                     std::array<int, ALPHABET_SIZE>& a) {
  a.fill(0);
  for (std::size_t index = offset; index < text.size(); index += keylength)
    ++a[text[index] - ALPHABET_START];
  return (text.size() - offset + keylength - 1) / keylength;
}


char vd::FindKeyChar(const std::string& text, int offset, int keylength) {
  std::array<double, ALPHABET_SIZE> freq;
  const std::array<double, ALPHABET_SIZE> letter_freq = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
  };
  std::array<int, ALPHABET_SIZE> counters;
  int count = CountLetters(text, offset, keylength, counters);
  std::transform(counters.begin(), counters.end(), freq.begin(),
                 [count](double x){return x / count * 100.;});
  int caeser_key = 0;
  double min_chi = std::numeric_limits<double>::max();
  for (int step = 0; step < ALPHABET_SIZE; ++step) {
    // calc chi squared
    // https://en.wikipedia.org/wiki/Chi-squared_test
    double chi = 0.;
    for (int index = 0; index < ALPHABET_SIZE; ++index) {
      double actual = freq[(step + index) % ALPHABET_SIZE];
      double expected = letter_freq[index];
      chi += pow(expected - actual, 2) / expected;
    }
    if (chi < min_chi) {
      min_chi = chi;
      caeser_key = step;
    }
  }
  return ALPHABET_START + caeser_key;
}

// Calc index of coincidence
// For details see: https://en.wikipedia.org/wiki/Index_of_coincidence
double vd::CalcIC(const std::string& text, int offset, int keylength) {
  std::array<int, ALPHABET_SIZE> counters;
  int count = CountLetters(text, offset, keylength, counters);
  return std::accumulate(counters.begin(), counters.end(), 0.,
         [count](double sum, double x) {
           return sum + (x / count) * ((x - 1) / (count - 1));
         }) * ALPHABET_SIZE;
}

int vd::FindKeyLength(const std::string& text) {
  int out = 0;
  double min = std::numeric_limits<double>::max();
  for (int keylength = 1; keylength <= MAX_KEY_LENGTH; ++keylength) {
    double ic = 0.;
    for (int offset = 0; offset < keylength; ++offset) {
      ic += CalcIC(text, offset, keylength);
    }
    ic /= keylength;
    double x = std::abs(IC_ENGLISH - ic);
    if (x < min) {
      min = x;
      out = keylength;
    }
  }
  return out;
}
