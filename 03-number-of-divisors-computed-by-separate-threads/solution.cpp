#include <bits/stdc++.h>
using namespace std;
void count_div(vector<int>&V,int ind,vector<int>&Ans){
    int ans=0;
    for(int i = 1;i*i<=V[ind];i++){
        if(V[ind]%i==0){
            ans+=2;
            ans-=(i==(V[ind]/i));
        }
    }
    Ans[ind]=ans;
}
int main(){
    int n;
    cin >> n;
    vector<int>V(n);
    vector<int>Ans(n);
    for(int i = 0;i<n;i++)
        cin >> V[i];
    {
        vector<jthread>Threads;
        for(int i = 0;i<n;i++)
            Threads.emplace_back(count_div,ref(V),i,ref(Ans));
    }
    for(auto& x:Ans)
        cout << x << '\n';
    return 0;
}
