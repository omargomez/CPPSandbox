//
//  fib_iterator.cpp
//  08 STATEMENTS
//
//  Created by Omar Eduardo Gomez Padilla on 23/12/20.
//

#include <stdio.h>
#include "fibonacci.h"

bool FibonacciIterator::operator!=(int x) const {
  return x >= current;
}

FibonacciIterator& FibonacciIterator::operator++() {
  const auto tmp = current;
  current += last;
  last = tmp;
  return *this;
}

int FibonacciIterator::operator*() const {
  return current;
}

