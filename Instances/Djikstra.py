'''
Author: Pt
Date: 2020-11-19 15:07:18
LastEditTime: 2020-11-19 20:42:53
Description: 
'''
import math
from collections import deque

inf = math.inf
adj_matrix = []

n = 5
for i in range(5):
    adj_matrix.append([inf] * 5)
    adj_matrix[i][i] = 0

adj_matrix[0][1] = 10
adj_matrix[0][4] = 100
adj_matrix[0][3] = 30
adj_matrix[1][2] = 50
adj_matrix[2][4] = 10
adj_matrix[3][2] = 20
adj_matrix[3][4] = 60

def djikstra(start,adj_matrix,n):
    traversed = [0] * n
    distance = [inf] * n
    path = [-1] * n

    # traversed[start] = 1

    for i in range(n):
        distance[i] = adj_matrix[start][i]

    # 每一次都会有一个新的顶并到集合S中，在程序里表现为traversed[i] = 1
    for i in range(n):
        _min = inf
        for j in range(n):
            if distance[j] < _min and traversed[j] != 1:
                _min = distance[j]
                _min_idx = j
        
        traversed[_min_idx] = 1

        for j in range(n):
            if distance[j] > _min + adj_matrix[_min_idx][j]:
                distance[j] = _min + adj_matrix[_min_idx][j]
                path[j] = _min_idx
    return distance,path
    
def backtracking(path,start,end):
    stack = deque()
    step = path[end - 1]
    # if step == -1:
    #     stack.append(start)

    stack.append(end)
    
    while step != -1:
        stack.append(step + 1)
        step = path[step]

    stack.append(start)

    while stack:
        print(stack.pop(),end='')


distance,path = djikstra(0,adj_matrix,n)

print("distance is:{}".format(distance))
for i in range(1,6):
    print("path from 1 to {} is:".format(i))
    backtracking(path,1,i)
    print()