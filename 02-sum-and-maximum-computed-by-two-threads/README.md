# Sum and maximum computed by two threads

| Language | Tests | Time (run / limit) | Memory (used / limit) | Solved |
|---|---|---|---|---|
| C++ | ✅ 7/7 | 78 / 100 ms | 58.7 MB / 256 MB | 2026-10-17 |

## Problem statement

The first line of standard input contains an integer $n$ from the interval
$[1, 10^5]$. The second line contains $n$ integers from the interval
$[-10^9, 10^9]$, separated by single spaces.

Write a program that computes the sum and the largest value of the given numbers,
using worker threads for the computation. The number of threads and the way the work
is divided among them are up to you.

#### Output

The output is two lines. On the first line, print the sum of the numbers, and on the
second the largest of them.

#### Example

**Input**
```
5
3 -7 12 4 12
```

**Output**
```
24
12
```

> **Note.** The program prints no messages other than the output. A prompt asking for
> input results in a failed check.

> **Note.** The sum of the numbers can exceed the range of `int`.

> **Note.** The order in which threads run is undefined, so only the main thread
> prints the output, after the other threads have finished.

## Solution

File: [`solution.cpp`](solution.cpp)

```cpp
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
```
