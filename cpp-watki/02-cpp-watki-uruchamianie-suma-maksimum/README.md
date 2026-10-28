# Suma i największa wartość wyznaczane przez dwa wątki

| | |
|---|---|
| **Course** | [Programowanie wielowątkowe w C++](http://localhost:3000/zestawy/cpp-watki) |
| **Difficulty** | 🟢 easy |
| **Language** | C++ |
| **Limits** | 100 ms · 256 MB |
| **Result** | ✅ 7/7 tests · max 78 ms · 58.7 MB |
| **Solved** | 2026-10-17 |

[Open the problem on Gym Analitica →](http://localhost:3000/zadania/cpp-watki-uruchamianie-suma-maksimum)

## Problem statement

Na standardowym wejściu zapisana jest w pierwszym wierszu liczba całkowita $n$
z przedziału $[1, 10^5]$. W wierszu drugim zapisanych jest $n$ liczb całkowitych
z przedziału $[-10^9, 10^9]$, rozdzielonych pojedynczymi odstępami.

Napisz program, który wyznaczy sumę oraz największą wartość zapisanych liczb,
wykorzystując do obliczeń wątki robocze. Liczba wątków i sposób podziału pracy
między nie są dowolne.

#### Wynik

Wynikiem są dwa wiersze. W pierwszym wierszu należy wypisać sumę liczb,
a w drugim największą z nich.

#### Przykład

**Wejście**
```
5
3 -7 12 4 12
```

**Wynik**
```
24
12
```

> **Uwaga.** Program nie wypisuje żadnych komunikatów poza wynikiem. Tekst
> zachęty do podania danych powoduje ocenę negatywną.

> **Uwaga.** Suma liczb może przekroczyć zakres typu `int`.

> **Uwaga.** Kolejność wykonania wątków jest nieokreślona, wobec czego wynik
> wypisuje wyłącznie wątek główny po zakończeniu pozostałych wątków.

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
