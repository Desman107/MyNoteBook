# data link layer review

## main functions of Data link layer
1. link management 
2. Framing
3. Flow control
4. Error control
5. Transparent transmission
6. Mac addressing

点对点用ppp协议(point to point protocol)

## 数据同步方式

+ 同步：是接收端与发送端在手法数据的时间基准上保持一致
+ 同步问题：
  + 如何保证数据块的起始位置对准
  + 如何保证数据块中的每一位对准
+ 同步方式
  + 位同步
  + 帧同步
  

位同步：
1. 外同步，发数据同时发时钟信号
2. 自同步，通过特殊编码（如曼彻斯特编码）数据信号包含了同步脉冲


帧同步：
识别一个帧的起始和结束。以帧为边界实现数据块的同步接收

帧是包含了数据和控制信息的数据块

### framing封装成帧
framing就是在数据前后分别添加首部和尾部
首部和尾部的重要作用就是帧定界

字符填充：byte stuffing


## transparent transmission透明传输
无论发送什么样的比特组合数据，这些数据都能按照原样没有差错第通过这个数据链路层

## Error control差错控制



## ppp要求
简单
封装成帧
透明性
多重网络协议
多种类型链路
差错检测
检测连接状态
最大传送单元
网络层地址协商
数据压缩协商

不用的功能：

纠错
流量控制
序号
多点线路
半双工或单工链路

## ppp协议的组成
三个组成部分

1. 将ip数据报封装到串行链路的方法---区分帧的边界，并支持差错检测
2. 链路控制协议lcp（LINK CONTROL PROTOCOL） 
3. 网络控制协议 NCP

## CSMA/CD
Carrier Sense Multiple Access with Collision Detection

1. listen before sending 
2. listen and send
3. conflict then stop
4. retransmission after random delay
   
## 集线器和交换机的带宽
N个用户共享集线器的带宽b
平均每个用户仅占有B/N的带宽

交换机为诶个端口提供带宽B
N个用户，每个用户独占带宽B
交换机总带宽达到B*N

