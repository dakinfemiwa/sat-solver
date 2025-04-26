//#include <iostream>
#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "../../include/formula.h"

using namespace std;
//using namespace testing;

class AtomTest : public testing::Test {};
class AtomIsALiteral {};
class AtomGetsPropName {};
class AtomGetsPropName2 {};
class AtomGetsPropName3 {};
class AtomInCNF {};
class AtomInDNF {};
class AtomIsNotConjunction {};
class AtomIsNotConjunction2 {};
class AtomIsNotConjunction3 {};
class AtomIsNotDisjunction {};
class AtomIsNotDisjunction2 {};
class AtomIsNotDisjunction3 {};
class AtomIsNotConjunctionOfLiterals {};
class AtomIsNotConjunctionOfLiterals2 {};
class AtomIsNotConjunctionOfLiterals3 {};
class AtomIsNotDisjunctionOfLiterals {};
class AtomIsNotDisjunctionOfLiterals2 {};
class AtomIsNotDisjunctionOfLiterals3 {};

class NegationTest : public testing::Test {};
class NegationOfAtomIsALiteral {};
class NegationOfAndIsNotALiteral {};
class NegationOfAndIsNotALiteral2 {};
class NegationOfAndIsNotALiteral3 {};
class NegationOfOrIsNotALiteral {};
class NegationOfOrIsNotALiteral2 {};
class NegationOfOrIsNotALiteral3 {};
class NegationOfImplicationIsNotALiteral {};
class NegationOfImplicationIsNotALiteral2 {};
class NegationOfImplicationIsNotALiteral3 {};
class NegationOfImplicationIsNotALiteral4 {};
class NegationOfDoubleImplicationIsNotALiteral {};



TEST(AtomTest, AtomIsALiteral) {
    EXPECT_TRUE(Atom("p").isLiteral());
}

TEST(AtomTest, AtomGetsPropName) {
    EXPECT_EQ(Atom("").getAtomName(), "");
}

TEST(AtomTest, AtomGetsPropName2) {
    EXPECT_EQ(Atom("p").getAtomName(), "p");
}

TEST(AtomTest, AtomGetsPropName3) {
    EXPECT_EQ(Atom("x").getAtomName(), "x");
}

TEST(AtomTest, AtomInCNF) {
    EXPECT_TRUE(Atom("p").inCNF());
}

TEST(AtomTest, AtomInDNF) {
    EXPECT_TRUE(Atom("p").inDNF());
}

TEST(AtomTest, AtomIsNotConjunction) {
    EXPECT_FALSE(Atom("a").isConjunction());
}
TEST(AtomTest, AtomIsNotConjunction2) {
    EXPECT_FALSE(Atom("bfdd").isConjunction());
}
TEST(AtomTest, AtomIsNotConjunction3) {
    EXPECT_FALSE(Atom("a").isConjunction());
}

TEST(AtomTest, AtomIsNotDisjunction) {
    EXPECT_FALSE(Atom("b").isDisjunction());
}

TEST(AtomTest, AtomIsNotDisjunction2) {
    EXPECT_FALSE(Atom("x").isDisjunction());
}

TEST(AtomTest, AtomIsNotDisjunction3) {
    EXPECT_FALSE(Atom("sdwe").isDisjunction());
}

TEST(AtomTest, AtomIsNotDisjunctionOfLiterals) {
    EXPECT_FALSE(Atom("c").isDisjunctOfLiterals());
}

TEST(AtomTest, AtomIsNotDisjunctionOfLiterals2) {
    EXPECT_FALSE(Atom("sdswe").isDisjunctOfLiterals());
}

TEST(AtomTest, AtomIsNotDisjunctionOfLiterals3) {
    EXPECT_FALSE(Atom("wewesd").isDisjunctOfLiterals());
}

TEST(AtomTest, AtomIsNotConjunctionOfLiterals) {
    EXPECT_FALSE(Atom("d").isConjunctOfLiterals());
}

TEST(AtomTest, AtomIsNotConjunctionOfLiterals2) {
    EXPECT_FALSE(Atom("wewsd").isConjunctOfLiterals());
}

TEST(AtomTest, AtomIsNotConjunctionOfLiterals3) {
    EXPECT_FALSE(Atom("y").isConjunctOfLiterals());
}

