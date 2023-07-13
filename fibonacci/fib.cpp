#include "fib.h"
#include <iostream>

int Fibonacci::fib_rec(int n) {
    if (n <= 1) {
        return n;
    }
    fibVector[n] = fib_rec(n - 1) + fib_rec(n - 2);
    return fibVector[n];
}

int Fibonacci::fib_memo(int n) {
    
    if (n <= 1) {
        return n;
    }

    if (fibVector[n] != -1) {
        return fibVector[n];
    }

    fibVector[n] = fib_memo(n - 1) + fib_memo(n - 2);
    return fibVector[n];
}

void Fibonacci::fib_dp(int n) {
    
    for (int i = 2; i <= n; i++) {
        fibVector[i] = fibVector[i-1] + fibVector[i-2];
    }
}