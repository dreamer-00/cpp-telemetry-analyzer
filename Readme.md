# 🚀 C++ Telemetry Analyzer

A C++ project that simulates a high-frequency telemetry pipeline by generating millions of data points, computing volatility (standard deviation), and benchmarking processing performance.

This project is inspired by real-world systems used in **high-frequency trading, satellite telemetry, and real-time analytics**.

---

## 🧠 Overview

The project consists of two main components:

### 1. Generator (`generator.cpp`)

Generates a large dataset (default: **5,000,000 samples**) of random integers and writes them to `data.txt`.

This simulates incoming telemetry / market data.

### 2. Engine (`engine.cpp`)

Reads the generated data, computes:

- Total samples
- Mean
- Volatility (Standard Deviation)

It also benchmarks how long the entire computation takes using `std::chrono`.

The analyzer measures **real execution time**, similar to how low-latency systems evaluate performance.

---

## 📂 Project Structure

cpp-telemetry-analyzer/
├── generator.cpp # Generates massive telemetry dataset
├── engine.cpp # Processes data + benchmarks execution
├── data.txt # Generated dataset (created at runtime)
└── README.md

---

## ⚙️ How It Works

### Step 1 — Generate Data

Compile and run:

````bash
g++ generator.cpp -O2 -o generator
./generator

---

## ⚙️ How It Works

### Step 1 — Generate Data

Compile and run:

```bash
g++ generator.cpp -O2 -o generator
./generator

---

## ⚙️ How It Works

### Step 1 — Generate Data

Compile and run:
```bash
g++ generator.cpp -O2 -o generator
./generator
This creates data.txt containing millions of random values.

### Step 2 — Analyze + Benchmark

Compile and run:
g++ engine.cpp -O2 -o engine
./engine

### Example output:

    Samples: 5000000
    Mean: 50.47
    Volatility: 28.82
    Processing Time: 410 ms

📐 Volatility Formula

Standard Deviation is computed as:
    *sqrt( Σ(x − mean)² / N )*
This is the same metric commonly used in finance (price volatility) and signal processing (noise estimation).
⏱ Benchmarking

### Execution time is measured using:
    std::chrono::high_resolution_clock


Timing starts before file reading and ends after volatility calculation, giving an end-to-end performance metric.

The code is compiled with -O2 to enable compiler optimizations.

🎯 Key Concepts Demonstrated

Large-scale data generation
File I/O in C++
Vector-based data ingestion
Statistical computation (mean + standard deviation)
Performance benchmarking with std::chrono
Compiler optimization (-O2)
Basic telemetry pipeline design

🧪 Why This Project Exists

### This project was built to understand:

How real systems process large numeric streams
How volatility is computed in practice
How execution time is measured in performance-critical software
How to structure multi-stage C++ pipelines

### It serves as a foundational systems project before moving toward:
Streaming algorithms (no vectors)
Numerically stable variance (Welford)
Cache-aware processing
Low-latency design

🚧 Future Improvements

### Planned upgrades:

Streaming mean/variance (no full dataset storage)
Numerically stable volatility calculation
CSV support
Larger datasets
CPU cache optimization experiments

✅ Summary

From raw data to volatility metrics — a beginner-friendly C++ telemetry pipeline focused on performance awareness.

This project represents an early step into systems programming and real-time data analysis.
````
