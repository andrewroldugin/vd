# VD - Vigenere decipher for english text
## Algorithm description
[Friedman test](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher#Friedman_test)
## How to use:
```
./vd <FILE>
```
Test files to decipher:
```
data/ciphered.txt (key: SCUBASCUBA, original text in data/clear.txt)
data/shak_simpson.txt (key: SIMPSON, original text in data/shak.txt)
```
## How to build
### Requirements:
It requires `gtest` to be installed on your system for building tests.

To install required packages on ArchLinux run the following:
```
sudo pacman -S gtest
```
### Building:
To build both program & tests:
```
make
```
To build only decipher program without tests:
```
make vd
```
To build & run tests:
```
make test
```
## Limitations:
Punctuation preserving isn't supported.
