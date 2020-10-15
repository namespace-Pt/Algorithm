"""
    Given Initial Node and Destination Node, using BFS to determine whether there's a possible path between them,
    finding odd circle in the graph

    Using Queue
"""

from utils import Node
from utils import adjacency_multipath as adjacency
from collections import deque as queue

# maintain queue within a loop
# determine whether there's a path between init node and dest node
def bfs(queue,nodes,init,dest):
    layer = 0

    node = nodes[init]
    node.traversed = True
    queue.append(node)
    
    while queue:
        cnt = queue.popleft()
        layer += 1
        for neighbor in adjacency[cnt.id]:
            if neighbor == dest:
                return True
            if not nodes[neighbor].traversed:
                nodes[neighbor].traversed = True
                queue.append(nodes[neighbor])
    return False

# call bfs recursively
# determine whether there's a path between init node and dest node
def bfs_recur(queue,nodes,init,dest):
    node = nodes[init]
    if init == dest:
        return True
    
    # if node.traversed:
        # return False

    # change the status of the current node
    node.traversed = True

    # append all neighbor of the current node into queue
    for neighbor in adjacency[init]:
        neighborNode = nodes[neighbor]
        if neighborNode.traversed:
            continue
        
        # changing status of the node because when it's in the queue, it will be traversed at last
        neighborNode.traversed = True
        queue.append(neighborNode)
    
    # call bfs for all nodes in the queue
    while queue:
        node = queue.popleft()

        # must Return before the end of the function
        if(bfs_recur(queue,nodes,node.id,dest)):
            return True
    
    return False

# maintain queue within a loop
# determine whether there's an odd circle
def bfs_OddC(queue,nodes):
    for node in nodes:
        layer = 0
        if node.traversed:
            continue
    
        node.traversed = True
        node.setLayer(layer)
        queue.append(node)
        
        while queue:
            cnt = queue.popleft()
            layer += 1
            for neighbor in adjacency[cnt.id]:
                
                nodes[neighbor].setLayer(layer)
                if nodes[neighbor].layer == cnt.layer:
                    print("Odd Circle Found!")
                    return
                    
                if not nodes[neighbor].traversed:
                    nodes[neighbor].traversed = True
                    queue.append(nodes[neighbor])

    print("No Odd Circle Found!")          
    return

if __name__ == "__main__":
    nodes = [Node(0),Node(1),Node(2),Node(3),Node(4),Node(5),Node(6)]
    paths = []
    myqueue = queue()
    # print(bfs(myqueue,nodes,0,4))
    bfs_OddC(myqueue,nodes)