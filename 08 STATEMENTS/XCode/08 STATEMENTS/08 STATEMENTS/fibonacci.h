//
//  fibonacci.h
//  08 STATEMENTS
//
//  Created by Omar Eduardo Gomez Padilla on 23/12/20.
//

#ifndef fibonacci_h
#define fibonacci_h

struct FibonacciIterator {
    bool operator!=(int x) const;

    FibonacciIterator& operator++();

    int operator*() const;

  private:
  int current{ 1 }, last{ 1 };
};

struct FibonacciRange {
    explicit FibonacciRange(int max);
    
    FibonacciIterator begin() const;

    int end() const;

  private:
    const int max;
};

#endif /* fibonacci_h */
