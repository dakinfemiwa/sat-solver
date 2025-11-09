/*
Baseline SAT Solver - Using vectors with linear search instead of hashmaps
This is the NAIVE implementation for performance comparison
*/

#ifndef SATSOLVE_BASELINE_H
#define SATSOLVE_BASELINE_H

#include <memory>
#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include "../../include/formula.h"

using namespace std;

namespace baseline {

enum formula_state_baseline {SAT_BASELINE, UNSAT_BASELINE, UNKNOWN_BASELINE};

struct satisfiedClause_baseline {
    bool satisfied;
    shared_ptr<Formula> satisfyingLiteral;
};

struct conjunctStatus_baseline {
    shared_ptr<Formula> conjunct;
    satisfiedClause_baseline satisfaction;
    int level;
    int conjunctCount;
    int originalCount;
};

struct Decision_baseline {
    shared_ptr<Formula> literal;
    int level;
    bool value;
    vector<shared_ptr<conjunctStatus_baseline>> clauses;
    vector<pair<shared_ptr<Formula>, bool>> valuations;  // BASELINE: vector instead of hashmap
    vector<pair<shared_ptr<Formula>, bool>> wrongValuations;  // BASELINE: vector instead of hashmap
    int clausesLeft;
    shared_ptr<conjunctStatus_baseline> conflictClause; 
};

struct satSolveStatus_baseline {
    vector<pair<shared_ptr<Formula>, bool>> valuations;  // BASELINE: vector instead of hashmap
    vector<pair<shared_ptr<Formula>, bool>> wrongValuations;  // BASELINE: vector instead of hashmap
    vector<shared_ptr<conjunctStatus_baseline>> conjuncts;
    int clausesLeft;
    formula_state_baseline state;
    
    stack<Decision_baseline> decisionStack;
    int currentLevel;
};

shared_ptr<satSolveStatus_baseline> satSolveInit_baseline(vector<shared_ptr<Formula>> conjuncts);
shared_ptr<conjunctStatus_baseline> getLiteral_baseline(shared_ptr<satSolveStatus_baseline> status);
bool hasLiteral_baseline(shared_ptr<conjunctStatus_baseline> conjunct, shared_ptr<Formula> literal);
void set_valuation_baseline(shared_ptr<satSolveStatus_baseline> status,
                    shared_ptr<Formula> literal,
                    bool valuation);
bool hasContradiction_baseline(shared_ptr<satSolveStatus_baseline> status);
shared_ptr<satSolveStatus_baseline> handle_contradiction_baseline(shared_ptr<satSolveStatus_baseline> status,
                                                        shared_ptr<Formula> literal,
                                                        bool valuation);
void addDecision_baseline(shared_ptr<satSolveStatus_baseline> status, 
                 shared_ptr<Formula> literal,
                 bool valuation);

// BASELINE HELPER FUNCTIONS for linear search
bool findValuation_baseline(const vector<pair<shared_ptr<Formula>, bool>>& valuations, 
                   shared_ptr<Formula> literal, bool& value);
void setValuation_baseline(vector<pair<shared_ptr<Formula>, bool>>& valuations,
                  shared_ptr<Formula> literal, bool value);

} // namespace baseline

#endif // SATSOLVE_BASELINE_H
