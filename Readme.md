# 📊 High-Frequency Telemetry Analyzer (C++)

A high-performance C++ telemetry pipeline that generates millions of samples, computes statistical volatility (standard deviation), and benchmarks execution time using both single-threaded and multi-threaded analysis.

This project focuses on **systems-level performance**, not just correctness.

---

## 🎯 Project Goals

This project was built to understand:

- Large-scale data generation
- File I/O bottlenecks vs CPU computation
- Statistical volatility (standard deviation)
- Multithreaded computation (parallel reduction)
- Accurate benchmarking
- Real-world performance debugging

It simulates a simplified **high-frequency telemetry / analytics engine**.

---

## ✨ Features

### ✅ Data Generator
Generates millions of random integer samples and writes them to disk.

- Uses `std::mt19937`
- Produces realistic large datasets
- Avoids trivial “toy inputs”

---

### ✅ Analysis Engine

Computes:

- Mean
- Volatility (Standard Deviation)

Implements:

- Chunked workload splitting
- Multi-threaded variance calculation
- Safe thread-local accumulation
- Final reduction on main thread

Pattern used: **Parallel Reduction**

---

### ✅ Benchmarking

Uses `std::chrono` to measure **compute time only** (I/O excluded).

This exposes the real performance of the analytics engine rather than disk speed.

---

## 📂 Project Structure

telemetry-analyzer/
├── generator.cpp // Creates large dataset
├── engine.cpp // Multi-threaded analysis + benchmark
└── README.md


---

## ⚙️ Build Instructions

### Compile Generator

```bash
g++ generator.cpp -O2 -o generator
Run Generator
./generator
Creates:

data.txt
(≈ 5 million samples)

Compile Analyzer (Multi-Threaded)
g++ analyzer.cpp -O3 -pthread -o analyzer
Run Engine
./engine
🧪 Example Output
Samples: 5000000
Mean: 50.01
Volatility: 28.86
Time: 15 ms
(Timing measured only for computation, not file I/O.)
```

🧠 Key Engineering Lessons

1. Never Benchmark I/O With Compute
Initial measurements incorrectly included file reading and text parsing (~1.1s).

After isolating computation:

→ execution dropped to ~15ms.

This demonstrates a critical systems principle:

Always separate I/O from CPU benchmarking.

2. Parallel Reduction
Data is divided into equal chunks:

Thread 0 → chunk 0
Thread 1 → chunk 1
Thread 2 → chunk 2
Thread 3 → chunk 3
Each thread computes partial variance.
Main thread performs final reduction.

No locks.
No atomics.
No shared writes.

3. Memory Bandwidth Bound
At ~15ms for 5M elements, performance approaches hardware memory limits.

Further gains require:

Single-pass algorithms
SIMD
Memory-mapped files
Binary format
Not just “more threads”.

🚧 Possible Extensions

Parallel mean computation
Streaming Welford algorithm (single pass)
Binary file format (faster load)
Memory-mapped input
Cache-line optimization
CPU core auto-detection

✅ Summary
This project demonstrates a realistic telemetry analytics pipeline with emphasis on performance engineering rather than toy examples.

It covers:

Large data handling
Multithreading
Reduction patterns
Proper benchmarking
Bottleneck analysis
Built as a systems-focused learning project toward low-latency / high-performance C++.

🧑‍💻 Author Notes

This project intentionally avoids frameworks and abstractions to expose:
threading mechanics
memory behavior
performance limits

It is designed as a stepping stone toward HFT / game engine / infrastructure-style programming.
