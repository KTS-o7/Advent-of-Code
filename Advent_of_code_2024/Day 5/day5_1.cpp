// Day 5 of advent of code 2024. Phew didnt know that i could do this.

// The question is pretty complex
// So lets try to simplify it

/* 
Input Format:
First part: Rules in the format X|Y meaning "page X must be printed before page Y"
Second part: Lists of page numbers representing update sequences
*/


// Main task
// 1. For each update sequence:
//    - Check if it follows ALL applicable rules
//    - Rules only apply if BOTH pages mentioned in rule exist in the sequence
//    - If sequence is valid, find its middle number

// 2. Sum up all middle numbers from valid sequences

// Example:
// Rules: "47|53" means 47 must come before 53
// Sequence "75,47,61,53,29" is valid because:
// - All rules involving these numbers are followed
// - Middle number is 61


// Possible approach:
// 1. Parse input into:
//    - Map/vector of rules
//    - Vector of sequences

// 2. For each sequence:
//    - Check each applicable rule
//    - If all rules pass, add middle number to sum

// 3. Return final sum


#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<int> parse_sequence(string sequence) {
    vector<int> pages;
    stringstream ss(sequence);
    string num;
    
    while (getline(ss, num, ',')) {
        if (!num.empty()) {
            pages.push_back(stoi(num));
        }
    }
    return pages;
}

bool check_rules(const vector<int>& sequence, const vector<pair<int,int>>& rules) {
    // Create a map of positions
    unordered_map<int, int> positions;
    for (int i = 0; i < sequence.size(); i++) {
        positions[sequence[i]] = i;
    }
    // position[i] = j means page i is at position j in the sequence
    // Check each applicable rule
    for (const auto& rule : rules) {
        int before = rule.first;
        int after = rule.second;
        
        // Only check rule if both pages exist in sequence
        if (positions.count(before) && positions.count(after)) {
            if (positions[before] >= positions[after]) {
                return false;
            }
        }
    }
    return true;
}

int find_sum_of_mid(vector<string>& rules, vector<string>& sequences) {
    // Parse rules
    vector<pair<int,int>> parsed_rules;
    for (const string& rule : rules) {
        int page1, page2;
        if (sscanf(rule.c_str(), "%d|%d", &page1, &page2) == 2) {
            parsed_rules.push_back({page1, page2});
        }
    }

    // Process sequences
    int sum = 0;
    for (const string& sequence : sequences) {
        if (sequence.empty()) 
            continue;
        
        vector<int> pages = parse_sequence(sequence);
        if (pages.empty()) 
            continue;
        
        if (check_rules(pages, parsed_rules)) {
            sum += pages[pages.size() / 2];
        }
    }

    return sum;
}

int main() {
    vector<string> rules;
    vector<string> sequences;
    string line;
    
    freopen("day5_input.txt", "r", stdin);
    
    // Read rules until empty line
    while (getline(cin, line) && !line.empty()) {
        if (line.find('|') != string::npos) {
            rules.push_back(line);
        }
    }
    
    // Read sequences
    while (getline(cin, line)) {
        if (!line.empty()) {
            sequences.push_back(line);
        }
    }

    try {
        int result = find_sum_of_mid(rules, sequences);
        cout << "The sum of middle elements is " << result << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}