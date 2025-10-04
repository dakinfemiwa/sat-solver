/*
Contains structures used in SAT solving algorithm
*/

#include <memory>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "formula.h"

using namespace std;

enum formula_state {SAT, UNSAT, UNKNOWN};

struct satisfiedClause {
    bool satisfied;
    shared_ptr<Formula> satisfyingLiteral;
};

struct conjunctStatus {
    shared_ptr<Formula> conjunct;
    satisfiedClause satisfiedClause;
    int level;
    int conjunctCount;
    int originalCount; // Store original count for backtracking
};

// Decision for backtracking
struct Decision {
    shared_ptr<Formula> literal;
    bool value;
    int level;
    vector<shared_ptr<conjunctStatus>> modifiedClauses;
    vector<int> originalCounts; // Store original counts for backtracking
};

// AVL Tree Node for clause prioritization
struct AVLNode {
    shared_ptr<conjunctStatus> clause;
    int height;
    shared_ptr<AVLNode> left;
    shared_ptr<AVLNode> right;
    
    AVLNode(shared_ptr<conjunctStatus> c) : clause(c), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    shared_ptr<AVLNode> root;
    
    int getHeight(shared_ptr<AVLNode> node);
    int getBalance(shared_ptr<AVLNode> node);
    shared_ptr<AVLNode> rotateRight(shared_ptr<AVLNode> y);
    shared_ptr<AVLNode> rotateLeft(shared_ptr<AVLNode> x);
    shared_ptr<AVLNode> insert(shared_ptr<AVLNode> node, shared_ptr<conjunctStatus> clause);
    shared_ptr<AVLNode> remove(shared_ptr<AVLNode> node, shared_ptr<conjunctStatus> clause);
    shared_ptr<AVLNode> findMin(shared_ptr<AVLNode> node);
    void collectUnsatisfied(shared_ptr<AVLNode> node, vector<shared_ptr<conjunctStatus>>& result);
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(shared_ptr<conjunctStatus> clause);
    void remove(shared_ptr<conjunctStatus> clause);
    shared_ptr<conjunctStatus> getSmallestUnsatisfied();
    void rebuild(vector<shared_ptr<conjunctStatus>>& clauses);
    bool isEmpty();
};

struct satSolveStatus {
    unordered_map<shared_ptr<Formula>, bool> valuations;
    unordered_map<shared_ptr<Formula>, bool> wrongValuations;
    vector<shared_ptr<conjunctStatus>> conjuncts;
    AVLTree clauseTree;
    int clausesLeft;
    formula_state state;
    
    // Backtracking stack
    stack<Decision> decisionStack;
    int currentLevel;
};

// Functions
shared_ptr<struct satSolveStatus> satSolveInit(vector<shared_ptr<Formula>> conjuncts);
void chooseLiteral(shared_ptr<Formula> literal, bool value, shared_ptr<struct satSolveStatus> status);
bool backtrack(shared_ptr<struct satSolveStatus> status);
shared_ptr<Formula> selectNextLiteral(shared_ptr<struct satSolveStatus> status);
bool unitPropagate(shared_ptr<struct satSolveStatus> status);
bool dpllSolve(shared_ptr<struct satSolveStatus> status);
bool solveSAT(vector<shared_ptr<Formula>> conjuncts);


