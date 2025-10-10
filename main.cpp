#include <iostream>
#include "Tests/Tests.cpp"

int main() {
    bool testCorrectness = 0;
    
    if(testCorrectness){
        testDjikstraCorrectness();
    } else {
        testDjikstra();
    }
    
    
    return 0;
}