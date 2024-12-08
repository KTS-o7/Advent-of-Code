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
                cout << "Found antenna " << input[i][j] << " at (" << i << "," << j << ")\n";
            }
        }
    }
    
    set<pair<int,int>> antinodes;
    
    for(auto& [freq, positions] : freq_map) {
        for(int i = 0; i < positions.size(); i++) {
            for(int j = i + 1; j < positions.size(); j++) {
                auto [y1, x1] = positions[i];
                auto [y2, x2] = positions[j];
                
                // Check every point in grid
                for(int y = 0; y < rows; y++) {
                    for(int x = 0; x < cols; x++) {
                        // Calculate distances
                        double d1 = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
                        double d2 = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
                        
                        // Check collinearity using cross product
                        long long cross = (long long)(x - x1) * (y2 - y1) - 
                                        (long long)(y - y1) * (x2 - x1);
                        
                        // Check if point is collinear and has 2:1 distance ratio
                        if(cross == 0) {
                            double ratio = max(d1, d2) / min(d1, d2);
                            if(abs(ratio - 2.0) < 0.0001) {
                                cout << "Found antinode at (" << y << "," << x << ") for frequency " 
                                     << freq << " ratio: " << ratio << "\n";
                                antinodes.insert({y, x});
                            }
                        }
                    }
                }
            }
        }
    }
    
    cout << "Total antinodes found: " << antinodes.size() << "\n";
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