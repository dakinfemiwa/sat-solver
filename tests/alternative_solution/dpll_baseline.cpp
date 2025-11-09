/*
BASELINE DPLL Implementation - uses linear search version
*/

#include <memory>
#include <vector>
#include "dpll_baseline.h"
#include "satsolve_baseline.h"
#include "../../include/formula.h"

using namespace std;
using namespace baseline;

void dpllSatSolve_baseline(vector<shared_ptr<Formula>> conjuncts) {
    shared_ptr<satSolveStatus_baseline> status = satSolveInit_baseline(conjuncts);

    while (status->state == UNKNOWN_BASELINE && status->clausesLeft > 0) {
        shared_ptr<conjunctStatus_baseline> chosenConjunct = getLiteral_baseline(status);
        vector<shared_ptr<Formula>> literals = chosenConjunct->conjunct->getLiterals();
        shared_ptr<Formula> f = literals[0];

        addDecision_baseline(status, f, true);
        set_valuation_baseline(status, f, true);
        
        if (hasContradiction_baseline(status)) {
            status = handle_contradiction_baseline(status, f, true);
            if (hasContradiction_baseline(status)) {
                status->state = UNSAT_BASELINE;
            }
        }
        
        if (status->clausesLeft == 0) {
            status->state = SAT_BASELINE;
        }
    }
}
