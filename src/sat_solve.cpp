#include <iostream>
#include "../include/formula.h"
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

enum formula_state {SAT, UNSAT, UNKNOWN};

//bad_valuations must always consist of unique keys
enum formula_state check_sat(shared_ptr<Formula> f, bool value,
unordered_map<shared_ptr<Formula>, bool> bad_valuations) {
    //Check if mapping exists
    if (bad_valuations.find(f) != bad_valuations.end()) {
        if (value == !bad_valuations[f]) {
            return UNSAT;
        }
    }
    bad_valuations.insert({f, value});
    return UNKNOWN;

}

//Chooses a literal and removes all the clauses that are "satisfied"
vector<shared_ptr<Formula>> choose_literal(Formula l, shared_ptr<And> conjunct) {
    vector<shared_ptr<Formula>> newConjuncts = {};
    vector<shared_ptr<Formula>> conjuncts = conjunct->getFormulas();
    for (shared_ptr<Formula> f : conjuncts) {
        if (f->isLiteral() && f->equals(l)) {
            newConjuncts.push_back(f);
        }
    }
    return newConjuncts;
}