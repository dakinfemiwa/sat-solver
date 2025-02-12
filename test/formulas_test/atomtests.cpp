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