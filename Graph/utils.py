# adjacency matrix
# recording neighbors of each node


# multi-path
adjacency_multipath = {
    0:[1],
    1:[0,2,3,4],
    2:[1,4],
    3:[1,4],
    4:[1,2,3,5],
    5:[4],
    6:None
}

# circle
adjacency_circle = {
    0:[1,3,4],
    1:[0,2,4],
    2:[1,3],
    3:[0,2],
    4:[0,1]
}


# adjancency matrix
import numpy
G1 = numpy.array([
    [0,1,0,-1],
    [-1,0,1,0],
    [0,-1,0,1],
    [1,0,-1,0]
])

G2 = numpy.array([
    [1,0,-1,0],
    [-1,0,1,0],
    [0,1,0,-1],
    [0,-1,0,1]
])

# define node
# id is to distinguish between different node, corresponding to adjacency matrix
class Node():
    def __init__(self,id):
        self.traversed = False
        self.id = id
        self.layer = -1
    def __repr__(self):
        return 'id:{}'.format(self.id)
    def setLayer(self,layer):
        if self.layer == -1:
            self.layer = layer


# define state used in VF2
class State:
    def __init__(self):
        # Mapping Matrix M comprises of node pairs (n,m)
        # n \in G1, m \in G2
        self.M = []
        self.M1 = [x[0] for x in self.M]
        self.M2 = [x[1] for x in self.M]