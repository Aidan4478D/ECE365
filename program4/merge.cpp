#include <iostream>
#include <string>

#include <vector> 
#include <fstream>


using namespace std; 

#define MAX_LENGTH 1000
#define INF 1000000

string checkMerge(string s1, string s2, string merge) {
    
    //if the two lengths don't add up it's not a valid merge to begin with
    if(s1.length() + s2.length() != merge.length()) return "*** NOT A MERGE ***"; 

    //create matrix
    int matrix[MAX_LENGTH + 1][MAX_LENGTH + 1]; 


    //initialize initial rows and columns of matrix
    for(int i = 0; i <= s1.size(); i++)
        matrix[0][i] = INF; 
    for(int j = 0; j <= s2.size(); j++)
        matrix[j][0] = INF; 

    //initial row 0 check
    for(int i = 1; i < s1.size(); i++) {
        if(s1[i - 1] == merge[i - 1])
            matrix[0][i] = matrix[0][i - 1] + 1;
    }
    //initial column 0 check
    for(int j = 1; j < s2.size(); j++) {
        if(s2[j - 1] == merge[j - 1])
            matrix[j][0] = matrix[j - 1][0] + 1;
    }

    //merge check stuff here (figure this out)
    for(int i = 1; i <= s2.size(); i++) {
        for(int j = 1; j <= s1.size(); j++) {
    
            
        }   
    }




    return nullptr; 
}


int main() {

    string file;
    cout << "Enter name of input file: ";
    cin >> file; 

    ifstream f(file);

    cout << "Enter name of the output file: ";
    cin >> file; 
    ofstream of(file); 
    
    string line, s1, s2, merge;
    int counter = 0;

    while(!f.eof()) {
        
        //get content from file
        getline(f, line);
        if(line.empty()) continue; 
        
        if((counter % 3) == 0) s1 = line; 
        if((counter % 3) == 1) s2 = line; 
        if((counter % 3) == 2) { 
            merge = line;
            of << checkMerge(s1, s2, merge) << "\n"; 
        }
        counter++; 
    }

    return 0; 
}
