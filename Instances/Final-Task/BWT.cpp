#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<string>
#include<time.h>
#include<map>
#include<vector>
#include<utility>
#include<limits.h>
#include<algorithm>
#define DELTA 20
#define VOCAB 4
using namespace std;

struct suffix
{
    int index;
    unsigned int rank[2];
};

struct character
{
    unsigned int count;
    unsigned int start_pos;
};

string txt;
map<char,character> vocab_count;
map<char,unsigned int> vocab_idx;
unsigned int ** tally = nullptr;

int * sa = nullptr;
char * first = nullptr;
char * last = nullptr;

int myEqual(unsigned int * a, unsigned int * b, unsigned int n){
    for(unsigned int i = 0;i < n;i ++){
        if (a[i] != b[i])
        {
            return 0;
        }
    }
    return 1;
}

int getMax(unsigned int a){
    if(a > 0){
        return a - 1;
    }
    else if(a == 0){
        return 0;
    }
    else
    {
        cout<<"fuck!"<<endl;
        return -1;
    } 
}

void print(suffix array[], int n){
    for(int i = 0;i < n;i++){
        cout<<txt[i]<<":"<<array[i].index<<','<<"rank:"<<array[i].rank<<endl;
    }
}

// 计数排序
// void countSort(suffix array[], int n, int exp){
//     suffix * output = new suffix[n];
//     int i, count[11] = {0};
//     for(i = 0;i < n; i++){
//         count[(array[i].rank / exp) % 10 + 1]++;
//     }
    
//     for(i = 1;i < 11;i++){
//         count[i] += count[i - 1];
//     }
    
//     for(i = n-1;i >= 0;i--){
//         output[count[(array[i].rank / exp) % 10 + 1] - 1] = array[i];
//         count[(array[i].rank / exp) % 10 + 1]--;
//     }
//     memcpy(array,output,n*sizeof(suffix));
// }

// void radixSort(suffix array[], unsigned int n, unsigned int max){
//     for (int exp=1; max/exp > 0; exp*=10){
//         countSort(array, n, exp);
//     }
// }

int cmp(struct suffix a, struct suffix b) 
{ 
    return (a.rank[0] == b.rank[0])?(a.rank[1] < b.rank[1] ?1: 0):(a.rank[0] < b.rank[0] ?1: 0); 
} 

void buildBWT(string txt, int n){
    suffix * suffixes = new suffix[n+1];
    
    // 如果第一个字母一样, rank[0]相同；如果第二个字母一样, rank[1]相同
    for(int i = 0;i < n+1;i++){
        suffixes[i].index = i;
        suffixes[i].rank[0] = (txt[i] - '@');
        suffixes[i].rank[1] = ((i+1) < n)?(txt[i + 1] - '@'):-1;
    }
    // 每个后缀字符串按照前两个字母排序
    // radixSort(suffixes, n, 99);

    sort(suffixes, suffixes+n, cmp); 
    
    // indicator[i]代表index=i的后缀在当前permutation中的位置
    unsigned int * indicator = new unsigned int[n];

    for(unsigned int k = 4; k < 2*n; k=k*2){

        unsigned int rank = 0;
        unsigned int next_idx = 0;

        unsigned int pre_rank[2] = {suffixes[0].rank[0],suffixes[0].rank[1]};

        suffixes[0].rank[0] = rank;
        indicator[suffixes[0].index] = 0;

        for (unsigned int i = 1;i < n;i++){
            // 将前k/2个字符的比较结果放在一位表示, 如果两个后缀字符串前k/2个字符相同, 则rank[0]相同
            if(myEqual(suffixes[i].rank, pre_rank, 2)){
                pre_rank[0] = suffixes[i].rank[0];
                pre_rank[1] = suffixes[i].rank[1];

                suffixes[i].rank[0] = rank;
            }
            else{
                pre_rank[0] = suffixes[i].rank[0];
                pre_rank[1] = suffixes[i].rank[1];

                suffixes[i].rank[0] = (++rank);
            }

            indicator[suffixes[i].index] = i;
        }

        // print(suffixes,n);
        for(int i = 0;i < n;i++){
            next_idx = suffixes[i].index + k/2;
            // 从next_idx开始的后缀字符串就是当前后缀字符串往后k/2个字符后的字符串, 这个子字符串已经被上一步比较过了, 因此直接拿来用
            suffixes[i].rank[1] = (next_idx < n) ? (suffixes[indicator[next_idx]].rank[0]) : -1;
        }

        // print(suffixes, n);

        // radixSort(suffixes, n, rank);
        sort(suffixes, suffixes+n, cmp);

        // print(suffixes, n);
    }

    // print(suffixes,n);
   
    char *F = new char[n+1];
    char *L = new char[n+1];
    int * SA = new int[n+1];

    for(int i = 0;i < n;i++){
        SA[i] = suffixes[i].index; 
        L[i] = (suffixes[i].index > 0) ? txt[suffixes[i].index - 1] : '@';
        F[i] = txt[suffixes[i].index];

        if(F[i] != '@'){

            vocab_count[F[i]].count ++;
            if(vocab_idx.find(F[i]) == vocab_idx.end()){
                vocab_idx[F[i]] = vocab_idx.size();
            }
        }
    }
    auto iter = vocab_count.begin();
    auto pre_iter = iter;
    iter->second.start_pos = 1;
    iter++;
    
    for(iter;iter!=vocab_count.end();iter++,pre_iter++){
        iter->second.start_pos = pre_iter->second.start_pos + pre_iter->second.count;
    }

    // 输出单词表
    cout<<"the vocabulary in string is :"<<endl;
    for(auto i = vocab_count.begin();i != vocab_count.end();i++){
        cout<<i->first<<','<<i->second.start_pos<<'-'<<i->second.count<<endl;
    }

    delete [] suffixes;

    first = F;
    last = L;
    sa = SA;

    // 输出F,L和SA
    ofstream fout("D:/Data/Class_data/Alg_data/FinalTask/debug.txt");
    for(int i = 0;i < n; i++){
        fout<<first[i]<<','<<last[i]<<','<<sa[i]<<endl;
    }
    fout.close();
}

