/*
Contains structures used in SAT solving algorithm
*/

#ifndef SATSOLVE_H
#define SATSOLVE_H

#include <memory>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "formula.h"

using namespace std;

enum formula_state {SAT, UNSAT, UNKNOWN};

struct satisfiedClause {
    bool satisfied;
    shared_ptr<Formula> satisfyingLiteral;
};

struct conjunctStatus {
    shared_ptr<Formula> conjunct;
    satisfiedClause satisfaction;
    int level;
    int conjunctCount;
    int originalCount; // Store original count for backtracking
};

struct Decision {
    shared_ptr<Formula> literal;
    int level;
    bool value;
    vector<shared_ptr<conjunctStatus>> clauses;
    unordered_map<shared_ptr<Formula>, bool> valuations;
    unordered_map<shared_ptr<Formula>, bool> wrongValuations;
    int clausesLeft;
    shared_ptr<conjunctStatus> conflictClause; 

};

struct satSolveStatus {
    unordered_map<shared_ptr<Formula>, bool> valuations;
    unordered_map<shared_ptr<Formula>, bool> wrongValuations;
    vector<shared_ptr<conjunctStatus>> conjuncts;
    int clausesLeft;
    formula_state state;
    
    // Backtracking stack
    stack<Decision> decisionStack;
    int currentLevel;
};

shared_ptr<struct satSolveStatus> satSolveInit(vector<shared_ptr<Formula>> conjuncts);
shared_ptr<struct conjunctStatus> getLiteral(shared_ptr<struct satSolveStatus> status);
bool hasLiteral(shared_ptr<struct conjunctStatus> conjunct, shared_ptr<Formula> literal);
void set_valuation(shared_ptr<struct satSolveStatus> status,
                    shared_ptr<Formula> literal,
                    bool valuation);
bool hasContradiction(shared_ptr<struct satSolveStatus> status);
void addDecision(shared_ptr<struct satSolveStatus> status, 
                    shared_ptr<Formula> literal,
                    bool valuation);
shared_ptr<struct satSolveStatus> handle_contradiction(shared_ptr<struct satSolveStatus> status,
                                                        shared_ptr<Formula> literal,
                                                        bool valuation);

#endif // SATSOLVE_H
