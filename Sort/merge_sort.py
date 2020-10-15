# Devide-and-Conquer
# different logic with c++, using objects' reference rather than pointers, return reference to keep the changes

def merge(left,right):
    seq_temp = []
    idx_l = 0
    idx_r = 0
    len_l = len(left)
    len_r = len(right)

    # use METHOD:Append to construct the temporary ordered sequence 
    while idx_l < len_l and idx_r < len_r:
        if left[idx_l] < right[idx_r]:
            seq_temp.append(left[idx_l])
            idx_l += 1
        else:
            seq_temp.append(right[idx_r])
            idx_r += 1
    
    if idx_l < len_l:
        seq_temp += left[idx_l:]
    elif idx_r < len_r:
        seq_temp += right[idx_r:]
    
    # return it recursively
    return seq_temp

def merge_sort(seq):
    # boundary conditions
    # when length of the sequence is less than 1, it means the sequence is one element and it is natually ordered
    if len(seq) <= 1:
        return seq

    mid = int(len(seq)/2)

    # using reference
    left = merge_sort(seq[:mid])
    right = merge_sort(seq[mid:])
    return merge(left,right)

if __name__ == "__main__":
    seq = [1123,23,12111,-10,-1120]
    seq = merge_sort(seq)
    print(seq)