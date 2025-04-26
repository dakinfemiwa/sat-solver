/*
Utilises structs and utility helper functions to carry out CDCL algorithm with 
heurestics like VSIDs
*/

#include <algorithm>
#include "../include/satsolve.h"
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

vector<shared_ptr<Formula>> takeLiteralOutOfDisjunct(shared_ptr<Or> disjunction) {
    vector<shared_ptr<Formula>> formulas = disjunction->getLiterals();
    //formulas.erase(remove_if(formulas.begin(), formulas.end(), ), formulas.end())
    return {};
}

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
vector<shared_ptr<Formula>> choose_literal(shared_ptr<Formula> l, shared_ptr<And> conjunct) {
    vector<shared_ptr<Formula>> newConjuncts = {};
    vector<shared_ptr<Formula>> conjuncts = conjunct->getFormulas();
    for (shared_ptr<Formula> f : conjuncts) {
        if (!f->isLiteral() || !f->equals(l)  || !f->equals(make_shared<Negation>(l))) {
            newConjuncts.push_back(f);
        }
        //f is a disjunction of literals (f being a literal was handled in the first if statement)
        
        vector<shared_ptr<Formula>> disjunctsInLiterals = f->getLiterals();
        vector<shared_ptr<Formula>> newdisjunctionOfLiterals;
        copy_if(disjunctsInLiterals.begin(), disjunctsInLiterals.end(), 
        newdisjunctionOfLiterals, 
        [l] (shared_ptr<Formula> f)
             {return f->equals(l) || f->equals(make_shared<Negation>(l));});

        //TODO: ensure that if neg a is selected, instances of a are removed
    

    }
    return newConjuncts;
}