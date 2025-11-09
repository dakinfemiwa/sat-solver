/*
BASELINE SAT Solver Implementation - Using LINEAR SEARCH with vectors
This is intentionally slower for performance comparison with hashmap version
*/

#include "satsolve_baseline.h"
#include <climits>

using namespace std;

namespace baseline {

// BASELINE: Linear search to find a valuation - O(n) instead of O(1)
bool findValuation_baseline(const vector<pair<shared_ptr<Formula>, bool>>& valuations, 
                   shared_ptr<Formula> literal, bool& value) {
    for (const auto& pair : valuations) {
        if (pair.first == literal) {
            value = pair.second;
            return true;
        }
    }
    return false;
}

// BASELINE: Linear search to set/update a valuation - O(n) instead of O(1)
void setValuation_baseline(vector<pair<shared_ptr<Formula>, bool>>& valuations,
                  shared_ptr<Formula> literal, bool value) {
    // Check if it exists first
    for (auto& pair : valuations) {
        if (pair.first == literal) {
            pair.second = value;
            return;
        }
    }
    // If not found, add it
    valuations.push_back({literal, value});
}

shared_ptr<satSolveStatus_baseline> satSolveInit_baseline(vector<shared_ptr<Formula>> conjuncts) {
    shared_ptr<satSolveStatus_baseline> status = make_shared<satSolveStatus_baseline>();
    status->state = UNKNOWN_BASELINE;
    status->clausesLeft = conjuncts.size();
    status->currentLevel = 0;
    
    for (auto& conjunct : conjuncts) {
        shared_ptr<conjunctStatus_baseline> conjunctStatus = make_shared<conjunctStatus_baseline>();
        conjunctStatus->conjunct = conjunct;
        conjunctStatus->satisfaction.satisfied = false;
        conjunctStatus->satisfaction.satisfyingLiteral = nullptr;
        conjunctStatus->level = 0;
        conjunctStatus->conjunctCount = conjunct->getLiterals().size();
        conjunctStatus->originalCount = conjunct->getLiterals().size();
        status->conjuncts.push_back(conjunctStatus);
    }
    
    return status;
}

shared_ptr<conjunctStatus_baseline> getLiteral_baseline(shared_ptr<satSolveStatus_baseline> status) {
    int minNum = INT_MAX;
    shared_ptr<conjunctStatus_baseline> minConjunct = nullptr;
    
    for (auto& c : status->conjuncts) {
        if (c->conjunctCount < minNum) {
            minNum = c->conjunctCount;
            minConjunct = c;
        }
        // Early exit for unit clause
        if (minNum == 1) {
            break;
        }
    }
    
    return minConjunct;
}

bool hasLiteral_baseline(shared_ptr<conjunctStatus_baseline> conjunct, shared_ptr<Formula> literal) {
    return std::find(conjunct->conjunct->getLiterals().begin(), 
                     conjunct->conjunct->getLiterals().end(),
                     literal) != conjunct->conjunct->getLiterals().end();
}

void set_valuation_baseline(shared_ptr<satSolveStatus_baseline> status,
                    shared_ptr<Formula> literal,
                    bool valuation) {
    setValuation_baseline(status->valuations, literal, valuation);  // BASELINE: O(n) operation
    
    //Satisfy clauses
    for (auto& c : status->conjuncts) {
        if (valuation && hasLiteral_baseline(c, literal)) {
            //Satisfy clause - literal is true and appears in clause
            c->satisfaction.satisfied = true;
            c->satisfaction.satisfyingLiteral = literal;
            status->clausesLeft--;
        } else if (!valuation && hasLiteral_baseline(c, literal->negationOf())) {
            //Satisfy clause - literal is false, so its negation is true
            c->satisfaction.satisfied = true;
            c->satisfaction.satisfyingLiteral = literal->negationOf();
            status->clausesLeft--;
        }

        //Remove contradictory literals
        if (hasLiteral_baseline(c, literal->negationOf()) && valuation) {
            c->conjunctCount--;
        } else if (hasLiteral_baseline(c, literal) && !valuation) {
            c->conjunctCount--;
        }
    }
}

bool hasContradiction_baseline(shared_ptr<satSolveStatus_baseline> status) {
    for (auto& c : status->conjuncts) {
        if (!c->satisfaction.satisfied && c->conjunctCount == 0) {
            return true;
        }
    }
    return false;
}

shared_ptr<satSolveStatus_baseline> handle_contradiction_baseline(shared_ptr<satSolveStatus_baseline> status,
                                                        shared_ptr<Formula> literal,
                                                        bool valuation) {
    // BASELINE: Linear search to check if we tried this literal before - O(n)
    bool previousVal;
    if (findValuation_baseline(status->wrongValuations, literal, previousVal)) {
        if (previousVal != valuation) {
            //Unsatisfiable formula
            status->state = UNSAT_BASELINE;
            return status;
        }
    }
        
    if (!status->decisionStack.empty()) {
        Decision_baseline lastDecision = status->decisionStack.top();
        status->decisionStack.pop();
        status->conjuncts = lastDecision.clauses;
        status->valuations = lastDecision.valuations;
        status->wrongValuations = lastDecision.wrongValuations;
        status->clausesLeft = lastDecision.clausesLeft;
    }
    
    setValuation_baseline(status->wrongValuations, literal, valuation);  // BASELINE: O(n)
    set_valuation_baseline(status, literal, !valuation);
    return status;    
}

void addDecision_baseline(shared_ptr<satSolveStatus_baseline> status, 
                 shared_ptr<Formula> literal,
                 bool valuation) {
    Decision_baseline decision;
    decision.literal = literal;
    decision.value = valuation;
    decision.clauses = status->conjuncts;
    decision.valuations = status->valuations;
    decision.wrongValuations = status->wrongValuations;
    decision.clausesLeft = status->clausesLeft;
    status->decisionStack.push(decision);
}

} // namespace baseline
