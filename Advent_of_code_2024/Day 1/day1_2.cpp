#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

int find_similarity_score(const vector<int>list1, const vector<int>list2){
    map<int, int>frequency;
    for(int i=0; i<list2.size(); i++){
        frequency[list2[i]]++;
    }

    int similarity_score = 0;
    for(int i=0; i<list1.size(); i++){
        similarity_score += frequency[list1[i]]*list1[i];
    }
    return similarity_score;
}

int main(){
    FILE *f;
    f = freopen("./day1_1_input.txt", "r", stdin);
    vector<int>list1;
    vector<int>list2;
    int a, b;
    while(cin >> a >> b){
        list1.push_back(a);
        list2.push_back(b);
    }
    cout <<"Sum of similarity scores is " <<  find_similarity_score(list1, list2) << endl;
    fclose(f);
    return 0;
}