# stl容器
1. vector, 变长数组
2. string，字符串，substr(),c_str()
3. priority_queue,优先队列,push(),top(),pop()
4. queue,队列，push(),front(),pop()
5. stack,栈,push(),top(),pop()
6. set,map,multiset,multimap，动态维护有序序列
7. unordered，哈希
8. bitset，压位
   
## 导入库
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
```
## vector
初始化
```cpp
vector<int> a(10);//定义一个长度为10的vector
vector<int> a(10,3);//定义长度为10的vector，内容全是3
vector<int> a[10];//定义10个vector
```
功能
```cpp
a.size();//返回a中元素的个数,所有容器都有
a.empty();//返回a是否空，所有容器都有
a.clear();//清空，并不是所有容器都有
```
增删查
```cpp
a.front();//返回第一个数
a.back();//返回最后一个数
a.push_back();//向最后插入一个数
a.pop_back();//删最后一个数
begin();end();//第零个数和最后一个数的后一个数
```
遍历
```cpp
for ( int i = 0; i < a.size(); i ++ ) cout << a[i] << ' ';
for ( vector<int>::iterator i = a.begin(); i != a.end(); i ++ ) cout << *i << ' '; 
for(auto x : a) cout << x << ' ';
```

## pair
二元组
初始化
```cpp
pair<int, string> p;
p = make_pair(10,"hdz")
p = {20, "abc"}
```
方法
```cpp
p.first//第一个元素
p.second
```

## string
支持size(),empty(),clear();
初始化与相加
```cpp
string a = "abc";
a += "pp";
```
子串
```cpp
a.substr(4,6)//起始位置和长度 
a.substr(4) == a.substr(4,a.size()+10);
```
## queue
无clear()
```cpp
push() //向队尾插入
front()//返回队头元素
back()//返回对胃元素
pop()//弹出对头元素
```

## priority_queue
优先队列，默认是大根堆
push(),pop(),top()

## stack
push(),top(),pop()
无clear()

## deque
size(),
empty(),
clear(),
front(),back(),
push_back(),push_front(),
pop_front(),pop_back(),
begin(),end(),
[]

## set/multiset
insert()
find()
count()
erase()