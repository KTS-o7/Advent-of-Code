// Day 6 of advent of code
// Today we have a problem to find the path of the patrolling guard and count the distinct points visited by the guard

/*
The map shows the current position of the guard with ^ (to indicate the guard is currently facing up from the perspective of the map). Any obstructions - crates, desks, alchemical reactors, etc. - are shown as #.
*/

// Input is a vector of strings, each string is a row of the map
//guards follow a very strict patrol protocol which involves repeatedly following these steps:

// If there is something directly in front of you, turn right 90 degrees.
// Otherwise, take a step forward.
// the guard eventually leaves the mapped area
// How many distinct positions will the guard visit before leaving the mapped area including the starting position?



// First step is to find the starting point of the guard
// Then we need to find the path of the guard
// Then we need to count the distinct points visited by the guard
// We need to mark the points visited by the guard with a special character to count the distinct points

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int count_visited_points(vector<string> input) {
    int n = input.size(), m = input[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    
    // Find starting position
    int x = -1, y = -1;
    for(int i = 0; i < n && x == -1; i++) {
        for(int j = 0; j < m; j++) {
            if(input[i][j] == '^') {
                x = i;
                y = j;
                break;
            }
        }
    }
    
    // Direction vectors: UP, RIGHT, DOWN, LEFT
    vector<int> dx = {-1, 0, 1, 0};
    vector<int> dy = {0, 1, 0, -1};
    int direction = 0; // Start facing UP
    
    // Track visited positions until guard leaves map
    int turns = 0; // Count consecutive turns
    
    while(x >= 0 && x < n && y >= 0 && y < m) {
        // Mark current position
        visited[x][y] = true;
        
        // Check position in front
        int next_x = x + dx[direction];
        int next_y = y + dy[direction];
        
        // If next position is blocked or out of bounds, turn right
        if(next_x < 0 || next_x >= n || next_y < 0 || next_y >= m) {
            break;
        }
        if(input[next_x][next_y] == '#') {
            direction = (direction + 1) % 4;
        }
        else {
            // Move forward
            x = next_x;
            y = next_y;
            turns = 0; // Reset turns counter when we move
        }
    }
    
    // Count total visited positions
    int count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(visited[i][j]) {
                count++;
            }
        }
    }
    
    return count;
}

int main(){
    freopen("day6_input.txt", "r", stdin);
    vector<string> input;
    string s;
    while(getline(cin, s)){
        input.push_back(s);
    }

    cout<<"The total number of points visited by the guard are: "<<count_visited_points(input)<<endl;
}