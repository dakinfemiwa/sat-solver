#include "../../include/satsolve.h"

int AVLTree::getHeight(shared_ptr<AVLNode> node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(shared_ptr<AVLNode> node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

shared_ptr<AVLNode> AVLTree::rotateRight(shared_ptr<AVLNode> y) {
    shared_ptr<AVLNode> x = y->left;
    shared_ptr<AVLNode> T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    
    return x;
}

shared_ptr<AVLNode> AVLTree::rotateLeft(shared_ptr<AVLNode> x) {
    shared_ptr<AVLNode> y = x->right;
    shared_ptr<AVLNode> T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    
    return y;
}

shared_ptr<AVLNode> AVLTree::insert(shared_ptr<AVLNode> node, shared_ptr<conjunctStatus> clause) {
    // Standard BST insertion
    if (!node) {
        return make_shared<AVLNode>(clause);
    }
    
    if (clause->conjunctCount < node->clause->conjunctCount) {
        node->left = insert(node->left, clause);
    } else if (clause->conjunctCount > node->clause->conjunctCount) {
        node->right = insert(node->right, clause);
    } else {
        // Equal counts - insert to left for consistency
        node->left = insert(node->left, clause);
    }
    
    // Update height
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    
    // Get balance factor
    int balance = getBalance(node);
    
    // Left Left Case
    if (balance > 1 && clause->conjunctCount < node->left->clause->conjunctCount) {
        return rotateRight(node);
    }
    
    // Right Right Case
    if (balance < -1 && clause->conjunctCount > node->right->clause->conjunctCount) {
        return rotateLeft(node);
    }
    
    // Left Right Case
    if (balance > 1 && clause->conjunctCount > node->left->clause->conjunctCount) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Right Left Case
    if (balance < -1 && clause->conjunctCount < node->right->clause->conjunctCount) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

shared_ptr<AVLNode> AVLTree::findMin(shared_ptr<AVLNode> node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

shared_ptr<AVLNode> AVLTree::remove(shared_ptr<AVLNode> node, shared_ptr<conjunctStatus> clause) {
    if (!node) return node;
    
    if (clause->conjunctCount < node->clause->conjunctCount) {
        node->left = remove(node->left, clause);
    } else if (clause->conjunctCount > node->clause->conjunctCount) {
        node->right = remove(node->right, clause);
    } else if (node->clause == clause) {
        // Found the node to delete
        if (!node->left || !node->right) {
            shared_ptr<AVLNode> temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
        } else {
            shared_ptr<AVLNode> temp = findMin(node->right);
            node->clause = temp->clause;
            node->right = remove(node->right, temp->clause);
        }
    } else {
        // Same count but different clause - search both subtrees
        node->left = remove(node->left, clause);
        node->right = remove(node->right, clause);
    }
    
    if (!node) return node;
    
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    
    int balance = getBalance(node);
    
    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }
    
    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }
    
    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

void AVLTree::collectUnsatisfied(shared_ptr<AVLNode> node, vector<shared_ptr<conjunctStatus>>& result) {
    if (!node) return;
    
    collectUnsatisfied(node->left, result);
    if (!node->clause->satisfiedClause.satisfied) {
        result.push_back(node->clause);
    }
    collectUnsatisfied(node->right, result);
}

void AVLTree::insert(shared_ptr<conjunctStatus> clause) {
    root = insert(root, clause);
}

void AVLTree::remove(shared_ptr<conjunctStatus> clause) {
    root = remove(root, clause);
}

shared_ptr<conjunctStatus> AVLTree::getSmallestUnsatisfied() {
    vector<shared_ptr<conjunctStatus>> unsatisfied;
    collectUnsatisfied(root, unsatisfied);
    
    if (unsatisfied.empty()) return nullptr;
    
    // Find smallest conjunctCount among unsatisfied
    shared_ptr<conjunctStatus> smallest = unsatisfied[0];
    for (auto& clause : unsatisfied) {
        if (clause->conjunctCount < smallest->conjunctCount) {
            smallest = clause;
        }
    }
    
    return smallest;
}

void AVLTree::rebuild(vector<shared_ptr<conjunctStatus>>& clauses) {
    root = nullptr;
    for (auto& clause : clauses) {
        insert(clause);
    }
}

bool AVLTree::isEmpty() {
    return root == nullptr;
}