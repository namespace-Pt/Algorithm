path_save = r'D:\Data\Class_data\Alg_data\FinalTask\l_1.txt'
path = r'D:\Data\Class_data\Alg_data\FinalTask\F.txt'

with open(path,'r',encoding='utf-8',errors='ignore') as f:
    string = ''
    # for line in f:    
    #         string += line.strip()
        # except:
            # continue
    string = f.read()

    print(len(string))

g = open(path_save,'w')
g.write(string)
g.close()