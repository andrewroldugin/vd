#include <iostream>

#include "vd/decipher.h"

using std::endl;
using namespace vd;

int main(int argc, char* argv[]) {
  if (argc > 1) {
    try {
      auto text = PrepareText(ReadText(argv[1]));
      auto key = FindKey(text, FindKeyLength(text));
      auto deciphered = DecipherText(text, key);
      std::cout << "Key: " << endl << key << endl << endl
                << "Text: " << endl << deciphered << endl;
    } catch (const std::exception& e) {
      std::cerr << e.what() << endl;
    }
  } else {
    std::cout << "Usage: vd <FILE>" << endl
              << "Vigenere decipher for english text" << endl << endl
              << "  <FILE> - file to decipher" << endl;
  }
  return 0;
}
