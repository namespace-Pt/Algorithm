# NP完全理论
[TOC]
## 语言
### 基本定义
- 判定问题$Q$的实例
  - 以二进制编码的方式将**判定问题$Q$的问题实例( 问题的输入 )** 映射到$\Sigma^* = \{0,1\}^*$上, 得到**具体问题**
- **语言**
  - 一个问题$Q$的解为$1$的实例的集合描述了这个问题, 因此可以用这些实例形成一个语言, 代表整个具体问题, 有
  $$L = \{x\in \Sigma^*\mid Q(x)=1\}$$即问题$Q$转化为解为$1$的问题实例组成的集合$L$
  - **语言由某个问题抽象出来**, 而该问题由其**解**描述( **哈密尔顿圈的图由“包含哈密尔顿圈的图”完全构成, 与“不包含哈密尔顿圈的图”没有任何关系** ), 因此将**问题的解的编码汇总为一个集合, 即语言**；一个算法, 是用来解决这个问题的, 比如某算法判定一个图是否包含哈密尔顿圈。
    - 简而言之, **问题诱导出语言, 算法解决问题**
  - 最直观的定义语言的方式:$$L=\{<Q>\mid Q为真\}$$
  其中$<Q>$为问题$Q$的编码
    - **举例:** $L = \{<C>\mid C是一个包含哈密尔顿圈的图\}$
- **接受**
  - 对于输入的编码串$x,|x|=n$, 若$A(x)=1$, 则称算法$A$接受串$x$
- **拒绝**
  - 对于输入的编码串$x,|x|=n$, 若$A(x)=0$, 则称算法$A$拒绝串$x$
### 算法接受语言
对于给定的$L\subseteq \{0,1\}^*$, $$\exist k\in R, \forall x\in L, |x| = n, 有A(x)=1$$并且$T(A(x)) = O(n^k)$, 那么算法$A$能够在多项式时间内**接受**$L$
### 算法判定语言
对于给定的语言$L\subseteq \{0,1\}^*$,$$\exist k\in R, \forall x\in \{0,1\}^*, |x| = n,  有A(x)=\begin{cases}
    0&x\notin L\\
    1&x\in L
\end{cases} $$并且$T(A(x)) = O(n^k)$, 那么算法$A$能够在多项式时间内**判定**$L$
### 算法验证语言
对于给定的语言$L\subseteq \{0,1\}^*$, $$\exist c\in R, \forall x\in L,\exist y, |y| = O(|x|^c), 有A(x,y)=1$$
并且$T(A(x)) = O(n^k)$, 那么算法$A$能够在多项式时间内**验证**$L$
## P
$$\begin{aligned}
    P&=\{L\subseteq \{0,1\}^*\mid 存在一个算法A,可以在多项式时间内\textbf{判定}L \}\\
    \Leftrightarrow P&=\{L\subseteq \{0,1\}^*\mid 存在一个算法A, 可以在多项式时间内\textbf{接受}L \}
\end{aligned}$$

## NP
$$
    NP = \{L\subseteq\{0,1\}^*\mid存在一个算法A, 可以在多项式时间\textbf{验证}L\}
$$
### 性质
- $P\subseteq NP$
  - 在$P$对应的一个算法$A$中, 直接忽略证书, 然后像之前那样正常工作, 即可
- $NP\subseteq? P$
  - $co\_NP$为$\{0,1\}^*-NP$中仍然属于`NP`的语言结合, 那么$co\_NP$与`NP`是否相等尚待解决
  - 主流的观点认为$NP\ne co\_NP$且$P\subseteqq NP\cap co\_NP$

### 归约
#### 可归约性
  - $$\exist f:\{0,1\}^*\rightarrow \{0,1\}^*, \forall x\in L_1 \Leftrightarrow f(x)\in L_2, 并且T(f(x)) = O(n^k)$$则称语言$L_1$可以在多项式时间内归约到$L_2$, 记作$L_1\leq_p L_2$
  - **问题$Q$($L_1$对应的问题)的解也是$Q'$($L_2$对应的问题)的解**
  - 问题$Q$在**一个多项式因子内**与$Q'$**一样难**
#### 性质
  1. $$若L_1\leq_p L_2, \ 则L_2 \subseteq P \implies L_1\subseteq P$$
  2. $$若L'\subseteq NPC且L' \leq_p L\implies L\subseteq NP\_hard; 又若L\subseteq NP,则L\subseteq NPC$$
### NP完全
#### 定义
- $L\subseteq \{0,1\}^*$是`NPC`, **当且仅当**
  - **性质1:** $L\subseteq NP$
  - **性质2:** $\forall L' \subseteq NP, 有L'\leq_p L$
