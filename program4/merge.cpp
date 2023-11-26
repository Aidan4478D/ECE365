#include <iostream>

using namespace std; 

int LCSP(string s1, string s2) {

    int r = s1.length(); 
    int c = s2.length(); 
    //character matrix to store characters in strings
    int matrix[r][c]; 

    //initialize first column and first row with zeros
    for(int i = 0; i < r; i++)
        matrix[0][i] = 0; 
    for(int j = 0; j < c; j++)
        matrix[j][0] = 0; 
    
    
    for(int i = 1; i < r - 1; i++) {
        
        for(int j = 1; j < c - 1; j++) {
            
            if(s1[i] == s2[j]) {
                matrix[i][j] = matrix[i - 1][j - 1] + 1; 
            }
            else if(matrix[i - 1][j] >= matrix[i][j - 1]) {
                matrix[i][j] = matrix[i - 1][j];
            }
            else {
                matrix[i][j] = matrix[i][j - 1]; 
            }
        }
    }
    //return matrix[r - 1][c - 1]; */
    return 0; 
}

string checkMerge(string s1, string s2, string merge) {

    return nullptr; 
}


int main() {

    string s1 = "hello";
    string s2 = "world";
    string s3 = "wohrellold";


    int result = LCSP(s1, s3);

    cout << s3 << " and " << s1 << " have an LCSP value of " << result << endl; 

    return 0; 
}
