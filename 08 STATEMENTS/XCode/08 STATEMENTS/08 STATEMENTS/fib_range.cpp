//
//  fib_range.cpp
//  08 STATEMENTS
//
//  Created by Omar Eduardo Gomez Padilla on 23/12/20.
//

#include <stdio.h>
#include "fibonacci.h"

FibonacciRange::FibonacciRange(int max)
    : max{ max } {}

FibonacciIterator FibonacciRange::begin() const {
  return FibonacciIterator{};
}

int FibonacciRange::end() const {
  return max;
}

