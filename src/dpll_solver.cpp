/*
DPLL SAT Solver - Main Implementation

This file contains the main DPLL algorithm implementation with:
- Unit propagation
- Conflict-driven backtracking
- AVL tree for efficient clause prioritization
- Stack-based decision tracking

The solver implements a modern DPLL algorithm that can handle large SAT instances
efficiently through optimized data structures and pruning techniques.
*/

#include "../../include/satsolve.h"
#include <iostream>

// Example usage and test function
void testSATSolver() {
    // Create some test formulas
    // Example: (A ∨ B) ∧ (¬A ∨ C) ∧ (¬B ∨ ¬C)
    
    shared_ptr<Formula> A = make_shared<Atom>("A");
    shared_ptr<Formula> B = make_shared<Atom>("B");
    shared_ptr<Formula> C = make_shared<Atom>("C");
    shared_ptr<Formula> notA = A->negationOf();
    shared_ptr<Formula> notB = B->negationOf();
    shared_ptr<Formula> notC = C->negationOf();
    
    // Create clauses
    vector<shared_ptr<Formula>> clause1 = {A, B};
    vector<shared_ptr<Formula>> clause2 = {notA, C};
    vector<shared_ptr<Formula>> clause3 = {notB, notC};
    
    shared_ptr<Formula> or1 = make_shared<Or>(clause1);
    shared_ptr<Formula> or2 = make_shared<Or>(clause2);
    shared_ptr<Formula> or3 = make_shared<Or>(clause3);
    
    vector<shared_ptr<Formula>> conjuncts = {or1, or2, or3};
    
    // Solve the SAT instance
    bool isSatisfiable = solveSAT(conjuncts);
    
    if (isSatisfiable) {
        std::cout << "Formula is SATISFIABLE" << std::endl;
    } else {
        std::cout << "Formula is UNSATISFIABLE" << std::endl;
    }
}

// Function to solve SAT with detailed output
bool solveSATWithDetails(vector<shared_ptr<Formula>> conjuncts, bool verbose = false) {
    shared_ptr<struct satSolveStatus> status = satSolveInit(conjuncts);
    
    if (verbose) {
        std::cout << "Initialized SAT solver with " << conjuncts.size() << " clauses" << std::endl;
        std::cout << "Starting DPLL algorithm..." << std::endl;
    }
    
    bool result = dpllSolve(status);
    
    if (verbose) {
        if (result) {
            std::cout << "SATISFIABLE - Found satisfying assignment:" << std::endl;
            for (const auto& assignment : status->valuations) {
                std::cout << "  " << assignment.first->toString() << " = " 
                         << (assignment.second ? "TRUE" : "FALSE") << std::endl;
            }
        } else {
            std::cout << "UNSATISFIABLE - No satisfying assignment exists" << std::endl;
        }
        
        std::cout << "Decision levels explored: " << status->currentLevel << std::endl;
    }
    
    return result;
}