- 如果$L$仅满足性质2, 不满足性质1, 那么$L$是`NP-hard`
#### 证明一个语言$L\subseteq NPC$
- 由[归约的性质2](#归约), 首先证明$L\subseteq NP$
- 之后选择一个已知属于`NPC`的语言$L'$
- 证明$L'\leq_p L$, 即
  - 设计一个转换函数$f$, 能将$L'$中的每个实例映射到$L$中
  - 函数满足[可归约性](#归约)中提出的要求
  - 证明转换函数$f$是多项式时间的算法

## 实例
### 布尔公式(电路)可满足性
### 3-CNF可满足性
#### 注意点
  - 在构造`SAT`到`3-CNF`的归约函数$f$时, 由于电路中一个门电路的输出本质上是门电路输入的一个逻辑操作的结果, 然而输出和输入有不同的名字, 比如输入$x_1,x_2$, 输出$x_3$, 有$x_3 = x_1\wedge x_2$, 要想在布尔公式中同时反映$x_1,x_2,x_3$之间的关系, 需要使用$\leftrightarrow$(等价运算)作为一个**赋值操作**, 即$x_3\leftrightarrow (x_1\wedge x_2)$本质上和$x_3 = x_1\wedge x_2$没有任何不同
  - 将任意一个布尔公式转化为语法树后, 得到的表达式中每个合取的因子**最多都只有$3$项(根节点, 左子树根节点, 右子树根节点)**
### 最大团
- 定义
  - 图$G$上的一个完全子图
#### 对应语言
$$CLIQUE=\{<G,k>\mid G是一个包含规模为k的团的图\}$$
### 最小顶点覆盖
#### 对应语言
$$VC = \{<G,k>\mid G是一个包含规模为k的顶点覆盖的图\}$$
#### 证明为NPC
- 记图$G$为$G(V,E)$
- **证明$VC\subseteq NP$**
  - $\exist c\in R$, 对于$<G,k>$中一个给定的输入$x$,记$n = |x|$, 和一个证书$y$, 记图为$G(V,E)$, 显然有$|y| = O(V^2) = O(|x|^c)$
  - 由于$y$实际上是一个顶点的集合$V'$, 要验证该证书是否为$G$的顶点覆盖, 只需要遍历图$G$的邻接矩阵中每一个元素, 对于$M_{i,j} = 1$, 则检查$i,j$中是否至少有一个属于$V'$, 这个操作可以在$O(V^2) = O(|x|^2) = O(n^2)$内完成, 因此是多项式时间可验证的
  - 得证
- **证明$\exist L\subseteq NPC, L\leq_p VC$**
  - **选定**$L=CLIQUE$
  - **构造归约算法**$f$
    - $f$输入为$VC(G,k)$, 输出为$CLIQUE(\overline{G},n-k)$
  - **证明**$x\in CLIQUE\Leftrightarrow f(x)\in VC$
    - **充分性**$\Rightarrow$:
      - 考虑$V'$是$G$的团, $|V|=k$, 现要证明$V-V'$是$\overline{G}(V,\overline{E})$的一个顶点覆盖, 即$$\forall e(u,v) \in \overline{E}\quad u\in V-V', v\in V-V'至少成立一个$$
      - 对于$\forall e(u,v)\in \overline{E}$,假设$u\in V'$且$v\in V'$, 则根据$V'$是一个团, 一定有$e(u,v)\in E$, 产生矛盾；因此$u,v$中至少有一个顶不属于$V'\Leftrightarrow$属于$V-V'$ 
    - **必要性**$\Leftarrow$:
      - 考虑$V-V'$为$\overline{G}$的顶点覆盖, $|V-V'|=n-k$, 现要证明$V'$是$G$的一个团, 即$$\forall u,v\in V', \quad e(u,v)\in E$$
      - 对于$\forall u,v\in V'$, 若$e(u,v)\notin E$, 即$e(u,v)\in \overline{E}$, 则由于$V-V'$是$\overline{E}$的顶点覆盖, 则$e(u,v)$中至少有一个顶包含在$V-V'$中, 产生矛盾；因此$e(u,v)$一定属于$E$
    - 得证
  - **证明$f$是多项式时间的算法**
    - 将$G$转换为$\overline{G}$仅需要遍历其邻接矩阵中每一个元素, 将$1$改为$0$,$0$改为$1$即可完成
    - 因此有时间复杂度$O(V^2) = O(n^2)$
    - 得证
### 哈密尔顿圈
- 选定$L=Vertex\_Cover$
### 旅行商问题
- 选定$L=Hamilton$