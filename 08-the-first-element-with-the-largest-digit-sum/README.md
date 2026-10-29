# The first element with the largest digit sum

| Language | Tests | Time (run / limit) | Memory (used / limit) | Solved |
|---|---|---|---|---|
| C++ | ✅ 6/6 | 124 / 125 ms | 38.5 MB / 256 MB | 2026-10-29 |

## Problem statement

The digit sum of a number is the sum of the digits of its decimal notation. The digit
sum of $505$ is $10$, and the digit sum of $0$ is $0$.

The first line of standard input contains two integers: $n$ from the interval
$[1, 10^5]$ and $w$ from the interval $[1, 16]$. The second line contains $n$
integers from the interval $[0, 10^{18}]$, separated by single spaces. The numbers
are numbered from $1$ to $n$, in the order they're given.

Write a program that computes the largest digit sum occurring among the given numbers
and the number of the **first** number with that digit sum, dividing the computation
among threads. The number $w$ is a suggested number of threads; the way the work is
divided is up to you. The result must not depend on which thread finishes first.

#### Output

The output is one line containing two numbers separated by a single space: the number
of the first number with the largest digit sum, and that digit sum.

#### Example

**Input**
```
7 3
15 88 4 79 97 16 3
```

**Output**
```
2 16
```

The largest digit sum, equal to $16$, belongs to the numbers numbered $2$, $4$ and
$5$. The result is the smallest number.

> **Note.** The numbers in the input exceed the range of `int`.

> **Note.** The checker compares only standard output and doesn't detect data races.
> A solution containing a data race may be graded differently on the next submission.

## Solution

File: [`solution.cpp`](solution.cpp)

```cpp
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
```
