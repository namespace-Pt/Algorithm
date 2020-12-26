'''
Author: Pt
Date: 2020-11-16 16:05:24
LastEditTime: 2020-11-17 17:32:02
Description: implement BWT and FM index to match string of length m in string of length n, with time comlexity of O(m)
'''
from collections import defaultdict

def get_bw_suffix_matrix(string):
    """ get bw suffix matrix, store character number on right to $ for each row with fixed interval
    O(n^2)

    """
    temp = string*2
    BW_matrix = []
    for i in reversed(range(0,len(string))):
        # if not i % 2:
        #     row = [i]
        # else:
        #     row = [None]
        row = [i]
        _string = ''
        for j in range(i,i+len(string)):
            if string[j] == '$':
                _string += '$'
                break
            _string += string[j]

        row.append(_string)
        BW_matrix.append(row)
    return BW_matrix

def sortCriterion(row):
    return row[1]

def get_first_last_col(BW_matrix_suffix,string):
    """ get the first and last row in BW_matrix_suffix, however
    O(n)
    """
    F = ''
    L = ''
    for row in BW_matrix_suffix:
        F += row[1][0]
        L += string[row[0] -1]
    return F,L

def get_char_occurance(F):
    """ get char_occurance, which indicates the first row index corresponding to character, and char_dict, which map character into interger
    O(n)
    """
    F += ' '
    char_occurance = defaultdict(list)
    char_dict = {}
    pre = ' '
    count = 0
    for char in F:
        if pre == char:
            count += 1
            continue
        else:
            if pre != ' ':
                char_occurance[pre].append(count)
            if char != ' ':
                char_occurance[char].append(count)
                char_dict[char] = len(char_dict)
            pre = char
            count += 1
    return char_occurance,char_dict

def get_tally(L,char_dict):
    """ get tally which indicates character index in the last column
    """
    tally = []
    pre_row = [0] * len(char_dict)
    for char in L:
        pre_row[char_dict[char]] += 1
        tally.append(pre_row.copy())
    return tally

def query_F(F,query,char_occurance,rank=None):
    """ query the first column to find query character within rank( if given )

    Args:
        rank: tuple of the rank of the query character, default is None
    
    Returns:
        index_interval: tuple of the indexes corresponding to the query within rank( if given )
    """
    if rank:
        return [char_occurance[query][0] + rank[0], char_occurance[query][0] + rank[1] + 1]
    return char_occurance[query]

def query_L(L,query,tally,index,char_dict):
    """ query the last column to find query vector within given index
    
    Args:
        index: tuple of the index interval in which to find the query character in tally
    
    Returns:
        rank_interval: tuple of the ranks corresponding to the query within index
    """
    try:
        query_index = char_dict[query]
        rank_start = tally[index[0] - 1][query_index]
        rank_end = tally[index[1] - 1][query_index]
        # row_start = tally[index[0]][query_index]
        # row_end = tally[index[1] - 1][query_index]
    except:
        print("No Matching!")
        return None
    # important to subtract 1 because offset between counting of query in tally and rank of query is natually 1
    return [rank_start,rank_end - 1]

def query(F,L,query_string,char_dict,char_occurance,tally):
    """ query the substring in string
    """
    indicator = len(query_string) - 1
    rank_query = None
    to_F = True
    to_L = False
    while indicator >= 0:
        query = query_string[indicator]
        if to_F:
            index_query = query_F(F,query,char_occurance,rank_query)
            indicator -= 1

            to_F = False
            to_L = True
            continue
        if to_L:
            rank_query = query_L(L,query,tally,index_query,char_dict)
            
            if not rank_query:
                return None

            to_F = True
            to_L = False
            continue

    return index_query

def get_index_of_origin_string(string,index_query,BW_matrix_suffix):
    """ derive starting index list of substring
    """
    indexes_origin_string = []
    for indicator in range(index_query[0],index_query[1]):
        suffix = BW_matrix_suffix[indicator][0]
        if suffix is not None:
            indexes_origin_string.append(suffix)
    return indexes_origin_string


if __name__ == "__main__":
    # string = input('string: ')
    x = input('substring: ')
    
    f = open(r'D:\Data\Class_data\Alg_data\gene_10000.txt','r',encoding='utf-8')
    string = f.read()
    string += '$'

    BW_matrix_suffix = get_bw_suffix_matrix(string)
    BW_matrix_suffix.sort(key=sortCriterion)
    print('fuck')
    
    F,L = get_first_last_col(BW_matrix_suffix,string)
    
    char_occurance,char_dict = get_char_occurance(F)
    
    tally = get_tally(L,char_dict)


    index_query = query(F,L,x,char_dict,char_occurance,tally)
    
    indexes_origin_string = get_index_of_origin_string(string,index_query,BW_matrix_suffix)

    print(indexes_origin_string)