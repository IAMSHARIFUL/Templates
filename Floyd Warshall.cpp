#include<bits/stdc++.h>
#include<string.h>
using namespace std;
#define MAX 400
#define MAX_LEN 510
#define BEGIN 0
#define DEFAULT_VALUE 0
#define MOD 1000000007
#define INF 100000000
int Graph[MAX][MAX];
void initialize(int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i!=j)
            {
                Graph[i][j]=INF;
            }
        }
    }
}
void FloydWarshall(int n)
{
    int i,j,k;
    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(Graph[i][j]>Graph[i][k]+Graph[k][j])
                {
                    Graph[i][j]=Graph[i][k]+Graph[k][j];
                }
            }
        }
    }
}
int main()
{
    int n,i,j,q,m;
    scanf("%d %d",&n,&m);
    initialize(n);
    for(i=0;i<m;i++)
    {
        int x,y,r;
        scanf("%d %d %d",&x,&y,&r);
        x--;
        y--;
        if(x!=y)
        {
            Graph[x][y]=r;
        }
    }
    scanf("%d",&q);
    FloydWarshall(n);
    for(i=0;i<q;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        x--;
        y--;
        if(Graph[x][y]>=INF) printf("-1\n");
        else printf("%d\n",Graph[x][y]);
    }
    return 0;
}
