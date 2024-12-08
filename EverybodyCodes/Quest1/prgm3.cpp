#include <iostream>
#include <bits/stdc++.h>

using namespace std;
/*
The final round is here, and, as expected, it is the most challenging of all! Although no new enemies have appeared, they have grown wiser and realized their strength in numbers.
In this ultimate challenge, you will not just face pairs, but also groups of three! For these tough battles, you will need 2 extra potions per creature compared to fighting them one-on-one.
Example based on the following notes:
xBxAAABCDxCC
Once the battles are split into their respective groups, they will unfold as follows:
xBx AAA BCD xCC
In total, you must order: 1 + 6 + 15 + 8 = 30 potions.
*/
int count_potions(string s){
    unordered_map<char, int> potion_map = {{'A', 0}, {'B', 1}, {'C', 3}, {'D', 5}};
    int potions = 0;
    for(int i=0;i<s.size();i=i+3){
        char first = s[i];
        char second = (i + 1 < s.size()) ? s[i + 1] : 'x';
        char third = (i + 2 < s.size()) ? s[i + 2] : 'x';
        if(first == 'x'){
            int temp = 0;
            if(second == 'x' && third == 'x'){
                temp = 0;
            }
            else if(second == 'x'){
                temp = potion_map[third];
            }
            else if(third == 'x'){
                temp = potion_map[second];
            }
            else{
                temp = potion_map[second] + potion_map[third] + 2;
            }
            potions += temp;
        }
        else{
            int temp = 0;
            if(second == 'x' && third == 'x'){
                temp = potion_map[first];
            }
            else if(second == 'x'){
                temp = potion_map[first] + potion_map[third] + 2;
            }
            else if(third == 'x'){
                temp = potion_map[first] + potion_map[second] + 2;
            }
            else{
                temp = potion_map[first] + potion_map[second] + potion_map[third] + 6;
            }
            potions += temp;
        }
   
    }
    return potions;
}

int main(){
    freopen("input3.txt", "r", stdin);
    string s;
    cin >> s;
    cout<<"Number of potions needed is "<< count_potions(s) << endl;
    return 0;
}