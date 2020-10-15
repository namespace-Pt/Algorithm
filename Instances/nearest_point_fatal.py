import math
import csv

# 根据讲义定义函数
def cpair2(s,length):

    # 如果分治后得到的一边仅有一个点，那么将其距离设置为正无穷，这样默认在合并两边区域的时候进行计算其和另一边点之间的距离
    # O(1)
    if length < 2:
        return math.inf
    
    # 这里的mid_x可以用中位数
    # O(1)
    mid_x = s[int(length/2)][0]
    
    # 这里的逻辑不能用横坐标小于mid_x的点作为集合s1，大于等于的点作为集合s2
    # 因为有可能超过半数的点的坐标相同，这样的话中位数恒为该定值，那么在分治时无法将当前s分为两半
    # 因为横坐标小于等于mid_x的点会被归到一边，造成死循环
    # O(1)，c++等可以用memcpy做
    s1 = s[0:int(length/2)]      #[x for x in s if x[0]<= mid_x]
    s2 = s[int(length/2):]       #[x for x in s if x[0] > mid_x]

    # 分治
    # T(n/2) * 2
    d1 = cpair2(s1,int(length/2))
    d2 = cpair2(s2,length-int(length/2))

    # O(1)
    dm = min(d1,d2)

    # 将s1中抽取距离中线一个dm内的点作为候选集
    # s2同理
    # O(n)
    p1 = [x for x in s1 if 0<= mid_x - x[0] < dm]
    p2 = [x for x in s2 if 0<= x[0] - mid_x < dm]
    
    # 将候选集中的点按纵坐标排序
    # p1可以不进行排序，但是这样会隐性扩大y的搜索范围，如果排序后y的搜索区间重叠最小
    # O(nlgn)
    p1.sort(key=lambda x: x[1])
    p2.sort(key=lambda x: x[1])

    # 没必要保存dl=dm，节省空间
    for x in p1:
        for y in p2:
            # 如果y的指针范围超过2dm，就跳出
            if y[1] - x[1] > dm:
                break
            elif x[1] - y[1] > dm:
                break
            
            # 保存临时距离
            tmp = math.sqrt(pow(y[0]-x[0],2) + pow(y[1] - x[1],2))
            # 更新最小值
            if tmp < dm:
                dm = tmp

    return dm

if __name__ == "__main__":
    f = open(r'D:\Data\Class_data\Alg_data\lab1_points.csv',encoding='utf-8-sig')
    s = []
    for line in csv.reader(f):
        s.append((int(line[0]),int(line[1])))

    #s = [(0,0),(1,3),(2,1),(4,-2),(-1,5)]
    #s.sort(key=lambda x: x[0])
    print(cpair2(s,len(s)))
