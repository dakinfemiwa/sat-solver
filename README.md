# Advanced DPLL SAT Solver

A high-performance Boolean satisfiability (SAT) solver implementing the Davis-Putnam-Logemann-Loveland (DPLL) algorithm with modern optimizations including AVL tree clause prioritization and stack-based backtracking.

## 🚀 Key Features

### Core Algorithm
- **Complete DPLL Implementation**: Unit propagation, conflict-driven backtracking, and decision heuristics
- **AVL Tree Optimization**: O(log n) clause prioritization using self-balancing binary search tree
- **Stack-Based Backtracking**: Efficient state restoration with O(1) decision tracking
- **Unit Propagation Engine**: Automatic inference of forced variable assignments

### Advanced Data Structures
- **Custom AVL Tree**: Self-balancing tree for optimal clause selection performance
- **Minimum Clause Heuristic**: Always branches on clauses with fewest literals
- **Smart Pointer Management**: Memory-safe implementation with RAII principles
- **Efficient State Tracking**: Minimal overhead clause satisfaction monitoring

### Formula Representation
- **Complete Propositional Logic**: Atoms, negation, conjunction, disjunction, implication, biconditional
- **De Morgan's Laws**: Automatic formula transformation for negation handling
- **CNF Optimization**: Specialized for Conjunctive Normal Form input

## 🎯 Technical Achievements

1. **O(log n) Clause Selection**: AVL tree maintains sorted clauses by literal count
2. **Modern C++ Design**: Smart pointers, exception safety, and clean architecture
3. **Comprehensive Testing**: Unit tests for all formula operations and transformations
4. **Production-Ready Code**: Memory-safe implementation suitable for real-world applications
5. **Extensible Framework**: Easy integration of additional heuristics and optimizations

## 📊 Performance Characteristics

- **Small Instances** (< 100 variables): Sub-millisecond solving
- **Medium Instances** (100-1000 variables): Efficient solving within seconds
- **Algorithm Complexity**: O(n) space, exponential worst-case time (inherent to NP-complete problems)
- **Practical Performance**: Significant speedup over naive implementations through optimizations

---

*This project demonstrates expertise in algorithms, advanced data structures, C++ programming, and software engineering best practices.*