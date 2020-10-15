# 没写完

from utils import State,G1,G2
import networkx

# define data structure for isomorphism
# according to VF2
core_1 = [0]*len(G1)
core_2 = [0]*len(G2)

in_1 = [0]*len(G1)
in_2 = [0]*len(G2)

out_1 = [0]*len(G1)
out_2 = [0]*len(G2)

def pred(s,n,m):
    judge1 = False
    judge2 = False

    for n_1 in s.M1:
        # pred(n)
        if n in [x for x in G1[n] if x == -1]:
            for m_1 in [x for x in G2[m] if x == -1]:
                if m_1 in s.M2:
                    judge1 = True
                else:
                    judge1 = False
    

def match(s):
    if len(s.M) == len(G1):
        print(s.M)
    else:
        """
        compute candidte states 
        """
        for p in P:
            # compute state s' obtained by adding p into s
            match(s_next)
        