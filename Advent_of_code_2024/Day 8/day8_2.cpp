#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int count_antinodes(vector<string> input) {
    int rows = input.size();
    int cols = input[0].size();
    
    map<char, vector<pair<int,int>>> freq_map;
    
    // Find all antennas
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(input[i][j] != '.') {
                freq_map[input[i][j]].push_back({i, j});
            }
        }
    }
    
    set<pair<int,int>> antinodes;
    
    for(auto& [freq, positions] : freq_map) {
        // If more than one antenna of this frequency exists
        if(positions.size() > 1) {
            // Add all antenna positions as antinodes
            for(auto& pos : positions) {
                antinodes.insert(pos);
            }
            
            // Check all pairs of antennas
            for(int i = 0; i < positions.size(); i++) {
                for(int j = i + 1; j < positions.size(); j++) {
                    auto [y1, x1] = positions[i];
                    auto [y2, x2] = positions[j];
                    
                    // Check every point in grid
                    for(int y = 0; y < rows; y++) {
                        for(int x = 0; x < cols; x++) {
                            // Check collinearity using cross product
                            long long cross = (long long)(x - x1) * (y2 - y1) - 
                                            (long long)(y - y1) * (x2 - x1);
                            
                            if(cross == 0) {
                                antinodes.insert({y, x});
                            }
                        }
                    }
                }
            }
        }
    }
    
    return antinodes.size();
}

int main(){
    vector<string> input;
    string s;
    freopen("day8_input.txt", "r", stdin);
    while(getline(cin, s)){
        input.push_back(s);
    }
    cout << "Number of antinodes: " << count_antinodes(input) << endl;
    return 0;
}