#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct PartialResult {
    double sum = 0.0;
    double variance = 0.0;
};

void worker(const vector<int>& data,
            size_t start,
            size_t end,
            double mean,
            PartialResult& result)
{
    double localSum = 0.0;
    double localVar = 0.0;

    for (size_t i = start; i < end; i++) {
        localSum += data[i];
    }

    for (size_t i = start; i < end; i++) {
        double diff = data[i] - mean;
        localVar += diff * diff;
    }

    result.sum = localSum;
    result.variance = localVar;
}

int main() {
    ifstream file("data.txt");
    if (!file.is_open()) {
        cerr << "Cannot open file\n";
        return 1;
    }

    vector<int> data;
    int x;
    while (file >> x) data.push_back(x);
    auto startTime = high_resolution_clock::now();

    size_t N = data.size();
    cout << "Samples: " << N << endl;

    // ---------- MEAN (single thread first) ----------

    double mean = 0.0;
    for (int v : data) mean += v;
    mean /= N;

    // ---------- MULTI THREADED VARIANCE ----------

    const int THREADS = 4;
    vector<thread> workers;
    PartialResult results[THREADS];

    size_t block = N / THREADS;

    for (int i = 0; i < THREADS; i++) {
        size_t begin = i * block;
        size_t end = (i == THREADS - 1) ? N : begin + block;

        workers.emplace_back(worker,
                             cref(data),
                             begin,
                             end,
                             mean,
                             ref(results[i]));
    }

    for (auto& t : workers)
        t.join();

    double totalVar = 0.0;
    for (int i = 0; i < THREADS; i++)
        totalVar += results[i].variance;

    double stddev = sqrt(totalVar / N);

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);

    cout << "Mean: " << mean << endl;
    cout << "Volatility: " << stddev << endl;
    cout << "Time: " << duration.count() << " ms\n";
}
