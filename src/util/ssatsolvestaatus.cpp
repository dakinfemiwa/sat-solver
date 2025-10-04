/*
SatSolveStatus 

- DPLL SAT Solver with AVL Tree optimization and stack-based backtracking
- Implements unit propagation, conflict-driven backtracking, and efficient clause prioritization
*/

#include "../../include/satsolve.h"
#include <algorithm>

// Initialize SAT solver with AVL tree for clause prioritization
shared_ptr<struct satSolveStatus> satSolveInit(vector<shared_ptr<Formula>> conjuncts) {
    shared_ptr<struct satSolveStatus> satSolveStatus = make_shared<struct satSolveStatus>();
    satSolveStatus->state = UNKNOWN;
    satSolveStatus->clausesLeft = 0;
    satSolveStatus->valuations = {};
    satSolveStatus->wrongValuations = {};
    satSolveStatus->conjuncts = {};
    satSolveStatus->currentLevel = 0;

    for (shared_ptr<Formula> f : conjuncts) {
        shared_ptr<struct conjunctStatus> conjunctStat = make_shared<struct conjunctStatus>();
        conjunctStat->conjunct = f;
        conjunctStat->satisfiedClause.satisfied = false;
        conjunctStat->satisfiedClause.satisfyingLiteral = nullptr;
        conjunctStat->conjunctCount = f->getLiterals().size();
        conjunctStat->originalCount = conjunctStat->conjunctCount;
        conjunctStat->level = -1;
        
        satSolveStatus->conjuncts.push_back(conjunctStat);
        satSolveStatus->clauseTree.insert(conjunctStat);
        satSolveStatus->clausesLeft++;
    }

    return satSolveStatus;
}

// Unit propagation with conflict detection
bool unitPropagate(shared_ptr<struct satSolveStatus> status) {
    bool propagated = false;
    
    do {
        propagated = false;
        
        for (auto& clause : status->conjuncts) {
            if (clause->satisfiedClause.satisfied || clause->conjunctCount != 1) {
                continue;
            }
            
            // Find the unassigned literal in this unit clause
            shared_ptr<Formula> unitLiteral = nullptr;
            for (auto& literal : clause->conjunct->getLiterals()) {
                if (status->valuations.find(literal) == status->valuations.end() &&
                    status->valuations.find(literal->negationOf()) == status->valuations.end()) {
                    unitLiteral = literal;
                    break;
                }
            }
            
            if (unitLiteral) {
                chooseLiteral(unitLiteral, true, status);
                propagated = true;
                
                if (status->state == UNSAT) {
                    return false;
                }
            }
        }
    } while (propagated);
    
    return true;
}

void chooseLiteral(shared_ptr<Formula> literal, bool value, 
shared_ptr<struct satSolveStatus> status) {
    // Check for conflicts
    if (status->valuations.find(literal) != status->valuations.end()) {
        if (status->valuations[literal] != value) {
            status->state = UNSAT;
            return;
        }
        return; // Already assigned
    }
    
    // Create decision for backtracking
    Decision decision;
    decision.literal = literal;
    decision.value = value;
    decision.level = status->currentLevel;
    
    shared_ptr<Formula> negLiteral = literal->negationOf();
    
    // Process all clauses
    for (auto& c : status->conjuncts) {
        if (c->satisfiedClause.satisfied) {
            continue;
        }
        
        vector<shared_ptr<Formula>> literals = c->conjunct->getLiterals();
        bool modified = false;
        int originalCount = c->conjunctCount;
        
        // Check if literal satisfies clause
        if (find(literals.begin(), literals.end(), literal) != literals.end()) {
            c->level = status->currentLevel;
            c->satisfiedClause.satisfyingLiteral = literal;
            c->satisfiedClause.satisfied = true;
            status->clausesLeft--;
            modified = true;
        }
        // Check if negation of literal is in clause
        else if (find(literals.begin(), literals.end(), negLiteral) != literals.end()) {
            c->conjunctCount--;
            modified = true;
            
            if (c->conjunctCount == 0) {
                status->state = UNSAT;
                return;
            }
        }
        
        if (modified) {
            decision.modifiedClauses.push_back(c);
            decision.originalCounts.push_back(originalCount);
            
            // Update AVL tree
            status->clauseTree.remove(c);
            if (!c->satisfiedClause.satisfied) {
                status->clauseTree.insert(c);
            }
        }
    }
    
    // Push decision onto stack
    status->decisionStack.push(decision);
    
    // Set valuation
    status->valuations[literal] = value;
    
    // Check if satisfied
    if (status->clausesLeft == 0) {
        status->state = SAT;
    }
}

