#include <bits/stdc++.h>
using namespace std;
#define ll long long
void Max(vector<int>&V,int& ans){
    int a = -INT_MAX;
    for(int i = 0;i<V.size();i++)
        a=max(V[i],a);
    ans = a;
}
void Sum(vector<int>&V,ll& ans){
    ll a = 0;
    for(int i = 0;i<V.size();i++)
        a+=V[i];    
    ans = a;
}
int main(){
    int n;
    cin >> n;
    vector<int>V(n);
    for(int i = 0;i<n;i++)
        cin >> V[i];

    int max_=0;
    ll sum_=0; 
    thread s(Max,ref(V),ref(max_));
    thread m(Sum,ref(V),ref(sum_));
    s.join();
    m.join();
    cout << sum_ << '\n' << max_;
    return 0;
}
