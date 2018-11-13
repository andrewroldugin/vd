#include <gtest/gtest.h>

#include "vd/decipher.h"

using namespace vd;

TEST(DecipherTest, ReadFileToString) {
  std::string expected = "one\ntwo\nthree\n";
  EXPECT_EQ(expected, ReadText("data/file.txt"));
}

TEST(DecipherTest, ReadFileToStringFailed) {
  std::string filename = "data/nonexisting.txt";
  try {
    ReadText(filename);
    FAIL() << "ReadFileToString() should throw an error\n";
  } catch (const std::runtime_error& e) {
    EXPECT_EQ("Failed to read " + filename, e.what());
  }
}

TEST(DecipherTest, FindKey) {
  auto text = ReadText("data/scuba_ciphered.txt");
  EXPECT_EQ("SCUBA", FindKey(text, 5));
}

TEST(DecipherTest, CalcIC) {
  EXPECT_NEAR(2.31, CalcIC("HELLOWORLD", 0, 1), 1e-2);
}

TEST(DecipherTest, FindKeyLength) {
  std::string key = "SIMPSON";
  EXPECT_EQ(key.size(), FindKeyLength(ReadText("data/shak_simpson.txt")));
}

TEST(DecipherTest, PrepareText) {
  EXPECT_EQ("HELLOWORLD", PrepareText("Hello,._[]World!<>()"));
}

TEST(DecipherTest, DecipherText) {
  std::string key = "VIGENERE";
  std::string text = "OWHIBVESOBUFRXYEOQYXUIHYZAZMBR";
  std::string expected = "TOBEORNOTTOBETHATISTHEQUESTION";
  EXPECT_EQ(expected, DecipherText(text, key));
}

TEST(FunctionalTest, DecipherText) {
  auto text = PrepareText(ReadText("data/shak_simpson.txt"));
  EXPECT_EQ(ReadText("data/shak.txt"),
            DecipherText(text, FindKey(text, FindKeyLength(text))));
}

TEST(FunctionalTest, DecipherTextWithPunctuation) {
  auto text = PrepareText(ReadText("data/ciphered.txt"));
  // decipher with punctuation preserving isn't supported yet
  // so compare result with prepared clear text
  EXPECT_EQ(PrepareText(ReadText("data/clear.txt")),
            DecipherText(text, FindKey(text, FindKeyLength(text))));
}
