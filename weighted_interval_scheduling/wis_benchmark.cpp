#include "wis.h"
#include <iostream>
#include <benchmark/benchmark.h>

static void BM_weighted_interval_scheduling_rec(benchmark::State& state) {
    WeightedIntervalScheduling wis;
    wis.add_job(Job(0, 6, 60));
    wis.add_job(Job(1, 4, 30));
    wis.add_job(Job(3, 5, 10));
    wis.add_job(Job(5, 7, 30));
    wis.add_job(Job(5, 9, 50));
    wis.add_job(Job(7, 8, 10));
    wis.sort_jobs_by(wis.sort_by::END_TIME);  
    for (auto _ : state) {
        wis.weighted_interval_scheduling_rec(wis.jobs_size()-1);
    }
}

BENCHMARK(BM_weighted_interval_scheduling_rec);
BENCHMARK_MAIN();