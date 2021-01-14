//
//  lambdatest.cpp
//  09 FUNCTION
//
//  Created by Omar Eduardo Gomez Padilla on 11/01/21.
//

#include "lambdatest.hpp"
#include <cstdio>
#include <cstdint>
#include <cstring>

template <typename Fn>
void transform(Fn fn, const int* in, int* out, size_t length) {
  for(size_t i{}; i<length; i++) {
    out[i] = fn(in[i]);
  }
}

void example915() {
    const size_t len{ 3 };
    int base[]{ 1, 2, 3 }, a[len], b[len], c[len];
    transform([](int x) { return 1; }, base, a, len);
    transform([](int x) { return x; }, base, b, len);
    transform([](int x) { return 10*x+5; }, base, c, len);
    transform([](int x) { return x*x; }, base, c, len);
    for (size_t i{}; i < len; i++) {
      printf("Element %zu: %d %d %d\n", i, a[i], b[i], c[i]);
    }
}

void myexample() {
    
    auto lambda = [](){ printf("My lambda\n"); };
    auto lambda3 = [](const char *str){ return strlen(str); };
    auto lambda2 = [](const char *str){ printf("Hello: %s, %d\n", str, 0); };

    lambda2("Omar");
    
}

void lambdatest_main() {
    myexample();
}

