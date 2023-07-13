#include "fib.h"
#include <benchmark/benchmark.h>

static void BM_fib_rec(benchmark::State& state) {
    Fibonacci fib;
    for (auto _ : state) {
        fib.fibVector.resize(state.range(0)+1);
        fib.fib_rec(state.range(0));
    }
}

static void BM_fib_memo(benchmark::State& state) {
    Fibonacci fib;
    for (auto _ : state) {
        fib.fibVector.resize(state.range(0)+1, -1);
        fib.fibVector[0] = 0;
        fib.fibVector[1] = 1;
        fib.fib_memo(state.range(0));
    }
}

static void BM_fib_dp(benchmark::State& state) {
    Fibonacci fib;
    for (auto _ : state) {
        fib.fibVector.resize(state.range(0)+1);
        fib.fibVector[0] = 0;
        fib.fibVector[1] = 1;
        fib.fib_dp(state.range(0));
    }
}

BENCHMARK(BM_fib_rec)->DenseRange(1, 1 << 5, 1);
BENCHMARK(BM_fib_memo)->DenseRange(1, 1 << 5, 1);
BENCHMARK(BM_fib_dp)->DenseRange(1, 1 << 5, 1);

BENCHMARK_MAIN();
