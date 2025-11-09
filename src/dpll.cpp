#include <memory>
#include <vector>
#include <stack>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "../include/formula.h"
#include "../include/satsolve.h"

void dpllSatSolve(vector<shared_ptr<Formula>> conjuncts) {
    shared_ptr<struct satSolveStatus> status = satSolveInit(conjuncts);
    int decisions =0;

    while (status->state == UNKNOWN && status->clausesLeft > 0) {
        decisions++;
        //bool currentVal = true;
        shared_ptr<struct conjunctStatus> chosenConjunct = getLiteral(status);
        vector<shared_ptr<Formula>> literals = chosenConjunct->conjunct->getLiterals();
        shared_ptr<Formula> f = literals[0];

        addDecision(status, f, true);
        set_valuation(status, f, true);
        if (hasContradiction(status)) {
            status = handle_contradiction(status, f, true);
            
            if (hasContradiction(status)) {
                status->state = UNSAT;
            }
        }
        if (status->clausesLeft == 0) {
            status->state = SAT;
        }
    

        
    }
    cout << "Optimized decisions: " << decisions << endl;  // ADD THIS


}
