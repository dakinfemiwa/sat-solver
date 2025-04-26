#include "../../include/formula.h"

shared_ptr<Formula> Formula::negationOf() {
    return make_shared<Negation>(shared_from_this());
}

shared_ptr<Formula> And::negationOf() {
    vector<shared_ptr<Formula>> negatedConjuncts;
    for (const auto& f: formulas) {
        negatedConjuncts.push_back(f->negationOf());
    }
    return make_shared<Or>(negatedConjuncts);
}

shared_ptr<Formula> Or::negationOf() {
    vector<shared_ptr<Formula>> negatedFormulas;
    for (const auto& f: formulas) {
        negatedFormulas.push_back(f->negationOf());
    }
    return make_shared<And>(negatedFormulas);
}

shared_ptr<Formula> Implication::negationOf() {
    vector<shared_ptr<Formula>> conjuncts;
    conjuncts.push_back(leftFormula);
    conjuncts.push_back(rightFormula->negationOf());
    return make_shared<And>(conjuncts);
}

shared_ptr<Formula> DoubleImplication::negationOf() {
    vector<shared_ptr<Formula>> leftConjuncts;
    leftConjuncts.push_back(leftFormula);
    leftConjuncts.push_back(rightFormula->negationOf());
    
    vector<shared_ptr<Formula>> rightConjuncts;
    rightConjuncts.push_back(leftFormula->negationOf());
    rightConjuncts.push_back(rightFormula);
    
    vector<shared_ptr<Formula>> disjuncts;
    disjuncts.push_back(make_shared<And>(leftConjuncts));
    disjuncts.push_back(make_shared<And>(rightConjuncts));
    
    return make_shared<Or>(disjuncts);
}   