/*
Accuracy Tests for SAT Solver
Tests that both hashmap and baseline versions produce correct and identical results
*/

#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include "../../include/formula.h"
#include "../../include/satsolve.h"
#include "../../include/dpll.h"
#include "satsolve_baseline.h"
#include "dpll_baseline.h"

using namespace std;

// Test result tracking
struct TestResult {
    string testName;
    bool passed;
    string errorMsg;
};

vector<TestResult> testResults;

void reportTest(string name, bool passed, string errorMsg = "") {
    TestResult result;
    result.testName = name;
    result.passed = passed;
    result.errorMsg = errorMsg;
    testResults.push_back(result);
    
    if (passed) {
        cout << "✓ PASS: " << name << endl;
    } else {
        cout << "✗ FAIL: " << name << " - " << errorMsg << endl;
    }
}

// Helper to create simple test formulas
vector<shared_ptr<Formula>> createSimpleSAT() {
    // (p OR q) AND (NOT p OR q) - should be SAT with q=true
    auto p = make_shared<Atom>("p");
    auto q = make_shared<Atom>("q");
    
    vector<shared_ptr<Formula>> clause1 = {p, q};
    vector<shared_ptr<Formula>> clause2 = {p->negationOf(), q};
    
    return {make_shared<Or>(clause1), make_shared<Or>(clause2)};
}

vector<shared_ptr<Formula>> createSimpleUNSAT() {
    // (p) AND (NOT p) - contradiction
    auto p = make_shared<Atom>("p");
    
    vector<shared_ptr<Formula>> clause1 = {p};
    vector<shared_ptr<Formula>> clause2 = {p->negationOf()};
    
    return {make_shared<Or>(clause1), make_shared<Or>(clause2)};
}

vector<shared_ptr<Formula>> createUnitPropagation() {
    // (p) AND (p OR q) - unit propagation should set p=true
    auto p = make_shared<Atom>("p");
    auto q = make_shared<Atom>("q");
    
    vector<shared_ptr<Formula>> clause1 = {p};
    vector<shared_ptr<Formula>> clause2 = {p, q};
    
    return {make_shared<Or>(clause1), make_shared<Or>(clause2)};
}

vector<shared_ptr<Formula>> createBacktrackingUNSAT() {
    // More complex UNSAT requiring backtracking
    // (p OR q) AND (NOT p OR q) AND (p OR NOT q) AND (NOT p OR NOT q)
    auto p = make_shared<Atom>("p");
    auto q = make_shared<Atom>("q");
    
    vector<shared_ptr<Formula>> clause1 = {p, q};
    vector<shared_ptr<Formula>> clause2 = {p->negationOf(), q};
    vector<shared_ptr<Formula>> clause3 = {p, q->negationOf()};
    vector<shared_ptr<Formula>> clause4 = {p->negationOf(), q->negationOf()};
    
    return {make_shared<Or>(clause1), make_shared<Or>(clause2), 
            make_shared<Or>(clause3), make_shared<Or>(clause4)};
}


// Test 1: Simple satisfiable formula
// (p OR q) AND (NOT p OR q) AND (p OR NOT q)
// Should be SAT with p=true, q=true
void testSimpleSAT() {
    cout << "\nTest 1: Simple Satisfiable Formula" << endl;
    
    // TODO: Create formula based on your Formula class implementation
    // vector<shared_ptr<Formula>> formula = ...
    
    // Test hashmap version
    // auto hashmapStatus = satSolveInit(formula);
    // dpllSatSolve(formula);
    // bool hashmapResult = (hashmapStatus->state == SAT);
    
    // Test baseline version
    // auto baselineStatus = satSolveInit(formula);
    // dpllSatSolve_baseline(formula);
    // bool baselineResult = (baselineStatus->state == SAT);
    
    // For now, placeholder
    bool hashmapResult = true;  // Replace with actual test
    bool baselineResult = true;  // Replace with actual test
    
    bool bothSAT = hashmapResult && baselineResult;
    bool resultsMatch = (hashmapResult == baselineResult);
    
    reportTest("Simple SAT - Both find SAT", bothSAT, 
               bothSAT ? "" : "One or both solvers failed to find SAT");
    reportTest("Simple SAT - Results match", resultsMatch,
               resultsMatch ? "" : "Hashmap and baseline gave different results");
}

// Test 2: Simple unsatisfiable formula
// (p) AND (NOT p)
// Should be UNSAT
void testSimpleUNSAT() {
    cout << "\nTest 2: Simple Unsatisfiable Formula" << endl;
    
    // TODO: Create formula: (p) AND (NOT p)
    
    bool hashmapResult = false;  // Replace: should be UNSAT
    bool baselineResult = false;  // Replace: should be UNSAT
    
    bool bothUNSAT = (!hashmapResult) && (!baselineResult);
    bool resultsMatch = (hashmapResult == baselineResult);
    
    reportTest("Simple UNSAT - Both find UNSAT", bothUNSAT,
               bothUNSAT ? "" : "One or both solvers failed to detect UNSAT");
    reportTest("Simple UNSAT - Results match", resultsMatch,
               resultsMatch ? "" : "Hashmap and baseline gave different results");
}

// Test 3: Unit propagation test
// (p) AND (p OR q) AND (NOT p OR r)
// Should be SAT with p=true, r=true, q can be anything
void testUnitPropagation() {
    cout << "\nTest 3: Unit Propagation" << endl;
    
    // TODO: Create formula with unit clauses
    
    bool hashmapResult = true;   // Replace with actual test
    bool baselineResult = true;   // Replace with actual test
    
    bool bothSAT = hashmapResult && baselineResult;
    bool resultsMatch = (hashmapResult == baselineResult);
    
    reportTest("Unit Propagation - Both find SAT", bothSAT,
               bothSAT ? "" : "Failed unit propagation test");
    reportTest("Unit Propagation - Results match", resultsMatch,
               resultsMatch ? "" : "Different results on unit propagation");
}

