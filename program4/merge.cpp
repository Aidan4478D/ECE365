#include <iostream>
#include <string>
#include <vector> 
#include <fstream>

#define MAX_LENGTH 1000
#define INF 1000000

using namespace std; 

string checkMerge(string s1, string s2, string merge) {
    
    int len1 = s1.length();
    int len2 = s2.length(); 

    //if the two lengths don't add up it's not a valid merge to begin with
    if(len1 + len2 != merge.length()) return "*** NOT A MERGE ***"; 

    //create matrix
    int matrix[MAX_LENGTH + 1][MAX_LENGTH + 1]; 

    //initialize initial rows and columns of matrix
    for(int i = 0; i <= len1; i++)
        matrix[0][i] = INF; 
    for(int j = 0; j <= len2; j++)
        matrix[j][0] = INF; 

    //initial row 0 check
    for(int i = 1; i < len1; i++) {
        if(s1[i - 1] == merge[i - 1]) 
            matrix[0][i] = matrix[0][i - 1] + 1;
    }
    //initial column 0 check
    for(int j = 1; j < len2; j++) {
        if(s2[j - 1] == merge[j - 1]) 
            matrix[j][0] = matrix[j - 1][0] + 1;
    }


    //merge check
    for(int i = 1; i <= len2; i++) {
        for(int j = 1; j <= len1; j++) {
            
            //if the string 2 character matches up with the merged string character
            //set its matrix value to 1 + the row above it (same column)
            if(s2[i - 1] == merge[i + j - 1] && matrix[i - 1][j] != INF) {
                matrix[i][j] = matrix[i - 1][j] + 1;
                continue;
            }
            
            //if the string 1 character matches up with the merged string character
            //set its matrix value to 1 + the column to the left of it (same row)
            if(s1[j - 1] == merge[i + j - 1] && matrix[i][j - 1] != INF) {
                matrix[i][j] = matrix[i][j - 1] + 1;
                continue;
            }

            //otherwise set the matrix cell to be unknown
            matrix[i][j] = INF;
        }   
    }
    
    //output
    if (matrix[len2][len1] != INF) {
        
        while (len1 > 0 && len2 >= 0) {

            //match the first string to the merge string but not the second
            if ((matrix[len2][len1] != INF) && (len2 == 0 || (matrix[len2 - 1][len1]) == INF)) {

                //overwrite the original string with uppercase
                merge[len1 + len2 - 1] = toupper(merge[len1 + len2 - 1]);
                len1--;
            } 
            else len2--;
        }

        return merge; 

    } else return "*** NOT A MERGE ***";
}


int main() {

    string file;

    cout << "Enter name of input file: ";
    cin >> file; 
    ifstream f(file);

    cout << "Enter name of output file: ";
    cin >> file; 
    ofstream of(file); 
    
    string line, s1, s2, merge;
    int counter = 0;

    //get input
    while (getline(f, s1) && getline(f, s2) && getline(f, merge)) {
        
        //output merge result in output file
        of << checkMerge(s1, s2, merge) << "\n";
    }

    f.close();
    of.close(); 

    return 0; 
}
