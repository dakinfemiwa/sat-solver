#include <string>
#include <type_traits>
#include <vector>
#include <memory>

using namespace std;

enum Value { NOVALUE, TRUE, FALSE };

class Formula {
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

        virtual vector<Formula> getLiterals() {
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

        bool inDNF() {
            return true;
        }


    private:
        shared_ptr<Formula> formula;
};


class And : public Formula {
    public:
        And(vector<shared_ptr<Formula>>& formulas) : formulas(formulas) {}

        bool isConjunction() {
            return true;
        }

        vector<shared_ptr<Formula>> getFormulas() {
            return this->formulas;
        }

        bool isConjunctOfLiterals() {
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
            
    
    private:
        vector<shared_ptr<Formula>> &formulas;
    
};

class Or : public Formula {
    public:
        Or(vector<shared_ptr<Formula>> formulas) : formulas(formulas) {}

        bool isDisjunction() {
            return true;
        }

        vector<shared_ptr<Formula>> getFormulas() {
            return this->formulas;
        }


        bool isDisjunctOfLiterals() {
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
    
    private:
        shared_ptr<Formula> leftFormula;
        shared_ptr<Formula> rightFormula;
    
};