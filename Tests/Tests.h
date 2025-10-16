#include <string>
#include <chrono>


void testDjikstra(int nodes, int density, int minCap, int maxCap, bool directed, std::chrono::milliseconds &time, std::chrono::milliseconds &time2, int numThreads);
void testDjikstraCorrectness(std::string filename);
void testScenarios();