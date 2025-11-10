/*
Performance Benchmark: Hashmap vs Linear Search (Baseline)
Measures the performance improvement from using hashmaps for state tracking
*/

#include <iostream>
#include <chrono>
#include <vector>
#include <memory>
#include <iomanip>
#include "../../include/formula.h"
#include "../../include/satsolve.h"
#include "../../include/dpll.h"
#include "satsolve_baseline.h"
#include "dpll_baseline.h"

using namespace std;
using namespace std::chrono;

struct BenchmarkResult {
    string testName;
    int numVariables;
    int numClauses;
    double hashmapTime;
    double baselineTime;
    double speedup;
    double percentImprovement;
};

// Run multiple iterations and return average
BenchmarkResult runBenchmark(string testName, int numVars, vector<shared_ptr<Formula>> formula, int iterations = 5) {
    BenchmarkResult result;
    result.testName = testName;
    result.numVariables = numVars;
    result.numClauses = formula.size();
    
    double totalHashmapTime = 0.0;
    double totalBaselineTime = 0.0;
    
    // Run multiple iterations
    for (int i = 0; i < iterations; i++) {
        // Benchmark HASHMAP version
        auto start = high_resolution_clock::now();
        dpllSatSolve(formula);
        auto end = high_resolution_clock::now();
        totalHashmapTime += duration_cast<microseconds>(end - start).count() / 1000.0;
        
        // Benchmark BASELINE version
        start = high_resolution_clock::now();
        dpllSatSolve_baseline(formula);
        end = high_resolution_clock::now();
        totalBaselineTime += duration_cast<microseconds>(end - start).count() / 1000.0;
    }
    
    // Average the results
    result.hashmapTime = totalHashmapTime / iterations;
    result.baselineTime = totalBaselineTime / iterations;
    
    // Calculate speedup
    result.speedup = result.baselineTime / result.hashmapTime;
    result.percentImprovement = ((result.baselineTime - result.hashmapTime) / result.baselineTime) * 100.0;
    
    return result;
}

void printResults(const vector<BenchmarkResult>& results) {
    cout << "\n========================================\n";
    cout << "  PERFORMANCE BENCHMARK RESULTS\n";
    cout << "  Hashmap vs Linear Search (Baseline)\n";
    cout << "  (Average of 5 iterations per test)\n";
    cout << "========================================\n\n";
    
    cout << left << setw(20) << "Test Name"
         << setw(12) << "Variables"
         << setw(12) << "Clauses"
         << setw(15) << "Hashmap (ms)"
         << setw(15) << "Baseline (ms)"
         << setw(12) << "Speedup"
         << setw(15) << "Improvement"
         << "\n";
    cout << string(100, '-') << "\n";
    
    double totalImprovement = 0.0;
    
    for (const auto& result : results) {
        cout << left << setw(20) << result.testName
             << setw(12) << result.numVariables
             << setw(12) << result.numClauses
             << setw(15) << fixed << setprecision(3) << result.hashmapTime
             << setw(15) << fixed << setprecision(3) << result.baselineTime
             << setw(12) << fixed << setprecision(2) << result.speedup << "x"
             << setw(15) << fixed << setprecision(2) << result.percentImprovement << "%"
             << "\n";
        
        totalImprovement += result.percentImprovement;
    }
    
    cout << string(100, '-') << "\n";
    cout << "Average Improvement: " << fixed << setprecision(2) 
         << (totalImprovement / results.size()) << "%\n";
    cout << "========================================\n\n";
}

vector<shared_ptr<Formula>> createTestFormula(int numVariables, int numClauses) {
    vector<shared_ptr<Formula>> clauses;
    
    // Create variables
    vector<shared_ptr<Formula>> variables;
    for (int i = 0; i < numVariables; i++) {
        variables.push_back(make_shared<Atom>("x" + to_string(i)));
    }
    
    // Create 3-SAT style clauses
    for (int i = 0; i < numClauses; i++) {
        vector<shared_ptr<Formula>> literals;
        
        // Each clause has 3 literals
        for (int j = 0; j < 3; j++) {
            int varIdx = (i * 3 + j) % numVariables;
            shared_ptr<Formula> var = variables[varIdx];
            
            // Randomly negate
            if ((i + j) % 2 == 0) {
                literals.push_back(var->negationOf());
            } else {
                literals.push_back(var);
            }
        }
        
        shared_ptr<Formula> clause = make_shared<Or>(literals);
        clauses.push_back(clause);
    }
    
    return clauses;
}

int main() {
    vector<BenchmarkResult> results;
    
    cout << "Running SAT Solver Performance Benchmarks...\n";
    cout << "Comparing Hashmap-based vs Linear Search implementations\n";
    cout << "Each test runs 5 iterations and reports the average\n\n";
    
    cout << "Running small test (50 variables, 100 clauses)...\n";
    auto smallFormula = createTestFormula(50, 100);
    results.push_back(runBenchmark("Small", 50, smallFormula));
    
    cout << "Running medium test (100 variables, 300 clauses)...\n";
    auto mediumFormula = createTestFormula(100, 300);
    results.push_back(runBenchmark("Medium", 100, mediumFormula));
    
    cout << "Running large test (200 variables, 600 clauses)...\n";
    auto largeFormula = createTestFormula(200, 600);
    results.push_back(runBenchmark("Large", 200, largeFormula));
    
    cout << "Running extra large test (500 variables, 1500 clauses)...\n";
    auto xlargeFormula = createTestFormula(500, 1500);
    results.push_back(runBenchmark("Extra Large", 500, xlargeFormula));
    
    printResults(results);
    
    return 0;
}