/*******************************************************************************
 * Name        : Fast_mult.cpp
 * Author      : Annanya Jain
 * Version     : 1.0
 * Date        : 18th November 2023
 * Description : Implementing Karatsuba Algorithm for fast multiplication
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// padding Function is used to add zeros at the beginning of the smaller string in order to make both strings of same length. 
string padding(const string str, int maxlen){
    return string(maxlen - str.length(), '0') + str;
}

// add Function is used to add strings a and b
string add(const string& a, const string& b) {
    int n = max(a.length(), b.length());        // finds max length of strings a and b
    string new_a = padding(a, n);               // Using padding fucntion to make them of the same length
    string new_b = padding(b, n);               // Using padding fucntion to make them of the same length

    string add_output = "";                     // Initialised the add_output string where I will add my output of the additon.
    int carry = 0;                              // Initialised carry to be 0. 

    // For loop to perform addition digit by digit starting from the end of the string. 
    for (int i = n - 1; i >= 0; i--)
    {
        int char_a = new_a[i] - '0';            // Converting ith charachter of the string to integer 
        int char_b = new_b[i] - '0';            // Converting ith charachter of the string to integer 
        int sum = char_a + char_b + carry;      // Summing up the ith character of both strings (converted to integer) with a carry 

    // inserting the (sum % 10) in the form of string into add_output which is the last digit of the sum and the remaining part of sum is set to carry. 
        add_output.insert(add_output.begin(), sum % 10 + '0'); 
        carry = sum / 10;
    }
    
    // After the for loop, if the carry is non-zero, it will be inserted in the beginning of the add_output
    if(carry > 0){
        add_output.insert(add_output.begin(), carry + '0');
    }
    // if no string is given, then the add_output will be 0. 
    return add_output;
}

// subtract Function is used to subtract strings a and b
string subtract(const string& a, const string& b) {
    int n = max(a.length(), b.length());
    string new_a = padding(a, n);
    string new_b = padding(b, n);

    string sub_output = "";              // Initialised the sub_output string where which will store my output of the subtraction.
    int borrow = 0;                                 
    for (int i = n - 1; i >= 0; i--)          
    {
        int char_a = new_a[i] - '0';
        int char_b = new_b[i] - '0';
        int sub = 0;
        sub = char_a - borrow - char_b;   // Subtract the ith character of string a and b and if there was a borrow, I update my string a by subtracting the borrow
        if(sub < 0){                      // if the subtraction is less than 0, it means borrowing is needed: 
            sub = sub + 10;               // subtraction is updated by adding 10 as a borrow of 1 is taken from the left digit
            borrow = 1;
        }
        else{
            borrow = 0;
        }
        sub_output.insert(sub_output.begin(), sub + '0'); 
    }

    // removing any leading zeros in the output by looping through the sub_output. 
    for (int i = 0; sub_output[0] == '0'; i++)
    {
        sub_output.erase(0, 1);
    }
    return sub_output;
}

// Multiply function is used to multiply two strings a and b 
string multiply(const string& a, const string& b) { 
    int n = max(a.length(), b.length());
    // if n is odd, then I want to make the string of even number of digits. So, i incremented n
    if(n%2 != 0){
        n = n + 1;
    }
    // Padding zeros at the beginning of the strings. 
    string new_a = padding(a, n);
    string new_b = padding(b, n);
    int split = n / 2;
    string result;

    // Base Case
    if (a.length() == 1 && b.length() == 1){
        result = to_string((a[0] - '0') * (b[0] - '0'));
        return result;
    }
    string a1 = new_a.substr(0, split); 
    string a0 = new_a.substr(split, split);
    string b1 = new_b.substr(0, split);
    string b0 = new_b.substr(split, split);

    string c2 = multiply(a1, b1);                   // c2 = a1. b1 
    string c0 = multiply(a0, b0);                   // c0 = a0. b0
    string c1 = multiply(add(a1, a0), add(b1, b0)); // c1 = (a1 + a0) * (b1 + b0)
    string h1 = c2 + string(n, '0');                
    string h2 = subtract(c1, c2);
    string h3 = subtract(h2, c0) + string(n / 2, '0');  

    result = add(add(h1, h3), c0);                  // c2 * 10^n + (c1 - c2 - c0)* 10^n/2 + c0

    // removing leading zeros
    for (int i = 0; result[0] == '0'; i++)
    {
        result.erase(0, 1);
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <num1> <num2>" << endl;
        return 1;
    }

    string num1(argv[1]);
    string num2(argv[2]);

    string result = multiply(num1, num2);
    cout << result << endl;

    return 0;
}


