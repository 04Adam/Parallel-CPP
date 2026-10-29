#include <bits/stdc++.h>
using namespace std;
bool is_prime(int a){
    if(a<=1)
        return false;
    for(int i = 2;i*i<=a;i++)
        if(a%i==0)
            return false;
    return true;
}
void counter(vector<int>&Ans,int l,int r,int n){
    int ans=0;
    for(int i = l;i<r;i++)
        ans+=is_prime(i);
    Ans[n] = ans;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int l,r,T;
    cin >> l >> r >> T;
    vector<int>Ans(T);
    {
        vector<jthread>Threads;
        for(int i = 0;i<T;i++){
            Threads.emplace_back(counter,ref(Ans),(r-l)*i/T+l,(r-l)*(i+1)/T+l+(i==(T-1)),i);
           // cout << (r-l)*(i)/T+l << ' ' << (r-l)*(i+1)/T+l+(i==(T-1)) << '\n';
        }
    }
    int ans=0;
    for(auto& x:Ans)
        ans+=x;
    cout << ans << '\n';

    return 0;
}