bool backtrack(shared_ptr<struct satSolveStatus> status) {
    if (status->decisionStack.empty()) {
        return false; // No more decisions to backtrack
    }
    
    Decision lastDecision = status->decisionStack.top();
    status->decisionStack.pop();
    
    // Restore clause states
    for (size_t i = 0; i < lastDecision.modifiedClauses.size(); i++) {
        auto clause = lastDecision.modifiedClauses[i];
        int originalCount = lastDecision.originalCounts[i];
        
        // Remove from tree
        status->clauseTree.remove(clause);
        
        // Restore original state
        if (clause->satisfiedClause.satisfied && clause->level == lastDecision.level) {
            clause->satisfiedClause.satisfied = false;
            clause->satisfiedClause.satisfyingLiteral = nullptr;
            clause->level = -1;
            status->clausesLeft++;
        }
        
        clause->conjunctCount = originalCount;
        
        // Re-insert into tree
        status->clauseTree.insert(clause);
    }
    
    // Remove valuation
    status->valuations.erase(lastDecision.literal);
    
    // Try opposite value
    if (status->wrongValuations.find(lastDecision.literal) == status->wrongValuations.end()) {
        status->wrongValuations[lastDecision.literal] = lastDecision.value;
        chooseLiteral(lastDecision.literal, !lastDecision.value, status);
        return true;
    } else {
        // Both values tried, continue backtracking
        status->wrongValuations.erase(lastDecision.literal);
        return backtrack(status);
    }
}

shared_ptr<Formula> selectNextLiteral(shared_ptr<struct satSolveStatus> status) {
    // Get smallest unsatisfied clause
    shared_ptr<conjunctStatus> smallestClause = status->clauseTree.getSmallestUnsatisfied();
    
    if (!smallestClause) {
        return nullptr;
    }
    
    // Find unassigned literal in this clause
    for (auto& literal : smallestClause->conjunct->getLiterals()) {
        if (status->valuations.find(literal) == status->valuations.end() &&
            status->valuations.find(literal->negationOf()) == status->valuations.end() &&
            status->wrongValuations.find(literal) == status->wrongValuations.end()) {
            return literal;
        }
    }
    
    return nullptr;
}

bool dpllSolve(shared_ptr<struct satSolveStatus> status) {
    while (status->state == UNKNOWN) {
        // Unit propagation
        if (!unitPropagate(status)) {
            // Conflict during unit propagation
            if (!backtrack(status)) {
                status->state = UNSAT;
                return false;
            }
            continue;
        }
        
        if (status->state != UNKNOWN) {
            break;
        }
        
        // Select next literal
        shared_ptr<Formula> nextLiteral = selectNextLiteral(status);
        
        if (!nextLiteral) {
            status->state = SAT;
            return true;
        }
        
        // Make decision
        status->currentLevel++;
        chooseLiteral(nextLiteral, true, status);
        
        // Handle conflicts
        if (status->state == UNSAT) {
            if (!backtrack(status)) {
                return false;
            }
        }
    }
    
    return status->state == SAT;
}

bool solveSAT(vector<shared_ptr<Formula>> conjuncts) {
    shared_ptr<struct satSolveStatus> status = satSolveInit(conjuncts);
    return dpllSolve(status);
}