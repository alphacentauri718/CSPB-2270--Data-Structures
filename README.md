# Project Title
Dynamic programming vs the greedy algorithm
## Introduction
If we have to choose an optimal subset of items given conditions such as capacity and value, how do we know which items to take? 
What algorithms do we use? 
Are there speed/ time complexity concerns? Is there a way we address them and still get the best solution every time?
I will answer all of these questions in this project. 
## Features
- Greedy algorithm implementation
- Dynamic programming function with exponential time complexity
- Memoization table that gets same solution as dynamic programming with far less time complexity
## How the Data Structure Works
Let's say you are a thief trying to steal a bunch of items. You have a knapsack with a weight capacity. If you go over the weight capacity, your knapsack rips and you get caught. 
How can you steal the maximum value of goods given all of the goods also have a weight? Each time you take a weight, you gain the resale value of the item but you also have to incur
the weight in your knapsack. This problem shows up a lot in the real world-- investors trying to pick stocks with a given budget, or ships trying to load containers full of goods on decks.
The dynamic programming function "knapsack" works by recursively checking every possible combination of taking or leaving items from a set to arrive at an optimal solution. 
Unlike a greedy algorithm, which computes a ratio for each item and ranks them by these ratios and takes the best ratios, the knapsack algorithm checks every possible alternative. There
are 2 choices for each item (take or leave) and the knapsack algorithm checks every possible rabbit hole recursively (2^(number of items) possible scenarios) and picks out the one with
the maximum return. 

The base cases for this algorithm are if we are over capacity, the return value is -999999 (basically a big negative number) so that option never gets picked by the max function and the
recursion stops. Another base case is if the remaining capacity is equal to zero, we know we have to stop right there so it returns zero and the value accumulated up until that point gets
evaluated by the max function. The last base case is if we have evaluated every item in the list but we still have leftover capacity, the function should stop recursing and it behaves 
identically to the 2nd base case I mentioned (returns 0). As long as these three base cases are not true, the algorithm starts with a max_so_far value (this is the accumulated loot) 
that starts at zero. At every recursion, we iterate through the list of items and decide whether we should take it or not. The max value has 2 alternatives, the current "max_so_far" value
which signifies leaving the item (we keep what we have already and go on to the next item) or taking the item we are deciding on, in which case our "max_so_far" value gets adjusted to
reflect the gained value and so does the available capacity. The recursion goes through every possible alternative and the function returns the "max_so_far" variable at the end, so that
at the end we are comparing 2 "max_so_far" values as we go up the call stack. This function doesn't show us which items to pick, only the maximum attainable value.

I purposefully chose items with prices and weight capacities set so that the greedy algorithm is fooled and the knapsack algorithm delivers a better answer. These values are editable in
the main method where they are initialized, so you can create alternative scenarios and pit the algorithms against each other.

I lastly implemented one more algorithm, the "knapsack_with_memo". One of the shortcomings of the "knapsack" algorithm is that it has exponential time complexity. Oftemtimes (especially 
in a problem with a lot of items) it has to do the same recursive check again and again. For instance, let's say we have 4 items. It computes one scenario if it takes the item, one
scenario if it leaves the item. The remaining 3 items have an optimal solution given a certain available weight capacity and for the first item, it will have to recursively find the answer
to the same 3 items 2 times. This gets exponentially worse with more items and you can see that if you had 60 items, the algorithm would take a long time. 

The "knapsack_with_memo" algorithm has a great solution to this issue. It creates an (nxm) matrix which is filled in starting from the fringe base cases (capacity = 0 and item list is ended)
and fills the matrix slowly increasing the available capacity and saving the maximum achievable value at each capacity given a number of available items. It uses values it has already 
computed in evaluating decisions and works its way up to the point where all items are available and capacity is at its maximum. At that cell, we have our maximum achievable value/loot and
it takes far less time complexity (Theta(N) instead of Theta(2^(num_items))). While we are filling this matrix, we can also fill in another matrix which keeps track of whether or not
we kept the item in question as we go up the matrix. This matrix (called "matrix2") is storing the best possible decision given available weight capacity. We also fill this matrix up all the 
way up to the matrix2[0][max_capacity] cell and to output the decision chain we need to make for the most value, we start at matrix2[0][max_capacity] and traverse the matrix by taking or 
leaving the items as it prescribes. 

### Time and Space Complexity
| Operation     | Average Case | Worst Case |
|---------------|------------------|------------|
Greedy alg.     | Theta(n)         | O(n)
Knapsack        | Theta(2^(n))     | O(2^(n))
Knapsack w memo | Theta(n)         | O(n)
## File Structure
Explain the folder and file organization.
```
/.vscode
/build
CMakeLists.txt
finalproject.h
finalproject.cpp
main.cpp 
```
## Installation / Setup
Step-by-step instructions to set up the project locally.
Dependency: You have to have the -- GNU 15.2.0 CXX compiler. Download at: "https://www.msys2.org/". I ran on Windows.
```powershell
git clone git@github.com:alphacentauri718/CSPB-2270--Data-Structures.git
cd CSPB-2270--Data-Structures
$env:Path = "C:\msys64\ucrt64\bin;C:\msys64\usr\bin;$env:Path"
mkdir build
cd build
cmake .. -G "Unix Makefiles"
cmake --build .
.\finalproject.exe
```
## Usage
You can edit the main.cpp file and edit the prices and weights arrays. Each item's price and weight are the price[index] and weights[index]. 
## Application Demo
The main.cpp file can run the 3 algorithms (Greedy, Knapsack, Knapsack with Memoization) and clock how fast they run, so you can compare solutions and speed. The default prices and weights
are a table that trick the greedy algorithm into accepting an inferior solution. The functions output everything to console. Try them with different inputs but caveat-- The price and weights
vector lengths must be equal and you can't use repeat values (2 prices are the same or 2 weights are the same) or you will get incorrect results.

<img width="852" height="329" alt="image" src="https://github.com/user-attachments/assets/d6fdb11b-fa91-4788-8c98-c9199b696b5a" />

## Testing
Just change the prices and weights vectors in the main.cpp file and build and run. Everything is outputted to console.
## References
I'd like to credit my algorithms class here at UCB where I learned about all this and my professor, Dr. Reckwerdt.
### Future Improvements
This problem comes in many flavors, and I could have algorithms suited for problems of all kinds. Sometimes there are infinite items to pick, sometimes some solutions are forbidden.
### License
This project is licensed under the terms of the MIT license.
