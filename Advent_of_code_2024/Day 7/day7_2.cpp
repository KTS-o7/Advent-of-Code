#include <iostream>
#include <bits/stdc++.h>

using namespace std;

bool try_operations(const vector<long long>& numbers, long long target, long long current_value, int position) {
    if(position == numbers.size()) {
        return current_value == target;
    }
    
    // Try addition
    if(current_value <= LLONG_MAX - numbers[position] && 
       current_value + numbers[position] <= target) {
        if(try_operations(numbers, target, current_value + numbers[position], position + 1))
            return true;
    }
    
    // Try multiplication
    if(current_value != 0 && numbers[position] <= LLONG_MAX / current_value && 
       current_value * numbers[position] <= target) {
        if(try_operations(numbers, target, current_value * numbers[position], position + 1))
            return true;
    }
    
    // Try concatenation (||)
    if(current_value != 0) {
        string num1 = to_string(current_value);
        string num2 = to_string(numbers[position]);
        string concatenated = num1 + num2;
        try {
            long long concat_value = stoll(concatenated);
            if(concat_value <= target) {
                if(try_operations(numbers, target, concat_value, position + 1))
                    return true;
            }
        } catch(const exception& e) {
            // Skip if concatenation results in overflow
            cout<<"Exception: Occured when adding "<<num1<<" and " <<num2<<" "<<e.what()<<endl;

        }
    }
    
    return false;
}

long long calculate_calibration_sum(const vector<pair<long long, vector<long long>>>& parsed_input) {
    long long total_sum = 0;
    
    for(const auto& [target_value, numbers] : parsed_input) {
        if(!numbers.empty() && try_operations(numbers, target_value, numbers[0], 1)) {
            total_sum += target_value;
        }
    }
    
    return total_sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    freopen("test.txt", "r", stdin);
    vector<pair<long long, vector<long long>>> parsed_input;
    string line;
    
    while(getline(cin, line)) {
        stringstream ss(line);
        long long target;
        char colon;
        ss >> target >> colon;
        
        vector<long long> numbers;
        long long num;
        while(ss >> num) {
            numbers.push_back(num);
        }
        
        parsed_input.emplace_back(target, numbers);
    }
    
    cout << calculate_calibration_sum(parsed_input) << endl;
    return 0;
}