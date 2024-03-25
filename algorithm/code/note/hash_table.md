# hash table

将大范围数映射到小范围数

通常采用模运算
最好采用质数，这样冲突概率最小

可能存在冲突

## 拉链法
![拉链法解决冲突](image/拉链hash.drawio.png)
使用链表存储冲突数
一般冲突数很小

插入操作代码
```cpp
int h[N], e[N], ne[N], idx;

void insert(int x){
    int k = (x % N + N) % N;//防止出现负数
    e[idx] = x;
    ne[idx] = h[k];//头插
    h[k] = idx ++ ;
}
```
![](image/hash_insert.drawio.png)