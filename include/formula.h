#include <string>
#include <type_traits>
#include <vector>
#include <memory>

using namespace std;
class Formula;
class Negation;
class Or;
//enum Value { NOVALUE, TRUE, FALSE };

class Formula : public enable_shared_from_this<Formula> {
    public:
        virtual bool inCNF() {
            return false;
        }
        virtual bool isConjunction() {
            return false;
        }
        virtual bool isDisjunction() {
            return false;
        }
        virtual bool isConjunctOfLiterals() {
            return false;
        }
        virtual bool isDisjunctOfLiterals() {
            return false;
        }
        virtual bool isLiteral() {
            return false;
        }
        virtual bool isNegation() {
            return false;
        }

        virtual bool isAtom() {
            return false;
        }             

        virtual bool equals(shared_ptr<Formula> f) {
            return false;
        }

        virtual shared_ptr<Formula> negationOf() {
            return make_shared<Negation>(shared_from_this());
        }

        virtual vector<shared_ptr<Formula>> getLiterals() {
            return {};
        }

        virtual ~Formula() = default;
};

class Atom : public Formula {
    public:
        Atom(const string& name) : atomName(name) {}

        string getAtomName() const {
            return atomName;
        }

        bool isAtom() {
            return true;
        }        

        bool isLiteral() {
            return true;
        }

        bool inCNF() {
            return true;
        }

        bool inDNF() {
            return true;
        }

        bool equals(shared_ptr<Formula> f) {
            return false;
        }


        bool equals(shared_ptr<Atom> n) {
            return n->getAtomName() == getAtomName();
        }        

        vector<shared_ptr<Formula>> getLiterals() {            
            return {make_shared<Atom>(atomName)};
        }


    private:
        string atomName;
};

class Negation : public Formula {
    public:
        Negation(shared_ptr<Formula> formula) {
            this->formula = formula;
        }

        bool isLiteral() {
            return this->formula->isLiteral();
        }

        shared_ptr<Formula> getFormula() {
            return this->formula;
        }

        bool isNegation() {
            return true;
        }

        bool inCNF() {
            return true;
        }

        bool equals(shared_ptr<Formula> f) {
            return false;
        }

        bool equals(shared_ptr<Negation> n) {
            return n->getFormula() == getFormula();
        }

        bool inDNF() {
            return true;
        }

        shared_ptr<Formula> negationOf() {
            return formula;
        }

        vector<shared_ptr<Formula>> getLiterals() {
            if (formula->isAtom()) {
                return {formula};
            }
            return formula->getLiterals();
        }

    private:
        shared_ptr<Formula> formula;
};


class And : public Formula {
    public:
        And(vector<shared_ptr<Formula>> formulas) : formulas(formulas) {}

        bool isConjunction() override {
            return true;
        }

        vector<shared_ptr<Formula>> getFormulas() {
            return this->formulas;
        }

        bool isConjunctOfLiterals() override {
            bool conjunctOfLiterals = true;
            for (shared_ptr<Formula> f : formulas) {
                conjunctOfLiterals &= f->isLiteral() ;
            }
            return conjunctOfLiterals;
        }

        bool isCNF() {
            for (shared_ptr<Formula> f : formulas) {
                if (!f->isDisjunctOfLiterals() && !f->isLiteral()) {
                    return false;
                }
            }
            return true;
        }

        vector<shared_ptr<Formula>> getLiterals() override {
            if (formulas.empty()) {
                return {};
            }
            vector<shared_ptr<Formula>> literals = formulas.front()->getLiterals();

            for (int i = 1; i < formulas.size(); i++) {
                vector<shared_ptr<Formula>> newLiteralsList = formulas.at(i)->getLiterals();
                literals.insert(literals.end(), newLiteralsList.begin(), newLiteralsList.end());

            }
            return literals;
        }

        shared_ptr<Formula> negationOf() override {
            vector<shared_ptr<Formula>> negatedFormulas;
            for (const auto& f: formulas) {
                negatedFormulas.push_back(f->negationOf());
            }
            return make_shared<Or>(negatedFormulas);
        }
            
    
    private:
        vector<shared_ptr<Formula>> formulas;
    
};

class Or : public Formula {
    public:
        Or(vector<shared_ptr<Formula>> formulas) : formulas(formulas) {}

        bool isDisjunction() override {
            return true;
        }

        vector<shared_ptr<Formula>> getFormulas() {
            return this->formulas;
        }


        bool isDisjunctOfLiterals() override {
            for (shared_ptr<Formula> f: formulas) {
                if (!f->isLiteral()) return false;
            }
            return true;
        }

        bool isDNF() {
            for (shared_ptr<Formula> f: formulas) {
                if (!f->isConjunctOfLiterals() && !f->isLiteral()) {
                    return false;
                }
            }
            return true;
        }

        vector<shared_ptr<Formula>> getLiterals() override {
            if (formulas.empty()) {
                return {};
            }
            vector<shared_ptr<Formula>> literals = formulas.front()->getLiterals();

            for (int i = 1; i < formulas.size(); i++) {
                vector<shared_ptr<Formula>> newLiteralsList = formulas.at(i)->getLiterals();
                literals.insert(literals.end(), newLiteralsList.begin(), newLiteralsList.end());

            }
            return literals;
        }        

        shared_ptr<Formula> negationOf() override {
            vector<shared_ptr<Formula>> negatedFormulas;
            for (const auto& f: formulas) {
                negatedFormulas.push_back(f->negationOf());
            }
            return make_shared<And>(negatedFormulas);
        }        
    
    private:
        vector<shared_ptr<Formula>> formulas;
    
};

class Implication : public Formula {
    public:
        Implication(shared_ptr<Formula> leftFormula, shared_ptr<Formula> rightFormula) {
            this->leftFormula = leftFormula;
            this->rightFormula = rightFormula;
        }


        shared_ptr<Formula> getLeftFormula() const {
            return this->leftFormula;
        }

        shared_ptr<Formula> getRightFormula() const {
            return this->rightFormula;
        }

        vector<shared_ptr<Formula>> getLiterals() override {
            vector<shared_ptr<Formula>> literals = leftFormula->getLiterals();
            vector<shared_ptr<Formula>> literals2 = rightFormula->getLiterals();
            literals.insert(literals.end(), literals2.begin(), literals2.end());
            return literals;
        }

        shared_ptr<Formula> negationOf() override {
            // ¬(A → B) = A ∧ ¬B
            vector<shared_ptr<Formula>> conjuncts;
            conjuncts.push_back(leftFormula);
            conjuncts.push_back(rightFormula->negationOf());
            return make_shared<And>(conjuncts);
        }        
    
    private:
        shared_ptr<Formula> leftFormula;
        shared_ptr<Formula> rightFormula;
    
};

//Might remove as it's redundant
class DoubleImplication : public Formula {
    public:
        DoubleImplication(shared_ptr<Formula> leftFormula, shared_ptr<Formula> rightFormula) {
            this->leftFormula = leftFormula;
            this->rightFormula = rightFormula;
        }


        shared_ptr<Formula> getLeftFormula() const {
            return this->leftFormula;
        }

        shared_ptr<Formula> getRightFormula() const {
            return this->rightFormula;
        }            
    
        shared_ptr<Formula> negationOf() override {
            // ¬(A ↔ B) = (A ∧ ¬B) ∨ (¬A ∧ B)
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

    private:
        shared_ptr<Formula> leftFormula;
        shared_ptr<Formula> rightFormula;
    
};