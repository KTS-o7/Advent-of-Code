#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

int sum_of_mul_parsing(vector<string> data){
    int sum = 0;
    // Input to this function is a vector of strings
    // In each string we need to find patterns of form mul(x,y) where x and y are integers of 1 to 3 digits
    // any other characters are ignored
    // even substrings like mul( 2, 3) are invalid
    // We need to find all such patterns and return the sum of all x*y

    // We can use regex to find the pattern
    // The pattern is mul(1-3 digits,1-3 digits)
    regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    for (const auto& str : data) {
        auto words_begin = sregex_iterator(str.begin(), str.end(), pattern);
        auto words_end = sregex_iterator();
        for (auto it = words_begin; it != words_end; ++it) {
            smatch match = *it;
            int x = stoi(match[1].str());
            int y = stoi(match[2].str());
            sum += x * y;
        }
    }
    cout << "Sum of all x*y is " << sum << endl;

    return sum;
}


int main(){
    freopen("./day3_input.txt", "r", stdin);
    string line;
    vector<string> data;
    while(getline(cin, line)){
        data.push_back(line);
    }
    //for(auto i: data){
      //  cout << i << endl;
    //}
    sum_of_mul_parsing(data);
    return 0;
}