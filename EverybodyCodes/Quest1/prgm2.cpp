#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
This time, however, the battles become more challenging. According to the kingdom's spies, the enemies sometimes join forces in pairs, making them tougher to defeat.
When two monsters pair up, you will need one more potion per creature than in a one-on-one fight.
Your list remains a single line of creatures, but now you must interpret it in pairs. The x symbol shows an empty spot where no monster appears, so for these pairs your calculations should follow the same rules as for individual battles.
Example based on the following notes:
AxBCDDCAxD
After splitting into pairs, the battle sequence looks like this:
Ax BC DD CA xD
The Ax pair requires no potions because a single Ancient Ant remains weak as before.
The BC pair requires 6 potions which is 2 for the Badass Beetle and 4 for the Creepy Cockroach because they are attacking together.
The DD pair requires 12 potions which is 6 per Diabolical Dragonfly instead of the usual 5 since they are attacking together.
The CA pair requires 5 potions which is 4 for the Creepy Cockroach and 1 for the Ancient Ant.
The xD pair requires 5 potions because no additional potion is needed for a single Diabolical Dragonfly.
In total, you must order: 0 + 6 + 12 + 5 + 5 = 28 potions.
*/

int count_potions(string s) {
    unordered_map<char, int> potion_map = {{'A', 1}, {'B', 2}, {'C', 4}, {'D', 6}};
    int potions = 0;
    for (int i = 0; i < s.size(); i += 2) {
        cout<<s[i]<<" "<<s[i+1]<<endl;
        char first = s[i];
        char second = (i + 1 < s.size()) ? s[i + 1] : 'x';
        if (first == 'x') {
            potions += ((second == 'x') ? 0 : potion_map[second] - 1);
        } 
        else {
            potions += ((second == 'x') ? potion_map[first]-1 : (potion_map[first] + potion_map[second]));
        }
        cout<<"scores: "<<potions<<endl;
    }
    return potions;
}

int main(){
    freopen("input2.txt", "r", stdin);
    string s;
    cin >> s;
    cout<<"Number of potions needed is "<< count_potions(s) << endl;
    return 0;
}