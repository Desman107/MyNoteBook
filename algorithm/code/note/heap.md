## heap堆

由完全二叉树构成
数组模拟heap，下标从1开始
某个下表为x的节点，其左孩子是2x，右孩子是2x+1

根节点是整个树的最小值，左节点是左边树的最小值，右节点是右边树的最小值

## 相关操作
1. down(x):
找到x和2x，2x+1三个节点中的最小值，将最小值和x交换
```cpp
#include<algorithm>
int h[N],size;
void down(int u){
    int t = u;
    if (u * 2 <= size && h[u * 2] < h[t]) t = u * 2;
    if (u * 2 + 1 <= size && h[2 * u + 1] < h[t]) t = u * 2 + 1;
    if( u != t){
        swap(h[u], h[t]);
        down(t);
    }
}
```

2. up(x):
   将x与其父节点进行比较，比较后进行交换

3. 插入某个数x
   heap[++size] = x, up(size)
   
4. 求集合最小值
   heap[1]
5. 删除最小值
   heap[1] = heap[size];size--;down(1)
6. 删除任意元素
   heap[x] = heap[size];size--;down(x);up(x)
7. 修改任意元素 
   heap[k] = x;down(k);up(k)
8. 给定一个数组，将其变成heap
```cpp
for(i = size / 2; i ; i -- ){
    down(i);
}
```