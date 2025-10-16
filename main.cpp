#include <iostream>
#include "Tests/Tests.h"

int main(int argc, char* argv[]) {
    bool testCorrectness = 0;

    if(testCorrectness){
        testDjikstraCorrectness(argv[1]);
    } else {
        testScenarios();
    }
    
    
    return 0;
}