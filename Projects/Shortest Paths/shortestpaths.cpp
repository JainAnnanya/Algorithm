/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Annanya Jain, Yanran Jia
 * Version     : 1.0
 * Date        : 6th December 2023
 * Description : All Pairs Shortest Paths
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/


#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <climits>

using namespace std;

// Imitialised my Infinity value
const long INF = LONG_MAX;

// Applied Floyd Algorithm to find all Pairs Shortest Path between vertices
void floydWarshall(vector<vector<long>>& graph, vector<vector<long>>& intermediate) {
    int V = graph.size();
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (graph[i][k] != INF && graph[k][j] != INF && (graph[i][k] + graph[k][j]) < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    intermediate[i][j] = k;
                }
            }
        }
    }
}

// To Print shortest paths between every vertex to every other vertex. For this I declared a string and kept appending the path found recursively. 
string findShortestPath(int start, int end, vector<vector<long>>& graph, vector<vector<long>>& intermediate){
    if (start != end && intermediate[start][end] == INF) {
        char e = static_cast<char>(end + 'A');
        string str = " -> ";
        str = str + e; 
        return str;

    } else if (start != end) {
        // Recursively finding the path from start to immediate and storing in a string 
        string a = findShortestPath(start, intermediate[start][end], graph, intermediate);
        // Recursively finding the path from immediate to end (the other part)
        string b = findShortestPath(intermediate[start][end], end, graph, intermediate);
        // adding both strings
        return a + b;
    }
    return "";
}

// Displays the matrix on the screen formatted as a table.
void display_table(vector<vector<long>> const &matrix, const string &label, const bool use_letters = false) {
    cout << label << endl;
    long max_val = 0;
    int V = matrix.size();
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            long cell = matrix[i][j];
            if (cell < INF && cell > max_val) {
                max_val = matrix[i][j];
            }
        }
    }
    int max_cell_width = use_letters ? to_string(max_val).length() : to_string(max(static_cast<long>(V), max_val)).length();
    cout << ' ';
    for (int j = 0; j < V; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < V; i++) {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < V; j++) {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == INF) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>(matrix[i][j] + 'A');
            } else {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    
    // Create an ifstream object.
    ifstream input_file(argv[1]);

    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    // Vertices is declared to be V
    int V;
    // Graph is a vector of vectors
    vector<vector<long>> graph;
    // Intermediate is a vector or vector for storing intermediates between path
    vector<vector<long>> intermediate;

    try {
        unsigned int line_number = 1;
        getline(input_file, line);
        istringstream iss(line);

        // Handling case for vertice should not be more than 26 or less than equal to 0. It should be a number. 
        if(!(iss >> V) || V <= 0 || V > 26){
            cerr << "Error: Invalid number of vertices '" << line << "' on line 1.";
            return 1;
        }

        // Initialsed Graph to have INF value. 
        graph = vector<vector<long> >(V, vector<long>(V, INF));
        // Initialsed Intermediate to have INF value. 
        intermediate = vector<vector<long> >(V, vector<long>(V, INF));  
        // The diagonal of the graph is initialed is to be 0. 
        for (int i = 0; i < V; ++i) {
            graph.at(i).at(i) = 0;
        }
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line)) {
            line_number++;
            istringstream iss(line);
            // Defined start, end and weight to take input for starting vertex, ending vertex and weight. 
            string start, end, weight_;
            
            // Handling error cases for start, end, weight. 
            if(!(iss>> start) || start.length() != 1 || (start[0] < 'A' || start [0] >= V + 'A')){
                cerr << "Error: Starting vertex '" << start << "' on line " << line_number << " is not among valid values A-" << static_cast<char>(V + 'A' - 1) << "." << endl;
                return 1;
            }
            if(!(iss>> end) || end.length() != 1 || (end[0] < 'A' || end[0] >= V + 'A')){
                cerr << "Error: Ending vertex '" << end << "' on line " << line_number << " is not among valid values A-" << static_cast<char>(V + 'A' - 1) << "." << endl;
                return 1;
            }

            if (!(iss >> weight_)) {
                cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
                return 1;
            }

            iss >> weight_; 
            int weight; 

            try{
                int weight = stoi(weight_);
                if(weight <= 0){
                    cerr << "Error: Invalid edge weight '" << weight_ << "' on line " << line_number << "." << endl;
                    return 1;
                }
            }    
            catch (const std::invalid_argument &i) {
                cerr << "Error: Invalid edge weight '" << weight_ << "' on line " << line_number << "." << endl;
                return 1;
            }    
        
            int u = start[0] - 'A';  // integer form of starting vertex
            int v = end[0] - 'A';    // integer form of ending vertex
            
            weight = stoi(weight_);   // Converting weight_ (string type) to integer type called weight
            // Through each iteration if while loop, graph at index (u, v) will contain the weight which will finally create a distance matrix.  
            graph.at(u).at(v) = weight;   
        }

        // Displaying the graph for Distance matrix. 
        display_table(graph, "Distance matrix:");    
        // Graph is created when the Floyd's Algorithm has been run. Simultaneously storing the intermediates in vector of vectors called intermediate. 
        floydWarshall(graph, intermediate);
        // Displaying the graph for path length after the Floyd's Algorithm has been run. 
        display_table(graph, "Path lengths:");  
        // Displaying the intermediate vertices after the Floyd's Algorithm has been run. 
        display_table(intermediate, "Intermediate vertices:", true);
        
        // Through nested for loops, determining all the possible combination of pairs of vertices possible in order to display the shortest paths. 
        for (int i = 0; i < V; i++){
            for (int j = 0; j < V; j++){
                cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A');
                if(graph[i][j] == INF){
                    cout << ", distance: infinity, path: none" << endl;
                }
                else{
                    cout << ", distance: " << graph[i][j] << ", path: ";
                    // if starting and ending vertex is same, then the path will just be starting vertex.
                    if(i == j){
                        cout << static_cast<char>(i + 'A') << endl;
                    }
                    // if starting and ending vertex is not the same, findShortestPath function is called. 
                    else{
                        cout << static_cast<char>(i + 'A'); 
                        cout << findShortestPath(i, j, graph, intermediate);
                        cout << endl;
                    }
                }
            }
        }

        // Don't forget to close the file
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }
    return 0;
}