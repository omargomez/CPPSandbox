//
//  main.cpp
//  06 COMPILE-TIME POLYMORPHISM
//
//  Created by Omar Eduardo Gomez Padilla on 2/12/20.
//

#include <iostream>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

template <typename T>
T mean(const T* values, size_t length) {
  T result{};
  for(size_t i{}; i < length; i++) {
    result += values[i];
  }
  return result / length;
}

void mean_test() {
    const double nums_d[]{ 1.0, 2.0, 3.0, 4.0 };
    const auto result1 = mean<double>(nums_d, 4);
    printf("double: %f\n", result1);

    const float nums_f[]{ 1.0f, 2.0f, 3.0f, 4.0f };
    const auto result2 = mean<float>(nums_f, 4);
    printf("float: %f\n", result2);

    const size_t nums_c[]{ 1, 2, 3, 4 };
    const auto result3 = mean<size_t>(nums_c, 4);
    printf("size_t: %zd\n", result3);
}

template <typename T>
T mode(T* values, size_t len) {

    T sorted[len];
    
    memcpy(sorted, values, len*sizeof(*values));
    
    auto n = len;
    for(auto j=n-1; j > 0; j--)
        for(int k=0; k < j; k++)
            if (sorted[k+1] < sorted[k]) {
                auto temp = sorted[k];
                sorted[k] = sorted[k+1];
                sorted[k+1] = temp;
            }

    // Once sorted, lets run
    T curr_element = sorted[0];
    int curr_count = 1;
    auto old_element = curr_element;
    auto old_count = curr_count;
    
    for (int q = 1; q < len; q++) {
        if (sorted[q] == curr_element) {
            curr_count += 1;
        }
        else {

            if (old_count != 0) { // can be compared
                if (curr_count > old_count) {
                    old_count = curr_count;
                    old_element = curr_element;
                }
            }
            
            curr_element = sorted[q];
            curr_count = 1;
        }
    }
    // for tha last element ...
    if (curr_count > old_count) {
        old_count = curr_count;
        old_element = curr_element;
    }

    return old_element;
}

void mode_test() {
    {
        int numbers[] = {1,1,2,2,3,3,3,4,4};
        int m = mode(numbers, sizeof(numbers)/sizeof(numbers[0]));
        printf("Mode = %d\n", m);
    }
    {
        long numbers[] = {1,1,2,2,3,3,3,4,4};
        long m = mode(numbers, sizeof(numbers)/sizeof(numbers[0]));
        printf("Mode = %ld\n", m);
    }
    {
        float numbers[] = {1.0,1.0,2.0,2.0,3.0,3.0,3.0,4.0,4.0,4.0,4.0,4.0,4.0};
        float m = mode(numbers, sizeof(numbers)/sizeof(numbers[0]));
        printf("Mode = %f\n", m);
    }
}

template <typename T, size_t Length>
T mean(T (&values)[Length]) {
  T result{};
  for(size_t i{}; i < Length; i++) {
    result += values[i];
  }
  return result / Length;
}

template <size_t Length>
double meann(double (&values)[Length]) {
  double result{};
  for(size_t i{}; i < Length; i++) {
    result += values[i];
  }
  return result / Length;
}

void main_mean() {
    {
        int arr[]{ 1, 1, 2, 3, 5 };
        printf("mean %d\n", mean(arr));
    }
    {
        long arr[]{ 1, 1, 2, 3, 5 };
        printf("mean %ld\n", mean(arr));
    }
    {
        float arr[]{ 1, 1, 2, 3, 5 };
        printf("mean %f\n", mean(arr));
    }
    {
        double arr[]{ 1, 1, 2, 3, 5 };
        printf("mean %lf\n", mean(arr));
        printf("mean %lf\n", meann(arr));
    }
}

// Bank project

struct Logger {
  virtual ~Logger() = default;
  virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger {
    ConsoleLogger(const char *aPrefix) :
        prefix{ aPrefix } {

    }
  void log_transfer(long from, long to, double amount) override {
    printf("[%s] %ld -> %ld: %f\n", prefix, from, to, amount);
  }
private:
    const char *prefix;
};

struct FileLogger : Logger {
  void log_transfer(long from, long to, double amount) override {
    printf("[file] %ld,%ld,%f\n", from, to, amount);
  }
};

struct Account {
    
    virtual double balance() = 0;
    
    virtual void deposit(double amount) = 0;
    
    virtual void withdraw(double amount) = 0;
    
    long number;
};

struct CheckingAccount: Account {
    
    CheckingAccount(long aNumber)
    {
        number = aNumber;
    }
    
    double balance() override {
        return 0;
    }
    
    void deposit(double amount) override {
    }
    
    void withdraw(double amount) override  {
    }
    
};

struct SavingsAccount: Account {
    
    SavingsAccount(long aNumber)
    {
        number = aNumber;
    }
    
    double balance() override {
        return 0;
    }
    
    void deposit(double amount) override {
    }
    
    void withdraw(double amount) override  {
    }
    
};

template <typename T>
struct Bank {
  Bank(Logger& logger)
    : logger{ logger } {}
  void make_transfer(T &from, T &to, double amount) {
      from.withdraw(amount);
      to.deposit(amount);
      logger.log_transfer(from.number, to.number, amount);
  }

  private:
    Logger& logger;
};

void main_bank() {
    ConsoleLogger logger{ "##>" };
    
    CheckingAccount accountA{1010};
    CheckingAccount accountB{2020};
    SavingsAccount accountC{3030};
    SavingsAccount accountD{4040};
    Bank<Account> bank{ logger };
    
    bank.make_transfer(accountA, accountB, 49.95);
    bank.make_transfer(accountC, accountD, 49.95);
    bank.make_transfer(accountA, accountD, 49.95);
//    bank.make_transfer(2000, 4000, 20.00);
}


int main(int argc, const char * argv[]) {
    // insert code here...
//    mode_test();
//    main_mean();
    main_bank();
    return 0;
}
