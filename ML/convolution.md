# 卷积

## 连续函数的卷积操作
given continuous function $f(x)$ and $g(x)$
the convolution of the two function is $y(n)$
the formula of continuous convolution is:
$$
\begin{aligned}
y(n) &= f(n) * g(n) \\
&= \int_{-\infty}^{+\infty}f(x)g(n-x)dx
\end{aligned}
$$

## 离散函数的卷积
given discrete function $f[n]$ and $g[n]$ 
the convolution of the two function is $y[n]$
the formula of discrete convolution is:
$$
\begin{aligned}
y[n] &= f[n] * g[n] \\
&=\sum_{x=-\infty}^{+\infty}f[x]\cdot g[n-x]
\end{aligned}
$$