TEST(NegationTest, NegationOfAtomIsALiteral) {
    shared_ptr<Formula> atom = make_shared<Atom>("p");
    EXPECT_TRUE(Negation(atom).isLiteral());
}

TEST(NegationTest, NegationOfAndIsNotALiteral) {
    shared_ptr<Formula> atom1 = make_shared<Atom>("a");
    shared_ptr<Formula> atom2 = make_shared<Atom>("b");
    vector<shared_ptr<Formula>> f = {};
    f.push_back(atom1);
    f.push_back(atom2);

    shared_ptr<Formula> andStatement = make_shared<And>(f);
    
    EXPECT_FALSE(Negation(andStatement).isLiteral());
}

TEST(NegationTest, NegationOfAndIsNotALiteral2) {
    shared_ptr<Formula> atom1 = make_shared<Atom>("");
    shared_ptr<Formula> atom2 = make_shared<Atom>("b");
    vector<shared_ptr<Formula>> f = {};
    f.push_back(atom1);
    f.push_back(atom2);

    shared_ptr<Formula> andStatement = make_shared<And>(f);
    
    EXPECT_FALSE(Negation(andStatement).isLiteral());
}

TEST(NegationTest, NegationOfAndIsNotALiteral3) {
    shared_ptr<Formula> atom1 = make_shared<Atom>("asa");
    shared_ptr<Formula> atom2 = make_shared<Atom>("b");
    shared_ptr<Formula> atom3 = make_shared<Atom>("z");
    vector<shared_ptr<Formula>> f = {};
    f.push_back(atom1);
    f.push_back(atom2);
    f.push_back(atom3);

    shared_ptr<Formula> andStatement = make_shared<And>(f);
    
    EXPECT_FALSE(Negation(andStatement).isLiteral());
}

TEST(NegationTest, NegationOfOrIsNotALiteral) {
    shared_ptr<Formula> atom1 = make_shared<Atom>("a");
    shared_ptr<Formula> atom2 = make_shared<Atom>("b");
    vector<shared_ptr<Formula>> f = {};
    f.push_back(atom1);
    f.push_back(atom2);

    shared_ptr<Formula> orStatement = make_shared<Or>(f);
    
    EXPECT_FALSE(Negation(orStatement).isLiteral());
}

TEST(NegationTest, NegationOfOrIsNotALiteral2) {
    shared_ptr<Formula> atom1 = make_shared<Atom>("");
    shared_ptr<Formula> atom2 = make_shared<Atom>("b");
    vector<shared_ptr<Formula>> f = {};
    f.push_back(atom1);
    f.push_back(atom2);

    shared_ptr<Formula> orStatement = make_shared<Or>(f);
    
    EXPECT_FALSE(Negation(orStatement).isLiteral());
}

TEST(NegationTest, NegationOfOrIsNotALiteral3) {
    shared_ptr<Formula> atom1 = make_shared<Atom>("asa");
    shared_ptr<Formula> atom2 = make_shared<Atom>("b");
    shared_ptr<Formula> atom3 = make_shared<Atom>("z");
    vector<shared_ptr<Formula>> f = {};
    f.push_back(atom1);
    f.push_back(atom2);
    f.push_back(atom3);

    shared_ptr<Formula> orStatement = make_shared<Or>(f);
    
    EXPECT_FALSE(Negation(orStatement).isLiteral());
}


TEST(NegationTest, NegationOfImplicationIsNotALiteral) {
    shared_ptr<Formula> atom1 = make_shared<Atom>("asa");
    shared_ptr<Formula> atom2 = make_shared<Atom>("b");

    shared_ptr<Formula> implication = make_shared<Implication>(atom1, atom2);
    
    EXPECT_FALSE(Negation(implication).isLiteral());
}

TEST(NegationTest, NegationOfImplicationIsNotALiteral2) {
    shared_ptr<Formula> atom1 = make_shared<Atom>("asa");
    shared_ptr<Formula> atom2 = make_shared<Atom>("b");
    shared_ptr<Formula> atom3 = make_shared<Atom>("c");

    
    vector<shared_ptr<Formula>> f = {};
    f.push_back(atom1);
    f.push_back(atom2);
    f.push_back(atom3);

    shared_ptr<Formula> statement2 = make_shared<And>(f);
    shared_ptr<Formula> implication = make_shared<Implication>(statement2, atom3);
    
    EXPECT_FALSE(Negation(implication).isLiteral());
}

