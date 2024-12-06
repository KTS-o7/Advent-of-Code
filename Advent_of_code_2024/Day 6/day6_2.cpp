#include <iostream>
#include <bits/stdc++.h>

using namespace std;

pair<int, int> find_start(const vector<string>& grid_map) {

    // This function finds the starting position of the guard
    // in the grid map. The guard is represented by the character '^'.
    // The function returns the position of the guard as a pair of integers.
    for(int i = 0; i < grid_map.size(); i++) {
        for(int j = 0; j < grid_map[0].size(); j++) {
            if(grid_map[i][j] == '^') {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

bool is_inside(const pair<int, int>& pos, int rows, int cols) {
    // This function checks if a position is inside the grid map.
    // The function returns true if the position is inside the grid map
    return pos.first >= 0 && pos.first < rows && pos.second >= 0 && pos.second < cols;
}

set<pair<int, int>> get_original_path(vector<string> grid_map) {
    // This function finds the path of the guard in the grid map.
    // The function returns a set of pairs representing the path of the guard.
    // The first element of the pair is the row index and the second element is the column index.
    set<pair<int, int>> path;
    pair<int, int> pos = find_start(grid_map);
    pair<int, int> dir = {-1, 0}; // Start facing up
    
    while(is_inside(pos, grid_map.size(), grid_map[0].size())) {
        path.insert(pos);
        
        if(grid_map[pos.first][pos.second] != '#') {
            grid_map[pos.first][pos.second] = 'X';
        } 
        else {
            // Backtrack and turn right
            pos.first -= dir.first;
            pos.second -= dir.second;
            
            // Rotate direction right
            int temp = dir.first;
            dir.first = dir.second;
            dir.second = -temp;
        }
        
        pos.first += dir.first;
        pos.second += dir.second;
    }
    
    return path;
}

bool creates_loop(vector<string> grid_map) {
    pair<int, int> pos = find_start(grid_map);
    pair<int, int> dir = {-1, 0};
    unordered_map<int, vector<pair<int, int>>> visited;
    
    while(is_inside(pos, grid_map.size(), grid_map[0].size())) {
        if(grid_map[pos.first][pos.second] != '#') {
            int idx = pos.first * grid_map.size() + pos.second;
            
            for(const auto& d : visited[idx]) {
                if(d == dir) return true;
            }
            
            visited[idx].push_back(dir);
        } 
        else {
            // Backtrack and turn right
            pos.first -= dir.first;
            pos.second -= dir.second;
            
            int temp = dir.first;
            dir.first = dir.second;
            dir.second = -temp;
        }
        
        pos.first += dir.first;
        pos.second += dir.second;
    }
    
    return false;
}

int count_loop_positions(const vector<string>& grid_map) {
    set<pair<int, int>> original_path = get_original_path(grid_map);
    int count = 0;
    
    for(const auto& pos : original_path) {
        if(grid_map[pos.first][pos.second] == '.') {
            vector<string> test_grid_map = grid_map;
            test_grid_map[pos.first][pos.second] = '#';
            
            if(creates_loop(test_grid_map)) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    freopen("day6_input.txt", "r", stdin);
    vector<string> grid_map;
    string line;
    
    while(getline(cin, line)) {
        grid_map.push_back(line);
    }
    
    cout << "Number of positions that create loops: " << count_loop_positions(grid_map) << endl;
    return 0;
}