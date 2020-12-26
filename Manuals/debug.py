import math
key = ['','do','if','read','while']
p = [0,3,3,1,1]
q = [2,3,1,1,1]
n = len(p) - 1
Estimate = []
Cost = []
Root = []

for i in range(n+2):
    Estimate.append([math.inf]*(n+1))
    Cost.append([0]*(n+1))
for i in range(n+1):
    Root.append([0]*(n+1))

# 初始化
for i in range(n+1):
    Estimate[i+1][i] = q[i]
    Cost[i+1][i] = q[i]

# l = 1 is not ordinary
for l in range(1,n+1):
    for i in range(1,n-l+2):
        j = i + l
        Cost[i][j-1] = Cost[i][j-2] + p[j-1] + q[j-1]
        for k in range(i,j):
            tmp = Estimate[i][k-1] + Estimate[k+1][j-1] + Cost[i][j-1]
            if tmp < Estimate[i][j-1]:
                Estimate[i][j-1] = tmp
                Root[i][j-1] = k

def printBST(Root,i,j):
    if i == j+1:
        return
    else:
        r = Root[i][j]
        print(key[r])

        printBST(Root,i,r-1)
        printBST(Root,i+1,j)

printBST(Root,1,n)