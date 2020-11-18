//  main.cpp
//  03 REFERENCE TYPES
//
//  Created by Omar Gomez on 9/11/20.
//  Copyright © 2020 padilla. All rights reserved.
//

//
#include <cstdio>


static int main32();
char read_from(const char *buf, size_t size, int pos);
void write_to(char *buf, size_t size, int pos, char val);
#define arr_size(arr) (sizeof(arr)/sizeof(arr[0]))

static int main33();
static int main34();
static int main35();

int main32() {
    char lower[] = "abc?e";
    char upper[] = "ABC?E";
    char* upper_ptr = upper; // Equivalent: &upper[0]
    
    write_to(lower, arr_size(lower), 3, 'd');
    write_to(upper_ptr, arr_size(upper), 3, 'D');
    
    char letter_d = read_from(lower, arr_size(lower), 3);
    char letter_D = read_from(upper_ptr, arr_size(upper), 3);
    
    printf("lower: %s\nupper: %s", lower, upper);
    
    write_to(lower, arr_size(lower), 7, 'g');

    return 0;
}

char read_from(const char *buf, size_t size, int pos) {
    if (pos >= size) {
        return 0;
    }
    
    return buf[pos];
}

void write_to(char *buf, size_t size, int pos, char val) {
    if (pos >= size) {
        return;
    }
    
    buf[pos] = val;
}

struct Element {
    Element* next{};
    Element* prev{};
    void insert_after(Element* new_element) {
        new_element->next = next;
        if (next) {
            next->prev = new_element;
        }
        next = new_element;
        
        new_element->prev = this;
    }
    void insert_before(Element* new_element) {
        new_element->next = this;
        if (prev) {
            prev->next = new_element;
        }
        new_element->prev = prev;
        prev = new_element;
    }
    
    char prefix[2];
    short operating_number;
};

int main33() {
    Element trooper1, trooper2, trooper3;
    trooper1.prefix[0] = 'T';
    trooper1.prefix[1] = 'K';
    trooper1.operating_number = 2187;
    trooper1.insert_after(&trooper2);
    trooper2.prefix[0] = 'F';
    trooper2.prefix[1] = 'N';
    trooper2.operating_number = 421;
    trooper2.insert_after(&trooper3);
    trooper3.prefix[0] = 'L';
    trooper3.prefix[1] = 'S';
    trooper3.operating_number = 005;

    for(Element* cursor = &trooper1; cursor; cursor = cursor->next) {
        printf("Storm Trooper %c%c-%d\n", cursor->prefix[0], cursor->prefix[1], cursor->operating_number);
    }
    for(Element* cursor = &trooper3; cursor; cursor = cursor->prev) {
        printf("<< Storm Trooper %c%c-%d\n", cursor->prefix[0], cursor->prefix[1], cursor->operating_number);
    }
    return 0;
}

int main34() {
    auto original = 100;
    auto& original_ref = original;
    printf("Original:  %d\n", original);
    printf("Reference: %d\n", original_ref);
    
    auto new_value = 200;
    original_ref = new_value;
    printf("Original:  %d\n", original);
    printf("New Value: %d\n", new_value);
    printf("Reference: %d\n", original_ref);
    
    return 0;
}

int main35() {
    
    { // 2.1
        const unsigned short a = 0b10101010;
        printf("%hu\n", a);
        const int b = 0123;
        printf("%d\n", b);
        const unsigned long long d = 0xFFFFFFFFFFFFFFFF;
        printf("%llu\n", d);

    }
    
    { // 2.7
        const auto t = true;
        const auto f = false;
        printf("!true: %d\n", !t);
        printf("true  &&  false: %d\n", t && f);
        printf("true  && !false: %d\n", t && !f);
        printf("true  ||  false: %d\n", t || f);
        printf("false ||  false: %d\n", f || f);
    }
    
    { // 2.10
        unsigned long maximum = 0;
        const unsigned long values[] = { 10, 50, 20, 40, 0 };
        for(size_t i = 0; i < 5; i++) {
            if(values[i] > maximum)
                maximum = values[i];
        }
        printf("The maximum value is %lu.", maximum);
    }
    
    {
        struct Book {
            char name[256];
            int year;
            int pages;
            bool hardcover;
        };
        
        Book neuromancer;
        neuromancer.pages = 271;
        printf("Neuromancer has %d pages.", neuromancer.pages);
    }
    
    return 0;
}

int main() {
    return main35();
}

