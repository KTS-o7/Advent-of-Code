#include<stdio.h>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

int count_safe_levels(vector<vector<int>>list){
    int safe_levels = 0;
    for(int i=0; i<list.size(); i++){
        int size = list[i].size();
        // Need to satisfy these 2 conditions
        // The levels are either all increasing or all decreasing.
        //Any two adjacent levels differ by at least one and at most three.
        // So we cant sort the list and compare the difference between adjacent elements
        // We need to first check if the level is increasing or decreasing
        // Then check if the difference between adjacent elements is between 1 and 3
        bool increasing = true;
        bool decreasing = true;
        bool valid_diff = true;
        for(int j=0; j<size-1; j++){
            if(list[i][j] > list[i][j+1]){
                increasing = false;
            }
            if(list[i][j] < list[i][j+1]){
                decreasing = false;
            }
            if(abs(list[i][j] - list[i][j+1]) > 3 || abs(list[i][j] - list[i][j+1]) < 1){
                valid_diff = false;
            }
            if(!increasing && !decreasing && !valid_diff){
                break;
            }
        }
        if((increasing || decreasing) && valid_diff){
            safe_levels++;
        }
    }
      return safe_levels;
}




int main() {
    FILE *f = freopen("./day2_1_input.txt", "r", stdin);
    vector<vector<int>> data;
    string line;

    while (getline(cin, line)) {
        istringstream iss(line);
        vector<int> row;
        int number;
        while (iss >> number) {
            row.push_back(number);
        }
        data.push_back(row);
    }

    cout << "Number of safe levels is " << count_safe_levels(data) << endl;
    fclose(f);
    return 0;
}