#include <iostream>
#include <gtest/gtest.h>
#include "../../include/formula.h"

using namespace std;

class AtomTest : public testing::Test {

};

class AtomIsALiteral {

};

TEST(AtomTest, AtomIsALiteral) {
    EXPECT_EQ(Atom("p").isLiteral(), true);

}
