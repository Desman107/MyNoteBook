# dp

## 01背包
+ 状态表示用$f(i,j)$,表示只从前$i$个物品中选,总体积不超过$j$时的取值最大值
+ 若$f(i,j)$中不含第$i$个物品，则$f(i,j)=f(i-1,j)$
+ 若含$i$则$f(i,j)=f(i-1,j-v_i)+w_i $。
+ 由此，可以推导出状态转移方程


```cpp
int v[N], w[N]; // 表示物品的体积和价值
int f[N][N];
cin >> n >> m;
for  (int i = 1; i <= n; i ++ ) cin >> v[i] >> w[i];
for (int i = 1; i <= n; i ++ ){
    for (int j = 0; j <= m; j ++ ){
        f[i][j] = f[i - 1][j]; 
        if ( j >= v[i]) f[i][j]  max(f[i][j], f[i - 1][j - v[i]] + w[i]);
    }
}
cout << f[n][m] << endl;
```
### 滚动数组优化
```cpp
for (int i = 1; i <= n; i ++ )
    for (int j = m; j >= v[i]; j -- )
        f[j] = max(f[j], f[j - v[i]] +w[i]);
```

## 完全背包问题
f[i,j]表示所有只考虑前$i$个物品，且总体积不大于$j$的所有选法的价值最大值
+ 当不含第$i$个物品`f[i,j] = f[i-1,j]`
+ 当含$k$个物品$i$，`f[i,j] = f[i-1,j-k*v[i]]  + k*w[i]`

```cpp
for (int i = 1; i <= n; i ++ )
    for (int j = 0; j <= m; j ++ )
        for(int k = 0; k * v[i] <= j; k ++ )
            f[i][j] = max(f[i][j], f[i - 1][j - v[i] * k] + w[i] * k);
```
很明显，时间复杂度过高，需要优化

### 滚动数组优化
当 $j = v_i$ 时 $f_j$ 的位置一定只有一个物品 $i$， 当$j = k \cdot v_i$时， $j$ 的位置已近包含了 $k - 1$个物品 $i$ 的情况
```cpp
for (int i = 1; i <= n; i ++ )
    for (int j = v[i]; j <= m; j ++ )
            f[j] = max(f[j],f[j -  v[i]] +  w[i]);
        
    
```

## 多重背包问题


```cpp
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 1010;
int n, m;
int v[N], w[N], s[N];
int f[N][N];
int main(){
    cin >> n >> m;
    for (int i = 1; i <= n;  i ++ ){
        cin >> v[i] >> w[i] >> s[i];
    }
    for (int i = 1; i <= n; i ++ ){
        for (int j = 0; j <= m; j ++ ){
            for (int k = 0; k <= s[i] && k * v[i] <= j; k ++ ){
                
                f[i][j] = max(f[i][j],f[i - 1][j - k * v[i]] + k * w[i]);
            }
        }
    }
    cout << f[n][m];
}
```


### 二进制优化
若有$s$个物品$i$,可以将其分为若干组物品，每组物品视为一个数量只有1个的新物品

在二进制中
$$
\begin{align}
2^0&=1 \\
2^1&=10 \\
2^2&=100\\
2^3&=1000\\
2^4-1&=1111
\end{align}
$$
```cpp
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 25000, M = 2010;

int v[N], w[N];
int f[M];

int n, m;

int main(){
    
    cin >> n >> m;
    int cnt = 0;
    for(int i = 1; i <= n; i ++ ){
        int a, b, s; // 记录第i个物品的体积价值和个数
        cin >> a >> b >>s;
        int k = 1; // 从1个一组开始打包
        while( k <= s){
            cnt ++ ;
            v[cnt] = k * a; // 记录本次拆分的体积
            w[cnt] = k * b; // 记录本次拆分的价值
            s -= k; // 总个数减去本次打包个数
            k *= 2; // 下次打包的个数是本次的两倍
            
        }
        // 若还有剩余，则将剩下的物品打包成一组
        if(s > 0){
            cnt ++ ;
            v[cnt] = s * a;
            w[cnt] = s * b;
        }
    }

    // 剩下的就是把问题当成01背包做
    n = cnt;
    for (int i = 1; i <= n; i ++ ){
        for(int j = m; j >= v[i]; j -- ){
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    cout << f[m];
}
```