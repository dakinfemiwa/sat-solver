# DPLL SAT Solver

A Boolean satisfiability (SAT) solver implementing the Davis-Putnam-Logemann-Loveland (DPLL) algorithm with modern optimizations including AVL tree clause prioritization and stack-based backtracking.

## Key Features

### Core Algorithm
- **Complete DPLL Implementation**: Unit propagation and backtracking heuristics
- **Stack-Based Backtracking**: Efficient state restoration with O(1) decision tracking
- **Unit Propagation**: Automatic inference of forced variable assignments
- **Minimum Clause Heuristic**: Always branches on clauses with fewest literals