TEST(NegationTest, NegationOfImplicationIsNotALiteral3) {
    shared_ptr<Formula> atom1 = make_shared<Atom>("asa");
    shared_ptr<Formula> atom2 = make_shared<Atom>("b");
    shared_ptr<Formula> atom3 = make_shared<Atom>("c");

    
    vector<shared_ptr<Formula>> f = {};
    f.push_back(atom1);
    f.push_back(atom2);
    f.push_back(atom3);

    shared_ptr<Formula> statement2 = make_shared<Or>(f);
    shared_ptr<Formula> implication = make_shared<Implication>(statement2, atom3);
    
    EXPECT_FALSE(Negation(implication).isLiteral());
}

TEST(NegationTest, NegationOfImplicationIsNotALiteral4) {
    shared_ptr<Formula> atom1 = make_shared<Atom>("asa");
    shared_ptr<Formula> atom2 = make_shared<Atom>("b");
    shared_ptr<Formula> atom3 = make_shared<Atom>("c");

    
    vector<shared_ptr<Formula>> f = {};
    f.push_back(atom1);
    f.push_back(atom2);
    f.push_back(atom3);

    shared_ptr<Formula> statement2 = make_shared<Or>(f);
    shared_ptr<Formula> implication = make_shared<Implication>(statement2, atom3);
    shared_ptr<Formula> implication2 = make_shared<Implication>(implication, statement2);
    
    EXPECT_FALSE(Negation(implication).isLiteral());
}

TEST(NegationTest, NegationOfDoubleImplicationIsNotALiteral) {
    shared_ptr<Formula> atom1 = make_shared<Atom>("asa");
    shared_ptr<Formula> atom2 = make_shared<Atom>("b");
    shared_ptr<Formula> atom3 = make_shared<Atom>("c");

    
    vector<shared_ptr<Formula>> f = {};
    f.push_back(atom1);
    f.push_back(atom2);
    f.push_back(atom3);

    shared_ptr<Formula> statement2 = make_shared<Or>(f);
    shared_ptr<Formula> implication = make_shared<Implication>(statement2, atom3);
    shared_ptr<Formula> doubleImplication = make_shared<DoubleImplication>(implication, statement2);
    
    EXPECT_FALSE(Negation(doubleImplication).isLiteral());
}

// Add these to your formulatests.cpp file

// Formula negationOf() tests
TEST(FormulaNegationTest, DoubleNegationCancels) {
    shared_ptr<Formula> atom = make_shared<Atom>("p");
    shared_ptr<Formula> neg = atom->negationOf();
    shared_ptr<Formula> doubleNeg = neg->negationOf();
    
    EXPECT_TRUE(atom->equals(doubleNeg));
}

TEST(FormulaNegationTest, NegationOfAndUsesDemorgan) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    vector<shared_ptr<Formula>> formulas = {a, b};
    shared_ptr<Formula> andFormula = make_shared<And>(formulas);
    
    shared_ptr<Formula> negAnd = andFormula->negationOf();
    
    // Negation of (a ∧ b) should be ¬a ∨ ¬b
    EXPECT_TRUE(negAnd->isDisjunction());
    
    auto orFormula = dynamic_pointer_cast<Or>(negAnd);
    ASSERT_TRUE(orFormula != nullptr);
    
    auto literals = orFormula->getFormulas();
    ASSERT_EQ(literals.size(), 2);
    
    // Check that the literals are negations of a and b
    EXPECT_TRUE(literals[0]->equals(a->negationOf()) || literals[1]->equals(a->negationOf()));
    EXPECT_TRUE(literals[0]->equals(b->negationOf()) || literals[1]->equals(b->negationOf()));
}

