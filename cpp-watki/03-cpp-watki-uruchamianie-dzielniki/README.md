# Liczba dzielników wyznaczana przez osobne wątki

| | |
|---|---|
| **Course** | [Programowanie wielowątkowe w C++](http://localhost:3000/zestawy/cpp-watki) |
| **Difficulty** | 🟡 medium |
| **Language** | C++ |
| **Limits** | 250 ms · 256 MB |
| **Result** | ✅ 6/6 tests · max 11 ms · 58.8 MB |
| **Solved** | 2026-10-17 |

[Open the problem on Gym Analitica →](http://localhost:3000/zadania/cpp-watki-uruchamianie-dzielniki)

## Problem statement

Dzielnikiem liczby $x$ nazywa się liczbę całkowitą dodatnią, przez którą $x$
dzieli się bez reszty. Liczba $1$ ma jeden dzielnik, a liczba $12$ ma ich
sześć: $1$, $2$, $3$, $4$, $6$ oraz $12$.

Na standardowym wejściu zapisana jest w pierwszym wierszu liczba całkowita $k$
z przedziału $[1, 16]$. W wierszu drugim zapisanych jest $k$ liczb całkowitych
z przedziału $[1, 10^{14}]$, rozdzielonych pojedynczymi odstępami.

Napisz program, który wyznaczy liczbę dzielników każdej z zapisanych liczb,
rozdzielając obliczenia między wątki działające w tym samym czasie. Liczba
wątków i sposób podziału pracy między nie są dowolne.

#### Wynik

Wynikiem jest $k$ wierszy. W wierszu o numerze $i$ należy wypisać liczbę
dzielników $i$-tej liczby z wejścia.

#### Przykład

**Wejście**
```
4
12 1 7 36
```

**Wynik**
```
6
1
2
9
```

> **Uwaga.** Liczby z wejścia przekraczają zakres typu `int`.

> **Uwaga.** Kolejność wykonania wątków jest nieokreślona, wobec czego wynik
> wypisuje wyłącznie wątek główny po zakończeniu pozostałych wątków.

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
