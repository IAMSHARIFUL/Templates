#include<bits/stdc++.h>
#include<vector>
using namespace std;
#define MAX 100000
#define BEGIN 1
#define NOT_VISITED 0
#define VISITING 1
#define VISITED 2
struct Edge{
    int node;
    int weight;
    Edge(int n,int w)
    {
        node=n;
        weight=w;
    }
};
vector<Edge>Graph[MAX+BEGIN];
vector<Edge>AntiGraph[MAX+BEGIN];
vector<int>Visit;
int visited[MAX+BEGIN];
int P[MAX+BEGIN],members[MAX+BEGIN];
int Find(int x)
{
    if(P[x]==x) return x;
    else
    {
        P[x]=Find(P[x]);
        return P[x];
    }
}
bool Join(int x,int y)
{
    int Pox=Find(x);
    int Poy=Find(y);
    if(Pox==Poy) return false;
    else
    {
        if(members[Pox]>members[Poy])
        {
            members[Pox]+=members[Poy];
            members[Poy]=0;
            P[Poy]=P[Pox];
        }
        else
        {
            members[Poy]+=members[Pox];
            members[Pox]=0;
            P[Pox]=P[Poy];
        }
        return true;
    }
}
void clearVisit(int N)
{
    int i;
    for(i=BEGIN; i<BEGIN+N; i++)
    {
        visited[i]=NOT_VISITED;
    }
}
void clearGraph(int N)
{
    int i;
    for(i=BEGIN; i<BEGIN+N; i++)
    {
        while(Graph[i].size()>0)
        {
            Graph[i].pop_back();
        }
        while(AntiGraph[i].size()>0)
        {
            AntiGraph[i].pop_back();
        }
        P[i]=i;
        visited[i]=NOT_VISITED;
        members[i]=1;
    }
    while(Visit.size()>0)
    {
        Visit.pop_back();
    }
}
void FirstDFS(int node)
{
    visited[node]=VISITED;
    int i;
    for(i=0;i<Graph[node].size();i++)
    {
        if(visited[Graph[node][i].node]!=NOT_VISITED) continue;
        FirstDFS(Graph[node][i].node);
    }
    Visit.push_back(node);
}
int SecondDFS(int node)
{
    int i,compressed=0;
    visited[node]=VISITED;
    for(i=0;i<AntiGraph[node].size();i++)
    {
        if(visited[AntiGraph[node][i].node]!=VISITING) continue;
        if(Join(AntiGraph[node][i].node,node)) compressed++;
        compressed=compressed+SecondDFS(AntiGraph[node][i].node);
    }
    return compressed;
}
int SCC(int N)
{
    int i,j,compressed=0;
    for(i=BEGIN;i<BEGIN+N;i++)
    {
        if(visited[i]==VISITED) continue;
        FirstDFS(i);
        for(j=0;j<Visit.size();j++)
        {
            visited[Visit[j]]=VISITING;
        }
        while(Visit.size()>0)
        {
            if(visited[Visit[Visit.size()-1]]==VISITING)
            {
                compressed=compressed+SecondDFS(Visit[Visit.size()-1]);
            }
            Visit.pop_back();
        }
    }
    return N-compressed;
}
int DFS(int node)
{
    visited[node]=VISITING;
    int i,compressed=0;
    for(i=0;i<Graph[node].size();i++)
    {
        int x=Find(node);
        int y=Find(Graph[node][i].node);
        if(x!=y&&members[y]>0)
        {
            //members[x]+=members[y];
            members[y]=0;
            compressed++;
        }
        if(visited[Graph[node][i].node]!=NOT_VISITED) continue;
        compressed=compressed+DFS(Graph[node][i].node);
    }
    visited[node]=VISITED;
    return compressed;
}
int main()
{
    int T,k;
    scanf("%d",&T);
    for(k=1;k<=T;k++)
    {
        int i,n,m;
        scanf("%d %d",&n,&m);
        clearGraph(n);
        for(i=0;i<m;i++)
        {
            int u,v;
            scanf("%d %d",&u,&v);
            Graph[u].push_back(Edge(v,1));
            AntiGraph[v].push_back(Edge(u,1));
        }
        int result=SCC(n);
        //printf("%d SCC's\n",result);
        clearVisit(n);
        for(i=BEGIN;i<BEGIN+n;i++)
        {
            if(visited[i]!=NOT_VISITED) continue;
            result=result-DFS(i);
            //printf("result=%d (%d)\n",result,i);
        }
        printf("Case %d: %d\n",k,result);
    }
    return 0;
}
