#ifndef DPLL_H
#define DPLL_H

#include <memory>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "formula.h"
#include "satsolve.h"

void dpllSatSolve(vector<shared_ptr<Formula>> conjuncts); 


#endif