/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Annanya Jain
 * Date        : 30 September, 2023
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/

#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

    // Using for each loop, I traverse through each character in the string s to check whether all characters in string are lowercase letters or not.
    for (char i : s)
    {
        //If each charachter in the string is not lowercase letter, it returns false otherwise true. 
        if(!islower(i)){
            return false; 
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only.  Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.

    // An unsigned vector and setter is assgned to 0 initially. 
    unsigned int vector = 0; 
    unsigned int setter = 0;

    // Using for each loop, I traverse through each character in the string s 
    for (char i : s)
    {
        // Starting from the first character in the given string, the distance between character 'a' and the character at i is calculated
        // 1 is then left shifted using the bitwise left operator "<<" to represent the bit representation of that character which is finally stored in setter
        setter = 1 << (i - 'a'); 
        // Bitwise AND operation (&) is carried out between vector and setter to check if that character was already present in the string. 
        // We perform & operation because :
        // if (vector & setter) != 0 ---> it would mean there are duplicates of the same character in the string
        // This is because, if bit 1 represents the count of the character in the string in vector, and is present in the setter too, it would not result in 0. 
        if((vector & setter) == 0){
            vector = vector | setter;
            // If 0, it means that character is unique in the string, and hence we use Bitwise OR (|), and store the bit in the vector. 
        }
        else{
            // if (vector & setter) != 0 ---> it would mean there are duplicates of the same character in the string and hence the loop stops. 
            return false;
        }
    }

    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    // argc counts the number of arguments given as input
    // if argc is less than or more than 2, it prints out an error. 
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " <string>" << endl; 
        return 1;
    }

    // if the string i.e given as an input is not a string or the characters in string is not in lowercase, then it printss out the error message. 
    if(is_all_lowercase(argv[1]) == false){
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    // The method called all_unique_letters iss called, if the method returns true, it means that all characters within the string is unique. 
    // If false, it means there are duplicate letters. 
    if(all_unique_letters(argv[1])){
        cout << "All letters are unique." << endl;
    }
    else{
        cout << "Duplicate letters found." << endl;
    }

    return 0;
}
