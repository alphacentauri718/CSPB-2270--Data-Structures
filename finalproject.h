
#ifndef FINAL_H__
#define FINAL_H__

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <tuple>
#include <chrono>

using namespace std;
using namespace std::chrono;

void greedy(std::vector<int> prices, std::vector<int> weights, int capacity);

//removeElementAndReturn is a helper function
std::vector<int> removeElementAndReturn(const std::vector<int>& originalVector, int indexToRemove);
int knapsack(std::vector<int> prices, std::vector<int> weights, int capacity);

int knapsack_with_memo(vector<int> prices, vector<int> weights, int capacity);

#endif 