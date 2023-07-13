#include <gtest/gtest.h>
#include "wis.h"
#include <assert.h>

class MyWeightedIntervalSchedulingTest : public ::testing::Test {
    protected:
    WeightedIntervalScheduling wis;
    virtual void SetUp() {
        //Job(start, finish, weight)
        wis.add_job(Job(0, 6, 60));
        wis.add_job(Job(1, 4, 30));
        wis.add_job(Job(3, 5, 10));
        wis.add_job(Job(5, 7, 30));
        wis.add_job(Job(5, 9, 50));
        wis.add_job(Job(7, 8, 10)); 
        wis.sort_jobs_by(wis.sort_by::END_TIME);  
    }
};

TEST_F(MyWeightedIntervalSchedulingTest, weighted_interval_scheduling_rec_basic) {
    EXPECT_EQ(wis.weighted_interval_scheduling_rec(wis.jobs_size()-1), 80);
}

TEST_F(MyWeightedIntervalSchedulingTest, weighted_interval_scheduling_dp_basic_test)
{
    EXPECT_EQ(wis.weighted_interval_scheduling_dp(), 80);
}

TEST_F(MyWeightedIntervalSchedulingTest, weighted_interval_scheduling_memo_basic)
{
    wis.opt.resize(wis.jobs_size(), -1);
    EXPECT_EQ(wis.weighted_interval_scheduling_memo(wis.jobs_size() - 1), 80);
}

TEST_F(MyWeightedIntervalSchedulingTest, weighted_interval_scheduling_dp_with_jobs_basic)
{
    wis.optimal.resize(wis.jobs_size());
    EXPECT_EQ(wis.weighted_interval_scheduling_dp_with_jobs(), 80);
    std::vector<Job> expected_optimal_jobs = {Job(1, 4, 30), Job(5, 9, 50)};
    std::vector<Job> actual_optimal_jobs = wis.optimal[wis.jobs_size()-1].optimal_jobs;
    for (size_t i = 0; i < expected_optimal_jobs.size(); i++) {
        EXPECT_EQ(expected_optimal_jobs[i].start, actual_optimal_jobs[i].start);
        EXPECT_EQ(expected_optimal_jobs[i].finish, actual_optimal_jobs[i].finish);
        EXPECT_EQ(expected_optimal_jobs[i].weight, actual_optimal_jobs[i].weight);
    }
}

TEST(WeightedIntervalSchedulingTest, weighted_interval_scheduling_rec_basic1) {
    WeightedIntervalScheduling wis;
    wis.add_job(Job(3, 10, 20));
    wis.add_job(Job(1, 2, 50));
    wis.add_job(Job(6, 19, 100));
    wis.add_job(Job(2, 100, 200));
    wis.sort_jobs_by(wis.sort_by::END_TIME);  
    EXPECT_EQ(wis.weighted_interval_scheduling_rec(wis.jobs_size()-1), 250);
}

TEST(WeightedIntervalSchedulingTest, weighted_interval_scheduling_rec_leetcode_basic1)
{
    WeightedIntervalScheduling wis;
    wis.add_job(Job(1, 3, 20));
    wis.add_job(Job(2, 5, 20));
    wis.add_job(Job(3, 10, 100));
    wis.add_job(Job(4, 6, 70));
    wis.add_job(Job(6, 9, 60));
    wis.sort_jobs_by(wis.sort_by::END_TIME);
    EXPECT_EQ(wis.weighted_interval_scheduling_rec(wis.jobs_size() - 1), 150);
}

TEST(WeightedIntervalSchedulingTest, weighted_interval_scheduling_memo_leetcode_basic1)
{
    WeightedIntervalScheduling wis;
    wis.add_job(Job(1, 3, 20));
    wis.add_job(Job(2, 5, 20));
    wis.add_job(Job(3, 10, 100));
    wis.add_job(Job(4, 6, 70));
    wis.add_job(Job(6, 9, 60));
    wis.sort_jobs_by(wis.sort_by::END_TIME);
    wis.opt.resize(wis.jobs_size(), -1);
    EXPECT_EQ(wis.weighted_interval_scheduling_memo(wis.jobs_size() - 1), 150);
}

TEST(WeightedIntervalSchedulingTest, weighted_interval_scheduling_dp_leetcode_basic1)
{
    WeightedIntervalScheduling wis;
    wis.add_job(Job(1, 3, 20));
    wis.add_job(Job(2, 5, 20));
    wis.add_job(Job(3, 10, 100));
    wis.add_job(Job(4, 6, 70));
    wis.add_job(Job(6, 9, 60));
    wis.sort_jobs_by(wis.sort_by::END_TIME);
    EXPECT_EQ(wis.weighted_interval_scheduling_dp(), 150);
}

TEST(WeightedIntervalSchedulingTest, weighted_interval_scheduling_dp_with_jobs_leetcode_basic1) {
    WeightedIntervalScheduling wis;
    wis.add_job(Job(1, 3, 20));
    wis.add_job(Job(2, 5, 20));
    wis.add_job(Job(3, 10, 100));
    wis.add_job(Job(4, 6, 70));
    wis.add_job(Job(6, 9, 60));
    wis.sort_jobs_by(wis.sort_by::END_TIME);
    wis.optimal.resize(wis.jobs_size());
    EXPECT_EQ(wis.weighted_interval_scheduling_dp_with_jobs(), 180);
    std::vector<Job> expected_optimal_jobs = {Job(1, 3, 20), Job(4, 6, 70), Job(6, 9, 60)};
    std::vector<Job> actual_optimal_jobs = wis.optimal[wis.jobs_size() - 1].optimal_jobs;
    for (size_t i = 0; i < expected_optimal_jobs.size(); i++)
    {
        EXPECT_EQ(expected_optimal_jobs[i].start, actual_optimal_jobs[i].start);
        EXPECT_EQ(expected_optimal_jobs[i].finish, actual_optimal_jobs[i].finish);
        EXPECT_EQ(expected_optimal_jobs[i].weight, actual_optimal_jobs[i].weight);
    }
}
int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}