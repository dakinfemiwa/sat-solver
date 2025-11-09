CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -Iinclude

# Directories
SRC_DIR = src
UTIL_DIR = $(SRC_DIR)/util
TEST_DIR = tests/alternative_solution

# Source files
FORMULA_SOURCE = $(UTIL_DIR)/formula.cpp
OPTIMIZED_SOURCES = $(UTIL_DIR)/satsolve.cpp $(SRC_DIR)/dpll.cpp
BASELINE_SOURCES = $(TEST_DIR)/satsolve_baseline.cpp $(TEST_DIR)/dpll_baseline.cpp
BENCHMARK_SOURCE = $(TEST_DIR)/benchmark.cpp
ACCURACY_SOURCE = $(TEST_DIR)/accuracy_tests.cpp

# Object files
FORMULA_OBJ = formula.o
OPTIMIZED_OBJS = satsolve.o dpll.o
BASELINE_OBJS = satsolve_baseline.o dpll_baseline.o
BENCHMARK_OBJ = benchmark.o
ACCURACY_OBJ = accuracy_tests.o

# Targets
BENCHMARK_TARGET = benchmark
ACCURACY_TARGET = accuracy_tests

.PHONY: all test run run-all clean help

all: $(BENCHMARK_TARGET) $(ACCURACY_TARGET)

$(BENCHMARK_TARGET): $(FORMULA_OBJ) $(OPTIMIZED_OBJS) $(BASELINE_OBJS) $(BENCHMARK_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Benchmark built successfully!"

$(ACCURACY_TARGET): $(FORMULA_OBJ) $(OPTIMIZED_OBJS) $(BASELINE_OBJS) $(ACCURACY_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Accuracy tests built successfully!"

formula.o: $(UTIL_DIR)/formula.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

satsolve.o: $(UTIL_DIR)/satsolve.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

dpll.o: $(SRC_DIR)/dpll.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

satsolve_baseline.o: $(TEST_DIR)/satsolve_baseline.cpp $(TEST_DIR)/satsolve_baseline.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

dpll_baseline.o: $(TEST_DIR)/dpll_baseline.cpp $(TEST_DIR)/dpll_baseline.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

benchmark.o: $(TEST_DIR)/benchmark.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

accuracy_tests.o: $(TEST_DIR)/accuracy_tests.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(ACCURACY_TARGET)
	@echo ""
	@echo "========================================="
	@echo "Running Accuracy Tests"
	@echo "========================================="
	./$(ACCURACY_TARGET)

run: $(BENCHMARK_TARGET)
	@echo ""
	@echo "========================================="
	@echo "Running Performance Benchmark"
	@echo "========================================="
	./$(BENCHMARK_TARGET)

run-all: test run

clean:
	rm -f $(BENCHMARK_TARGET) $(ACCURACY_TARGET) *.o
	@echo "Cleaned build artifacts"

help:
	@echo "SAT Solver Benchmark Makefile"
	@echo "=============================="
	@echo "Targets:"
	@echo "  make           - Build benchmark and accuracy tests"
	@echo "  make test      - Run accuracy tests"
	@echo "  make run       - Run performance benchmark"
	@echo "  make run-all   - Run both tests and benchmark"
	@echo "  make clean     - Remove build artifacts"
	@echo "  make help      - Show this help message"