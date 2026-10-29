#include <bits/stdc++.h>
using namespace std;
#define ll long long
void counter(vector<ll>&tab,vector<pair<int,int>>&Ans,int l,int r,int T){
    int Max = 0;
    int ind = 0;
    for(int i = l;i<r;i++){
        int sum=0;
        ll num = tab[i];
        do{
            sum+=num%10;
            num/=10;
        }
        while(num>0);
        if(Max<sum){
            Max=sum;
            ind = i;
        }
    }
    Ans[T]={Max,ind};
}
int main(){
    int n,T;
    cin >> n >> T;
    vector<ll>tab(n);
    for(int i = 0;i<n;i++)
        cin >> tab[i];
    vector<pair<int,int>>Ans(T,{0,0});
    {
        vector<jthread>Threads;
        for(int i = 0;i<T;i++)
            Threads.emplace_back(counter,ref(tab),ref(Ans),n*i/T,n*(i+1)/T,i);
    }
    pair<int,int>ans={0,0};
    for(auto x:Ans){
        if(ans.first<x.first)
            ans=x;
    }
    cout << ans.second+1 << ' ' << ans.first << '\n';

    return 0;
}
