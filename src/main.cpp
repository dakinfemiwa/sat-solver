#include <iostream>
#include "../include/satsolve.h"
#include "../include/formula.h"

using namespace std;

// Forward declaration for test function
bool solveSATWithDetails(vector<shared_ptr<Formula>> conjuncts, bool verbose);

int main() {
    cout << "DPLL SAT Solver - Advanced Implementation" << endl;
    cout << "=========================================" << endl;
    
    // Create test formulas
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
    
    cout << "Test Formula: (A ∨ B) ∧ (¬A ∨ C) ∧ (¬B ∨ ¬C)" << endl;
    cout << "Running DPLL solver..." << endl;
    
    // Solve the SAT instance
    bool isSatisfiable = solveSAT(conjuncts);
    
    if (isSatisfiable) {
        cout << "Result: SATISFIABLE" << endl;
    } else {
        cout << "Result: UNSATISFIABLE" << endl;
    }
    
    cout << endl << "Features implemented:" << endl;
    cout << "- DPLL algorithm with unit propagation" << endl;
    cout << "- AVL tree for efficient clause prioritization" << endl;
    cout << "- Stack-based backtracking" << endl;
    cout << "- Conflict-driven learning preparation" << endl;
    cout << "- De Morgan's law implementations" << endl;
    
    return 0;
}