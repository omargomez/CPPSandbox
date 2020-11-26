//
//  main.cpp
//  04 THE OBJECT LIFE CYCLE
//
//  Created by Omar Gomez on 18/11/20.
//  Copyright © 2020 padilla. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <sys/time.h>
#include <unistd.h>

struct SimpleString {
  SimpleString(size_t max_size)
      : max_size{ max_size }
      , length{} {
    if(max_size == 0) {
      throw std::runtime_error{ "Max size must be at least 1." };
    }
    buffer = new char[max_size];
    buffer[0] = 0;
      printf("contructor\n");
  }
  ~SimpleString() {
    printf("destructor %s\n", buffer);
    delete[] buffer;
//      printf("destructor %zd\n", max_size);
  }
  SimpleString(const SimpleString& other)
      : max_size{ other.max_size }
      , buffer{ new char[other.max_size] }
      , length{ other.length } {
    std::strncpy(buffer, other.buffer, max_size);
      printf("lvalue contructor\n");
  }
  SimpleString(SimpleString&& other) noexcept
      : max_size(other.max_size)
      , buffer(other.buffer)
      , length(other.length) {
    other.length = 0;
    other.buffer = nullptr;
    other.max_size = 0;
      printf("rvalue contructor\n");
  }
  SimpleString& operator=(const SimpleString& other) {
    if(this == &other)
      return *this;
    const auto new_buffer = new char[other.max_size];
    delete[] buffer;
    buffer = new_buffer;
    length = other.length;
    max_size = other.max_size;
    std::strncpy(buffer, other.buffer, max_size);
      printf("lvalue copy\n");
    return *this;
  }
  SimpleString& operator=(SimpleString&& other) noexcept {
    if(this == &other)
      return *this;
    delete[] buffer;
    buffer = other.buffer;
    length = other.length;
    max_size = other.max_size;
    other.buffer = nullptr;
    other.length = 0;
    other.max_size = 0;
      printf("rvalue copy\n");
    return *this;
  }
  void print(const char* tag) const {
    printf("%s: %s\n", tag, buffer);
  }
  bool append_line(const char* x) {
    const auto x_len = strlen(x);
    if(x_len + length + 2 > max_size)
      return false;
    std::strncpy(buffer + length, x, max_size - length);
    length += x_len;
    buffer[length++] = '\n';
    buffer[length] = 0;
    return true;
  }

  private:
  size_t max_size;
  char* buffer;
  size_t length;
};

int timeval_subtract(struct timeval *result, struct timeval *x, struct timeval *y)
{
    // preserve *y
    struct timeval yy = *y;
    y = &yy;
    
    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_usec < y->tv_usec) {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000) {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }
    
    /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;
    
    /* Return 1 if result is negative. */
    return x->tv_sec < y->tv_sec;
}

struct TimerClass {
  

    TimerClass(const char *name) {
        gettimeofday(&timestamp, 0);
        strncpy(this->name, name, sizeof(this->name)-1);
    }
    
    TimerClass(const TimerClass& other)
    : timestamp(other.timestamp) {
        memcpy(name, &other.name, sizeof(name));
    }
    
    TimerClass(TimerClass&& other)
    : timestamp(other.timestamp) {
        memcpy(name, &other.name, sizeof(name));
        other.timestamp.tv_sec = 0;
        other.timestamp.tv_usec = 0;
        memset(&other.name, 0, sizeof(this->name));
    }
    
    TimerClass& operator=(const TimerClass& other) {
        if(this == &other)
            return *this;
        
        timestamp = other.timestamp;
        memcpy(this->name, &other.name, sizeof(this->name));
        return *this;
    }
    
    TimerClass & operator=(TimerClass&& other) {
        if (this == &other) {
            return *this;
        }
        
        this->timestamp = other.timestamp;
        other.timestamp.tv_sec = 0;
        other.timestamp.tv_usec = 0;
        memset(&other.name, 0, sizeof(this->name));
        
        return *this;
    }
    
    ~TimerClass() {
        if (timestamp.tv_usec == 0 && timestamp.tv_sec == 0)
            return;
        
        timeval curr, diff;
        gettimeofday(&curr, 0);
        
        timeval_subtract(&diff, &curr, &timestamp);
        
        double asSecs = (double) diff.tv_sec + ( (double) diff.tv_usec / 1000000.0 );

        printf("Delay from %s: %lf\n", name, asSecs );
    }
    
    timeval timestamp;
    char name[256];

};


void timer_class_main() {
    
    TimerClass a("a");
    TimerClass A("A");
    
    {
        TimerClass b(a);
        printf("debug: %s\n", b.name);
        sleep(1);
    }
    
    {
        TimerClass B(std::move(A));
        printf("debug: %s\n", B.name);
        sleep(1);
    }

    sleep(1);
    
}

int main(int argc, const char * argv[]) {
    // insert code here...

    timer_class_main();
    
    return 0;
}

void simple_main() {
    SimpleString a{ 10 };
    a.append_line("a");
    a.print("a ");
    
    {
        SimpleString b{ a };
        b.append_line("+ b");
        b.print("b ");
    }
    
    {
        //        auto aa = std::move(a);
        SimpleString c{ SimpleString(a) };
        c.append_line("+ c");
        c.print("c ");
    }
    
    {
        SimpleString(SimpleString(a)).print("tmp: ");
    }
    
    printf("-----\n");
    
}
