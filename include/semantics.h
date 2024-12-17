#include <cstddef>
#include <string>
#include <type_traits>
#include <vector>
#include <memory>
#include "formula.h"

//Might just use bool true and false


struct valuationMap {
    Formula f;
    bool value;
};

struct valuation {
    shared_ptr<Formula> f;
    bool value;
};
