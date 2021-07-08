import math

def _append(dest,node):
    """
    将node节点添加到dest节点左边
    """
    if not dest:
        print("dest is empty!")

    target = dest.left
    dest.left = node
    node.right = dest

    target.right = node
    node.left = target

def _concat(node1,node2):
    if not node1:
        print("node #1 empty!")
    if not node2:
        print("node #2 empty!")

    left_1 = node1.left
    left_2 = node2.left

    node1.left = left_2
    left_2.right = node1
    
    node2.left = left_1
    left_1.right = node2

def _delete(node):
    if not node:
        print("node is empty!")
    left_node = node.left
    right_node = node.right
    left_node.right = right_node
    right_node.left = left_node

    # node.left = None
    # node.right = None

def _link(y, x):
    """
    从根链表删除y, 把y加入x的孩子链表, x的度数+1且y的标志记为False
    """
    _delete(y)
    if x.cld:
        _append(x.cld,y)
    else:
        # y.left = y
        # y.right = y
        x.cld = y
    x.degree += 1
    y.mark = False

class Node:
    def __init__(self, key=0, pnt=None, cld=None, degree=0, mark=False):
        self.key = key
        # self.value = 0
        self.pnt = pnt
        self.cld = cld
        self.left = self
        self.right = self
        self.degree = degree
        self.mark = mark

    def __repr__(self):
        return str("key:{}, left:{}, right:{}".format(self.key,self.left.key,self.right.key))

class Fibonacci_Heap():
    def __init__(self):
        self.min = None
        self.n = 0

    def _union(self,H2):
        H = Fibonacci_Heap()
        H.min = self.min
        # 两者链表合并
        _concat(H.min, H2.min)

        if self.min == None or (H2.min != None and H2.min.key < self.min.key):
            H.min = H2.mind
        
        H.n = self.n + H2.min
        return H
    
    def insert(self,x):
        x.degree = 0
        x.pnt = None
        x.cld = None
        x.mark = False
        if not self.min:
            x.left = x
            x.right = x
            self.min = x
        
        else:
            """
            加入到链表里, 放在min节点的左边, 根链表中节点次序是任意的, 所以直接加到最小节点的左边
            """
            _append(self.min,x)

            if x.key < self.min.key:
                self.min = x
        self.n += 1
    
    def extractMin(self):
        ptr = self.min
        if ptr:
            if ptr.cld:
                cld = ptr.cld
                start = cld

                while 1:
                    cld.prn = None
                    next_cld = cld.left

                    # ptr.left == ptr怎么办？
                    # 试了一下是没有影响的
                    _append(ptr.left,cld)
                    cld = next_cld
                    if cld == start:
                        break

                # _concat(ptr.left,ptr.cld)
                
            # 从根链表中删除ptr
            _delete(ptr)

            if ptr == ptr.right:
                self.min = None
            else:
                # 这里是随便指的
                self.min = ptr.right

                self._consolidate()

            self.n -= 1
        return ptr
    
    def _consolidate(self):
        A = [None] * int(math.log(self.n) + 1)
        
        start = self.min
        iterator = start
        while 1:
            degree = iterator.degree
            
            next_node = iterator.left
            
            while A[degree]:
                another = A[degree]
                
                if iterator.key > another.key:
                    iterator, another = another,iterator

                _link(another,iterator)

                A[degree] = None
                degree += 1
            
            A[degree] = iterator
            
            iterator = next_node
            if iterator == start:
                break
        
        self.min = None
        
        for node in A:
            if node:
                if self.min == None:
                    node.left = node
                    node.right = node
                    self.min = node
                else:
                    _append(self.min,node)
                    if node.key < self.min.key:
                        self.min = node