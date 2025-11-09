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

BenchmarkResult runBenchmark(string testName, int numVars, vector<shared_ptr<Formula>> formula) {
    BenchmarkResult result;
    result.testName = testName;
    result.numVariables = numVars;  // Now properly set
    result.numClauses = formula.size();
    
    // Benchmark HASHMAP version
    auto start = high_resolution_clock::now();
    dpllSatSolve(formula);  // Your optimized version
    auto end = high_resolution_clock::now();
    result.hashmapTime = duration_cast<microseconds>(end - start).count() / 1000.0; // ms
    
    // Benchmark BASELINE version (linear search)
    start = high_resolution_clock::now();
    dpllSatSolve_baseline(formula);  // Baseline version
    end = high_resolution_clock::now();
    result.baselineTime = duration_cast<microseconds>(end - start).count() / 1000.0; // ms
    
    // Calculate speedup
    result.speedup = result.baselineTime / result.hashmapTime;
    result.percentImprovement = ((result.baselineTime - result.hashmapTime) / result.baselineTime) * 100.0;
    
    return result;
}

void printResults(const vector<BenchmarkResult>& results) {
    cout << "\n========================================\n";
    cout << "  PERFORMANCE BENCHMARK RESULTS\n";
    cout << "  Hashmap vs Linear Search (Baseline)\n";
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
    
    // Create variables (atoms)
    vector<shared_ptr<Formula>> variables;
    for (int i = 0; i < numVariables; i++) {
        variables.push_back(make_shared<Atom>("x" + to_string(i)));  // Changed Variable to Atom
    }
    
    // Create 3-SAT style clauses
    for (int i = 0; i < numClauses; i++) {
        vector<shared_ptr<Formula>> literals;
        
        // Each clause has 3 literals
        for (int j = 0; j < 3; j++) {
            int varIdx = (i * 3 + j) % numVariables;
            shared_ptr<Formula> var = variables[varIdx];
            
            // Randomly negate based on position
            if ((i + j) % 2 == 0) {
                literals.push_back(var->negationOf());
            } else {
                literals.push_back(var);
            }
        }
        
        // Create OR clause
        shared_ptr<Formula> clause = make_shared<Or>(literals);
        clauses.push_back(clause);
    }
    
    return clauses;
}

int main() {
    vector<BenchmarkResult> results;
    
    cout << "Running SAT Solver Performance Benchmarks...\n";
    cout << "Comparing Hashmap-based vs Linear Search implementations\n\n";
    
    // Small test
    cout << "Running small test (50 variables, 100 clauses)...\n";
    auto smallFormula = createTestFormula(50, 100);
    results.push_back(runBenchmark("Small", 50, smallFormula));
    
    // Medium test
    cout << "Running medium test (100 variables, 300 clauses)...\n";
    auto mediumFormula = createTestFormula(100, 300);
    results.push_back(runBenchmark("Medium", 100, mediumFormula));
    
    // Large test
    cout << "Running large test (200 variables, 600 clauses)...\n";
    auto largeFormula = createTestFormula(200, 600);
    results.push_back(runBenchmark("Large", 200, largeFormula));
    
    // Extra large test
    cout << "Running extra large test (500 variables, 1500 clauses)...\n";
    auto xlargeFormula = createTestFormula(500, 1500);
    results.push_back(runBenchmark("Extra Large", 500, xlargeFormula));
    
    // Print all results
    printResults(results);
    
    cout << "\n*** CV CLAIM ***\n";
    cout << "Achieved " << fixed << setprecision(1) 
         << (results.back().percentImprovement) 
         << "% performance improvement using hashmap-based state tracking\n";
    cout << "in SAT solver implementation (tested on formulas with up to " 
         << results.back().numClauses << " clauses)\n\n";
    
    return 0;
}
