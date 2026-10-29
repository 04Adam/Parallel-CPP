# Primes in an interval counted without a shared counter

| Language | Tests | Time (run / limit) | Memory (used / limit) | Solved |
|---|---|---|---|---|
| C++ | ✅ 7/7 | 51 / 75 ms | 27.4 MB / 256 MB | 2026-10-29 |

## Problem statement

A prime is an integer greater than $1$ that has exactly two divisors: $1$ and itself.
The numbers $2$, $3$, $5$ and $7$ are primes, while $1$ and $9$ aren't.

Standard input contains three integers on one line: $a$ and $b$, satisfying
$1 \le a \le b \le 2 \cdot 10^5$, and $w$ from the interval $[1, 16]$.

Write a program that computes how many primes belong to the interval $[a, b]$,
dividing the computation among threads. The number $w$ is a suggested number of
threads; the way the work is divided is up to you.

#### Output

The output is one line containing the number of primes in the interval $[a, b]$.

#### Example

**Input**
```
1 100 4
```

**Output**
```
25
```

> **Note.** The checker compares only standard output and doesn't detect data races.
> A solution containing a data race may be graded differently on the next submission.

## Solution

File: [`solution.cpp`](solution.cpp)

```cpp
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
```
