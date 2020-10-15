def insert_sort(seq):
    idx = 1
    while idx < len(seq):
        var = seq[idx]
        idx_s = idx - 1
        while(seq[idx_s] > var and idx_s >= 0):
            seq[idx_s + 1] = seq[idx_s]
            idx_s -= 1
        seq[idx_s + 1] = var
        idx += 1

if __name__ == "__main__":
    seq = [12,3213,-99,213,8]
    insert_sort(seq)
    print(seq)
            
