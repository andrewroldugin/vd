#include <gmock/gmock.h>
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

TEST(DecipherTest, ReadFileLines) {
  auto actual = ReadLines("data/file.txt");
  std::vector<std::string> expected = {"one", "two", "three"};
  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(DecipherTest, ReadLinesFailed) {
  std::string filename = "data/nonexisting.txt";
  try {
    ReadLines(filename);
    FAIL() << "ReadLines() should throw an error\n";
  } catch (const std::runtime_error& e) {
    EXPECT_EQ("Failed to read " + filename, e.what());
  }
}

TEST(DecipherTest, FindKey) {
  auto text = ReadText("data/scuba_ciphered.txt");
  EXPECT_EQ("SCUBA", FindKey(text, 5));
  std::transform(text.begin(), text.end(), text.begin(), ::tolower);
  EXPECT_EQ("SCUBA", FindKey(text, 5));
}
