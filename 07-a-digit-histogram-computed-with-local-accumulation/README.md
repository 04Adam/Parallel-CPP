# A digit histogram computed with local accumulation

| Language | Tests | Time (run / limit) | Memory (used / limit) | Solved |
|---|---|---|---|---|
| C++ | ✅ 6/6 | 78 / 150 ms | 32.0 MB / 256 MB | 2026-10-29 |

## Problem statement

The first line of standard input contains two integers: $n$ from the interval
$[1, 10^5]$ and $w$ from the interval $[1, 16]$. The second line contains $n$
integers from the interval $[0, 10^{18}]$, separated by single spaces.

Write a program that, for each digit from $0$ to $9$, computes how many times it
occurs in total in the decimal notations of all the given numbers, dividing the
computation among threads. The number $w$ is a suggested number of threads; the way
the work is divided is up to you.

The number $0$ has one digit $0$ in decimal notation.

#### Output

The output is one line containing ten numbers separated by single spaces: the number
of occurrences of digit $0$, digit $1$ and so on, up to digit $9$.

#### Example

**Input**
```
4 2
120 7 0 9907
```

**Output**
```
3 1 1 0 0 0 0 2 0 2
```

> **Note.** The numbers in the input exceed the range of `int`.

> **Note.** The checker compares only standard output and doesn't detect data races.
> A solution containing a data race may be graded differently on the next submission.

## Solution

File: [`solution.cpp`](solution.cpp)

```cpp
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
```
