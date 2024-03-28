

# data link layer

## basic 
+ link
  + 一条无源的点到点的物理线路段，中间没有任何其他的交换节点

+ data link
  + protocol + link
  + 在不可靠的物理线路(错误，延迟，丢失)上实现可靠的传输

end to end 包含中间节点
point to point 不包含任何节点

## main function

1. framing
2. flow control
3. error control
4. transparent transmission
5. mac addressing
6. link management

## framing
bit stuffing
以一个特定的位序作为帧的头尾标志
为了避免原始数据与标志组合相同，会在即将重合的位置插入0或1

## error control
cyclic redundancy check循环冗余检测CRC
n + 1位的除数
n位的crc码

* 发送端
  先将原始数据后加n位0
  与除数相除后得到余数crc码
  k位数据后跟n位crc

* 接收端
  若余数位0则接受
  否则抛弃
  接受后前k位是信息
