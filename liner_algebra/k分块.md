# 矩阵分块

左边矩阵列的分块方法必须与右边矩阵行的分块方法保持一致
这也两个矩阵分块后一定可以相乘
左边只有列有要求，右边只有行有要求
尽可能分出一些特殊的矩阵（零矩阵或单位矩阵）


$$
A = 
\begin{bmatrix}
a& \cdots & b \\
\vdots & \ddots & \vdots\\
c & \cdots & d  
\end{bmatrix}
$$