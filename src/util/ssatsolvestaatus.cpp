/*
SatSolveStatus 

- to handle the utility functions associating with the SAT solving algorithm
- initialise structs and use structs to solve SAT solving problem


*/

#include "../../include/satsolve.h"
#include <memory>
#include <vector>

bool satSolveInit(shared_ptr<struct status> status, 
vector<shared_ptr<Formula>> conjuncts, vector<shared_ptr<Formula>> disjuncts,
vector<shared_ptr<Formula>> prev_conjuncts) {
    status->valuations = {};
    status->wrongValuations = {};
    status->conjuncts = conjuncts;
    status->prevConjuncts = prev_conjuncts;
    return true;
}

//Initialise satisfiedClauses

//Initialise information concerning SAT solver
shared_ptr<struct satSolveStatus> satSolveInit(vector<shared_ptr<Formula>> conjuncts) {
    shared_ptr<struct satSolveStatus> satSolveStatus = make_shared<struct satSolveStatus>();
    satSolveStatus->state = UNKNOWN;
    satSolveStatus->clausesLeft = 0;
    satSolveStatus->valuations={};
    satSolveStatus->wrongValuations = {};

    satSolveStatus->conjuncts = {};
    for (shared_ptr<Formula> f : conjuncts) {
        shared_ptr<struct satisfiedClause> satisfiedClause;
        shared_ptr<struct conjunctStatus> conjunctStat = make_shared<struct conjunctStatus>();
        conjunctStat->satisfiedClause = *satisfiedClause;
        
        satSolveStatus->conjuncts.push_back(conjunctStat);
        satSolveStatus->clausesLeft++;
    }

    return satSolveStatus;
}

void chooseLiteral(shared_ptr<Formula> literal, bool value, 
shared_ptr<struct satSolveStatus> status) {
    //
    if (status->valuations.find(literal) != status->valuations.end()) {
        //
        if (status->valuations[literal] != value) {
            status->state = UNSAT;
            return;
        }
    }
    
    vector<shared_ptr<struct conjunctStatus>> conjuncts = status->conjuncts;
    for (shared_ptr<conjunctStatus> c : conjuncts) {
        //Assuming c is a disjunction of literals or a literal 
        //  They are identical if their lists are identical
        if (c->conjunct->getLiterals() == literal->getLiterals()) {
            c->level++;
            c->satisfiedClause.satisfyingLiteral = literal;
            c->satisfiedClause.satisfied = true;
        } 
        //Deal with negation of literal, we should not be looking at negations of literals
        else if (c->conjunct->isNegation() && c->conjunct->negationOf() == literal) {
            c->conjunctCount--;
            if (c->conjunctCount == 0) {
                status->state = UNSAT;
                return;
            }
        }
    }
    //
    status->clausesLeft--;
    status->valuations.insert({literal, true});
    if (status->clausesLeft == 0) {
        status->state = SAT;
    }

    
    
}

void chooseNegation() {

}

//Function to choose a literal


