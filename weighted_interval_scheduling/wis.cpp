#include "wis.h"
#include <iostream>

void WeightedIntervalScheduling::print_jobs()
{
    for (auto job : jobs)
    {
        std::cout << job << std::endl;
    }
}

void WeightedIntervalScheduling::sort_jobs_by(WeightedIntervalScheduling::sort_by sortby)
{
    // ...
    std::function<bool(Job, Job)> predicate;
    if (sortby == WeightedIntervalScheduling::sort_by::END_TIME) {
        predicate = [](Job a, Job b) { return a.finish < b.finish; };
    } else if (sortby == WeightedIntervalScheduling::sort_by::START_TIME) {
        predicate = [](Job a, Job b) { return a.start < b.start; };
    } else if (sortby == WeightedIntervalScheduling::sort_by::WEIGHT) {
        predicate = [](Job a, Job b) { return a.weight < b.weight; };
    }
    std::sort(jobs.begin(), jobs.end(), predicate);
}

int WeightedIntervalScheduling::findLastNonConflictingJob(int n)
{
    // Process suffixes of jobs[0..n-1]
    for (int i = n-1; i >= 0; i--) {
        if (jobs[i].finish <= jobs[n].start) {
            return i;
        }
    }
    return NON_CONFLICTING_JOB_NOT_FOUND;
}

int WeightedIntervalScheduling::weighted_interval_scheduling_rec(int n)
{
    // Handle the NON_CONFLICTING_JOB_NOT_FOUND case
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return jobs[0].weight;
    }
    int index = findLastNonConflictingJob(n); 
    int incl_job_n = jobs[n].weight + weighted_interval_scheduling_rec(index);
    int excl_job_n = weighted_interval_scheduling_rec(n-1);
    return std::max(incl_job_n, excl_job_n);
    
}

int WeightedIntervalScheduling::weighted_interval_scheduling_memo(int n)
{
    // Handle the NON_CONFLICTING_JOB_NOT_FOUND case
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return jobs[0].weight;
    }

    if (opt[n] != -1) {
        return opt[n];
    }

    int index = findLastNonConflictingJob(n);
    int incl_job_n = jobs[n].weight + weighted_interval_scheduling_rec(index);
    int excl_job_n = weighted_interval_scheduling_rec(n - 1);
    opt[n] = std::max(incl_job_n, excl_job_n);
    return opt[n];
}

int WeightedIntervalScheduling::weighted_interval_scheduling_dp()
{
    int no_of_jobs = jobs.size();
    std::vector<int> opt(no_of_jobs);
    opt[0] = jobs[0].weight;
    for (int i = 1; i < no_of_jobs; i++) {
        int incl_job_i = jobs[i].weight;
        int index = findLastNonConflictingJob(i);
        if (index != NON_CONFLICTING_JOB_NOT_FOUND) {
            incl_job_i += opt[index];
        }
        opt[i] = std::max(incl_job_i, opt[i-1]);
    }
    return opt[no_of_jobs-1];
}

void WeightedIntervalScheduling::print_optimal_jobs()
{
    std::cout << "####### Optimal Jobs: #########" << std::endl;
    for (auto job : optimal[jobs_size()-1].optimal_jobs)
    {
        std::cout << job << std::endl;
    }
}

int WeightedIntervalScheduling::weighted_interval_scheduling_dp_with_jobs()
{
    int no_of_jobs = jobs.size();
    
    optimal[0].optimal_jobs.push_back(jobs[0]);
    optimal[0].optimal_weight = jobs[0].weight;
    for (int i = 1; i < no_of_jobs; i++) {
        int incl_job_i = jobs[i].weight;
        int index = findLastNonConflictingJob(i);
        if (index != NON_CONFLICTING_JOB_NOT_FOUND) {
            incl_job_i += optimal[index].optimal_weight;
        }
        if (incl_job_i > optimal[i-1].optimal_weight) {
            if (index != NON_CONFLICTING_JOB_NOT_FOUND) {
                optimal[i].optimal_jobs = optimal[index].optimal_jobs;
            }
            optimal[i].optimal_jobs.push_back(jobs[i]);
            optimal[i].optimal_weight = incl_job_i;
        } else {
            optimal[i].optimal_jobs = optimal[i-1].optimal_jobs;
            optimal[i].optimal_weight = optimal[i-1].optimal_weight;
        }
    }

    return optimal[no_of_jobs-1].optimal_weight;
}

