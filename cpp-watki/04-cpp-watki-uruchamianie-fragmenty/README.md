# Sumy rozłącznych fragmentów ciągu

| | |
|---|---|
| **Course** | [Programowanie wielowątkowe w C++](http://localhost:3000/zestawy/cpp-watki) |
| **Difficulty** | 🟡 medium |
| **Language** | C++ |
| **Limits** | 100 ms · 256 MB |
| **Result** | ✅ 7/7 tests · max 29 ms · 62.2 MB |
| **Solved** | 2026-10-17 |

[Open the problem on Gym Analitica →](http://localhost:3000/zadania/cpp-watki-uruchamianie-fragmenty)

## Problem statement

Ciąg $n$ liczb o indeksach od $0$ do $n - 1$ dzieli się na $w$ fragmentów
o numerach od $0$ do $w - 1$. Fragment o numerze $k$ obejmuje indeksy od
$\lfloor n \cdot k / w \rfloor$ włącznie do $\lfloor n \cdot (k + 1) / w \rfloor$
wyłącznie. Dla $n = 10$ oraz $w = 3$ fragmenty obejmują kolejno indeksy
$0$–$2$, $3$–$5$ oraz $6$–$9$. Fragment może być pusty, a jego suma wynosi
wówczas $0$.

Na standardowym wejściu zapisane są w pierwszym wierszu dwie liczby całkowite:
$n$ z przedziału $[1, 10^5]$ oraz $w$ z przedziału $[1, 16]$. W wierszu drugim
zapisanych jest $n$ liczb całkowitych z przedziału $[-10^9, 10^9]$,
rozdzielonych pojedynczymi odstępami.

Napisz program, który wyznaczy sumę każdego fragmentu ciągu oraz sumę całego
ciągu, korzystając z wątków roboczych. Fragmenty określają wyłącznie postać
wyniku: liczba wątków i sposób podziału pracy między nie są dowolne.

#### Wynik

Wynikiem jest $w + 1$ wierszy. W pierwszych $w$ wierszach należy wypisać sumy
kolejnych fragmentów, w kolejności ich numerów, a w wierszu ostatnim sumę
całego ciągu.

#### Przykład

**Wejście**
```
10 3
4 8 15 16 23 42 1 2 3 5
```

**Wynik**
```
27
81
11
119
```

> **Uwaga.** Iloczyn $n \cdot (k + 1)$ może przekroczyć zakres typu `int`.

> **Uwaga.** Kolejność wykonania wątków jest nieokreślona, wobec czego wynik
> wypisuje wyłącznie wątek główny po zakończeniu pozostałych wątków.

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
