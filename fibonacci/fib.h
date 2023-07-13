#ifndef FIB_H
#define FIB_H

#include <vector>

class Fibonacci {
    public:
    std::vector<int> fibVector;
    int fib_rec(int n);
    int fib_memo(int n);
    void fib_dp(int n);
};

#endif