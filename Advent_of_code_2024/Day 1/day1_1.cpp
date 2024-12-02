#include<bits/stdc++.h>
#include <stdio.h>

using namespace std;

int find_sum_of_errors(vector<int>list1, vector<int>list2){
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());
    int sum = 0;
    for(int i = 0; i < list1.size(); i++){
        sum += abs(list1[i] - list2[i]);
    }
    return sum;
}

int main(){
    // Read input from file but i dont know the input size
    // Data is of format
    // 1 2
    // 3 4
    // list1 will be 1, 3
    // list2 will be 2, 4

    freopen("./day1_1_input.txt", "r", stdin);
    vector<int>list1;
    vector<int>list2;
    int a, b;
    while(cin >> a >> b){
        list1.push_back(a);
        list2.push_back(b);
    }
    cout <<"Sum of errors is " <<  find_sum_of_errors(list1, list2) << endl;
    return 0;
}

