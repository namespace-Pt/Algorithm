# 概率分析和随机算法
## 界
### 级数求和
- 经典
  $$1 + \int_2^{n+1}\frac{1}{x}dx \leq\sum_{i=1}^{n}\frac{1}{i} \leq 1+ \int_1^n\frac{1}{x}dx\\\implies 1+\ln2+\ln n \leq \sum_{i=1}^{n}\frac{1}{i} \leq 1+\ln n$$

## 实例
### 雇佣问题
- **依次面试候选人, 如果面试的人是目前最好的, 那就雇佣他, 直到所有候选人面试完毕； 面试一个人的费用是$c_1$(每个人都要被面试), 雇佣一个人的费用是$c_2$, 求期望总雇佣花费(期望总雇佣人数)**
  - $X_i$代表第$i$个候选人被雇佣, 有
    $$P(X_i) = \frac{1}{i}$$
    - 因为前$i$个候选人中每个人出现的顺序是随机的, 最后一个人有$\frac{1}{i}$的可能性是最好的
  - 指示器随机变量, 设$I(X_i) = 1$当$X_i$发生, $I(X_i) = 0$当$X_i$不发生, 有
    $$E(I(X_i)) = P(X_i)\\
    期望总雇佣人数 = E(\sum I(X_i)) = \sum E(I(X_i)) = \sum_{i=1}^{n}\frac{1}{n} = \ln n + O(1)$$
- 所以有期望总雇佣花费$c_2*O(\ln n)$, **然而, 算法的运行时间很大程度依赖于输入的分布, 如果输入的候选人质量一直是递增的, 那么算法一直会有最坏时间复杂度! 因此考虑再算法内部将输入进行随机化**
- 生成随机输入: **任何一种输入序列的出现概率为$\frac{1}{n!}$**
  - `PERMUTE-BY-SORTING`
    - 给每个候选人一个$rank = random(1,n^3)$, 依照rank排序
    - 时间复杂度$O(nlgn)$, 因为要存储每个候选人的ranl, 因此空间复杂度$O(n)$
  - `RANDOMIZE-IN-PLACE`
    - 循环不变式:
      - 第$i$次迭代前, 任一可能的$i-1$排列出现在$A[1...n]$中的概率为$\frac{(n-i+1)!}{n!}$
    - 时间复杂度$O(n)$, 空间复杂度$0$

### 在线雇佣
- **依次面试候选人, 只雇佣一个, 每面试完一个人必须立刻给出是否雇佣**
  - 无论前$k$个候选者表现如何都不雇佣, 在$k$个之后, 如果出现比前$k$个更好的, 直接雇佣, **确定最合适的$k$, 使得雇佣到$n$个候选者中最好的概率最大**
  - 记成功雇佣到最好的候选者的事件为$X$, 记第$i$个候选人被雇佣的事件为$X_i$, 且其恰好是$n$个候选者中最好的
  $$P(X) = \sum_{i=k+1}^n P(X_i)$$
  - 记第$i$个人恰好是最佳候选者的事件为$B_i$, 则由于所有候选者以随机的顺序依次面试, 有$$P(B_i) = \frac{1}{n}$$
  - 记第$k+1\sim i-1$个候选者中没有出现比$1\sim k$中更好的候选者的事件为$C_i$, 则**等价于第$1\sim i-1$个候选者中最好的那个出现在$1\sim k$个中**, 有
  $$P(C_i) = \frac{k}{i-1}$$
  - $B_i$仅与第$i$个候选者有关, $C_i$仅与前$i-1$个候选者的排列有关, 因此两者**独立**
  $$P(X_i) = P(B_i) * P(C_i)$$
  - 于是$$P(X) = \sum_{i=k+1}^n P(X_i) = \sum_{i=k+1}^n \frac{k}{n(i-1)} = \frac{k}{n} \sum_{j=k}^{n-1} \frac{1}{j}$$
  - 计算得$$P(X) \ge \frac{k}{n}(\ln n - \ln k)$$ 对$k$求导, 最终有
  $$k = \frac{n}{e}$$ 此时有最大的下界$P(X) \ge \frac{1}{e}$

### 生日悖论
- 一年$n$天, 求$k$, 使得$k$个人中存在两个人生日概率相同的概率超过$50\%$
- 直接算:
  $$P(X) = 1 - P(k个人生日互不相同) = 1-(1 * \frac{n-1}{n} *\cdots*\frac{n-k+1}{n})\ge \frac{1}{2}$$
- 指示器随机变量:
  $$E(I(X)) = \sum_{i=1}^k\sum_{j=i+1}^k E(I(X_i))\ge 2*\frac{1}{2} = 1$$

### 球与盒子
- 把相同的球随机地扔进$b$个盒子里, 在每个盒子都有球之前, 要扔多少个球
- 定义$i$阶段: 第$i-1$个球命中了一个空箱子, 直到下一次命中空箱子(第$i$次)的期间
  - 记$X_i$为第$i$阶段投球总次数, 符合**几何分布**, 有$$E(X_i) = \frac{1}{\frac{b-i+1}{b}} = \frac{b}{b-i+1}$$
  - 最终有$$E(X) = \sum_{i=0}^bE(X_i) = b(\ln b + O(1))$$

### 拉斯维加斯算法: 识别重复元素
- 重复调用, 直到得出正确解
- 程序在任一次迭代中得到正确解并退出的概率为$\frac{\frac{n}{2}*(\frac{n}{2} - 1)}{n^2}$, 则$$n\ge 10 时 P(退出) \ge \frac{1}{5}$$ 
- 在一次迭代中代价为$O(1)$, 在前$c\alpha\lg n$次调用中占用的资源即为$c\alpha\lg n$, 有
  $$P( T(n) \leq c\alpha\lg n) \ge 1-(1 - \frac{1}{5})^{c\alpha\lg n} = 1-(\frac{1}{n})^{c\alpha \lg \frac{5}{4}} $$
令$c\ge \lg\frac{4}{5}$则有$P(T(n) \leq c\alpha\lg n) \ge 1-(\frac{1}{n})^{a}$
### 蒙特卡洛算法: 多数问题
- 重复调用, 算法返回`False`不一定是没有正确解, 算法返回`True`一定是正确解
- 返回`False`的概率$p_f < \frac{1}{2}$ (有$\frac{n}{2}$个“非多数”), $k$次迭代每一次都返回`False`的概率$p_f^k < (\frac{1}{2})^k$, 令$k=\epsilon$, 则算法返回`True`的概率$$p_t \ge 1-(\frac{1}{2})^k = 1-\epsilon$$为$1-\epsilon$正确的蒙特卡洛算法 

### 随机跳跃表