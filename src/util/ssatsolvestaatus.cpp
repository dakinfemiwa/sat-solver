/*
SatSolveStatus 

- to handle the utility functions associating with the SAT solving algorithm
- initialise structs and use structs to solve SAT solving problem


*/

#include "../../include/satsolve.h"
#include <cstddef>
#include <memory>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

/*
bool satSolveInit(
    shared_ptr<struct status> status, 
    vector<shared_ptr<Formula>> conjuncts, 
    vector<shared_ptr<Formula>> disjuncts,
    vector<shared_ptr<Formula>> prev_conjuncts) 
{
    status->valuations = {};
    status->wrongValuations = {};
    status->conjuncts = conjuncts;
    status->prevConjuncts = prev_conjuncts;
    return true;
}*/
//Initialise satisfiedClauses


//Initialise information concerning SAT solver
shared_ptr<struct satSolveStatus> satSolveInit(vector<shared_ptr<Formula>> conjuncts) {
    shared_ptr<struct satSolveStatus> satSolveStatus = make_shared<struct satSolveStatus>();
    satSolveStatus->state = UNKNOWN;
    satSolveStatus->clausesLeft = 0;
    satSolveStatus->valuations={};
    satSolveStatus->wrongValuations = {};

    satSolveStatus->conjuncts = {};

    satSolveStatus->clauseComp = clauseComparator();

    for (shared_ptr<Formula> f : conjuncts) {
        //shared_ptr<struct satisfiedClause> satisfiedClause;
        shared_ptr<struct conjunctStatus> conjunctStat = make_shared<struct conjunctStatus>();
        conjunctStat->conjunct = f;
        //conjunctStat->conjunctCount
        conjunctStat->satisfiedClause.satisfied = false;
        conjunctStat->satisfiedClause.satisfyingLiteral = NULL;

        conjunctStat->conjunctCount = f->getLiterals().size();
        
        satSolveStatus->conjuncts.push_back(conjunctStat);
        satSolveStatus->conjunctHeap.push_back(conjunctStat);        
        
        satSolveStatus->clausesLeft++;
    }

    make_heap(satSolveStatus->conjunctHeap.begin(),
    satSolveStatus->conjunctHeap.end(), 
    satSolveStatus->clauseComp);    

    return satSolveStatus;
}

void remakeHeap(shared_ptr<struct satSolveStatus> status) {
    make_heap(status->conjunctHeap.begin(), 
    status->conjunctHeap.end(), 
    status->clauseComp);
}

void updateClause(shared_ptr<struct satSolveStatus> status, 
    size_t index,
    shared_ptr<conjunctStatus> c) {
        if (index >= status->conjunctHeap.size()) {
            return;
        }

        size_t current = index;
        size_t parent = (current - 1) / 2;
        while (current > 0 && 
            status->clauseComp(c, status->conjunctHeap[parent])) 
            {
            swap(status->conjunctHeap[current], status->conjunctHeap[parent]);
            current = parent;
            parent = (current - 1) / 2;
        }

        size_t heapLength = status->conjunctHeap.size();

        if (current == index) {
            size_t child = 2 * current + 1;
            while (child < heapLength) {
                if (child + 1 < heapLength && 
                    status->clauseComp(status->conjunctHeap[child + 1], 
                    status->conjunctHeap[child])) {
                    child++;
                }
                if (!status->clauseComp(c, status->conjunctHeap[child])) {
                    break;
                }
                swap(status->conjunctHeap[current], status->conjunctHeap[child]);
                current = child;
                child = 2 * current + 1;
            
            }
        }
}

void chooseLiteral(shared_ptr<Formula> literal, bool value, 
shared_ptr<struct satSolveStatus> status) {
    //If we've assigned a value to a literal, we need to check if it is consistent with the current valuations
    //  If it is not consistent, we need to backtrack and remove the literal from the valuations
    if (status->valuations.find(literal) != status->valuations.end()) {
        // If the literal has already been assigned the opposite value, then we know the 
        //  formula is unsatisfiable
        if (status->valuations[literal] != value) {
            status->state = UNSAT;
            return;
        }
    }
    
    vector<shared_ptr<struct conjunctStatus>> conjuncts = status->conjuncts;
    for (shared_ptr<conjunctStatus> c : conjuncts) {
        //Assuming c is a disjunction of literals or a literal 
        //  They are identical if their lists are identical
        vector<shared_ptr<Formula>> conjcs = c->conjunct->getLiterals();
        if ((c->conjunct->getLiterals() == literal->getLiterals() &&
        !c->satisfiedClause.satisfied) || 
        (find(conjcs.begin(), conjcs.end(), literal) != conjcs.end()))  {
            c->level++;
            c->satisfiedClause.satisfyingLiteral = literal;
            c->satisfiedClause.satisfied = true;
            //If a clause is satisfied we have less clauses to satisfy
            status->clausesLeft--;
        }
        //Deal with negation of literal, we should not be looking at negations of literals
        else if (c->conjunct->negationOf() == literal) {
            //Most important part is how many literals are left
            /* SIDE NOTE: Could be useful looking at the case
            //   where there is 1 literal left - simplifies 
            //   process as we know we have to use a specific valuation*/
            c->conjunctCount--;
            if (c->conjunctCount == 0) {
                status->state = UNSAT;
                return;
            }
        }
    }
    //
    
    status->valuations.insert({literal, value});
    if (status->clausesLeft == 0) {
        status->state = SAT;
    }

    

}

void backtrackLiteral(shared_ptr<Formula> literal, 
shared_ptr<struct satSolveStatus> status)  {
    if (status->state == UNSAT) {
        status->state = UNKNOWN;
    }
    status->wrongValuations.insert({literal, 
        status->valuations[literal]});
    status->valuations.erase(literal);

    vector<shared_ptr<struct conjunctStatus>> conjuncts = status->conjuncts;
    for (shared_ptr<conjunctStatus> c : conjuncts) {
        if (c->conjunct->getLiterals() == literal->getLiterals()) {
            c->level--;
            c->satisfiedClause.satisfyingLiteral = NULL;
            c->satisfiedClause.satisfied = false;
            status->clausesLeft++;
            
        } else if (c->conjunct->negationOf() == literal) {
            c->conjunctCount++;
        }
    }    

    
}