#include <bits/stdc++.h>
using namespace std;

// ./spj input user_out answer score judge_message
ifstream input     ; // 题目的输入文件
ifstream output    ; // 用户输出

void spoj_assert (bool f, const char *s) {
    if (!f) throw s ;
}

void judge () {
    int T, n, m ;
    input >> T >> n >> m ;
    int c[n+2];
    for(int i=0;i<n+2;i++)
        input >> c[i] ;
    int d[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            input >> d[i][j] ;
    int b[n][m];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            input >> b[i][j] ;
    int x, y;
    output >> x >> y ;
    spoj_assert (x>=0 and x<=n, "x out of range.");
    spoj_assert (y>=0 and y<=1048576, "too many operations.") ;
    for(int i=0;i<x;i++)
    {
        int a;
        output >> a ;
        spoj_assert (a>=1 and a<=n, "out of range.") ;
        a-- ;
        reverse(b[a],b[a]+m);
    }
    stack<int> tubes[n+2];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            tubes[i].push(b[i][j]-1);
    int capacity[n+2];
    for(int i=0;i<n+2;i++)
        capacity[i]=m;
    long long curScore=0;
    for(int i=0;i<y;i++)
    {
        int type;
        output >> type ;
        spoj_assert (type==1 or type==2, "operation type error.") ;
        if(type==1)
        {
            int p,q;
            output >> p >> q ;
            spoj_assert(p!=q, "P and Q are the same tube.");
            spoj_assert(p>=1 and p<=n+2, "out of range.");
            spoj_assert(q>=1 and q<=n+2, "out of range.");
            p--,q--;
            spoj_assert(!tubes[p].empty(), "P is empty.");
            spoj_assert(tubes[q].size()<capacity[q], "Q is full.");
            int u=tubes[p].top();
            if(tubes[q].empty())
                curScore+=0;
            else
            {
                int v=tubes[q].top();
                spoj_assert(d[u][v]!=-1, "invalid operation.");
                curScore+=d[u][v];
            }
            tubes[q].push(u);
            tubes[p].pop();
        }
        else
        {
            int p;
            output >> p ;
            spoj_assert(p>=1 and p<=n+2, "out of range.");
            p--;
            capacity[p]++;
            curScore+=c[p];
        }
    }
    for(int i=0;i<n+2;i++)
    {
        if(!tubes[i].empty())
        {
            spoj_assert(tubes[i].size()==m, "wrong answer.");
            int u=tubes[i].top();
            while(!tubes[i].empty())
            {
                int v=tubes[i].top();
                spoj_assert(u==v, "wrong answer.");
                tubes[i].pop();
            }
        }
    }
    // score << max (0.0, 1.0 - (double) curScore / 67108864) ;
    printf("total cost: %lld score: %lld\n", curScore, 67108864 - curScore) ;
}

int main(int argc, char * argv[]) {
    
    try {
        input .open (argv[1]); // 题目的输入文件
        output    .open(argv[2]); // 用户输出

        // fscanf , fprintf
        try {
            judge () ;
        } catch (const char *s) {
            printf("%s\n", s) ;
        }

        input.close() ;
        output.close() ;

    } catch (...) {
        return -1;
    }
	
    return 0;
}