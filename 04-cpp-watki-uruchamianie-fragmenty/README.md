# Sums of disjoint chunks of a sequence

| Language | Tests | Time (run / limit) | Memory (used / limit) | Solved |
|---|---|---|---|---|
| C++ | ✅ 7/7 | 29 / 100 ms | 62.2 MB / 256 MB | 2026-10-17 |

## Problem statement

A sequence of $n$ numbers with indices from $0$ to $n - 1$ is divided into $w$ chunks
numbered from $0$ to $w - 1$. Chunk number $k$ covers indices from
$\lfloor n \cdot k / w \rfloor$ inclusive to $\lfloor n \cdot (k + 1) / w \rfloor$
exclusive. For $n = 10$ and $w = 3$, the chunks cover indices $0$–$2$, $3$–$5$ and
$6$–$9$ in turn. A chunk may be empty, and its sum is then $0$.

The first line of standard input contains two integers: $n$ from the interval
$[1, 10^5]$ and $w$ from the interval $[1, 16]$. The second line contains $n$
integers from the interval $[-10^9, 10^9]$, separated by single spaces.

Write a program that computes the sum of each chunk of the sequence and the sum of
the whole sequence, using worker threads. The chunks only define the form of the
output: the number of threads and the way the work is divided among them are up to
you.

#### Output

The output is $w + 1$ lines. On the first $w$ lines, print the sums of consecutive
chunks, in order of their numbers, and on the last line the sum of the whole
sequence.

#### Example

**Input**
```
10 3
4 8 15 16 23 42 1 2 3 5
```

**Output**
```
27
81
11
119
```

> **Note.** The product $n \cdot (k + 1)$ can exceed the range of `int`.

> **Note.** The order in which threads run is undefined, so only the main thread
> prints the output, after the other threads have finished.

## Solution

File: [`solution.cpp`](solution.cpp)

```cpp
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
```
