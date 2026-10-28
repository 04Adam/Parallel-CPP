# Number of divisors computed by separate threads

| Language | Tests | Time (run / limit) | Memory (used / limit) | Solved |
|---|---|---|---|---|
| C++ | ✅ 6/6 | 11 / 250 ms | 58.8 MB / 256 MB | 2026-10-17 |

## Problem statement

A divisor of a number $x$ is a positive integer that divides $x$ without a remainder.
The number $1$ has one divisor, and the number $12$ has six: $1$, $2$, $3$, $4$, $6$
and $12$.

The first line of standard input contains an integer $k$ from the interval
$[1, 16]$. The second line contains $k$ integers from the interval $[1, 10^{14}]$,
separated by single spaces.

Write a program that computes the number of divisors of each given number, dividing
the computation among threads running at the same time. The number of threads and
the way the work is divided among them are up to you.

#### Output

The output is $k$ lines. On line number $i$, print the number of divisors of the
$i$-th number from the input.

#### Example

**Input**
```
4
12 1 7 36
```

**Output**
```
6
1
2
9
```

> **Note.** The numbers in the input exceed the range of `int`.

> **Note.** The order in which threads run is undefined, so only the main thread
> prints the output, after the other threads have finished.

## Solution

File: [`solution.cpp`](solution.cpp)

```cpp
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
```
