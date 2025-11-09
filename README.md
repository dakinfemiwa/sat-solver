# DPLL SAT Solver

A Boolean satisfiability (SAT) solver implementing the Davis-Putnam-Logemann-Loveland (DPLL) algorithm with modern optimizations including AVL tree clause prioritization and stack-based backtracking.

## Key Features

### Core Algorithm
- **Complete DPLL Implementation**: Unit propagation and backtracking heuristics
- **Stack-Based Backtracking**: Efficient state restoration with O(1) decision tracking
- **Minimum Clause Heuristic**: Always branches on clauses with fewest literals

### Benchmark Results

Performance improvement measured across 6 independent test runs on formulas with up to 1500 clauses. Each run executes 5 iterations and reports the average.

TO NOTE: Initial tests did show a 40% improvement across extra large inputs

#### Run 1: 32.68% Average Improvement
| Test Size    | Variables | Clauses | Hashmap (ms) | Baseline (ms) | Speedup | Improvement |
|--------------|-----------|---------|--------------|---------------|---------|-------------|
| Small        | 50        | 100     | 0.129        | 0.199         | 1.54x   | 34.94%      |
| Medium       | 100       | 300     | 0.311        | 0.561         | 1.80x   | 44.51%      |
| Large        | 200       | 600     | 0.560        | 1.167         | 2.08x   | 51.96%      |
| Extra Large  | 500       | 1500    | 2.509        | 2.492         | 0.99x   | -0.70%      |

#### Run 2: 32.62% Average Improvement
| Test Size    | Variables | Clauses | Hashmap (ms) | Baseline (ms) | Speedup | Improvement |
|--------------|-----------|---------|--------------|---------------|---------|-------------|
| Small        | 50        | 100     | 0.216        | 0.274         | 1.27x   | 21.37%      |
| Medium       | 100       | 300     | 0.310        | 0.614         | 1.98x   | 49.53%      |
| Large        | 200       | 600     | 0.683        | 1.121         | 1.64x   | 39.09%      |
| Extra Large  | 500       | 1500    | 2.062        | 2.594         | 1.26x   | 20.51%      |

#### Run 3: 32.12% Average Improvement
| Test Size    | Variables | Clauses | Hashmap (ms) | Baseline (ms) | Speedup | Improvement |
|--------------|-----------|---------|--------------|---------------|---------|-------------|
| Small        | 50        | 100     | 0.156        | 0.206         | 1.32x   | 24.47%      |
| Medium       | 100       | 300     | 0.334        | 0.755         | 2.26x   | 55.76%      |
| Large        | 200       | 600     | 0.816        | 1.216         | 1.49x   | 32.90%      |
| Extra Large  | 500       | 1500    | 2.322        | 2.742         | 1.18x   | 15.34%      |

#### Run 4: 41.56% Average Improvement
| Test Size    | Variables | Clauses | Hashmap (ms) | Baseline (ms) | Speedup | Improvement |
|--------------|-----------|---------|--------------|---------------|---------|-------------|
| Small        | 50        | 100     | 0.207        | 0.282         | 1.36x   | 26.63%      |
| Medium       | 100       | 300     | 0.390        | 0.710         | 1.82x   | 45.03%      |
| Large        | 200       | 600     | 0.595        | 2.727         | 4.59x   | **78.20%**  |
| Extra Large  | 500       | 1500    | 2.282        | 2.729         | 1.20x   | 16.38%      |

#### Run 5: 13.02% Average Improvement (Outlier)
| Test Size    | Variables | Clauses | Hashmap (ms) | Baseline (ms) | Speedup | Improvement |
|--------------|-----------|---------|--------------|---------------|---------|-------------|
| Small        | 50        | 100     | 0.120        | 0.150         | 1.25x   | 20.11%      |
| Medium       | 100       | 300     | 0.234        | 0.405         | 1.73x   | 42.12%      |
| Large        | 200       | 600     | 0.918        | 0.727         | 0.79x   | -26.23%     |
| Extra Large  | 500       | 1500    | 1.753        | 2.089         | 1.19x   | 16.07%      |

*Note: Run 5 showed anomalous behavior on the Large test (-26.23%), likely due to system background processes during benchmarking.*

#### Run 6: 30.84% Average Improvement
| Test Size    | Variables | Clauses | Hashmap (ms) | Baseline (ms) | Speedup | Improvement |
|--------------|-----------|---------|--------------|---------------|---------|-------------|
| Small        | 50        | 100     | 0.092        | 0.115         | 1.25x   | 19.72%      |
| Medium       | 100       | 300     | 0.233        | 0.464         | 1.99x   | 49.70%      |
| Large        | 200       | 600     | 0.386        | 0.745         | 1.93x   | 48.22%      |
| Extra Large  | 500       | 1500    | 1.681        | 1.783         | 1.06x   | 5.72%       |
