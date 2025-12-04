#include "finalproject.h"

void greedy(std::vector<int> prices, std::vector<int> weights, int capacity){
    
    //compute array of ratios of price / weight for each item
    std::vector<float> rates;
    std::vector<int> temp_prices = prices;
    std::vector<int> temp_weights = weights;

    for (int i = 0; i < prices.size(); i++){
        float rate = prices[i] / weights[i];
        rates.push_back(rate);
    }

    // do floor division with capacity / item weight with max rate until no more divisions can be done

    // initialize final value accumulated to zero and the ret array which will contain all choices 
    // if items made by the greedy algorithm
    int value = 0;
    std::vector<int> ret;

    while (rates.size() > 0 ){

        // pick the item with the maximum ratio and get its index
        std::vector<float>::iterator max_element = std::max_element(rates.begin(), rates.end());
        int idx = std::distance(rates.begin(), max_element);
        
        // check if this item's weight exceed available capacity. if not, take the item
        if (temp_weights[idx] <= capacity){

            // adjust capacity and value accumulated
            capacity = capacity - temp_weights[idx];
            value = value + temp_prices[idx];

            // find this item's index in original vectors and save that we picked this item
            int target = temp_prices[idx];
            auto main_idx = std::find(prices.begin(), prices.end(), target);
            int push_value = std::distance(prices.begin(), main_idx);
            ret.push_back(push_value);
            
            //pop this item from the vectors since we won't use it anymore
            rates.erase(rates.begin() + idx);
            temp_prices.erase(temp_prices.begin() + idx);
            temp_weights.erase(temp_weights.begin() + idx);


        }
        else{

            // if item's weight is too much, just remove it and try again with another item
            rates.erase(rates.begin() + idx);
            temp_prices.erase(temp_prices.begin() + idx);
            temp_weights.erase(temp_weights.begin() + idx);
        }

        
    }
    std::cout << "Greedy algorithm:" << std::endl;
    std::cout << "Items chosen: " << std::endl;
    for (int i = 0; i < ret.size(); i++){
        if (i < ret.size() - 1){
            std::cout << ret[i] << ", ";}
        else{
            std::cout << ret[i] << std::endl;
        }
    }
     
    std::cout << "Remaining capacity: "<< capacity << std::endl; 
    std::cout << "Total value accumulated: "<< value << std::endl;
    
    return ;

}

std::vector<int> removeElementAndReturn(const std::vector<int>& originalVector, int indexToRemove) {
    std::vector<int> newVector = originalVector; // Create a copy

    if (indexToRemove >= 0 && indexToRemove < newVector.size()) {
        newVector.erase(newVector.begin() + indexToRemove); // Remove the element
    }
    return newVector;}

int knapsack(std::vector<int> prices, std::vector<int> weights, int capacity){

    // base case 1: if capacity went negative, our knapsack ripped and we want to discourage that to the algorithm
    if (capacity < 0){
        return -999999;
    }

    // base case 2: if capacity is full, we want to stop the algorithm from taking any more items
    if (capacity == 0){
        return 0;
    }

    // if we reach the end of our item list and still have capacity leftover, return 0
    if (prices.size() == 0 and capacity > 0){
        return 0;
    }

    // initialize max_so_far to 0
    int max_so_far = 0;

    std::vector<int> new_prices;
    std::vector<int> new_weights;

    // iterate through the items and decide whether we want our knapsack to stay as it is, or take the item
    for (int i = 0; i < prices.size(); i++){
        std::vector<int> new_prices = removeElementAndReturn(prices, i);
        std::vector<int> new_weights = removeElementAndReturn(weights, i);
        // if we leave the item, our value stays the same. if we take the item, our value increases and capacity decreases
        max_so_far = std::max(max_so_far, prices[i] + knapsack(new_prices, new_weights, capacity-weights[i]));
    }
    return max_so_far;
}

int knapsack_with_memo(vector<int> prices, vector<int> weights, int capacity){

    // initialize dimensions of  n x w matrix
    int n = prices.size();
    int w = capacity;
    
    // initialize matricies
    std::vector<std::vector<int>> matrix(n+1, std::vector<int>(w+1, 0));
    std::vector<std::vector<int>> matrix2(n+1, std::vector<int>(w+1, 0));

    // For loop iterators for n+1 columns and w+1 rows.
    // One row and one column for base cases in which there are no more items and there
    // is no more capacity.
    for (int i = n; i >= 0; i--) {
        for (int j = 0; j < w +1; j++) {

            // base case 1: capacity is zero
            if (j == 0){
                matrix[i][j] = 0;
                // we add the value "0" to matrix2 if we want to leave, and "1" if we want to keep
                matrix2[i][j] = 0;
                continue;
            }
            
            // base case 2: out of items to make "take or leave" decisions on
            if (i == n){
                matrix[i][j] = 0;
                matrix2[i][j] = 0;
                continue;
            }

            // if matrix cell has capacity, the cell "choses" the option of taking or leaving
            // the item based on which will provide maximum return. 

            // the matrix is filled from left to right, then bottom to top. it starts with 
            // capacity = 0 and item = n+1 (both base cases) and then decides max value achievable
            // starting from less capacity and works its way to item = 0 and capacity = total
            if (j >= weights[i]){
                matrix[i][j] = std::max(matrix[i+1][j], prices[i] + matrix[i+1][j-weights[i]]);
                if (matrix[i][j] != matrix[i+1][j]){
                    matrix2[i][j] = 1;
                }
                else{
                    matrix2[i][j] = 0;
                }
            }

            // if matrix cell has not enough capacity, it is forced to leave the item
            else{
                matrix[i][j] = matrix[i+1][j];
                matrix2[i][j] = 0;
            }
            
        }
    }

    // traverse the matrix to get decision history
    int c = capacity;
    int item = prices.size()-1;
    std::vector<int> ret;
    while (c > 0 and item >= 0){
        if (matrix2[item][c] == 1){
            ret.push_back(item);
            c -= weights[item];
            item -= 1;
        }
        else{
            item -= 1;
        }
    }
    std::cout << "Dynamic programming algorithm:" << std::endl;
    std::cout << "Items chosen: " << std::endl;
    for (int i = 0; i < ret.size(); i++){
        if (i < ret.size() - 1){
            std::cout << ret[i] << ", ";}
        else{
            std::cout << ret[i] << std::endl;
        }
    }
     
    std::cout << "Remaining capacity: "<< c << std::endl; 
    std::cout << "Total value accumulated: "<< matrix[0][w] << std::endl;
    
    // once table is populated, we have the max achievable value for the whole problem 
    // at the end.
    return matrix[0][w];

    }





