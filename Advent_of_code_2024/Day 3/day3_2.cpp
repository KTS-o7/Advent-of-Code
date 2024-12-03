#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

int sum_of_mul_parsing(vector<string> data) {
    int sum = 0;
    bool enabled = true;
    // Input to this function is a vector of strings
    // In each string we need to find patterns of form mul(x,y) where x and y are integers of 1 to 3 digits
    // any other characters are ignored
    // even substrings like mul( 2, 3) are invalid
    // We need to find all such patterns and return the sum of all x*y

    // We can use regex to find the pattern
    // Combined regex pattern to match both control and mul instructions
    regex pattern(R"(((?:do|don't)\(\)|mul\((\d{1,3}),(\d{1,3})\)))");

    // Once we find the pattern, we need to check if it is a control instruction or a multiplication instruction
    // If it is a control instruction, we need to enable or disable the multiplication instructions
    // If it is a multiplication instruction, we need to multiply the numbers and add to the sum
    
    for (const auto& str : data) {
        auto begin = sregex_iterator(str.begin(), str.end(), pattern);
        auto end = sregex_iterator();
        
        for (auto it = begin; it != end; ++it) {
            smatch match = *it;
            string full_match = match[0].str();
            
            if (full_match == "do()" || full_match == "don't()") {
                // Handle control instruction
                enabled = (full_match == "do()");
                cout << "Control instruction: " << full_match << ", enabled = " << enabled << endl;
            }
            else if (enabled) {
                // Handle multiplication when enabled
                int x = stoi(match[2].str());
                int y = stoi(match[3].str());
                sum += x * y;
                cout << "Processing mul(" << x << "," << y << ") = " << x * y << endl;
            }

            else if (!enabled){
                cout<<"Control disabled"<<" Ignoring mul("<<match[2].str()<<","<<match[3].str()<<")"<<endl;
            }
        }
    }
    
    cout << "Final sum: " << sum << endl;
    return sum;
}

int main() {
    freopen("./day3_input.txt", "r", stdin);
    string line;
    vector<string> data;
    
    while (getline(cin, line)) {
        data.push_back(line);
    }
    
    sum_of_mul_parsing(data);
    return 0;
}