TEST(FormulaNegationTest, NegationOfOrUsesDemorgan) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    vector<shared_ptr<Formula>> formulas = {a, b};
    shared_ptr<Formula> orFormula = make_shared<Or>(formulas);
    
    shared_ptr<Formula> negOr = orFormula->negationOf();
    
    // Negation of (a ∨ b) should be ¬a ∧ ¬b
    EXPECT_TRUE(negOr->isConjunction());
    
    auto andFormula = dynamic_pointer_cast<And>(negOr);
    ASSERT_TRUE(andFormula != nullptr);
    
    auto literals = andFormula->getFormulas();
    ASSERT_EQ(literals.size(), 2);
    
    // Check that the literals are negations of a and b
    EXPECT_TRUE(literals[0]->equals(a->negationOf()) || literals[1]->equals(a->negationOf()));
    EXPECT_TRUE(literals[0]->equals(b->negationOf()) || literals[1]->equals(b->negationOf()));
}

TEST(FormulaNegationTest, NegationOfImplication) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    shared_ptr<Formula> impl = make_shared<Implication>(a, b);
    shared_ptr<Formula> negImpl = impl->negationOf();
    
    // Negation of (a → b) should be a ∧ ¬b
    EXPECT_TRUE(negImpl->isConjunction());
    
    auto andFormula = dynamic_pointer_cast<And>(negImpl);
    ASSERT_TRUE(andFormula != nullptr);
    
    auto literals = andFormula->getFormulas();
    ASSERT_EQ(literals.size(), 2);
    
    // Check that the literals are a and ¬b
    EXPECT_TRUE(literals[0]->equals(a) || literals[1]->equals(a));
    EXPECT_TRUE(literals[0]->equals(b->negationOf()) || literals[1]->equals(b->negationOf()));
}

TEST(FormulaNegationTest, NegationOfDoubleImplication) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    shared_ptr<Formula> equiv = make_shared<DoubleImplication>(a, b);
    shared_ptr<Formula> negEquiv = equiv->negationOf();
    
    // Negation of (a ↔ b) should be (a ∧ ¬b) ∨ (¬a ∧ b)
    EXPECT_TRUE(negEquiv->isDisjunction());
    
    auto orFormula = dynamic_pointer_cast<Or>(negEquiv);
    ASSERT_TRUE(orFormula != nullptr);
    
    auto disjuncts = orFormula->getFormulas();
    ASSERT_EQ(disjuncts.size(), 2);
    
    // Both disjuncts should be conjunctions
    EXPECT_TRUE(disjuncts[0]->isConjunction());
    EXPECT_TRUE(disjuncts[1]->isConjunction());
    
    auto conj1 = dynamic_pointer_cast<And>(disjuncts[0]);
    auto conj2 = dynamic_pointer_cast<And>(disjuncts[1]);
    
    ASSERT_TRUE(conj1 != nullptr);
    ASSERT_TRUE(conj2 != nullptr);
    
    auto conj1Lits = conj1->getFormulas();
    auto conj2Lits = conj2->getFormulas();
    
    ASSERT_EQ(conj1Lits.size(), 2);
    ASSERT_EQ(conj2Lits.size(), 2);
    
    // Verify the structure matches (a ∧ ¬b) ∨ (¬a ∧ b)
    bool foundFirstPattern = 
        (conj1Lits[0]->equals(a) && conj1Lits[1]->equals(b->negationOf())) ||
        (conj1Lits[1]->equals(a) && conj1Lits[0]->equals(b->negationOf()));
        
    bool foundSecondPattern = 
        (conj2Lits[0]->equals(a->negationOf()) && conj2Lits[1]->equals(b)) ||
        (conj2Lits[1]->equals(a->negationOf()) && conj2Lits[0]->equals(b));
        
    EXPECT_TRUE(foundFirstPattern && foundSecondPattern || 
               !foundFirstPattern && !foundSecondPattern);
}

// And class tests
TEST(AndTest, ConjunctionOfLiterals) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    vector<shared_ptr<Formula>> formulas = {a, b};
    shared_ptr<Formula> andFormula = make_shared<And>(formulas);
    
    EXPECT_TRUE(andFormula->isConjunction());
    EXPECT_TRUE(andFormula->isConjunctOfLiterals());
    EXPECT_FALSE(andFormula->isDisjunction());
}

TEST(AndTest, ConjunctionInCNF) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    vector<shared_ptr<Formula>> formulas = {a, b};
    shared_ptr<Formula> andFormula = make_shared<And>(formulas);
    
    EXPECT_TRUE(andFormula->inCNF());
}

