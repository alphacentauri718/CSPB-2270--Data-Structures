#include "finalproject.h"

int main() {

    // Initialization -- EDIT here for experimentation
    int capacity = 200;
    std::vector<int> weights = {10, 20, 30, 40, 50, 60, 70};
    std::vector<int> prices = {60, 100, 120, 140, 160, 180, 200 };

    std::cout<< "Number of items: " << weights.size() << std::endl;
    std::cout<< "Weight limit: " << capacity << std::endl;
    std::cout << std::endl;
    // Greedy algorithm
    auto start = high_resolution_clock::now();
    greedy(prices, weights, capacity); 
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Greedy algorithm Time: " << duration.count() << " ms\n";
    std::cout << std::endl;

    // Dynamic programming
    auto start2 = high_resolution_clock::now();
    int true_max = knapsack(prices, weights, capacity);
    std::cout << "Dynamic programming solution (no memoization): " << true_max << std::endl;
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end2 - start2);
    cout << "Dynamic Programming (no memo) Time: " << duration2.count() << " ms\n";
    std::cout << std::endl; 

    // Knapsack with memo table and item index selection
    auto start3 = high_resolution_clock::now();
    int max2 = knapsack_with_memo(prices, weights, capacity);
    auto end3 = high_resolution_clock::now();
    auto duration3 = duration_cast<milliseconds>(end3 - start3);
    cout << "Dynamic programming (with memo) Time: " << duration3.count() << " ms\n";
    std::cout << std::endl;
    

    return 0;
}