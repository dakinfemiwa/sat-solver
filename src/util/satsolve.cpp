#include "../../include/satsolve.h"
#include <algorithm>
#include <climits>

using namespace std;

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
        conjunctStat->satisfaction.satisfied = false;
        conjunctStat->satisfaction.satisfyingLiteral = nullptr;
        conjunctStat->conjunctCount = f->getLiterals().size();
        conjunctStat->originalCount = conjunctStat->conjunctCount;
        conjunctStat->level = -1;
        
        satSolveStatus->conjuncts.push_back(conjunctStat);
        satSolveStatus->clausesLeft++;
    }

    return satSolveStatus;
}

shared_ptr<struct conjunctStatus> getLiteral(shared_ptr<struct satSolveStatus> status) {
    int minNum = INT_MAX;
    shared_ptr<struct conjunctStatus> minConjunct = nullptr;

    for (auto& c : status->conjuncts) {
        if (!c->satisfaction.satisfied && c->conjunctCount < minNum) {
            minNum = c->conjunctCount;
            minConjunct = c;
            if (minNum == 1) {
                return minConjunct;
            }
        }
    }

    return minConjunct;
}

bool hasLiteral(shared_ptr<struct conjunctStatus> conjunct, shared_ptr<Formula> literal) {
    return std::find(conjunct->conjunct->getLiterals().begin(), 
                     conjunct->conjunct->getLiterals().end(),
                     literal) != conjunct->conjunct->getLiterals().end();
}

void set_valuation(shared_ptr<struct satSolveStatus> status,
                    shared_ptr<Formula> literal,
                    bool valuation) {
    status->valuations[literal] = valuation;
    //Satisfy clauses
    for (auto& c : status->conjuncts) {
        if (!c->satisfaction.satisfied && valuation && hasLiteral(c, literal)) {
            //Satisfy clause - literal is true and appears in clause
            c->satisfaction.satisfied = true;
            c->satisfaction.satisfyingLiteral = literal;
            status->clausesLeft--;
        } else if (!c->satisfaction.satisfied && !valuation && hasLiteral(c, literal->negationOf())) {
            //Satisfy clause - literal is false, so its negation is true
            c->satisfaction.satisfied = true;
            c->satisfaction.satisfyingLiteral = literal->negationOf();
            status->clausesLeft--;
        }

        //Remove contradictory literals
        if (!c->satisfaction.satisfied && hasLiteral(c, literal->negationOf()) && valuation) {
            c->conjunctCount--;
        } else if (!c->satisfaction.satisfied && hasLiteral(c, literal) && !valuation) {
            c->conjunctCount--;
        }
    }
    
}

bool hasContradiction(shared_ptr<struct satSolveStatus> status) {

    for (auto& c : status->conjuncts) {
        if (!c->satisfaction.satisfied && c->conjunctCount == 0) {
            return true;
        }
    }
    return false;
}

void addDecision(shared_ptr<struct satSolveStatus> status, 
                    shared_ptr<Formula> literal,
                    bool valuation) {
        struct Decision decision;
        decision.literal = literal;
        decision.value = valuation;
        decision.clauses = status->conjuncts;
        decision.valuations = status->valuations;
        decision.wrongValuations = status->wrongValuations;
        decision.clausesLeft = status->clausesLeft;
        status->decisionStack.push(decision);
}

//Function to handle contradions
shared_ptr<struct satSolveStatus> handle_contradiction(shared_ptr<struct satSolveStatus> status,
                                                        shared_ptr<Formula> literal,
                                                        bool valuation) {
    if (status->wrongValuations.find(literal) != status->wrongValuations.end()) {
        if (status->wrongValuations[literal] != valuation) {
            //Unsatisfiable formula
            status->state = UNSAT;
            return status;
        }
    }
        
    if (!status->decisionStack.empty()) {
        Decision lastDecision = status->decisionStack.top();
        status->decisionStack.pop();
        status->conjuncts = lastDecision.clauses;
        status->valuations = lastDecision.valuations;
        status->clausesLeft = lastDecision.clausesLeft;
    }
    status->wrongValuations[literal] = valuation;
    set_valuation(status, literal, !valuation);
    //Even if we couldn't backtrack we must 
    return status;    

    
}