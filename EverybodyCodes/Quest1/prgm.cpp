#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int count_potions(string s){
    int potions = 0;
    for(auto ch:s){
        if(ch == 'A'){
            continue;;
        }
        else if(ch == 'B'){
            potions++;
        }
        else if(ch == 'C'){
            potions += 3;
        }
    }
    return potions;
}

int main(){
    freopen("input.txt", "r", stdin);
    string s;
    cin >> s;
    cout<<"Number of potions needed is "<< count_potions(s) << endl;
    return 0;
}