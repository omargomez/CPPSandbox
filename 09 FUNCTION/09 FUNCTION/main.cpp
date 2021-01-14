//
//  main.cpp
//  09 FUNCTION
//
//  Created by Omar Eduardo Gomez Padilla on 11/01/21.
//

#include <iostream>
#include "lambdatest.hpp"

template <typename Fun, typename In, typename Out>
constexpr Out fold(Fun fun, In *in, size_t size, Out initial) {
    
    auto result = initial;
    
    for (int i = 0; i < size; i++) {
        result = fun(result, in[i]);
    }
    
    return result;
}

void exercise91() {
    int data[]{ 100, 200, 300, 400, 500 };
    float float_data[]{ 100, 200, 300, 400, 500 };
    size_t data_len = 5;
    auto sum = fold([](auto x, auto y) { return x + y; }, float_data, data_len,
  (float) 0);
    
    
    printf("Sum: %f\n", sum);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    exercise91();
}


