//
//  main.cpp
//  Crash Course Types Ex
//
//  Created by Omar Gomez on 5/11/20.
//  Copyright © 2020 padilla. All rights reserved.
//

#include <iostream>

enum class Operation {
    Add,
    Subtract,
    Multiply,
    Divide
};

struct Calculator {
    
    
    Calculator() {
        operation = Operation::Add;
    }
    
    Calculator(Operation anOperation) {
        operation = anOperation;
    }
    
    int calculate(int a, int b) {
        int result;
        switch (operation) {
            case Operation::Add:
                result = a + b;
                break;
            case Operation::Subtract:
                result = a - b;
                break;
            case Operation::Multiply:
                result = a * b;
                break;
            case Operation::Divide:
                result = a / b;
                break;
                
            default:
                break;
        }
        
        return result;
    }
    
private:
    
    Operation operation;
};


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Sub: %d \n", Operation::Subtract);
    
    Calculator div{ Operation::Divide }, mul{ Operation::Multiply }, def;
    
    printf("div: %d, mul: %d, def: %d \n", div.calculate(100, 10), mul.calculate(100, 10), def.calculate(100, 10));
    
    return 0;
}