void getTally(char * first, char * last, int n){
    tally = new unsigned int * [static_cast<unsigned int>(n/DELTA) + 1];
    
    unsigned int idx = 0;
    unsigned int * cnt_row = new unsigned int [VOCAB];
    for(int i = 0;i < VOCAB;i++){
        cnt_row[i] = 0;
    }

    // 输出第一行
    // for(auto iter = cnt_row.begin();iter != cnt_row.end();iter++){
    //     cout<<*iter;
    // }
    
    for(unsigned int i = 0;i < n;i++){
        // if(first[i] != '@'){            
        //     cnt_row[vocab_idx[first[i]]] ++;
        // }

        if(last[i] != '@'){
            cnt_row[vocab_idx[last[i]]] ++;
        }
        if(i % DELTA == 0){
            // 输出上一行
            // for(int j = 0;j < VOCAB;j++){
            //     cout<<cnt_row[j]<<'.';
            // }
            // cout<<endl;
            // cout<<idx;
            tally[idx] = cnt_row;

            cnt_row = new unsigned int [VOCAB];
            for(int j = 0;j < VOCAB;j++){
                cnt_row[j] = tally[idx][j];
            }
            idx++;
            // for(int j = 0;j < VOCAB;j++){
            //     cout<<j;
            // }
        }
    }
    if((n-1) % DELTA){
        tally[idx++] = cnt_row;
    }

    // 输出tally数组
    // for(int i = 0;i<idx;i++){
    //     for(int j = 0;j < VOCAB;j++){
    //         cout<<tally[i][j]<<',';
    //     }
    //     cout<<endl;
    // }
}

