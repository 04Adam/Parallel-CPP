#include <bits/stdc++.h>
using namespace std;
#define ll long long
void counter(vector<ll>&tab,vector<vector<int>>&Ans,int l,int r,int T){
    for(int i=l;i<r;i++){
        ll num = tab[i];
        do{
            Ans[T][num%10]++;
            num/=10;
        }
        while(num>0);
    }
}
int main(){
    int n,T;
    cin >> n >> T;
    vector<ll>tab(n);
    for(int i = 0;i<n;i++)
        cin >> tab[i];
    vector<vector<int>>Ans(T,vector<int>(10));
    {
        vector<jthread>Threads;
        for(int t = 0;t<T;t++){
            Threads.emplace_back(counter,ref(tab),ref(Ans),n*t/T,n*(t+1)/T,t);
        }
    }
    /*
    for(int i = 0;i<T;i++){
        for(auto x:Ans[i])
            cout << x << ' ';
        cout << '\n';
    }
    */
    for(int i = 0;i<=9;i++){
        int occ=0;
        for(int t = 0;t<T;t++)
            occ+=Ans[t][i];
        cout << occ << ' ';
    }


    return 0;
}
