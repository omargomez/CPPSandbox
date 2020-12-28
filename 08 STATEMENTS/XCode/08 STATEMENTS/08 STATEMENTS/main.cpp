//
//  main.cpp
//  08 STATEMENTS
//
//  Created by Omar Eduardo Gomez Padilla on 23/12/20.
//

#include <iostream>
#include "fibonacci.h"

void fib_main() {
    for(const auto i : FibonacciRange{ 14 }) {
      printf("%d ", i);
    }
}

int *prime_arr(int up_to) {
    
    auto max = up_to;
    auto *arr{ new bool[max+1]() };
    
    int root = (int) sqrt((float) up_to);
    for (auto i = 2; i <= root; i++ ) {
        if (!arr[i])
            for (auto j = i*i; j <= max; j += i) {
                arr[j] = true;
            }
    }
    
    int count = 0;
    for (int i = 2; i <= max; i++) {
        if (!arr[i])
            count++;
    }
    
    int *result{ new int[count+1]() };
    
    for (int i = 2, j = 0; i <= max; i++) {
        if (!arr[i]) {
            result[j++] = i;
        }
    }
    
    delete[] arr;
    return result;
}

struct PrimeIterator {
    
    explicit PrimeIterator(int *primes): values { primes }, idx{0} {}
    
    bool operator != (int x) {
        return x >= values[idx] && values[idx] != 0;
    }
    
    PrimeIterator &operator++() {
        idx++;
        return *this;
    }
    
    int operator*() const {
        return values[idx];
    }
    
private:
    const int *values;
    int idx;
};

struct PrimeRange {
    explicit PrimeRange(int max): max{max}, primes{ prime_arr(max) } {}
    
    PrimeIterator begin() const {
        return PrimeIterator{ primes };
    }
    
    int end() const {
        return max;
    }
    
    virtual ~PrimeRange() {
        delete[] primes;
    }
    
private:
    const int max;
    int *primes;
};

void prime_main(void) {
    int max = 20;

    for (const auto i: PrimeRange{ max }) {
        printf("%d ", i);
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    prime_main();
    return 0;
}