void query(string query){
    int k = query.length();
    clock_t t_1 = clock();
    for(int i = 0;i < k;i++){
        if(!vocab_count[query[i]].count){
            cout<<"NO MATCHING!"<<endl;
            return;
        }
    }
    // rank是在F中query的某个字母的rank范围
    unsigned int rank[2] = {0,vocab_count[query[k-1]].count - 1};
    // index是在L(tally)中query的某个字母的范围
    unsigned int index[2] = {0};
    unsigned int base[2] = {0};

    // 查checkpoint时记录中间路径上有几个查询字母；
    int offset = 0;

    char cnt = '\0';
    char pre = '\0';

    for(int i = k - 1;i >= 0;i --){
        // int start = vocab_count[query[i]];
        cnt = query[i];
        index[0] = vocab_count[cnt].start_pos + rank[0];
        index[1] = vocab_count[cnt].start_pos + rank[1];
        
        // 如果没结束, 再接着找前一个, 即当前字母cnt的前一个字母pre所在的L中的位置
        if(i > 0){
            pre = query[i-1];
            base[0] = index[0]/DELTA;
            base[1] = index[1]/DELTA;

            // 所求字母的给定index范围内的tally表的上一行的值 == 其rank的下界
            if(index[0] % DELTA == 0){
                if(last[index[0]] == pre){
                    rank[0] = tally[base[0]][vocab_idx[pre]] - 1;
                }
                else{
                    rank[0] = tally[base[0]][vocab_idx[pre]];
                }
            }
            //不管当前index到底是不是pre, 都不影响截止到index的pre的rank
            else if(index[0] % DELTA >= DELTA/2){ 
                for(int l = index[0] % DELTA;l <= DELTA;l++){
                    if(last[base[0]*DELTA + l] == pre){
                        offset ++;
                    }
                }
                // if(last[index[0]] == pre){
                //     rank[0] = tally[base[0] + 1][vocab_idx[pre]] - offset - 1;
                // }
                // else{
                //     rank[0] = tally[base[0] + 1][vocab_idx[pre]] - offset;
                // }
                rank[0] = tally[base[0] + 1][vocab_idx[pre]] - offset;
            }
            // 不需要管检查点到底是什么
            else{
                for(int l = 1;l < (index[0] % DELTA);l++){
                    if(last[base[0]*DELTA + l] == pre){
                        offset ++;
                    }
                }
                // if(last[index[0]] == pre){
                //     rank[0] = tally[base[0]][vocab_idx[pre]] + offset - 1;
                // }
                // else{
                //     rank[0] = tally[base[0]][vocab_idx[pre]] + offset;
                // }
                rank[0] = tally[base[0]][vocab_idx[pre]] + offset;
            }

            offset = 0;

            // 所求字母的给定index范围内的tally表的最后一行的值 == 其rank的上届
            if(index[1] % DELTA == 0){
                if(last[index[1]] == pre){
                    rank[1] = tally[base[1]][vocab_idx[pre]] - 1;
                }
                else{
                    rank[1] = tally[base[1]][vocab_idx[pre]];
                }
            }

            else if(index[1] % DELTA >= DELTA/2){
                for(int l = index[1] % DELTA + 1;l <= DELTA;l++){
                    if(last[base[1]*DELTA + l] == pre){
                        offset ++;
                    }
                }
                // if(last[index[1]] == pre){
                //     rank[1] = tally[base[1] + 1][vocab_idx[pre]] - offset - 1;
                // }
                // else{
                //     rank[1] = tally[base[1] + 1][vocab_idx[pre]] - offset;
                // }
                rank[1] = tally[base[1] + 1][vocab_idx[pre]] - offset - 1;

            }
            // 不需要管检查点到底是什么
            else{
                for(int l = 1;l <= (index[1] % DELTA);l++){
                    if(last[base[1]*DELTA + l] == pre){
                        offset ++;
                    }
                }
                // if(last[index[1]] == pre){
                //     rank[1] = tally[base[1]][vocab_idx[pre]] + offset - 1;
                // }
                // else{
                //     rank[1] = tally[base[1]][vocab_idx[pre]] + offset;
                // }
                rank[1] = tally[base[1]][vocab_idx[pre]] + offset - 1;
            }

            offset = 0;

            // rank[0] = tally[index[0] - 1][vocab_idx[pre]];
            // rank[1] = tally[index[1]][vocab_idx[pre]] - 1;

            if(rank[1] < rank[0]){
                cout<<"NO MATCHING!"<<endl;
                return;
            }
        }
    }

    clock_t t_2 = clock();
    // cout<<index[0]<<index[1]<<endl;
    int start = 0;
    ofstream fout("results.txt");

    cout<<"There are "<<index[1] - index[0] + 1<< " Results:"<<endl;
    cout<<"query time consumed: "<< (t_2-t_1)/CLOCKS_PER_SEC <<endl;
    cout<<"writing to results..."<<endl;
    for(int i = index[0];i <= index[1];i ++){
        start = sa[i];
        fout<<start<<":";
        if(k > 100){
            for(int j = 0;j < 100;j ++){
                fout<<txt[start+j];
            }
            fout<<"...";
        }
        else
        {
            for(int j = 0;j < k;j ++){
                fout<<txt[start+j];
            }
        }
        fout<<endl;
    }
    fout.close();
    cout<<"writing accomplished!"<<endl;
}



int main(){
    string file_path;
    cout << "input file directory of Long String:"<<endl;
    cin >> file_path;

    cout<<"reading file..."<<endl;
    ifstream fin(file_path);
    fin>>txt;
    fin.close();
    
    txt += '@';
    int n = txt.length();

    cout<<"reading accomplished"<<endl;
    cout<<"Long String length is: "<<txt.length()<<endl;
    
    cout<<"constructing Suffix Array(sorted)..."<<endl;
    clock_t t_1 = clock();
    
    buildBWT(txt,n);
    // fout.close();

    // 输出后缀数组, F和L
    // for(int i = 0;i < n;i++){
    //     cout<<first[i]<<','<<last[i]<<','<<sa[i]<<endl;
    // }

    getTally(first,last,n);

    clock_t t_2 = clock();
    cout<< "construction time consumed:" << float(t_2-t_1)/CLOCKS_PER_SEC << endl;
    
    while(1){
        string q;
        string path;
        cout<<"input query file..."<<endl;
        cin>> path;

        fin.open(path);

        cout<<"reading query..."<<endl;
        fin>>q;
        fin.close();
        cout<<"reading accomplished! query length is "<<q.size()<<"!"<<endl;
        
        if(q == "exit") break;
        transform(q.begin(),q.end(),q.begin(),::toupper);

        query(q);
    }
    
    return 0;
}

/* 
    char * a = (char*)malloc(8);
    char * c = (char*)malloc(8);
    // a[0] = 'a';
    // a[1] = 'b';
    strcpy(a,"rbcrabb");
    strcpy(c,"rbcaaaa");

    unsigned long long *b = ((unsigned long long *)a);
    unsigned long long *d = ((unsigned long long *)c);
    
    // printf("%p,%c\n",a,a[0]);
    // printf("%p,%c\n",&a[1],a[1]);
    cout<<*b<<endl;
    printf("%d,%d",sizeof(long long),sizeof(char));
    printf("%s,%s\n",a,c);
    printf("%p,%llx\n",b,*b);
    printf("%p,%llx",d,*d); 
*/