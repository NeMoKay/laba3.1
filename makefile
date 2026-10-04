CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iincude -I/opt/homebrew/include -I/usr/local/include
LDFLAGS = -L/opt/homebrew/lib -L/usr/local/lib -lgtest -lgtest_main -pthread
DIR = /Users/kay/Proga/labs/3/laba3.1

REGULAR_TESTS = $(filter-out tests/TEST_Load.cpp, $(wildcard tests/*.cpp))

main:
	$(CXX) $(CXXFLAGS) src/main.cpp -o main
	./main

test:
	$(CXX) $(CXXFLAGS) $(REGULAR_TESTS) -o test_bin $(LDFLAGS)
	./test_bin

load_test:
	$(CXX) $(CXXFLAGS) tests/TEST_Load.cpp -o load_test_bin $(LDFLAGS)
	./load_test_bin

clean:
	rm -f main test_bin load_test_bin
	find $(DIR) -type f -name "*.o" -delete
	find $(DIR) -type f -name "*.out" -delete
	find $(DIR) -type f -name "*.gch" -delete
	find $(DIR) -type d -name "*.dSYM" -exec rm -rf {} +