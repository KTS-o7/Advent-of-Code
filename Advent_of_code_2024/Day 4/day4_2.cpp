#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

int find_xmas(vector<string> data){
    int count = 0;
    // Now we need to find number of MAS in X format
    // We supposed to find two MAS in the shape of an X. One way to achieve that is like this:
    /*
        M.S
        .A.
        M.S
    */    
    /*
    Example
    .M.S......
    ..A..MSMS.
    .M.S.MAA..
    ..A.ASMSM.
    .M.S.M....
    ..........
    S.S.S.S.S.
    .A.A.A.A..
    M.M.M.M.M.
    ..........


    Irrelevant characters have again been replaced with '.' in the above diagram. Within the X, each MAS can be written forwards or backwards.
    */

    int n = data.size();
    if (n == 0) return 0;
    int m = data[0].size();

    string word1 = "MAS";
    string word2 = "SAM";

    // Need at least 3x3 grid for an X pattern
    if (n < 3 || m < 3) return 0;

    for (int i = 1; i < n - 1; i++) {  // Start from 1 and end before last row
        for (int j = 1; j < m - 1; j++) {  // Start from 1 and end before last column
            // Check if center is 'A'
            if (data[i][j] != 'A') // if not 'A' then skip
                continue;

            // Get both diagonals
            string diag1, diag2;
            
            // Top-left to bottom-right diagonal
            diag1 += data[i-1][j-1];
            diag1 += data[i][j];
            diag1 += data[i+1][j+1];

            // Top-right to bottom-left diagonal
            diag2 += data[i-1][j+1];
            diag2 += data[i][j];
            diag2 += data[i+1][j-1];

            // Check if we have valid X pattern
            bool valid_diag1 = (diag1 == word1 || diag1 == word2);
            bool valid_diag2 = (diag2 == word1 || diag2 == word2);

            // Only count if both diagonals are valid
            if (valid_diag1 && valid_diag2) {
                count++;
            }
        }
    }
    return count;
}

int main(){
    freopen("day4_input.txt", "r", stdin);
    string s;
    vector<string> data;
    while(getline(cin, s)){
        data.push_back(s);
    }
    cout<<"Number of XMAS's in the data is: "<<find_xmas(data)<<endl;
    return 0;
}