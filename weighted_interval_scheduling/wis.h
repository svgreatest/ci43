#ifndef WEIGHTED_INTERVAL_SCHEDULING_H
#define WEIGHTED_INTERVAL_SCHEDULING_H

#include<vector>
#include<iostream>

class Job
{
public:
    int start;
    int finish;
    int weight;
    Job(int s, int f, int w) : start(s), finish(f), weight(w) {}
    friend std::ostream& operator<<(std::ostream &os, const Job &job)
    {
        os << "(" << job.start << ", " << job.finish << ", " << job.weight << ")";
        return os;
    }
};

class WeightedIntervalScheduling
{
    std::vector<Job> jobs;
    const int NON_CONFLICTING_JOB_NOT_FOUND = -1;
    struct OptimalJobs
    {
        std::vector<Job> optimal_jobs;
        int optimal_weight;
    };
    int findLastNonConflictingJob(int n);
    public:
    std::vector<OptimalJobs> optimal;
    std::vector<int> opt;
    typedef enum SORT_BY
    {
        START_TIME,
        END_TIME,
        WEIGHT
    } sort_by;
    int weighted_interval_scheduling_rec(int n);
    int weighted_interval_scheduling_memo(int n);
    int weighted_interval_scheduling_dp();
    int weighted_interval_scheduling_dp_with_jobs();
    void print_jobs();
    void print_optimal_jobs();
    size_t jobs_size() { return jobs.size(); }
    std::vector<Job> get_jobs() { return jobs; }
    void add_job(Job job) { jobs.push_back(job); }
    void sort_jobs_by(sort_by sortby);
};

#endif