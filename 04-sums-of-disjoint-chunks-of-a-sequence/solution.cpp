#include <bits/stdc++.h>
using namespace std;
void sum_seg(vector<int>&V,vector<long long>&seg,int ind,vector<long long>&Ans){
    int n = ind==seg.size()-1?seg.size():seg[ind+1];
    //cout << seg[ind] << ' ' << n << '\n';
    long long ans = 0;
    for(int i = seg[ind];i<n;i++)
        ans+=V[i];
    Ans[ind]=ans;
}
int main(){
    long long n,k;
    cin >> n >> k;
    vector<int>V(n);
    for(int i = 0;i<n;i++)
        cin>>V[i];
    vector<long long>seg(k);
    for(int i = 1;i<k;i++)
        seg[i] = n*i/k;
    seg.push_back(n);
    vector<long long>Ans(k);
    {
        vector<jthread>Threads;
        for(int i = 0;i<seg.size()-1;i++)
            Threads.emplace_back(sum_seg,ref(V),ref(seg),i,ref(Ans));
    }
    for(int i = 0;i<k;i++)
        cout << Ans[i] << '\n';
    cout << accumulate(Ans.begin(),Ans.begin()+k,(long long)0);
    return 0;
}
