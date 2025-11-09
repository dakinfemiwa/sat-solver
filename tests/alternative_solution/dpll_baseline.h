/*
BASELINE DPLL SAT Solver Header - Linear Search Version
*/

#ifndef DPLL_BASELINE_H
#define DPLL_BASELINE_H

#include <vector>
#include <memory>
#include "../../include/formula.h"

using namespace std;

// Main DPLL solver function using baseline (linear search) implementation
void dpllSatSolve_baseline(vector<shared_ptr<Formula>> conjuncts);

#endif // DPLL_BASELINE_H
