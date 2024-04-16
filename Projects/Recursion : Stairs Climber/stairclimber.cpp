/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Annanya Jain
 * Date        : 6th October 2023
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    // if there are 0 or negative num_stairs, then it returns a vector containimg empty vectors. 
    if(num_stairs <=0){
        return {{}};
    }
    // Created a new vector conatining vectors named ways
    vector< vector<int> > ways;
    
    // Since, we can maximum jump 3 stairs, we iterate through the loop until i < 4. 
    for (int i = 1; i < 4; i++)
    {
        if(num_stairs >= i){
            // result is a vector containing vectors which stores the ways to climb stairs at each step through recursion. 
            vector< vector<int> > result = get_ways(num_stairs - i);
            for (size_t j = 0; j < result.size(); j++)
            {
                // We keep storing these different combinations of ways to climb num_stairs iteratively in the vector form in the begininng of vector.  
                result[j].insert(result[j].begin(), i);
                // Finally, we add each of the vectors stored in result, in the "ways" vector in each iteration of the loop. 
                ways.push_back(result[j]);
            }
        }
    }
    // "ways" which stores different combinations of ways to climb num_stairs is then returned. 
    return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

    // In order to right align, I had to count the number of digits in the number of ways possible to climb num_stairs. So, I used while loop to do it. 
    int num = ways.size();
    int count = 0;
    while(num != 0)
    {
        num /= 10;
        count++;
    };

    //Iterating through the ways vector using a loop to display each combination of ways to climb num_stairs that we calculated in get_ways. 
    for (size_t i = 0; i < ways.size(); i++)
    {
        // setw(count) is then used to right align. 
        cout << setw(count) << i + 1 << ". [";
        for (size_t j = 0; j < ways[i].size(); j++){
            cout << ways[i][j];
            if (j < ways[i].size() - 1) {
                cout << ", ";
            }    
        }
        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {

    int num_stairs;

    // If less or more than 2 arguments are given, it prints a usage message. 
    if (argc != 2){
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }

    istringstream iss(argv[1]);

    // If num_stairs is an invalid imput, eg: a string, 0 or negative number, it prints an error message. 
    if ( !(iss >> num_stairs) ) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    if (num_stairs <= 0 ) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    vector< vector<int> > ways = get_ways(num_stairs);

    if(ways.size() == 1){
        cout << ways.size() << " way to climb " << num_stairs << " stair." << endl;
    }
    else{
        cout << ways.size() << " ways to climb " << num_stairs << " stairs." << endl;
    }

    display_ways(ways);
    return 0; 
}
