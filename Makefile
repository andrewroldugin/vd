# $@ name of the target
# $^ name of all prerequisites with duplicates removed
# $< name of the first prerequisite

PRJ = vd
TESTS = $(PRJ)_tests
CP = cp $< $@
CXXFLAGS = -Og -Wextra -Wall -Isrc -std=c++1z
LDLIBS = -lstdc++

all: $(PRJ) $(TESTS)

$(PRJ): src/main
	$(CP)

$(TESTS): src/main_tests
	$(CP)

src/main_tests: LDLIBS += -lgtest

test: $(TESTS)
	@./$<

clean:
	find src -name *.o -delete
	rm -f src/main src/main_tests $(PRJ) $(TESTS)

.PHONY: all test clean
