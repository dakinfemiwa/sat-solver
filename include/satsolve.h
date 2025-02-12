/*
Contains structures used in SAT solving algorithm
*/

#include <memory>
#include <vector>
#include "formula.h"
#include <unordered_map>

enum formula_state {SAT, UNSAT, UNKNOWN};

struct satisfiedClause {
    bool satisfied;
    shared_ptr<Formula> satisfyingLiteral;
};

struct status {
    unordered_map<shared_ptr<Formula>, bool> valuations;
    unordered_map<shared_ptr<Formula>, bool> wrongValuations;
    vector<shared_ptr<Formula>> prevConjuncts;
    vector<shared_ptr<Formula>> conjuncts;
};

struct conjunctStatus {
    shared_ptr<Formula> conjunct;
    //Stored whether a clause is satisfied and what literal satisfied it
    satisfiedClause satisfiedClause;
    //Data to identify at what stage a conjunct was satisfied
    //  so if there needs to be backtracking that can be done
    int level;
    //Checks how many clauses are left in formula
    int conjunctCount;
};

//Checks if a literal has been removed from a clause
struct literalStatus {
    shared_ptr<Formula> literal;
    bool removed;
};

struct satSolveStatus {
    unordered_map<shared_ptr<Formula>, bool> valuations;
    unordered_map<shared_ptr<Formula>, bool> wrongValuations;
    vector<shared_ptr<struct conjunctStatus>> conjuncts;
    int clausesLeft;
    formula_state state;
};

//Functions
shared_ptr<struct satSolveStatus> satSolveInit(vector<shared_ptr<Formula>> conjuncts);