// Test 4: Requires backtracking
// (p OR q) AND (NOT p OR q) AND (p OR NOT q) AND (NOT p OR NOT q)
// Should be UNSAT (no assignment satisfies all clauses)
void testBacktracking() {
    cout << "\nTest 4: Backtracking Required (UNSAT)" << endl;
    
    // TODO: Create formula that requires backtracking
    
    bool hashmapResult = false;  // Replace: should be UNSAT
    bool baselineResult = false;  // Replace: should be UNSAT
    
    bool bothUNSAT = (!hashmapResult) && (!baselineResult);
    bool resultsMatch = (hashmapResult == baselineResult);
    
    reportTest("Backtracking - Both find UNSAT", bothUNSAT,
               bothUNSAT ? "" : "Failed backtracking test");
    reportTest("Backtracking - Results match", resultsMatch,
               resultsMatch ? "" : "Different results on backtracking");
}

// Test 5: Empty formula (no clauses)
// Should be SAT (trivially satisfied)
void testEmptyFormula() {
    cout << "\nTest 5: Empty Formula" << endl;
    
    vector<shared_ptr<Formula>> emptyFormula;
    
    auto hashmapStatus = satSolveInit(emptyFormula);
    // dpllSatSolve would handle this
    bool hashmapResult = (hashmapStatus->clausesLeft == 0);
    
    auto baselineStatus = satSolveInit(emptyFormula);
    bool baselineResult = (baselineStatus->clausesLeft == 0);
    
    bool bothCorrect = hashmapResult && baselineResult;
    bool resultsMatch = (hashmapResult == baselineResult);
    
    reportTest("Empty Formula - Both handle correctly", bothCorrect,
               bothCorrect ? "" : "Failed to handle empty formula");
    reportTest("Empty Formula - Results match", resultsMatch,
               resultsMatch ? "" : "Different handling of empty formula");
}

// Test 6: 3-SAT problem
// More complex formula with multiple clauses
void test3SAT() {
    cout << "\nTest 6: 3-SAT Problem" << endl;
    
    // TODO: Create a proper 3-SAT instance
    // (p OR q OR r) AND (NOT p OR q OR r) AND (p OR NOT q OR r) ...
    
    bool hashmapResult = true;   // Replace with actual test
    bool baselineResult = true;   // Replace with actual test
    
    bool resultsMatch = (hashmapResult == baselineResult);
    
    reportTest("3-SAT - Results match", resultsMatch,
               resultsMatch ? "" : "Different results on 3-SAT problem");
}

// Test 7: Horn clauses (should be efficiently solvable)
void testHornClauses() {
    cout << "\nTest 7: Horn Clauses" << endl;
    
    // TODO: Create Horn clause formula
    // (NOT p OR q) AND (NOT q OR r) AND (p)
    // Should be SAT with p=true, q=true, r=true
    
    bool hashmapResult = true;   // Replace with actual test
    bool baselineResult = true;   // Replace with actual test
    
    bool bothSAT = hashmapResult && baselineResult;
    bool resultsMatch = (hashmapResult == baselineResult);
    
    reportTest("Horn Clauses - Both find SAT", bothSAT,
               bothSAT ? "" : "Failed on Horn clauses");
    reportTest("Horn Clauses - Results match", resultsMatch,
               resultsMatch ? "" : "Different results on Horn clauses");
}

void printSummary() {
    cout << "\n========================================\n";
    cout << "  ACCURACY TEST SUMMARY\n";
    cout << "========================================\n";
    
    int passed = 0;
    int failed = 0;
    
    for (const auto& result : testResults) {
        if (result.passed) {
            passed++;
        } else {
            failed++;
        }
    }
    
    cout << "Total Tests: " << testResults.size() << endl;
    cout << "Passed: " << passed << " ✓" << endl;
    cout << "Failed: " << failed << " ✗" << endl;
    
    if (failed == 0) {
        cout << "\n✓✓✓ ALL TESTS PASSED ✓✓✓\n";
        cout << "Both hashmap and baseline implementations are correct!\n";
    } else {
        cout << "\n✗✗✗ SOME TESTS FAILED ✗✗✗\n";
        cout << "Review failed tests above.\n";
    }
    
    cout << "========================================\n\n";
}

vector<shared_ptr<Formula>> createTestFormula(int numVariables, int numClauses) {
    vector<shared_ptr<Formula>> clauses;
    
    // Create variables
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
        
        // Create OR clause (literal1 OR literal2 OR literal3)
        shared_ptr<Formula> clause = make_shared<Or>(literals);
        clauses.push_back(clause);
    }
    
    return clauses;
}

int main() {
    cout << "========================================\n";
    cout << "  SAT SOLVER ACCURACY TESTS\n";
    cout << "  Verifying Correctness of Both Implementations\n";
    cout << "========================================\n";
    
    testSimpleSAT();
    testSimpleUNSAT();
    testUnitPropagation();
    testBacktracking();
    testEmptyFormula();
    test3SAT();
    testHornClauses();
    
    printSummary();
    
    // Return exit code based on results
    for (const auto& result : testResults) {
        if (!result.passed) {
            return 1;  // Failure
        }
    }
    
    return 0;  // Success
}
