/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Annanya Jain
 * Version     : 1.0
 * Date        : 29th October 2023
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time using two nested loops.
 */
long count_inversions_slow(int array[], int length) {
    long cnt = 0;  // Initialised the counter to be equal to 0
    for (int i = 0; i < length - 1; i++) // The outer loop starts from the first element and runs till the second last element
    {
        for (int j = i + 1; j < length; j++) // The inner loop starts from 2nd element and runs till the last element
        {
            if(array[i] > array[j]){  // Comparing the previous element with the next element 
                cnt++;   
            // if the previous element is greater than the next element, it means there is an inversion and hence the counter is incremented
            }
        }
    }
    return cnt;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int* scratch = new int[length];   // Creates an array called scratch of array's length which is stored in a heap. Thus, used new keyword.
    for (int i = 0; i < length; i++)  // By Looping, I initisalised all elements of scratch to be equal to the elements of an array
    {
        scratch[i] = array[i];
    }
    
    long cnt = mergesort(array, scratch, 0, length - 1); // Calls the mergesort function which returns the count of the total inversions

    delete[] scratch;                                    // Cleared up the memory by deleting scratch
    return cnt;                                          // Returns the final count of the total inversions in an array
}

// The merge2 function is used to perform the merge operation of the array
long merge2(int array[], int scratch[], int low, int mid, int high) {
    long cnt = 0;                           // Initialised cnt (count of the inversions) to be 0
    int i1 = low;                           // Initialised i1 as the starting index of the left subarray 
    int i2 = mid +1;                        // Initialised i2 = mid + 1 i.e the start index of the right subarray
    int i = low;                            
    while(i1 <= mid && i2 <= high){         // Loop until i1 reaches mid and i2 reaches the high
        if(array[i1]<=array[i2]){           // If element at index i1 <= element at index i2, then: 
            scratch[i++] = array[i1++];     // The element at index i1 of the left subarray is copied to the scratch at index i. 
        }                                   // The index i and i1 is then increased by 1. In this case, no inversion is there. 

        else{                               // Else the element at index i2 of the righ subarray is copied to the scratch at index i
            scratch[i++] = array[i2++];     // The index i and i2 is increased by 1. Here, inversion occurs and hence we increase the cnt. 
            cnt += mid - i1 + 1;            // cnt is then calculated as cnt = cnt + mid - i1 + 1
        }
    }

    // If either the i1 or i2 exceeds their bounds, the remaining elements of the other subarray should be copied at the end of the scratch. 

    while(i1 <= mid)               
    {                          
        scratch[i++] = array[i1++]; 
    }

    while(i2 <= high)               
    {
        scratch[i++] = array[i2++]; 
    }
    
    // The elements of the merged array i.e in scratch is copied in the "array". 
    for (int i = low; i <= high; i++) 
    {
        array[i] = scratch[i];
    }
    return cnt;                       // It returns the count of the inversions in the merging process
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // Mergesort function is implemented using the recursion and the total count of inversions are returned
    if (low < high){  
        int mid = low + (high - low)/2;   
        // The inversions calculated at each merge step are added in the cnt. 
        return mergesort(array, scratch, low, mid) + mergesort(array, scratch, mid + 1, high) + merge2(array, scratch, low, mid, high);
    }
    else{
        return 0; // Base case i.e has no inversions
    }
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    // If the number of arguments is more than 2, then an error is returned 
    if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    }

    // if the number of arguements is 2, then the first optional arguement is given by the user which can only be given as "slow". 
    if (argc == 2) {
        string option = argv[1]; 
        if(option != "slow"){    
            cerr << "Error: Unrecognized option '" << option << "'."<< endl;
            return 1;
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output

    size_t num_values = values.size(); 
    // If no integers are given
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    // if only 1 integer is given, then there are no inversions. 
    if (num_values == 1){
        if(argc == 2){
            cout<< "Number of inversions (" << argv[1] << "): 0" << endl;
            return 0;
        }
        if(argc == 1){
            cout<< "Number of inversions (fast): 0" << endl;
            return 0;
        }
    }

    // If the number of arguments is 2 and the first argument is slow, then the count_inversions_slow function is executed. 
    if(argc == 2){
        string option = argv[1];
        if(option == "slow"){
            cout<< "Number of inversions (slow): " << count_inversions_slow(&values[0], num_values) << endl;
            return 0;
        }
    }
    else{ 
        cout<< "Number of inversions (fast): " << count_inversions_fast(&values[0], num_values) << endl;
    }
    return 0;
}