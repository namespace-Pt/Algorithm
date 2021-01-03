# 数学知识
## 界
### 函数增长
- $$n! = w(2^n)$$
- $$n! = O(n^n)$$
### 求和
- $$\begin{aligned}
    1 + \int_2^{n+1}\frac{1}{x}dx &\leq\sum_{i=1}^{n}\frac{1}{i} \leq 1+ \int_1^n\frac{1}{x}dx\\
    \implies 1+\ln2+\ln n &\leq \sum_{i=1}^{n}\frac{1}{i} \leq 1+\ln n
\end{aligned}$$
- $$\forall |x| < 1\quad\sum_{k=0}^{\infty}kx^k = \frac{x}{(1-x)^2}$$
- $$(\sum_{i}^nf(i))^2 = ?$$
- $$\sum_{i=1}^n\lceil\lg i\rceil = n\lg n -n + 1????$$
### 向上取整和向下取整
- $$\forall n,m\in N^+ \quad \lfloor \frac{n}{m}\rfloor + 1 = \lceil\frac{n+1}{m}\rceil$$ 
### 极限
- **斯特林公式**:$$\lim_{n\rightarrow \infin}\frac{n!}{\sqrt{2\pi n }(\frac{n}{e})^n} = 1$$

## 树
- $k$层的完全二叉树有$2^{k+1}-1$个节点(**单独一个顶点的树为0层**)
- 完全二叉树的第$i$层共有$2^i$个节点
