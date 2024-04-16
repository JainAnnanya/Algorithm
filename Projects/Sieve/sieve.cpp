/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Annanya Jain
 * Date        : 19 September, 2023
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
    is_prime_{new bool[limit + 1]}, limit_{limit} {
        sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the requirements document.

    // To find count of the integers which are prime where loop starts countuing from 2 to the max_prime_. 
    int cnt = 0;
    for (int i = 2; i <= max_prime_; i++){
        if (is_prime_[i] == true){
            cnt++;
        }
    }
    cout << cnt << endl;

    cout << "Primes up to " << limit_ << ":" << endl;

    // To find the width of the maximum prime value and how many primes we can fit on a row, I have used the given formula. 
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);

    // To count the prime numbers printed, I will keep adding them once printed in the variable : current_primes_number
    // Thus, I initialised the variable to 0. 
    int current_primes_number = 0;
    for (int i = 2; i <= max_prime_; i++)
    {
        if(is_prime_[i] == true){

            // Since we can fit only 80 characters on a row. If all the primes till the given limit can fit in a single row,
            // then the maximum limit should be given as 106, where max_prime number will be 103. 
            // In this case, we print out only 1 space between the prime numbers. 
            if(limit_ <= 106){
                // if condition is for printing the first prime integer in the row. 
                if(current_primes_number == 0){
                    cout << i;
                    current_primes_number++;
                }
                else{
                    cout << " " << i;
                    current_primes_number++;
                }    
            }
            // If all the primes till the given limit cannot fit in a single row, 
            // I have used an else condition for printing primes in this case.
            else{
                // When the variable current_primes_number is equal the primes_per_row allowed, I start printing them on the next row.
                // Hence, current_primes_number is again set to 0 to make it start counting again. 
                if(current_primes_number == primes_per_row){
                    cout << "\n";
                    current_primes_number = 0;
                }

                // if condition is for printing the first prime integer in the row, as in this case the space before printing the 
                // first prime in that row will vary accodingly. Hence, the passed formula in setw varies from that of the else condition.   
                if(current_primes_number == 0){
                    cout << setw(max_prime_width - num_digits(i)) << "" << i;
                    current_primes_number++;
                }
                else{
                    cout  << setw(max_prime_width - num_digits(i) + 1) << "" << i;
                    current_primes_number++;
                }    
            }
        }
    }    
    cout << "\n";
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.

    //Traversing the array is_prime_ starting from smallest prime number 2 to the limit. 
    // We initailise all the indexes i representing the actual numbers to boolean true. 

    for (int i = 2; i <= limit_; i++)
    {
        is_prime_[i] = true;
    }

    // Using Sieve of Eratosthenes algorithm to assign the correct integers true or false depending whether they are prime or not. 
    for (int i = 2; i <= sqrt(limit_); i++){
        if (is_prime_[i] == true){
            for(int j = i*i; j<= limit_; j+=i){
                is_prime_[j] = false;
            }
        }
    }

    // We calculate the maximum prime number in the given limit and input it in the variable max_prime_.
    max_prime_ = 2;
    for(int i = 2; i <= limit_ ; i++){
        if(is_prime_[i] == true){
            max_prime_ = i;
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count = 0;
    while(num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    cout << endl;
    cout << "Number of primes found: ";
    PrimesSieve sieve(limit);
    // I have hereby called the display_primes() function to print the desired output. 
    sieve.display_primes();
    return 0;
}
