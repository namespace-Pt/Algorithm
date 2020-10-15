'''
    Given Initial Node and Destination Node, compute one path,all possible paths,all loops between them,
    each of the result paths contains no duplicated nodes 

    Using Stack
'''

from utils import Node
from utils import adjacency_multipath as adjacency

# only maintain stack within a loop
# can find one path from init to dest
# can find all paths only if maintain a list in which stores the previous traversed neighbors for each node
def dfs(path_stack,nodes,init,dest):
    node_ini = nodes[init]
    node_ini.traversed = True
    path_stack.append(node_ini)

    while path_stack:
        available = False
        top = path_stack[-1]
        for neighbor in adjacency[top.id]:

            if not nodes[neighbor].traversed:
                nodes[neighbor].traversed = True
                path_stack.append(nodes[neighbor])

                available = True
                if neighbor == dest:
                    paths.append(path_stack.copy())
                    tmp = path_stack.pop()
                    tmp.traversed = False
                    
                break
        if not available:
            tmp = path_stack.pop()

# call dfs recursively
# can find all paths from init to dest
# the order to traverse the neighbor of the current node natually follow the order defined in adjacency,
# thus we don't need to care about which node is contained in the current path and which node has been traversed in one of the previous path
def dfs_recur(path_stack,nodes,init,dest):
    node = nodes[init]
    # if reach destination
    # append the current path into the available path collection
    if init == dest:
        path_stack.append(node)
        paths.append(path_stack.copy())
        return

    # traversed the current node
    # append it into our path
    node.traversed = True
    path_stack.append(node)

    for neighbor in adjacency[init]:
        # pre-judge whether this neighbor node has been traversed
        # so that we don't need to add the second boundary condition

        if nodes[neighbor].traversed:
            continue
        
        # recursive
        dfs_recur(path_stack,nodes,neighbor,dest)
        # maintain a stack where the current path is stocked
        tmp = path_stack.pop()
        tmp.traversed = False

    # when function ends, it natually returns
    return

# recursive call dfs
# can find all loops from init to dest
def dfs_recur_circle(path_stack,nodes,init,dest):
    node = nodes[init]
    # if reach destination
    # append the current path into the available path collection
    if init == dest:
        path_stack.append(node)
        paths.append(path_stack.copy())

        # enconter init node for the second time
        # break
        if len(path_stack) > 1:
            return
        
        path_stack.pop()
    
    # traverse the current node
    # append it into our path
    node.traversed = True
    path_stack.append(node)

    for neighbor in adjacency[init]:
        # pre-judge whether this neighbor node has been traversed
        # so that we don't need to add the second boundary condition
        if neighbor == dest and path_stack[-2].id != dest:
            nodes[neighbor].traversed = False

        if nodes[neighbor].traversed:
            continue
        
        # recursive
        dfs_recur_circle(path_stack,nodes,neighbor,dest)
        # maintain a stack where the current path is stocked
        tmp = path_stack.pop()
        tmp.traversed = False

        # the dest node is always in the stack so only when it's encounterd again shall its traversed-state change to False
        if tmp.id == dest:
            tmp.traversed = True

if __name__ == "__main__":
    nodes = [Node(0),Node(1),Node(2),Node(3),Node(4),Node(5)]
    
    # collection of paths
    paths = []
    
    # discerning whether the 2nd node can connect to the 4th node
    # print(dfs(nodes[4],0))
    path_stack = []

    # three different funciton based on dfs

    # dfs(path_stack,nodes,0,5)
    # dfs_recur(path_stack,nodes,0,5)
    dfs_recur_circle(path_stack,nodes,1,1)
    print(paths)