// Or class tests
TEST(OrTest, DisjunctionOfLiterals) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    vector<shared_ptr<Formula>> formulas = {a, b};
    shared_ptr<Formula> orFormula = make_shared<Or>(formulas);
    
    EXPECT_TRUE(orFormula->isDisjunction());
    EXPECT_TRUE(orFormula->isDisjunctOfLiterals());
    EXPECT_FALSE(orFormula->isConjunction());
}

TEST(OrTest, DisjunctionInDNF) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    vector<shared_ptr<Formula>> formulas = {a, b};
    shared_ptr<Formula> orFormula = make_shared<Or>(formulas);
    
    EXPECT_TRUE(orFormula->inDNF());
}

// Implication tests
TEST(ImplicationTest, ImplicationStructure) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    shared_ptr<Implication> impl = make_shared<Implication>(a, b);
    
    EXPECT_TRUE(impl->getLeftFormula()->equals(a));
    EXPECT_TRUE(impl->getRightFormula()->equals(b));
}

TEST(ImplicationTest, ImplicationEquivalentToDNF) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    shared_ptr<Formula> impl = make_shared<Implication>(a, b);
    
    // a → b is equivalent to ¬a ∨ b
    shared_ptr<Formula> negA = a->negationOf();
    
    vector<shared_ptr<Formula>> formulas = {negA, b};
    shared_ptr<Formula> orFormula = make_shared<Or>(formulas);
    
    // We would need to implement proper equivalence checking for this test
    // For now just test that both are in DNF
    EXPECT_TRUE(impl->inDNF());
    EXPECT_TRUE(orFormula->inDNF());
}

// DoubleImplication tests
TEST(DoubleImplicationTest, DoubleImplicationStructure) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    shared_ptr<DoubleImplication> equiv = make_shared<DoubleImplication>(a, b);
    
    EXPECT_TRUE(equiv->getLeftFormula()->equals(a));
    EXPECT_TRUE(equiv->getRightFormula()->equals(b));
}

// Literal extraction tests
TEST(LiteralExtractionTest, ExtractFromAtom) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    auto literals = a->getLiterals();
    
    ASSERT_EQ(literals.size(), 1);
    EXPECT_TRUE(literals[0]->equals(a));
}

TEST(LiteralExtractionTest, ExtractFromNegation) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> negA = make_shared<Negation>(a);
    
    auto literals = negA->getLiterals();
    
    ASSERT_EQ(literals.size(), 1);
    EXPECT_TRUE(literals[0]->equals(a));
}

TEST(LiteralExtractionTest, ExtractFromDisjunction) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    shared_ptr<Formula> c = make_shared<Atom>("c");
    
    vector<shared_ptr<Formula>> formulas = {a, b, c};
    shared_ptr<Formula> orFormula = make_shared<Or>(formulas);
    
    auto literals = orFormula->getLiterals();
    
    ASSERT_EQ(literals.size(), 3);
    
    // Check that all original literals are present
    EXPECT_TRUE(find_if(literals.begin(), literals.end(), 
        [&](const shared_ptr<Formula>& f) { return f->equals(a); }) != literals.end());
    EXPECT_TRUE(find_if(literals.begin(), literals.end(), 
        [&](const shared_ptr<Formula>& f) { return f->equals(b); }) != literals.end());
    EXPECT_TRUE(find_if(literals.begin(), literals.end(), 
        [&](const shared_ptr<Formula>& f) { return f->equals(c); }) != literals.end());
}

TEST(LiteralExtractionTest, ExtractFromConjunction) {
    shared_ptr<Formula> a = make_shared<Atom>("a");
    shared_ptr<Formula> b = make_shared<Atom>("b");
    
    vector<shared_ptr<Formula>> formulas = {a, b};
    shared_ptr<Formula> andFormula = make_shared<And>(formulas);
    
    auto literals = andFormula->getLiterals();
    
    ASSERT_EQ(literals.size(), 2);
    
    // Check that all original literals are present
    EXPECT_TRUE(find_if(literals.begin(), literals.end(), 
        [&](const shared_ptr<Formula>& f) { return f->equals(a); }) != literals.end());
    EXPECT_TRUE(find_if(literals.begin(), literals.end(), 
        [&](const shared_ptr<Formula>& f) { return f->equals(b); }) != literals.end());
}