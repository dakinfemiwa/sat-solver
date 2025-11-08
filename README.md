# DPLL SAT Solver

A high-performance Boolean satisfiability (SAT) solver implementing the Davis-Putnam-Logemann-Loveland (DPLL) algorithm with modern optimizations including AVL tree clause prioritization and stack-based backtracking.

## Key Features

### Core Algorithm
- **Complete DPLL Implementation**: Unit propagation and backtracking heuristics
- **AVL Tree Optimization**: O(log n) clause prioritization using self-balancing binary search tree
- **Stack-Based Backtracking**: Efficient state restoration with O(1) decision tracking
- **Unit Propagation Engine**: Automatic inference of forced variable assignments

### Data Structures
- **Custom AVL Tree**: Self-balancing tree for optimal clause selection performance
- **Minimum Clause Heuristic**: Always branches on clauses with fewest literals
