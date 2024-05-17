# network layer

## router

buffering required when datagrams arrive from fabric faster than the transmission rate

scheduling discipline chooses among queued datagrams for transmission

## ip protocol

relay:中继

有五种中继设备
1. 物理层：repeater
2. 数据链路层：bridge
3. 网络层：router
4. 网桥和路由器混合：brouter
5. 网络层以上：网关 gateway

当中继系统是转发器或网桥时，一般并不称之为**网络互连**，因为这仅仅时把一个**网络扩大**了，而这任然时一个网络

## Virtual interconnection network
+ 互联起来的物理网络看起来时异构的，但使用IP protocol 就可以使这些性能各异的网络从用户看起来好像是一个统一的网络
+ 看起来像一个网络一样
+ 如果在这种覆盖全球的IP网上使用TCP协议，那么就是现在的互联网