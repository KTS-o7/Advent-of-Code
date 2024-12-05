// Ok now for part two we have to do the following

/*
For each of the incorrectly-ordered updates, use the page ordering rules to put the page numbers in the right order. For the above example, here are the three incorrectly-ordered updates and their correct orderings:

75,97,47,61,53 becomes 97,75,47,61,53.
61,13,29 becomes 61,29,13.
97,13,75,29,47 becomes 97,75,47,29,13.
After taking only the incorrectly-ordered updates and ordering them correctly, their middle page numbers are 47, 29, and 47. Adding these together produces 123.

Find the updates which are not in the correct order. What do you get if you add up the middle page numbers after correctly ordering just those updates?

*/


#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<int> parse_sequence(string sequence) {

    // This function will parse the sequence and return a vector of integers. Nothing fancy here.
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

    // This function also is same as the previous one. It will take a sequence and a vector of rules and check if the rules are being followed or not.
    unordered_map<int, int> positions;
    for (int i = 0; i < sequence.size(); i++) {
        positions[sequence[i]] = i;
    }
    
    for (const auto& rule : rules) {
        if (positions.count(rule.first) && positions.count(rule.second)) {
            if (positions[rule.first] >= positions[rule.second]) {
                return false;
            }
        }
    }
    return true;
}

vector<int> topological_sort(const vector<int>& sequence, const vector<pair<int,int>>& rules) {
    // This is a new addition. This function will take a sequence and a vector of rules and return a topologically sorted sequence.
    // We would need topological sort because we need to take a non qualified sequence and sort it according to the rules.
    // Rules are basically precedence rules. If 47 comes before 53, then 47 is the parent and 53 is the child.
    // So we need to arrange them in topological order.

    // Create adjacency list
    unordered_map<int, vector<int>> graph;
    unordered_map<int, int> indegree;
    
    // Initialize
    // This is creating a graph where each page number is a node and the indegree is initialized to 0.
    for (int page : sequence) {
        graph[page] = vector<int>();
        indegree[page] = 0;
    }
    
    // Build graph from applicable rules
    // Here rules are basically telling us which page number comes before which page number.
    // So we are creating a graph where the parent is the page number and the child is the page number that comes after the parent.
    for (const auto& rule : rules) {
        if (graph.count(rule.first) && graph.count(rule.second)) {
            graph[rule.first].push_back(rule.second);
            indegree[rule.second]++;
        }
    }
    
    // Find starting nodes (indegree = 0)
    priority_queue<int> pq; // Use priority queue for lexicographical order
    for (const auto& node : indegree) {
        if (node.second == 0) {
            pq.push(node.first);
        }
    }
    
    vector<int> result;
    
    // Process nodes
    while (!pq.empty()) {
        int current = pq.top();
        pq.pop();
        result.push_back(current);
        
        for (int next : graph[current]) {
            indegree[next]--;
            if (indegree[next] == 0) {
                pq.push(next);
            }
        }
    }
    
    // Ultimately we will get a topologically sorted sequence.
    // Now all we need to do is to find its middle elemen and add it to the sum as needed.
    return result;
}

int find_sum_of_mid_incorrect(vector<string>& rules, vector<string>& sequences) {
    // Parse rules same as before
    vector<pair<int,int>> parsed_rules;
    for (const string& rule : rules) {
        int page1, page2;
        if (sscanf(rule.c_str(), "%d|%d", &page1, &page2) == 2) {
            parsed_rules.push_back({page1, page2});
        }
    }

    int sum = 0;
    for (const string& sequence : sequences) {
        if (sequence.empty()) 
            continue;
        
        vector<int> pages = parse_sequence(sequence);
        if (pages.empty()) 
            continue;
        
        // Only process incorrect sequences. This is the update for part two.
        if (!check_rules(pages, parsed_rules)) {
            vector<int> sorted_pages = topological_sort(pages, parsed_rules);
            sum += sorted_pages[sorted_pages.size() / 2];
        }
    }

    return sum;
}

int main() {
    vector<string> rules;
    vector<string> sequences;
    string line;
    
    freopen("day5_input.txt", "r", stdin);
    
    // Read rules
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
        int result = find_sum_of_mid_incorrect(rules, sequences);
        cout << "The sum of middle elements from incorrect sequences is " << result << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}