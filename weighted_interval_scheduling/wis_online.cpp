/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int NON_CONFLICTING_JOB_NOT_FOUND = -1;
class Job
{
public:
    int start;
    int finish;
    int weight;
    Job(int s, int f, int w) : start(s), finish(f), weight(w) {}
};

vector<Job> jobs;

int findLastNonConflictingJob(int n)
{
    // Process suffixes of jobs[0..n-1]
    for (int i = n - 1; i >= 0; i--)
    {
        if (jobs[i].finish <= jobs[n].start)
        {
            return i;
        }
    }
    return NON_CONFLICTING_JOB_NOT_FOUND;
}

/* Exercise:
jobs = {Job(1, 3, 20), Job(2, 5, 20), Job(3, 10, 100), Job(4, 6, 70), Job(6, 9, 60)};
*/
int main()
{
    jobs = {Job(1, 3, 20), Job(2, 5, 20), Job(3, 10, 100), Job(4, 6, 70), Job(6, 9, 60)};
    // jobs = {Job(3, 10, 20), Job(1, 2, 50), Job(6, 19, 100), Job(2, 100, 200)};
    std::sort(jobs.begin(), jobs.end(), [](Job a, Job b)
              { return a.finish < b.finish; });
    int no_of_jobs = jobs.size();
    std::vector<int> opt(no_of_jobs);
    opt[0] = jobs[0].weight;
    for (int i = 1; i < no_of_jobs; i++)
    {
        int incl_job_i = jobs[i].weight;
        int index = findLastNonConflictingJob(i);
        if (index != NON_CONFLICTING_JOB_NOT_FOUND)
        {
            incl_job_i += opt[index];
        }
        opt[i] = std::max(incl_job_i, opt[i - 1]);
    }
    return opt[no_of_jobs - 1];
}