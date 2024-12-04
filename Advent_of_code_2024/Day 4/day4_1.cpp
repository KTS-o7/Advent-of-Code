#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

int find_xmas(vector<string> data){
    int count = 0;
    int n = data.size();
    if (n == 0) return 0;
    int m = data[0].size();

    // Directions: right, down-right, down, down-left, left, up-left, up, up-right
    vector<int> dx = {0, 1, 1, 1, 0, -1, -1, -1};
    vector<int> dy = {1, 1, 0, -1, -1, -1, 0, 1};
    string word = "XMAS";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // The two outer loops iterate over all cells of the grid
            for (int dir = 0; dir < 8; dir++) {
                // The inner loop iterates over all directions
                int x = i, y = j, k;
                // Try to build the word in the current direction
                for (k = 0; k < 4; k++) {
                    // This loop iterates over all characters of the word XMAS
                    if (x < 0 || x >= n || y < 0 || y >= m) // break if out of bounds
                        break;
                    if (data[x][y] != word[k]) // break if the character is not matching
                        break;
                    x += dx[dir]; // This is the step to even include the overlapping characters
                    y += dy[dir];
                }
                if (k == 4)
                    count++;
            }

            // This will first find in horizontal right ,then down-right diagonal, then down, then down-left diagonal, then left, then up-left diagonal, then up and then up-right diagonal
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